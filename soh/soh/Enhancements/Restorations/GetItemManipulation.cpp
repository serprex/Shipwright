#include "GimRestoration.h"
#include "soh/Enhancements/game-interactor/GameInteractor_Hooks.h"
#include "soh/Enhancements/item-tables/ItemTableManager.h"
#include "soh/ShipInit.hpp"

extern "C" {
#include "macros.h"
#include "variables.h"
extern PlayState* gPlayState;
}

// On N64, Get Item Manipulation (GIM) makes the player receive an item with a negative getItemId,
// so the vanilla lookup `sGetItemTable[getItemId - 1]` reads out of bounds below the table. The
// bytes it lands on are fixed player overlay data, so each negative getItemId deterministically
// resolves to the itemId below, indexed by getItemId + 128. getItemId is s8 on console, so
// [-128, -1] covers every value reachable there.
static const uint8_t sGimItemIds[128] = {
    ITEM_POE,          ITEM_BOMB,         ITEM_NONE,         ITEM_BEAN,          ITEM_NUT,          ITEM_BOMB,
    ITEM_NONE,         ITEM_BOMBS_10,     ITEM_TUNIC_GORON,  ITEM_NONE,          ITEM_ARROW_FIRE,   ITEM_BOOTS_HOVER,
    ITEM_STICK,        ITEM_STICK,        ITEM_ARROW_FIRE,   ITEM_MASK_KEATON,   ITEM_NONE,         ITEM_BOMBS_5,
    ITEM_ARROW_FIRE,   ITEM_POTION_RED,   ITEM_STICK,        ITEM_ARROW_ICE,     ITEM_STICK,        ITEM_BOMB,
    ITEM_SLINGSHOT,    ITEM_PRESCRIPTION, ITEM_NONE,         ITEM_BOMBS_5,       ITEM_SLINGSHOT,    ITEM_BOMBS_10,
    ITEM_NUT,          ITEM_ODD_POTION,   ITEM_STICK,        ITEM_NUT,           ITEM_STICK,        ITEM_NONE,
    ITEM_NONE,         ITEM_BOMBS_10,     ITEM_STICK,        ITEM_BOW,           ITEM_STICK,        ITEM_STICK,
    ITEM_NUT,          ITEM_NUT,          ITEM_STICK,        ITEM_TUNIC_GORON,   ITEM_STICK,        ITEM_TUNIC_GORON,
    ITEM_NONE,         ITEM_TUNIC_GORON,  ITEM_STICK,        ITEM_TUNIC_GORON,   ITEM_STICK,        ITEM_TUNIC_GORON,
    ITEM_STICK,        ITEM_TUNIC_GORON,  ITEM_ARROW_LIGHT,  ITEM_ARROW_LIGHT,   ITEM_POTION_BLUE,  ITEM_ARROW_LIGHT,
    ITEM_POTION_BLUE,  ITEM_POTION_BLUE,  ITEM_BIG_POE,      ITEM_POTION_BLUE,   ITEM_BIG_POE,      ITEM_ARROW_LIGHT,
    ITEM_POTION_BLUE,  ITEM_ARROW_LIGHT,  ITEM_POTION_BLUE,  ITEM_STICK,         ITEM_MASK_BUNNY,   ITEM_ARROW_FIRE,
    ITEM_POCKET_CUCCO, ITEM_ARROW_FIRE,   ITEM_POCKET_CUCCO, ITEM_ARROW_FIRE,    ITEM_POCKET_EGG,   ITEM_ARROW_FIRE,
    ITEM_POCKET_CUCCO, ITEM_ARROW_FIRE,   ITEM_STICK,        ITEM_SHIELD_HYLIAN, ITEM_STICK,        ITEM_TUNIC_GORON,
    ITEM_STICK,        ITEM_TUNIC_KOKIRI, ITEM_STICK,        ITEM_TUNIC_GORON,   ITEM_STICK,        ITEM_TUNIC_KOKIRI,
    ITEM_STICK,        ITEM_NONE,         ITEM_NONE,         ITEM_NONE,          ITEM_STICK,        ITEM_STICK,
    ITEM_NONE,         ITEM_NONE,         ITEM_STICK,        ITEM_STICK,         ITEM_STICK,        ITEM_STICK,
    ITEM_NONE,         ITEM_NONE,         ITEM_STICK,        ITEM_ARROW_FIRE,    ITEM_LETTER_ZELDA, ITEM_ARROW_FIRE,
    ITEM_LETTER_ZELDA, ITEM_ARROW_FIRE,   ITEM_POCKET_EGG,   ITEM_ARROW_FIRE,    ITEM_POCKET_EGG,   ITEM_ARROW_FIRE,
    ITEM_LETTER_ZELDA, ITEM_STICK,        ITEM_STICK,        ITEM_STICK,         ITEM_STICK,        ITEM_SHIELD_HYLIAN,
    ITEM_STICK,        ITEM_STICK,        ITEM_STICK,        ITEM_STICK,         ITEM_STICK,        ITEM_STICK,
    ITEM_STICK,        ITEM_STICK
};

extern "C" GetItemEntry Gim_RetrieveOobItemEntry(int16_t getItemId) {
    // SoH widened Player.getItemId from s8 to s16, so values below the console range can
    // exist here; treat them (and the restoration being disabled) as an item table miss.
    if (!CVarGetInteger(CVAR_ENHANCEMENT("GetItemManipulation"), 0) || getItemId < -128) {
        return GET_ITEM_NONE;
    }

    // Only the received itemId of the console OOB read is documented, so use the compass
    // entry as a stand-in for the rest (object, draw id, text) to keep the get-item
    // cutscene valid.
    GetItemEntry giEntry = ItemTableManager::Instance->RetrieveItemEntry(MOD_NONE, GI_COMPASS);
    giEntry.itemId = sGimItemIds[getItemId + 128];
    return giEntry;
}
