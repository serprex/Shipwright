#include "soh/Enhancements/game-interactor/GameInteractor_Hooks.h"
#include "soh/ShipInit.hpp"
#include "soh/Enhancements/randomizer/context.h"

#define RAND_GET_OPTION(option) Rando::Context::GetInstance()->GetOption(option).Get()

extern "C" {
extern PlayState* gPlayState;
#include "src/overlays/actors/ovl_En_Niw_Lady/z_en_niw_lady.h"
}

void RegisterCuccosToReturn() {
    COND_VB_SHOULD(VB_SET_CUCCO_COUNT, CVarGetInteger(CVAR_ENHANCEMENT("CuccosToReturn"), 7) != 7, {
        EnNiwLady* enNiwLady = va_arg(args, EnNiwLady*);
        // Override starting Cucco count using setting value
        enNiwLady->cuccosInPen = 7 - CVarGetInteger(CVAR_ENHANCEMENT("CuccosToReturn"), 7);
        if (IS_RANDO && enNiwLady->cuccosInPen == 7) {
            // force at least 1 in rando to test str0
            enNiwLady->cuccosInPen = 6;
        }
        *should = false;
    });
}

static RegisterShipInitFunc initFunc(RegisterCuccosToReturn, { CVAR_ENHANCEMENT("CuccosToReturn") });
