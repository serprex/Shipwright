#include "ActorAccessibility.h"
#include "soh/OTRGlobals.h"

#include <map>
#include <random>

#include <functions.h>
#include <macros.h>
#include <stdio.h>
#include <string>
#include <float.h>

extern "C" {
#include "overlays/actors/ovl_Obj_Switch/z_obj_switch.h"
#include "overlays/actors/ovl_Bg_Bdan_Switch/z_bg_bdan_switch.h"
#include "overlays/actors/ovl_Boss_Goma/z_boss_goma.h"
#include "overlays/actors/ovl_En_Karebaba/z_en_karebaba.h"
#include "overlays/actors/ovl_En_Box/z_en_box.h"
#include "overlays/actors/ovl_Obj_Syokudai/z_obj_syokudai.h"
#include "overlays/actors/ovl_En_Dog/z_en_dog.h"
#include "overlays/actors/ovl_En_Ba/z_en_ba.h"
#include "overlays/actors/ovl_En_Fz/z_en_fz.h"
#include "overlays/actors/ovl_En_Ice_Hono/z_en_ice_hono.h"
#include "overlays/actors/ovl_En_Eiyer/z_en_eiyer.h"
#include "overlays/actors/ovl_En_G_Switch/z_en_g_switch.h"
#include "overlays/actors/ovl_Door_Shutter/z_door_shutter.h"
#include "overlays/actors/ovl_Bg_Po_Event/z_bg_po_event.h"
#include "overlays/actors/ovl_En_Kakasi2/z_en_kakasi2.h"

void EnBox_WaitOpen(EnBox*, PlayState*);
void EnKarebaba_DeadItemDrop(EnKarebaba*, PlayState*);
void EnDog_FollowPlayer(EnDog*, PlayState*);
s8 EnDog_CanFollow(EnDog*, PlayState*);
void EnEiyer_Die(EnEiyer*, PlayState*);
void EnEiyer_Dead(EnEiyer*, PlayState*);
void EnGSwitch_SilverRupeeIdle(EnGSwitch*, PlayState*);

extern u8 sBgPoEventPuzzleState;
}

// User data for the general helper VA.
typedef struct {
    s16 currentScene;
    s8 currentRoom;
    bool currentRoomClear;
} GeneralHelperData;

typedef struct {
    f32 linearVelocity;
    int framesUntilChime;
} AudioCompassData;

void accessible_grotto(AccessibleActor* actor) {
    if ((actor->actor->params & 0x300) == 0) {
        ActorAccessibility_PlaySoundForActor(actor, 0, NA_SE_EV_DROP_FALL, false);
    }
}

void accessible_torches(AccessibleActor* actor) {
    ObjSyokudai* torche = (ObjSyokudai*)actor->actor;
    // temporary torches
    if ((actor->actor->params) == 4230 || (actor->actor->params) == 4220 || (actor->actor->params) == 4227 ||
        (actor->actor->params) == 4380 || actor->actor->params == 4321) {
        if (torche->litTimer != 0) {
            actor->policy.volume = 0.1;
            if ((actor->frameCount & 31) != 0) {
                return;
            }
            ActorAccessibility_PlaySoundForActor(actor, 0, NA_SE_IT_BOMB_IGNIT, false);
        } else {
            if (actor->policy.volume != 1.0) {
                actor->policy.volume = 1.0;
            }
        }
        if ((actor->frameCount & 31) != 0) {
            return;
        }
        ActorAccessibility_PlaySoundForActor(actor, 0, NA_SE_IT_BOMB_IGNIT, false);
    }
    if ((actor->frameCount & 31) != 0) {
        return;
    }

    // unlit permanent torches
    if ((actor->actor->params) == 8192) {
        if (torche->litTimer == 0) {
            ActorAccessibility_PlaySoundForActor(actor, 0, NA_SE_IT_BOMB_IGNIT, false);
        } else {
            ActorAccessibility_PlaySoundForActor(actor, 0, NA_SE_EN_ANUBIS_FIRE, false);
        }
    }
    // lit permanent torches
    if ((actor->actor->params) == 9216 || (actor->actor->params) == 962) {

        actor->policy.volume = 0.5;
        actor->policy.distance = 200.0;
        ActorAccessibility_PlaySoundForActor(actor, 0, NA_SE_EN_ANUBIS_FIRE, false);
    }
}

void accessible_switch(AccessibleActor* actor) {
    Player* player = GET_PLAYER(actor->play);
    ObjSwitch* sw = (ObjSwitch*)actor->actor;
    Vec3f& scale = actor->actor->scale;
    if ((actor->actor->params & 7) == 0) {
        if (actor->xyzDistToPlayer > 800) {
            return;
        }
        if (scale.y >= 33.0f / 200.0f) {
            if (actor->play->sceneNum == 0 && actor->play->roomCtx.curRoom.num == 5 && actor->xzDistToPlayer < 20) {
                ActorAccessibility_PlaySoundForActor(actor, 0, NA_SE_EV_DIAMOND_SWITCH, false);
            }
            if ((actor->frameCount & 31) != 0) {
                return;
            }
            ActorAccessibility_PlaySoundForActor(actor, 1, NA_SE_EV_FOOT_SWITCH, false);
        }
    } else if ((actor->frameCount & 31) != 0) {
        return;
    } else if ((actor->actor->params & 7) == 1) {
        if (actor->xyzDistToPlayer > 800) {
            return;
        }
        if (scale.y >= 33.0f / 200.0f) { //(!(Flags_GetSwitch(actor->play, (actor->params >> 8 & 0x3F)))) {
            ActorAccessibility_PlaySoundForActor(actor, 0, NA_SE_IT_HAMMER_HIT, false);
        }
    } else if ((actor->actor->params & 7) == 2) {
        if (sw->eyeTexIndex == 0) {
            actor->policy.aimAssist.isProvider = true;
            actor->policy.ydist = 1000;
            ActorAccessibility_PlaySoundForActor(actor, 0, NA_SE_EV_FOOT_SWITCH, false);
        }
    } else {
        if (actor->xyzDistToPlayer > 800) {
            return;
        }
        ActorAccessibility_PlaySoundForActor(actor, 0, NA_SE_EV_DIAMOND_SWITCH, false);
    }
}

void accessible_larva(AccessibleActor* actor) {
    if (actor->actor->bgCheckFlags == 0) {
        ActorAccessibility_PlaySoundForActor(actor, 0, NA_SE_EN_GOMA_BJR_EGG1, false);
    }
}

