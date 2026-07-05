#include "GetItemManipulation.h"
#include "soh/Enhancements/game-interactor/GameInteractor_Hooks.h"
#include "soh/Enhancements/item-tables/ItemTableManager.h"

extern "C" {
#include "macros.h"
#include "variables.h"
extern PlayState* gPlayState;
GetItemID RetrieveGetItemIDFromItemID(ItemID itemID);
}

// On N64, Get Item Manipulation (GIM) makes the player receive an item with a negative getItemId,
// so the vanilla lookup `sGetItemTable[getItemId - 1]` reads out of bounds below the table. The
// bytes it lands on are fixed player overlay data, so each negative getItemId deterministically
// resolves to a whole GetItemEntry (item, text id, object, draw id) below the table, indexed by
// getItemId + 128. getItemId is s8 on console, so [-128, -1] covers every value reachable there.
//
// https://docs.google.com/spreadsheets/d/1iC55h-oy3NAIW739yNQ8Cg9QNpDGTyVRys_NLHpnG_o
typedef struct {
    uint16_t itemId;
    uint16_t textId;
    uint16_t objectId;
    uint8_t drawGi;
} GimOobEntry;

// clang-format off
static const GimOobEntry sGimEntriesNtsc[128] = {
    { ITEM_POE,           0xA4, 0x0030, 0x8F },
    { ITEM_BOMB,          0x25, 0x0C20, 0x28 },
    { ITEM_NONE,          0x40, 0x3025, 0x00 },
    { ITEM_BEAN,          0x15, 0x8E0F, 0x00 },
    { ITEM_NUT,           0xA4, 0x0030, 0x8F },
    { ITEM_BOMB,          0x25, 0x0C20, 0x28 },
    { ITEM_NONE,          0xA7, 0x0034, 0xAF },
    { ITEM_BOMBS_10,      0x34, 0x3C01, 0x00 },
    { ITEM_TUNIC_GORON,   0x81, 0x5000, 0x44 },
    { ITEM_NONE,          0x90, 0x3C06, 0x00 },
    { ITEM_ARROW_FIRE,    0xC6, 0x31A0, 0x24 },
    { ITEM_BOOTS_HOVER,   0x3C, 0x8FA4, 0x40 },
    { ITEM_STICK,         0x00, 0x0004, 0x45 },
    { ITEM_STICK,         0x00, 0x3C06, 0x00 },
    { ITEM_ARROW_FIRE,    0x00, 0x0001, 0x10 },
    { ITEM_MASK_KEATON,   0xF0, 0x0C20, 0x2D },
    { ITEM_NONE,          0x00, 0x2825, 0x02 },
    { ITEM_BOMBS_5,       0xAC, 0x3C0E, 0x01 },
    { ITEM_ARROW_FIRE,    0xCE, 0x2DF0, 0x25 },
    { ITEM_POTION_RED,    0x04, 0x8FA4, 0x00 },
    { ITEM_STICK,         0x00, 0x2825, 0x02 },
    { ITEM_ARROW_ICE,     0xCC, 0x2406, 0xC3 },
    { ITEM_STICK,         0x20, 0xC076, 0x0C },
    { ITEM_BOMB,          0x25, 0x8E18, 0x20 },
    { ITEM_SLINGSHOT,     0x01, 0x2000, 0x3C },
    { ITEM_PRESCRIPTION,  0x40, 0x0301, 0x00 },
    { ITEM_NONE,          0x19, 0x066C, 0xAE },
    { ITEM_BOMBS_5,       0x84, 0x8E02, 0x06 },
    { ITEM_SLINGSHOT,     0x62, 0x000D, 0x54 },
    { ITEM_BOMBS_10,      0x1C, 0x9468, 0x00 },
    { ITEM_NUT,           0x01, 0x0200, 0x24 },
    { ITEM_ODD_POTION,    0x00, 0x5121, 0xFF },
    { ITEM_STICK,         0xBF, 0x001C, 0x8F },
    { ITEM_NUT,           0x04, 0x2405, 0x00 },
    { ITEM_STICK,         0x4B, 0x0100, 0x35 },
    { ITEM_NONE,          0x04, 0x0C20, 0x00 },
    { ITEM_NONE,          0xA4, 0x0030, 0x8F },
    { ITEM_BOMBS_10,      0x1C, 0x8FB0, 0x00 },
    { ITEM_STICK,         0xBD, 0x0030, 0x27 },
    { ITEM_BOW,           0x08, 0x0000, 0x00 },
    { ITEM_STICK,         0x00, 0x0000, 0x00 },
    { ITEM_STICK,         0x00, 0x0000, 0x00 },
    { ITEM_NUT,           0x01, 0x0101, 0x01 },
    { ITEM_NUT,           0x01, 0x0101, 0x01 },
    { ITEM_STICK,         0x60, 0x0000, 0x42 },
    { ITEM_TUNIC_GORON,   0x00, 0x3F80, 0x00 },
    { ITEM_STICK,         0xDE, 0x0000, 0x42 },
    { ITEM_TUNIC_GORON,   0x00, 0x429E, 0x00 },
    { ITEM_NONE,          0x6C, 0x0000, 0x42 },
    { ITEM_TUNIC_GORON,   0x00, 0x4198, 0x00 },
    { ITEM_STICK,         0x10, 0x0000, 0x42 },
    { ITEM_TUNIC_GORON,   0x33, 0x4260, 0x33 },
    { ITEM_STICK,         0x88, 0x0000, 0x42 },
    { ITEM_TUNIC_GORON,   0x00, 0x4190, 0x00 },
    { ITEM_STICK,         0x70, 0x0000, 0x41 },
    { ITEM_TUNIC_GORON,   0x00, 0x0009, 0x00 },
    { ITEM_ARROW_LIGHT,   0x67, 0x0008, 0x01 },
    { ITEM_ARROW_LIGHT,   0x7C, 0x0009, 0x01 },
    { ITEM_POTION_BLUE,   0x67, 0x0008, 0x01 },
    { ITEM_ARROW_LIGHT,   0x7C, 0x0009, 0x01 },
    { ITEM_POTION_BLUE,   0x67, 0x0009, 0x01 },
    { ITEM_POTION_BLUE,   0x67, 0x0009, 0x01 },
    { ITEM_BIG_POE,       0x7C, 0x0009, 0x01 },
    { ITEM_POTION_BLUE,   0x67, 0x0009, 0x01 },
    { ITEM_BIG_POE,       0x7C, 0x0008, 0x01 },
    { ITEM_ARROW_LIGHT,   0x7C, 0x0009, 0x01 },
    { ITEM_POTION_BLUE,   0x67, 0xF9C8, 0x01 },
    { ITEM_ARROW_LIGHT,   0x7C, 0xF9C9, 0x01 },
    { ITEM_POTION_BLUE,   0x67, 0x0000, 0x01 },
    { ITEM_STICK,         0x00, 0x0400, 0x00 },
    { ITEM_MASK_BUNNY,    0x00, 0x2720, 0x04 },
    { ITEM_ARROW_FIRE,    0x38, 0x0400, 0x28 },
    { ITEM_POCKET_CUCCO,  0x00, 0x2E78, 0x04 },
    { ITEM_ARROW_FIRE,    0x80, 0x0400, 0x2E },
    { ITEM_POCKET_CUCCO,  0x00, 0x2D90, 0x04 },
    { ITEM_ARROW_FIRE,    0x98, 0x0400, 0x2D },
    { ITEM_POCKET_EGG,    0x00, 0x2D78, 0x04 },
    { ITEM_ARROW_FIRE,    0x50, 0x0400, 0x2E },
    { ITEM_POCKET_CUCCO,  0x00, 0x2E68, 0x04 },
    { ITEM_ARROW_FIRE,    0x60, 0x4220, 0x2E },
    { ITEM_STICK,         0x70, 0x0000, 0x42 },
    { ITEM_SHIELD_HYLIAN, 0xA6, 0x428E, 0xA5 },
    { ITEM_STICK,         0x48, 0x0000, 0x42 },
    { ITEM_TUNIC_GORON,   0x00, 0x421C, 0x00 },
    { ITEM_STICK,         0xD8, 0x0000, 0x41 },
    { ITEM_TUNIC_KOKIRI,  0x00, 0x41B0, 0x00 },
    { ITEM_STICK,         0xEC, 0xCCCD, 0x41 },
    { ITEM_TUNIC_GORON,   0x00, 0x4240, 0x00 },
    { ITEM_STICK,         0x35, 0x2D2E, 0x42 },
    { ITEM_TUNIC_KOKIRI,  0x00, 0x4140, 0x00 },
    { ITEM_STICK,         0x5C, 0x0000, 0x42 },
    { ITEM_NONE,          0xED, 0x036C, 0x0D },
    { ITEM_NONE,          0x92, 0x035E, 0x0D },
    { ITEM_NONE,          0x71, 0x03A9, 0x13 },
    { ITEM_STICK,         0x56, 0x017C, 0x12 },
    { ITEM_STICK,         0xEA, 0x0167, 0x17 },
    { ITEM_NONE,          0x71, 0x03A9, 0x13 },
    { ITEM_NONE,          0x5F, 0x03A9, 0x19 },
    { ITEM_STICK,         0xEA, 0x0167, 0x17 },
    { ITEM_STICK,         0x0D, 0x017C, 0x1E },
    { ITEM_STICK,         0x56, 0x017C, 0x12 },
    { ITEM_STICK,         0xEA, 0x0167, 0x17 },
    { ITEM_NONE,          0x56, 0x017C, 0x12 },
    { ITEM_NONE,          0xEA, 0x0167, 0x17 },
    { ITEM_STICK,         0x00, 0x0000, 0x00 },
    { ITEM_ARROW_FIRE,    0x18, 0x0400, 0x23 },
    { ITEM_LETTER_ZELDA,  0x00, 0x23A8, 0x04 },
    { ITEM_ARROW_FIRE,    0xE0, 0x0400, 0x23 },
    { ITEM_LETTER_ZELDA,  0x00, 0x23F0, 0x04 },
    { ITEM_ARROW_FIRE,    0xF8, 0x0400, 0x23 },
    { ITEM_POCKET_EGG,    0x00, 0x2D98, 0x04 },
    { ITEM_ARROW_FIRE,    0x70, 0x0400, 0x2D },
    { ITEM_POCKET_EGG,    0x00, 0x23C0, 0x04 },
    { ITEM_ARROW_FIRE,    0xC8, 0x0400, 0x23 },
    { ITEM_LETTER_ZELDA,  0x00, 0x23D0, 0x04 },
    { ITEM_STICK,         0x00, 0x0000, 0x00 },
    { ITEM_STICK,         0x00, 0x0000, 0x00 },
    { ITEM_STICK,         0x00, 0x0000, 0x00 },
    { ITEM_STICK,         0x00, 0x0000, 0x00 },
    { ITEM_SHIELD_HYLIAN, 0x00, 0x3F80, 0x00 },
    { ITEM_STICK,         0x00, 0x0000, 0x00 },
    { ITEM_STICK,         0x00, 0x0000, 0x00 },
    { ITEM_STICK,         0x00, 0x0000, 0x00 },
    { ITEM_STICK,         0x00, 0x0000, 0x00 },
    { ITEM_STICK,         0x00, 0x0000, 0x00 },
    { ITEM_STICK,         0x00, 0x0000, 0x00 },
    { ITEM_STICK,         0x00, 0x0000, 0x00 },
    { ITEM_STICK,         0x00, 0x680F, 0x00 },
};

