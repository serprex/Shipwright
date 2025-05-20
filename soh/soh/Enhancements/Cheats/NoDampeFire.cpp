#include "soh/Enhancements/game-interactor/GameInteractor_Hooks.h"
#include "soh/ShipInit.hpp"

extern "C" {
extern PlayState* gPlayState;
#include "src/overlays/actors/ovl_En_Po_Relay/z_en_po_relay.h"
}

#define CVAR_NO_DAMPE_FIRE_NAME CVAR_CHEAT("NoDampeFire")
#define CVAR_NO_DAMPE_FIRE_DEFAULT 0
#define CVAR_NO_DAMPE_FIRE_VALUE CVarGetInteger(CVAR_NO_DAMPE_FIRE_NAME, CVAR_NO_DAMPE_FIRE_DEFAULT)

void OnHonoTrapInit(void* actor) {
    if (gPlayState->sceneNum == SCENE_WINDMILL_AND_DAMPES_GRAVE) {
        Actor_Kill((Actor*)actor);
    }
}

void RegisterNoDampeFire() {
    COND_ID_HOOK(OnActorInit, ACTOR_EN_HONOTRAP, CVAR_NO_DAMPE_FIRE_VALUE, OnHonoTrapInit);
}

static RegisterShipInitFunc initFunc(RegisterNoDampeFire, { CVAR_NO_DAMPE_FIRE_NAME });