void accessible_area_change(AccessibleActor* actor) {
    Player* player = GET_PLAYER(actor->play);
    actor->policy.distance = 1500;
    actor->policy.ydist = 2000;

    if (actor->yDistToPlayer > 500.0 && actor->sceneIndex != SCENE_DEATH_MOUNTAIN_TRAIL &&
        actor->play->sceneNum != SCENE_HYRULE_FIELD && actor->play->sceneNum != 82) {
        return;
    }

    if (actor->play->sceneNum == SCENE_HYRULE_FIELD) {
        if (actor->xzDistToPlayer > 700) {
            actor->policy.distance = actor->xzDistToPlayer * 1.2;
            if (actor->xzDistToPlayer > 8000) {
                return;
            }
        } else {
            actor->policy.distance = 1500;
            if (actor->xzDistToPlayer > 1500) {
                return;
            }
        }
    } else if (actor->play->sceneNum == SCENE_KAKARIKO_VILLAGE) {
        if (actor->sceneIndex == SCENE_GRAVEYARD || actor->sceneIndex == SCENE_HYRULE_FIELD ||
            actor->sceneIndex == SCENE_DEATH_MOUNTAIN_TRAIL) {
            actor->policy.runsAlways = true;
            actor->policy.ydist = 5000;
            if (actor->xzDistToPlayer > 700) {
                if (actor->sceneIndex == SCENE_HYRULE_FIELD) {
                    actor->policy.distance = actor->xyzDistToPlayer * 1.4;
                } else {
                    actor->policy.distance = actor->xyzDistToPlayer * 1.2;
                }
                if (actor->xzDistToPlayer > 8000) {
                    return;
                }
            } else {
                actor->policy.distance = 1500;
                if (actor->xzDistToPlayer > 1500) {
                    return;
                }
            }
        } else if (actor->sceneIndex == SCENE_BOTTOM_OF_THE_WELL) {
            if (!(((gSaveContext.eventChkInf[6]) >> (7)) & 1))
                return;
        } else {
            actor->policy.ydist = 500;
            actor->policy.distance = 1000;
            if (actor->xzDistToPlayer > 1000) {
                return;
            }
        }
    } else if (actor->play->sceneNum == SCENE_LOST_WOODS ||
               actor->play->sceneNum == SCENE_CASTLE_COURTYARD_GUARDS_DAY ||
               actor->play->sceneNum == SCENE_CASTLE_COURTYARD_GUARDS_NIGHT) {
        actor->policy.distance = 1000;
        if (actor->xzDistToPlayer > 1000) {
            return;
        }
    } else {
        if (actor->xzDistToPlayer > 1500) {
            return;
        }
    }
    if (actor->sceneIndex == SCENE_KOKIRI_FOREST || actor->sceneIndex == SCENE_LOST_WOODS) {
        if (actor->play->sceneNum == SCENE_LOST_WOODS &&
            gSaveContext.entranceIndex != ENTR_LOST_WOODS_BRIDGE_EAST_EXIT &&
            gSaveContext.entranceIndex != ENTR_LOST_WOODS_BRIDGE_WEST_EXIT) {
            return;
        }
        if (actor->play->sceneNum == SCENE_KOKIRI_FOREST && actor->pos.y < 0) {
            ActorAccessibility_PlaySoundForActor(actor, 0, NA_SE_EV_HORSE_RUN_LEVEL, false);
        } else {
            ActorAccessibility_PlaySoundForActor(actor, 0, NA_SE_EV_SARIA_MELODY, false);
        }
        // kokiri forest and lost woods
    } else if (actor->play->sceneNum >= SCENE_DEKU_TREE_BOSS && actor->play->sceneNum <= SCENE_GANONDORF_BOSS) {
        return; // dont check for entrances while in boss rooms
    } else if (actor->sceneIndex == SCENE_HYRULE_FIELD) {
        ActorAccessibility_PlaySoundForActor(actor, 0, NA_SE_EV_HORSE_RUN_LEVEL, false);
    } else if (actor->sceneIndex <= SCENE_GERUDO_TRAINING_GROUND) {
        ActorAccessibility_PlaySoundForActor(actor, 0, NA_SE_EV_FANTOM_WARP_S, false);
    } else if (actor->sceneIndex >= SCENE_MARKET_ENTRANCE_DAY && actor->sceneIndex <= SCENE_MARKET_ENTRANCE_RUINS) {
        if (actor->play->sceneNum >= SCENE_MARKET_DAY && actor->play->sceneNum <= SCENE_MARKET_RUINS) {
            ActorAccessibility_PlaySoundForActor(actor, 0, NA_SE_EV_HORSE_RUN_LEVEL, false);
        } else {
            ActorAccessibility_PlaySoundForActor(actor, 0, NA_SE_EV_SMALL_DOG_BARK, false);
        }
    } else if (actor->sceneIndex >= SCENE_BACK_ALLEY_DAY && actor->sceneIndex <= SCENE_MARKET_NIGHT) {
        ActorAccessibility_PlaySoundForActor(actor, 0, NA_SE_EV_SMALL_DOG_BARK, false);
    } else if (actor->sceneIndex >= SCENE_MARKET_RUINS && actor->sceneIndex <= SCENE_TEMPLE_OF_TIME_EXTERIOR_RUINS) {
        ActorAccessibility_PlaySoundForActor(actor, 0, NA_SE_EV_STONE_BOUND, false);
    } else if (actor->play->sceneNum == SCENE_TEMPLE_OF_TIME) {
        ActorAccessibility_PlaySoundForActor(actor, 0, NA_SE_EV_SMALL_DOG_BARK, false);
    } else if (actor->sceneIndex == SCENE_CASTLE_COURTYARD_GUARDS_DAY ||
               actor->sceneIndex == SCENE_CASTLE_COURTYARD_GUARDS_NIGHT) {
        ActorAccessibility_PlaySoundForActor(actor, 0, NA_SE_EN_MUSI_SINK, false);
    } else if (actor->sceneIndex == SCENE_KAKARIKO_VILLAGE) {
        ActorAccessibility_PlaySoundForActor(actor, 0, NA_SE_EV_CHICKEN_CRY_M, false);
    } else if (actor->sceneIndex == SCENE_GRAVEYARD) {
        ActorAccessibility_PlaySoundForActor(actor, 0, NA_SE_EN_PO_APPEAR, false);
    } else if (actor->sceneIndex == SCENE_ZORAS_RIVER || actor->sceneIndex == SCENE_ZORAS_DOMAIN ||
               actor->sceneIndex == SCENE_ZORAS_FOUNTAIN) {
        ActorAccessibility_PlaySoundForActor(actor, 0, NA_SE_EV_RIVER_STREAM_S, false);
    } else if (actor->sceneIndex == SCENE_SACRED_FOREST_MEADOW) {
    } else if (actor->sceneIndex == SCENE_LAKE_HYLIA) {
        ActorAccessibility_PlaySoundForActor(actor, 0, NA_SE_EV_WATER_WALL, false);
    } else if (actor->sceneIndex == SCENE_GERUDO_VALLEY || actor->sceneIndex == SCENE_GERUDOS_FORTRESS) {
        ActorAccessibility_PlaySoundForActor(actor, 0, NA_SE_EN_GERUDOFT_BREATH, false);
    } else if (actor->sceneIndex == SCENE_DESERT_COLOSSUS || actor->sceneIndex == SCENE_HAUNTED_WASTELAND) {
        ActorAccessibility_PlaySoundForActor(actor, 0, NA_SE_EV_SAND_STORM, false);
    } else if (actor->sceneIndex == SCENE_OUTSIDE_GANONS_CASTLE || actor->sceneIndex == SCENE_HYRULE_CASTLE) {
        ActorAccessibility_PlaySoundForActor(actor, 0, NA_SE_EV_BRIDGE_OPEN, false);
    } else if (actor->sceneIndex == SCENE_DEATH_MOUNTAIN_TRAIL) {
        ActorAccessibility_PlaySoundForActor(actor, 0, NA_SE_EN_DODO_K_ROLL, false);
    } else if (actor->sceneIndex == SCENE_DEATH_MOUNTAIN_CRATER) {
        ActorAccessibility_PlaySoundForActor(actor, 0, NA_SE_EN_DODO_K_LAVA, false);
    } else if (actor->sceneIndex == SCENE_GORON_CITY) {
        ActorAccessibility_PlaySoundForActor(actor, 0, NA_SE_EN_DARUNIA_HIT_BREAST, false);
    } else if (actor->sceneIndex == SCENE_LON_LON_RANCH) {
        ActorAccessibility_PlaySoundForActor(actor, 0, NA_SE_EV_COW_CRY, false);
    } else if (actor->sceneIndex >= SCENE_DEKU_TREE_BOSS && actor->sceneIndex <= SCENE_GANONDORF_BOSS) {
        return;
    } else {
        actor->policy.distance = 500;
        if (actor->play->sceneNum == SCENE_GRAVEYARD) {
            actor->policy.ydist = 0;
        }
        ActorAccessibility_PlaySoundForActor(actor, 0, NA_SE_OC_DOOR_OPEN, false);
    }
}

void accessible_en_guard(AccessibleActor* actor) {
    Player* player = GET_PLAYER(actor->play);
    f32 guardsfx = NA_SE_IT_SWORD_IMPACT;
    if (fabs(actor->actor->world.pos.x - player->actor.world.pos.x) >
        fabs(actor->actor->world.pos.z - player->actor.world.pos.z)) {
        if (fabs(actor->actor->shape.rot.y - 16384) < 1000) {
            if (actor->actor->world.pos.x < player->actor.world.pos.x) {
                ActorAccessibility_PlaySoundForActor(actor, 0, guardsfx, false);
                ActorAccessibility_SetSoundPitch(actor, 0, 2.0);
            } else {
                ActorAccessibility_PlaySoundForActor(actor, 0, guardsfx, false);
                ActorAccessibility_SetSoundPitch(actor, 0, 0.2);
            }
        } else if ((actor->actor->shape.rot.y + 16384) < 1000) {
            if (actor->actor->world.pos.x < player->actor.world.pos.x) {
                ActorAccessibility_PlaySoundForActor(actor, 0, guardsfx, false);
                ActorAccessibility_SetSoundPitch(actor, 0, 0.2);
            } else {
                ActorAccessibility_PlaySoundForActor(actor, 0, guardsfx, false);
                ActorAccessibility_SetSoundPitch(actor, 0, 2.0);
            }
        } else {
            ActorAccessibility_PlaySoundForActor(actor, 0, guardsfx, false);
            ActorAccessibility_SetSoundPitch(actor, 0, 1.0);
        }
    } else {
        if (fabs(actor->actor->shape.rot.y) < 1000) {
            if (actor->actor->world.pos.z < player->actor.world.pos.z) {
                ActorAccessibility_PlaySoundForActor(actor, 0, guardsfx, false);
                ActorAccessibility_SetSoundPitch(actor, 0, 2.0);
            } else {
                ActorAccessibility_PlaySoundForActor(actor, 0, guardsfx, false);
                ActorAccessibility_SetSoundPitch(actor, 0, 0.2);
            }
        } else if (fabs(actor->actor->shape.rot.y + 32768) < 1000) {
            if (actor->actor->world.pos.z < player->actor.world.pos.z) {
                ActorAccessibility_PlaySoundForActor(actor, 0, guardsfx, false);
                ActorAccessibility_SetSoundPitch(actor, 0, 0.2);
            } else {
                ActorAccessibility_PlaySoundForActor(actor, 0, guardsfx, false);
                ActorAccessibility_SetSoundPitch(actor, 0, 2.0);
            }
        } else {
            ActorAccessibility_PlaySoundForActor(actor, 0, guardsfx, false);
            ActorAccessibility_SetSoundPitch(actor, 0, 1.0);
        }
    }
}

