#pragma once

#include <soh/OTRGlobals.h>
#include <soh/Enhancements/randomizer/randomizerTypes.h>
#include <stdint.h>
#include <libultraship/libultra.h>

static bool IsSilverInPool(RandomizerGet rg);
static RandomizerGet SilverFromSwitchFlag(s16 switchFlag);
static s8 SilverTotal(RandomizerGet rg);
static bool IsSilverCleared(s16 switchFlag);
static bool IsSilverCleared(RandomizerGet rg);
static bool IsSilver(RandomizerGet rg);
