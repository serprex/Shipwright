#pragma once

#include <stdint.h>
#include "soh/Enhancements/item-tables/ItemTableTypes.h"

#ifdef __cplusplus
extern "C" {
#endif

GetItemEntry Gim_RetrieveOobItemEntry(int16_t getItemId);

#ifdef __cplusplus
}
#endif