void accessible_en_dogs(AccessibleActor* actor) {
    EnDog* dog = (EnDog*)actor->actor;
    if (EnDog_CanFollow(dog, actor->play) == 1) {
        dog->actionFunc = EnDog_FollowPlayer;
        ActorAccessibility_PlaySoundForActor(actor, 0, NA_SE_EV_DIAMOND_SWITCH, false);
        ActorAccessibility_SetSoundPitch(actor, 0, 1.0);
    }
    if ((actor->frameCount & 31) != 0) {
        return;
    }
    if (actor->actor->params == 608 || actor->actor->params == 336 || actor->actor->params == 304 ||
        actor->actor->params == 3088 || actor->actor->params == 2576 || actor->actor->params < 0) {
        ActorAccessibility_PlaySoundForActor(actor, 0, NA_SE_EV_SMALL_DOG_BARK, false);

        ActorAccessibility_SetSoundPitch(actor, 0, 2.0);
    } else {
        ActorAccessibility_PlaySoundForActor(actor, 0, NA_SE_EV_SMALL_DOG_BARK, false);
        ActorAccessibility_SetSoundPitch(actor, 0, 0.5);
    }
}

void accessible_goma(AccessibleActor* actor) {
    BossGoma* goma = (BossGoma*)actor->actor;
    if (goma->visualState == 0) {
        ActorAccessibility_PlaySoundForActor(actor, 0, NA_SE_EV_DIAMOND_SWITCH, false);
    }
}

void accessible_sticks(AccessibleActor* actor) {
    EnKarebaba* baba = (EnKarebaba*)actor->actor;

    if (baba->actionFunc != EnKarebaba_DeadItemDrop)
        return;
    if (actor->actor->flags == 80) {
        ActorAccessibility_PlaySoundForActor(actor, 0, NA_SE_EN_NUTS_DAMAGE, false);
    }
}

void accessible_cucco(AccessibleActor* actor) {
    if (actor->actor->params == 14) {

    } else if (actor->actor->params == 13) {
        ActorAccessibility_PlaySoundForActor(actor, 0, NA_SE_EV_CHICKEN_CRY_N, false);
        ActorAccessibility_SetSoundPitch(actor, 0, 1.5);
    } else {
        ActorAccessibility_PlaySoundForActor(actor, 0, NA_SE_EV_CHICKEN_CRY_N, false);
    }
}

bool accessible_general_helper_init(AccessibleActor* actor) {
    GeneralHelperData* data = (GeneralHelperData*)malloc(sizeof(GeneralHelperData));
    if (data == nullptr)
        return false;
    data->currentRoom = -1;
    data->currentRoomClear = false;
    data->currentScene = -1;

    actor->userData = data;
    return true;
}

void accessible_general_helper_cleanup(AccessibleActor* actor) {
    free(actor->userData);
    actor->userData = nullptr;
}

void accessible_va_general_helper(AccessibleActor* actor) {
    GeneralHelperData* data = (GeneralHelperData*)actor->userData;
    if (data->currentScene == actor->play->sceneNum && data->currentRoom != actor->play->roomCtx.curRoom.num) {
        ActorAccessibility_AnnounceRoomNumber(actor->play);
        data->currentRoom = actor->play->roomCtx.curRoom.num;
        data->currentRoomClear = Flags_GetClear(actor->play, data->currentRoom);
    }
    if (data->currentScene != actor->play->sceneNum) {
        ActorAccessibility_InterpretCurrentScene(actor->play);
        data->currentScene = actor->play->sceneNum;
        data->currentRoom = actor->play->roomCtx.curRoom.num;
        data->currentRoomClear = Flags_GetClear(actor->play, data->currentRoom);
    }
    // Report when a room is completed.
    if (!data->currentRoomClear && Flags_GetClear(actor->play, data->currentRoom)) {
        data->currentRoomClear = Flags_GetClear(actor->play, data->currentRoom);
        ActorAccessibility_AnnounceRoomNumber(actor->play);
    }
}

bool accessible_audio_compass_init(AccessibleActor* actor) {
    AudioCompassData* data = (AudioCompassData*)malloc(sizeof(AudioCompassData));
    if (data == nullptr)
        return false;
    data->linearVelocity = 0;
    data->framesUntilChime = 0;

    actor->userData = data;
    return true;
}

void accessible_audio_compass_cleanup(AccessibleActor* actor) {
    free(actor->userData);
}

void accessible_audio_compass(AccessibleActor* actor) {
    Player* player = GET_PLAYER(actor->play);
    OSContPad* trackerButtonsPressed =
        std::dynamic_pointer_cast<LUS::ControlDeck>(Ship::Context::GetInstance()->GetControlDeck())->GetPads();
    AudioCompassData* data = (AudioCompassData*)actor->userData;
    bool compassCombo = trackerButtonsPressed != nullptr && trackerButtonsPressed[0].button & BTN_DDOWN &&
                        trackerButtonsPressed[0].button & BTN_L;
    actor->pos = player->actor.world.pos;
    actor->pos.z -= 50;

    if (data->framesUntilChime > 0)
        data->framesUntilChime--;
    if (compassCombo && data->framesUntilChime <= 0) {
        ActorAccessibility_PlaySoundForActor(actor, 0, actor->policy.sound, false);
        data->framesUntilChime = 30;
    }
}

void accessible_stick_warning(AccessibleActor* actor) {
    Player* player = GET_PLAYER(actor->play);
    actor->pos = player->actor.world.pos;
    actor->pos.z -= 50;
    if (fabs(player->unk_860 - 25) < 24.0 && player->heldItemId == 0) {
        ActorAccessibility_PlaySoundForActor(actor, 0, NA_SE_SY_WARNING_COUNT_N, false);
    }

    if (Player_HoldsHookshot(player) && player->heldActor != NULL && player->actor.scale.y >= 0.0f &&
        (player->stateFlags1 & PLAYER_STATE1_FIRST_PERSON)) {
        CollisionPoly* colPoly;
        s32 bgId;
        Vec3f hookshotEnd;
        Vec3f firstHit;
        f32 hookshotLength = ((player->heldItemAction == PLAYER_IA_HOOKSHOT) ? 380.0f : 770.0f) *
                             CVarGetFloat(CVAR_CHEAT("HookshotReachMultiplier"), 1.0f);
        hookshotEnd.x = player->heldActor->world.pos.x + Math_SinS(player->heldActor->world.rot.y) *
                                                             Math_SinS(-player->heldActor->world.rot.x) *
                                                             hookshotLength;
        hookshotEnd.y = player->heldActor->world.pos.y + Math_SinS(-player->heldActor->world.rot.x) * hookshotLength;
        hookshotEnd.z = player->heldActor->world.pos.z + Math_CosS(player->heldActor->world.rot.y) *
                                                             Math_CosS(-player->heldActor->world.rot.x) *
                                                             hookshotLength;
        if (BgCheck_AnyLineTest3(&actor->play->colCtx, &player->heldActor->world.pos, &hookshotEnd, &firstHit, &colPoly,
                                 1, 1, 1, 1, &bgId)) {
            if (SurfaceType_IsHookshotSurface(&actor->play->colCtx, colPoly, bgId)) {
                ActorAccessibility_PlaySoundForActor(actor, 1, NA_SE_IT_HOOKSHOT_STICK_OBJ, false);
            }
        }
    }
}

