#include <soh/OTRGlobals.h>
extern "C" {
extern PlayState* gPlayState;
#include "variables.h"
#include "functions.h"
#include "overlays/actors/ovl_En_Ossan/z_en_ossan.h"
}

void RegisterShuffleSpeak() {
    bool shouldRegister = IS_RANDO && Rando::Context::GetInstance()->GetOption(RSK_SHUFFLE_SPEAK).Get();

    COND_VB_SHOULD(VB_SPEAK, shouldRegister, {
        Actor* talkActor = GET_PLAYER(gPlayState)->talkActor;
        if (talkActor != NULL && talkActor->category == ACTORCAT_NPC) {
            RandomizerInf inf = RAND_INF_MAX;
            switch (talkActor->id) {
                case ACTOR_EN_DNS:
                case ACTOR_EN_HINTNUTS:
                case ACTOR_OBJ_DEKUJR:
                    inf = RAND_INF_CAN_SPEAK_DEKU;
                    break;
                case ACTOR_EN_GE1:
                case ACTOR_EN_GE3:
                case ACTOR_EN_NB:
                    // skip ACTOR_EN_GE2 to always be able to ask to be thrown in jail
                    inf = RAND_INF_CAN_SPEAK_GERUDO;
                    break;
                case ACTOR_EN_GO:
                case ACTOR_EN_GO2:
                    inf = RAND_INF_CAN_SPEAK_GORON;
                    break;
                case ACTOR_DEMO_IM:
                case ACTOR_EN_DS:
                case ACTOR_EN_GB:
                case ACTOR_EN_GIRLA:
                case ACTOR_EN_GUEST:
                case ACTOR_EN_HY:
                case ACTOR_EN_OWL:
                case ACTOR_EN_TK:
                case ACTOR_EN_XC:
                case ACTOR_EN_ZL1:
                case ACTOR_EN_ZL2:
                case ACTOR_EN_ZL3:
                case ACTOR_EN_ZL4:
                    inf = RAND_INF_CAN_SPEAK_HYLIAN;
                    break;
                case ACTOR_EN_KO:
                case ACTOR_EN_MD:
                    inf = RAND_INF_CAN_SPEAK_KOKIRI;
                    break;
                case ACTOR_EN_KZ:
                case ACTOR_EN_RU1:
                case ACTOR_EN_RU2:
                case ACTOR_EN_ZO:
                    inf = RAND_INF_CAN_SPEAK_ZORA;
                    break;
                case ACTOR_EN_OSSAN:
                    switch (talkActor->params) {
                        case OSSAN_TYPE_KOKIRI:
                            inf = RAND_INF_CAN_SPEAK_ZORA;
                            break;
                        case OSSAN_TYPE_KAKARIKO_POTION:
                        case OSSAN_TYPE_BOMBCHUS:
                        case OSSAN_TYPE_MARKET_POTION:
                        case OSSAN_TYPE_BAZAAR:
                        case OSSAN_TYPE_ADULT:
                        case OSSAN_TYPE_TALON:
                        case OSSAN_TYPE_INGO:
                        case OSSAN_TYPE_MASK:
                            inf = RAND_INF_CAN_SPEAK_HYLIAN;
                            break;
                        case OSSAN_TYPE_GORON:
                            inf = RAND_INF_CAN_SPEAK_GORON;
                            break;
                        case OSSAN_TYPE_ZORA:
                            inf = RAND_INF_CAN_SPEAK_ZORA;
                            break;
                    }
                    break;
            }
            if (inf != RAND_INF_MAX && !Flags_GetRandomizerInf(inf)) {
                *should = false;
            }
        }
    });
}

static RegisterShipInitFunc initFunc(RegisterShuffleSpeak, { "IS_RANDO" });