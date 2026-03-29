#pragma once

#include <string>
#include <vector>
#include <stdint.h>
#include <libultraship/libultraship.h>

void DrawItemAmmo(int itemId);

typedef enum ItemKind {
    ITEM_KIND_ITEM,
    ITEM_KIND_QUEST,
    ITEM_KIND_RG,
} ItemKind;

typedef struct ItemTrackerItem {
    uint32_t id;
    ItemKind kind;
    std::string name;
    std::string nameFaded;
    uint32_t data;
    void (*drawFunc)(ItemTrackerItem);
} ItemTrackerItem;

bool HasSong(ItemTrackerItem);
bool HasQuestItem(ItemTrackerItem);
bool HasEquipment(ItemTrackerItem);

#define ITEM_TRACKER_ITEM(id, data, drawFunc) \
    { id, ITEM_KIND_ITEM, #id, #id "_Faded", data, drawFunc }
#define ITEM_TRACKER_ITEM_CUSTOM(id, name, data, drawFunc) \
    { id, ITEM_KIND_ITEM, #name, #name "_Faded", data, drawFunc }

#define ITEM_TRACKER_QUEST(id, data, drawFunc) \
    { id, ITEM_KIND_QUEST, #id, #id "_Faded", data, drawFunc }
#define ITEM_TRACKER_QUEST_CUSTOM(id, name, data, drawFunc) \
    { id, ITEM_KIND_QUEST, #name, #name "_Faded", data, drawFunc }

#define ITEM_TRACKER_RG(id, data, drawFunc) \
    { id, ITEM_KIND_RG, #id, #id "_Faded", data, drawFunc }
#define ITEM_TRACKER_RG_CUSTOM(id, name, data, drawFunc) \
    { id, ITEM_KIND_RG, #name, #name "_Faded", data, drawFunc }

static std::array<const char*, 16> itemTrackerWindowIDs = { "Item Tracker",
                                                            "Inventory Items Tracker",
                                                            "Equipment Items Tracker",
                                                            "Misc Items Tracker",
                                                            "Dungeon Rewards Tracker",
                                                            "Songs Tracker",
                                                            "Dungeon Items Tracker",
                                                            "Greg Tracker",
                                                            "Triforce Piece Tracker",
                                                            "Boss Soul Tracker",
                                                            "Ocarina Button Tracker",
                                                            "Overworld Key Tracker",
                                                            "Silver Rupee Tracker",
                                                            "Fishing Pole Tracker",
                                                            "Personal Notes",
                                                            "Total Checks" };
void ItemTracker_LoadFromPreset(nlohmann::json trackerInfo);

typedef struct ItemTrackerDungeon {
    uint32_t id;
    std::vector<uint32_t> items;
} ItemTrackerDungeon;

class ItemTrackerSettingsWindow final : public Ship::GuiWindow {
  public:
    using GuiWindow::GuiWindow;

  protected:
    void InitElement() override{};
    void DrawElement() override;
    void UpdateElement() override{};
};

class ItemTrackerWindow final : public Ship::GuiWindow {
  public:
    using GuiWindow::GuiWindow;
    void Draw() override;

  protected:
    void InitElement() override;
    void DrawElement() override;
    void UpdateElement() override{};
};
