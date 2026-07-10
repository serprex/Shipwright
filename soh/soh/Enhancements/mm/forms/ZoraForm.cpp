#include "soh/Enhancements/mm/forms/FormsCommon.h"

#include <libultraship/bridge.h>
#include "soh/Enhancements/game-interactor/GameInteractor.h"
#include "soh/ShipInit.hpp"

extern "C" {
#include "soh/Enhancements/mm/MMPlayerAnims.h"
}

// Zora form: fast swimming, free diving, no drown timer and lakebed walking, adapted from
// MM's Zora swim actions (2Ship2Harkinian Player_Action_56 / func_80850BF8 / func_80850BA8)
// and grafted onto OOT's swim system:
//
// - Holding A while in any vanilla swim action starts the MM fast swim (pz_fishswim, full 3D
//   movement steered by pitch/yaw), replacing OOT's depth-limited A-dive entirely — diving is
//   simply swimming downward.
// - Releasing A winds down through pz_swimtowait; if that happens deep underwater the form
//   sinks and walks the lakebed. MM implements this with PLAYER_BOOTS_ZORA_UNDERWATER; here
//   the same result comes from temporarily forcing OOT's iron boots, whose sink/walk/land
//   handling already exists on every relevant engine path. Pressing A on the lakebed kicks
//   back off into a swim.
// - MM zeroes underwaterTimer for the Zora every frame (mm z_player.c func_8083BB4C); doing
//   the same here disables OOT's underwater env-hazard timer and drowning damage.
// - Regular paddling gets MM's Zora speed edge via VB_PLAYER_MODIFY_SWIM_SPEED.
//
// VB_PLAYER_RESET_SWIM_STATE keeps func_8083D53C from resetting the custom swim actions
// into the vanilla tread-water action every frame.

typedef struct ZoraSwimState {
    bool fastSwim;      // MM PLAYER_STATE3_8000: in the fish-swim actions
    bool bootsForced;   // iron boots override active (MM PLAYER_BOOTS_ZORA_UNDERWATER)
    s16 pitch;          // MM unk_AAA: dive angle, positive = downward
    s16 floorBumpTimer; // MM unk_B8C: cooldown after bouncing off the lakebed
    f32 speed3D;        // MM unk_B48: speed along the pitched swim direction
} ZoraSwimState;

static ZoraSwimState sSwim;

void ZoraForm_FastSwimAction(Player* player, PlayState* play);
void ZoraForm_SwimToWaitAction(Player* player, PlayState* play);

static bool IsZoraSwimActionFunc(PlayerActionFunc func) {
    return func == ZoraForm_FastSwimAction || func == ZoraForm_SwimToWaitAction;
}

static bool IsVanillaSwimAction(PlayerActionFunc func) {
    return func == Player_Action_8084D610 || func == Player_Action_8084D84C || func == Player_Action_8084DAB4 ||
           func == Player_Action_8084DC48;
}

static bool IsNeutralGroundAction(Player* player) {
    return player->actionFunc == Player_Action_Idle || player->actionFunc == Player_Action_80840450 ||
           player->actionFunc == Player_Action_808407CC || player->actionFunc == Player_Action_80840DE4 ||
           player->actionFunc == Player_Action_808414F8 || player->actionFunc == Player_Action_8084170C;
}

static void RestoreBoots(PlayState* play, Player* player) {
    if (sSwim.bootsForced) {
        sSwim.bootsForced = false;
        player->currentBoots = CUR_EQUIP_VALUE(EQUIP_TYPE_BOOTS) - 1;
        Player_SetBootData(play, player);
    }
}

static void StartFastSwim(PlayState* play, Player* player) {
    RestoreBoots(play, player);
    Player_SetupAction(play, player, ZoraForm_FastSwimAction, 1);
    Player_AnimPlayLoopAdjusted(play, player, (LinkAnimationHeader*)gPlayerAnim_pz_fishswim);
    sSwim.fastSwim = true;
    sSwim.floorBumpTimer = 0;
    // Carry the current motion into the pitched swim direction (MM Action_28)
    sSwim.pitch = Math_Atan2S(player->linearVelocity, -player->actor.velocity.y);
    sSwim.pitch = CLAMP(sSwim.pitch, -0x3000, 0x3000);
    sSwim.speed3D = CLAMP_MIN(sqrtf(SQ(player->linearVelocity) + SQ(player->actor.velocity.y)), 3.0f);
    Player_PlaySfx(&player->actor, NA_SE_PL_SWIM);
}

static void ExitFastSwim(PlayState* play, Player* player) {
    sSwim.fastSwim = false;
    player->actor.shape.rot.x = 0;
}