void ActorAccessibility_InitActors() {
    const int Npc_Frames = 35;
    ActorAccessibilityPolicy policy;
    ActorAccessibility_InitPolicy(&policy, "Rock", NA_SE_EN_OCTAROCK_ROCK);
    ActorAccessibility_AddSupportedActor(ACTOR_EN_ISHI, policy);

    ActorAccessibility_InitPolicy(&policy, "Story NPCs", NA_SE_VO_NA_HELLO_0);
    policy.englishName = "Mido";
    policy.n = Npc_Frames;
    policy.distance = 1000;
    policy.pitch = 1.1;
    ActorAccessibility_AddSupportedActor(ACTOR_EN_MD, policy);
    policy.englishName = "Malon";
    policy.distance = 500;
    ActorAccessibility_AddSupportedActor(ACTOR_EN_MA1, policy);
    policy.englishName = "Talon";
    ActorAccessibility_AddSupportedActor(ACTOR_EN_TA, policy);
    policy.englishName = "King Zora";
    ActorAccessibility_AddSupportedActor(ACTOR_EN_KZ, policy);
    policy.englishName = "Diving Zora";
    ActorAccessibility_AddSupportedActor(ACTOR_EN_DIVING_GAME, policy);
    policy.englishName = "Child Zelda";
    ActorAccessibility_AddSupportedActor(ACTOR_EN_ZL4, policy);
    policy.englishName = "Ingo";
    ActorAccessibility_AddSupportedActor(ACTOR_EN_IN, policy);
    policy.englishName = "Cucco Lady";
    ActorAccessibility_AddSupportedActor(ACTOR_EN_NIW_LADY, policy);
    policy.englishName = "Windmill Man";
    ActorAccessibility_AddSupportedActor(ACTOR_EN_FU, policy);
    policy.englishName = "Durania";
    ActorAccessibility_AddSupportedActor(ACTOR_EN_DU, policy);
    policy.englishName = "Owl";
    ActorAccessibility_AddSupportedActor(ACTOR_EN_OWL, policy);
    ActorAccessibility_InitPolicy(&policy, "Cursed Skulltula Person", NA_SE_VO_ST_DAMAGE);
    ActorAccessibility_AddSupportedActor(ACTOR_EN_SSH, policy);
    ActorAccessibility_InitPolicy(&policy, "Catching Guards", accessible_en_guard);
    policy.n = 10;
    policy.distance = 500;
    policy.ydist = 300;
    ActorAccessibility_AddSupportedActor(ACTOR_EN_HEISHI1, policy);
    ActorAccessibility_AddSupportedActor(ACTOR_EN_HEISHI3, policy);

    ActorAccessibility_InitPolicy(&policy, "Passive Guards", NA_SE_IT_SWORD_IMPACT);
    ActorAccessibility_AddSupportedActor(ACTOR_EN_HEISHI2, policy);
    ActorAccessibility_AddSupportedActor(ACTOR_EN_HEISHI4, policy);

    ActorAccessibility_InitPolicy(&policy, "Shopkeepers", NA_SE_VO_NA_HELLO_1);
    policy.pitch = 0.6;
    policy.n = 30;
    policy.englishName = "Shooting Gallery Man";
    ActorAccessibility_AddSupportedActor(ACTOR_EN_SYATEKI_MAN, policy);
    policy.englishName = "Bombchu Bowling Alley Lady";
    ActorAccessibility_AddSupportedActor(ACTOR_EN_BOM_BOWL_MAN, policy);
    policy.englishName = "Shop Keeper";
    ActorAccessibility_AddSupportedActor(ACTOR_EN_OSSAN, policy);
    policy.englishName = "Potion Shop Granny";
    ActorAccessibility_AddSupportedActor(ACTOR_EN_DS, policy);

    // general NPCs
    ActorAccessibility_InitPolicy(&policy, "Kokiri Child", NA_SE_VO_NB_LAUGH);
    policy.n = Npc_Frames;
    policy.pitch = 1.1;
    ActorAccessibility_AddSupportedActor(ACTOR_EN_KO, policy);
    policy.englishName = "Zoras";
    ActorAccessibility_AddSupportedActor(ACTOR_EN_ZO, policy);
    policy.englishName = "Gorons";
    ActorAccessibility_AddSupportedActor(ACTOR_EN_GO2, policy);
    policy.englishName = "Saria";
    ActorAccessibility_AddSupportedActor(ACTOR_EN_SA, policy);
    policy.englishName = "King Zora";
    ActorAccessibility_AddSupportedActor(ACTOR_EN_KZ, policy);
    policy.englishName = "Lakeside Professor";
    ActorAccessibility_AddSupportedActor(ACTOR_EN_MK, policy);
    policy.englishName = "Graveyard Kid";
    ActorAccessibility_AddSupportedActor(ACTOR_EN_CS, policy);
    policy.englishName = "Dampe (Alive)";
    ActorAccessibility_AddSupportedActor(ACTOR_EN_TK, policy);
    policy.englishName = "Happy Mask Shop Customer";
    ActorAccessibility_AddSupportedActor(ACTOR_EN_GUEST, policy);
    policy.englishName = "Running Man";
    ActorAccessibility_AddSupportedActor(ACTOR_EN_MM, policy);
    ActorAccessibility_AddSupportedActor(ACTOR_EN_MM2, policy);
    policy.englishName = "Sheik";
    ActorAccessibility_AddSupportedActor(ACTOR_EN_XC, policy);
    policy.englishName = "Market Npc";
    ActorAccessibility_AddSupportedActor(ACTOR_EN_HY, policy);
    policy.englishName = "Girl Chassing Cucco";
    ActorAccessibility_AddSupportedActor(ACTOR_EN_NIW_GIRL, policy);
    policy.englishName = "Honey & Darling";
    ActorAccessibility_AddSupportedActor(ACTOR_EN_TG, policy);
    policy.englishName = "Haggling Townspeople";
    ActorAccessibility_AddSupportedActor(ACTOR_EN_MU, policy);
    policy.englishName = "Skull Kid";
    ActorAccessibility_AddSupportedActor(ACTOR_EN_SKJ, policy);
    policy.englishName = "Boss Carpenter";
    ActorAccessibility_AddSupportedActor(ACTOR_EN_TORYO, policy);
    policy.englishName = "Carpenters (Kakariko)";
    ActorAccessibility_AddSupportedActor(ACTOR_EN_DAIKU_KAKARIKO, policy);
    policy.englishName = "Kakariko Rooftop Man";
    ActorAccessibility_AddSupportedActor(ACTOR_EN_ANI, policy);
    policy.englishName = "Uncursed Skulltula Person";
    ActorAccessibility_AddSupportedActor(ACTOR_EN_STH, policy);
    policy.englishName = "Gossip Stone";
    policy.pitch = 0.75;
    ActorAccessibility_AddSupportedActor(ACTOR_EN_GS, policy);
    ActorAccessibility_InitPolicy(&policy, "Scarecrow", NA_SE_EV_KAKASHI_SWING);
    ActorAccessibility_AddSupportedActor(ACTOR_EN_KAKASI, policy);
    ActorAccessibility_AddSupportedActor(ACTOR_EN_KAKASI3, policy);

    ActorAccessibility_InitPolicy(&policy, "Dogs", accessible_en_dogs);
    policy.n = 1;
    ActorAccessibility_AddSupportedActor(ACTOR_EN_DOG, policy);

    ActorAccessibility_InitPolicy(&policy, "Horses", NA_SE_EV_HORSE_NEIGH);
    policy.n = 30;
    ActorAccessibility_AddSupportedActor(ACTOR_EN_HORSE_NORMAL, policy);
    ActorAccessibility_InitPolicy(&policy, "Cows", NA_SE_EV_COW_CRY_LV);
    policy.n = 30;
    ActorAccessibility_AddSupportedActor(ACTOR_EN_COW, policy);
    ActorAccessibility_InitPolicy(&policy, "Cuccos", accessible_cucco);
    ActorAccessibility_AddSupportedActor(ACTOR_EN_NIW, policy);
    ActorAccessibility_InitPolicy(&policy, "Bush", NA_SE_PL_PULL_UP_PLANT);
    ActorAccessibility_AddSupportedActor(ACTOR_EN_KUSA, policy);
    ActorAccessibility_InitPolicy(&policy, "Trees", NA_SE_EV_TREE_CUT);
    ActorAccessibility_AddSupportedActor(ACTOR_EN_WOOD02, policy);
    ActorAccessibility_InitPolicy(&policy, "Scarecrow Spawn", [](AccessibleActor* actor) {
        if ((actor->frameCount & 63) == 0) {
            EnKakasi2* kakasi = (EnKakasi2*)actor->actor;
            actor->policy.distance = kakasi->maxSpawnDistance.x;
            actor->policy.ydist = kakasi->maxSpawnDistance.y;
            ActorAccessibility_PlaySoundForActor(actor, 0, NA_SE_EV_KAKASHI_SWING, false);
        }
    });
    policy.distance = 2000;
    policy.n = 1;
    policy.aimAssist.isProvider = true;
    ActorAccessibility_AddSupportedActor(ACTOR_EN_KAKASI2, policy);
    ActorAccessibility_InitPolicy(&policy, "Chest", [](AccessibleActor* actor) {
        Player* player = GET_PLAYER(actor->play);
        EnBox* chest = (EnBox*)actor->actor;
        if (chest->actionFunc != EnBox_WaitOpen)
            return;
        s32 treasureFlag = actor->actor->params & 0x1F;
        s8 size;
        if (chest->type <= 8 && chest->type >= 5) {
            size = 15; // small
        } else {
            size = 30; // large
        }
        if (!(treasureFlag >= 20 && treasureFlag < 32)) {
            ActorAccessibility_PlaySoundForActor(actor, 0, NA_SE_EV_TBOX_UNLOCK, false);
        }
        // Only chests that are "waiting to be opened" should play a sound. Chests which have not yet appeared (because
        // some enemy has not been killed, switch has not been hit, etc) will not be in this action mode.
        f32 leftAngle = actor->actor->world.rot.y - 16384;
        f32 velocityXRight = Math_SinS(leftAngle);
        f32 velocityZRight = Math_CosS(leftAngle);

        f32 frontAngle = actor->actor->world.rot.y;
        f32 velocityXFront = Math_SinS(frontAngle);
        f32 velocityZFront = Math_CosS(frontAngle);

        f32 xdist = (player->actor.world.pos.x - actor->actor->world.pos.x) * velocityXFront +
                    (player->actor.world.pos.z - actor->actor->world.pos.z) * velocityZFront;
        f32 zdist = fabs((player->actor.world.pos.x - actor->actor->world.pos.x) * velocityXRight +
                         (player->actor.world.pos.z - actor->actor->world.pos.z) * velocityZRight);

        if ((xdist - size / 2) < 0) {
            ActorAccessibility_SetSoundPitch(actor, 0, 0.5);
        } else if ((xdist + size / 2) > 0 && zdist < size / 2 && xdist < 150.0) {
            ActorAccessibility_PlaySoundForActor(actor, 1, NA_SE_EV_DIAMOND_SWITCH, false);
        }
    });
    policy.pitch = 1.1;
    policy.distance = 1000;
    ActorAccessibility_AddSupportedActor(ACTOR_EN_BOX, policy);
    ActorAccessibility_InitPolicy(&policy, "Sign", NA_SE_IT_REFLECTION_WOOD);
    policy.n = 40;
    policy.pitch = 1.6;
    policy.distance = 800;
    ActorAccessibility_AddSupportedActor(ACTOR_EN_KANBAN, policy);

    // ACTOR_EN_A_OBJ has exactly the same configuration.
    ActorAccessibility_AddSupportedActor(ACTOR_EN_A_OBJ, policy);
    ActorAccessibility_InitPolicy(&policy, "Large Crate", NA_SE_EV_WOODBOX_BREAK);
    ActorAccessibility_AddSupportedActor(ACTOR_OBJ_KIBAKO, policy);
    ActorAccessibility_AddSupportedActor(ACTOR_OBJ_KIBAKO2, policy);
    ActorAccessibility_InitPolicy(&policy, "deku stick drops", accessible_sticks);
    ActorAccessibility_AddSupportedActor(ACTOR_EN_DEKUBABA, policy);
    ActorAccessibility_AddSupportedActor(ACTOR_EN_KAREBABA, policy);
    ActorAccessibility_InitPolicy(&policy, "Owl", NA_SE_EN_OWL_FLUTTER);
    ActorAccessibility_AddSupportedActor(ACTOR_EN_OWL, policy);

    ActorAccessibility_InitPolicy(&policy, "Ruto", NA_SE_VO_RT_LAUGH_0);
    policy.n = 40;
    policy.pitch = 1.1;
    ActorAccessibility_AddSupportedActor(ACTOR_EN_RU1, policy);

    ActorAccessibility_InitPolicy(&policy, "Bean patch", NA_SE_EN_MUSI_SINK);
    policy.n = 60;
    policy.distance = 2400;
    policy.pitch = 1.3;
    ActorAccessibility_AddSupportedActor(ACTOR_OBJ_BEAN, policy);
    ActorAccessibility_InitPolicy(&policy, "Graveyard Digging Spot", NA_SE_IT_WOODSTICK_BROKEN);
    ActorAccessibility_AddSupportedActor(ACTOR_EN_IT, policy);
    ActorAccessibility_InitPolicy(&policy, "Collectible", NA_SE_EN_NUTS_DAMAGE);
    policy.n = 40;
    policy.pitch = 1.4;
    ActorAccessibility_AddSupportedActor(ACTOR_EN_ITEM00, policy);

    ActorAccessibility_InitPolicy(&policy, "big poe spawn", NA_SE_EN_PO_BIG_GET);
    policy.distance = 1500;
    policy.n = 60;
    ActorAccessibility_AddSupportedActor(ACTOR_EN_PO_FIELD, policy);

    // TODO better gerudo guard logic
    ActorAccessibility_InitPolicy(&policy, "Gerudo Guard", NA_SE_VO_NB_LAUGH);
    policy.n = Npc_Frames;
    policy.pitch = 1.1;
    ActorAccessibility_AddSupportedActor(ACTOR_EN_GE1, policy);
    ActorAccessibility_InitPolicy(&policy, "Boulder", NA_SE_EV_ROCK_BROKEN);
    ActorAccessibility_AddSupportedActor(ACTOR_OBJ_BOMBIWA, policy);
    ActorAccessibility_InitPolicy(&policy, "Bronze Boulder", NA_SE_IT_HAMMER_HIT);
    ActorAccessibility_AddSupportedActor(ACTOR_OBJ_HAMISHI, policy);
    ActorAccessibility_InitPolicy(&policy, "Time Block", NA_SE_EV_TIMETRIP_LIGHT);
    policy.distance = 800;
    ActorAccessibility_AddSupportedActor(ACTOR_OBJ_TIMEBLOCK, policy);
    ActorAccessibility_InitPolicy(&policy, "Grotto Door", accessible_grotto);
    policy.n = 30;
    policy.pitch = 1.0;
    ActorAccessibility_AddSupportedActor(ACTOR_DOOR_ANA, policy);
    ActorAccessibility_InitPolicy(&policy, "Web", NA_SE_EV_WEB_BROKEN);
    policy.n = 40;
    policy.ydist = 2000;
    policy.distance = 2000;
    policy.pitch = 1.2;
    ActorAccessibility_AddSupportedActor(ACTOR_BG_YDAN_SP, policy);

    ActorAccessibility_InitPolicy(&policy, "Shutter Door", [](AccessibleActor* actor) {
        DoorShutter* doorShutter = (DoorShutter*)actor->actor;
        if (doorShutter->doorType == SHUTTER_KEY_LOCKED && !Flags_GetSwitch(actor->play, actor->actor->params & 0x3F)) {
            ActorAccessibility_PlaySoundForActor(actor, 0, NA_SE_EV_CHAIN_KEY_UNLOCK_B, false);
        } else {
            ActorAccessibility_PlaySoundForActor(actor, 0, NA_SE_OC_DOOR_OPEN, false);
        }
    });
    policy.n = 30;
    policy.distance = 1000;
    policy.pitch = 1.1;
    ActorAccessibility_AddSupportedActor(ACTOR_DOOR_SHUTTER, policy);
    ActorAccessibility_InitPolicy(&policy, "Ice Shutter Door", NA_SE_OC_DOOR_OPEN);
    ActorAccessibility_AddSupportedActor(ACTOR_BG_SPOT18_SHUTTER, policy);
    ActorAccessibility_InitPolicy(&policy, "Switch", accessible_switch);
    policy.distance = 2000;
    policy.n = 1;
    policy.ydist = 200;
    policy.pitch = 1.1;
    ActorAccessibility_AddSupportedActor(ACTOR_OBJ_SWITCH, policy);
    ActorAccessibility_InitPolicy(&policy, "Jabu Switch", [](AccessibleActor* actor) {
        int type = actor->actor->params & 0xFF;
        if (type == YELLOW_TALL_1 || type == YELLOW_TALL_2) {
            actor->policy.aimAssist.isProvider = true;
        }
        if ((actor->frameCount & 31) == 0) {
            ActorAccessibility_PlaySoundForActor(actor, 0, NA_SE_EV_DIAMOND_SWITCH, false);
        }
    });
    policy.n = 1;
    policy.volume = 0.6;
    policy.distance = 1000;
    policy.ydist = 300;
    ActorAccessibility_AddSupportedActor(ACTOR_BG_BDAN_SWITCH, policy);
    ActorAccessibility_InitPolicy(&policy, "Jabu Object", [](AccessibleActor* actor) {
        if ((actor->actor->params & 0xFF) == 2 && actor->xzDistToPlayer > 50) {
            // Jabu Elevator
            ActorAccessibility_PlaySoundForActor(actor, 0, NA_SE_PL_LAND_LADDER, false);
        }
    });
    policy.n = 1;
    policy.ydist = 50;
    ActorAccessibility_AddSupportedActor(ACTOR_BG_BDAN_OBJECTS, policy);
    ActorAccessibility_InitPolicy(&policy, "Ocarina Spots", NA_SE_EV_DIAMOND_SWITCH);
    policy.n = 30;
    policy.distance = 800;
    policy.pitch = 1.1;
    policy.ydist = 500;
    ActorAccessibility_AddSupportedActor(ACTOR_EN_OKARINA_TAG, policy);
    ActorAccessibility_InitPolicy(&policy, "Pushable Block", NA_SE_EV_TRAP_BOUND);
    policy.n = 30;
    policy.distance = 800;
    policy.pitch = 1.1;
    ActorAccessibility_AddSupportedActor(ACTOR_OBJ_OSHIHIKI, policy);
    ActorAccessibility_AddSupportedActor(ACTOR_BG_SPOT15_RRBOX, policy);
    ActorAccessibility_InitPolicy(&policy, "Torch", accessible_torches);
    policy.n = 1;
    policy.pitch = 1.1;
    policy.distance = 800;
    ActorAccessibility_AddSupportedActor(ACTOR_OBJ_SYOKUDAI, policy);
    ActorAccessibility_InitPolicy(&policy, "Deku Tree Moving Platform", [](AccessibleActor* actor) {
        if ((actor->actor->params) == 0) {
            actor->policy.ydist = 1000;
            actor->policy.distance = 1000;
            ActorAccessibility_PlaySoundForActor(actor, 0, NA_SE_EN_OCTAROCK_ROCK, false);
        } else if ((actor->actor->params) == 1) {
            actor->policy.ydist = 1000;
            ActorAccessibility_PlaySoundForActor(actor, 0, NA_SE_PL_DAMAGE, false);
        }
    });
    policy.distance = 1000;
    ActorAccessibility_AddSupportedActor(ACTOR_BG_YDAN_HASI, policy);
    ActorAccessibility_InitPolicy(&policy, "Poe Object", [](AccessibleActor* actor) {
        BgPoEvent* po = (BgPoEvent*)actor->actor;
        if (po->type == 0) {
            actor->policy.distance = 400;
            if ((actor->frameCount & 31) == 0) {
                ActorAccessibility_SetSoundPitch(actor, 0, 0.5f + 1.0f * po->index);
                ActorAccessibility_PlaySoundForActor(actor, 0, NA_SE_EN_PO_APPEAR, false);
            }
        } else if (po->type == 1) {
            actor->policy.distance = 300;
            if ((actor->frameCount & 31) == 0) {
                ActorAccessibility_PlaySoundForActor(actor, 0, NA_SE_EV_TRAP_BOUND, false);
            }
        } else if (po->index == sBgPoEventPuzzleState && (actor->frameCount & 63) == 0) {
            ActorAccessibility_PlaySoundForActor(actor, 0, NA_SE_EN_PO_CRY, false);
        }
    });
    policy.aimAssist.isProvider = true;
    policy.aimAssist.tolerance = 50.0f;
    policy.n = 1;
    policy.ydist = 1000;
    policy.distance = 1000;
    ActorAccessibility_AddSupportedActor(ACTOR_BG_PO_EVENT, policy);
    ActorAccessibility_InitPolicy(&policy, "Poe Sister", [](AccessibleActor* actor) {
        if (actor->actor->category == ACTORCAT_PROP) {
            actor->policy.aimAssist.isProvider = false;
        }
    });
    policy.aimAssist.isProvider = true;
    policy.aimAssist.tolerance = 20.0f;
    policy.n = 1;
    ActorAccessibility_AddSupportedActor(ACTOR_EN_PO_SISTERS, policy);
    ActorAccessibility_InitPolicy(&policy, "Lake Hylia Object", nullptr);
    policy.aimAssist.isProvider = true;
    policy.n = 1;
    policy.ydist = 600;
    policy.distance = 600;
    ActorAccessibility_AddSupportedActor(ACTOR_BG_SPOT06_OBJECTS, policy);
    ActorAccessibility_InitPolicy(&policy, "Pot", NA_SE_EV_POT_BROKEN);
    ActorAccessibility_AddSupportedActor(ACTOR_OBJ_TSUBO, policy);
    ActorAccessibility_InitPolicy(&policy, "Platform collapsible", NA_SE_EV_BLOCK_SHAKE);
    ActorAccessibility_AddSupportedActor(ACTOR_OBJ_LIFT, policy);
    ActorAccessibility_InitPolicy(&policy, "Ladder in Slingshot Room", [](AccessibleActor* actor) {
        if (actor->actor->params == 1) {
            ActorAccessibility_PlaySoundForActor(actor, 0, NA_SE_PL_LAND_LADDER, false);
        }
    });
    ActorAccessibility_AddSupportedActor(ACTOR_BG_YDAN_MARUTA, policy);
    ActorAccessibility_InitPolicy(&policy, "bombable wall", NA_SE_EN_OCTAROCK_ROCK);
    ActorAccessibility_AddSupportedActor(ACTOR_BG_BREAKWALL, policy);
    ActorAccessibility_AddSupportedActor(ACTOR_BG_BOMBWALL, policy);
    ActorAccessibility_InitPolicy(&policy, "231 dekus", [](AccessibleActor* actor) {
        if (actor->actor->params == 1) {
            ActorAccessibility_PlaySoundForActor(actor, 0, NA_SE_EN_NUTS_FAINT, false);
            ActorAccessibility_SetSoundPitch(actor, 0, 1.0);
        } else if (actor->actor->params == 2) {
            ActorAccessibility_PlaySoundForActor(actor, 0, NA_SE_EN_NUTS_FAINT, false);
            ActorAccessibility_SetSoundPitch(actor, 0, 0.5);
        } else if (actor->actor->params == 3) {
            ActorAccessibility_PlaySoundForActor(actor, 0, NA_SE_EN_NUTS_FAINT, false);
            ActorAccessibility_SetSoundPitch(actor, 0, 1.5);
        }
    });
    policy.distance = 2000;
    policy.n = 50;
    ActorAccessibility_AddSupportedActor(ACTOR_EN_HINTNUTS, policy);
    ActorAccessibility_InitPolicy(&policy, "Flame Circle", NA_SE_EV_FIRE_PILLAR);
    ActorAccessibility_AddSupportedActor(ACTOR_BG_HIDAN_CURTAIN, policy);

    ActorAccessibility_InitPolicy(&policy, "Blue Fire", [](AccessibleActor* actor) {
        if (actor->actor->params == -1) {
            ActorAccessibility_PlaySoundForActor(actor, 0, NA_SE_IT_FLAME, false);
        }
    });
    policy.n = 60;
    ActorAccessibility_AddSupportedActor(ACTOR_EN_ICE_HONO, policy);
    ActorAccessibility_InitPolicy(&policy, "Ice Barred", NA_SE_EV_CHAIN_KEY_UNLOCK);
    ActorAccessibility_AddSupportedActor(ACTOR_BG_ICE_SHUTTER, policy);
    ActorAccessibility_InitPolicy(&policy, "Ice Block", NA_SE_PL_SLIP_ICE_LELEL);
    ActorAccessibility_AddSupportedActor(ACTOR_BG_GND_ICEBLOCK, policy);
    ActorAccessibility_AddSupportedActor(ACTOR_BG_ICE_OBJECTS, policy);
    ActorAccessibility_InitPolicy(&policy, "Iceberg", NA_SE_EV_ICE_FREEZE);
    policy.distance = 1500;
    ActorAccessibility_AddSupportedActor(ACTOR_BG_SPOT08_ICEBLOCK, policy);
    policy.englishName = "Red Ice";
    policy.distance = 300;
    ActorAccessibility_AddSupportedActor(ACTOR_BG_ICE_SHELTER, policy);

    ActorAccessibility_InitPolicy(&policy, "uninteractable rocks in kokiri forest", [](AccessibleActor* actor) {
        if (actor->actor->params == 1) {
            ActorAccessibility_PlaySoundForActor(actor, 0, NA_SE_EN_OCTAROCK_ROCK, false);
        } else if (actor->actor->params == 0) {
            ActorAccessibility_PlaySoundForActor(actor, 0, NA_SE_EV_DIG_UP, false);
        }
    });
    ActorAccessibility_AddSupportedActor(ACTOR_OBJ_HANA, policy);
    ActorAccessibility_InitPolicy(&policy, "gold skulltula token", NA_SE_EN_NUTS_DAMAGE);
    ActorAccessibility_AddSupportedActor(ACTOR_EN_SI, policy);
    ActorAccessibility_InitPolicy(&policy, "Gold and Wall skulltulas", nullptr);
    policy.aimAssist.isProvider = true;
    policy.n = 1;
    policy.ydist = 500;
    policy.distance = 750;
    ActorAccessibility_AddSupportedActor(ACTOR_EN_SW, policy);
    ActorAccessibility_InitPolicy(&policy, "Big Skulltula", [](AccessibleActor* actor) {
        s16 angleTowardsLink = ABS((s16)(actor->actor->yawTowardsPlayer - actor->actor->shape.rot.y));
        if (angleTowardsLink >= 0x3FFC) {
            ActorAccessibility_PlaySoundForActor(actor, 0, NA_SE_VO_ST_DAMAGE, false);
        } else if ((actor->frameCount & 63) == 0) {
            ActorAccessibility_PlaySoundForActor(actor, 0, NA_SE_EN_STALTU_LAUGH, false);
        }
    });
    policy.ydist = 100;
    ActorAccessibility_AddSupportedActor(ACTOR_EN_ST, policy);
    ActorAccessibility_InitPolicy(&policy, "goma larva egg", accessible_larva);
    policy.distance = 1000;
    policy.ydist = 1000;
    ActorAccessibility_AddSupportedActor(ACTOR_EN_GOMA, policy);
    ActorAccessibility_InitPolicy(&policy, "jabu jabu", NA_SE_EV_JABJAB_HICCUP);
    policy.distance = 10000;
    ActorAccessibility_AddSupportedActor(ACTOR_EN_JJ, policy);
    ActorAccessibility_InitPolicy(&policy, "small jellyfish", NA_SE_EN_BIRI_FLY);
    ActorAccessibility_AddSupportedActor(ACTOR_EN_BILI, policy);
    ActorAccessibility_InitPolicy(&policy, "stinger", [](AccessibleActor* actor) {
        auto actionFunc = ((EnEiyer*)actor->actor)->actionFunc;
        if (actionFunc == EnEiyer_Die || actionFunc == EnEiyer_Dead) {
            ActorAccessibility_StopAllSoundsForActor(actor);
        } else if (GET_PLAYER(actor->play)->actor.world.pos.y > actor->actor->world.pos.y - 8) {
            ActorAccessibility_PlaySoundForActor(actor, 0, NA_SE_IT_FISHING_REEL_SLOW, false);
        } else {
            ActorAccessibility_PlaySoundForActor(actor, 0, NA_SE_IT_FISHING_REEL_HIGH, false);
        }
    });
    policy.n = 1;
    policy.distance = 1000;
    policy.ydist = 200;
    ActorAccessibility_AddSupportedActor(ACTOR_EN_EIYER, policy);
    ActorAccessibility_InitPolicy(&policy, "bubble", NA_SE_EN_DAIOCTA_SPLASH);
    policy.ydist = 200;
    ActorAccessibility_AddSupportedActor(ACTOR_EN_BUBBLE, policy);
    ActorAccessibility_InitPolicy(&policy, "tentacle obstacle", NA_SE_EN_BALINADE_THUNDER);
    policy.distance = 100;
    ActorAccessibility_AddSupportedActor(ACTOR_EN_BX, policy);
    ActorAccessibility_InitPolicy(&policy, "tentacle", [](AccessibleActor* actor) {
        if (actor->actor->params < EN_BA_DEAD_BLOB) {
            actor->policy.volume = 2.5 - (actor->actor->world.pos.y - actor->actor->home.pos.y) / 200.0;
            ActorAccessibility_PlaySoundForActor(actor, 0, NA_SE_EN_OWL_FLUTTER, false);
        }
    });
    policy.distance = 1500;
    policy.ydist = 1000;
    policy.n = 5;
    ActorAccessibility_AddSupportedActor(ACTOR_EN_BA, policy);
    ActorAccessibility_InitPolicy(&policy, "redead", NA_SE_EN_REDEAD_CRY);
    ActorAccessibility_AddSupportedActor(ACTOR_EN_RD, policy);
    ActorAccessibility_InitPolicy(&policy, "freezard", [](AccessibleActor* actor) {
        EnFz* fz = (EnFz*)actor->actor;
        if (fz->state != 0) {
            ActorAccessibility_PlaySoundForActor(actor, 0, NA_SE_EN_FREEZAD_DEAD, false);
        }
    });
    policy.n = 20;
    policy.aimAssist.isProvider = true;
    ActorAccessibility_AddSupportedActor(ACTOR_EN_FZ, policy);
    ActorAccessibility_InitPolicy(&policy, "Beamos", NA_SE_EN_BIMOS_AIM);
    ActorAccessibility_AddSupportedActor(ACTOR_EN_VM, policy);
    ActorAccessibility_InitPolicy(&policy, "heart canister", NA_SE_EN_NUTS_DAMAGE);
    ActorAccessibility_AddSupportedActor(ACTOR_ITEM_B_HEART, policy);
    ActorAccessibility_InitPolicy(&policy, "Ocarina of Time", [](AccessibleActor* actor) {
        if (actor->play->sceneNum == SCENE_ZORAS_DOMAIN || actor->play->sceneNum == SCENE_HYRULE_FIELD ||
            actor->play->sceneNum == SCENE_LAKE_HYLIA) {
            int freq = actor->xzDistToPlayer < 10    ? 0
                       : actor->xzDistToPlayer < 20  ? 1
                       : actor->xzDistToPlayer < 40  ? 3
                       : actor->xzDistToPlayer < 70  ? 7
                       : actor->xzDistToPlayer < 110 ? 15
                       : actor->xzDistToPlayer < 200 ? 31
                                                     : 63;
            if ((actor->frameCount & freq) == 0) {
                ActorAccessibility_PlaySoundForActor(actor, 0, NA_SE_EV_BOMB_DROP_WATER, false);
            }
        }
    });
    policy.n = 1;
    policy.distance = 1500;
    policy.ydist = 500;
    ActorAccessibility_AddSupportedActor(ACTOR_EN_EX_RUPPY, policy);
    ActorAccessibility_AddSupportedActor(ACTOR_ITEM_ETCETERA, policy);
    ActorAccessibility_AddSupportedActor(ACTOR_ITEM_OCARINA, policy);
    ActorAccessibility_InitPolicy(&policy, "Goma", accessible_goma);
    policy.distance = 5000;
    policy.ydist = 2000;
    ActorAccessibility_AddSupportedActor(ACTOR_BOSS_GOMA, policy);
    ActorAccessibility_InitPolicy(&policy, "bombflowers", NA_SE_EV_BOMB_BOUND);
    ActorAccessibility_AddSupportedActor(ACTOR_EN_BOMBF, policy);
    ActorAccessibility_InitPolicy(&policy, "Amos Statue", NA_SE_EN_AMOS_WAVE);
    policy.n = 30;
    ActorAccessibility_AddSupportedActor(ACTOR_EN_AM, policy);
    ActorAccessibility_InitPolicy(&policy, "Big Rupee", [](AccessibleActor* actor) {
        if ((actor->frameCount & 31) == 0) {
            EnGSwitch* gswitch = (EnGSwitch*)actor->actor;
            if (gswitch->actionFunc == EnGSwitch_SilverRupeeIdle) {
                ActorAccessibility_PlaySoundForActor(actor, 0, NA_SE_EV_FIVE_COUNT_LUPY, false);
            }
        }
    });
    policy.aimAssist.isProvider = true;
    policy.distance = 1000;
    policy.n = 1;
    ActorAccessibility_AddSupportedActor(ACTOR_EN_G_SWITCH, policy);
    ActorAccessibility_InitPolicy(&policy, "crawlspace", NA_SE_EN_MUSI_SINK);
    policy.volume = 1.5;
    policy.distance = 2000;
    ActorAccessibility_AddSupportedActor(VA_CRAWLSPACE, policy);
    ActorAccessibility_InitPolicy(&policy, "Ladder/climable", [](AccessibleActor* actor) {
        Player* player = GET_PLAYER(actor->play);
        f32 waterLoc = player->actor.yDistToWater + player->actor.world.pos.y;
        if (actor->pos.y < waterLoc) {
            actor->pos.y = waterLoc;
        }
        if (actor->yDistToPlayer < 80)
            ActorAccessibility_PlaySoundForActor(actor, 0, NA_SE_PL_LAND_LADDER, false);
    });
    policy.pitch = 1.3;
    ActorAccessibility_AddSupportedActor(VA_CLIMB, policy);
    ActorAccessibility_InitPolicy(&policy, "Door", NA_SE_OC_DOOR_OPEN);
    policy.n = 30;
    policy.pitch = 1.1;
    policy.distance = 1000;
    ActorAccessibility_AddSupportedActor(VA_DOOR, policy);
    ActorAccessibility_AddSupportedActor(ACTOR_EN_DOOR, policy);
    ActorAccessibility_InitPolicy(&policy, "Area Change", accessible_area_change);
    policy.n = 60;
    policy.distance = 100000;
    ActorAccessibility_AddSupportedActor(VA_AREA_CHANGE, policy);
    ActorAccessibility_InitPolicy(&policy, "marker", NA_SE_EV_DIAMOND_SWITCH);
    policy.distance = 1000;
    policy.pitch = 1.7;
    ActorAccessibility_AddSupportedActor(VA_MARKER, policy);
    ActorAccessibility_InitPolicy(&policy, "Stick Burnout Warning", accessible_stick_warning);
    policy.n = 1;
    policy.runsAlways = true;
    ActorAccessibility_AddSupportedActor(VA_STICK_WARNING, policy);
    ActorAccessibility_InitPolicy(&policy, "System general helper", accessible_va_general_helper);
    policy.n = 1;
    policy.cleanupUserData = accessible_general_helper_cleanup;
    policy.initUserData = accessible_general_helper_init;
    policy.runsAlways = true;
    ActorAccessibility_AddSupportedActor(VA_GENERAL_HELPER, policy);
    ActorAccessibility_InitPolicy(&policy, "Audio Compass", accessible_audio_compass);
    policy.n = 1;
    policy.cleanupUserData = accessible_audio_compass_cleanup;
    policy.initUserData = accessible_audio_compass_init;
    policy.runsAlways = true;
    policy.sound = NA_SE_EV_SHIP_BELL; // Setting this here so it's easy to change if we ever decide to change it.
    policy.pitch = 0.5;

    ActorAccessibility_AddSupportedActor(VA_AUDIO_COMPASS, policy);

    // Now query a list of virtual actors for a given location (scene and room number).
    VirtualActorList* list = (VirtualActorList*)ActorAccessibility_GetVirtualActorList(EVERYWHERE, 0);
    AccessibleActor* temp;

    // Now place the actor.
    ActorAccessibility_AddVirtualActor(list, VA_GENERAL_HELPER, { 0, 0, 0 });
    ActorAccessibility_AddVirtualActor(list, VA_AUDIO_COMPASS, { 0, 0, 0 });
    ActorAccessibility_AddVirtualActor(list, VA_STICK_WARNING, { 0, 0, 0 });

    list = ActorAccessibility_GetVirtualActorList(SCENE_KOKIRI_FOREST, 0);
    ActorAccessibility_AddVirtualActor(list, VA_CRAWLSPACE, { -784, 120, 1046 });
    ActorAccessibility_AddVirtualActor(list, VA_MARKER, { 2146, 1, -142.8 });

    // Kokiri Forest Room with boulder and kokiri sword
    list = ActorAccessibility_GetVirtualActorList(SCENE_KOKIRI_FOREST, 2);
    ActorAccessibility_AddVirtualActor(list, VA_CRAWLSPACE, { -788, 120, 1392 });

    list = ActorAccessibility_GetVirtualActorList(SCENE_LOST_WOODS, 1);
    temp = ActorAccessibility_AddVirtualActor(list, VA_MARKER, { 1348, 25, -25 });
    temp->policy.aimAssist.isProvider = true;
    temp->policy.distance = 700;
    temp->policy.n = 1;

    list = ActorAccessibility_GetVirtualActorList(SCENE_DEKU_TREE, 2); // deku tree slingshot room

    list = ActorAccessibility_GetVirtualActorList(SCENE_DEKU_TREE, 10); // deku tree compass room

    list = ActorAccessibility_GetVirtualActorList(SCENE_DEKU_TREE, 7); // bombable wall room
    ActorAccessibility_AddVirtualActor(list, VA_CRAWLSPACE, { -1209, -820.0, 3.5 });

    list = ActorAccessibility_GetVirtualActorList(SCENE_DEKU_TREE, 3); // basement 1 lobby
    ActorAccessibility_AddVirtualActor(list, VA_CRAWLSPACE, { -901, -820, 0.5 });
    ActorAccessibility_AddVirtualActor(list, VA_MARKER, { -181.76, -905, -28.3 });

    list = ActorAccessibility_GetVirtualActorList(SCENE_DODONGOS_CAVERN, 0);
    temp = ActorAccessibility_AddVirtualActor(list, VA_MARKER, { -80, 310, -1540 });
    temp->policy.distance = 150;
    temp->policy.ydist = 100;
    temp = ActorAccessibility_AddVirtualActor(list, VA_MARKER, { 80, 310, -1540 });
    temp->policy.distance = 150;
    temp->policy.ydist = 100;
    temp = ActorAccessibility_AddVirtualActor(list, VA_MARKER, { -80, 510, -1540 });
    temp->policy.distance = 150;
    temp->policy.ydist = 100;
    temp = ActorAccessibility_AddVirtualActor(list, VA_MARKER, { 80, 510, -1540 });
    temp->policy.distance = 150;
    temp->policy.ydist = 100;

    list = ActorAccessibility_GetVirtualActorList(SCENE_DODONGOS_CAVERN, 2); // dodongo bombflower stairs room
    ActorAccessibility_AddVirtualActor(list, VA_MARKER, { -1958, 20, -1297 });

    list = ActorAccessibility_GetVirtualActorList(SCENE_JABU_JABU, 2);
    temp = ActorAccessibility_AddVirtualActor(list, VA_MARKER, { -260, -400, -3377 }); // green tentacle hole
    temp->policy.distance = 200;
    temp->policy.sound = NA_SE_EN_DAIOCTA_DEAD;
    temp = ActorAccessibility_AddVirtualActor(list, VA_MARKER, { 230, -400, -3211 }); // ruto hole
    temp->policy.distance = 200;
    temp->policy.sound = NA_SE_VO_RT_FALL;

    list = ActorAccessibility_GetVirtualActorList(SCENE_CASTLE_COURTYARD_GUARDS_DAY, 0);
    ActorAccessibility_AddVirtualActor(list, VA_MARKER, { 1734.0, 0.0, 140.514 });
    temp = ActorAccessibility_AddVirtualActor(list, VA_MARKER, { 1734.0, 0.0, 140.514 });
    temp->policy.pitch = 0.3;
    temp->policy.volume = 0.5;
    ActorAccessibility_AddVirtualActor(list, VA_MARKER, { 1040.0, 0.0, 140.514 });
    temp = ActorAccessibility_AddVirtualActor(list, VA_MARKER, { 1734.0, 0.0, 140.514 });
    temp->policy.pitch = 0.6;
    temp->policy.volume = 0.5;
    ActorAccessibility_AddVirtualActor(list, VA_MARKER, { 230.0, 0.0, 188.514 });
    temp = ActorAccessibility_AddVirtualActor(list, VA_MARKER, { 1734.0, 0.0, 140.514 });
    temp->policy.pitch = 0.9;
    temp->policy.volume = 0.5;
    ActorAccessibility_AddVirtualActor(list, VA_MARKER, { -426.0, 0.0, 130.514 });
    temp = ActorAccessibility_AddVirtualActor(list, VA_MARKER, { 1734.0, 0.0, 140.514 });
    temp->policy.pitch = 1.2;
    temp->policy.volume = 0.5;
    ActorAccessibility_AddVirtualActor(list, VA_MARKER, { -1206.0, 0.0, 133.514 });
    temp = ActorAccessibility_AddVirtualActor(list, VA_MARKER, { 1734.0, 0.0, 140.514 });
    temp->policy.pitch = 1.5;
    temp->policy.volume = 0.5;
    ActorAccessibility_AddVirtualActor(list, VA_MARKER, { -1571.0, 0.0, -834.514 });
    temp = ActorAccessibility_AddVirtualActor(list, VA_MARKER, { 1734.0, 0.0, 140.514 });
    temp->policy.pitch = 1.8;
    temp->policy.volume = 0.5;

    list = ActorAccessibility_GetVirtualActorList(SCENE_TEMPLE_OF_TIME, 0);
    temp = ActorAccessibility_AddVirtualActor(list, VA_MARKER, { 0, 0, 0 });
    temp->policy.englishName = "Master Sword Pedestal";
    temp->policy.distance = 1500;
    temp->policy.sound = NA_SE_PL_SWORD_CHARGE;

    list = ActorAccessibility_GetVirtualActorList(SCENE_WINDMILL_AND_DAMPES_GRAVE, 0);
    ActorAccessibility_AddVirtualActor(list, VA_MARKER, { -50, -530, -2300 });
    ActorAccessibility_AddVirtualActor(list, VA_MARKER, { 25, -530, -2875 });
    ActorAccessibility_AddVirtualActor(list, VA_MARKER, { 300, -530, -3020 });

    list = ActorAccessibility_GetVirtualActorList(SCENE_WINDMILL_AND_DAMPES_GRAVE, 1);
    ActorAccessibility_AddVirtualActor(list, VA_MARKER, { 370, -500, -3430 });
    ActorAccessibility_AddVirtualActor(list, VA_MARKER, { 410, -530, -3770 });
    ActorAccessibility_AddVirtualActor(list, VA_MARKER, { 675, -570, -3930 });
    ActorAccessibility_AddVirtualActor(list, VA_MARKER, { 675, -610, -4300 });
    ActorAccessibility_AddVirtualActor(list, VA_MARKER, { 560, -600, -4500 });
    ActorAccessibility_AddVirtualActor(list, VA_MARKER, { 470, -570, -4775 });
    ActorAccessibility_AddVirtualActor(list, VA_MARKER, { 300, -570, -4910 });
    ActorAccessibility_AddVirtualActor(list, VA_MARKER, { 230, -570, -5300 });

    list = ActorAccessibility_GetVirtualActorList(SCENE_WINDMILL_AND_DAMPES_GRAVE, 2);
    ActorAccessibility_AddVirtualActor(list, VA_MARKER, { 300, -570, -5400 });
    ActorAccessibility_AddVirtualActor(list, VA_MARKER, { 500, -570, -5400 });
    ActorAccessibility_AddVirtualActor(list, VA_MARKER, { 650, -570, -5275 });
    ActorAccessibility_AddVirtualActor(list, VA_MARKER, { 1200, -730, -5125 });
    ActorAccessibility_AddVirtualActor(list, VA_MARKER, { 1345, -730, -4930 });
    ActorAccessibility_AddVirtualActor(list, VA_MARKER, { 1560, -730, -4765 });
    ActorAccessibility_AddVirtualActor(list, VA_MARKER, { 1730, -730, -4550 });
    ActorAccessibility_AddVirtualActor(list, VA_MARKER, { 1940, -730, -4430 });

    list = ActorAccessibility_GetVirtualActorList(SCENE_WINDMILL_AND_DAMPES_GRAVE, 3);
    ActorAccessibility_AddVirtualActor(list, VA_MARKER, { 1990, -730, -4185 });
    ActorAccessibility_AddVirtualActor(list, VA_MARKER, { 1800, -730, -3950 });
    ActorAccessibility_AddVirtualActor(list, VA_MARKER, { 1720, -730, -3850 });
    ActorAccessibility_AddVirtualActor(list, VA_MARKER, { 1690, -730, -3145 });
    ActorAccessibility_AddVirtualActor(list, VA_MARKER, { 1655, -668, -3035 });
    ActorAccessibility_AddVirtualActor(list, VA_MARKER, { 1710, -668, -2660 });
    ActorAccessibility_AddVirtualActor(list, VA_MARKER, { 2285, -610, -2650 });
    ActorAccessibility_AddVirtualActor(list, VA_MARKER, { 2625, -610, -2700 });
    ActorAccessibility_AddVirtualActor(list, VA_MARKER, { 3080, -530, -2700 });
    ActorAccessibility_AddVirtualActor(list, VA_MARKER, { 3230, -470, -2515 });
    ActorAccessibility_AddVirtualActor(list, VA_MARKER, { 3170, -420, -2300 });
    ActorAccessibility_AddVirtualActor(list, VA_MARKER, { 2960, -410, -2000 });

    list = ActorAccessibility_GetVirtualActorList(SCENE_FOREST_TEMPLE, 15);
    // falling ceiling safe spots
    temp = ActorAccessibility_AddVirtualActor(list, VA_MARKER, { 2070, -403, -3000 });
    temp->policy.volume = 0.5;
    temp->policy.distance = 1500;
    temp = ActorAccessibility_AddVirtualActor(list, VA_MARKER, { 2150, -403, -2560 });
    temp->policy.volume = 0.5;
    temp->policy.distance = 1500;
    temp = ActorAccessibility_AddVirtualActor(list, VA_MARKER, { 2070, -403, -3000 });
    temp->policy.volume = 0.5;
    temp->policy.distance = 1500;
    temp = ActorAccessibility_AddVirtualActor(list, VA_MARKER, { 1990, -403, -1850 });
    temp->policy.volume = 0.5;
    temp->policy.distance = 1500;

    list = ActorAccessibility_GetVirtualActorList(SCENE_ICE_CAVERN, 9);
    temp = ActorAccessibility_AddVirtualActor(list, VA_MARKER, { 860, 180, -2400 });
    temp->policy.distance = 300;
    temp->policy.ydist = 100;
    temp->policy.sound = NA_SE_EV_BLOCK_SHAKE;

    ActorAccessibility_InitCues();
}
