#pragma once

#include "z64item.h"

// This array is structured from input index (getItemID & 0xFF) - 128
const uint8_t GimItemId[] = {
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

void Give_Gim_Bottle(PlayState* play, u8 item) {
#define BUTTON_STATUS_INDEX(button) ((button) >= 4) ? ((button) + 1) : (button)

    s16 i;
    s16 temp = SLOT(item);

    for (i = 0; i < 4; i++) {
        if (gSaveContext.inventory.items[temp + i] == ITEM_BOTTLE) {
            goto BOTTLE_FOUND;
        }
    }

    // No bottle found
    i = 0;

BOTTLE_FOUND:
    // "Item_Pt(1)=%d Item_Pt(2)=%d Item_Pt(3)=%d   Empty Bottle=%d   Content=%d"
    osSyncPrintf("Item_Pt(1)=%d Item_Pt(2)=%d Item_Pt(3)=%d   空瓶=%d   中味=%d\n", gSaveContext.equips.cButtonSlots[0],
                 gSaveContext.equips.cButtonSlots[1], gSaveContext.equips.cButtonSlots[2], temp + i, item);

    for (int buttonIndex = 1; buttonIndex < ARRAY_COUNT(gSaveContext.equips.buttonItems); buttonIndex++) {
        if ((temp + i) == gSaveContext.equips.cButtonSlots[buttonIndex - 1]) {
            gSaveContext.equips.buttonItems[buttonIndex] = item;
            if (play != NULL) {
                Interface_LoadItemIcon2(play, buttonIndex);
            }
            gSaveContext.buttonStatus[BUTTON_STATUS_INDEX(buttonIndex)] = BTN_ENABLED;
            break;
        }
    }

    gSaveContext.inventory.items[temp + i] = item;
}