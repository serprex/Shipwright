#include <soh/OTRGlobals.h>
#include "dungeon.h"
#include "SeedContext.h"
#include "draw.h"
#include "static_data.h"
#include "randomizer.h"
#include "randomizer_check_tracker.h"


static bool IsSilverInPool(RandomizerGet rg);
static RandomizerGet SilverFromSwitchFlag(s16 switchFlag);
static s8* SilverFieldFromSaveContext(SaveContext* saveContext, RandomizerGet rg);
static s8 SilverTotal(RandomizerGet rg);
static bool IsSilverCleared(s16 switchFlag);
static bool IsSilverCleared(RandomizerGet rg);
static bool IsSilver(RandomizerGet rg);