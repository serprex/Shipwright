#include "ShuffleRocks.h"
#include "soh_assets.h"
#include "static_data.h"

extern "C" {
#include "variables.h"
#include "overlays/actors/ovl_En_Ishi/z_en_ishi.h"
#include "overlays/actors/ovl_Obj_Bombiwa/z_obj_bombiwa.h"
#include "overlays/actors/ovl_Obj_Hamishi/z_obj_hamishi.h"
#include "objects/gameplay_field_keep/gameplay_field_keep.h"
#include "objects/object_bombiwa/object_bombiwa.h"
extern PlayState* gPlayState;
}

#define RAND_GET_OPTION(option) Rando::Context::GetInstance()->GetOption(option).Get()

extern void EnItem00_DrawRandomizedItem(EnItem00* enItem00, PlayState* play);

extern "C" void EnIshi_RandomizerDraw(Actor* thisx, PlayState* play) {
    auto rockActor = ((EnIshi*)thisx);

    OPEN_DISPS(play->state.gfxCtx);
    Gfx_SetupDL_25Opa(play->state.gfxCtx);
    gDPSetGrayscaleColor(POLY_OPA_DISP++, 175, 255, 0, 255);

    if (rockActor->rockIdentity.randomizerCheck != RC_MAX &&
        Flags_GetRandomizerInf(rockActor->rockIdentity.randomizerInf) == 0) {
        gSPGrayscale(POLY_OPA_DISP++, true);
    }

    if (rockActor->actor.params & 1) {
        Gfx_SetupDL_25Opa(play->state.gfxCtx);
        gSPMatrix(POLY_OPA_DISP++, MATRIX_NEWMTX(play->state.gfxCtx),
                  G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW);
        gDPSetPrimColor(POLY_OPA_DISP++, 0, 0, 255, 255, 255, 255);
        gSPDisplayList(POLY_OPA_DISP++, (Gfx*)gSilverRockDL);
    } else {
        Gfx_DrawDListOpa(play, (Gfx*)gFieldKakeraDL);
    }

    gSPGrayscale(POLY_OPA_DISP++, false);

    CLOSE_DISPS(play->state.gfxCtx);
}

extern "C" void ObjBombiwa_RandomizerDraw(Actor* thisx, PlayState* play) {
    auto rockActor = ((ObjBombiwa*)thisx);

    OPEN_DISPS(play->state.gfxCtx);
    Gfx_SetupDL_25Opa(play->state.gfxCtx);
    gDPSetGrayscaleColor(POLY_OPA_DISP++, 175, 255, 0, 255);

    if (rockActor->rockIdentity.randomizerCheck != RC_MAX &&
        Flags_GetRandomizerInf(rockActor->rockIdentity.randomizerInf) == 0) {
        gSPGrayscale(POLY_OPA_DISP++, true);
    }

    Gfx_DrawDListOpa(play, (Gfx*)object_bombiwa_DL_0009E0);

    gSPGrayscale(POLY_OPA_DISP++, false);

    CLOSE_DISPS(play->state.gfxCtx);
}

extern "C" void ObjHamishi_RandomizerDraw(Actor* thisx, PlayState* play) {
    auto rockActor = ((ObjHamishi*)thisx);

    OPEN_DISPS(play->state.gfxCtx);
    Gfx_SetupDL_25Opa(play->state.gfxCtx);
    gDPSetGrayscaleColor(POLY_OPA_DISP++, 175, 255, 0, 255);

    if (rockActor->rockIdentity.randomizerCheck != RC_MAX &&
        Flags_GetRandomizerInf(rockActor->rockIdentity.randomizerInf) == 0) {
        gSPGrayscale(POLY_OPA_DISP++, true);
    }

    Gfx_SetupDL_25Opa(play->state.gfxCtx);

    gSPMatrix(POLY_OPA_DISP++, MATRIX_NEWMTX(play->state.gfxCtx),
              G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW);
    gDPSetPrimColor(POLY_OPA_DISP++, 0, 0, 255, 170, 130, 255);
    gSPDisplayList(POLY_OPA_DISP++, (Gfx*)gSilverRockDL);

    gSPGrayscale(POLY_OPA_DISP++, false);

    CLOSE_DISPS(play->state.gfxCtx);
}

uint8_t Rock_RandomizerHoldsItem(RockIdentity rockIdentity, PlayState* play) {
    RandomizerCheck rc = rockIdentity.randomizerCheck;
    if (rc == RC_MAX)
        return false;

    uint8_t rockSetting = Rando::Context::GetInstance()->GetOption(RSK_SHUFFLE_ROCKS).Get();

    // Don't pull randomized item if rock isn't randomized or is already checked
    return IS_RANDO && rockSetting &&
        !Flags_GetRandomizerInf(rockIdentity.randomizerInf) &&
        rockIdentity.randomizerCheck != RC_UNKNOWN_CHECK;
}

void Rock_RandomizerSpawnCollectible(Actor* actor, RockIdentity rockIdentity, PlayState* play) {
    EnItem00* item00 = (EnItem00*)Item_DropCollectible2(play, &actor->world.pos, ITEM00_SOH_DUMMY);
    item00->randoInf = rockIdentity.randomizerInf;
    item00->itemEntry = Rando::Context::GetInstance()->GetFinalGIEntry(rockIdentity.randomizerCheck, true, GI_NONE);
    item00->actor.draw = (ActorFunc)EnItem00_DrawRandomizedItem;
    item00->actor.velocity.y = 9.0f;
    item00->actor.speedXZ = 2.0f;
    item00->actor.world.rot.y = Rand_CenteredFloat(65536.0f);
}