static const GimOobEntry sGimEntriesPal[128] = {
    { ITEM_STICK,            0x00, 0x2825, 0x02 },
    { ITEM_ARROW_ICE,        0x64, 0x0040, 0xC3 },
    { ITEM_ODD_MUSHROOM,     0x00, 0x0015, 0x10 },
    { ITEM_BOMBS_5,          0xAC, 0x8FA4, 0x01 },
    { ITEM_STICK,            0x00, 0x2825, 0x02 },
    { ITEM_ARROW_ICE,        0x2E, 0xAFA7, 0xD5 },
    { ITEM_STICK,            0xA7, 0x0034, 0x8F },
    { ITEM_SWORD_MASTER,     0x20, 0x4481, 0x42 },
    { ITEM_BRACELET,         0xE8, 0x0090, 0xC4 },
    { ITEM_SWORD_MASTER,     0x00, 0x24C6, 0x04 },
    { ITEM_ODD_POTION,       0x0A, 0x403C, 0x46 },
    { ITEM_BOMBS_10,         0x30, 0x4500, 0x00 },
    { ITEM_STICK,            0x00, 0x0000, 0x00 },
    { ITEM_SWORD_MASTER,     0x00, 0x1000, 0x04 },
    { ITEM_STICK,            0xC6, 0x2DF0, 0x24 },
    { ITEM_ARROW_ICE,        0x79, 0x0200, 0xC3 },
    { ITEM_MASK_GORON,       0x0F, 0x01AC, 0x8E },
    { ITEM_SWORD_MASTER,     0x00, 0x25CE, 0x04 },
    { ITEM_POCKET_EGG,       0xCF, 0x0004, 0x15 },
    { ITEM_BOMBS_10,         0x30, 0x0200, 0x00 },
    { ITEM_MASK_GORON,       0x20, 0xC6AD, 0x0C },
    { ITEM_MASK_KEATON,      0x19, 0x0C20, 0x00 },
    { ITEM_NONE,             0x00, 0x2025, 0x02 },
    { ITEM_BOMBS_5,          0x6C, 0x3C01, 0x06 },
    { ITEM_POE,              0x21, 0x0040, 0x34 },
    { ITEM_BOW,              0x25, 0xAE19, 0xC8 },
    { ITEM_SLINGSHOT,        0x03, 0x0684, 0x8E },
    { ITEM_BOMBS_5,          0x7C, 0x5462, 0x06 },
    { ITEM_STICK,            0xBF, 0x001C, 0x8F },
    { ITEM_ARROWS_LARGE,     0x0E, 0x2401, 0x01 },
    { ITEM_BOMB,             0x09, 0xFF00, 0x31 },
    { ITEM_GAUNTLETS_SILVER, 0x08, 0x8FBF, 0x00 },
    { ITEM_STICK,            0x4A, 0x0004, 0x8C },
    { ITEM_MASK_KEATON,      0x0B, 0x354B, 0x00 },
    { ITEM_NUT,              0x4B, 0x0004, 0xAC },
    { ITEM_ARROW_ICE,        0xAC, 0x8FA4, 0xD2 },
    { ITEM_STICK,            0xBF, 0x001C, 0x8F },
    { ITEM_BOMBS_10,         0x18, 0x27BD, 0x00 },
    { ITEM_STICK,            0xE0, 0x0008, 0x03 },
    { ITEM_STICK,            0x00, 0x0000, 0x00 },
    { ITEM_STICK,            0x00, 0x0000, 0x00 },
    { ITEM_STICK,            0x00, 0x0000, 0x00 },
    { ITEM_NUT,              0x01, 0x0101, 0x01 },
    { ITEM_NUT,              0x01, 0x0101, 0x01 },
    { ITEM_STICK,            0x60, 0x0000, 0x42 },
    { ITEM_TUNIC_GORON,      0x00, 0x3F80, 0x00 },
    { ITEM_STICK,            0xDE, 0x0000, 0x42 },
    { ITEM_TUNIC_GORON,      0x00, 0x429E, 0x00 },
    { ITEM_NONE,             0x6C, 0x0000, 0x42 },
    { ITEM_TUNIC_GORON,      0x00, 0x4198, 0x00 },
    { ITEM_STICK,            0x10, 0x0000, 0x42 },
    { ITEM_TUNIC_GORON,      0x33, 0x4260, 0x33 },
    { ITEM_STICK,            0x88, 0x0000, 0x42 },
    { ITEM_TUNIC_GORON,      0x00, 0x4190, 0x00 },
    { ITEM_STICK,            0x70, 0x0000, 0x41 },
    { ITEM_TUNIC_GORON,      0x00, 0x0009, 0x00 },
    { ITEM_ARROW_LIGHT,      0x67, 0x0008, 0x01 },
    { ITEM_ARROW_LIGHT,      0x7C, 0x0009, 0x01 },
    { ITEM_POTION_BLUE,      0x67, 0x0008, 0x01 },
    { ITEM_ARROW_LIGHT,      0x7C, 0x0009, 0x01 },
    { ITEM_POTION_BLUE,      0x67, 0x0009, 0x01 },
    { ITEM_POTION_BLUE,      0x67, 0x0009, 0x01 },
    { ITEM_BIG_POE,          0x7C, 0x0009, 0x01 },
    { ITEM_POTION_BLUE,      0x67, 0x0009, 0x01 },
    { ITEM_BIG_POE,          0x7C, 0x0008, 0x01 },
    { ITEM_ARROW_LIGHT,      0x7C, 0x0009, 0x01 },
    { ITEM_POTION_BLUE,      0x67, 0xF9C8, 0x01 },
    { ITEM_ARROW_LIGHT,      0x7C, 0xF9C9, 0x01 },
    { ITEM_POTION_BLUE,      0x67, 0x0000, 0x01 },
    { ITEM_STICK,            0x00, 0x0400, 0x00 },
    { ITEM_MASK_BUNNY,       0x00, 0x2720, 0x04 },
    { ITEM_ARROW_FIRE,       0x38, 0x0400, 0x28 },
    { ITEM_POCKET_CUCCO,     0x00, 0x2E78, 0x04 },
    { ITEM_ARROW_FIRE,       0x80, 0x0400, 0x2E },
    { ITEM_POCKET_CUCCO,     0x00, 0x2D90, 0x04 },
    { ITEM_ARROW_FIRE,       0x98, 0x0400, 0x2D },
    { ITEM_POCKET_EGG,       0x00, 0x2D78, 0x04 },
    { ITEM_ARROW_FIRE,       0x50, 0x0400, 0x2E },
    { ITEM_POCKET_CUCCO,     0x00, 0x2E68, 0x04 },
    { ITEM_ARROW_FIRE,       0x60, 0x4220, 0x2E },
    { ITEM_STICK,            0x70, 0x0000, 0x42 },
    { ITEM_SHIELD_HYLIAN,    0xA6, 0x428E, 0xA5 },
    { ITEM_STICK,            0x48, 0x0000, 0x42 },
    { ITEM_TUNIC_GORON,      0x00, 0x421C, 0x00 },
    { ITEM_STICK,            0xD8, 0x0000, 0x41 },
    { ITEM_TUNIC_KOKIRI,     0x00, 0x41B0, 0x00 },
    { ITEM_STICK,            0xEC, 0xCCCD, 0x41 },
    { ITEM_TUNIC_GORON,      0x00, 0x4240, 0x00 },
    { ITEM_STICK,            0x35, 0x2D2E, 0x42 },
    { ITEM_TUNIC_KOKIRI,     0x00, 0x4140, 0x00 },
    { ITEM_STICK,            0x5C, 0x0000, 0x42 },
    { ITEM_NONE,             0xED, 0x036C, 0x0D },
    { ITEM_NONE,             0x92, 0x035E, 0x0D },
    { ITEM_NONE,             0x71, 0x03A9, 0x13 },
    { ITEM_STICK,            0x56, 0x017C, 0x12 },
    { ITEM_STICK,            0xEA, 0x0167, 0x17 },
    { ITEM_NONE,             0x71, 0x03A9, 0x13 },
    { ITEM_NONE,             0x5F, 0x03A9, 0x19 },
    { ITEM_STICK,            0xEA, 0x0167, 0x17 },
    { ITEM_STICK,            0x0D, 0x017C, 0x1E },
    { ITEM_STICK,            0x56, 0x017C, 0x12 },
    { ITEM_STICK,            0xEA, 0x0167, 0x17 },
    { ITEM_NONE,             0x56, 0x017C, 0x12 },
    { ITEM_NONE,             0xEA, 0x0167, 0x17 },
    { ITEM_STICK,            0x00, 0x0000, 0x00 },
    { ITEM_ARROW_FIRE,       0x18, 0x0400, 0x23 },
    { ITEM_LETTER_ZELDA,     0x00, 0x23A8, 0x04 },
    { ITEM_ARROW_FIRE,       0xE0, 0x0400, 0x23 },
    { ITEM_LETTER_ZELDA,     0x00, 0x23F0, 0x04 },
    { ITEM_ARROW_FIRE,       0xF8, 0x0400, 0x23 },
    { ITEM_POCKET_EGG,       0x00, 0x2D98, 0x04 },
    { ITEM_ARROW_FIRE,       0x70, 0x0400, 0x2D },
    { ITEM_POCKET_EGG,       0x00, 0x23C0, 0x04 },
    { ITEM_ARROW_FIRE,       0xC8, 0x0400, 0x23 },
    { ITEM_LETTER_ZELDA,     0x00, 0x23D0, 0x04 },
    { ITEM_STICK,            0x00, 0x0000, 0x00 },
    { ITEM_STICK,            0x00, 0x0000, 0x00 },
    { ITEM_STICK,            0x00, 0x0000, 0x00 },
    { ITEM_STICK,            0x00, 0x0000, 0x00 },
    { ITEM_SHIELD_HYLIAN,    0x00, 0x3F80, 0x00 },
    { ITEM_STICK,            0x00, 0x0000, 0x00 },
    { ITEM_STICK,            0x00, 0x0000, 0x00 },
    { ITEM_STICK,            0x00, 0x0000, 0x00 },
    { ITEM_STICK,            0x00, 0x0000, 0x00 },
    { ITEM_STICK,            0x00, 0x0000, 0x00 },
    { ITEM_STICK,            0x00, 0x0000, 0x00 },
    { ITEM_STICK,            0x00, 0x0000, 0x00 },
    { ITEM_STICK,            0x00, 0x680F, 0x00 },
};
// clang-format on