void ZoraForm_FastSwimAction(Player* player, PlayState* play) {
    Input* input = &play->state.input[0];

    player->stateFlags2 |= PLAYER_STATE2_DISABLE_ROTATION_Z_TARGET;

    // Anim speed follows the swim speed (MM func_808477D0)
    player->skelAnime.playSpeed = CLAMP(sSwim.speed3D * 0.15f, 1.0f, 2.5f) * PLAYER_ANIM_ADJUSTED_SPEED;
    LinkAnimation_Update(play, &player->skelAnime);

    if (!(player->actor.bgCheckFlags & 0x20)) {
        // Breached the surface: ballistic arc until landing or splashing back in
        player->actor.gravity = -1.0f;
        sSwim.pitch = Math_Atan2S(player->linearVelocity, -player->actor.velocity.y);
        player->actor.shape.rot.x = -sSwim.pitch;

        if (player->actor.bgCheckFlags & 1) {
            ExitFastSwim(play, player);
            func_80839F90(player, play);
        }
        return;
    }

    player->actor.gravity = 0.0f;

    if (!CHECK_BTN_ALL(input->cur.button, BTN_A)) {
        // A released: wind down through pz_swimtowait
        Player_SetupAction(play, player, ZoraForm_SwimToWaitAction, 1);
        Player_AnimPlayOnceAdjusted(play, player, (LinkAnimationHeader*)gPlayerAnim_pz_swimtowait);
        return;
    }

    // --- steering (MM func_80850BF8 + Action_56 pitch control) ---
    s8 stickX = input->rel.stick_x;
    s8 stickY = input->rel.stick_y;

    Math_AsymStepToF(&sSwim.speed3D, 9.0f, 1.0f, (fabsf(sSwim.speed3D) * 0.01f) + 0.4f);

    f32 turnCurve = Math_CosS(stickX * 0x10E);
    s16 yawStep = (s16)(((stickX >= 0) ? 1 : -1) * (1.0f - turnCurve) * -1100.0f);
    yawStep = CLAMP(yawStep, -0x1F40, 0x1F40);
    player->yaw += yawStep;

    s16 pitchTarget = stickY * 0xC8;
    if (sSwim.floorBumpTimer != 0) {
        sSwim.floorBumpTimer--;
        pitchTarget = CLAMP_MAX(pitchTarget, (s16)(player->floorPitch - 0xFA0));
    }
    // Near the surface, keep a slight downward pitch unless deliberately pitching up to breach
    if ((sSwim.pitch >= -0x1555) && (player->actor.yDistToWater < (player->ageProperties->unk_24 + 10.0f))) {
        pitchTarget = CLAMP_MIN(pitchTarget, 0x7D0);
    }
    Math_SmoothStepToS(&sSwim.pitch, pitchTarget, 4, 0xFA0, 0x190);

    // Bounce off the lakebed (MM Action_56)
    if ((player->actor.bgCheckFlags & 1) && (sSwim.floorBumpTimer < 8)) {
        sSwim.pitch += (s16)((-player->floorPitch - sSwim.pitch) * 2);
        sSwim.floorBumpTimer = 15;
        Player_PlaySfx(&player->actor, NA_SE_PL_BOUND); // MM NA_SE_PL_BODY_BOUND
    }

    // Head-on wall bonk
    if ((player->actor.bgCheckFlags & 8) && (sSwim.speed3D > 4.0f)) {
        s16 facingWall = player->yaw - (s16)(player->actor.wallYaw + 0x8000);

        if (ABS(facingWall) < 0x1C00) {
            sSwim.speed3D = 2.0f;
            Player_RequestQuake(play, 33267, 3, 12);
            Player_RequestRumble(player, 255, 20, 150, 0);
            Player_PlaySfx(&player->actor, NA_SE_PL_BODY_HIT);
        }
    }

    // Apply the pitched swim velocity (MM func_80850BA8)
    player->linearVelocity = Math_CosS(sSwim.pitch) * sSwim.speed3D;
    player->actor.velocity.y = -Math_SinS(sSwim.pitch) * sSwim.speed3D;
    player->actor.shape.rot.y = player->yaw;
    player->actor.shape.rot.x = -sSwim.pitch;

    if ((play->gameplayFrames % 16) == 0) {
        Player_PlaySfx(&player->actor, NA_SE_PL_SWIM); // MM NA_SE_PL_ZORA_SWIM_LV
    }
}