void EnIshi_RandomizerInit(void* actorRef) {
    Actor* actor = static_cast<Actor*>(actorRef);

    if (actor->id != ACTOR_EN_ISHI)
        return;

    EnIshi* rockActor = static_cast<EnIshi*>(actorRef);

    rockActor->rockIdentity = OTRGlobals::Instance->gRandomizer->IdentifyRock(
        gPlayState->sceneNum, (s16)actor->world.pos.x, (s16)actor->world.pos.z);
    LUSLOG_INFO("ROCK ishi%d %d\t:\t%d, %d", rockActor->rockIdentity.randomizerCheck, actor->params&1, (s16)actor->world.pos.x, (s16)actor->world.pos.z);
    if (Rock_RandomizerHoldsItem(rockActor->rockIdentity, gPlayState)) {
        rockActor->actor.draw = EnIshi_RandomizerDraw;
    }
}

void ObjBombiwa_RandomizerInit(void* actorRef) {
    Actor* actor = static_cast<Actor*>(actorRef);

    if (actor->id != ACTOR_OBJ_BOMBIWA)
        return;

    ObjBombiwa* rockActor = static_cast<ObjBombiwa*>(actorRef);

    rockActor->rockIdentity = OTRGlobals::Instance->gRandomizer->IdentifyRock(
        gPlayState->sceneNum, (s16)actor->world.pos.x, (s16)actor->world.pos.z);
    LUSLOG_INFO("ROCK bombiwa%d\t:\t%d, %d", rockActor->rockIdentity.randomizerCheck, (s16)actor->world.pos.x, (s16)actor->world.pos.z);
    if (Rock_RandomizerHoldsItem(rockActor->rockIdentity, gPlayState)) {
        rockActor->actor.draw = ObjBombiwa_RandomizerDraw;
    }
}

void ObjHamishi_RandomizerInit(void* actorRef) {
    Actor* actor = static_cast<Actor*>(actorRef);

    if (actor->id != ACTOR_OBJ_HAMISHI)
        return;

    ObjHamishi* rockActor = static_cast<ObjHamishi*>(actorRef);

    rockActor->rockIdentity = OTRGlobals::Instance->gRandomizer->IdentifyRock(
        gPlayState->sceneNum, (s16)actor->world.pos.x, (s16)actor->world.pos.z);
    LUSLOG_INFO("ROCK hamishi%d\t:\t%d, %d", rockActor->rockIdentity.randomizerCheck, (s16)actor->world.pos.x, (s16)actor->world.pos.z);
    if (Rock_RandomizerHoldsItem(rockActor->rockIdentity, gPlayState)) {
        rockActor->actor.draw = ObjHamishi_RandomizerDraw;
    }
}

void RegisterShuffleRock() {
    bool shouldRegister = IS_RANDO && RAND_GET_OPTION(RSK_SHUFFLE_ROCKS);

    COND_ID_HOOK(OnActorInit, ACTOR_EN_ISHI, shouldRegister, EnIshi_RandomizerInit);
    COND_ID_HOOK(OnActorInit, ACTOR_OBJ_BOMBIWA, shouldRegister, ObjBombiwa_RandomizerInit);
    COND_ID_HOOK(OnActorInit, ACTOR_OBJ_HAMISHI, shouldRegister, ObjHamishi_RandomizerInit);

    COND_VB_SHOULD(VB_ROCK_DROP_ITEM, shouldRegister, {
        EnIshi* rockActor = va_arg(args, EnIshi*);
        if (Rock_RandomizerHoldsItem(rockActor->rockIdentity, gPlayState)) {
            Rock_RandomizerSpawnCollectible(&rockActor->actor, rockActor->rockIdentity, gPlayState);
            rockActor->rockIdentity.randomizerCheck = RC_MAX;
            rockActor->rockIdentity.randomizerInf = RAND_INF_MAX;
            *should = false;
        } else {
            *should = true;
        }
    });

    COND_VB_SHOULD(VB_BOULDER_BREAK_FLAG, shouldRegister, {
        ObjBombiwa* rockActor = va_arg(args, ObjBombiwa*);
        if (Rock_RandomizerHoldsItem(rockActor->rockIdentity, gPlayState)) {
            Rock_RandomizerSpawnCollectible(&rockActor->actor, rockActor->rockIdentity, gPlayState);
            rockActor->rockIdentity.randomizerCheck = RC_MAX;
            rockActor->rockIdentity.randomizerInf = RAND_INF_MAX;
            *should = false;
        }
    });

    COND_VB_SHOULD(VB_BRONZE_BOULDER_BREAK_FLAG, shouldRegister, {
        ObjHamishi* rockActor = va_arg(args, ObjHamishi*);
        if (Rock_RandomizerHoldsItem(rockActor->rockIdentity, gPlayState)) {
            Rock_RandomizerSpawnCollectible(&rockActor->actor, rockActor->rockIdentity, gPlayState);
            rockActor->rockIdentity.randomizerCheck = RC_MAX;
            rockActor->rockIdentity.randomizerInf = RAND_INF_MAX;
            *should = false;
        }
    });
}

static RegisterShipInitFunc initFunc(RegisterShuffleRock, { "IS_RANDO" });