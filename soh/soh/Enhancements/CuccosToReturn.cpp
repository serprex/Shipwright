#include "soh/Enhancements/game-interactor/GameInteractor_Hooks.h"
#include "soh/ShipInit.hpp"
#include "soh/Enhancements/randomizer/context.h"

#define RAND_GET_OPTION(option) Rando::Context::GetInstance()->GetOption(option).Get()

extern "C" {
extern PlayState* gPlayState;
#include "src/overlays/actors/ovl_En_Niw_Lady/z_en_niw_lady.h"
}

void RegisterCuccosToReturn() {
    COND_VB_SHOULD(VB_SET_CUCCO_COUNT, IS_RANDO || CVarGetInteger(CVAR_ENHANCEMENT("CuccosToReturn"), 7) != 7, {
        EnNiwLady* enNiwLady = va_arg(args, EnNiwLady*);
        // Override starting Cucco count using setting value
        enNiwLady->cuccosInPen =
            7 - (IS_RANDO ? RAND_GET_OPTION(RSK_CUCCO_COUNT) : CVarGetInteger(CVAR_ENHANCEMENT("CuccosToReturn"), 7));
        *should = false;
    });
}

static RegisterShipInitFunc initFunc(RegisterCuccosToReturn, { "IS_RANDO", CVAR_ENHANCEMENT("CuccosToReturn") });
