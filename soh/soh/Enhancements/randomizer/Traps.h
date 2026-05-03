#pragma once

#ifndef __cplusplus
#error This header should not be used in C files
#endif

#include "soh/Enhancements/custom-message/text.h"
#include "soh/Enhancements/item-tables/ItemTableTypes.h"
#include "soh/Enhancements/randomizer/randomizerTypes.h"

class CustomMessage;

namespace Rando {
namespace Traps {
Text GetTrapName(RandomizerGet id, RandoIceTrapNames iceTrapNamesOption);
RandomizerGet GetTrapTrickModel();
bool ShouldJunkItemBeTrap();
void BuildIceTrapMessage(CustomMessage& msg, GetItemEntry getItemEntry);
} // namespace Traps
} // namespace Rando