void ZoraForm_SwimToWaitAction(Player* player, PlayState* play) {
    player->stateFlags2 |= PLAYER_STATE2_DISABLE_ROTATION_Z_TARGET;
    player->actor.gravity = 0.0f;

    Math_StepToF(&player->linearVelocity, 0.0f, 1.0f);
    Math_StepToF(&player->actor.velocity.y, 0.0f, 1.0f);
    Math_ScaledStepToS(&player->actor.shape.rot.x, 0, 0x400);

    if (LinkAnimation_Update(play, &player->skelAnime)) {
        bool deep = player->actor.yDistToWater > (player->ageProperties->unk_2C + 40.0f);

        ExitFastSwim(play, player);
        if (deep) {
            // Sink and walk the lakebed: MM's Zora underwater boots, via OOT's iron boots
            sSwim.bootsForced = true;
        }
        func_80838F18(play, player);
    }
}

static void CleanupZoraSwim(PlayState* play, Player* player) {
    RestoreBoots(play, player);
    if (sSwim.fastSwim) {
        ExitFastSwim(play, player);
        if (IsZoraSwimActionFunc(player->actionFunc)) {
            if (player->stateFlags1 & PLAYER_STATE1_IN_WATER) {
                func_80838F18(play, player);
            } else {
                func_80839F90(player, play);
            }
        }
    }
}

static void RegisterZoraForm() {
    GameInteractor::Instance->RegisterGameHook<GameInteractor::ShouldActorUpdate>([](void* actorRef, bool*) {
        Actor* actor = (Actor*)actorRef;
        PlayState* play = gPlayState;

        if (play == nullptr || actor != &GET_PLAYER(play)->actor) {
            return;
        }
        Player* player = GET_PLAYER(play);

        if (PlayerForm_GetApplied() != PLAYER_SHIPFORM_ZORA) {
            if (sSwim.fastSwim || sSwim.bootsForced) {
                CleanupZoraSwim(play, player);
            }
            return;
        }

        // Our action was replaced externally (damage, cutscene, grab)
        if (sSwim.fastSwim && !IsZoraSwimActionFunc(player->actionFunc)) {
            ExitFastSwim(play, player);
        }

        // Iron-boots override while settled deep underwater
        if (sSwim.bootsForced) {
            bool stillUnder = (player->stateFlags1 & PLAYER_STATE1_IN_WATER) &&
                              (player->actor.yDistToWater > player->ageProperties->unk_2C);

            if (!stillUnder || sSwim.fastSwim) {
                RestoreBoots(play, player);
            } else if (player->currentBoots != PLAYER_BOOTS_IRON) {
                // Reassert after pause-menu equipment changes
                player->currentBoots = PLAYER_BOOTS_IRON;
                Player_SetBootData(play, player);
            }
        }

        if (Player_InBlockingCsMode(play, player) ||
            (player->stateFlags1 &
             (PLAYER_STATE1_IN_CUTSCENE | PLAYER_STATE1_GETTING_ITEM | PLAYER_STATE1_CARRYING_ACTOR))) {
            return;
        }

        if (CHECK_BTN_ALL(play->state.input[0].press.button, BTN_A)) {
            // Holding A in any vanilla swim state starts the fast swim (this replaces the
            // vanilla depth-limited dive), and A on the lakebed kicks back off into a swim
            if (IsVanillaSwimAction(player->actionFunc) || player->actionFunc == ZoraForm_SwimToWaitAction) {
                StartFastSwim(play, player);
            } else if (sSwim.bootsForced && (player->actor.bgCheckFlags & 1) && IsNeutralGroundAction(player)) {
                StartFastSwim(play, player);
                sSwim.pitch = -0x1800; // kick off slightly upward
                sSwim.speed3D = 5.0f;
            }
        }
    });

    // MM zeroes the Zora's underwater timer every frame; this kills both the env-hazard
    // (drowning) timer and the deep-underwater face textures
    GameInteractor::Instance->RegisterGameHook<GameInteractor::OnPlayerUpdate>([]() {
        if (PlayerForm_GetApplied() == PLAYER_SHIPFORM_ZORA && gPlayState != nullptr) {
            GET_PLAYER(gPlayState)->underwaterTimer = 0;
        }
    });

    // Keep func_8083D53C from resetting the custom swim actions into the vanilla tread
    REGISTER_VB_SHOULD(VB_PLAYER_RESET_SWIM_STATE, {
        Player* player = va_arg(args, Player*);

        if (IsZoraSwimActionFunc(player->actionFunc)) {
            *should = false;
        }
    });

    // MM's Zora paddles noticeably faster than the other forms even outside the fast swim
    REGISTER_VB_SHOULD(VB_PLAYER_MODIFY_SWIM_SPEED, {
        va_arg(args, Player*);
        f32* swimSpeed = va_arg(args, f32*);

        if (PlayerForm_GetApplied() == PLAYER_SHIPFORM_ZORA) {
            *swimSpeed *= 1.5f;
        }
    });
}

static RegisterShipInitFunc initFunc(RegisterZoraForm);
