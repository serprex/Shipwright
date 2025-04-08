#include "soh/Enhancements/game-interactor/GameInteractor.h"
#include "soh/Enhancements/game-interactor/GameInteractor_Hooks.h"
#include "soh/OTRGlobals.h"

extern "C" {
#include "z64save.h"
}

void FasterBeanSkulltula_Register() {
    REGISTER_VB_SHOULD(VB_SPAWN_BEAN_SKULLTULA, {
        if (CVarGetInteger(CVAR_ENHANCEMENT("FasterBeanSkull"), 0)) {
            *should = true;
        }
    });
}
