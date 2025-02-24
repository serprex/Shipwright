#include "soh/Enhancements/game-interactor/GameInteractor_Hooks.h"
#include "soh/ShipInit.hpp"
#include "soh/Enhancements/randomizer/SeedContext.h"

extern "C" {
#include <z64.h>
#include "functions.h"
#include "variables.h"
#include "src/overlays/actors/ovl_En_Door/z_en_door.h"
#include "src/overlays/actors/ovl_Door_Shutter/z_door_shutter.h"
extern PlayState* gPlayState;
}

void RegisterShuffleDoors() {
    bool shouldRegister = IS_RANDO && RAND_GET_OPTION(RSK_SHUFFLE_DUNGEON_DOORS);

    // Teleport through doors instead of playing animation.
    // OTRfunc_8009728C's MapDoor redirect resolves actual destination.
    COND_VB_SHOULD(VB_PLAYER_DOOR_SETUP, shouldRegister, {
        Player* player = va_arg(args, Player*);
        Actor* doorActor = va_arg(args, Actor*);
        s32 doorDirection = va_arg(args, s32);

        uint8_t mapIndex = gSaveContext.mapIndex;
        if (doorActor->id == ACTOR_EN_DOOR) {
            EnDoor* enDoor = reinterpret_cast<EnDoor*>(doorActor);
            if (enDoor->lockTimer != 0) {
                gSaveContext.inventory.dungeonKeys[mapIndex]--;
                Flags_SetSwitch(gPlayState, doorActor->params & 0x3F);
                Audio_PlayActorSound2(doorActor, NA_SE_EV_CHAIN_KEY_UNLOCK);
                GameInteractor_ExecuteOnDungeonKeyUsedHooks(mapIndex);
                enDoor->lockTimer = 0;
                doorActor->params = (doorActor->params & ~0x380) | (DOOR_SCENEEXIT << 7);
            }
        } else if (doorActor->id == ACTOR_DOOR_SHUTTER) {
            DoorShutter* shutter = reinterpret_cast<DoorShutter*>(doorActor);
            if (shutter->doorType == SHUTTER_KEY_LOCKED && shutter->unlockTimer != 0) {
                if (shutter->doorType != SHUTTER_BOSS) {
                    gSaveContext.inventory.dungeonKeys[mapIndex]--;
                }
                Flags_SetSwitch(gPlayState, shutter->dyna.actor.params & 0x3F);
                Audio_PlayActorSound2(doorActor, NA_SE_EV_CHAIN_KEY_UNLOCK);
                GameInteractor_ExecuteOnDungeonKeyUsedHooks(mapIndex);
                shutter->unlockTimer = 0;
                shutter->unk_164 = 1;
            }
        }

        s32 frontRoom =
            gPlayState->transiActorCtx.list[(u16)doorActor->params >> 10].sides[(doorDirection > 0) ? 0 : 1].room;
        if (frontRoom != gPlayState->roomCtx.curRoom.num) {
            func_8009728C(gPlayState, &gPlayState->roomCtx, frontRoom);

            // Clean up previous room's actors. Vanilla calls func_80097534 after the door animation/cutscene
            // completes, which kills actors not in the current or previous room (func_80031B14)
            func_80097534(gPlayState, &gPlayState->roomCtx);
        }

        player->doorType = PLAYER_DOORTYPE_NONE;
        player->doorActor = NULL;
        *should = false;
    });
}

static RegisterShipInitFunc initFunc(RegisterShuffleDoors, { "IS_RANDO" });