extern "C" GetItemEntry Gim_RetrieveOobGetItemEntry(int16_t getItemId) {
    int32_t version = CVarGetInteger(CVAR_ENHANCEMENT("GetItemManipulation"), GIM_DISABLED);

    // SoH widened Player.getItemId from s8 to s16, so values below the console range can
    // exist here; treat them (and the restoration being disabled) as an item table miss.
    if (version == GIM_DISABLED || getItemId < -128) {
        return GET_ITEM_NONE;
    }

    const GimOobEntry& entry = (version == GIM_PAL ? sGimEntriesPal : sGimEntriesNtsc)[getItemId + 128];

    // Base the entry on the resolved item's own get-item entry so it is given (and, by default,
    // drawn) correctly. A few items reachable via GIM have no get-item entry (e.g. Master Sword,
    // Kokiri Tunic); fall back to a valid scaffold and just set the item id for those.
    GetItemID giId = RetrieveGetItemIDFromItemID((ItemID)entry.itemId);
    GetItemEntry giEntry;
    if (giId != GI_MAX) {
        giEntry = ItemTableManager::Instance->RetrieveItemEntry(MOD_NONE, giId);
    } else {
        giEntry = ItemTableManager::Instance->RetrieveItemEntry(MOD_NONE, GI_COMPASS);
        giEntry.itemId = entry.itemId;
        giEntry.drawItemId = entry.itemId;
    }

    // Best-effort console reproduction: draw the (often "wrong") model the OOB read actually
    // points at, but only when its object and draw id are in range and the object is small enough
    // to fit the fixed get-item object buffer (Player asserts on objects larger than 8 KiB).
    // Otherwise the resolved item's own model is drawn.
    int32_t drawId = ABS((int8_t)entry.drawGi) - 1;
    if (drawId >= 0 && drawId < GID_MAXIMUM && entry.objectId != OBJECT_INVALID && entry.objectId < OBJECT_ID_MAX &&
        (gObjectTable[entry.objectId].vromEnd - gObjectTable[entry.objectId].vromStart) <= 0x2000) {
        giEntry.gi = (int8_t)entry.drawGi;
        giEntry.objectId = entry.objectId;
    }

    // The textId the console shows for the OOB read is documented, so reproduce it either way.
    giEntry.textId = entry.textId;
    return giEntry;
}
