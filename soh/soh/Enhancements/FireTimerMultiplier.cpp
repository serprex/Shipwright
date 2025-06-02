#include "soh/Enhancements/game-interactor/GameInteractor_Hooks.h"
#include "soh/ShipInit.hpp"

extern "C" {
extern PlayState* gPlayState;
}

void RegisterFireTimerMultiplier() {
    COND_VB_SHOULD(VB_FIRE_TIMER_TICK, CVarGetInteger(CVAR_ENHANCEMENT("FireTimerMultiplier"), 0) != 0, {
        int factor = CVarGetInteger(CVAR_ENHANCEMENT("FireTimerMultiplier"), 0);
        if (factor != 0) {
            if (factor > 0 && gPlayState->gameplayFrames % (factor + 1) != 0) {
                *should = false;
            } else if (gPlayState->gameplayFrames % (6 + factor) == 0) {
                s16* timer = va_arg(args, s16*);
                if (*timer != 0) {
                    *timer--;
                }
            }
        }
    });
}

static RegisterShipInitFunc initFunc(RegisterFireTimerMultiplier, { CVAR_ENHANCEMENT("FireTimerMultiplier") });
