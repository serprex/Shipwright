#include <soh/OTRGlobals.h>
extern "C" {
extern PlayState* gPlayState;
#include "variables.h"
#include "functions.h"
}

void RegisterShuffleSpeak() {
    bool shouldRegister = IS_RANDO && Rando::Context::GetInstance()->GetOption(RSK_SHUFFLE_SPEAK).Get();

    COND_VB_SHOULD(VB_SPEAK, shouldRegister, {
        if (!Flags_GetRandomizerInf(RAND_INF_CAN_SPEAK)) {
            Actor* talkActor = GET_PLAYER(gPlayState)->talkActor;
            if (talkActor != NULL && talkActor->category == ACTORCAT_NPC) {
                *should = false;
            }
        }
    });
}

static RegisterShipInitFunc initFunc(RegisterShuffleSpeak, { "IS_RANDO" });