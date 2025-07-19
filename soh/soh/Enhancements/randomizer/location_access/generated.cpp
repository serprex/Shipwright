#include "soh/Enhancements/randomizer/location_access.h"
#include "soh/Enhancements/randomizer/entrance.h"
#include "soh/Enhancements/randomizer/dungeon.h"

using namespace Rando;
extern "C" SaveContext gSaveContext;

void RegionTable_Init_Generated() {
// clang-format off
areaTable[RR_ROOT] = Region("Root", SCENE_ID_MAX, false, {RA_LINKS_POCKET}, {
	EventAccess(&logic->KakarikoVillageGateOpen, []{return ctx->GetOption(RSK_KAK_GATE).Is(RO_KAK_GATE_OPEN);}),
	EventAccess(&logic->THCouldFree1TorchCarpenter, []{return ctx->GetOption(RSK_GERUDO_FORTRESS).Is(RO_GF_CARPENTERS_FREE);}),
	EventAccess(&logic->THCouldFreeDoubleCellCarpenter, []{return (ctx->GetOption(RSK_GERUDO_FORTRESS).Is(RO_GF_CARPENTERS_FREE) || ctx->GetOption(RSK_GERUDO_FORTRESS).Is(RO_GF_CARPENTERS_FAST));}),
	EventAccess(&logic->TH_CouldFreeDeadEndCarpenter, []{return (ctx->GetOption(RSK_GERUDO_FORTRESS).Is(RO_GF_CARPENTERS_FREE) || ctx->GetOption(RSK_GERUDO_FORTRESS).Is(RO_GF_CARPENTERS_FAST));}),
	EventAccess(&logic->THCouldRescueSlopeCarpenter, []{return (ctx->GetOption(RSK_GERUDO_FORTRESS).Is(RO_GF_CARPENTERS_FREE) || ctx->GetOption(RSK_GERUDO_FORTRESS).Is(RO_GF_CARPENTERS_FAST));}),
	EventAccess(&logic->THRescuedAllCarpenters, []{return ctx->GetOption(RSK_GERUDO_FORTRESS).Is(RO_GF_CARPENTERS_FREE);}),
}, {
	LOCATION(RC_LINKS_POCKET, true),
	LOCATION(RC_TRIFORCE_COMPLETED, (gSaveContext.ship.quest.data.randomizer.triforcePiecesCollected >= (ctx->GetOption(RSK_TRIFORCE_HUNT_PIECES_REQUIRED).Get() + 1))),
	LOCATION(RC_SARIA_SONG_HINT, logic->CanUse(RG_SARIAS_SONG)),
}, {
	Entrance(RR_ROOT_EXITS, []{return true;}),
});
areaTable[RR_ROOT_EXITS] = Region("Root Exits", SCENE_ID_MAX, false, {RA_LINKS_POCKET}, {}, {}, {
	Entrance(RR_CHILD_SPAWN, []{return logic->IsChild;}),
	Entrance(RR_ADULT_SPAWN, []{return logic->IsAdult;}),
	Entrance(RR_MINUET_OF_FOREST_WARP, []{return logic->CanUse(RG_MINUET_OF_FOREST);}),
	Entrance(RR_BOLERO_OF_FIRE_WARP, []{return logic->CanUse(RG_BOLERO_OF_FIRE);}),
	Entrance(RR_SERENADE_OF_WATER_WARP, []{return logic->CanUse(RG_SERENADE_OF_WATER);}),
	Entrance(RR_NOCTURNE_OF_SHADOW_WARP, []{return logic->CanUse(RG_NOCTURNE_OF_SHADOW);}),
	Entrance(RR_REQUIEM_OF_SPIRIT_WARP, []{return logic->CanUse(RG_REQUIEM_OF_SPIRIT);}),
	Entrance(RR_PRELUDE_OF_LIGHT_WARP, []{return logic->CanUse(RG_PRELUDE_OF_LIGHT);}),
});
areaTable[RR_CHILD_SPAWN] = Region("Child Spawn", SCENE_ID_MAX, false, {RA_LINKS_POCKET}, {}, {}, {
	Entrance(RR_KF_LINKS_HOUSE, []{return true;}),
});
areaTable[RR_ADULT_SPAWN] = Region("Adult Spawn", SCENE_ID_MAX, false, {RA_LINKS_POCKET}, {}, {}, {
	Entrance(RR_TEMPLE_OF_TIME, []{return true;}),
});
areaTable[RR_MINUET_OF_FOREST_WARP] = Region("Minuet of Forest Warp", SCENE_ID_MAX, false, {RA_LINKS_POCKET}, {}, {}, {
	Entrance(RR_SACRED_FOREST_MEADOW, []{return true;}),
});
areaTable[RR_BOLERO_OF_FIRE_WARP] = Region("Bolero of Fire Warp", SCENE_ID_MAX, false, {RA_LINKS_POCKET}, {}, {}, {
	Entrance(RR_DMC_CENTRAL_LOCAL, []{return true;}),
});
areaTable[RR_SERENADE_OF_WATER_WARP] = Region("Serenade of Water Warp", SCENE_ID_MAX, false, {RA_LINKS_POCKET}, {}, {}, {
	Entrance(RR_LAKE_HYLIA, []{return true;}),
});
areaTable[RR_REQUIEM_OF_SPIRIT_WARP] = Region("Requiem of Spirit Warp", SCENE_ID_MAX, false, {RA_LINKS_POCKET}, {}, {}, {
	Entrance(RR_DESERT_COLOSSUS, []{return true;}),
});
areaTable[RR_NOCTURNE_OF_SHADOW_WARP] = Region("Nocturne of Shadow Warp", SCENE_ID_MAX, false, {RA_LINKS_POCKET}, {}, {}, {
	Entrance(RR_GRAVEYARD_WARP_PAD_REGION, []{return true;}),
});
areaTable[RR_PRELUDE_OF_LIGHT_WARP] = Region("Prelude of Light Warp", SCENE_ID_MAX, false, {RA_LINKS_POCKET}, {}, {}, {
	Entrance(RR_TEMPLE_OF_TIME, []{return true;}),
});
areaTable[RR_KOKIRI_FOREST] = Region("Kokiri Forest", SCENE_KOKIRI_FOREST, false, {RA_KOKIRI_FOREST}, {
	EventAccess(&logic->BeanPlantFairy, []{return (logic->IsChild && (logic->CanUse(RG_MAGIC_BEAN) && logic->CanUse(RG_SONG_OF_STORMS)));}),
	EventAccess(&logic->GossipStoneFairy, []{return logic->CallGossipFairyExceptSuns();}),
	EventAccess(&logic->ShowedMidoSwordAndShield, []{return (logic->IsChild && (logic->CanUse(RG_KOKIRI_SWORD) && logic->CanUse(RG_DEKU_SHIELD)));}),
}, {
	LOCATION(RC_KF_KOKIRI_SWORD_CHEST, logic->IsChild),
	LOCATION(RC_KF_GS_KNOW_IT_ALL_HOUSE, (logic->IsChild && (logic->CanAttack() && logic->CanGetNightTimeGS()))),
	LOCATION(RC_KF_GS_BEAN_PATCH, (logic->CanSpawnSoilSkull() && logic->CanAttack())),
	LOCATION(RC_KF_GS_HOUSE_OF_TWINS, (logic->IsAdult && ((logic->HookshotOrBoomerang() || ((bool)ctx->GetTrickOption(RT_KF_ADULT_GS) && logic->CanUse(RG_HOVER_BOOTS))) && logic->CanGetNightTimeGS()))),
	LOCATION(RC_KF_BEAN_SPROUT_FAIRY_1, (logic->IsChild && (logic->CanUse(RG_MAGIC_BEAN) && logic->CanUse(RG_SONG_OF_STORMS)))),
	LOCATION(RC_KF_BEAN_SPROUT_FAIRY_2, (logic->IsChild && (logic->CanUse(RG_MAGIC_BEAN) && logic->CanUse(RG_SONG_OF_STORMS)))),
	LOCATION(RC_KF_BEAN_SPROUT_FAIRY_3, (logic->IsChild && (logic->CanUse(RG_MAGIC_BEAN) && logic->CanUse(RG_SONG_OF_STORMS)))),
	LOCATION(RC_KF_GOSSIP_STONE_FAIRY, logic->CallGossipFairyExceptSuns()),
	LOCATION(RC_KF_GOSSIP_STONE_FAIRY_BIG, logic->CanUse(RG_SONG_OF_STORMS)),
	LOCATION(RC_KF_BRIDGE_RUPEE, logic->IsChild),
	LOCATION(RC_KF_BEHIND_MIDOS_RUPEE, logic->IsChild),
	LOCATION(RC_KF_SOUTH_GRASS_WEST_RUPEE, logic->IsChild),
	LOCATION(RC_KF_SOUTH_GRASS_EAST_RUPEE, logic->IsChild),
	LOCATION(RC_KF_NORTH_GRASS_WEST_RUPEE, logic->IsChild),
	LOCATION(RC_KF_NORTH_GRASS_EAST_RUPEE, logic->IsChild),
	LOCATION(RC_KF_BOULDER_RUPEE_1, logic->IsChild),
	LOCATION(RC_KF_BOULDER_RUPEE_2, logic->IsChild),
	LOCATION(RC_KF_BEAN_RUPEE_1, (logic->IsAdult && (CanPlantBean(RR_KOKIRI_FOREST) || (logic->CanUse(RG_HOVER_BOOTS) || logic->CanUse(RG_BOOMERANG))))),
	LOCATION(RC_KF_BEAN_RUPEE_2, (logic->IsAdult && (CanPlantBean(RR_KOKIRI_FOREST) || (logic->CanUse(RG_HOVER_BOOTS) || logic->CanUse(RG_BOOMERANG))))),
	LOCATION(RC_KF_BEAN_RUPEE_3, (logic->IsAdult && (CanPlantBean(RR_KOKIRI_FOREST) || (logic->CanUse(RG_HOVER_BOOTS) || logic->CanUse(RG_BOOMERANG))))),
	LOCATION(RC_KF_BEAN_RUPEE_4, (logic->IsAdult && (CanPlantBean(RR_KOKIRI_FOREST) || (logic->CanUse(RG_HOVER_BOOTS) || logic->CanUse(RG_BOOMERANG))))),
	LOCATION(RC_KF_BEAN_RUPEE_5, (logic->IsAdult && (CanPlantBean(RR_KOKIRI_FOREST) || (logic->CanUse(RG_HOVER_BOOTS) || logic->CanUse(RG_BOOMERANG))))),
	LOCATION(RC_KF_BEAN_RUPEE_6, (logic->IsAdult && (CanPlantBean(RR_KOKIRI_FOREST) || (logic->CanUse(RG_HOVER_BOOTS) || logic->CanUse(RG_BOOMERANG))))),
	LOCATION(RC_KF_BEAN_RED_RUPEE, (logic->IsAdult && (CanPlantBean(RR_KOKIRI_FOREST) || (logic->CanUse(RG_HOVER_BOOTS) || logic->CanUse(RG_BOOMERANG))))),
	LOCATION(RC_KF_SARIAS_ROOF_WEST_HEART, logic->IsChild),
	LOCATION(RC_KF_SARIAS_ROOF_EAST_HEART, logic->IsChild),
	LOCATION(RC_KF_SARIAS_ROOF_NORTH_HEART, logic->IsChild),
	LOCATION(RC_KF_GOSSIP_STONE, true),
	LOCATION(RC_KF_CHILD_GRASS_1, (logic->IsChild && logic->CanCutShrubs())),
	LOCATION(RC_KF_CHILD_GRASS_2, (logic->IsChild && logic->CanCutShrubs())),
	LOCATION(RC_KF_CHILD_GRASS_3, (logic->IsChild && logic->CanCutShrubs())),
	LOCATION(RC_KF_CHILD_GRASS_4, (logic->IsChild && logic->CanCutShrubs())),
	LOCATION(RC_KF_CHILD_GRASS_5, (logic->IsChild && logic->CanCutShrubs())),
	LOCATION(RC_KF_CHILD_GRASS_6, (logic->IsChild && logic->CanCutShrubs())),
	LOCATION(RC_KF_CHILD_GRASS_7, (logic->IsChild && logic->CanCutShrubs())),
	LOCATION(RC_KF_CHILD_GRASS_8, (logic->IsChild && logic->CanCutShrubs())),
	LOCATION(RC_KF_CHILD_GRASS_9, (logic->IsChild && logic->CanCutShrubs())),
	LOCATION(RC_KF_CHILD_GRASS_10, (logic->IsChild && logic->CanCutShrubs())),
	LOCATION(RC_KF_CHILD_GRASS_11, (logic->IsChild && logic->CanCutShrubs())),
	LOCATION(RC_KF_CHILD_GRASS_12, (logic->IsChild && logic->CanCutShrubs())),
	LOCATION(RC_KF_CHILD_GRASS_MAZE_1, (logic->IsChild && logic->CanCutShrubs())),
	LOCATION(RC_KF_CHILD_GRASS_MAZE_2, (logic->IsChild && logic->CanCutShrubs())),
	LOCATION(RC_KF_CHILD_GRASS_MAZE_3, (logic->IsChild && logic->CanCutShrubs())),
	LOCATION(RC_KF_ADULT_GRASS_1, (logic->IsAdult && logic->CanCutShrubs())),
	LOCATION(RC_KF_ADULT_GRASS_2, (logic->IsAdult && logic->CanCutShrubs())),
	LOCATION(RC_KF_ADULT_GRASS_3, (logic->IsAdult && logic->CanCutShrubs())),
	LOCATION(RC_KF_ADULT_GRASS_4, (logic->IsAdult && logic->CanCutShrubs())),
	LOCATION(RC_KF_ADULT_GRASS_5, (logic->IsAdult && logic->CanCutShrubs())),
	LOCATION(RC_KF_ADULT_GRASS_6, (logic->IsAdult && logic->CanCutShrubs())),
	LOCATION(RC_KF_ADULT_GRASS_7, (logic->IsAdult && logic->CanCutShrubs())),
	LOCATION(RC_KF_ADULT_GRASS_8, (logic->IsAdult && logic->CanCutShrubs())),
	LOCATION(RC_KF_ADULT_GRASS_9, (logic->IsAdult && logic->CanCutShrubs())),
	LOCATION(RC_KF_ADULT_GRASS_10, (logic->IsAdult && logic->CanCutShrubs())),
	LOCATION(RC_KF_ADULT_GRASS_11, (logic->IsAdult && logic->CanCutShrubs())),
	LOCATION(RC_KF_ADULT_GRASS_12, (logic->IsAdult && logic->CanCutShrubs())),
	LOCATION(RC_KF_ADULT_GRASS_13, (logic->IsAdult && logic->CanCutShrubs())),
	LOCATION(RC_KF_ADULT_GRASS_14, (logic->IsAdult && logic->CanCutShrubs())),
	LOCATION(RC_KF_ADULT_GRASS_15, (logic->IsAdult && logic->CanCutShrubs())),
	LOCATION(RC_KF_ADULT_GRASS_16, (logic->IsAdult && logic->CanCutShrubs())),
	LOCATION(RC_KF_ADULT_GRASS_17, (logic->IsAdult && logic->CanCutShrubs())),
	LOCATION(RC_KF_ADULT_GRASS_18, (logic->IsAdult && logic->CanCutShrubs())),
	LOCATION(RC_KF_ADULT_GRASS_19, (logic->IsAdult && logic->CanCutShrubs())),
	LOCATION(RC_KF_ADULT_GRASS_20, (logic->IsAdult && logic->CanCutShrubs())),
}, {
	Entrance(RR_KF_LINKS_HOUSE, []{return true;}),
	Entrance(RR_KF_MIDOS_HOUSE, []{return true;}),
	Entrance(RR_KF_SARIAS_HOUSE, []{return true;}),
	Entrance(RR_KF_HOUSE_OF_TWINS, []{return true;}),
	Entrance(RR_KF_KNOW_IT_ALL_HOUSE, []{return true;}),
	Entrance(RR_KF_KOKIRI_SHOP, []{return true;}),
	Entrance(RR_KF_OUTSIDE_DEKU_TREE, []{return ((logic->IsAdult && (logic->CanPassEnemy(RE_BIG_SKULLTULA) || logic->ForestTempleClear)) || (ctx->GetOption(RSK_FOREST).Is(RO_CLOSED_FOREST_OFF) || logic->ShowedMidoSwordAndShield));}),
	Entrance(RR_THE_LOST_WOODS, []{return true;}),
	Entrance(RR_LW_BRIDGE_FROM_FOREST, []{return (logic->IsAdult || (ctx->GetOption(RSK_FOREST).IsNot(RO_CLOSED_FOREST_ON) || logic->DekuTreeClear));}),
	Entrance(RR_KF_STORMS_GROTTO, []{return logic->CanOpenStormsGrotto();}),
});
areaTable[RR_KF_LINKS_HOUSE] = Region("KF Link's House", SCENE_LINKS_HOUSE, false, {}, {}, {
	LOCATION(RC_KF_LINKS_HOUSE_COW, (logic->IsAdult && (logic->CanUse(RG_EPONAS_SONG) && logic->LinksCow))),
	LOCATION(RC_KF_LINKS_HOUSE_POT, logic->CanBreakPots()),
}, {
	Entrance(RR_KOKIRI_FOREST, []{return true;}),
});
areaTable[RR_KF_MIDOS_HOUSE] = Region("KF Mido's House", SCENE_MIDOS_HOUSE, false, {}, {}, {
	LOCATION(RC_KF_MIDOS_TOP_LEFT_CHEST, true),
	LOCATION(RC_KF_MIDOS_TOP_RIGHT_CHEST, true),
	LOCATION(RC_KF_MIDOS_BOTTOM_LEFT_CHEST, true),
	LOCATION(RC_KF_MIDOS_BOTTOM_RIGHT_CHEST, true),
}, {
	Entrance(RR_KOKIRI_FOREST, []{return true;}),
});
areaTable[RR_KF_SARIAS_HOUSE] = Region("KF Saria's House", SCENE_SARIAS_HOUSE, false, {}, {}, {
	LOCATION(RC_KF_SARIAS_TOP_LEFT_HEART, true),
	LOCATION(RC_KF_SARIAS_TOP_RIGHT_HEART, true),
	LOCATION(RC_KF_SARIAS_BOTTOM_LEFT_HEART, true),
	LOCATION(RC_KF_SARIAS_BOTTOM_RIGHT_HEART, true),
}, {
	Entrance(RR_KOKIRI_FOREST, []{return true;}),
});
areaTable[RR_KF_HOUSE_OF_TWINS] = Region("KF House of Twins", SCENE_TWINS_HOUSE, false, {}, {}, {
	LOCATION(RC_KF_TWINS_HOUSE_POT_1, logic->CanBreakPots()),
	LOCATION(RC_KF_TWINS_HOUSE_POT_2, logic->CanBreakPots()),
}, {
	Entrance(RR_KOKIRI_FOREST, []{return true;}),
});
areaTable[RR_KF_KNOW_IT_ALL_HOUSE] = Region("KF Know It All House", SCENE_KNOW_IT_ALL_BROS_HOUSE, false, {}, {}, {
	LOCATION(RC_KF_BROTHERS_HOUSE_POT_1, logic->CanBreakPots()),
	LOCATION(RC_KF_BROTHERS_HOUSE_POT_2, logic->CanBreakPots()),
}, {
	Entrance(RR_KOKIRI_FOREST, []{return true;}),
});
areaTable[RR_KF_KOKIRI_SHOP] = Region("KF Kokiri Shop", SCENE_KOKIRI_SHOP, false, {}, {}, {
	LOCATION(RC_KF_SHOP_ITEM_1, true),
	LOCATION(RC_KF_SHOP_ITEM_2, true),
	LOCATION(RC_KF_SHOP_ITEM_3, true),
	LOCATION(RC_KF_SHOP_ITEM_4, true),
	LOCATION(RC_KF_SHOP_ITEM_5, true),
	LOCATION(RC_KF_SHOP_ITEM_6, true),
	LOCATION(RC_KF_SHOP_ITEM_7, true),
	LOCATION(RC_KF_SHOP_ITEM_8, true),
}, {
	Entrance(RR_KOKIRI_FOREST, []{return true;}),
});
areaTable[RR_KF_OUTSIDE_DEKU_TREE] = Region("KF Outside Deku Tree", SCENE_KOKIRI_FOREST, false, {RA_KOKIRI_FOREST}, {
	EventAccess(&logic->DekuBabaSticks, []{return logic->CanGetDekuBabaSticks();}),
	EventAccess(&logic->DekuBabaNuts, []{return logic->CanGetDekuBabaNuts();}),
	EventAccess(&logic->ShowedMidoSwordAndShield, []{return (logic->IsChild && (logic->CanUse(RG_KOKIRI_SWORD) && logic->CanUse(RG_DEKU_SHIELD)));}),
}, {
	LOCATION(RC_KF_DEKU_TREE_LEFT_GOSSIP_STONE_FAIRY, logic->CallGossipFairyExceptSuns()),
	LOCATION(RC_KF_DEKU_TREE_LEFT_GOSSIP_STONE_FAIRY_BIG, logic->CanUse(RG_SONG_OF_STORMS)),
	LOCATION(RC_KF_DEKU_TREE_RIGHT_GOSSIP_STONE_FAIRY, logic->CallGossipFairyExceptSuns()),
	LOCATION(RC_KF_DEKU_TREE_RIGHT_GOSSIP_STONE_FAIRY_BIG, logic->CanUse(RG_SONG_OF_STORMS)),
	LOCATION(RC_KF_DEKU_TREE_LEFT_GOSSIP_STONE, true),
	LOCATION(RC_KF_DEKU_TREE_RIGHT_GOSSIP_STONE, true),
}, {
	Entrance(RR_DEKU_TREE_ENTRYWAY, []{return (logic->IsChild || (ctx->GetOption(RSK_SHUFFLE_DUNGEON_ENTRANCES).IsNot(RO_DUNGEON_ENTRANCE_SHUFFLE_OFF) && (ctx->GetOption(RSK_FOREST).Is(RO_CLOSED_FOREST_OFF) || logic->ShowedMidoSwordAndShield)));}),
	Entrance(RR_KOKIRI_FOREST, []{return ((logic->IsAdult && (logic->CanPassEnemy(RE_BIG_SKULLTULA) || logic->ForestTempleClear)) || (ctx->GetOption(RSK_FOREST).Is(RO_CLOSED_FOREST_OFF) || logic->ShowedMidoSwordAndShield));}),
});
areaTable[RR_KF_STORMS_GROTTO] = Region("KF Storms Grotto", SCENE_GROTTOS, false, {}, {
	EventAccess(&logic->GossipStoneFairy, []{return logic->CallGossipFairy();}),
	EventAccess(&logic->ButterflyFairy, []{return logic->CanUse(RG_STICKS);}),
	EventAccess(&logic->BugShrub, []{return logic->CanCutShrubs();}),
	EventAccess(&logic->LoneFish, []{return true;}),
}, {
	LOCATION(RC_KF_STORMS_GROTTO_CHEST, true),
	LOCATION(RC_KF_STORMS_GROTTO_FISH, logic->HasBottle()),
	LOCATION(RC_KF_STORMS_GROTTO_GOSSIP_STONE_FAIRY, logic->CallGossipFairy()),
	LOCATION(RC_KF_STORMS_GROTTO_GOSSIP_STONE_FAIRY_BIG, logic->CanUse(RG_SONG_OF_STORMS)),
	LOCATION(RC_KF_STORMS_GROTTO_GOSSIP_STONE, true),
	LOCATION(RC_KF_STORMS_GROTTO_BEEHIVE_LEFT, logic->CanBreakLowerBeehives()),
	LOCATION(RC_KF_STORMS_GROTTO_BEEHIVE_RIGHT, logic->CanBreakLowerBeehives()),
	LOCATION(RC_KF_STORMS_GROTTO_GRASS_1, logic->CanCutShrubs()),
	LOCATION(RC_KF_STORMS_GROTTO_GRASS_2, logic->CanCutShrubs()),
	LOCATION(RC_KF_STORMS_GROTTO_GRASS_3, logic->CanCutShrubs()),
	LOCATION(RC_KF_STORMS_GROTTO_GRASS_4, logic->CanCutShrubs()),
}, {
	Entrance(RR_KOKIRI_FOREST, []{return true;}),
});
areaTable[RR_THE_LOST_WOODS] = Region("Lost Woods", SCENE_LOST_WOODS, false, {RA_THE_LOST_WOODS}, {
	EventAccess(&logic->GossipStoneFairy, []{return logic->CallGossipFairyExceptSuns();}),
	EventAccess(&logic->BeanPlantFairy, []{return (logic->IsChild && (logic->CanUse(RG_MAGIC_BEAN) && logic->CanUse(RG_SONG_OF_STORMS)));}),
	EventAccess(&logic->BugShrub, []{return (logic->IsChild && logic->CanCutShrubs());}),
	EventAccess(&logic->BorrowSpookyMask, []{return (logic->IsChild && (logic->BorrowSkullMask && (logic->CanUse(RG_SARIAS_SONG) && logic->HasItem(RG_CHILD_WALLET))));}),
}, {
	LOCATION(RC_LW_SKULL_KID, (logic->IsChild && logic->CanUse(RG_SARIAS_SONG))),
	LOCATION(RC_LW_TRADE_COJIRO, (logic->IsAdult && logic->CanUse(RG_COJIRO))),
	LOCATION(RC_LW_TRADE_ODD_POTION, (logic->IsAdult && logic->CanUse(RG_ODD_POTION))),
	LOCATION(RC_LW_OCARINA_MEMORY_GAME, (logic->IsChild && (logic->HasItem(RG_FAIRY_OCARINA) && (logic->OcarinaButtons() >= 5)))),
	LOCATION(RC_LW_TARGET_IN_WOODS, (logic->IsChild && logic->CanUse(RG_FAIRY_SLINGSHOT))),
	LOCATION(RC_LW_DEKU_SCRUB_NEAR_BRIDGE, (logic->IsChild && logic->CanStunDeku())),
	LOCATION(RC_LW_GS_BEAN_PATCH_NEAR_BRIDGE, (logic->CanSpawnSoilSkull() && logic->CanAttack())),
	LOCATION(RC_LW_SHORTCUT_RUPEE_1, (logic->IsChild && (logic->HasItem(RG_SILVER_SCALE) || logic->CanUse(RG_IRON_BOOTS)))),
	LOCATION(RC_LW_SHORTCUT_RUPEE_2, (logic->IsChild && (logic->HasItem(RG_SILVER_SCALE) || logic->CanUse(RG_IRON_BOOTS)))),
	LOCATION(RC_LW_SHORTCUT_RUPEE_3, (logic->IsChild && (logic->HasItem(RG_SILVER_SCALE) || logic->CanUse(RG_IRON_BOOTS)))),
	LOCATION(RC_LW_SHORTCUT_RUPEE_4, (logic->IsChild && (logic->HasItem(RG_SILVER_SCALE) || logic->CanUse(RG_IRON_BOOTS)))),
	LOCATION(RC_LW_SHORTCUT_RUPEE_5, (logic->IsChild && (logic->HasItem(RG_SILVER_SCALE) || logic->CanUse(RG_IRON_BOOTS)))),
	LOCATION(RC_LW_SHORTCUT_RUPEE_6, (logic->IsChild && (logic->HasItem(RG_SILVER_SCALE) || logic->CanUse(RG_IRON_BOOTS)))),
	LOCATION(RC_LW_SHORTCUT_RUPEE_7, (logic->IsChild && (logic->HasItem(RG_SILVER_SCALE) || logic->CanUse(RG_IRON_BOOTS)))),
	LOCATION(RC_LW_SHORTCUT_RUPEE_8, (logic->IsChild && (logic->HasItem(RG_SILVER_SCALE) || logic->CanUse(RG_IRON_BOOTS)))),
	LOCATION(RC_LW_BEAN_SPROUT_NEAR_BRIDGE_FAIRY_1, (logic->IsChild && (logic->CanUse(RG_MAGIC_BEAN) && logic->CanUse(RG_SONG_OF_STORMS)))),
	LOCATION(RC_LW_BEAN_SPROUT_NEAR_BRIDGE_FAIRY_2, (logic->IsChild && (logic->CanUse(RG_MAGIC_BEAN) && logic->CanUse(RG_SONG_OF_STORMS)))),
	LOCATION(RC_LW_BEAN_SPROUT_NEAR_BRIDGE_FAIRY_3, (logic->IsChild && (logic->CanUse(RG_MAGIC_BEAN) && logic->CanUse(RG_SONG_OF_STORMS)))),
	LOCATION(RC_LW_GOSSIP_STONE_FAIRY, logic->CallGossipFairyExceptSuns()),
	LOCATION(RC_LW_GOSSIP_STONE_FAIRY_BIG, logic->CanUse(RG_SONG_OF_STORMS)),
	LOCATION(RC_LW_SHORTCUT_STORMS_FAIRY, logic->CanUse(RG_SONG_OF_STORMS)),
	LOCATION(RC_LW_GOSSIP_STONE, true),
	LOCATION(RC_LW_GRASS_1, logic->CanCutShrubs()),
	LOCATION(RC_LW_GRASS_2, logic->CanCutShrubs()),
	LOCATION(RC_LW_GRASS_3, logic->CanCutShrubs()),
}, {
	Entrance(RR_LW_FOREST_EXIT, []{return true;}),
	Entrance(RR_GC_WOODS_WARP, []{return true;}),
	Entrance(RR_LW_BRIDGE, []{return ((logic->IsAdult && (CanPlantBean(RR_THE_LOST_WOODS) || (bool)ctx->GetTrickOption(RT_LW_BRIDGE))) || (logic->CanUse(RG_HOVER_BOOTS) || logic->CanUse(RG_LONGSHOT)));}),
	Entrance(RR_ZR_FROM_SHORTCUT, []{return (logic->HasItem(RG_SILVER_SCALE) || (logic->CanUse(RG_IRON_BOOTS) || ((bool)ctx->GetTrickOption(RT_LOST_WOOD_NAVI_DIVE) && (logic->IsChild && (logic->HasItem(RG_BRONZE_SCALE) && logic->CanJumpslash())))));}),
	Entrance(RR_LW_BEYOND_MIDO, []{return (logic->IsChild || (logic->CanUse(RG_SARIAS_SONG) || (bool)ctx->GetTrickOption(RT_LW_MIDO_BACKFLIP)));}),
	Entrance(RR_LW_NEAR_SHORTCUTS_GROTTO, []{return Here(RR_THE_LOST_WOODS, []{return logic->BlastOrSmash();});}),
});
areaTable[RR_LW_BRIDGE_FROM_FOREST] = Region("LW Bridge From Forest", SCENE_LOST_WOODS, false, {RA_THE_LOST_WOODS}, {}, {
	LOCATION(RC_LW_GIFT_FROM_SARIA, true),
}, {
	Entrance(RR_LW_BRIDGE, []{return true;}),
});
areaTable[RR_LW_BRIDGE] = Region("LW Bridge", SCENE_LOST_WOODS, false, {RA_THE_LOST_WOODS}, {}, {}, {
	Entrance(RR_KOKIRI_FOREST, []{return true;}),
	Entrance(RR_HYRULE_FIELD, []{return true;}),
	Entrance(RR_THE_LOST_WOODS, []{return logic->CanUse(RG_LONGSHOT);}),
});
areaTable[RR_LW_FOREST_EXIT] = Region("LW Forest Exit", SCENE_LOST_WOODS, false, {RA_THE_LOST_WOODS}, {}, {}, {
	Entrance(RR_KOKIRI_FOREST, []{return true;}),
});
areaTable[RR_LW_BEYOND_MIDO] = Region("LW Beyond Mido", SCENE_LOST_WOODS, false, {RA_THE_LOST_WOODS}, {
	EventAccess(&logic->ButterflyFairy, []{return logic->CanUse(RG_STICKS);}),
}, {
	LOCATION(RC_LW_DEKU_SCRUB_NEAR_DEKU_THEATER_RIGHT, (logic->IsChild && logic->CanStunDeku())),
	LOCATION(RC_LW_DEKU_SCRUB_NEAR_DEKU_THEATER_LEFT, (logic->IsChild && logic->CanStunDeku())),
	LOCATION(RC_LW_GS_ABOVE_THEATER, (logic->IsAdult && (((CanPlantBean(RR_LW_BEYOND_MIDO) && logic->CanAttack()) || ((bool)ctx->GetTrickOption(RT_LW_GS_BEAN) && (logic->CanUse(RG_HOOKSHOT) && (logic->CanUse(RG_LONGSHOT) || (logic->CanUse(RG_FAIRY_BOW) || (logic->CanUse(RG_FAIRY_SLINGSHOT) || (logic->CanUse(RG_BOMBCHU_5) || logic->CanUse(RG_DINS_FIRE)))))))) && logic->CanGetNightTimeGS()))),
	LOCATION(RC_LW_GS_BEAN_PATCH_NEAR_THEATER, (logic->CanSpawnSoilSkull() && (logic->CanAttack() || (ctx->GetOption(RSK_SHUFFLE_SCRUBS).Is(RO_SCRUBS_OFF) && logic->CanReflectNuts())))),
	LOCATION(RC_LW_BOULDER_RUPEE, logic->BlastOrSmash()),
	LOCATION(RC_LW_BEAN_SPROUT_NEAR_THEATER_FAIRY_1, (logic->IsChild && (logic->HasItem(RG_MAGIC_BEAN) && logic->CanUse(RG_SONG_OF_STORMS)))),
	LOCATION(RC_LW_BEAN_SPROUT_NEAR_THEATER_FAIRY_2, (logic->IsChild && (logic->HasItem(RG_MAGIC_BEAN) && logic->CanUse(RG_SONG_OF_STORMS)))),
	LOCATION(RC_LW_BEAN_SPROUT_NEAR_THEATER_FAIRY_3, (logic->IsChild && (logic->HasItem(RG_MAGIC_BEAN) && logic->CanUse(RG_SONG_OF_STORMS)))),
	LOCATION(RC_LW_GRASS_4, logic->CanCutShrubs()),
	LOCATION(RC_LW_GRASS_5, logic->CanCutShrubs()),
	LOCATION(RC_LW_GRASS_6, logic->CanCutShrubs()),
	LOCATION(RC_LW_GRASS_7, logic->CanCutShrubs()),
	LOCATION(RC_LW_GRASS_8, logic->CanCutShrubs()),
	LOCATION(RC_LW_GRASS_9, logic->CanCutShrubs()),
}, {
	Entrance(RR_LW_FOREST_EXIT, []{return true;}),
	Entrance(RR_THE_LOST_WOODS, []{return (logic->IsChild || logic->CanUse(RG_SARIAS_SONG));}),
	Entrance(RR_SFM_ENTRYWAY, []{return true;}),
	Entrance(RR_DEKU_THEATER, []{return true;}),
	Entrance(RR_LW_SCRUBS_GROTTO, []{return Here(RR_LW_BEYOND_MIDO, []{return logic->BlastOrSmash();});}),
});
areaTable[RR_LW_NEAR_SHORTCUTS_GROTTO] = Region("LW Near Shortcuts Grotto", SCENE_GROTTOS, false, {}, {
	EventAccess(&logic->GossipStoneFairy, []{return logic->CallGossipFairy();}),
	EventAccess(&logic->ButterflyFairy, []{return logic->CanUse(RG_STICKS);}),
	EventAccess(&logic->BugShrub, []{return logic->CanCutShrubs();}),
	EventAccess(&logic->LoneFish, []{return true;}),
}, {
	LOCATION(RC_LW_NEAR_SHORTCUTS_GROTTO_CHEST, true),
	LOCATION(RC_LW_NEAR_SHORTCUTS_GROTTO_FISH, logic->HasBottle()),
	LOCATION(RC_LW_NEAR_SHORTCUTS_GROTTO_GOSSIP_STONE_FAIRY, logic->CallGossipFairy()),
	LOCATION(RC_LW_NEAR_SHORTCUTS_GROTTO_GOSSIP_STONE_FAIRY_BIG, logic->CanUse(RG_SONG_OF_STORMS)),
	LOCATION(RC_LW_NEAR_SHORTCUTS_GROTTO_GOSSIP_STONE, true),
	LOCATION(RC_LW_NEAR_SHORTCUTS_GROTTO_BEEHIVE_LEFT, logic->CanBreakLowerBeehives()),
	LOCATION(RC_LW_NEAR_SHORTCUTS_GROTTO_BEEHIVE_RIGHT, logic->CanBreakLowerBeehives()),
	LOCATION(RC_LW_NEAR_SHORTCUTS_GROTTO_GRASS_1, logic->CanCutShrubs()),
	LOCATION(RC_LW_NEAR_SHORTCUTS_GROTTO_GRASS_2, logic->CanCutShrubs()),
	LOCATION(RC_LW_NEAR_SHORTCUTS_GROTTO_GRASS_3, logic->CanCutShrubs()),
	LOCATION(RC_LW_NEAR_SHORTCUTS_GROTTO_GRASS_4, logic->CanCutShrubs()),
}, {
	Entrance(RR_THE_LOST_WOODS, []{return true;}),
});
areaTable[RR_DEKU_THEATER] = Region("Deku Theater", SCENE_GROTTOS, false, {}, {}, {
	LOCATION(RC_DEKU_THEATER_SKULL_MASK, (logic->IsChild && logic->BorrowSkullMask)),
	LOCATION(RC_DEKU_THEATER_MASK_OF_TRUTH, (logic->IsChild && logic->BorrowRightMasks)),
}, {
	Entrance(RR_LW_BEYOND_MIDO, []{return true;}),
});
areaTable[RR_LW_SCRUBS_GROTTO] = Region("LW Scrubs Grotto", SCENE_GROTTOS, false, {}, {}, {
	LOCATION(RC_LW_DEKU_SCRUB_GROTTO_REAR, logic->CanStunDeku()),
	LOCATION(RC_LW_DEKU_SCRUB_GROTTO_FRONT, logic->CanStunDeku()),
	LOCATION(RC_LW_DEKU_SCRUB_GROTTO_BEEHIVE, logic->CanBreakUpperBeehives()),
	LOCATION(RC_LW_DEKU_SCRUB_GROTTO_SUN_FAIRY, logic->CanUse(RG_SUNS_SONG)),
}, {
	Entrance(RR_LW_BEYOND_MIDO, []{return true;}),
});
areaTable[RR_SFM_ENTRYWAY] = Region("SFM Entryway", SCENE_SACRED_FOREST_MEADOW, false, {RA_SACRED_FOREST_MEADOW}, {}, {}, {
	Entrance(RR_LW_BEYOND_MIDO, []{return true;}),
	Entrance(RR_SACRED_FOREST_MEADOW, []{return (logic->IsAdult || logic->CanKillEnemy(RE_WOLFOS));}),
	Entrance(RR_SFM_WOLFOS_GROTTO, []{return logic->CanOpenBombGrotto();}),
});
areaTable[RR_SACRED_FOREST_MEADOW] = Region("Sacred Forest Meadow", SCENE_SACRED_FOREST_MEADOW, false, {RA_SACRED_FOREST_MEADOW}, {
	EventAccess(&logic->GossipStoneFairy, []{return logic->CallGossipFairyExceptSuns();}),
}, {
	LOCATION(RC_SONG_FROM_SARIA, (logic->IsChild && logic->HasItem(RG_ZELDAS_LETTER))),
	LOCATION(RC_SHEIK_IN_FOREST, logic->IsAdult),
	LOCATION(RC_SFM_GS, (logic->IsAdult && (logic->HookshotOrBoomerang() && logic->CanGetNightTimeGS()))),
	LOCATION(RC_SFM_MAZE_LOWER_GOSSIP_STONE_FAIRY, logic->CallGossipFairyExceptSuns()),
	LOCATION(RC_SFM_MAZE_LOWER_GOSSIP_STONE_FAIRY_BIG, logic->CanUse(RG_SONG_OF_STORMS)),
	LOCATION(RC_SFM_MAZE_UPPER_GOSSIP_STONE_FAIRY, logic->CallGossipFairyExceptSuns()),
	LOCATION(RC_SFM_MAZE_UPPER_GOSSIP_STONE_FAIRY_BIG, logic->CanUse(RG_SONG_OF_STORMS)),
	LOCATION(RC_SFM_SARIA_GOSSIP_STONE_FAIRY, logic->CallGossipFairyExceptSuns()),
	LOCATION(RC_SFM_SARIA_GOSSIP_STONE_FAIRY_BIG, logic->CanUse(RG_SONG_OF_STORMS)),
	LOCATION(RC_SFM_MAZE_LOWER_GOSSIP_STONE, true),
	LOCATION(RC_SFM_MAZE_UPPER_GOSSIP_STONE, true),
	LOCATION(RC_SFM_SARIA_GOSSIP_STONE, true),
}, {
	Entrance(RR_SFM_ENTRYWAY, []{return true;}),
	Entrance(RR_FOREST_TEMPLE_ENTRYWAY, []{return logic->CanUse(RG_HOOKSHOT);}),
	Entrance(RR_SFM_FAIRY_GROTTO, []{return true;}),
	Entrance(RR_SFM_STORMS_GROTTO, []{return logic->CanOpenStormsGrotto();}),
});
areaTable[RR_SFM_WOLFOS_GROTTO] = Region("SFM Wolfos Grotto", SCENE_GROTTOS, false, {}, {}, {
	LOCATION(RC_SFM_WOLFOS_GROTTO_CHEST, logic->CanKillEnemy(RE_WOLFOS, ED_CLOSE, true, 2)),
}, {
	Entrance(RR_SFM_ENTRYWAY, []{return true;}),
});
areaTable[RR_SFM_FAIRY_GROTTO] = Region("SFM Fairy Grotto", SCENE_GROTTOS, false, {}, {
	EventAccess(&logic->FreeFairies, []{return true;}),
}, {
	LOCATION(RC_SFM_FAIRY_GROTTO_FAIRY_1, true),
	LOCATION(RC_SFM_FAIRY_GROTTO_FAIRY_2, true),
	LOCATION(RC_SFM_FAIRY_GROTTO_FAIRY_3, true),
	LOCATION(RC_SFM_FAIRY_GROTTO_FAIRY_4, true),
	LOCATION(RC_SFM_FAIRY_GROTTO_FAIRY_5, true),
	LOCATION(RC_SFM_FAIRY_GROTTO_FAIRY_6, true),
	LOCATION(RC_SFM_FAIRY_GROTTO_FAIRY_7, true),
	LOCATION(RC_SFM_FAIRY_GROTTO_FAIRY_8, true),
}, {
	Entrance(RR_SACRED_FOREST_MEADOW, []{return true;}),
});
areaTable[RR_SFM_STORMS_GROTTO] = Region("SFM Storms Grotto", SCENE_GROTTOS, false, {}, {}, {
	LOCATION(RC_SFM_DEKU_SCRUB_GROTTO_REAR, logic->CanStunDeku()),
	LOCATION(RC_SFM_DEKU_SCRUB_GROTTO_FRONT, logic->CanStunDeku()),
	LOCATION(RC_SFM_STORMS_GROTTO_BEEHIVE, logic->CanBreakUpperBeehives()),
}, {
	Entrance(RR_SACRED_FOREST_MEADOW, []{return true;}),
});
areaTable[RR_HYRULE_FIELD] = Region("Hyrule Field", SCENE_HYRULE_FIELD, true, {RA_HYRULE_FIELD}, {
	EventAccess(&logic->BigPoeKill, []{return (logic->HasBottle() && (logic->CanUse(RG_FAIRY_BOW) && (logic->CanUse(RG_EPONA) || (bool)ctx->GetTrickOption(RT_HF_BIG_POE_WITHOUT_EPONA))));}),
	EventAccess(&logic->BorrowRightMasks, []{return (logic->IsChild && (logic->BorrowBunnyHood && (logic->HasItem(RG_KOKIRI_EMERALD) && (logic->HasItem(RG_GORON_RUBY) && (logic->HasItem(RG_ZORA_SAPPHIRE) && logic->HasItem(RG_CHILD_WALLET))))));}),
}, {
	LOCATION(RC_HF_OCARINA_OF_TIME_ITEM, (logic->IsChild && ((logic->StoneCount() == 3) && logic->HasItem(RG_BRONZE_SCALE)))),
	LOCATION(RC_SONG_FROM_OCARINA_OF_TIME, (logic->IsChild && ((logic->StoneCount() == 3) && logic->HasItem(RG_BRONZE_SCALE)))),
	LOCATION(RC_HF_POND_STORMS_FAIRY, logic->CanUse(RG_SONG_OF_STORMS)),
	LOCATION(RC_HF_CENTRAL_GRASS_1, logic->CanCutShrubs()),
	LOCATION(RC_HF_CENTRAL_GRASS_2, logic->CanCutShrubs()),
	LOCATION(RC_HF_CENTRAL_GRASS_3, logic->CanCutShrubs()),
	LOCATION(RC_HF_CENTRAL_GRASS_4, logic->CanCutShrubs()),
	LOCATION(RC_HF_CENTRAL_GRASS_5, logic->CanCutShrubs()),
	LOCATION(RC_HF_CENTRAL_GRASS_6, logic->CanCutShrubs()),
	LOCATION(RC_HF_CENTRAL_GRASS_7, logic->CanCutShrubs()),
	LOCATION(RC_HF_CENTRAL_GRASS_8, logic->CanCutShrubs()),
	LOCATION(RC_HF_CENTRAL_GRASS_9, logic->CanCutShrubs()),
	LOCATION(RC_HF_CENTRAL_GRASS_10, logic->CanCutShrubs()),
	LOCATION(RC_HF_CENTRAL_GRASS_11, logic->CanCutShrubs()),
	LOCATION(RC_HF_CENTRAL_GRASS_12, logic->CanCutShrubs()),
	LOCATION(RC_HF_SOUTH_GRASS_1, logic->CanCutShrubs()),
	LOCATION(RC_HF_SOUTH_GRASS_2, logic->CanCutShrubs()),
	LOCATION(RC_HF_SOUTH_GRASS_3, logic->CanCutShrubs()),
	LOCATION(RC_HF_SOUTH_GRASS_4, logic->CanCutShrubs()),
	LOCATION(RC_HF_SOUTH_GRASS_5, logic->CanCutShrubs()),
	LOCATION(RC_HF_SOUTH_GRASS_6, logic->CanCutShrubs()),
	LOCATION(RC_HF_SOUTH_GRASS_7, logic->CanCutShrubs()),
	LOCATION(RC_HF_SOUTH_GRASS_8, logic->CanCutShrubs()),
	LOCATION(RC_HF_SOUTH_GRASS_9, logic->CanCutShrubs()),
	LOCATION(RC_HF_SOUTH_GRASS_10, logic->CanCutShrubs()),
	LOCATION(RC_HF_SOUTH_GRASS_11, logic->CanCutShrubs()),
	LOCATION(RC_HF_SOUTH_GRASS_12, logic->CanCutShrubs()),
	LOCATION(RC_HF_NEAR_MARKET_GRASS_1, logic->CanCutShrubs()),
	LOCATION(RC_HF_NEAR_MARKET_GRASS_2, logic->CanCutShrubs()),
	LOCATION(RC_HF_NEAR_MARKET_GRASS_3, logic->CanCutShrubs()),
	LOCATION(RC_HF_NEAR_MARKET_GRASS_4, logic->CanCutShrubs()),
	LOCATION(RC_HF_NEAR_MARKET_GRASS_5, logic->CanCutShrubs()),
	LOCATION(RC_HF_NEAR_MARKET_GRASS_6, logic->CanCutShrubs()),
	LOCATION(RC_HF_NEAR_MARKET_GRASS_7, logic->CanCutShrubs()),
	LOCATION(RC_HF_NEAR_MARKET_GRASS_8, logic->CanCutShrubs()),
	LOCATION(RC_HF_NEAR_MARKET_GRASS_9, logic->CanCutShrubs()),
	LOCATION(RC_HF_NEAR_MARKET_GRASS_10, logic->CanCutShrubs()),
	LOCATION(RC_HF_NEAR_MARKET_GRASS_11, logic->CanCutShrubs()),
	LOCATION(RC_HF_NEAR_MARKET_GRASS_12, logic->CanCutShrubs()),
	LOCATION(RC_HF_NEAR_KF_GRASS_1, logic->CanCutShrubs()),
	LOCATION(RC_HF_NEAR_KF_GRASS_2, logic->CanCutShrubs()),
	LOCATION(RC_HF_NEAR_KF_GRASS_3, logic->CanCutShrubs()),
	LOCATION(RC_HF_NEAR_KF_GRASS_4, logic->CanCutShrubs()),
	LOCATION(RC_HF_NEAR_KF_GRASS_5, logic->CanCutShrubs()),
	LOCATION(RC_HF_NEAR_KF_GRASS_6, logic->CanCutShrubs()),
	LOCATION(RC_HF_NEAR_KF_GRASS_7, logic->CanCutShrubs()),
	LOCATION(RC_HF_NEAR_KF_GRASS_8, logic->CanCutShrubs()),
	LOCATION(RC_HF_NEAR_KF_GRASS_9, logic->CanCutShrubs()),
	LOCATION(RC_HF_NEAR_KF_GRASS_10, logic->CanCutShrubs()),
	LOCATION(RC_HF_NEAR_KF_GRASS_11, logic->CanCutShrubs()),
	LOCATION(RC_HF_NEAR_KF_GRASS_12, logic->CanCutShrubs()),
}, {
	Entrance(RR_LW_BRIDGE, []{return true;}),
	Entrance(RR_LAKE_HYLIA, []{return true;}),
	Entrance(RR_GERUDO_VALLEY, []{return true;}),
	Entrance(RR_MARKET_ENTRANCE, []{return true;}),
	Entrance(RR_KAKARIKO_VILLAGE, []{return true;}),
	Entrance(RR_ZR_FRONT, []{return true;}),
	Entrance(RR_LON_LON_RANCH, []{return true;}),
	Entrance(RR_HF_SOUTHEAST_GROTTO, []{return Here(RR_HYRULE_FIELD, []{return logic->BlastOrSmash();});}),
	Entrance(RR_HF_OPEN_GROTTO, []{return true;}),
	Entrance(RR_HF_INSIDE_FENCE_GROTTO, []{return logic->CanOpenBombGrotto();}),
	Entrance(RR_HF_COW_GROTTO, []{return ((logic->CanUse(RG_MEGATON_HAMMER) || logic->IsChild) && logic->CanOpenBombGrotto());}),
	Entrance(RR_HF_NEAR_MARKET_GROTTO, []{return Here(RR_HYRULE_FIELD, []{return logic->BlastOrSmash();});}),
	Entrance(RR_HF_FAIRY_GROTTO, []{return Here(RR_HYRULE_FIELD, []{return logic->BlastOrSmash();});}),
	Entrance(RR_HF_NEAR_KAK_GROTTO, []{return logic->CanOpenBombGrotto();}),
	Entrance(RR_HF_TEKTITE_GROTTO, []{return logic->CanOpenBombGrotto();}),
});
areaTable[RR_HF_SOUTHEAST_GROTTO] = Region("HF Southeast Grotto", SCENE_GROTTOS, false, {}, {
	EventAccess(&logic->GossipStoneFairy, []{return logic->CallGossipFairy();}),
	EventAccess(&logic->ButterflyFairy, []{return logic->CanUse(RG_STICKS);}),
	EventAccess(&logic->BugShrub, []{return logic->CanCutShrubs();}),
	EventAccess(&logic->LoneFish, []{return true;}),
}, {
	LOCATION(RC_HF_SOUTHEAST_GROTTO_CHEST, true),
	LOCATION(RC_HF_SOUTHEAST_GROTTO_FISH, logic->HasBottle()),
	LOCATION(RC_HF_SOUTHEAST_GROTTO_GOSSIP_STONE_FAIRY, logic->CallGossipFairy()),
	LOCATION(RC_HF_SOUTHEAST_GROTTO_GOSSIP_STONE_FAIRY_BIG, logic->CanUse(RG_SONG_OF_STORMS)),
	LOCATION(RC_HF_SOUTHEAST_GROTTO_GOSSIP_STONE, true),
	LOCATION(RC_HF_SOUTHEAST_GROTTO_BEEHIVE_LEFT, logic->CanBreakLowerBeehives()),
	LOCATION(RC_HF_SOUTHEAST_GROTTO_BEEHIVE_RIGHT, logic->CanBreakLowerBeehives()),
	LOCATION(RC_HF_SOUTHEAST_GROTTO_GRASS_1, logic->CanCutShrubs()),
	LOCATION(RC_HF_SOUTHEAST_GROTTO_GRASS_2, logic->CanCutShrubs()),
	LOCATION(RC_HF_SOUTHEAST_GROTTO_GRASS_3, logic->CanCutShrubs()),
	LOCATION(RC_HF_SOUTHEAST_GROTTO_GRASS_4, logic->CanCutShrubs()),
}, {
	Entrance(RR_HYRULE_FIELD, []{return true;}),
});
areaTable[RR_HF_OPEN_GROTTO] = Region("HF Open Grotto", SCENE_GROTTOS, false, {}, {
	EventAccess(&logic->GossipStoneFairy, []{return logic->CallGossipFairy();}),
	EventAccess(&logic->ButterflyFairy, []{return logic->CanUse(RG_STICKS);}),
	EventAccess(&logic->BugShrub, []{return logic->CanCutShrubs();}),
	EventAccess(&logic->LoneFish, []{return true;}),
}, {
	LOCATION(RC_HF_OPEN_GROTTO_CHEST, true),
	LOCATION(RC_HF_OPEN_GROTTO_FISH, logic->HasBottle()),
	LOCATION(RC_HF_OPEN_GROTTO_GOSSIP_STONE_FAIRY, logic->CallGossipFairy()),
	LOCATION(RC_HF_OPEN_GROTTO_GOSSIP_STONE_FAIRY_BIG, logic->CanUse(RG_SONG_OF_STORMS)),
	LOCATION(RC_HF_OPEN_GROTTO_GOSSIP_STONE, true),
	LOCATION(RC_HF_OPEN_GROTTO_BEEHIVE_LEFT, logic->CanBreakLowerBeehives()),
	LOCATION(RC_HF_OPEN_GROTTO_BEEHIVE_RIGHT, logic->CanBreakLowerBeehives()),
	LOCATION(RC_HF_OPEN_GROTTO_GRASS_1, logic->CanCutShrubs()),
	LOCATION(RC_HF_OPEN_GROTTO_GRASS_2, logic->CanCutShrubs()),
	LOCATION(RC_HF_OPEN_GROTTO_GRASS_3, logic->CanCutShrubs()),
	LOCATION(RC_HF_OPEN_GROTTO_GRASS_4, logic->CanCutShrubs()),
}, {
	Entrance(RR_HYRULE_FIELD, []{return true;}),
});
areaTable[RR_HF_INSIDE_FENCE_GROTTO] = Region("HF Inside Fence Grotto", SCENE_GROTTOS, false, {}, {}, {
	LOCATION(RC_HF_DEKU_SCRUB_GROTTO, logic->CanStunDeku()),
	LOCATION(RC_HF_INSIDE_FENCE_GROTTO_BEEHIVE, logic->CanBreakLowerBeehives()),
	LOCATION(RC_HF_FENCE_GROTTO_STORMS_FAIRY, logic->CanUse(RG_SONG_OF_STORMS)),
}, {
	Entrance(RR_HYRULE_FIELD, []{return true;}),
});
areaTable[RR_HF_COW_GROTTO] = Region("HF Cow Grotto", SCENE_GROTTOS, false, {}, {}, {}, {
	Entrance(RR_HYRULE_FIELD, []{return true;}),
	Entrance(RR_HF_COW_GROTTO_BEHIND_WEBS, []{return logic->HasFireSource();}),
});
areaTable[RR_HF_COW_GROTTO_BEHIND_WEBS] = Region("HF Cow Grotto Behind Webs", SCENE_GROTTOS, false, {}, {
	EventAccess(&logic->BugShrub, []{return logic->CanCutShrubs();}),
	EventAccess(&logic->GossipStoneFairy, []{return logic->CallGossipFairy();}),
}, {
	LOCATION(RC_HF_GS_COW_GROTTO, logic->CanGetEnemyDrop(RE_GOLD_SKULLTULA, ED_BOOMERANG)),
	LOCATION(RC_HF_COW_GROTTO_COW, logic->CanUse(RG_EPONAS_SONG)),
	LOCATION(RC_HF_COW_GROTTO_GOSSIP_STONE_FAIRY, logic->CallGossipFairy()),
	LOCATION(RC_HF_COW_GROTTO_GOSSIP_STONE_FAIRY_BIG, logic->CanUse(RG_SONG_OF_STORMS)),
	LOCATION(RC_HF_COW_GROTTO_GOSSIP_STONE, true),
	LOCATION(RC_HF_COW_GROTTO_POT_1, logic->CanBreakPots()),
	LOCATION(RC_HF_COW_GROTTO_POT_2, logic->CanBreakPots()),
	LOCATION(RC_HF_COW_GROTTO_GRASS_1, logic->CanCutShrubs()),
	LOCATION(RC_HF_COW_GROTTO_GRASS_2, logic->CanCutShrubs()),
}, {
	Entrance(RR_HF_COW_GROTTO, []{return true;}),
});
areaTable[RR_HF_NEAR_MARKET_GROTTO] = Region("HF Near Market Grotto", SCENE_GROTTOS, false, {}, {
	EventAccess(&logic->GossipStoneFairy, []{return logic->CallGossipFairy();}),
	EventAccess(&logic->ButterflyFairy, []{return logic->CanUse(RG_STICKS);}),
	EventAccess(&logic->BugShrub, []{return logic->CanCutShrubs();}),
	EventAccess(&logic->LoneFish, []{return true;}),
}, {
	LOCATION(RC_HF_NEAR_MARKET_GROTTO_CHEST, true),
	LOCATION(RC_HF_NEAR_MARKET_GROTTO_FISH, logic->HasBottle()),
	LOCATION(RC_HF_NEAR_MARKET_GROTTO_GOSSIP_STONE_FAIRY, logic->CallGossipFairy()),
	LOCATION(RC_HF_NEAR_MARKET_GROTTO_GOSSIP_STONE_FAIRY_BIG, logic->CanUse(RG_SONG_OF_STORMS)),
	LOCATION(RC_HF_NEAR_MARKET_GROTTO_GOSSIP_STONE, true),
	LOCATION(RC_HF_NEAR_MARKET_GROTTO_BEEHIVE_LEFT, logic->CanBreakLowerBeehives()),
	LOCATION(RC_HF_NEAR_MARKET_GROTTO_BEEHIVE_RIGHT, logic->CanBreakLowerBeehives()),
	LOCATION(RC_HF_NEAR_MARKET_GROTTO_GRASS_1, logic->CanCutShrubs()),
	LOCATION(RC_HF_NEAR_MARKET_GROTTO_GRASS_2, logic->CanCutShrubs()),
	LOCATION(RC_HF_NEAR_MARKET_GROTTO_GRASS_3, logic->CanCutShrubs()),
	LOCATION(RC_HF_NEAR_MARKET_GROTTO_GRASS_4, logic->CanCutShrubs()),
}, {
	Entrance(RR_HYRULE_FIELD, []{return true;}),
});
areaTable[RR_HF_FAIRY_GROTTO] = Region("HF Fairy Grotto", SCENE_GROTTOS, false, {}, {
	EventAccess(&logic->FreeFairies, []{return true;}),
}, {
	LOCATION(RC_HF_FAIRY_GROTTO_FAIRY_1, true),
	LOCATION(RC_HF_FAIRY_GROTTO_FAIRY_2, true),
	LOCATION(RC_HF_FAIRY_GROTTO_FAIRY_3, true),
	LOCATION(RC_HF_FAIRY_GROTTO_FAIRY_4, true),
	LOCATION(RC_HF_FAIRY_GROTTO_FAIRY_5, true),
	LOCATION(RC_HF_FAIRY_GROTTO_FAIRY_6, true),
	LOCATION(RC_HF_FAIRY_GROTTO_FAIRY_7, true),
	LOCATION(RC_HF_FAIRY_GROTTO_FAIRY_8, true),
}, {
	Entrance(RR_HYRULE_FIELD, []{return true;}),
});
areaTable[RR_HF_NEAR_KAK_GROTTO] = Region("HF Near Kak Grotto", SCENE_GROTTOS, false, {}, {}, {
	LOCATION(RC_HF_GS_NEAR_KAK_GROTTO, logic->HookshotOrBoomerang()),
}, {
	Entrance(RR_HYRULE_FIELD, []{return true;}),
});
areaTable[RR_HF_TEKTITE_GROTTO] = Region("HF Tektite Grotto", SCENE_GROTTOS, false, {}, {}, {
	LOCATION(RC_HF_TEKTITE_GROTTO_FREESTANDING_POH, (logic->HasItem(RG_GOLDEN_SCALE) || logic->CanUse(RG_IRON_BOOTS))),
}, {
	Entrance(RR_HYRULE_FIELD, []{return true;}),
});
areaTable[RR_LAKE_HYLIA] = Region("Lake Hylia", SCENE_LAKE_HYLIA, true, {RA_LAKE_HYLIA}, {
	EventAccess(&logic->GossipStoneFairy, []{return logic->CallGossipFairy();}),
	EventAccess(&logic->BeanPlantFairy, []{return (logic->IsChild && (logic->CanUse(RG_MAGIC_BEAN) && logic->CanUse(RG_SONG_OF_STORMS)));}),
	EventAccess(&logic->ButterflyFairy, []{return logic->CanUse(RG_STICKS);}),
	EventAccess(&logic->BugShrub, []{return (logic->IsChild && logic->CanCutShrubs());}),
	EventAccess(&logic->ChildScarecrow, []{return (logic->IsChild && (logic->HasItem(RG_FAIRY_OCARINA) && (logic->OcarinaButtons() >= 2)));}),
	EventAccess(&logic->AdultScarecrow, []{return (logic->IsAdult && (logic->HasItem(RG_FAIRY_OCARINA) && (logic->OcarinaButtons() >= 2)));}),
}, {
	LOCATION(RC_LH_UNDERWATER_ITEM, (logic->IsChild && logic->HasItem(RG_SILVER_SCALE))),
	LOCATION(RC_LH_SUN, (logic->IsAdult && (((logic->WaterTempleClear && logic->HasItem(RG_BRONZE_SCALE)) || logic->CanUse(RG_DISTANT_SCARECROW)) && logic->CanUse(RG_FAIRY_BOW)))),
	LOCATION(RC_LH_FREESTANDING_POH, (logic->IsAdult && (logic->CanUse(RG_SCARECROW) || CanPlantBean(RR_LAKE_HYLIA)))),
	LOCATION(RC_LH_GS_BEAN_PATCH, (logic->CanSpawnSoilSkull() && logic->CanGetEnemyDrop(RE_GOLD_SKULLTULA))),
	LOCATION(RC_LH_GS_LAB_WALL, (logic->IsChild && ((logic->CanGetEnemyDrop(RE_GOLD_SKULLTULA, ED_BOOMERANG) || ((bool)ctx->GetTrickOption(RT_LH_LAB_WALL_GS) && logic->CanJumpslashExceptHammer())) && logic->CanGetNightTimeGS()))),
	LOCATION(RC_LH_GS_SMALL_ISLAND, (logic->IsChild && (logic->CanGetEnemyDrop(RE_GOLD_SKULLTULA) && (logic->CanGetNightTimeGS() && logic->HasItem(RG_BRONZE_SCALE))))),
	LOCATION(RC_LH_GS_TREE, (logic->IsAdult && (logic->CanUse(RG_LONGSHOT) && logic->CanGetNightTimeGS()))),
	LOCATION(RC_LH_FRONT_RUPEE, (logic->IsChild && logic->HasItem(RG_BRONZE_SCALE))),
	LOCATION(RC_LH_MIDDLE_RUPEE, (logic->IsChild && (logic->HasItem(RG_SILVER_SCALE) || logic->CanUse(RG_IRON_BOOTS)))),
	LOCATION(RC_LH_BACK_RUPEE, (logic->IsChild && (logic->HasItem(RG_SILVER_SCALE) || logic->CanUse(RG_IRON_BOOTS)))),
	LOCATION(RC_LH_BEAN_SPROUT_FAIRY_1, (logic->IsChild && (logic->CanUse(RG_MAGIC_BEAN) && logic->CanUse(RG_SONG_OF_STORMS)))),
	LOCATION(RC_LH_BEAN_SPROUT_FAIRY_2, (logic->IsChild && (logic->CanUse(RG_MAGIC_BEAN) && logic->CanUse(RG_SONG_OF_STORMS)))),
	LOCATION(RC_LH_BEAN_SPROUT_FAIRY_3, (logic->IsChild && (logic->CanUse(RG_MAGIC_BEAN) && logic->CanUse(RG_SONG_OF_STORMS)))),
	LOCATION(RC_LH_LAB_GOSSIP_STONE_FAIRY, logic->CallGossipFairy()),
	LOCATION(RC_LH_LAB_GOSSIP_STONE_FAIRY_BIG, logic->CanUse(RG_SONG_OF_STORMS)),
	LOCATION(RC_LH_SOUTHEAST_GOSSIP_STONE_FAIRY, logic->CallGossipFairy()),
	LOCATION(RC_LH_SOUTHEAST_GOSSIP_STONE_FAIRY_BIG, logic->CanUse(RG_SONG_OF_STORMS)),
	LOCATION(RC_LH_SOUTHWEST_GOSSIP_STONE_FAIRY, logic->CallGossipFairy()),
	LOCATION(RC_LH_SOUTHWEST_GOSSIP_STONE_FAIRY_BIG, logic->CanUse(RG_SONG_OF_STORMS)),
	LOCATION(RC_LH_ISLAND_SUN_FAIRY, (logic->CanUse(RG_SUNS_SONG) && ((logic->HasItem(RG_BRONZE_SCALE) && (logic->IsChild || logic->WaterTempleClear)) || logic->CanUse(RG_DISTANT_SCARECROW)))),
	LOCATION(RC_LH_LAB_GOSSIP_STONE, true),
	LOCATION(RC_LH_SOUTHEAST_GOSSIP_STONE, true),
	LOCATION(RC_LH_SOUTHWEST_GOSSIP_STONE, true),
	LOCATION(RC_LH_GRASS_1, logic->CanCutShrubs()),
	LOCATION(RC_LH_GRASS_2, logic->CanCutShrubs()),
	LOCATION(RC_LH_GRASS_3, logic->CanCutShrubs()),
	LOCATION(RC_LH_GRASS_4, logic->CanCutShrubs()),
	LOCATION(RC_LH_GRASS_5, logic->CanCutShrubs()),
	LOCATION(RC_LH_GRASS_6, logic->CanCutShrubs()),
	LOCATION(RC_LH_GRASS_7, logic->CanCutShrubs()),
	LOCATION(RC_LH_GRASS_8, logic->CanCutShrubs()),
	LOCATION(RC_LH_GRASS_9, logic->CanCutShrubs()),
	LOCATION(RC_LH_GRASS_10, logic->CanCutShrubs()),
	LOCATION(RC_LH_GRASS_11, logic->CanCutShrubs()),
	LOCATION(RC_LH_GRASS_12, logic->CanCutShrubs()),
	LOCATION(RC_LH_GRASS_13, logic->CanCutShrubs()),
	LOCATION(RC_LH_GRASS_14, logic->CanCutShrubs()),
	LOCATION(RC_LH_GRASS_15, logic->CanCutShrubs()),
	LOCATION(RC_LH_GRASS_16, logic->CanCutShrubs()),
	LOCATION(RC_LH_GRASS_17, logic->CanCutShrubs()),
	LOCATION(RC_LH_GRASS_18, logic->CanCutShrubs()),
	LOCATION(RC_LH_GRASS_19, logic->CanCutShrubs()),
	LOCATION(RC_LH_GRASS_20, logic->CanCutShrubs()),
	LOCATION(RC_LH_GRASS_21, logic->CanCutShrubs()),
	LOCATION(RC_LH_GRASS_22, logic->CanCutShrubs()),
	LOCATION(RC_LH_GRASS_23, logic->CanCutShrubs()),
	LOCATION(RC_LH_GRASS_24, logic->CanCutShrubs()),
	LOCATION(RC_LH_GRASS_25, logic->CanCutShrubs()),
	LOCATION(RC_LH_GRASS_26, logic->CanCutShrubs()),
	LOCATION(RC_LH_GRASS_27, logic->CanCutShrubs()),
	LOCATION(RC_LH_GRASS_28, logic->CanCutShrubs()),
	LOCATION(RC_LH_GRASS_29, logic->CanCutShrubs()),
	LOCATION(RC_LH_GRASS_30, logic->CanCutShrubs()),
	LOCATION(RC_LH_GRASS_31, logic->CanCutShrubs()),
	LOCATION(RC_LH_GRASS_32, logic->CanCutShrubs()),
	LOCATION(RC_LH_GRASS_33, logic->CanCutShrubs()),
	LOCATION(RC_LH_GRASS_34, logic->CanCutShrubs()),
	LOCATION(RC_LH_GRASS_35, logic->CanCutShrubs()),
	LOCATION(RC_LH_GRASS_36, logic->CanCutShrubs()),
	LOCATION(RC_LH_CHILD_GRASS_1, (logic->IsChild && logic->CanCutShrubs())),
	LOCATION(RC_LH_CHILD_GRASS_2, (logic->IsChild && logic->CanCutShrubs())),
	LOCATION(RC_LH_CHILD_GRASS_3, (logic->IsChild && logic->CanCutShrubs())),
	LOCATION(RC_LH_CHILD_GRASS_4, (logic->IsChild && logic->CanCutShrubs())),
	LOCATION(RC_LH_WARP_PAD_GRASS_1, logic->CanCutShrubs()),
	LOCATION(RC_LH_WARP_PAD_GRASS_2, logic->CanCutShrubs()),
}, {
	Entrance(RR_HYRULE_FIELD, []{return true;}),
	Entrance(RR_LH_FROM_SHORTCUT, []{return true;}),
	Entrance(RR_LH_OWL_FLIGHT, []{return logic->IsChild;}, "", false),
	Entrance(RR_LH_FISHING_ISLAND, []{return (((logic->IsChild || logic->WaterTempleClear) && logic->HasItem(RG_BRONZE_SCALE)) || (logic->IsAdult && (logic->CanUse(RG_SCARECROW) || CanPlantBean(RR_LAKE_HYLIA))));}),
	Entrance(RR_LH_LAB, []{return logic->CanOpenOverworldDoor(RG_HYLIA_LAB_KEY);}),
	Entrance(RR_LH_FROM_WATER_TEMPLE, []{return true;}),
	Entrance(RR_LH_GROTTO, []{return true;}),
});
areaTable[RR_LH_FROM_SHORTCUT] = Region("LH From Shortcut", SCENE_LAKE_HYLIA, false, {RA_LAKE_HYLIA}, {}, {}, {
	Entrance(RR_LAKE_HYLIA, []{return ((logic->Hearts() > 1) || (logic->HasItem(RG_BOTTLE_WITH_FAIRY) || (logic->HasItem(RG_BRONZE_SCALE) || logic->CanUse(RG_IRON_BOOTS))));}),
	Entrance(RR_ZORAS_DOMAIN, []{return (logic->IsChild && (logic->HasItem(RG_SILVER_SCALE) || logic->CanUse(RG_IRON_BOOTS)));}),
});
areaTable[RR_LH_FROM_WATER_TEMPLE] = Region("LH From Water Temple", SCENE_LAKE_HYLIA, false, {RA_LAKE_HYLIA}, {}, {}, {
	Entrance(RR_LAKE_HYLIA, []{return (logic->HasItem(RG_BRONZE_SCALE) || (logic->HasItem(RG_BOTTLE_WITH_FAIRY) || logic->CanUse(RG_IRON_BOOTS)));}),
	Entrance(RR_WATER_TEMPLE_ENTRYWAY, []{return (logic->CanUse(RG_HOOKSHOT) && ((logic->CanUse(RG_IRON_BOOTS) || ((bool)ctx->GetTrickOption(RT_LH_WATER_HOOKSHOT) && logic->HasItem(RG_GOLDEN_SCALE))) || (logic->IsAdult && (logic->CanUse(RG_LONGSHOT) && logic->HasItem(RG_GOLDEN_SCALE)))));}),
});
areaTable[RR_LH_FISHING_ISLAND] = Region("LH Fishing Island", SCENE_LAKE_HYLIA, true, {RA_LAKE_HYLIA}, {}, {}, {
	Entrance(RR_LAKE_HYLIA, []{return logic->HasItem(RG_BRONZE_SCALE);}),
	Entrance(RR_LH_FISHING_POND, []{return logic->CanOpenOverworldDoor(RG_FISHING_HOLE_KEY);}),
});
areaTable[RR_LH_OWL_FLIGHT] = Region("LH Owl Flight", SCENE_LAKE_HYLIA, true, {RA_LAKE_HYLIA}, {}, {}, {
	Entrance(RR_HYRULE_FIELD, []{return true;}, "", false),
});
areaTable[RR_LH_LAB] = Region("LH Lab", SCENE_LAKESIDE_LABORATORY, false, {}, {}, {
	LOCATION(RC_LH_LAB_DIVE, (logic->HasItem(RG_GOLDEN_SCALE) || ((bool)ctx->GetTrickOption(RT_LH_LAB_DIVING) && (logic->CanUse(RG_IRON_BOOTS) && (logic->CanUse(RG_HOOKSHOT) && logic->HasItem(RG_BRONZE_SCALE)))))),
	LOCATION(RC_LH_TRADE_FROG, (logic->IsAdult && logic->CanUse(RG_EYEBALL_FROG))),
	LOCATION(RC_LH_GS_LAB_CRATE, (logic->CanUse(RG_IRON_BOOTS) && (logic->CanUse(RG_HOOKSHOT) && logic->CanBreakCrates()))),
	LOCATION(RC_LH_LAB_FRONT_RUPEE, (logic->CanUse(RG_IRON_BOOTS) || logic->HasItem(RG_GOLDEN_SCALE))),
	LOCATION(RC_LH_LAB_LEFT_RUPEE, (logic->CanUse(RG_IRON_BOOTS) || logic->HasItem(RG_GOLDEN_SCALE))),
	LOCATION(RC_LH_LAB_RIGHT_RUPEE, (logic->CanUse(RG_IRON_BOOTS) || logic->HasItem(RG_GOLDEN_SCALE))),
	LOCATION(RC_LH_LAB_CRATE, (logic->CanUse(RG_IRON_BOOTS) && logic->CanBreakCrates())),
}, {
	Entrance(RR_LAKE_HYLIA, []{return true;}),
});
areaTable[RR_LH_FISHING_POND] = Region("LH Fishing Hole", SCENE_FISHING_POND, false, {}, {}, {
	LOCATION(RC_LH_CHILD_FISHING, (logic->CanUse(RG_FISHING_POLE) && logic->IsChild)),
	LOCATION(RC_LH_CHILD_FISH_1, (logic->CanUse(RG_FISHING_POLE) && (logic->IsChild || !ctx->GetOption(RSK_FISHSANITY_AGE_SPLIT)))),
	LOCATION(RC_LH_CHILD_FISH_2, (logic->CanUse(RG_FISHING_POLE) && (logic->IsChild || !ctx->GetOption(RSK_FISHSANITY_AGE_SPLIT)))),
	LOCATION(RC_LH_CHILD_FISH_3, (logic->CanUse(RG_FISHING_POLE) && (logic->IsChild || !ctx->GetOption(RSK_FISHSANITY_AGE_SPLIT)))),
	LOCATION(RC_LH_CHILD_FISH_4, (logic->CanUse(RG_FISHING_POLE) && (logic->IsChild || !ctx->GetOption(RSK_FISHSANITY_AGE_SPLIT)))),
	LOCATION(RC_LH_CHILD_FISH_5, (logic->CanUse(RG_FISHING_POLE) && (logic->IsChild || !ctx->GetOption(RSK_FISHSANITY_AGE_SPLIT)))),
	LOCATION(RC_LH_CHILD_FISH_6, (logic->CanUse(RG_FISHING_POLE) && (logic->IsChild || !ctx->GetOption(RSK_FISHSANITY_AGE_SPLIT)))),
	LOCATION(RC_LH_CHILD_FISH_7, (logic->CanUse(RG_FISHING_POLE) && (logic->IsChild || !ctx->GetOption(RSK_FISHSANITY_AGE_SPLIT)))),
	LOCATION(RC_LH_CHILD_FISH_8, (logic->CanUse(RG_FISHING_POLE) && (logic->IsChild || !ctx->GetOption(RSK_FISHSANITY_AGE_SPLIT)))),
	LOCATION(RC_LH_CHILD_FISH_9, (logic->CanUse(RG_FISHING_POLE) && (logic->IsChild || !ctx->GetOption(RSK_FISHSANITY_AGE_SPLIT)))),
	LOCATION(RC_LH_CHILD_FISH_10, (logic->CanUse(RG_FISHING_POLE) && (logic->IsChild || !ctx->GetOption(RSK_FISHSANITY_AGE_SPLIT)))),
	LOCATION(RC_LH_CHILD_FISH_11, (logic->CanUse(RG_FISHING_POLE) && (logic->IsChild || !ctx->GetOption(RSK_FISHSANITY_AGE_SPLIT)))),
	LOCATION(RC_LH_CHILD_FISH_12, (logic->CanUse(RG_FISHING_POLE) && (logic->IsChild || !ctx->GetOption(RSK_FISHSANITY_AGE_SPLIT)))),
	LOCATION(RC_LH_CHILD_FISH_13, (logic->CanUse(RG_FISHING_POLE) && (logic->IsChild || !ctx->GetOption(RSK_FISHSANITY_AGE_SPLIT)))),
	LOCATION(RC_LH_CHILD_FISH_14, (logic->CanUse(RG_FISHING_POLE) && (logic->IsChild || !ctx->GetOption(RSK_FISHSANITY_AGE_SPLIT)))),
	LOCATION(RC_LH_CHILD_FISH_15, (logic->CanUse(RG_FISHING_POLE) && (logic->IsChild || !ctx->GetOption(RSK_FISHSANITY_AGE_SPLIT)))),
	LOCATION(RC_LH_CHILD_LOACH_1, (logic->CanUse(RG_FISHING_POLE) && (logic->IsChild || !ctx->GetOption(RSK_FISHSANITY_AGE_SPLIT)))),
	LOCATION(RC_LH_CHILD_LOACH_2, (logic->CanUse(RG_FISHING_POLE) && (logic->IsChild || !ctx->GetOption(RSK_FISHSANITY_AGE_SPLIT)))),
	LOCATION(RC_LH_ADULT_FISHING, (logic->CanUse(RG_FISHING_POLE) && logic->IsAdult)),
	LOCATION(RC_LH_ADULT_FISH_1, (logic->CanUse(RG_FISHING_POLE) && (logic->IsAdult && ctx->GetOption(RSK_FISHSANITY_AGE_SPLIT)))),
	LOCATION(RC_LH_ADULT_FISH_2, (logic->CanUse(RG_FISHING_POLE) && (logic->IsAdult && ctx->GetOption(RSK_FISHSANITY_AGE_SPLIT)))),
	LOCATION(RC_LH_ADULT_FISH_3, (logic->CanUse(RG_FISHING_POLE) && (logic->IsAdult && ctx->GetOption(RSK_FISHSANITY_AGE_SPLIT)))),
	LOCATION(RC_LH_ADULT_FISH_4, (logic->CanUse(RG_FISHING_POLE) && (logic->IsAdult && ctx->GetOption(RSK_FISHSANITY_AGE_SPLIT)))),
	LOCATION(RC_LH_ADULT_FISH_5, (logic->CanUse(RG_FISHING_POLE) && (logic->IsAdult && ctx->GetOption(RSK_FISHSANITY_AGE_SPLIT)))),
	LOCATION(RC_LH_ADULT_FISH_6, (logic->CanUse(RG_FISHING_POLE) && (logic->IsAdult && ctx->GetOption(RSK_FISHSANITY_AGE_SPLIT)))),
	LOCATION(RC_LH_ADULT_FISH_7, (logic->CanUse(RG_FISHING_POLE) && (logic->IsAdult && ctx->GetOption(RSK_FISHSANITY_AGE_SPLIT)))),
	LOCATION(RC_LH_ADULT_FISH_8, (logic->CanUse(RG_FISHING_POLE) && (logic->IsAdult && ctx->GetOption(RSK_FISHSANITY_AGE_SPLIT)))),
	LOCATION(RC_LH_ADULT_FISH_9, (logic->CanUse(RG_FISHING_POLE) && (logic->IsAdult && ctx->GetOption(RSK_FISHSANITY_AGE_SPLIT)))),
	LOCATION(RC_LH_ADULT_FISH_10, (logic->CanUse(RG_FISHING_POLE) && (logic->IsAdult && ctx->GetOption(RSK_FISHSANITY_AGE_SPLIT)))),
	LOCATION(RC_LH_ADULT_FISH_11, (logic->CanUse(RG_FISHING_POLE) && (logic->IsAdult && ctx->GetOption(RSK_FISHSANITY_AGE_SPLIT)))),
	LOCATION(RC_LH_ADULT_FISH_12, (logic->CanUse(RG_FISHING_POLE) && (logic->IsAdult && ctx->GetOption(RSK_FISHSANITY_AGE_SPLIT)))),
	LOCATION(RC_LH_ADULT_FISH_13, (logic->CanUse(RG_FISHING_POLE) && (logic->IsAdult && ctx->GetOption(RSK_FISHSANITY_AGE_SPLIT)))),
	LOCATION(RC_LH_ADULT_FISH_14, (logic->CanUse(RG_FISHING_POLE) && (logic->IsAdult && ctx->GetOption(RSK_FISHSANITY_AGE_SPLIT)))),
	LOCATION(RC_LH_ADULT_FISH_15, (logic->CanUse(RG_FISHING_POLE) && (logic->IsAdult && ctx->GetOption(RSK_FISHSANITY_AGE_SPLIT)))),
	LOCATION(RC_LH_ADULT_LOACH, (logic->CanUse(RG_FISHING_POLE) && (logic->IsAdult && ctx->GetOption(RSK_FISHSANITY_AGE_SPLIT)))),
	LOCATION(RC_LH_HYRULE_LOACH, logic->CanUse(RG_FISHING_POLE)),
	LOCATION(RC_FISHING_POLE_HINT, true),
}, {
	Entrance(RR_LH_FISHING_ISLAND, []{return true;}),
});
areaTable[RR_LH_GROTTO] = Region("LH Grotto", SCENE_GROTTOS, false, {}, {}, {
	LOCATION(RC_LH_DEKU_SCRUB_GROTTO_LEFT, logic->CanStunDeku()),
	LOCATION(RC_LH_DEKU_SCRUB_GROTTO_RIGHT, logic->CanStunDeku()),
	LOCATION(RC_LH_DEKU_SCRUB_GROTTO_CENTER, logic->CanStunDeku()),
	LOCATION(RC_LH_GROTTO_BEEHIVE, logic->CanBreakUpperBeehives()),
}, {
	Entrance(RR_LAKE_HYLIA, []{return true;}),
});
areaTable[RR_GERUDO_VALLEY] = Region("Gerudo Valley", SCENE_GERUDO_VALLEY, true, {RA_GERUDO_VALLEY}, {
	EventAccess(&logic->BugRock, []{return logic->IsChild;}),
}, {
	LOCATION(RC_GV_GS_SMALL_BRIDGE, (logic->IsChild && (logic->HookshotOrBoomerang() && logic->CanGetNightTimeGS()))),
}, {
	Entrance(RR_HYRULE_FIELD, []{return true;}),
	Entrance(RR_GV_UPPER_STREAM, []{return (logic->IsChild || (logic->HasItem(RG_BRONZE_SCALE) || logic->TakeDamage()));}),
	Entrance(RR_GV_CRATE_LEDGE, []{return (logic->IsChild || logic->CanUse(RG_LONGSHOT));}),
	Entrance(RR_GV_GROTTO_LEDGE, []{return true;}),
	Entrance(RR_GV_FORTRESS_SIDE, []{return ((logic->IsAdult && (logic->CanUse(RG_EPONA) || (logic->CanUse(RG_LONGSHOT) || (ctx->GetOption(RSK_GERUDO_FORTRESS).Is(RO_GF_CARPENTERS_FREE) || logic->THRescuedAllCarpenters)))) || (logic->IsChild && logic->CanUse(RG_HOOKSHOT)));}),
	Entrance(RR_GV_LOWER_STREAM, []{return logic->IsChild;}),
});
areaTable[RR_GV_UPPER_STREAM] = Region("GV Upper Stream", SCENE_GERUDO_VALLEY, true, {RA_GERUDO_VALLEY}, {
	EventAccess(&logic->GossipStoneFairy, []{return logic->CallGossipFairy();}),
	EventAccess(&logic->BeanPlantFairy, []{return (logic->IsChild && (logic->CanUse(RG_MAGIC_BEAN) && logic->CanUse(RG_SONG_OF_STORMS)));}),
}, {
	LOCATION(RC_GV_WATERFALL_FREESTANDING_POH, (logic->IsChild || logic->HasItem(RG_BRONZE_SCALE))),
	LOCATION(RC_GV_GS_BEAN_PATCH, (logic->CanSpawnSoilSkull() && logic->CanAttack())),
	LOCATION(RC_GV_COW, (logic->IsChild && logic->CanUse(RG_EPONAS_SONG))),
	LOCATION(RC_GV_BEAN_SPROUT_FAIRY_1, (logic->IsChild && (logic->CanUse(RG_MAGIC_BEAN) && logic->CanUse(RG_SONG_OF_STORMS)))),
	LOCATION(RC_GV_BEAN_SPROUT_FAIRY_2, (logic->IsChild && (logic->CanUse(RG_MAGIC_BEAN) && logic->CanUse(RG_SONG_OF_STORMS)))),
	LOCATION(RC_GV_BEAN_SPROUT_FAIRY_3, (logic->IsChild && (logic->CanUse(RG_MAGIC_BEAN) && logic->CanUse(RG_SONG_OF_STORMS)))),
	LOCATION(RC_GV_GOSSIP_STONE_FAIRY, logic->CallGossipFairy()),
	LOCATION(RC_GV_GOSSIP_STONE_FAIRY_BIG, logic->CanUse(RG_SONG_OF_STORMS)),
	LOCATION(RC_GV_GOSSIP_STONE, true),
	LOCATION(RC_GV_NEAR_COW_CRATE, (logic->IsChild && logic->CanBreakCrates())),
}, {
	Entrance(RR_GV_LOWER_STREAM, []{return (logic->HasItem(RG_BRONZE_SCALE) || logic->CanUse(RG_IRON_BOOTS));}),
});
areaTable[RR_GV_LOWER_STREAM] = Region("GV Lower Stream", SCENE_GERUDO_VALLEY, true, {RA_GERUDO_VALLEY}, {}, {}, {
	Entrance(RR_LAKE_HYLIA, []{return true;}),
});
areaTable[RR_GV_GROTTO_LEDGE] = Region("GV Grotto Ledge", SCENE_GERUDO_VALLEY, true, {RA_GERUDO_VALLEY}, {}, {}, {
	Entrance(RR_GV_UPPER_STREAM, []{return ((bool)ctx->GetTrickOption(RT_DAMAGE_BOOST_SIMPLE) && logic->HasExplosives());}),
	Entrance(RR_GV_LOWER_STREAM, []{return (logic->HasItem(RG_BRONZE_SCALE) || logic->CanUse(RG_IRON_BOOTS));}),
	Entrance(RR_GV_OCTOROK_GROTTO, []{return logic->CanUse(RG_SILVER_GAUNTLETS);}),
	Entrance(RR_GV_CRATE_LEDGE, []{return logic->CanUse(RG_LONGSHOT);}),
});
areaTable[RR_GV_CRATE_LEDGE] = Region("GV Crate Ledge", SCENE_GERUDO_VALLEY, true, {RA_GERUDO_VALLEY}, {}, {
	LOCATION(RC_GV_CRATE_FREESTANDING_POH, logic->CanBreakCrates()),
	LOCATION(RC_GV_FREESTANDING_POH_CRATE, logic->CanBreakCrates()),
}, {
	Entrance(RR_GV_UPPER_STREAM, []{return ((bool)ctx->GetTrickOption(RT_DAMAGE_BOOST_SIMPLE) && logic->HasExplosives());}),
	Entrance(RR_GV_LOWER_STREAM, []{return (logic->HasItem(RG_BRONZE_SCALE) || logic->CanUse(RG_IRON_BOOTS));}),
});
areaTable[RR_GV_OCTOROK_GROTTO] = Region("GV Octorok Grotto", SCENE_GROTTOS, false, {}, {}, {
	LOCATION(RC_GV_OCTOROK_GROTTO_FRONT_LEFT_BLUE_RUPEE, (logic->HasItem(RG_BRONZE_SCALE) || (logic->CanUse(RG_IRON_BOOTS) || logic->CanUse(RG_BOOMERANG)))),
	LOCATION(RC_GV_OCTOROK_GROTTO_FRONT_RIGHT_BLUE_RUPEE, (logic->HasItem(RG_BRONZE_SCALE) || (logic->CanUse(RG_IRON_BOOTS) || logic->CanUse(RG_BOOMERANG)))),
	LOCATION(RC_GV_OCTOROK_GROTTO_BACK_BLUE_RUPEE, (logic->HasItem(RG_BRONZE_SCALE) || (logic->CanUse(RG_IRON_BOOTS) || logic->CanUse(RG_BOOMERANG)))),
	LOCATION(RC_GV_OCTOROK_GROTTO_FRONT_LEFT_GREEN_RUPEE, (logic->HasItem(RG_BRONZE_SCALE) || (logic->CanUse(RG_IRON_BOOTS) || logic->CanUse(RG_BOOMERANG)))),
	LOCATION(RC_GV_OCTOROK_GROTTO_FRONT_RIGHT_GREEN_RUPEE, (logic->HasItem(RG_BRONZE_SCALE) || (logic->CanUse(RG_IRON_BOOTS) || logic->CanUse(RG_BOOMERANG)))),
	LOCATION(RC_GV_OCTOROK_GROTTO_BACK_LEFT_GREEN_RUPEE, (logic->HasItem(RG_BRONZE_SCALE) || (logic->CanUse(RG_IRON_BOOTS) || logic->CanUse(RG_BOOMERANG)))),
	LOCATION(RC_GV_OCTOROK_GROTTO_BACK_RIGHT_GREEN_RUPEE, (logic->HasItem(RG_BRONZE_SCALE) || (logic->CanUse(RG_IRON_BOOTS) || logic->CanUse(RG_BOOMERANG)))),
	LOCATION(RC_GV_OCTOROK_GROTTO_RED_RUPEE, (logic->HasItem(RG_BRONZE_SCALE) || (logic->CanUse(RG_IRON_BOOTS) || logic->CanUse(RG_BOOMERANG)))),
}, {
	Entrance(RR_GV_GROTTO_LEDGE, []{return true;}),
});
areaTable[RR_GV_FORTRESS_SIDE] = Region("GV Fortress Side", SCENE_GERUDO_VALLEY, true, {RA_GERUDO_VALLEY}, {}, {
	LOCATION(RC_GV_CHEST, (logic->IsAdult && logic->CanUse(RG_MEGATON_HAMMER))),
	LOCATION(RC_GV_TRADE_SAW, (logic->IsAdult && logic->CanUse(RG_POACHERS_SAW))),
	LOCATION(RC_GV_GS_BEHIND_TENT, (logic->IsAdult && (logic->HookshotOrBoomerang() && logic->CanGetNightTimeGS()))),
	LOCATION(RC_GV_GS_PILLAR, (logic->IsAdult && (logic->HookshotOrBoomerang() && logic->CanGetNightTimeGS()))),
	LOCATION(RC_GV_CRATE_BRIDGE_1, (logic->IsChild && logic->CanBreakCrates())),
	LOCATION(RC_GV_CRATE_BRIDGE_2, (logic->IsChild && logic->CanBreakCrates())),
	LOCATION(RC_GV_CRATE_BRIDGE_3, (logic->IsChild && logic->CanBreakCrates())),
	LOCATION(RC_GV_CRATE_BRIDGE_4, (logic->IsChild && logic->CanBreakCrates())),
}, {
	Entrance(RR_GF_OUTSKIRTS, []{return true;}),
	Entrance(RR_GV_UPPER_STREAM, []{return true;}),
	Entrance(RR_GERUDO_VALLEY, []{return (logic->IsChild || (logic->CanUse(RG_EPONA) || (logic->CanUse(RG_LONGSHOT) || (ctx->GetOption(RSK_GERUDO_FORTRESS).Is(RO_GF_CARPENTERS_FREE) || logic->THRescuedAllCarpenters))));}),
	Entrance(RR_GV_CARPENTER_TENT, []{return logic->IsAdult;}),
	Entrance(RR_GV_STORMS_GROTTO, []{return (logic->IsAdult && logic->CanOpenStormsGrotto());}),
	Entrance(RR_GV_CRATE_LEDGE, []{return ((bool)ctx->GetTrickOption(RT_DAMAGE_BOOST_SIMPLE) && logic->HasExplosives());}),
});
areaTable[RR_GV_CARPENTER_TENT] = Region("GV Carpenter Tent", SCENE_CARPENTERS_TENT, false, {}, {}, {}, {
	Entrance(RR_GV_FORTRESS_SIDE, []{return true;}),
});
areaTable[RR_GV_STORMS_GROTTO] = Region("GV Storms Grotto", SCENE_GROTTOS, false, {}, {}, {
	LOCATION(RC_GV_DEKU_SCRUB_GROTTO_REAR, logic->CanStunDeku()),
	LOCATION(RC_GV_DEKU_SCRUB_GROTTO_FRONT, logic->CanStunDeku()),
	LOCATION(RC_GV_DEKU_SCRUB_GROTTO_BEEHIVE, logic->CanBreakUpperBeehives()),
}, {
	Entrance(RR_GV_FORTRESS_SIDE, []{return true;}),
});
areaTable[RR_GF_OUTSKIRTS] = Region("Gerudo Fortress Outskirts", SCENE_GERUDOS_FORTRESS, false, {RA_GERUDO_FORTRESS}, {
	EventAccess(&logic->GF_GateOpen, []{return (logic->IsAdult && logic->HasItem(RG_GERUDO_MEMBERSHIP_CARD));}),
}, {
	LOCATION(RC_GF_OUTSKIRTS_NE_CRATE, ((logic->IsChild || logic->CanPassEnemy(RE_GERUDO_GUARD)) && logic->CanBreakCrates())),
	LOCATION(RC_GF_OUTSKIRTS_NW_CRATE, (logic->IsChild || logic->CanPassEnemy(RE_GERUDO_GUARD))),
}, {
	Entrance(RR_GV_FORTRESS_SIDE, []{return true;}),
	Entrance(RR_TH_1_TORCH_CELL, []{return true;}),
	Entrance(RR_GF_OUTSIDE_GATE, []{return logic->GF_GateOpen;}),
	Entrance(RR_GF_NEAR_GROTTO, []{return (logic->IsChild || logic->CanPassEnemy(RE_GERUDO_GUARD));}),
	Entrance(RR_GF_OUTSIDE_GTG, []{return (logic->IsChild || logic->CanPassEnemy(RE_GERUDO_GUARD));}),
	Entrance(RR_GF_JAIL_WINDOW, []{return logic->CanUse(RG_HOOKSHOT);}),
});
areaTable[RR_GF_NEAR_GROTTO] = Region("GF Near Grotto", SCENE_GERUDOS_FORTRESS, false, {RA_GERUDO_FORTRESS}, {}, {
	LOCATION(RC_GF_SOUTHMOST_CENTER_CRATE, logic->CanBreakCrates()),
	LOCATION(RC_GF_MID_SOUTH_CENTER_CRATE, logic->CanBreakCrates()),
	LOCATION(RC_GF_MID_NORTH_CENTER_CRATE, logic->CanBreakCrates()),
	LOCATION(RC_GF_NORTHMOST_CENTER_CRATE, logic->CanBreakCrates()),
}, {
	Entrance(RR_TH_1_TORCH_CELL, []{return true;}),
	Entrance(RR_TH_STEEP_SLOPE_CELL, []{return true;}),
	Entrance(RR_TH_KITCHEN_CORRIDOR, []{return true;}),
	Entrance(RR_GF_OUTSKIRTS, []{return true;}),
	Entrance(RR_GF_JAIL_WINDOW, []{return logic->CanUse(RG_HOOKSHOT);}),
	Entrance(RR_GF_OUTSIDE_GTG, []{return (logic->IsChild || logic->CanPassEnemy(RE_GERUDO_GUARD));}),
	Entrance(RR_GF_TOP_OF_UPPER_VINES, []{return logic->CanUse(RG_LONGSHOT);}),
	Entrance(RR_GF_STORMS_GROTTO, []{return (logic->IsAdult && logic->CanOpenStormsGrotto());}),
});
areaTable[RR_GF_OUTSIDE_GTG] = Region("GF Outside GTG", SCENE_GERUDOS_FORTRESS, false, {RA_GERUDO_FORTRESS}, {
	EventAccess(&logic->GtG_GateOpen, []{return (logic->IsAdult && (logic->HasItem(RG_GERUDO_MEMBERSHIP_CARD) && logic->HasItem(RG_CHILD_WALLET)));}),
}, {}, {
	Entrance(RR_GF_TO_GTG, []{return (logic->GtG_GateOpen && (logic->IsAdult || ctx->GetOption(RSK_SHUFFLE_DUNGEON_ENTRANCES)));}),
	Entrance(RR_GF_JAIL_WINDOW, []{return logic->CanUse(RG_HOOKSHOT);}),
	Entrance(RR_GF_OUTSKIRTS, []{return true;}),
	Entrance(RR_GF_NEAR_GROTTO, []{return (logic->IsChild || logic->CanPassEnemy(RE_GERUDO_GUARD));}),
	Entrance(RR_GF_ABOVE_GTG, []{return (logic->IsChild || logic->CanPassEnemy(RE_GERUDO_GUARD));}),
	Entrance(RR_GF_TOP_OF_UPPER_VINES, []{return (logic->HasItem(RG_GERUDO_MEMBERSHIP_CARD) && logic->CanUse(RG_LONGSHOT));}),
	Entrance(RR_GF_HBA_RANGE, []{return (logic->IsChild || logic->HasItem(RG_GERUDO_MEMBERSHIP_CARD));}),
});
areaTable[RR_GF_TO_GTG] = Region("GF to GTG", SCENE_GERUDOS_FORTRESS, false, {RA_GERUDO_FORTRESS}, {}, {}, {
	Entrance(RR_GERUDO_TRAINING_GROUND_ENTRYWAY, []{return true;}),
});
areaTable[RR_GF_EXITING_GTG] = Region("GF Exiting GTG", SCENE_GERUDOS_FORTRESS, false, {RA_GERUDO_FORTRESS}, {}, {}, {
	Entrance(RR_GF_OUTSIDE_GTG, []{return (logic->IsChild || logic->HasItem(RG_GERUDO_MEMBERSHIP_CARD));}),
	Entrance(RR_GF_JAIL_WINDOW, []{return logic->CanUse(RG_HOOKSHOT);}),
	Entrance(RR_GF_OUTSKIRTS, []{return true;}),
});
areaTable[RR_GF_ABOVE_GTG] = Region("GF Above GTG", SCENE_GERUDOS_FORTRESS, false, {RA_GERUDO_FORTRESS}, {}, {}, {
	Entrance(RR_TH_DOUBLE_CELL, []{return true;}),
	Entrance(RR_TH_KITCHEN_CORRIDOR, []{return true;}),
	Entrance(RR_GF_JAIL_WINDOW, []{return logic->CanUse(RG_HOOKSHOT);}),
	Entrance(RR_GF_OUTSKIRTS, []{return true;}),
	Entrance(RR_GF_NEAR_GROTTO, []{return true;}),
	Entrance(RR_GF_OUTSIDE_GTG, []{return (logic->IsChild || logic->CanPassEnemy(RE_GERUDO_GUARD));}),
	Entrance(RR_GF_BOTTOM_OF_LOWER_VINES, []{return ((bool)ctx->GetTrickOption(RT_GF_JUMP) != 0);}),
});
areaTable[RR_GF_BOTTOM_OF_LOWER_VINES] = Region("GF Bottom of Lower Vines", SCENE_GERUDOS_FORTRESS, false, {RA_GERUDO_FORTRESS}, {}, {}, {
	Entrance(RR_TH_STEEP_SLOPE_CELL, []{return true;}),
	Entrance(RR_GF_NEAR_GROTTO, []{return true;}),
	Entrance(RR_GF_TOP_OF_LOWER_VINES, []{return true;}),
	Entrance(RR_GF_ABOVE_GTG, []{return true;}),
});
areaTable[RR_GF_TOP_OF_LOWER_VINES] = Region("GF Top of Lower Vines", SCENE_GERUDOS_FORTRESS, false, {RA_GERUDO_FORTRESS}, {}, {}, {
	Entrance(RR_TH_KITCHEN_TOP, []{return true;}),
	Entrance(RR_TH_DOUBLE_CELL, []{return true;}),
	Entrance(RR_GF_ABOVE_GTG, []{return true;}),
	Entrance(RR_GF_BOTTOM_OF_LOWER_VINES, []{return true;}),
	Entrance(RR_GF_BOTTOM_OF_UPPER_VINES, []{return (logic->IsAdult && (bool)ctx->GetTrickOption(RT_GF_JUMP));}),
});
areaTable[RR_GF_NEAR_GS] = Region("GF Near GS", SCENE_GERUDOS_FORTRESS, false, {RA_GERUDO_FORTRESS}, {}, {
	LOCATION(RC_GF_GS_TOP_FLOOR, (logic->IsAdult && (logic->CanGetEnemyDrop(RE_GOLD_SKULLTULA, ED_BOMB_THROW) && logic->CanGetNightTimeGS()))),
}, {
	Entrance(RR_TH_KITCHEN_TOP, []{return true;}),
	Entrance(RR_GF_BOTTOM_OF_LOWER_VINES, []{return true;}),
	Entrance(RR_GF_TOP_OF_LOWER_VINES, []{return true;}),
	Entrance(RR_GF_SLOPED_ROOF, []{return logic->IsAdult;}),
	Entrance(RR_GF_LONG_ROOF, []{return (logic->CanUse(RG_HOVER_BOOTS) || (logic->IsAdult && (bool)ctx->GetTrickOption(RT_GF_JUMP)));}),
	Entrance(RR_GF_NEAR_CHEST, []{return logic->CanUse(RG_LONGSHOT);}),
	Entrance(RR_GF_BELOW_GS, []{return true;}),
});
areaTable[RR_GF_SLOPED_ROOF] = Region("GF Sloped Roof", SCENE_GERUDOS_FORTRESS, false, {RA_GERUDO_FORTRESS}, {}, {}, {
	Entrance(RR_GF_TOP_OF_LOWER_VINES, []{return true;}),
	Entrance(RR_GF_NEAR_GS, []{return true;}),
	Entrance(RR_GF_BOTTOM_OF_UPPER_VINES, []{return true;}),
	Entrance(RR_GF_TOP_OF_UPPER_VINES, []{return (logic->IsAdult && (bool)ctx->GetTrickOption(RT_GF_JUMP));}),
});
areaTable[RR_GF_BOTTOM_OF_UPPER_VINES] = Region("GF Bottom of Upper Vines", SCENE_GERUDOS_FORTRESS, false, {RA_GERUDO_FORTRESS}, {}, {}, {
	Entrance(RR_GF_OUTSIDE_GTG, []{return true;}),
	Entrance(RR_GF_TOP_OF_LOWER_VINES, []{return true;}),
	Entrance(RR_GF_SLOPED_ROOF, []{return (logic->IsAdult && logic->CanUse(RG_HOVER_BOOTS));}),
	Entrance(RR_GF_TOP_OF_UPPER_VINES, []{return true;}),
	Entrance(RR_GF_TO_GTG, []{return (logic->IsAdult && (bool)ctx->GetTrickOption(RT_GF_LEDGE_CLIP_INTO_GTG));}),
});
areaTable[RR_GF_TOP_OF_UPPER_VINES] = Region("GF Top of Upper Vines", SCENE_GERUDOS_FORTRESS, false, {RA_GERUDO_FORTRESS}, {}, {
	LOCATION(RC_GF_GS_TOP_FLOOR, (logic->IsAdult && (logic->CanGetEnemyDrop(RE_GOLD_SKULLTULA, ED_SHORT_JUMPSLASH) && logic->CanGetNightTimeGS()))),
}, {
	Entrance(RR_GF_TOP_OF_LOWER_VINES, []{return true;}),
	Entrance(RR_GF_SLOPED_ROOF, []{return true;}),
	Entrance(RR_GF_BOTTOM_OF_UPPER_VINES, []{return true;}),
	Entrance(RR_GF_NEAR_CHEST, []{return (logic->CanUse(RG_HOVER_BOOTS) || ((logic->IsAdult && (logic->CanUse(RG_SCARECROW) && logic->CanUse(RG_HOOKSHOT))) || logic->CanUse(RG_LONGSHOT)));}),
});
areaTable[RR_GF_NEAR_CHEST] = Region("GF Near Chest", SCENE_GERUDOS_FORTRESS, false, {RA_GERUDO_FORTRESS}, {}, {
	LOCATION(RC_GF_CHEST, true),
	LOCATION(RC_GF_GS_TOP_FLOOR, (logic->IsAdult && (logic->CanGetEnemyDrop(RE_GOLD_SKULLTULA, ED_BOOMERANG) && logic->CanGetNightTimeGS()))),
}, {
	Entrance(RR_GF_NEAR_GS, []{return true;}),
	Entrance(RR_GF_LONG_ROOF, []{return true;}),
});
areaTable[RR_GF_LONG_ROOF] = Region("GF Long Roof", SCENE_GERUDOS_FORTRESS, false, {RA_GERUDO_FORTRESS}, {}, {}, {
	Entrance(RR_GF_BOTTOM_OF_LOWER_VINES, []{return true;}),
	Entrance(RR_GF_NEAR_GS, []{return ((logic->IsAdult && (bool)ctx->GetTrickOption(RT_GF_JUMP)) || logic->CanUse(RG_HOVER_BOOTS));}),
	Entrance(RR_GF_BELOW_GS, []{return true;}),
	Entrance(RR_GF_NEAR_CHEST, []{return logic->CanUse(RG_LONGSHOT);}),
	Entrance(RR_GF_BELOW_CHEST, []{return true;}),
});
areaTable[RR_GF_BELOW_GS] = Region("GF Below GS", SCENE_GERUDOS_FORTRESS, false, {RA_GERUDO_FORTRESS}, {}, {
	LOCATION(RC_GF_GS_TOP_FLOOR, (logic->IsAdult && (logic->CanGetEnemyDrop(RE_GOLD_SKULLTULA, ED_LONGSHOT) && logic->CanGetNightTimeGS()))),
}, {
	Entrance(RR_TH_DEAD_END_CELL, []{return true;}),
	Entrance(RR_GF_BOTTOM_OF_LOWER_VINES, []{return true;}),
});
areaTable[RR_GF_BELOW_CHEST] = Region("GF Below Chest", SCENE_GERUDOS_FORTRESS, false, {RA_GERUDO_FORTRESS}, {}, {}, {
	Entrance(RR_TH_BREAK_ROOM, []{return true;}),
	Entrance(RR_GF_OUTSKIRTS, []{return true;}),
});
areaTable[RR_GF_HBA_RANGE] = Region("GF HBA Range", SCENE_GERUDOS_FORTRESS, false, {RA_GERUDO_FORTRESS}, {}, {
	LOCATION(RC_GF_HBA_1000_POINTS, (logic->IsAdult && (logic->HasItem(RG_CHILD_WALLET) && (logic->HasItem(RG_GERUDO_MEMBERSHIP_CARD) && (logic->CanUse(RG_EPONA) && (logic->CanUse(RG_FAIRY_BOW) && logic->AtDay)))))),
	LOCATION(RC_GF_HBA_1500_POINTS, (logic->IsAdult && (logic->HasItem(RG_CHILD_WALLET) && (logic->HasItem(RG_GERUDO_MEMBERSHIP_CARD) && (logic->CanUse(RG_EPONA) && (logic->CanUse(RG_FAIRY_BOW) && logic->AtDay)))))),
	LOCATION(RC_GF_HBA_RANGE_GS, (logic->IsAdult && (logic->CanGetEnemyDrop(RE_GOLD_SKULLTULA, ED_BOOMERANG) && logic->CanGetNightTimeGS()))),
	LOCATION(RC_GF_HBA_RANGE_CRATE_1, logic->CanBreakCrates()),
	LOCATION(RC_GF_HBA_RANGE_CRATE_2, logic->CanBreakCrates()),
	LOCATION(RC_GF_HBA_RANGE_CRATE_3, logic->CanBreakCrates()),
	LOCATION(RC_GF_HBA_RANGE_CRATE_4, logic->CanBreakCrates()),
	LOCATION(RC_GF_HBA_RANGE_CRATE_5, logic->CanBreakCrates()),
	LOCATION(RC_GF_HBA_RANGE_CRATE_6, logic->CanBreakCrates()),
	LOCATION(RC_GF_HBA_RANGE_CRATE_7, logic->CanBreakCrates()),
	LOCATION(RC_GF_HBA_CANOPY_EAST_CRATE, logic->CanBreakCrates()),
	LOCATION(RC_GF_HBA_CANOPY_WEST_CRATE, logic->CanBreakCrates()),
	LOCATION(RC_GF_NORTH_TARGET_EAST_CRATE, logic->CanBreakCrates()),
	LOCATION(RC_GF_NORTH_TARGET_WEST_CRATE, (logic->IsAdult || (logic->BlastOrSmash() || (logic->HookshotOrBoomerang() || logic->CanUse(RG_HOVER_BOOTS))))),
	LOCATION(RC_GF_NORTH_TARGET_CHILD_CRATE, (logic->IsChild && logic->BlastOrSmash())),
	LOCATION(RC_GF_SOUTH_TARGET_EAST_CRATE, logic->CanBreakCrates()),
	LOCATION(RC_GF_SOUTH_TARGET_WEST_CRATE, logic->CanBreakCrates()),
}, {
	Entrance(RR_GF_OUTSIDE_GTG, []{return (logic->IsChild || logic->HasItem(RG_GERUDO_MEMBERSHIP_CARD));}),
});
areaTable[RR_GF_ABOVE_JAIL] = Region("GF Above Jail", SCENE_GERUDOS_FORTRESS, false, {RA_GERUDO_FORTRESS}, {}, {
	LOCATION(RC_GF_ABOVE_JAIL_CRATE, true),
}, {
	Entrance(RR_GF_OUTSKIRTS, []{return ((bool)ctx->GetTrickOption(RT_GF_JUMP) != 0);}),
	Entrance(RR_GF_NEAR_CHEST, []{return logic->CanUse(RG_LONGSHOT);}),
	Entrance(RR_GF_BELOW_CHEST, []{return logic->TakeDamage();}),
	Entrance(RR_GF_JAIL_WINDOW, []{return logic->CanUse(RG_HOOKSHOT);}),
});
areaTable[RR_GF_JAIL_WINDOW] = Region("GF Jail Window", SCENE_GERUDOS_FORTRESS, false, {RA_GERUDO_FORTRESS}, {}, {}, {
	Entrance(RR_GF_OUTSKIRTS, []{return true;}),
	Entrance(RR_GF_BELOW_CHEST, []{return true;}),
});
areaTable[RR_GF_OUTSIDE_GATE] = Region("GF Outside Gate", SCENE_GERUDOS_FORTRESS, false, {RA_GERUDO_FORTRESS}, {
	EventAccess(&logic->GF_GateOpen, []{return (logic->IsAdult && logic->HasItem(RG_GERUDO_MEMBERSHIP_CARD));}),
}, {}, {
	Entrance(RR_GF_OUTSKIRTS, []{return logic->GF_GateOpen;}),
	Entrance(RR_WASTELAND_NEAR_FORTRESS, []{return true;}),
});
areaTable[RR_GF_STORMS_GROTTO] = Region("GF Storms Grotto", SCENE_GROTTOS, false, {}, {
	EventAccess(&logic->FreeFairies, []{return true;}),
}, {
	LOCATION(RC_GF_FAIRY_GROTTO_FAIRY_1, true),
	LOCATION(RC_GF_FAIRY_GROTTO_FAIRY_2, true),
	LOCATION(RC_GF_FAIRY_GROTTO_FAIRY_3, true),
	LOCATION(RC_GF_FAIRY_GROTTO_FAIRY_4, true),
	LOCATION(RC_GF_FAIRY_GROTTO_FAIRY_5, true),
	LOCATION(RC_GF_FAIRY_GROTTO_FAIRY_6, true),
	LOCATION(RC_GF_FAIRY_GROTTO_FAIRY_7, true),
	LOCATION(RC_GF_FAIRY_GROTTO_FAIRY_8, true),
}, {
	Entrance(RR_GF_NEAR_GROTTO, []{return true;}),
});
areaTable[RR_TH_1_TORCH_CELL] = Region("Thieves Hideout 1 Torch Cell", SCENE_THIEVES_HIDEOUT, false, {RA_GERUDO_FORTRESS}, {
	EventAccess(&logic->THCouldFree1TorchCarpenter, []{return logic->CanKillEnemy(RE_GERUDO_WARRIOR);}),
	EventAccess(&logic->THRescuedAllCarpenters, []{return (logic->SmallKeys(RR_GF_OUTSKIRTS, (ctx->GetOption(RSK_GERUDO_FORTRESS).Is(RO_GF_CARPENTERS_NORMAL) ? 4 : 1)) && (logic->THCouldFree1TorchCarpenter && (logic->THCouldFreeDoubleCellCarpenter && (logic->TH_CouldFreeDeadEndCarpenter && logic->THCouldRescueSlopeCarpenter))));}),
}, {
	LOCATION(RC_TH_1_TORCH_CARPENTER, logic->CanKillEnemy(RE_GERUDO_WARRIOR)),
	LOCATION(RC_TH_1_TORCH_CELL_RIGHT_POT, logic->CanBreakPots()),
	LOCATION(RC_TH_1_TORCH_CELL_MID_POT, logic->CanBreakPots()),
	LOCATION(RC_TH_1_TORCH_CELL_LEFT_POT, logic->CanBreakPots()),
	LOCATION(RC_TH_1_TORCH_CELL_CRATE, logic->CanBreakCrates()),
	LOCATION(RC_TH_FREED_CARPENTERS, logic->THRescuedAllCarpenters),
}, {
	Entrance(RR_GF_OUTSKIRTS, []{return true;}),
	Entrance(RR_GF_NEAR_GROTTO, []{return true;}),
});
areaTable[RR_TH_DOUBLE_CELL] = Region("Thieves Hideout Double Cell", SCENE_THIEVES_HIDEOUT, false, {RA_GERUDO_FORTRESS}, {
	EventAccess(&logic->THCouldFreeDoubleCellCarpenter, []{return logic->CanKillEnemy(RE_GERUDO_WARRIOR);}),
	EventAccess(&logic->THRescuedAllCarpenters, []{return (ctx->GetOption(RSK_GERUDO_FORTRESS).Is(RO_GF_CARPENTERS_NORMAL) && (logic->SmallKeys(RR_GF_OUTSKIRTS, 4) && (logic->THCouldFree1TorchCarpenter && (logic->THCouldFreeDoubleCellCarpenter && (logic->TH_CouldFreeDeadEndCarpenter && logic->THCouldRescueSlopeCarpenter)))));}),
}, {
	LOCATION(RC_TH_DOUBLE_CELL_CARPENTER, logic->CanKillEnemy(RE_GERUDO_WARRIOR)),
	LOCATION(RC_TH_NEAR_DOUBLE_CELL_RIGHT_POT, logic->CanBreakPots()),
	LOCATION(RC_TH_NEAR_DOUBLE_CELL_MID_POT, logic->CanBreakPots()),
	LOCATION(RC_TH_NEAR_DOUBLE_CELL_LEFT_POT, logic->CanBreakPots()),
	LOCATION(RC_TH_RIGHTMOST_JAILED_POT, logic->CanBreakPots()),
	LOCATION(RC_TH_RIGHT_MIDDLE_JAILED_POT, logic->CanBreakPots()),
	LOCATION(RC_TH_LEFT_MIDDLE_JAILED_POT, logic->CanBreakPots()),
	LOCATION(RC_TH_LEFTMOST_JAILED_POT, logic->CanBreakPots()),
	LOCATION(RC_TH_DOUBLE_CELL_LEFT_CRATE, logic->CanBreakCrates()),
	LOCATION(RC_TH_DOUBLE_CELL_RIGHT_CRATE, logic->CanBreakCrates()),
	LOCATION(RC_TH_FREED_CARPENTERS, logic->THRescuedAllCarpenters),
}, {
	Entrance(RR_GF_OUTSKIRTS, []{return true;}),
	Entrance(RR_GF_NEAR_GROTTO, []{return true;}),
});
areaTable[RR_TH_DEAD_END_CELL] = Region("Thieves Hideout Dead End Cell", SCENE_THIEVES_HIDEOUT, false, {RA_GERUDO_FORTRESS}, {
	EventAccess(&logic->TH_CouldFreeDeadEndCarpenter, []{return logic->CanKillEnemy(RE_GERUDO_WARRIOR);}),
	EventAccess(&logic->THRescuedAllCarpenters, []{return (ctx->GetOption(RSK_GERUDO_FORTRESS).Is(RO_GF_CARPENTERS_NORMAL) && (logic->SmallKeys(RR_GF_OUTSKIRTS, 4) && (logic->THCouldFree1TorchCarpenter && (logic->THCouldFreeDoubleCellCarpenter && (logic->TH_CouldFreeDeadEndCarpenter && logic->THCouldRescueSlopeCarpenter)))));}),
}, {
	LOCATION(RC_TH_DEAD_END_CARPENTER, logic->CanKillEnemy(RE_GERUDO_WARRIOR)),
	LOCATION(RC_TH_DEAD_END_CELL_CRATE, logic->CanBreakCrates()),
	LOCATION(RC_TH_FREED_CARPENTERS, logic->THRescuedAllCarpenters),
}, {
	Entrance(RR_GF_BELOW_GS, []{return true;}),
});
areaTable[RR_TH_STEEP_SLOPE_CELL] = Region("Thieves Hideout Steep Slope Cell", SCENE_THIEVES_HIDEOUT, false, {RA_GERUDO_FORTRESS}, {
	EventAccess(&logic->THCouldRescueSlopeCarpenter, []{return logic->CanKillEnemy(RE_GERUDO_WARRIOR);}),
	EventAccess(&logic->THRescuedAllCarpenters, []{return (ctx->GetOption(RSK_GERUDO_FORTRESS).Is(RO_GF_CARPENTERS_NORMAL) && (logic->SmallKeys(RR_GF_OUTSKIRTS, 4) && (logic->THCouldFree1TorchCarpenter && (logic->THCouldFreeDoubleCellCarpenter && (logic->TH_CouldFreeDeadEndCarpenter && logic->THCouldRescueSlopeCarpenter)))));}),
}, {
	LOCATION(RC_TH_STEEP_SLOPE_CARPENTER, logic->CanKillEnemy(RE_GERUDO_WARRIOR)),
	LOCATION(RC_TH_STEEP_SLOPE_RIGHT_POT, logic->CanBreakPots()),
	LOCATION(RC_TH_STEEP_SLOPE_LEFT_POT, logic->CanBreakPots()),
	LOCATION(RC_TH_FREED_CARPENTERS, logic->THRescuedAllCarpenters),
}, {
	Entrance(RR_GF_ABOVE_GTG, []{return true;}),
	Entrance(RR_GF_TOP_OF_LOWER_VINES, []{return true;}),
});
areaTable[RR_TH_KITCHEN_CORRIDOR] = Region("Thieves Hideout Kitchen Corridor", SCENE_THIEVES_HIDEOUT, false, {RA_GERUDO_FORTRESS}, {}, {
	LOCATION(RC_TH_NEAR_KITCHEN_LEFTMOST_CRATE, logic->CanBreakCrates()),
	LOCATION(RC_TH_NEAR_KITCHEN_MID_LEFT_CRATE, logic->CanBreakCrates()),
	LOCATION(RC_TH_NEAR_KITCHEN_MID_RIGHT_CRATE, logic->CanBreakCrates()),
	LOCATION(RC_TH_NEAR_KITCHEN_RIGHTMOST_CRATE, logic->CanBreakCrates()),
}, {
	Entrance(RR_GF_NEAR_GROTTO, []{return true;}),
	Entrance(RR_GF_ABOVE_GTG, []{return true;}),
	Entrance(RR_TH_KITCHEN_MAIN, []{return logic->CanPassEnemy(RE_GERUDO_GUARD);}),
});
areaTable[RR_TH_KITCHEN_MAIN] = Region("Thieves Hideout Kitchen Bottom", SCENE_THIEVES_HIDEOUT, false, {RA_GERUDO_FORTRESS}, {}, {
	LOCATION(RC_TH_KITCHEN_POT_1, (logic->CanBreakPots() && logic->CanPassEnemy(RE_GERUDO_GUARD))),
	LOCATION(RC_TH_KITCHEN_POT_2, (logic->CanBreakPots() && logic->CanPassEnemy(RE_GERUDO_GUARD))),
	LOCATION(RC_TH_KITCHEN_CRATE, (logic->CanBreakCrates() && logic->CanPassEnemy(RE_GERUDO_GUARD))),
	LOCATION(RC_TH_KITCHEN_SUN_FAIRY, (logic->CanPassEnemy(RE_GERUDO_GUARD) && logic->CanUse(RG_SUNS_SONG))),
}, {
	Entrance(RR_TH_KITCHEN_CORRIDOR, []{return logic->CanPassEnemy(RE_GERUDO_GUARD);}),
	Entrance(RR_TH_KITCHEN_TOP, []{return logic->CanPassEnemy(RE_GERUDO_GUARD);}),
});
areaTable[RR_TH_KITCHEN_TOP] = Region("Thieves Hideout Kitchen Top", SCENE_THIEVES_HIDEOUT, false, {RA_GERUDO_FORTRESS}, {}, {
	LOCATION(RC_TH_KITCHEN_POT_1, logic->CanUse(RG_BOOMERANG)),
	LOCATION(RC_TH_KITCHEN_POT_2, logic->CanUse(RG_BOOMERANG)),
}, {
	Entrance(RR_TH_KITCHEN_MAIN, []{return true;}),
	Entrance(RR_GF_NEAR_GS, []{return (logic->CanPassEnemy(RE_GERUDO_GUARD) || logic->CanUse(RG_HOVER_BOOTS));}),
	Entrance(RR_GF_TOP_OF_LOWER_VINES, []{return (logic->CanPassEnemy(RE_GERUDO_GUARD) || logic->CanUse(RG_HOVER_BOOTS));}),
});
areaTable[RR_TH_BREAK_ROOM] = Region("Thieves Hideout Break Room", SCENE_THIEVES_HIDEOUT, false, {RA_GERUDO_FORTRESS}, {}, {
	LOCATION(RC_TH_BREAK_ROOM_FRONT_POT, ((logic->CanPassEnemy(RE_BREAK_ROOM_GUARD) && logic->CanBreakPots()) || (logic->CanPassEnemy(RE_GERUDO_GUARD) && logic->CanUse(RG_BOOMERANG)))),
	LOCATION(RC_TH_BREAK_ROOM_BACK_POT, ((logic->CanPassEnemy(RE_BREAK_ROOM_GUARD) && logic->CanBreakPots()) || (logic->CanPassEnemy(RE_GERUDO_GUARD) && logic->CanUse(RG_BOOMERANG)))),
	LOCATION(RC_TH_BREAK_HALLWAY_OUTER_CRATE, logic->CanBreakCrates()),
	LOCATION(RC_TH_BREAK_HALLWAY_INNER_CRATE, logic->CanBreakCrates()),
	LOCATION(RC_TH_BREAK_ROOM_RIGHT_CRATE, ((logic->CanPassEnemy(RE_BREAK_ROOM_GUARD) && logic->CanBreakCrates()) || (logic->CanPassEnemy(RE_GERUDO_GUARD) && (logic->HasExplosives() && logic->CanUse(RG_BOOMERANG))))),
	LOCATION(RC_TH_BREAK_ROOM_LEFT_CRATE, ((logic->CanPassEnemy(RE_BREAK_ROOM_GUARD) && logic->CanBreakCrates()) || (logic->CanPassEnemy(RE_GERUDO_GUARD) && (logic->HasExplosives() && logic->CanUse(RG_BOOMERANG))))),
}, {
	Entrance(RR_GF_BELOW_CHEST, []{return logic->CanPassEnemy(RE_GERUDO_GUARD);}),
	Entrance(RR_TH_BREAK_ROOM_CORRIDOR, []{return logic->CanUse(RG_HOOKSHOT);}),
});
areaTable[RR_TH_BREAK_ROOM_CORRIDOR] = Region("Thieves Hideout Break Room", SCENE_THIEVES_HIDEOUT, false, {RA_GERUDO_FORTRESS}, {}, {}, {
	Entrance(RR_TH_BREAK_ROOM, []{return logic->CanUse(RG_HOOKSHOT);}),
	Entrance(RR_GF_ABOVE_JAIL, []{return true;}),
});
areaTable[RR_WASTELAND_NEAR_FORTRESS] = Region("Wasteland Near Fortress", SCENE_HAUNTED_WASTELAND, false, {RA_HAUNTED_WASTELAND}, {}, {
	LOCATION(RC_HW_BEFORE_QUICKSAND_CRATE, logic->CanBreakCrates()),
}, {
	Entrance(RR_GF_OUTSIDE_GATE, []{return true;}),
	Entrance(RR_HAUNTED_WASTELAND, []{return (logic->CanUse(RG_HOVER_BOOTS) || (logic->CanUse(RG_LONGSHOT) || (bool)ctx->GetTrickOption(RT_HW_CROSSING)));}),
});
areaTable[RR_HAUNTED_WASTELAND] = Region("Haunted Wasteland", SCENE_HAUNTED_WASTELAND, false, {RA_HAUNTED_WASTELAND}, {
	EventAccess(&logic->FairyPot, []{return true;}),
	EventAccess(&logic->NutPot, []{return true;}),
	EventAccess(&logic->CarpetMerchant, []{return (logic->HasItem(RG_ADULT_WALLET) && (CanBuyCheck(RC_WASTELAND_BOMBCHU_SALESMAN) && (logic->CanJumpslash() || logic->CanUse(RG_HOVER_BOOTS))));}),
}, {
	LOCATION(RC_WASTELAND_CHEST, logic->HasFireSource()),
	LOCATION(RC_WASTELAND_BOMBCHU_SALESMAN, (logic->CanJumpslash() || logic->CanUse(RG_HOVER_BOOTS))),
	LOCATION(RC_WASTELAND_GS, logic->HookshotOrBoomerang()),
	LOCATION(RC_WASTELAND_NEAR_GS_POT_1, logic->CanBreakPots()),
	LOCATION(RC_WASTELAND_NEAR_GS_POT_2, logic->CanBreakPots()),
	LOCATION(RC_WASTELAND_NEAR_GS_POT_3, logic->CanBreakPots()),
	LOCATION(RC_WASTELAND_NEAR_GS_POT_4, logic->CanBreakPots()),
	LOCATION(RC_HW_AFTER_QUICKSAND_CRATE_1, logic->CanBreakCrates()),
	LOCATION(RC_HW_AFTER_QUICKSAND_CRATE_2, logic->CanBreakCrates()),
	LOCATION(RC_HW_AFTER_QUICKSAND_CRATE_3, logic->CanBreakCrates()),
}, {
	Entrance(RR_WASTELAND_NEAR_COLOSSUS, []{return ((bool)ctx->GetTrickOption(RT_LENS_HW) || logic->CanUse(RG_LENS_OF_TRUTH));}),
	Entrance(RR_WASTELAND_NEAR_FORTRESS, []{return (logic->CanUse(RG_HOVER_BOOTS) || (logic->CanUse(RG_LONGSHOT) || (bool)ctx->GetTrickOption(RT_HW_CROSSING)));}),
});
areaTable[RR_WASTELAND_NEAR_COLOSSUS] = Region("Wasteland Near Colossus", SCENE_HAUNTED_WASTELAND, false, {RA_HAUNTED_WASTELAND}, {}, {
	LOCATION(RC_HW_NEAR_COLOSSUS_CRATE, logic->CanBreakCrates()),
}, {
	Entrance(RR_DESERT_COLOSSUS, []{return true;}),
	Entrance(RR_HAUNTED_WASTELAND, []{return ((bool)ctx->GetTrickOption(RT_HW_REVERSE) || false);}),
});
areaTable[RR_DESERT_COLOSSUS] = Region("Desert Colossus", SCENE_DESERT_COLOSSUS, true, {RA_DESERT_COLOSSUS}, {
	EventAccess(&logic->FairyPond, []{return logic->CanUse(RG_SONG_OF_STORMS);}),
	EventAccess(&logic->BugRock, []{return true;}),
}, {
	LOCATION(RC_COLOSSUS_FREESTANDING_POH, (logic->IsAdult && CanPlantBean(RR_DESERT_COLOSSUS))),
	LOCATION(RC_COLOSSUS_GS_BEAN_PATCH, (logic->CanSpawnSoilSkull() && logic->CanAttack())),
	LOCATION(RC_COLOSSUS_GS_TREE, (logic->IsAdult && (logic->HookshotOrBoomerang() && logic->CanGetNightTimeGS()))),
	LOCATION(RC_COLOSSUS_GS_HILL, (logic->IsAdult && (((CanPlantBean(RR_DESERT_COLOSSUS) && logic->CanAttack()) || (logic->CanUse(RG_LONGSHOT) || ((bool)ctx->GetTrickOption(RT_COLOSSUS_GS) && logic->CanUse(RG_HOOKSHOT)))) && logic->CanGetNightTimeGS()))),
	LOCATION(RC_COLOSSUS_BEAN_SPROUT_FAIRY_1, (logic->IsChild && (logic->CanUse(RG_MAGIC_BEAN) && logic->CanUse(RG_SONG_OF_STORMS)))),
	LOCATION(RC_COLOSSUS_BEAN_SPROUT_FAIRY_2, (logic->IsChild && (logic->CanUse(RG_MAGIC_BEAN) && logic->CanUse(RG_SONG_OF_STORMS)))),
	LOCATION(RC_COLOSSUS_BEAN_SPROUT_FAIRY_3, (logic->IsChild && (logic->CanUse(RG_MAGIC_BEAN) && logic->CanUse(RG_SONG_OF_STORMS)))),
	LOCATION(RC_COLOSSUS_GOSSIP_STONE_FAIRY, logic->CallGossipFairy()),
	LOCATION(RC_COLOSSUS_GOSSIP_STONE_FAIRY_BIG, logic->CanUse(RG_SONG_OF_STORMS)),
	LOCATION(RC_COLOSSUS_GOSSIP_STONE, true),
}, {
	Entrance(RR_DESERT_COLOSSUS_OASIS, []{return (logic->CanUse(RG_SONG_OF_STORMS) && (logic->HasItem(RG_BRONZE_SCALE) || logic->CanUse(RG_IRON_BOOTS)));}),
	Entrance(RR_COLOSSUS_GREAT_FAIRY_FOUNTAIN, []{return logic->HasExplosives();}),
	Entrance(RR_SPIRIT_TEMPLE_ENTRYWAY, []{return true;}),
	Entrance(RR_WASTELAND_NEAR_COLOSSUS, []{return true;}),
	Entrance(RR_COLOSSUS_GROTTO, []{return logic->CanUse(RG_SILVER_GAUNTLETS);}),
});
areaTable[RR_DESERT_COLOSSUS_OASIS] = Region("Desert Colossus Oasis", SCENE_DESERT_COLOSSUS, true, {RA_DESERT_COLOSSUS}, {
	EventAccess(&logic->FairyPond, []{return true;}),
}, {
	LOCATION(RC_COLOSSUS_OASIS_FAIRY_1, true),
	LOCATION(RC_COLOSSUS_OASIS_FAIRY_2, true),
	LOCATION(RC_COLOSSUS_OASIS_FAIRY_3, true),
	LOCATION(RC_COLOSSUS_OASIS_FAIRY_4, true),
	LOCATION(RC_COLOSSUS_OASIS_FAIRY_5, true),
	LOCATION(RC_COLOSSUS_OASIS_FAIRY_6, true),
	LOCATION(RC_COLOSSUS_OASIS_FAIRY_7, true),
	LOCATION(RC_COLOSSUS_OASIS_FAIRY_8, true),
}, {
	Entrance(RR_DESERT_COLOSSUS, []{return true;}),
});
areaTable[RR_DESERT_COLOSSUS_OUTSIDE_TEMPLE] = Region("Desert Colossus From Spirit Entryway", SCENE_DESERT_COLOSSUS, true, {RA_DESERT_COLOSSUS}, {}, {
	LOCATION(RC_SHEIK_AT_COLOSSUS, true),
}, {
	Entrance(RR_DESERT_COLOSSUS, []{return true;}),
});
areaTable[RR_COLOSSUS_GREAT_FAIRY_FOUNTAIN] = Region("Colossus Great Fairy Fountain", SCENE_GREAT_FAIRYS_FOUNTAIN_SPELLS, false, {}, {}, {
	LOCATION(RC_COLOSSUS_GREAT_FAIRY_REWARD, logic->CanUse(RG_ZELDAS_LULLABY)),
}, {
	Entrance(RR_DESERT_COLOSSUS, []{return true;}),
});
areaTable[RR_COLOSSUS_GROTTO] = Region("Colossus Grotto", SCENE_GROTTOS, false, {}, {}, {
	LOCATION(RC_COLOSSUS_DEKU_SCRUB_GROTTO_REAR, logic->CanStunDeku()),
	LOCATION(RC_COLOSSUS_DEKU_SCRUB_GROTTO_FRONT, logic->CanStunDeku()),
	LOCATION(RC_COLOSSUS_GROTTO_BEEHIVE, logic->CanBreakUpperBeehives()),
}, {
	Entrance(RR_DESERT_COLOSSUS, []{return true;}),
});
areaTable[RR_MARKET_ENTRANCE] = Region("Market Entrance", SCENE_MARKET_ENTRANCE_DAY, false, {RA_THE_MARKET}, {}, {}, {
	Entrance(RR_HYRULE_FIELD, []{return (logic->IsAdult || logic->AtDay);}),
	Entrance(RR_THE_MARKET, []{return true;}),
	Entrance(RR_MARKET_GUARD_HOUSE, []{return logic->CanOpenOverworldDoor(RG_GUARD_HOUSE_KEY);}),
});
areaTable[RR_THE_MARKET] = Region("Market", SCENE_MARKET_DAY, false, {RA_THE_MARKET}, {}, {
	LOCATION(RC_MARKET_GRASS_1, (logic->IsChild && (logic->CanUseSword() || logic->HasItem(RG_GORONS_BRACELET)))),
	LOCATION(RC_MARKET_GRASS_2, (logic->IsChild && (logic->CanUseSword() || logic->HasItem(RG_GORONS_BRACELET)))),
	LOCATION(RC_MARKET_GRASS_3, (logic->IsChild && (logic->CanUseSword() || logic->HasItem(RG_GORONS_BRACELET)))),
	LOCATION(RC_MARKET_GRASS_4, (logic->IsChild && (logic->CanUseSword() || logic->HasItem(RG_GORONS_BRACELET)))),
	LOCATION(RC_MARKET_GRASS_5, (logic->IsChild && (logic->CanUseSword() || logic->HasItem(RG_GORONS_BRACELET)))),
	LOCATION(RC_MARKET_GRASS_6, (logic->IsChild && (logic->CanUseSword() || logic->HasItem(RG_GORONS_BRACELET)))),
	LOCATION(RC_MARKET_GRASS_7, (logic->IsChild && (logic->CanUseSword() || logic->HasItem(RG_GORONS_BRACELET)))),
	LOCATION(RC_MARKET_GRASS_8, (logic->IsChild && (logic->CanUseSword() || logic->HasItem(RG_GORONS_BRACELET)))),
	LOCATION(RC_MK_NEAR_BAZAAR_CRATE_1, logic->IsChild),
	LOCATION(RC_MK_NEAR_BAZAAR_CRATE_2, logic->IsChild),
	LOCATION(RC_MK_SHOOTING_GALLERY_CRATE_1, logic->IsChild),
	LOCATION(RC_MK_SHOOTING_GALLERY_CRATE_2, logic->IsChild),
}, {
	Entrance(RR_MARKET_ENTRANCE, []{return true;}),
	Entrance(RR_TOT_ENTRANCE, []{return true;}),
	Entrance(RR_CASTLE_GROUNDS, []{return true;}),
	Entrance(RR_MARKET_BAZAAR, []{return (logic->IsChild && (logic->AtDay && logic->CanOpenOverworldDoor(RG_MARKET_BAZAAR_KEY)));}),
	Entrance(RR_MARKET_MASK_SHOP, []{return (logic->IsChild && (logic->AtDay && logic->CanOpenOverworldDoor(RG_MASK_SHOP_KEY)));}),
	Entrance(RR_MARKET_SHOOTING_GALLERY, []{return (logic->IsChild && (logic->AtDay && logic->CanOpenOverworldDoor(RG_MARKET_SHOOTING_GALLERY_KEY)));}),
	Entrance(RR_MARKET_BOMBCHU_BOWLING, []{return (logic->IsChild && logic->CanOpenOverworldDoor(RG_BOMBCHU_BOWLING_KEY));}),
	Entrance(RR_MARKET_TREASURE_CHEST_GAME, []{return (logic->IsChild && (logic->AtNight && logic->CanOpenOverworldDoor(RG_TREASURE_CHEST_GAME_BUILDING_KEY)));}),
	Entrance(RR_MARKET_POTION_SHOP, []{return (logic->IsChild && (logic->AtDay && logic->CanOpenOverworldDoor(RG_MARKET_POTION_SHOP_KEY)));}),
	Entrance(RR_MARKET_BACK_ALLEY, []{return logic->IsChild;}),
});
areaTable[RR_MARKET_GUARD_HOUSE] = Region("Market Guard House", SCENE_MARKET_GUARD_HOUSE, false, {}, {
	EventAccess(&logic->CanEmptyBigPoes, []{return logic->IsAdult;}),
}, {
	LOCATION(RC_MARKET_10_BIG_POES, (logic->IsAdult && (logic->BigPoeKill || (logic->BigPoes >= ctx->GetOption(RSK_BIG_POE_COUNT).Get())))),
	LOCATION(RC_MARKET_GS_GUARD_HOUSE, logic->IsChild),
	LOCATION(RC_MK_GUARD_HOUSE_CHILD_POT_1, (logic->IsChild && logic->CanBreakPots())),
	LOCATION(RC_MK_GUARD_HOUSE_CHILD_POT_2, (logic->IsChild && logic->CanBreakPots())),
	LOCATION(RC_MK_GUARD_HOUSE_CHILD_POT_3, (logic->IsChild && logic->CanBreakPots())),
	LOCATION(RC_MK_GUARD_HOUSE_CHILD_POT_4, (logic->IsChild && logic->CanBreakPots())),
	LOCATION(RC_MK_GUARD_HOUSE_CHILD_POT_5, (logic->IsChild && logic->CanBreakPots())),
	LOCATION(RC_MK_GUARD_HOUSE_CHILD_POT_6, (logic->IsChild && logic->CanBreakPots())),
	LOCATION(RC_MK_GUARD_HOUSE_CHILD_POT_7, (logic->IsChild && logic->CanBreakPots())),
	LOCATION(RC_MK_GUARD_HOUSE_CHILD_POT_8, (logic->IsChild && logic->CanBreakPots())),
	LOCATION(RC_MK_GUARD_HOUSE_CHILD_POT_9, (logic->IsChild && logic->CanBreakPots())),
	LOCATION(RC_MK_GUARD_HOUSE_CHILD_POT_10, (logic->IsChild && logic->CanBreakPots())),
	LOCATION(RC_MK_GUARD_HOUSE_CHILD_POT_11, (logic->IsChild && logic->CanBreakPots())),
	LOCATION(RC_MK_GUARD_HOUSE_CHILD_POT_12, (logic->IsChild && logic->CanBreakPots())),
	LOCATION(RC_MK_GUARD_HOUSE_CHILD_POT_13, (logic->IsChild && logic->CanBreakPots())),
	LOCATION(RC_MK_GUARD_HOUSE_CHILD_POT_14, (logic->IsChild && logic->CanBreakPots())),
	LOCATION(RC_MK_GUARD_HOUSE_CHILD_POT_15, (logic->IsChild && logic->CanBreakPots())),
	LOCATION(RC_MK_GUARD_HOUSE_CHILD_POT_16, (logic->IsChild && logic->CanBreakPots())),
	LOCATION(RC_MK_GUARD_HOUSE_CHILD_POT_17, (logic->IsChild && logic->CanBreakPots())),
	LOCATION(RC_MK_GUARD_HOUSE_CHILD_POT_18, (logic->IsChild && logic->CanBreakPots())),
	LOCATION(RC_MK_GUARD_HOUSE_CHILD_POT_19, (logic->IsChild && logic->CanBreakPots())),
	LOCATION(RC_MK_GUARD_HOUSE_CHILD_POT_20, (logic->IsChild && logic->CanBreakPots())),
	LOCATION(RC_MK_GUARD_HOUSE_CHILD_POT_21, (logic->IsChild && logic->CanBreakPots())),
	LOCATION(RC_MK_GUARD_HOUSE_CHILD_POT_22, (logic->IsChild && logic->CanBreakPots())),
	LOCATION(RC_MK_GUARD_HOUSE_CHILD_POT_23, (logic->IsChild && logic->CanBreakPots())),
	LOCATION(RC_MK_GUARD_HOUSE_CHILD_POT_24, (logic->IsChild && logic->CanBreakPots())),
	LOCATION(RC_MK_GUARD_HOUSE_CHILD_POT_25, (logic->IsChild && logic->CanBreakPots())),
	LOCATION(RC_MK_GUARD_HOUSE_CHILD_POT_26, (logic->IsChild && logic->CanBreakPots())),
	LOCATION(RC_MK_GUARD_HOUSE_CHILD_POT_27, (logic->IsChild && logic->CanBreakPots())),
	LOCATION(RC_MK_GUARD_HOUSE_CHILD_POT_28, (logic->IsChild && logic->CanBreakPots())),
	LOCATION(RC_MK_GUARD_HOUSE_CHILD_POT_29, (logic->IsChild && logic->CanBreakPots())),
	LOCATION(RC_MK_GUARD_HOUSE_CHILD_POT_30, (logic->IsChild && logic->CanBreakPots())),
	LOCATION(RC_MK_GUARD_HOUSE_CHILD_POT_31, (logic->IsChild && logic->CanBreakPots())),
	LOCATION(RC_MK_GUARD_HOUSE_CHILD_POT_32, (logic->IsChild && logic->CanBreakPots())),
	LOCATION(RC_MK_GUARD_HOUSE_CHILD_POT_33, (logic->IsChild && logic->CanBreakPots())),
	LOCATION(RC_MK_GUARD_HOUSE_CHILD_POT_34, (logic->IsChild && logic->CanBreakPots())),
	LOCATION(RC_MK_GUARD_HOUSE_CHILD_POT_35, (logic->IsChild && logic->CanBreakPots())),
	LOCATION(RC_MK_GUARD_HOUSE_CHILD_POT_36, (logic->IsChild && logic->CanBreakPots())),
	LOCATION(RC_MK_GUARD_HOUSE_CHILD_POT_37, (logic->IsChild && logic->CanBreakPots())),
	LOCATION(RC_MK_GUARD_HOUSE_CHILD_POT_38, (logic->IsChild && logic->CanBreakPots())),
	LOCATION(RC_MK_GUARD_HOUSE_CHILD_POT_39, (logic->IsChild && logic->CanBreakPots())),
	LOCATION(RC_MK_GUARD_HOUSE_CHILD_POT_40, (logic->IsChild && logic->CanBreakPots())),
	LOCATION(RC_MK_GUARD_HOUSE_CHILD_POT_41, (logic->IsChild && logic->CanBreakPots())),
	LOCATION(RC_MK_GUARD_HOUSE_CHILD_POT_42, (logic->IsChild && logic->CanBreakPots())),
	LOCATION(RC_MK_GUARD_HOUSE_CHILD_POT_43, (logic->IsChild && logic->CanBreakPots())),
	LOCATION(RC_MK_GUARD_HOUSE_CHILD_POT_44, (logic->IsChild && logic->CanBreakPots())),
	LOCATION(RC_MK_GUARD_HOUSE_ADULT_POT_1, (logic->IsAdult && logic->CanBreakPots())),
	LOCATION(RC_MK_GUARD_HOUSE_ADULT_POT_2, (logic->IsAdult && logic->CanBreakPots())),
	LOCATION(RC_MK_GUARD_HOUSE_ADULT_POT_3, (logic->IsAdult && logic->CanBreakPots())),
	LOCATION(RC_MK_GUARD_HOUSE_ADULT_POT_4, (logic->IsAdult && logic->CanBreakPots())),
	LOCATION(RC_MK_GUARD_HOUSE_ADULT_POT_5, (logic->IsAdult && logic->CanBreakPots())),
	LOCATION(RC_MK_GUARD_HOUSE_ADULT_POT_6, (logic->IsAdult && logic->CanBreakPots())),
	LOCATION(RC_MK_GUARD_HOUSE_ADULT_POT_7, (logic->IsAdult && logic->CanBreakPots())),
	LOCATION(RC_MK_GUARD_HOUSE_ADULT_POT_8, (logic->IsAdult && logic->CanBreakPots())),
	LOCATION(RC_MK_GUARD_HOUSE_ADULT_POT_9, (logic->IsAdult && logic->CanBreakPots())),
	LOCATION(RC_MK_GUARD_HOUSE_ADULT_POT_10, (logic->IsAdult && logic->CanBreakPots())),
	LOCATION(RC_MK_GUARD_HOUSE_ADULT_POT_11, (logic->IsAdult && logic->CanBreakPots())),
	LOCATION(RC_MK_GUARD_HOUSE_CRATE_1, (logic->IsChild && logic->CanBreakCrates())),
	LOCATION(RC_MK_GUARD_HOUSE_CRATE_2, (logic->IsChild && logic->CanBreakCrates())),
	LOCATION(RC_MK_GUARD_HOUSE_CRATE_3, (logic->IsChild && logic->CanBreakCrates())),
	LOCATION(RC_MK_GUARD_HOUSE_CRATE_4, (logic->IsChild && logic->CanBreakCrates())),
	LOCATION(RC_MK_GUARD_HOUSE_CRATE_5, (logic->IsChild && logic->CanBreakCrates())),
}, {
	Entrance(RR_MARKET_ENTRANCE, []{return true;}),
});
areaTable[RR_MARKET_BAZAAR] = Region("Market Bazaar", SCENE_BAZAAR, false, {}, {}, {
	LOCATION(RC_MARKET_BAZAAR_ITEM_1, true),
	LOCATION(RC_MARKET_BAZAAR_ITEM_2, true),
	LOCATION(RC_MARKET_BAZAAR_ITEM_3, true),
	LOCATION(RC_MARKET_BAZAAR_ITEM_4, true),
	LOCATION(RC_MARKET_BAZAAR_ITEM_5, true),
	LOCATION(RC_MARKET_BAZAAR_ITEM_6, true),
	LOCATION(RC_MARKET_BAZAAR_ITEM_7, true),
	LOCATION(RC_MARKET_BAZAAR_ITEM_8, true),
}, {
	Entrance(RR_THE_MARKET, []{return true;}),
});
areaTable[RR_MARKET_MASK_SHOP] = Region("Market Mask Shop", SCENE_HAPPY_MASK_SHOP, false, {}, {
	EventAccess(&logic->CanBorrowMasks, []{return (logic->HasItem(RG_ZELDAS_LETTER) && logic->KakarikoVillageGateOpen);}),
	EventAccess(&logic->BorrowSkullMask, []{return (ctx->GetOption(RSK_COMPLETE_MASK_QUEST) && logic->CanBorrowMasks);}),
	EventAccess(&logic->BorrowSpookyMask, []{return (ctx->GetOption(RSK_COMPLETE_MASK_QUEST) && logic->CanBorrowMasks);}),
	EventAccess(&logic->BorrowBunnyHood, []{return (ctx->GetOption(RSK_COMPLETE_MASK_QUEST) && logic->CanBorrowMasks);}),
	EventAccess(&logic->BorrowRightMasks, []{return (ctx->GetOption(RSK_COMPLETE_MASK_QUEST) && logic->CanBorrowMasks);}),
}, {
	LOCATION(RC_MASK_SHOP_HINT, true),
}, {
	Entrance(RR_THE_MARKET, []{return true;}),
});
areaTable[RR_MARKET_SHOOTING_GALLERY] = Region("Market Shooting Gallery", SCENE_SHOOTING_GALLERY, false, {}, {}, {
	LOCATION(RC_MARKET_SHOOTING_GALLERY_REWARD, (logic->IsChild && logic->HasItem(RG_CHILD_WALLET))),
}, {
	Entrance(RR_THE_MARKET, []{return true;}),
});
areaTable[RR_MARKET_BOMBCHU_BOWLING] = Region("Market Bombchu Bowling", SCENE_BOMBCHU_BOWLING_ALLEY, false, {}, {
	EventAccess(&logic->CouldPlayBowling, []{return logic->HasItem(RG_CHILD_WALLET);}),
}, {
	LOCATION(RC_MARKET_BOMBCHU_BOWLING_FIRST_PRIZE, (logic->CouldPlayBowling && logic->BombchusEnabled())),
	LOCATION(RC_MARKET_BOMBCHU_BOWLING_SECOND_PRIZE, (logic->CouldPlayBowling && logic->BombchusEnabled())),
}, {
	Entrance(RR_THE_MARKET, []{return true;}),
});
areaTable[RR_MARKET_TREASURE_CHEST_GAME] = Region("Market Treasure Chest Game", SCENE_TREASURE_BOX_SHOP, false, {}, {}, {
	LOCATION(RC_GREG_HINT, logic->HasItem(RG_CHILD_WALLET)),
	LOCATION(RC_MARKET_TREASURE_CHEST_GAME_REWARD, (logic->HasItem(RG_CHILD_WALLET) && ((logic->CanUse(RG_LENS_OF_TRUTH) && !ctx->GetOption(RSK_SHUFFLE_CHEST_MINIGAME)) || ((ctx->GetOption(RSK_SHUFFLE_CHEST_MINIGAME).Is(RO_CHEST_GAME_SINGLE_KEYS) && logic->SmallKeys(RR_MARKET_TREASURE_CHEST_GAME, 6)) || (ctx->GetOption(RSK_SHUFFLE_CHEST_MINIGAME).Is(RO_CHEST_GAME_PACK) && logic->SmallKeys(RR_MARKET_TREASURE_CHEST_GAME, 1)))))),
	LOCATION(RC_MARKET_TREASURE_CHEST_GAME_KEY_1, (logic->HasItem(RG_CHILD_WALLET) && ((ctx->GetOption(RSK_SHUFFLE_CHEST_MINIGAME).Is(RO_CHEST_GAME_SINGLE_KEYS) && logic->SmallKeys(RR_MARKET_TREASURE_CHEST_GAME, 1)) || ((ctx->GetOption(RSK_SHUFFLE_CHEST_MINIGAME).Is(RO_CHEST_GAME_PACK) && logic->SmallKeys(RR_MARKET_TREASURE_CHEST_GAME, 1)) || (logic->CanUse(RG_LENS_OF_TRUTH) && !ctx->GetOption(RSK_SHUFFLE_CHEST_MINIGAME)))))),
	LOCATION(RC_MARKET_TREASURE_CHEST_GAME_ITEM_1, (logic->HasItem(RG_CHILD_WALLET) && ((ctx->GetOption(RSK_SHUFFLE_CHEST_MINIGAME).Is(RO_CHEST_GAME_SINGLE_KEYS) && logic->SmallKeys(RR_MARKET_TREASURE_CHEST_GAME, 1)) || ((ctx->GetOption(RSK_SHUFFLE_CHEST_MINIGAME).Is(RO_CHEST_GAME_PACK) && logic->SmallKeys(RR_MARKET_TREASURE_CHEST_GAME, 1)) || (logic->CanUse(RG_LENS_OF_TRUTH) && !ctx->GetOption(RSK_SHUFFLE_CHEST_MINIGAME)))))),
	LOCATION(RC_MARKET_TREASURE_CHEST_GAME_KEY_2, (logic->HasItem(RG_CHILD_WALLET) && ((ctx->GetOption(RSK_SHUFFLE_CHEST_MINIGAME).Is(RO_CHEST_GAME_SINGLE_KEYS) && logic->SmallKeys(RR_MARKET_TREASURE_CHEST_GAME, 2)) || ((ctx->GetOption(RSK_SHUFFLE_CHEST_MINIGAME).Is(RO_CHEST_GAME_PACK) && logic->SmallKeys(RR_MARKET_TREASURE_CHEST_GAME, 1)) || (logic->CanUse(RG_LENS_OF_TRUTH) && !ctx->GetOption(RSK_SHUFFLE_CHEST_MINIGAME)))))),
	LOCATION(RC_MARKET_TREASURE_CHEST_GAME_ITEM_2, (logic->HasItem(RG_CHILD_WALLET) && ((ctx->GetOption(RSK_SHUFFLE_CHEST_MINIGAME).Is(RO_CHEST_GAME_SINGLE_KEYS) && logic->SmallKeys(RR_MARKET_TREASURE_CHEST_GAME, 2)) || ((ctx->GetOption(RSK_SHUFFLE_CHEST_MINIGAME).Is(RO_CHEST_GAME_PACK) && logic->SmallKeys(RR_MARKET_TREASURE_CHEST_GAME, 1)) || (logic->CanUse(RG_LENS_OF_TRUTH) && !ctx->GetOption(RSK_SHUFFLE_CHEST_MINIGAME)))))),
	LOCATION(RC_MARKET_TREASURE_CHEST_GAME_KEY_3, (logic->HasItem(RG_CHILD_WALLET) && ((ctx->GetOption(RSK_SHUFFLE_CHEST_MINIGAME).Is(RO_CHEST_GAME_SINGLE_KEYS) && logic->SmallKeys(RR_MARKET_TREASURE_CHEST_GAME, 3)) || ((ctx->GetOption(RSK_SHUFFLE_CHEST_MINIGAME).Is(RO_CHEST_GAME_PACK) && logic->SmallKeys(RR_MARKET_TREASURE_CHEST_GAME, 1)) || (logic->CanUse(RG_LENS_OF_TRUTH) && !ctx->GetOption(RSK_SHUFFLE_CHEST_MINIGAME)))))),
	LOCATION(RC_MARKET_TREASURE_CHEST_GAME_ITEM_3, (logic->HasItem(RG_CHILD_WALLET) && ((ctx->GetOption(RSK_SHUFFLE_CHEST_MINIGAME).Is(RO_CHEST_GAME_SINGLE_KEYS) && logic->SmallKeys(RR_MARKET_TREASURE_CHEST_GAME, 3)) || ((ctx->GetOption(RSK_SHUFFLE_CHEST_MINIGAME).Is(RO_CHEST_GAME_PACK) && logic->SmallKeys(RR_MARKET_TREASURE_CHEST_GAME, 1)) || (logic->CanUse(RG_LENS_OF_TRUTH) && !ctx->GetOption(RSK_SHUFFLE_CHEST_MINIGAME)))))),
	LOCATION(RC_MARKET_TREASURE_CHEST_GAME_KEY_4, (logic->HasItem(RG_CHILD_WALLET) && ((ctx->GetOption(RSK_SHUFFLE_CHEST_MINIGAME).Is(RO_CHEST_GAME_SINGLE_KEYS) && logic->SmallKeys(RR_MARKET_TREASURE_CHEST_GAME, 4)) || ((ctx->GetOption(RSK_SHUFFLE_CHEST_MINIGAME).Is(RO_CHEST_GAME_PACK) && logic->SmallKeys(RR_MARKET_TREASURE_CHEST_GAME, 1)) || (logic->CanUse(RG_LENS_OF_TRUTH) && !ctx->GetOption(RSK_SHUFFLE_CHEST_MINIGAME)))))),
	LOCATION(RC_MARKET_TREASURE_CHEST_GAME_ITEM_4, (logic->HasItem(RG_CHILD_WALLET) && ((ctx->GetOption(RSK_SHUFFLE_CHEST_MINIGAME).Is(RO_CHEST_GAME_SINGLE_KEYS) && logic->SmallKeys(RR_MARKET_TREASURE_CHEST_GAME, 4)) || ((ctx->GetOption(RSK_SHUFFLE_CHEST_MINIGAME).Is(RO_CHEST_GAME_PACK) && logic->SmallKeys(RR_MARKET_TREASURE_CHEST_GAME, 1)) || (logic->CanUse(RG_LENS_OF_TRUTH) && !ctx->GetOption(RSK_SHUFFLE_CHEST_MINIGAME)))))),
	LOCATION(RC_MARKET_TREASURE_CHEST_GAME_KEY_5, (logic->HasItem(RG_CHILD_WALLET) && ((ctx->GetOption(RSK_SHUFFLE_CHEST_MINIGAME).Is(RO_CHEST_GAME_SINGLE_KEYS) && logic->SmallKeys(RR_MARKET_TREASURE_CHEST_GAME, 5)) || ((ctx->GetOption(RSK_SHUFFLE_CHEST_MINIGAME).Is(RO_CHEST_GAME_PACK) && logic->SmallKeys(RR_MARKET_TREASURE_CHEST_GAME, 1)) || (logic->CanUse(RG_LENS_OF_TRUTH) && !ctx->GetOption(RSK_SHUFFLE_CHEST_MINIGAME)))))),
	LOCATION(RC_MARKET_TREASURE_CHEST_GAME_ITEM_5, (logic->HasItem(RG_CHILD_WALLET) && ((ctx->GetOption(RSK_SHUFFLE_CHEST_MINIGAME).Is(RO_CHEST_GAME_SINGLE_KEYS) && logic->SmallKeys(RR_MARKET_TREASURE_CHEST_GAME, 5)) || ((ctx->GetOption(RSK_SHUFFLE_CHEST_MINIGAME).Is(RO_CHEST_GAME_PACK) && logic->SmallKeys(RR_MARKET_TREASURE_CHEST_GAME, 1)) || (logic->CanUse(RG_LENS_OF_TRUTH) && !ctx->GetOption(RSK_SHUFFLE_CHEST_MINIGAME)))))),
}, {
	Entrance(RR_THE_MARKET, []{return true;}),
});
areaTable[RR_MARKET_POTION_SHOP] = Region("Market Potion Shop", SCENE_POTION_SHOP_MARKET, false, {}, {}, {
	LOCATION(RC_MARKET_POTION_SHOP_ITEM_1, true),
	LOCATION(RC_MARKET_POTION_SHOP_ITEM_2, true),
	LOCATION(RC_MARKET_POTION_SHOP_ITEM_3, true),
	LOCATION(RC_MARKET_POTION_SHOP_ITEM_4, true),
	LOCATION(RC_MARKET_POTION_SHOP_ITEM_5, true),
	LOCATION(RC_MARKET_POTION_SHOP_ITEM_6, true),
	LOCATION(RC_MARKET_POTION_SHOP_ITEM_7, true),
	LOCATION(RC_MARKET_POTION_SHOP_ITEM_8, true),
}, {
	Entrance(RR_THE_MARKET, []{return true;}),
});
areaTable[RR_MARKET_BACK_ALLEY] = Region("Market Back Alley", SCENE_BACK_ALLEY_DAY, false, {RA_THE_MARKET}, {}, {}, {
	Entrance(RR_THE_MARKET, []{return true;}),
	Entrance(RR_MARKET_BOMBCHU_SHOP, []{return (logic->AtNight && logic->CanOpenOverworldDoor(RG_BOMBCHU_SHOP_KEY));}),
	Entrance(RR_MARKET_DOG_LADY_HOUSE, []{return logic->CanOpenOverworldDoor(RG_RICHARDS_HOUSE_KEY);}),
	Entrance(RR_MARKET_MAN_IN_GREEN_HOUSE, []{return (logic->AtNight && logic->CanOpenOverworldDoor(RG_ALLEY_HOUSE_KEY));}),
});
areaTable[RR_MARKET_BOMBCHU_SHOP] = Region("Market Bombchu Shop", SCENE_BOMBCHU_SHOP, false, {}, {}, {
	LOCATION(RC_MARKET_BOMBCHU_SHOP_ITEM_1, true),
	LOCATION(RC_MARKET_BOMBCHU_SHOP_ITEM_2, true),
	LOCATION(RC_MARKET_BOMBCHU_SHOP_ITEM_3, true),
	LOCATION(RC_MARKET_BOMBCHU_SHOP_ITEM_4, true),
	LOCATION(RC_MARKET_BOMBCHU_SHOP_ITEM_5, true),
	LOCATION(RC_MARKET_BOMBCHU_SHOP_ITEM_6, true),
	LOCATION(RC_MARKET_BOMBCHU_SHOP_ITEM_7, true),
	LOCATION(RC_MARKET_BOMBCHU_SHOP_ITEM_8, true),
}, {
	Entrance(RR_MARKET_BACK_ALLEY, []{return true;}),
});
areaTable[RR_MARKET_DOG_LADY_HOUSE] = Region("Market Dog Lady House", SCENE_DOG_LADY_HOUSE, false, {}, {}, {
	LOCATION(RC_MARKET_LOST_DOG, (logic->IsChild && logic->AtNight)),
	LOCATION(RC_MK_LOST_DOG_HOUSE_CRATE, logic->CanBreakCrates()),
}, {
	Entrance(RR_MARKET_BACK_ALLEY, []{return true;}),
});
areaTable[RR_MARKET_MAN_IN_GREEN_HOUSE] = Region("Market Man in Green House", SCENE_BACK_ALLEY_HOUSE, false, {}, {}, {
	LOCATION(RC_MK_BACK_ALLEY_HOUSE_POT_1, logic->CanBreakPots()),
	LOCATION(RC_MK_BACK_ALLEY_HOUSE_POT_2, logic->CanBreakPots()),
	LOCATION(RC_MK_BACK_ALLEY_HOUSE_POT_3, logic->CanBreakPots()),
}, {
	Entrance(RR_MARKET_BACK_ALLEY, []{return true;}),
});
areaTable[RR_TOT_ENTRANCE] = Region("ToT Entrance", SCENE_TEMPLE_OF_TIME_EXTERIOR_DAY, false, {RA_THE_MARKET}, {
	EventAccess(&logic->GossipStoneFairy, []{return logic->CallGossipFairyExceptSuns();}),
}, {
	LOCATION(RC_TOT_LEFTMOST_GOSSIP_STONE_FAIRY, (logic->CallGossipFairyExceptSuns() || (logic->CanUse(RG_SUNS_SONG) && logic->IsAdult))),
	LOCATION(RC_TOT_LEFTMOST_GOSSIP_STONE_FAIRY_BIG, logic->CanUse(RG_SONG_OF_STORMS)),
	LOCATION(RC_TOT_LEFT_CENTER_GOSSIP_STONE_FAIRY, (logic->CallGossipFairyExceptSuns() || (logic->CanUse(RG_SUNS_SONG) && logic->IsAdult))),
	LOCATION(RC_TOT_LEFT_CENTER_GOSSIP_STONE_FAIRY_BIG, logic->CanUse(RG_SONG_OF_STORMS)),
	LOCATION(RC_TOT_RIGHT_CENTER_GOSSIP_STONE_FAIRY, (logic->CallGossipFairyExceptSuns() || (logic->CanUse(RG_SUNS_SONG) && logic->IsAdult))),
	LOCATION(RC_TOT_RIGHT_CENTER_GOSSIP_STONE_FAIRY_BIG, logic->CanUse(RG_SONG_OF_STORMS)),
	LOCATION(RC_TOT_RIGHTMOST_GOSSIP_STONE_FAIRY, (logic->CallGossipFairyExceptSuns() || (logic->CanUse(RG_SUNS_SONG) && logic->IsAdult))),
	LOCATION(RC_TOT_RIGHTMOST_GOSSIP_STONE_FAIRY_BIG, logic->CanUse(RG_SONG_OF_STORMS)),
	LOCATION(RC_TOT_LEFTMOST_GOSSIP_STONE, true),
	LOCATION(RC_TOT_LEFT_CENTER_GOSSIP_STONE, true),
	LOCATION(RC_TOT_RIGHT_CENTER_GOSSIP_STONE, true),
	LOCATION(RC_TOT_RIGHTMOST_GOSSIP_STONE, true),
}, {
	Entrance(RR_THE_MARKET, []{return true;}),
	Entrance(RR_TEMPLE_OF_TIME, []{return true;}),
});
areaTable[RR_TEMPLE_OF_TIME] = Region("Temple of Time", SCENE_TEMPLE_OF_TIME, false, {RA_TEMPLE_OF_TIME}, {}, {
	LOCATION(RC_TOT_LIGHT_ARROWS_CUTSCENE, (logic->IsAdult && logic->CanTriggerLACS())),
	LOCATION(RC_ALTAR_HINT_CHILD, logic->IsChild),
	LOCATION(RC_ALTAR_HINT_ADULT, logic->IsAdult),
	LOCATION(RC_TOT_SHEIK_HINT, logic->IsAdult),
}, {
	Entrance(RR_TOT_ENTRANCE, []{return true;}),
	Entrance(RR_TOT_BEYOND_DOOR_OF_TIME, []{return (ctx->GetOption(RSK_DOOR_OF_TIME).Is(RO_DOOROFTIME_OPEN) || (logic->CanUse(RG_SONG_OF_TIME) && (ctx->GetOption(RSK_DOOR_OF_TIME).Is(RO_DOOROFTIME_SONGONLY) || ((logic->StoneCount() == 3) && logic->HasItem(RG_OCARINA_OF_TIME)))));}),
});
areaTable[RR_TOT_BEYOND_DOOR_OF_TIME] = Region("Beyond Door of Time", SCENE_TEMPLE_OF_TIME, false, {RA_TEMPLE_OF_TIME}, {}, {
	LOCATION(RC_TOT_MASTER_SWORD, logic->IsAdult),
	LOCATION(RC_GIFT_FROM_RAURU, logic->IsAdult),
	LOCATION(RC_SHEIK_AT_TEMPLE, (logic->HasItem(RG_FOREST_MEDALLION) && logic->IsAdult)),
}, {
	Entrance(RR_TEMPLE_OF_TIME, []{return true;}),
});
areaTable[RR_CASTLE_GROUNDS] = Region("Castle Grounds", SCENE_OUTSIDE_GANONS_CASTLE, false, {RA_CASTLE_GROUNDS}, {}, {}, {
	Entrance(RR_THE_MARKET, []{return true;}),
	Entrance(RR_HYRULE_CASTLE_GROUNDS, []{return logic->IsChild;}),
	Entrance(RR_GANONS_CASTLE_GROUNDS, []{return logic->IsAdult;}),
});
areaTable[RR_CASTLE_GROUNDS_FROM_GANONS_CASTLE] = Region("Castle Grounds From Ganon's Castle", SCENE_OUTSIDE_GANONS_CASTLE, false, {RA_OUTSIDE_GANONS_CASTLE}, {}, {}, {
	Entrance(RR_HYRULE_CASTLE_GROUNDS, []{return logic->IsChild;}),
	Entrance(RR_GANONS_CASTLE_LEDGE, []{return logic->IsAdult;}),
});
areaTable[RR_HYRULE_CASTLE_GROUNDS] = Region("Hyrule Castle Grounds", SCENE_HYRULE_CASTLE, true, {RA_HYRULE_CASTLE}, {
	EventAccess(&logic->GossipStoneFairy, []{return logic->CallGossipFairy();}),
	EventAccess(&logic->ButterflyFairy, []{return logic->CanUse(RG_STICKS);}),
	EventAccess(&logic->BugRock, []{return true;}),
}, {
	LOCATION(RC_HC_MALON_EGG, true),
	LOCATION(RC_HC_GS_TREE, (logic->IsChild && logic->CanKillEnemy(RE_GOLD_SKULLTULA, ED_CLOSE))),
	LOCATION(RC_HC_MALON_GOSSIP_STONE_FAIRY, logic->CallGossipFairy()),
	LOCATION(RC_HC_MALON_GOSSIP_STONE_FAIRY_BIG, logic->CanUse(RG_SONG_OF_STORMS)),
	LOCATION(RC_HC_ROCK_WALL_GOSSIP_STONE_FAIRY, logic->CallGossipFairy()),
	LOCATION(RC_HC_ROCK_WALL_GOSSIP_STONE_FAIRY_BIG, logic->CanUse(RG_SONG_OF_STORMS)),
	LOCATION(RC_HC_MALON_GOSSIP_STONE, true),
	LOCATION(RC_HC_ROCK_WALL_GOSSIP_STONE, true),
	LOCATION(RC_HC_GRASS_1, logic->CanCutShrubs()),
	LOCATION(RC_HC_GRASS_2, logic->CanCutShrubs()),
}, {
	Entrance(RR_CASTLE_GROUNDS, []{return true;}),
	Entrance(RR_HC_GARDEN, []{return (logic->CanUse(RG_WEIRD_EGG) || ((bool)ctx->GetTrickOption(RT_DAMAGE_BOOST_SIMPLE) && (logic->HasExplosives() && logic->CanJumpslash())));}),
	Entrance(RR_HC_GREAT_FAIRY_FOUNTAIN, []{return logic->BlastOrSmash();}),
	Entrance(RR_HC_STORMS_GROTTO, []{return logic->CanOpenStormsGrotto();}),
});
areaTable[RR_HC_GARDEN] = Region("HC Garden", SCENE_CASTLE_COURTYARD_ZELDA, false, {}, {}, {
	LOCATION(RC_HC_ZELDAS_LETTER, true),
	LOCATION(RC_SONG_FROM_IMPA, true),
}, {
	Entrance(RR_HYRULE_CASTLE_GROUNDS, []{return true;}),
});
areaTable[RR_HC_GREAT_FAIRY_FOUNTAIN] = Region("HC Great Fairy Fountain", SCENE_GREAT_FAIRYS_FOUNTAIN_SPELLS, false, {}, {}, {
	LOCATION(RC_HC_GREAT_FAIRY_REWARD, logic->CanUse(RG_ZELDAS_LULLABY)),
}, {
	Entrance(RR_CASTLE_GROUNDS, []{return true;}),
});
areaTable[RR_HC_STORMS_GROTTO] = Region("HC Storms Grotto", SCENE_GROTTOS, false, {}, {}, {
	LOCATION(RC_HC_GS_STORMS_GROTTO, (logic->CanUse(RG_BOOMERANG) && (bool)ctx->GetTrickOption(RT_HC_STORMS_GS))),
}, {
	Entrance(RR_CASTLE_GROUNDS, []{return true;}),
	Entrance(RR_HC_STORMS_GROTTO_BEHIND_WALLS, []{return logic->CanBreakMudWalls();}),
});
areaTable[RR_HC_STORMS_GROTTO_BEHIND_WALLS] = Region("HC Storms Grotto Behind Walls", SCENE_GROTTOS, false, {}, {
	EventAccess(&logic->NutPot, []{return true;}),
	EventAccess(&logic->GossipStoneFairy, []{return logic->CallGossipFairy();}),
	EventAccess(&logic->WanderingBugs, []{return true;}),
}, {
	LOCATION(RC_HC_GS_STORMS_GROTTO, logic->HookshotOrBoomerang()),
	LOCATION(RC_HC_STORMS_GROTTO_GOSSIP_STONE_FAIRY, logic->CallGossipFairy()),
	LOCATION(RC_HC_STORMS_GROTTO_GOSSIP_STONE_FAIRY_BIG, logic->CanUse(RG_SONG_OF_STORMS)),
	LOCATION(RC_HC_STORMS_GROTTO_GOSSIP_STONE, true),
	LOCATION(RC_HC_STORMS_GROTTO_POT_1, logic->CanBreakPots()),
	LOCATION(RC_HC_STORMS_GROTTO_POT_2, logic->CanBreakPots()),
	LOCATION(RC_HC_STORMS_GROTTO_POT_3, logic->CanBreakPots()),
	LOCATION(RC_HC_STORMS_GROTTO_POT_4, logic->CanBreakPots()),
}, {
	Entrance(RR_HC_STORMS_GROTTO, []{return true;}),
});
areaTable[RR_GANONS_CASTLE_GROUNDS] = Region("Ganon's Castle Grounds", SCENE_OUTSIDE_GANONS_CASTLE, false, {RA_OUTSIDE_GANONS_CASTLE}, {
	EventAccess(&logic->BuiltRainbowBridge, []{return logic->CanBuildRainbowBridge();}),
}, {
	LOCATION(RC_OGC_GS, (logic->CanJumpslashExceptHammer() || (logic->CanUseProjectile() || ((logic->CanShield() && logic->CanUse(RG_MEGATON_HAMMER)) || logic->CanUse(RG_DINS_FIRE))))),
}, {
	Entrance(RR_CASTLE_GROUNDS, []{return logic->AtNight;}),
	Entrance(RR_OGC_GREAT_FAIRY_FOUNTAIN, []{return (logic->CanUse(RG_GOLDEN_GAUNTLETS) && logic->AtNight);}),
	Entrance(RR_GANONS_CASTLE_LEDGE, []{return logic->BuiltRainbowBridge;}),
});
areaTable[RR_OGC_GREAT_FAIRY_FOUNTAIN] = Region("OGC Great Fairy Fountain", SCENE_GREAT_FAIRYS_FOUNTAIN_MAGIC, false, {}, {}, {
	LOCATION(RC_OGC_GREAT_FAIRY_REWARD, logic->CanUse(RG_ZELDAS_LULLABY)),
}, {
	Entrance(RR_CASTLE_GROUNDS, []{return true;}),
});
areaTable[RR_GANONS_CASTLE_LEDGE] = Region("Ganon's Castle Ledge", SCENE_OUTSIDE_GANONS_CASTLE, false, {RA_OUTSIDE_GANONS_CASTLE}, {}, {}, {
	Entrance(RR_GANONS_CASTLE_GROUNDS, []{return logic->BuiltRainbowBridge;}),
	Entrance(RR_GANONS_CASTLE_ENTRYWAY, []{return logic->IsAdult;}),
});
areaTable[RR_KAKARIKO_VILLAGE] = Region("Kakariko Village", SCENE_KAKARIKO_VILLAGE, true, {RA_KAKARIKO_VILLAGE}, {
	EventAccess(&logic->BugRock, []{return true;}),
	EventAccess(&logic->KakarikoVillageGateOpen, []{return (logic->IsChild && logic->HasItem(RG_ZELDAS_LETTER));}),
	EventAccess(&logic->BorrowSkullMask, []{return (logic->IsChild && (logic->CanBorrowMasks && logic->HasItem(RG_CHILD_WALLET)));}),
}, {
	LOCATION(RC_SHEIK_IN_KAKARIKO, (logic->IsAdult && (logic->HasItem(RG_FOREST_MEDALLION) && (logic->HasItem(RG_FIRE_MEDALLION) && logic->HasItem(RG_WATER_MEDALLION))))),
	LOCATION(RC_KAK_ANJU_AS_CHILD, (logic->IsChild && logic->AtDay)),
	LOCATION(RC_KAK_ANJU_AS_ADULT, (logic->IsAdult && logic->AtDay)),
	LOCATION(RC_KAK_TRADE_POCKET_CUCCO, (logic->IsAdult && (logic->AtDay && (logic->CanUse(RG_POCKET_EGG) && logic->WakeUpAdultTalon)))),
	LOCATION(RC_KAK_GS_HOUSE_UNDER_CONSTRUCTION, (logic->IsChild && logic->CanGetNightTimeGS())),
	LOCATION(RC_KAK_GS_SKULLTULA_HOUSE, (logic->IsChild && logic->CanGetNightTimeGS())),
	LOCATION(RC_KAK_GS_GUARDS_HOUSE, (logic->IsChild && logic->CanGetNightTimeGS())),
	LOCATION(RC_KAK_GS_TREE, (logic->IsChild && logic->CanGetNightTimeGS())),
	LOCATION(RC_KAK_GS_WATCHTOWER, (logic->IsChild && ((logic->CanKillEnemy(RE_GOLD_SKULLTULA, ED_LONGSHOT) || ((bool)ctx->GetTrickOption(RT_KAK_TOWER_GS) && logic->CanJumpslashExceptHammer())) && logic->CanGetNightTimeGS()))),
	LOCATION(RC_KAK_NEAR_POTION_SHOP_POT_1, (logic->IsChild && logic->CanBreakPots())),
	LOCATION(RC_KAK_NEAR_POTION_SHOP_POT_2, (logic->IsChild && logic->CanBreakPots())),
	LOCATION(RC_KAK_NEAR_POTION_SHOP_POT_3, (logic->IsChild && logic->CanBreakPots())),
	LOCATION(RC_KAK_NEAR_IMPAS_HOUSE_POT_1, (logic->IsChild && logic->CanBreakPots())),
	LOCATION(RC_KAK_NEAR_IMPAS_HOUSE_POT_2, (logic->IsChild && logic->CanBreakPots())),
	LOCATION(RC_KAK_NEAR_IMPAS_HOUSE_POT_3, (logic->IsChild && logic->CanBreakPots())),
	LOCATION(RC_KAK_NEAR_GUARDS_HOUSE_POT_1, (logic->IsChild && logic->CanBreakPots())),
	LOCATION(RC_KAK_NEAR_GUARDS_HOUSE_POT_2, (logic->IsChild && logic->CanBreakPots())),
	LOCATION(RC_KAK_NEAR_GUARDS_HOUSE_POT_3, (logic->IsChild && logic->CanBreakPots())),
	LOCATION(RC_KAK_GRASS_1, logic->CanCutShrubs()),
	LOCATION(RC_KAK_GRASS_2, logic->CanCutShrubs()),
	LOCATION(RC_KAK_GRASS_3, logic->CanCutShrubs()),
	LOCATION(RC_KAK_GRASS_4, logic->CanCutShrubs()),
	LOCATION(RC_KAK_GRASS_5, logic->CanCutShrubs()),
	LOCATION(RC_KAK_GRASS_6, logic->CanCutShrubs()),
	LOCATION(RC_KAK_GRASS_7, logic->CanCutShrubs()),
	LOCATION(RC_KAK_GRASS_8, logic->CanCutShrubs()),
	LOCATION(RC_KAK_NEAR_OPEN_GROTTO_ADULT_CRATE_1, (logic->IsAdult && logic->CanBreakCrates())),
	LOCATION(RC_KAK_NEAR_OPEN_GROTTO_ADULT_CRATE_2, (logic->IsAdult && logic->CanBreakCrates())),
	LOCATION(RC_KAK_NEAR_OPEN_GROTTO_ADULT_CRATE_3, (logic->IsAdult && logic->CanBreakCrates())),
	LOCATION(RC_KAK_NEAR_OPEN_GROTTO_ADULT_CRATE_4, (logic->IsAdult && logic->CanBreakCrates())),
	LOCATION(RC_KAK_NEAR_POTION_SHOP_ADULT_CRATE, (logic->IsAdult && logic->CanBreakCrates())),
	LOCATION(RC_KAK_NEAR_SHOOTING_GALLERY_ADULT_CRATE, (logic->IsAdult && logic->CanBreakCrates())),
	LOCATION(RC_KAK_NEAR_BOARDING_HOUSE_ADULT_CRATE_1, (logic->IsAdult && logic->CanBreakCrates())),
	LOCATION(RC_KAK_NEAR_BOARDING_HOUSE_ADULT_CRATE_2, (logic->IsAdult && logic->CanBreakCrates())),
	LOCATION(RC_KAK_NEAR_IMPAS_HOUSE_ADULT_CRATE_1, (logic->IsAdult && logic->CanBreakCrates())),
	LOCATION(RC_KAK_NEAR_IMPAS_HOUSE_ADULT_CRATE_2, (logic->IsAdult && logic->CanBreakCrates())),
	LOCATION(RC_KAK_NEAR_BAZAAR_ADULT_CRATE_1, (logic->IsAdult && logic->CanBreakCrates())),
	LOCATION(RC_KAK_NEAR_BAZAAR_ADULT_CRATE_2, (logic->IsAdult && logic->CanBreakCrates())),
	LOCATION(RC_KAK_BEHIND_GS_HOUSE_ADULT_CRATE, (logic->IsAdult && logic->CanBreakCrates())),
	LOCATION(RC_KAK_NEAR_GY_CHILD_CRATE, (logic->IsChild && logic->CanBreakCrates())),
	LOCATION(RC_KAK_NEAR_WINDMILL_CHILD_CRATE, (logic->IsChild && logic->CanBreakCrates())),
	LOCATION(RC_KAK_NEAR_FENCE_CHILD_CRATE, (logic->IsChild && logic->CanBreakCrates())),
	LOCATION(RC_KAK_NEAR_BOARDING_HOUSE_CHILD_CRATE, (logic->IsChild && logic->CanBreakCrates())),
	LOCATION(RC_KAK_NEAR_BAZAAR_CHILD_CRATE, (logic->IsChild && logic->CanBreakCrates())),
}, {
	Entrance(RR_HYRULE_FIELD, []{return true;}),
	Entrance(RR_KAK_CARPENTER_BOSS_HOUSE, []{return logic->CanOpenOverworldDoor(RG_BOSS_HOUSE_KEY);}),
	Entrance(RR_KAK_HOUSE_OF_SKULLTULA, []{return logic->CanOpenOverworldDoor(RG_SKULLTULA_HOUSE_KEY);}),
	Entrance(RR_KAK_IMPAS_HOUSE, []{return logic->CanOpenOverworldDoor(RG_IMPAS_HOUSE_KEY);}),
	Entrance(RR_KAK_WINDMILL, []{return logic->CanOpenOverworldDoor(RG_WINDMILL_KEY);}),
	Entrance(RR_KAK_BAZAAR, []{return (logic->IsAdult && (logic->AtDay && logic->CanOpenOverworldDoor(RG_KAK_BAZAAR_KEY)));}),
	Entrance(RR_KAK_SHOOTING_GALLERY, []{return (logic->IsAdult && (logic->AtDay && logic->CanOpenOverworldDoor(RG_KAK_SHOOTING_GALLERY_KEY)));}),
	Entrance(RR_KAK_WELL, []{return (logic->IsAdult || (logic->DrainWell || (logic->CanUse(RG_IRON_BOOTS) || ((bool)ctx->GetTrickOption(RT_BOTTOM_OF_THE_WELL_NAVI_DIVE) && (logic->IsChild && (logic->HasItem(RG_BRONZE_SCALE) && logic->CanJumpslash()))))));}),
	Entrance(RR_KAK_POTION_SHOP_FRONT, []{return ((logic->AtDay || logic->IsChild) && logic->CanOpenOverworldDoor(RG_KAK_POTION_SHOP_KEY));}),
	Entrance(RR_KAK_REDEAD_GROTTO, []{return logic->CanOpenBombGrotto();}),
	Entrance(RR_KAK_IMPAS_LEDGE, []{return ((logic->IsChild && logic->AtDay) || (logic->IsAdult && (bool)ctx->GetTrickOption(RT_VISIBLE_COLLISION)));}),
	Entrance(RR_KAK_WATCHTOWER, []{return (logic->IsAdult || (logic->AtDay || (logic->CanKillEnemy(RE_GOLD_SKULLTULA, ED_LONGSHOT) || ((bool)ctx->GetTrickOption(RT_KAK_TOWER_GS) && logic->CanJumpslashExceptHammer()))));}),
	Entrance(RR_KAK_ROOFTOP, []{return (logic->CanUse(RG_HOOKSHOT) || ((bool)ctx->GetTrickOption(RT_KAK_MAN_ON_ROOF) && logic->IsAdult));}),
	Entrance(RR_KAK_IMPAS_ROOFTOP, []{return (logic->CanUse(RG_HOOKSHOT) || ((bool)ctx->GetTrickOption(RT_KAK_ROOFTOP_GS) && logic->CanUse(RG_HOVER_BOOTS)));}),
	Entrance(RR_THE_GRAVEYARD, []{return true;}),
	Entrance(RR_KAK_BEHIND_GATE, []{return (logic->IsAdult || logic->KakarikoVillageGateOpen);}),
	Entrance(RR_KAK_BACKYARD, []{return (logic->IsAdult || logic->AtDay);}),
});
areaTable[RR_KAK_CARPENTER_BOSS_HOUSE] = Region("Kak Carpenter Boss House", SCENE_KAKARIKO_CENTER_GUEST_HOUSE, false, {}, {
	EventAccess(&logic->WakeUpAdultTalon, []{return (logic->IsAdult && logic->CanUse(RG_POCKET_EGG));}),
}, {}, {
	Entrance(RR_KAKARIKO_VILLAGE, []{return true;}),
});
areaTable[RR_KAK_HOUSE_OF_SKULLTULA] = Region("Kak House of Skulltula", SCENE_HOUSE_OF_SKULLTULA, false, {}, {}, {
	LOCATION(RC_KAK_10_GOLD_SKULLTULA_REWARD, (logic->GetGSCount() >= 10)),
	LOCATION(RC_KAK_20_GOLD_SKULLTULA_REWARD, (logic->GetGSCount() >= 20)),
	LOCATION(RC_KAK_30_GOLD_SKULLTULA_REWARD, (logic->GetGSCount() >= 30)),
	LOCATION(RC_KAK_40_GOLD_SKULLTULA_REWARD, (logic->GetGSCount() >= 40)),
	LOCATION(RC_KAK_50_GOLD_SKULLTULA_REWARD, (logic->GetGSCount() >= 50)),
	LOCATION(RC_KAK_100_GOLD_SKULLTULA_REWARD, (logic->GetGSCount() >= 100)),
}, {
	Entrance(RR_KAKARIKO_VILLAGE, []{return true;}),
});
areaTable[RR_KAK_IMPAS_HOUSE] = Region("Kak Impas House", SCENE_IMPAS_HOUSE, false, {}, {}, {
	LOCATION(RC_KAK_IMPAS_HOUSE_COW, logic->CanUse(RG_EPONAS_SONG)),
}, {
	Entrance(RR_KAKARIKO_VILLAGE, []{return true;}),
});
areaTable[RR_KAK_IMPAS_LEDGE] = Region("Kak Impas Ledge", SCENE_KAKARIKO_VILLAGE, true, {RA_KAKARIKO_VILLAGE}, {}, {}, {
	Entrance(RR_KAK_IMPAS_HOUSE_BACK, []{return true;}),
	Entrance(RR_KAKARIKO_VILLAGE, []{return true;}),
});
areaTable[RR_KAK_IMPAS_HOUSE_BACK] = Region("Kak Impas House Back", SCENE_IMPAS_HOUSE, false, {}, {}, {
	LOCATION(RC_KAK_IMPAS_HOUSE_FREESTANDING_POH, true),
	LOCATION(RC_KAK_IMPAS_HOUSE_COW, logic->CanUse(RG_EPONAS_SONG)),
}, {
	Entrance(RR_KAK_IMPAS_LEDGE, []{return true;}),
});
areaTable[RR_KAK_WINDMILL] = Region("Kak Windmill", SCENE_WINDMILL_AND_DAMPES_GRAVE, false, {}, {
	EventAccess(&logic->DrainWell, []{return (logic->IsChild && logic->CanUse(RG_SONG_OF_STORMS));}),
}, {
	LOCATION(RC_KAK_WINDMILL_FREESTANDING_POH, (logic->CanUse(RG_BOOMERANG) || (logic->DampesWindmillAccess || ((logic->IsAdult && (bool)ctx->GetTrickOption(RT_KAK_ADULT_WINDMILL_POH)) || (logic->IsChild && (logic->CanJumpslashExceptHammer() && (bool)ctx->GetTrickOption(RT_KAK_CHILD_WINDMILL_POH))))))),
	LOCATION(RC_SONG_FROM_WINDMILL, (logic->IsAdult && logic->HasItem(RG_FAIRY_OCARINA))),
}, {
	Entrance(RR_KAKARIKO_VILLAGE, []{return true;}),
});
areaTable[RR_KAK_BAZAAR] = Region("Kak Bazaar", SCENE_BAZAAR, false, {}, {}, {
	LOCATION(RC_KAK_BAZAAR_ITEM_1, true),
	LOCATION(RC_KAK_BAZAAR_ITEM_2, true),
	LOCATION(RC_KAK_BAZAAR_ITEM_3, true),
	LOCATION(RC_KAK_BAZAAR_ITEM_4, true),
	LOCATION(RC_KAK_BAZAAR_ITEM_5, true),
	LOCATION(RC_KAK_BAZAAR_ITEM_6, true),
	LOCATION(RC_KAK_BAZAAR_ITEM_7, true),
	LOCATION(RC_KAK_BAZAAR_ITEM_8, true),
}, {
	Entrance(RR_KAKARIKO_VILLAGE, []{return true;}),
});
areaTable[RR_KAK_SHOOTING_GALLERY] = Region("Kak Shooting Gallery", SCENE_SHOOTING_GALLERY, false, {}, {}, {
	LOCATION(RC_KAK_SHOOTING_GALLERY_REWARD, (logic->HasItem(RG_CHILD_WALLET) && (logic->IsAdult && logic->CanUse(RG_FAIRY_BOW)))),
}, {
	Entrance(RR_KAKARIKO_VILLAGE, []{return true;}),
});
areaTable[RR_KAK_POTION_SHOP_FRONT] = Region("Kak Potion Shop Front", SCENE_POTION_SHOP_KAKARIKO, false, {}, {}, {
	LOCATION(RC_KAK_POTION_SHOP_ITEM_1, logic->IsAdult),
	LOCATION(RC_KAK_POTION_SHOP_ITEM_2, logic->IsAdult),
	LOCATION(RC_KAK_POTION_SHOP_ITEM_3, logic->IsAdult),
	LOCATION(RC_KAK_POTION_SHOP_ITEM_4, logic->IsAdult),
	LOCATION(RC_KAK_POTION_SHOP_ITEM_5, logic->IsAdult),
	LOCATION(RC_KAK_POTION_SHOP_ITEM_6, logic->IsAdult),
	LOCATION(RC_KAK_POTION_SHOP_ITEM_7, logic->IsAdult),
	LOCATION(RC_KAK_POTION_SHOP_ITEM_8, logic->IsAdult),
}, {
	Entrance(RR_KAKARIKO_VILLAGE, []{return true;}),
	Entrance(RR_KAK_POTION_SHOP_BACK, []{return logic->IsAdult;}),
});
areaTable[RR_KAK_POTION_SHOP_BACK] = Region("Kak Potion Shop Back", SCENE_POTION_SHOP_KAKARIKO, false, {}, {}, {}, {
	Entrance(RR_KAK_BACKYARD, []{return logic->IsAdult;}),
	Entrance(RR_KAK_POTION_SHOP_FRONT, []{return true;}),
});
areaTable[RR_KAK_WATCHTOWER] = Region("Kak Watchtower", SCENE_KAKARIKO_VILLAGE, true, {RA_KAKARIKO_VILLAGE}, {}, {
	LOCATION(RC_KAK_GS_WATCHTOWER, (logic->IsChild && (logic->CanUse(RG_DINS_FIRE) && logic->CanGetNightTimeGS()))),
}, {
	Entrance(RR_KAKARIKO_VILLAGE, []{return true;}),
	Entrance(RR_KAK_ROOFTOP, []{return ((bool)ctx->GetTrickOption(RT_KAK_MAN_ON_ROOF) && logic->IsChild);}),
});
areaTable[RR_KAK_ROOFTOP] = Region("Kak Rooftop", SCENE_KAKARIKO_VILLAGE, true, {RA_KAKARIKO_VILLAGE}, {}, {
	LOCATION(RC_KAK_MAN_ON_ROOF, true),
}, {
	Entrance(RR_KAK_BACKYARD, []{return true;}),
	Entrance(RR_KAKARIKO_VILLAGE, []{return true;}),
});
areaTable[RR_KAK_IMPAS_ROOFTOP] = Region("Kak Impas Rooftop", SCENE_KAKARIKO_VILLAGE, true, {RA_KAKARIKO_VILLAGE}, {}, {
	LOCATION(RC_KAK_GS_ABOVE_IMPAS_HOUSE, (logic->IsAdult && (logic->CanGetNightTimeGS() && logic->CanKillEnemy(RE_GOLD_SKULLTULA)))),
}, {
	Entrance(RR_KAK_IMPAS_LEDGE, []{return true;}),
	Entrance(RR_KAKARIKO_VILLAGE, []{return true;}),
});
areaTable[RR_KAK_BEHIND_GATE] = Region("Kak Behind Gate", SCENE_KAKARIKO_VILLAGE, true, {RA_KAKARIKO_VILLAGE}, {}, {}, {
	Entrance(RR_KAKARIKO_VILLAGE, []{return (logic->IsAdult || ((bool)ctx->GetTrickOption(RT_VISIBLE_COLLISION) || logic->KakarikoVillageGateOpen));}),
	Entrance(RR_DEATH_MOUNTAIN_TRAIL, []{return true;}),
});
areaTable[RR_KAK_BACKYARD] = Region("Kak Backyard", SCENE_KAKARIKO_VILLAGE, true, {RA_KAKARIKO_VILLAGE}, {}, {
	LOCATION(RC_KAK_NEAR_MEDICINE_SHOP_POT_1, (logic->IsChild && logic->CanBreakPots())),
	LOCATION(RC_KAK_NEAR_MEDICINE_SHOP_POT_2, (logic->IsChild && logic->CanBreakPots())),
}, {
	Entrance(RR_KAKARIKO_VILLAGE, []{return true;}),
	Entrance(RR_KAK_OPEN_GROTTO, []{return true;}),
	Entrance(RR_KAK_ODD_POTION_BUILDING, []{return (logic->IsAdult && logic->CanOpenOverworldDoor(RG_GRANNYS_POTION_SHOP_KEY));}),
	Entrance(RR_KAK_POTION_SHOP_BACK, []{return (logic->IsAdult && (logic->AtDay && logic->CanOpenOverworldDoor(RG_KAK_POTION_SHOP_KEY)));}),
});
areaTable[RR_KAK_WELL] = Region("Kak Well", SCENE_KAKARIKO_VILLAGE, true, {RA_KAKARIKO_VILLAGE}, {}, {}, {
	Entrance(RR_KAKARIKO_VILLAGE, []{return (logic->IsAdult || (logic->HasItem(RG_BRONZE_SCALE) || logic->DrainWell));}),
	Entrance(RR_BOTTOM_OF_THE_WELL_ENTRYWAY, []{return (logic->IsChild || (logic->DrainWell && ctx->GetOption(RSK_SHUFFLE_DUNGEON_ENTRANCES).IsNot(RO_DUNGEON_ENTRANCE_SHUFFLE_OFF)));}),
});
areaTable[RR_KAK_ODD_POTION_BUILDING] = Region("Kak Granny's Potion Shop", SCENE_POTION_SHOP_GRANNY, false, {}, {}, {
	LOCATION(RC_KAK_TRADE_ODD_MUSHROOM, (logic->IsAdult && logic->CanUse(RG_ODD_MUSHROOM))),
	LOCATION(RC_KAK_GRANNYS_SHOP, (logic->IsAdult && (logic->CanUse(RG_ODD_MUSHROOM) || logic->TradeQuestStep(RG_ODD_MUSHROOM)))),
}, {
	Entrance(RR_KAK_BACKYARD, []{return true;}),
});
areaTable[RR_KAK_REDEAD_GROTTO] = Region("Kak Redead Grotto", SCENE_GROTTOS, false, {}, {}, {
	LOCATION(RC_KAK_REDEAD_GROTTO_CHEST, logic->CanKillEnemy(RE_REDEAD, ED_CLOSE, true, 2)),
}, {
	Entrance(RR_KAKARIKO_VILLAGE, []{return true;}),
});
areaTable[RR_KAK_OPEN_GROTTO] = Region("Kak Open Grotto", SCENE_GROTTOS, false, {}, {
	EventAccess(&logic->GossipStoneFairy, []{return logic->CallGossipFairy();}),
	EventAccess(&logic->ButterflyFairy, []{return logic->CanUse(RG_STICKS);}),
	EventAccess(&logic->BugShrub, []{return logic->CanCutShrubs();}),
	EventAccess(&logic->LoneFish, []{return true;}),
}, {
	LOCATION(RC_KAK_OPEN_GROTTO_CHEST, true),
	LOCATION(RC_KAK_OPEN_GROTTO_FISH, logic->HasBottle()),
	LOCATION(RC_KAK_OPEN_GROTTO_GOSSIP_STONE_FAIRY, logic->CallGossipFairy()),
	LOCATION(RC_KAK_OPEN_GROTTO_GOSSIP_STONE_FAIRY_BIG, logic->CanUse(RG_SONG_OF_STORMS)),
	LOCATION(RC_KAK_OPEN_GROTTO_GOSSIP_STONE, true),
	LOCATION(RC_KAK_OPEN_GROTTO_BEEHIVE_LEFT, logic->CanBreakLowerBeehives()),
	LOCATION(RC_KAK_OPEN_GROTTO_BEEHIVE_RIGHT, logic->CanBreakLowerBeehives()),
	LOCATION(RC_KAK_OPEN_GROTTO_GRASS_1, logic->CanCutShrubs()),
	LOCATION(RC_KAK_OPEN_GROTTO_GRASS_2, logic->CanCutShrubs()),
	LOCATION(RC_KAK_OPEN_GROTTO_GRASS_3, logic->CanCutShrubs()),
	LOCATION(RC_KAK_OPEN_GROTTO_GRASS_4, logic->CanCutShrubs()),
}, {
	Entrance(RR_KAK_BACKYARD, []{return true;}),
});
areaTable[RR_THE_GRAVEYARD] = Region("The Graveyard", SCENE_GRAVEYARD, false, {RA_THE_GRAVEYARD}, {
	EventAccess(&logic->ButterflyFairy, []{return (logic->CanUse(RG_STICKS) && logic->AtDay);}),
	EventAccess(&logic->BeanPlantFairy, []{return (logic->IsChild && (logic->CanUse(RG_MAGIC_BEAN) && logic->CanUse(RG_SONG_OF_STORMS)));}),
	EventAccess(&logic->BugRock, []{return true;}),
	EventAccess(&logic->BorrowBunnyHood, []{return (logic->IsChild && (logic->AtDay && (logic->BorrowSpookyMask && logic->HasItem(RG_CHILD_WALLET))));}),
}, {
	LOCATION(RC_GRAVEYARD_FREESTANDING_POH, ((((logic->IsAdult && CanPlantBean(RR_THE_GRAVEYARD)) || logic->CanUse(RG_LONGSHOT)) && logic->CanBreakCrates()) || ((bool)ctx->GetTrickOption(RT_GY_POH) && logic->CanUse(RG_BOOMERANG)))),
	LOCATION(RC_GRAVEYARD_DAMPE_GRAVEDIGGING_TOUR, (logic->HasItem(RG_CHILD_WALLET) && (logic->IsChild && logic->AtNight))),
	LOCATION(RC_GRAVEYARD_GS_WALL, (logic->IsChild && (logic->HookshotOrBoomerang() && (logic->AtNight && logic->CanGetNightTimeGS())))),
	LOCATION(RC_GRAVEYARD_GS_BEAN_PATCH, (logic->CanSpawnSoilSkull() && logic->CanAttack())),
	LOCATION(RC_GRAVEYARD_BEAN_SPROUT_FAIRY_1, (logic->IsChild && (logic->CanUse(RG_MAGIC_BEAN) && logic->CanUse(RG_SONG_OF_STORMS)))),
	LOCATION(RC_GRAVEYARD_BEAN_SPROUT_FAIRY_2, (logic->IsChild && (logic->CanUse(RG_MAGIC_BEAN) && logic->CanUse(RG_SONG_OF_STORMS)))),
	LOCATION(RC_GRAVEYARD_BEAN_SPROUT_FAIRY_3, (logic->IsChild && (logic->CanUse(RG_MAGIC_BEAN) && logic->CanUse(RG_SONG_OF_STORMS)))),
	LOCATION(RC_GY_GRASS_1, logic->CanCutShrubs()),
	LOCATION(RC_GY_GRASS_2, logic->CanCutShrubs()),
	LOCATION(RC_GY_GRASS_3, logic->CanCutShrubs()),
	LOCATION(RC_GY_GRASS_4, logic->CanCutShrubs()),
	LOCATION(RC_GY_GRASS_5, logic->CanCutShrubs()),
	LOCATION(RC_GY_GRASS_6, logic->CanCutShrubs()),
	LOCATION(RC_GY_GRASS_7, logic->CanCutShrubs()),
	LOCATION(RC_GY_GRASS_8, logic->CanCutShrubs()),
	LOCATION(RC_GY_GRASS_9, logic->CanCutShrubs()),
	LOCATION(RC_GY_GRASS_10, logic->CanCutShrubs()),
	LOCATION(RC_GY_GRASS_11, logic->CanCutShrubs()),
	LOCATION(RC_GY_GRASS_12, logic->CanCutShrubs()),
	LOCATION(RC_GRAVEYARD_CRATE, (((logic->IsAdult && CanPlantBean(RR_THE_GRAVEYARD)) || logic->CanUse(RG_LONGSHOT)) && logic->CanBreakCrates())),
}, {
	Entrance(RR_GRAVEYARD_SHIELD_GRAVE, []{return (logic->IsAdult || logic->AtNight);}),
	Entrance(RR_GRAVEYARD_COMPOSERS_GRAVE, []{return logic->CanUse(RG_ZELDAS_LULLABY);}),
	Entrance(RR_GRAVEYARD_HEART_PIECE_GRAVE, []{return (logic->IsAdult || logic->AtNight);}),
	Entrance(RR_GRAVEYARD_DAMPES_GRAVE, []{return logic->IsAdult;}),
	Entrance(RR_GRAVEYARD_DAMPES_HOUSE, []{return (logic->IsAdult && logic->CanOpenOverworldDoor(RG_DAMPES_HUT_KEY));}),
	Entrance(RR_KAKARIKO_VILLAGE, []{return true;}),
	Entrance(RR_GRAVEYARD_WARP_PAD_REGION, []{return false;}),
});
areaTable[RR_GRAVEYARD_DAMPES_GRAVE] = Region("Graveyard Dampes Grave", SCENE_WINDMILL_AND_DAMPES_GRAVE, false, {}, {
	EventAccess(&logic->NutPot, []{return true;}),
	EventAccess(&logic->DampesWindmillAccess, []{return (logic->IsAdult && logic->CanUse(RG_SONG_OF_TIME));}),
}, {
	LOCATION(RC_GRAVEYARD_HOOKSHOT_CHEST, true),
	LOCATION(RC_GRAVEYARD_DAMPE_RACE_FREESTANDING_POH, (logic->IsAdult || (bool)ctx->GetTrickOption(RT_GY_CHILD_DAMPE_RACE_POH))),
	LOCATION(RC_GY_DAMPES_GRAVE_POT_1, logic->CanBreakPots()),
	LOCATION(RC_GY_DAMPES_GRAVE_POT_2, logic->CanBreakPots()),
	LOCATION(RC_GY_DAMPES_GRAVE_POT_3, logic->CanBreakPots()),
	LOCATION(RC_GY_DAMPES_GRAVE_POT_4, logic->CanBreakPots()),
	LOCATION(RC_GY_DAMPES_GRAVE_POT_5, logic->CanBreakPots()),
	LOCATION(RC_GY_DAMPES_GRAVE_POT_6, logic->CanBreakPots()),
	LOCATION(RC_GRAVEYARD_DAMPE_RACE_RUPEE_1, true),
	LOCATION(RC_GRAVEYARD_DAMPE_RACE_RUPEE_2, true),
	LOCATION(RC_GRAVEYARD_DAMPE_RACE_RUPEE_3, true),
	LOCATION(RC_GRAVEYARD_DAMPE_RACE_RUPEE_4, true),
	LOCATION(RC_GRAVEYARD_DAMPE_RACE_RUPEE_5, true),
	LOCATION(RC_GRAVEYARD_DAMPE_RACE_RUPEE_6, true),
	LOCATION(RC_GRAVEYARD_DAMPE_RACE_RUPEE_7, true),
	LOCATION(RC_GRAVEYARD_DAMPE_RACE_RUPEE_8, true),
}, {
	Entrance(RR_THE_GRAVEYARD, []{return true;}),
	Entrance(RR_KAK_WINDMILL, []{return (logic->IsAdult && logic->CanUse(RG_SONG_OF_TIME));}, "", false),
});
areaTable[RR_GRAVEYARD_DAMPES_HOUSE] = Region("Graveyard Dampes House", SCENE_GRAVEKEEPERS_HUT, false, {}, {}, {
	LOCATION(RC_DAMPE_HINT, logic->IsAdult),
}, {
	Entrance(RR_THE_GRAVEYARD, []{return true;}),
});
areaTable[RR_GRAVEYARD_SHIELD_GRAVE] = Region("Graveyard Shield Grave", SCENE_GRAVE_WITH_FAIRYS_FOUNTAIN, false, {}, {}, {
	LOCATION(RC_GRAVEYARD_SHIELD_GRAVE_CHEST, true),
}, {
	Entrance(RR_THE_GRAVEYARD, []{return true;}),
	Entrance(RR_GRAVEYARD_SHIELD_GRAVE_BACK, []{return Here(RR_GRAVEYARD_SHIELD_GRAVE, []{return logic->CanBreakMudWalls();});}),
});
areaTable[RR_GRAVEYARD_SHIELD_GRAVE_BACK] = Region("Graveyard Shield Grave Back", SCENE_GRAVE_WITH_FAIRYS_FOUNTAIN, false, {}, {}, {
	LOCATION(RC_GRAVEYARD_SHIELD_GRAVE_FAIRY_1, true),
	LOCATION(RC_GRAVEYARD_SHIELD_GRAVE_FAIRY_2, true),
	LOCATION(RC_GRAVEYARD_SHIELD_GRAVE_FAIRY_3, true),
	LOCATION(RC_GRAVEYARD_SHIELD_GRAVE_FAIRY_4, true),
	LOCATION(RC_GRAVEYARD_SHIELD_GRAVE_FAIRY_5, true),
	LOCATION(RC_GRAVEYARD_SHIELD_GRAVE_FAIRY_6, true),
	LOCATION(RC_GRAVEYARD_SHIELD_GRAVE_FAIRY_7, true),
	LOCATION(RC_GRAVEYARD_SHIELD_GRAVE_FAIRY_8, true),
}, {
	Entrance(RR_GRAVEYARD_SHIELD_GRAVE, []{return true;}),
});
areaTable[RR_GRAVEYARD_COMPOSERS_GRAVE] = Region("Graveyard Composers Grave", SCENE_ROYAL_FAMILYS_TOMB, false, {}, {}, {
	LOCATION(RC_GRAVEYARD_ROYAL_FAMILYS_TOMB_CHEST, logic->HasFireSource()),
	LOCATION(RC_SONG_FROM_ROYAL_FAMILYS_TOMB, (logic->CanUseProjectile() || logic->CanJumpslash())),
	LOCATION(RC_GRAVEYARD_ROYAL_FAMILYS_TOMB_SUN_FAIRY, logic->CanUse(RG_SUNS_SONG)),
}, {
	Entrance(RR_THE_GRAVEYARD, []{return true;}),
});
areaTable[RR_GRAVEYARD_HEART_PIECE_GRAVE] = Region("Graveyard Heart Piece Grave", SCENE_REDEAD_GRAVE, false, {}, {}, {
	LOCATION(RC_GRAVEYARD_HEART_PIECE_GRAVE_CHEST, logic->CanUse(RG_SUNS_SONG)),
}, {
	Entrance(RR_THE_GRAVEYARD, []{return true;}),
});
areaTable[RR_GRAVEYARD_WARP_PAD_REGION] = Region("Graveyard Warp Pad Region", SCENE_GRAVEYARD, false, {RA_THE_GRAVEYARD}, {
	EventAccess(&logic->GossipStoneFairy, []{return logic->CallGossipFairyExceptSuns();}),
}, {
	LOCATION(RC_GRAVEYARD_GOSSIP_STONE_FAIRY, logic->CallGossipFairyExceptSuns()),
	LOCATION(RC_GRAVEYARD_GOSSIP_STONE_FAIRY_BIG, logic->CanUse(RG_SONG_OF_STORMS)),
	LOCATION(RC_GRAVEYARD_GOSSIP_STONE, true),
}, {
	Entrance(RR_THE_GRAVEYARD, []{return true;}),
	Entrance(RR_SHADOW_TEMPLE_ENTRYWAY, []{return (logic->CanUse(RG_DINS_FIRE) || ((bool)ctx->GetTrickOption(RT_GY_SHADOW_FIRE_ARROWS) && (logic->IsAdult && logic->CanUse(RG_FIRE_ARROWS))));}),
});
areaTable[RR_DEATH_MOUNTAIN_TRAIL] = Region("Death Mountain", SCENE_DEATH_MOUNTAIN_TRAIL, true, {RA_DEATH_MOUNTAIN_TRAIL}, {
	EventAccess(&logic->BeanPlantFairy, []{return (logic->IsChild && (logic->CanUse(RG_MAGIC_BEAN) && (logic->CanUse(RG_SONG_OF_STORMS) && (logic->HasExplosives() || logic->HasItem(RG_GORONS_BRACELET)))));}),
}, {
	LOCATION(RC_DMT_CHEST, (logic->BlastOrSmash() || ((bool)ctx->GetTrickOption(RT_DMT_BOMBABLE) && (logic->IsChild && logic->HasItem(RG_GORONS_BRACELET))))),
	LOCATION(RC_DMT_FREESTANDING_POH, (logic->TakeDamage() || (logic->CanUse(RG_HOVER_BOOTS) || (logic->IsAdult && (CanPlantBean(RR_DEATH_MOUNTAIN_TRAIL) && (logic->HasExplosives() || logic->HasItem(RG_GORONS_BRACELET))))))),
	LOCATION(RC_DMT_GS_BEAN_PATCH, (logic->CanSpawnSoilSkull() && (logic->HasExplosives() || (logic->HasItem(RG_GORONS_BRACELET) || ((bool)ctx->GetTrickOption(RT_DMT_SOIL_GS) && ((logic->TakeDamage() || logic->CanUse(RG_HOVER_BOOTS)) && logic->CanUse(RG_BOOMERANG))))))),
	LOCATION(RC_DMT_GS_NEAR_KAK, logic->BlastOrSmash()),
	LOCATION(RC_DMT_GS_ABOVE_DODONGOS_CAVERN, (logic->IsAdult && (logic->AtNight && ((logic->CanUse(RG_MEGATON_HAMMER) || (((bool)ctx->GetTrickOption(RT_DMT_HOOKSHOT_LOWER_GS) && logic->CanUse(RG_HOOKSHOT)) || (((bool)ctx->GetTrickOption(RT_DMT_BEAN_LOWER_GS) && CanPlantBean(RR_DEATH_MOUNTAIN_TRAIL)) || (((bool)ctx->GetTrickOption(RT_DMT_HOVERS_LOWER_GS) && logic->CanUse(RG_HOVER_BOOTS)) || (bool)ctx->GetTrickOption(RT_DMT_JS_LOWER_GS))))) && logic->CanGetNightTimeGS())))),
	LOCATION(RC_DMT_BLUE_RUPEE, (logic->IsChild && logic->BlastOrSmash())),
	LOCATION(RC_DMT_RED_RUPEE, (logic->IsChild && logic->BlastOrSmash())),
	LOCATION(RC_DMT_BEAN_SPROUT_FAIRY_1, (logic->IsChild && (logic->CanUse(RG_MAGIC_BEAN) && (logic->CanUse(RG_SONG_OF_STORMS) && (logic->HasExplosives() || logic->HasItem(RG_GORONS_BRACELET)))))),
	LOCATION(RC_DMT_BEAN_SPROUT_FAIRY_2, (logic->IsChild && (logic->CanUse(RG_MAGIC_BEAN) && (logic->CanUse(RG_SONG_OF_STORMS) && (logic->HasExplosives() || logic->HasItem(RG_GORONS_BRACELET)))))),
	LOCATION(RC_DMT_BEAN_SPROUT_FAIRY_3, (logic->IsChild && (logic->CanUse(RG_MAGIC_BEAN) && (logic->CanUse(RG_SONG_OF_STORMS) && (logic->HasExplosives() || logic->HasItem(RG_GORONS_BRACELET)))))),
	LOCATION(RC_DMT_FLAG_SUN_FAIRY, logic->CanUse(RG_SUNS_SONG)),
}, {
	Entrance(RR_KAK_BEHIND_GATE, []{return true;}),
	Entrance(RR_GORON_CITY, []{return true;}),
	Entrance(RR_DEATH_MOUNTAIN_SUMMIT, []{return (Here(RR_DEATH_MOUNTAIN_TRAIL, []{return logic->BlastOrSmash();}) || (logic->IsAdult && ((CanPlantBean(RR_DEATH_MOUNTAIN_TRAIL) && logic->HasItem(RG_GORONS_BRACELET)) || (logic->CanUse(RG_HOVER_BOOTS) && (bool)ctx->GetTrickOption(RT_DMT_CLIMB_HOVERS)))));}),
	Entrance(RR_DODONGOS_CAVERN_ENTRYWAY, []{return (logic->HasExplosives() || (logic->HasItem(RG_GORONS_BRACELET) || logic->IsAdult));}),
	Entrance(RR_DMT_STORMS_GROTTO, []{return logic->CanOpenStormsGrotto();}),
});
areaTable[RR_DEATH_MOUNTAIN_SUMMIT] = Region("Death Mountain Summit", SCENE_DEATH_MOUNTAIN_TRAIL, true, {RA_DEATH_MOUNTAIN_TRAIL}, {
	EventAccess(&logic->GossipStoneFairy, []{return logic->CallGossipFairy();}),
	EventAccess(&logic->BugRock, []{return logic->IsChild;}),
}, {
	LOCATION(RC_DMT_TRADE_BROKEN_SWORD, (logic->IsAdult && logic->CanUse(RG_BROKEN_SWORD))),
	LOCATION(RC_DMT_TRADE_EYEDROPS, (logic->IsAdult && logic->CanUse(RG_EYEDROPS))),
	LOCATION(RC_DMT_TRADE_CLAIM_CHECK, (logic->IsAdult && logic->CanUse(RG_CLAIM_CHECK))),
	LOCATION(RC_DMT_GS_FALLING_ROCKS_PATH, (logic->IsAdult && (logic->AtNight && ((logic->CanUse(RG_MEGATON_HAMMER) || (bool)ctx->GetTrickOption(RT_DMT_UPPER_GS)) && logic->CanGetNightTimeGS())))),
	LOCATION(RC_DMT_GOSSIP_STONE_FAIRY, logic->CallGossipFairy()),
	LOCATION(RC_DMT_GOSSIP_STONE_FAIRY_BIG, logic->CanUse(RG_SONG_OF_STORMS)),
	LOCATION(RC_DMT_GOSSIP_STONE, true),
}, {
	Entrance(RR_DEATH_MOUNTAIN_TRAIL, []{return true;}),
	Entrance(RR_DMC_UPPER_LOCAL, []{return true;}),
	Entrance(RR_DMT_OWL_FLIGHT, []{return logic->IsChild;}),
	Entrance(RR_DMT_COW_GROTTO, []{return Here(RR_DEATH_MOUNTAIN_SUMMIT, []{return logic->BlastOrSmash();});}),
	Entrance(RR_DMT_GREAT_FAIRY_FOUNTAIN, []{return Here(RR_DEATH_MOUNTAIN_SUMMIT, []{return logic->BlastOrSmash();});}),
});
areaTable[RR_DMT_OWL_FLIGHT] = Region("DMT Owl Flight", SCENE_DEATH_MOUNTAIN_TRAIL, true, {RA_DEATH_MOUNTAIN_TRAIL}, {}, {}, {
	Entrance(RR_KAK_IMPAS_ROOFTOP, []{return true;}),
});
areaTable[RR_DMT_GREAT_FAIRY_FOUNTAIN] = Region("DMT Great Fairy Fountain", SCENE_GREAT_FAIRYS_FOUNTAIN_MAGIC, false, {}, {}, {
	LOCATION(RC_DMT_GREAT_FAIRY_REWARD, logic->CanUse(RG_ZELDAS_LULLABY)),
}, {
	Entrance(RR_DEATH_MOUNTAIN_SUMMIT, []{return true;}),
});
areaTable[RR_DMT_COW_GROTTO] = Region("DMT Cow Grotto", SCENE_GROTTOS, false, {}, {}, {
	LOCATION(RC_DMT_COW_GROTTO_COW, logic->CanUse(RG_EPONAS_SONG)),
	LOCATION(RC_DMT_COW_GROTTO_BEEHIVE, logic->CanBreakLowerBeehives()),
	LOCATION(RC_DMT_COW_GROTTO_LEFT_HEART, true),
	LOCATION(RC_DMT_COW_GROTTO_MIDDLE_LEFT_HEART, true),
	LOCATION(RC_DMT_COW_GROTTO_MIDDLE_RIGHT_HEART, true),
	LOCATION(RC_DMT_COW_GROTTO_RIGHT_HEART, true),
	LOCATION(RC_DMT_COW_GROTTO_RUPEE_1, true),
	LOCATION(RC_DMT_COW_GROTTO_RUPEE_2, true),
	LOCATION(RC_DMT_COW_GROTTO_RUPEE_3, true),
	LOCATION(RC_DMT_COW_GROTTO_RUPEE_4, true),
	LOCATION(RC_DMT_COW_GROTTO_RUPEE_5, true),
	LOCATION(RC_DMT_COW_GROTTO_RUPEE_6, true),
	LOCATION(RC_DMT_COW_GROTTO_RED_RUPEE, true),
	LOCATION(RC_DMT_COW_GROTTO_STORMS_FAIRY, logic->CanUse(RG_SONG_OF_STORMS)),
	LOCATION(RC_DMT_COW_GROTTO_GRASS_1, logic->CanCutShrubs()),
	LOCATION(RC_DMT_COW_GROTTO_GRASS_2, logic->CanCutShrubs()),
}, {
	Entrance(RR_DEATH_MOUNTAIN_SUMMIT, []{return true;}),
});
areaTable[RR_DMT_STORMS_GROTTO] = Region("DMT Storms Grotto", SCENE_GROTTOS, false, {}, {
	EventAccess(&logic->GossipStoneFairy, []{return logic->CallGossipFairy();}),
	EventAccess(&logic->ButterflyFairy, []{return logic->CanUse(RG_STICKS);}),
	EventAccess(&logic->BugShrub, []{return logic->CanCutShrubs();}),
	EventAccess(&logic->LoneFish, []{return true;}),
}, {
	LOCATION(RC_DMT_STORMS_GROTTO_CHEST, true),
	LOCATION(RC_DMT_STORMS_GROTTO_FISH, logic->HasBottle()),
	LOCATION(RC_DMT_STORMS_GROTTO_GOSSIP_STONE_FAIRY, logic->CallGossipFairy()),
	LOCATION(RC_DMT_STORMS_GROTTO_GOSSIP_STONE_FAIRY_BIG, logic->CanUse(RG_SONG_OF_STORMS)),
	LOCATION(RC_DMT_STORMS_GROTTO_GOSSIP_STONE, true),
	LOCATION(RC_DMT_STORMS_GROTTO_BEEHIVE_LEFT, logic->CanBreakLowerBeehives()),
	LOCATION(RC_DMT_STORMS_GROTTO_BEEHIVE_RIGHT, logic->CanBreakLowerBeehives()),
	LOCATION(RC_DMT_STORMS_GROTTO_GRASS_1, logic->CanCutShrubs()),
	LOCATION(RC_DMT_STORMS_GROTTO_GRASS_2, logic->CanCutShrubs()),
	LOCATION(RC_DMT_STORMS_GROTTO_GRASS_3, logic->CanCutShrubs()),
	LOCATION(RC_DMT_STORMS_GROTTO_GRASS_4, logic->CanCutShrubs()),
}, {
	Entrance(RR_DEATH_MOUNTAIN_TRAIL, []{return true;}),
});
areaTable[RR_GORON_CITY] = Region("Goron City", SCENE_GORON_CITY, false, {RA_GORON_CITY}, {
	EventAccess(&logic->GossipStoneFairy, []{return logic->CallGossipFairyExceptSuns();}),
	EventAccess(&logic->StickPot, []{return logic->IsChild;}),
	EventAccess(&logic->BugRock, []{return (logic->BlastOrSmash() || logic->CanUse(RG_SILVER_GAUNTLETS));}),
	EventAccess(&logic->GoronCityChildFire, []{return (logic->IsChild && logic->CanUse(RG_DINS_FIRE));}),
	EventAccess(&logic->GCWoodsWarpOpen, []{return (logic->CanDetonateUprightBombFlower() || (logic->CanUse(RG_MEGATON_HAMMER) || logic->GoronCityChildFire));}),
	EventAccess(&logic->GCDaruniasDoorOpenChild, []{return (logic->IsChild && logic->CanUse(RG_ZELDAS_LULLABY));}),
	EventAccess(&logic->StopGCRollingGoronAsAdult, []{return (logic->IsAdult && (logic->HasItem(RG_GORONS_BRACELET) || (logic->HasExplosives() || (logic->CanUse(RG_FAIRY_BOW) || ((bool)ctx->GetTrickOption(RT_GC_LINK_GORON_DINS) && (logic->CanUse(RG_DINS_FIRE) || ((bool)ctx->GetTrickOption(RT_BLUE_FIRE_MUD_WALLS) && logic->CanUse(RG_BOTTLE_WITH_BLUE_FIRE))))))));}),
}, {
	LOCATION(RC_GC_MAZE_LEFT_CHEST, (logic->CanUse(RG_MEGATON_HAMMER) || (logic->CanUse(RG_SILVER_GAUNTLETS) || ((bool)ctx->GetTrickOption(RT_GC_LEFTMOST) && (logic->HasExplosives() && logic->CanUse(RG_HOVER_BOOTS)))))),
	LOCATION(RC_GC_MAZE_CENTER_CHEST, (logic->BlastOrSmash() || logic->CanUse(RG_SILVER_GAUNTLETS))),
	LOCATION(RC_GC_MAZE_RIGHT_CHEST, (logic->BlastOrSmash() || logic->CanUse(RG_SILVER_GAUNTLETS))),
	LOCATION(RC_GC_POT_FREESTANDING_POH, (logic->IsChild && (logic->GoronCityChildFire && (logic->CanUse(RG_BOMB_BAG) || ((logic->HasItem(RG_GORONS_BRACELET) && (bool)ctx->GetTrickOption(RT_GC_POT_STRENGTH)) || (logic->CanUse(RG_BOMBCHU_5) && (bool)ctx->GetTrickOption(RT_GC_POT))))))),
	LOCATION(RC_GC_ROLLING_GORON_AS_CHILD, (logic->IsChild && (logic->HasExplosives() || (logic->HasItem(RG_GORONS_BRACELET) && (bool)ctx->GetTrickOption(RT_GC_ROLLING_STRENGTH))))),
	LOCATION(RC_GC_ROLLING_GORON_AS_ADULT, logic->StopGCRollingGoronAsAdult),
	LOCATION(RC_GC_GS_BOULDER_MAZE, (logic->IsChild && logic->BlastOrSmash())),
	LOCATION(RC_GC_GS_CENTER_PLATFORM, (logic->IsAdult && logic->CanAttack())),
	LOCATION(RC_GC_MEDIGORON, (logic->IsAdult && (logic->CanBreakMudWalls() || logic->HasItem(RG_GORONS_BRACELET)))),
	LOCATION(RC_GC_MAZE_GOSSIP_STONE_FAIRY, ((logic->BlastOrSmash() || logic->CanUse(RG_SILVER_GAUNTLETS)) && logic->CallGossipFairyExceptSuns())),
	LOCATION(RC_GC_MAZE_GOSSIP_STONE_FAIRY_BIG, ((logic->BlastOrSmash() || logic->CanUse(RG_SILVER_GAUNTLETS)) && logic->CanUse(RG_SONG_OF_STORMS))),
	LOCATION(RC_GC_MAZE_GOSSIP_STONE, (logic->BlastOrSmash() || logic->CanUse(RG_SILVER_GAUNTLETS))),
	LOCATION(RC_GC_LOWER_STAIRCASE_POT_1, logic->CanBreakPots()),
	LOCATION(RC_GC_LOWER_STAIRCASE_POT_2, logic->CanBreakPots()),
	LOCATION(RC_GC_UPPER_STAIRCASE_POT_1, logic->CanBreakPots()),
	LOCATION(RC_GC_UPPER_STAIRCASE_POT_2, logic->CanBreakPots()),
	LOCATION(RC_GC_UPPER_STAIRCASE_POT_3, logic->CanBreakPots()),
	LOCATION(RC_GC_MAZE_CRATE, (logic->BlastOrSmash() || (logic->CanUse(RG_SILVER_GAUNTLETS) && logic->CanBreakCrates()))),
}, {
	Entrance(RR_DEATH_MOUNTAIN_TRAIL, []{return true;}),
	Entrance(RR_GC_MEDIGORON, []{return (logic->CanBreakMudWalls() || logic->HasItem(RG_GORONS_BRACELET));}),
	Entrance(RR_GC_WOODS_WARP, []{return logic->GCWoodsWarpOpen;}),
	Entrance(RR_GC_SHOP, []{return ((logic->IsAdult && logic->StopGCRollingGoronAsAdult) || (logic->IsChild && (logic->BlastOrSmash() || (logic->HasItem(RG_GORONS_BRACELET) || (logic->GoronCityChildFire || logic->CanUse(RG_FAIRY_BOW))))));}),
	Entrance(RR_GC_DARUNIAS_CHAMBER, []{return ((logic->IsAdult && logic->StopGCRollingGoronAsAdult) || (logic->IsChild && logic->GCDaruniasDoorOpenChild));}),
	Entrance(RR_GC_GROTTO_PLATFORM, []{return (logic->IsAdult && ((logic->CanUse(RG_SONG_OF_TIME) && ((logic->EffectiveHealth() > 2) || (logic->CanUse(RG_GORON_TUNIC) || (logic->CanUse(RG_LONGSHOT) || logic->CanUse(RG_NAYRUS_LOVE))))) || (((logic->EffectiveHealth() > 1) && (logic->CanUse(RG_GORON_TUNIC) && logic->CanUse(RG_HOOKSHOT))) || ((logic->CanUse(RG_NAYRUS_LOVE) && logic->CanUse(RG_HOOKSHOT)) || ((logic->EffectiveHealth() > 2) && (logic->CanUse(RG_HOOKSHOT) && (bool)ctx->GetTrickOption(RT_GC_GROTTO)))))));}),
});
areaTable[RR_GC_MEDIGORON] = Region("GC Medigoron", SCENE_GORON_CITY, false, {RA_GORON_CITY}, {}, {
	LOCATION(RC_GC_MEDIGORON_GOSSIP_STONE_FAIRY, logic->CallGossipFairyExceptSuns()),
	LOCATION(RC_GC_MEDIGORON_GOSSIP_STONE_FAIRY_BIG, logic->CanUse(RG_SONG_OF_STORMS)),
	LOCATION(RC_GC_MEDIGORON_GOSSIP_STONE, true),
	LOCATION(RC_GC_MEDIGORON_POT_1, logic->CanBreakPots()),
}, {
	Entrance(RR_GORON_CITY, []{return true;}),
});
areaTable[RR_GC_WOODS_WARP] = Region("GC Woods Warp", SCENE_GORON_CITY, false, {RA_GORON_CITY}, {
	EventAccess(&logic->GCWoodsWarpOpen, []{return (logic->BlastOrSmash() || logic->CanUse(RG_DINS_FIRE));}),
}, {}, {
	Entrance(RR_GORON_CITY, []{return logic->GCWoodsWarpOpen;}),
	Entrance(RR_THE_LOST_WOODS, []{return true;}),
});
areaTable[RR_GC_DARUNIAS_CHAMBER] = Region("GC Darunias Chamber", SCENE_GORON_CITY, false, {RA_GORON_CITY}, {
	EventAccess(&logic->GoronCityChildFire, []{return (logic->IsChild && logic->CanUse(RG_STICKS));}),
}, {
	LOCATION(RC_GC_DARUNIAS_JOY, (logic->IsChild && logic->CanUse(RG_SARIAS_SONG))),
	LOCATION(RC_GC_DARUNIA_POT_1, logic->CanBreakPots()),
	LOCATION(RC_GC_DARUNIA_POT_2, logic->CanBreakPots()),
	LOCATION(RC_GC_DARUNIA_POT_3, logic->CanBreakPots()),
}, {
	Entrance(RR_GORON_CITY, []{return true;}),
	Entrance(RR_DMC_LOWER_LOCAL, []{return logic->IsAdult;}),
});
areaTable[RR_GC_GROTTO_PLATFORM] = Region("GC Grotto Platform", SCENE_GORON_CITY, false, {RA_GORON_CITY}, {}, {}, {
	Entrance(RR_GC_GROTTO, []{return true;}),
	Entrance(RR_GORON_CITY, []{return ((logic->EffectiveHealth() > 2) || (logic->CanUse(RG_GORON_TUNIC) || (logic->CanUse(RG_NAYRUS_LOVE) || ((logic->IsChild || logic->CanUse(RG_SONG_OF_TIME)) && logic->CanUse(RG_LONGSHOT)))));}),
});
areaTable[RR_GC_SHOP] = Region("GC Shop", SCENE_GORON_SHOP, false, {}, {}, {
	LOCATION(RC_GC_SHOP_ITEM_1, true),
	LOCATION(RC_GC_SHOP_ITEM_2, true),
	LOCATION(RC_GC_SHOP_ITEM_3, true),
	LOCATION(RC_GC_SHOP_ITEM_4, true),
	LOCATION(RC_GC_SHOP_ITEM_5, true),
	LOCATION(RC_GC_SHOP_ITEM_6, true),
	LOCATION(RC_GC_SHOP_ITEM_7, true),
	LOCATION(RC_GC_SHOP_ITEM_8, true),
}, {
	Entrance(RR_GORON_CITY, []{return true;}),
});
areaTable[RR_GC_GROTTO] = Region("GC Grotto", SCENE_GROTTOS, false, {}, {}, {
	LOCATION(RC_GC_DEKU_SCRUB_GROTTO_LEFT, logic->CanStunDeku()),
	LOCATION(RC_GC_DEKU_SCRUB_GROTTO_RIGHT, logic->CanStunDeku()),
	LOCATION(RC_GC_DEKU_SCRUB_GROTTO_CENTER, logic->CanStunDeku()),
	LOCATION(RC_GC_GROTTO_BEEHIVE, logic->CanBreakUpperBeehives()),
}, {
	Entrance(RR_GC_GROTTO_PLATFORM, []{return true;}),
});
areaTable[RR_DMC_UPPER_LOCAL] = Region("DMC Upper Local", SCENE_DEATH_MOUNTAIN_CRATER, false, {RA_DEATH_MOUNTAIN_CRATER}, {
	EventAccess(&logic->GossipStoneFairy, []{return (logic->HasExplosives() && (logic->CallGossipFairyExceptSuns() && ((logic->FireTimer() >= 16) || (logic->Hearts() >= 3))));}),
}, {
	LOCATION(RC_DMC_WALL_FREESTANDING_POH, ((logic->FireTimer() >= 16) || (logic->Hearts() >= 3))),
	LOCATION(RC_DMC_GS_CRATE, (((logic->FireTimer() >= 8) || (logic->Hearts() >= 3)) && (logic->IsChild && (logic->CanAttack() && logic->CanBreakCrates())))),
	LOCATION(RC_DMC_GOSSIP_STONE_FAIRY, (logic->CallGossipFairyExceptSuns() && (logic->HasExplosives() && ((logic->FireTimer() >= 16) || (logic->Hearts() >= 3))))),
	LOCATION(RC_DMC_GOSSIP_STONE_FAIRY_BIG, (logic->CanUse(RG_SONG_OF_STORMS) && (logic->HasExplosives() && ((logic->FireTimer() >= 16) || (logic->Hearts() >= 3))))),
	LOCATION(RC_DMC_GOSSIP_STONE, (logic->HasExplosives() && ((logic->FireTimer() >= 16) || (logic->Hearts() >= 3)))),
	LOCATION(RC_DMC_CRATE, (((logic->FireTimer() >= 8) || (logic->Hearts() >= 3)) && (logic->IsChild && logic->CanBreakCrates()))),
}, {
	Entrance(RR_DMC_UPPER_NEARBY, []{return true;}),
	Entrance(RR_DMC_LADDER_AREA_NEARBY, []{return ((logic->FireTimer() >= 16) || (logic->Hearts() >= 3));}),
	Entrance(RR_DMC_CENTRAL_NEARBY, []{return (logic->IsAdult && (logic->CanUse(RG_GORON_TUNIC) && (logic->CanUse(RG_DISTANT_SCARECROW) && ((logic->EffectiveHealth() > 2) || ((logic->CanUse(RG_BOTTLE_WITH_FAIRY) && ctx->GetOption(RSK_SHUFFLE_DUNGEON_ENTRANCES).IsNot(RO_DUNGEON_ENTRANCE_SHUFFLE_OFF)) || logic->CanUse(RG_NAYRUS_LOVE))))));}),
	Entrance(RR_DMC_LOWER_NEARBY, []{return false;}),
	Entrance(RR_DMC_DISTANT_PLATFORM, []{return (((logic->FireTimer() >= 48) && (logic->Hearts() >= 2)) || (logic->Hearts() >= 3));}),
});
areaTable[RR_DMC_CENTRAL_LOCAL] = Region("DMC Central Local", SCENE_DEATH_MOUNTAIN_CRATER, false, {RA_DEATH_MOUNTAIN_CRATER}, {
	EventAccess(&logic->BeanPlantFairy, []{return (logic->IsChild && (logic->CanUse(RG_MAGIC_BEAN) && (logic->CanUse(RG_SONG_OF_STORMS) && ((logic->FireTimer() >= 8) || (logic->Hearts() >= 3)))));}),
}, {
	LOCATION(RC_DMC_GS_BEAN_PATCH, (((logic->FireTimer() >= 8) || (logic->Hearts() >= 3)) && (logic->CanSpawnSoilSkull() && logic->CanAttack()))),
	LOCATION(RC_DMC_NEAR_PLATFORM_RED_RUPEE, logic->IsChild),
	LOCATION(RC_DMC_MIDDLE_PLATFORM_RED_RUPEE, (logic->IsChild && ((logic->FireTimer() >= 8) || (logic->Hearts() >= 3)))),
	LOCATION(RC_DMC_MIDDLE_PLATFORM_BLUE_RUPEE_1, (logic->IsChild && ((logic->FireTimer() >= 8) || (logic->Hearts() >= 3)))),
	LOCATION(RC_DMC_MIDDLE_PLATFORM_BLUE_RUPEE_2, (logic->IsChild && ((logic->FireTimer() >= 8) || (logic->Hearts() >= 3)))),
	LOCATION(RC_DMC_MIDDLE_PLATFORM_BLUE_RUPEE_3, (logic->IsChild && ((logic->FireTimer() >= 8) || (logic->Hearts() >= 3)))),
	LOCATION(RC_DMC_MIDDLE_PLATFORM_BLUE_RUPEE_4, (logic->IsChild && ((logic->FireTimer() >= 8) || (logic->Hearts() >= 3)))),
	LOCATION(RC_DMC_MIDDLE_PLATFORM_BLUE_RUPEE_5, (logic->IsChild && ((logic->FireTimer() >= 8) || (logic->Hearts() >= 3)))),
	LOCATION(RC_DMC_MIDDLE_PLATFORM_BLUE_RUPEE_6, (logic->IsChild && ((logic->FireTimer() >= 8) || (logic->Hearts() >= 3)))),
	LOCATION(RC_DMC_BEAN_SPROUT_FAIRY_1, (logic->IsChild && (logic->CanUse(RG_MAGIC_BEAN) && (logic->CanUse(RG_SONG_OF_STORMS) && ((logic->FireTimer() >= 8) || (logic->Hearts() >= 3)))))),
	LOCATION(RC_DMC_BEAN_SPROUT_FAIRY_2, (logic->IsChild && (logic->CanUse(RG_MAGIC_BEAN) && (logic->CanUse(RG_SONG_OF_STORMS) && ((logic->FireTimer() >= 8) || (logic->Hearts() >= 3)))))),
	LOCATION(RC_DMC_BEAN_SPROUT_FAIRY_3, (logic->IsChild && (logic->CanUse(RG_MAGIC_BEAN) && (logic->CanUse(RG_SONG_OF_STORMS) && ((logic->FireTimer() >= 8) || (logic->Hearts() >= 3)))))),
}, {
	Entrance(RR_DMC_CENTRAL_NEARBY, []{return true;}),
	Entrance(RR_DMC_LOWER_NEARBY, []{return ((logic->IsAdult && CanPlantBean(RR_DMC_CENTRAL_LOCAL)) || (logic->CanUse(RG_HOVER_BOOTS) || logic->CanUse(RG_HOOKSHOT)));}),
	Entrance(RR_DMC_UPPER_NEARBY, []{return (logic->IsAdult && CanPlantBean(RR_DMC_CENTRAL_LOCAL));}),
	Entrance(RR_FIRE_TEMPLE_ENTRYWAY, []{return ((logic->IsChild && ((logic->Hearts() >= 3) && ctx->GetOption(RSK_SHUFFLE_DUNGEON_ENTRANCES).IsNot(RO_DUNGEON_ENTRANCE_SHUFFLE_OFF))) || (logic->IsAdult && (logic->FireTimer() >= 24)));}),
	Entrance(RR_DMC_DISTANT_PLATFORM, []{return ((logic->FireTimer() >= 48) && logic->CanUse(RG_DISTANT_SCARECROW));}),
});
areaTable[RR_DMC_LOWER_LOCAL] = Region("DMC Lower Local", SCENE_DEATH_MOUNTAIN_CRATER, false, {RA_DEATH_MOUNTAIN_CRATER}, {}, {}, {
	Entrance(RR_DMC_LOWER_NEARBY, []{return true;}),
	Entrance(RR_DMC_LADDER_AREA_NEARBY, []{return ((logic->FireTimer() >= 8) || (logic->Hearts() >= 3));}),
	Entrance(RR_DMC_CENTRAL_NEARBY, []{return ((logic->CanUse(RG_HOVER_BOOTS) || logic->CanUse(RG_HOOKSHOT)) && ((logic->FireTimer() >= 8) || (logic->Hearts() >= 3)));}),
	Entrance(RR_DMC_CENTRAL_LOCAL, []{return ((logic->CanUse(RG_HOVER_BOOTS) || (logic->CanUse(RG_HOOKSHOT) || (logic->IsAdult && (logic->CanShield() && (bool)ctx->GetTrickOption(RT_DMC_BOLERO_JUMP))))) && (logic->FireTimer() >= 24));}),
});
areaTable[RR_DMC_LOWER_NEARBY] = Region("DMC Lower Nearby", SCENE_DEATH_MOUNTAIN_CRATER, false, {RA_DEATH_MOUNTAIN_CRATER}, {}, {
	LOCATION(RC_DMC_NEAR_GC_POT_1, logic->CanBreakPots()),
	LOCATION(RC_DMC_NEAR_GC_POT_2, logic->CanBreakPots()),
	LOCATION(RC_DMC_NEAR_GC_POT_3, logic->CanBreakPots()),
	LOCATION(RC_DMC_NEAR_GC_POT_4, logic->CanBreakPots()),
}, {
	Entrance(RR_DMC_LOWER_LOCAL, []{return (logic->FireTimer() >= 48);}),
	Entrance(RR_GC_DARUNIAS_CHAMBER, []{return true;}),
	Entrance(RR_DMC_GREAT_FAIRY_FOUNTAIN, []{return logic->CanUse(RG_MEGATON_HAMMER);}),
	Entrance(RR_DMC_HAMMER_GROTTO, []{return (logic->IsAdult && logic->CanUse(RG_MEGATON_HAMMER));}),
});
areaTable[RR_DMC_UPPER_NEARBY] = Region("DMC Upper Nearby", SCENE_DEATH_MOUNTAIN_CRATER, false, {RA_DEATH_MOUNTAIN_CRATER}, {}, {}, {
	Entrance(RR_DMC_UPPER_LOCAL, []{return (logic->FireTimer() >= 48);}),
	Entrance(RR_DEATH_MOUNTAIN_SUMMIT, []{return true;}),
	Entrance(RR_DMC_UPPER_GROTTO, []{return Here(RR_DMC_UPPER_NEARBY, []{return (logic->BlastOrSmash() && ((logic->FireTimer() >= 8) || (logic->Hearts() >= 3)));});}),
});
areaTable[RR_DMC_CENTRAL_NEARBY] = Region("DMC Central Nearby", SCENE_DEATH_MOUNTAIN_CRATER, false, {RA_DEATH_MOUNTAIN_CRATER}, {}, {
	LOCATION(RC_DMC_VOLCANO_FREESTANDING_POH, (logic->IsAdult && ((logic->Hearts() >= 3) && (CanPlantBean(RR_DMC_CENTRAL_LOCAL) || ((bool)ctx->GetTrickOption(RT_DMC_HOVER_BEAN_POH) && logic->CanUse(RG_HOVER_BOOTS)))))),
	LOCATION(RC_SHEIK_IN_CRATER, (logic->IsAdult && ((logic->FireTimer() >= 8) || (logic->Hearts() >= 3)))),
}, {
	Entrance(RR_DMC_CENTRAL_LOCAL, []{return (logic->FireTimer() >= 48);}),
});
areaTable[RR_DMC_LADDER_AREA_NEARBY] = Region("DMC Ladder Region Nearby", SCENE_DEATH_MOUNTAIN_CRATER, false, {RA_DEATH_MOUNTAIN_CRATER}, {}, {
	LOCATION(RC_DMC_DEKU_SCRUB, (logic->IsChild && logic->CanStunDeku())),
}, {
	Entrance(RR_DMC_UPPER_NEARBY, []{return (logic->Hearts() >= 3);}),
	Entrance(RR_DMC_LOWER_NEARBY, []{return ((logic->Hearts() >= 3) && (logic->CanUse(RG_HOVER_BOOTS) || (((bool)ctx->GetTrickOption(RT_DMC_BOULDER_JS) && (logic->IsAdult && logic->CanUse(RG_MEGATON_HAMMER))) || ((bool)ctx->GetTrickOption(RT_DMC_BOULDER_SKIP) && logic->IsAdult))));}),
});
areaTable[RR_DMC_UPPER_GROTTO] = Region("DMC Upper Grotto", SCENE_GROTTOS, false, {}, {
	EventAccess(&logic->GossipStoneFairy, []{return logic->CallGossipFairy();}),
	EventAccess(&logic->ButterflyFairy, []{return logic->CanUse(RG_STICKS);}),
	EventAccess(&logic->BugShrub, []{return logic->CanCutShrubs();}),
	EventAccess(&logic->LoneFish, []{return true;}),
}, {
	LOCATION(RC_DMC_UPPER_GROTTO_CHEST, true),
	LOCATION(RC_DMC_UPPER_GROTTO_FISH, logic->HasBottle()),
	LOCATION(RC_DMC_UPPER_GROTTO_GOSSIP_STONE_FAIRY, logic->CallGossipFairy()),
	LOCATION(RC_DMC_UPPER_GROTTO_GOSSIP_STONE_FAIRY_BIG, logic->CanUse(RG_SONG_OF_STORMS)),
	LOCATION(RC_DMC_UPPER_GROTTO_GOSSIP_STONE, true),
	LOCATION(RC_DMC_UPPER_GROTTO_BEEHIVE_LEFT, logic->CanBreakLowerBeehives()),
	LOCATION(RC_DMC_UPPER_GROTTO_BEEHIVE_RIGHT, logic->CanBreakLowerBeehives()),
	LOCATION(RC_DMC_UPPER_GROTTO_GRASS_1, logic->CanCutShrubs()),
	LOCATION(RC_DMC_UPPER_GROTTO_GRASS_2, logic->CanCutShrubs()),
	LOCATION(RC_DMC_UPPER_GROTTO_GRASS_3, logic->CanCutShrubs()),
	LOCATION(RC_DMC_UPPER_GROTTO_GRASS_4, logic->CanCutShrubs()),
}, {
	Entrance(RR_DMC_UPPER_LOCAL, []{return true;}),
});
areaTable[RR_DMC_HAMMER_GROTTO] = Region("DMC Hammer Grotto", SCENE_GROTTOS, false, {}, {}, {
	LOCATION(RC_DMC_DEKU_SCRUB_GROTTO_LEFT, logic->CanStunDeku()),
	LOCATION(RC_DMC_DEKU_SCRUB_GROTTO_RIGHT, logic->CanStunDeku()),
	LOCATION(RC_DMC_DEKU_SCRUB_GROTTO_CENTER, logic->CanStunDeku()),
	LOCATION(RC_DMC_HAMMER_GROTTO_BEEHIVE, logic->CanBreakUpperBeehives()),
}, {
	Entrance(RR_DMC_LOWER_LOCAL, []{return true;}),
});
areaTable[RR_DMC_GREAT_FAIRY_FOUNTAIN] = Region("DMC Great Fairy Fountain", SCENE_GREAT_FAIRYS_FOUNTAIN_MAGIC, false, {}, {}, {
	LOCATION(RC_DMC_GREAT_FAIRY_REWARD, logic->CanUse(RG_ZELDAS_LULLABY)),
}, {
	Entrance(RR_DMC_LOWER_LOCAL, []{return true;}),
});
areaTable[RR_DMC_DISTANT_PLATFORM] = Region("DMC Distant Platform", SCENE_DEATH_MOUNTAIN_CRATER, false, {RA_DEATH_MOUNTAIN_CRATER}, {}, {
	LOCATION(RC_DMC_DISTANT_PLATFORM_GREEN_RUPEE_1, logic->IsAdult),
	LOCATION(RC_DMC_DISTANT_PLATFORM_GREEN_RUPEE_2, logic->IsAdult),
	LOCATION(RC_DMC_DISTANT_PLATFORM_GREEN_RUPEE_3, logic->IsAdult),
	LOCATION(RC_DMC_DISTANT_PLATFORM_GREEN_RUPEE_4, logic->IsAdult),
	LOCATION(RC_DMC_DISTANT_PLATFORM_GREEN_RUPEE_5, logic->IsAdult),
	LOCATION(RC_DMC_DISTANT_PLATFORM_GREEN_RUPEE_6, logic->IsAdult),
	LOCATION(RC_DMC_DISTANT_PLATFORM_RED_RUPEE, logic->IsAdult),
}, {
	Entrance(RR_DMC_CENTRAL_LOCAL, []{return ((logic->FireTimer() >= 48) && logic->CanUse(RG_DISTANT_SCARECROW));}),
});
areaTable[RR_ZR_FRONT] = Region("ZR Front", SCENE_ZORAS_RIVER, true, {RA_ZORAS_RIVER}, {}, {
	LOCATION(RC_ZR_GS_TREE, (logic->IsChild && logic->CanKillEnemy(RE_GOLD_SKULLTULA, ED_CLOSE))),
	LOCATION(RC_ZR_GRASS_1, logic->CanCutShrubs()),
	LOCATION(RC_ZR_GRASS_2, logic->CanCutShrubs()),
	LOCATION(RC_ZR_GRASS_3, logic->CanCutShrubs()),
	LOCATION(RC_ZR_GRASS_4, logic->CanCutShrubs()),
	LOCATION(RC_ZR_GRASS_5, logic->CanCutShrubs()),
	LOCATION(RC_ZR_GRASS_6, logic->CanCutShrubs()),
	LOCATION(RC_ZR_GRASS_7, logic->CanCutShrubs()),
	LOCATION(RC_ZR_GRASS_8, logic->CanCutShrubs()),
	LOCATION(RC_ZR_GRASS_9, logic->CanCutShrubs()),
	LOCATION(RC_ZR_GRASS_10, logic->CanCutShrubs()),
	LOCATION(RC_ZR_GRASS_11, logic->CanCutShrubs()),
	LOCATION(RC_ZR_GRASS_12, logic->CanCutShrubs()),
}, {
	Entrance(RR_ZORAS_RIVER, []{return (logic->IsAdult || logic->BlastOrSmash());}),
	Entrance(RR_HYRULE_FIELD, []{return true;}),
});
areaTable[RR_ZORAS_RIVER] = Region("Zora River", SCENE_ZORAS_RIVER, true, {RA_ZORAS_RIVER}, {
	EventAccess(&logic->GossipStoneFairy, []{return logic->CallGossipFairy();}),
	EventAccess(&logic->BeanPlantFairy, []{return (logic->IsChild && (logic->CanUse(RG_MAGIC_BEAN) && logic->CanUse(RG_SONG_OF_STORMS)));}),
	EventAccess(&logic->ButterflyFairy, []{return logic->CanUse(RG_STICKS);}),
	EventAccess(&logic->BugShrub, []{return logic->CanCutShrubs();}),
}, {
	LOCATION(RC_ZR_MAGIC_BEAN_SALESMAN, (logic->HasItem(RG_CHILD_WALLET) && logic->IsChild)),
	LOCATION(RC_ZR_FROGS_OCARINA_GAME, (logic->IsChild && (logic->CanUse(RG_ZELDAS_LULLABY) && (logic->CanUse(RG_SARIAS_SONG) && (logic->CanUse(RG_SUNS_SONG) && (logic->CanUse(RG_EPONAS_SONG) && (logic->CanUse(RG_SONG_OF_TIME) && logic->CanUse(RG_SONG_OF_STORMS)))))))),
	LOCATION(RC_ZR_FROGS_IN_THE_RAIN, (logic->IsChild && logic->CanUse(RG_SONG_OF_STORMS))),
	LOCATION(RC_ZR_FROGS_ZELDAS_LULLABY, (logic->IsChild && logic->CanUse(RG_ZELDAS_LULLABY))),
	LOCATION(RC_ZR_FROGS_EPONAS_SONG, (logic->IsChild && logic->CanUse(RG_EPONAS_SONG))),
	LOCATION(RC_ZR_FROGS_SARIAS_SONG, (logic->IsChild && logic->CanUse(RG_SARIAS_SONG))),
	LOCATION(RC_ZR_FROGS_SUNS_SONG, (logic->IsChild && logic->CanUse(RG_SUNS_SONG))),
	LOCATION(RC_ZR_FROGS_SONG_OF_TIME, (logic->IsChild && logic->CanUse(RG_SONG_OF_TIME))),
	LOCATION(RC_ZR_NEAR_OPEN_GROTTO_FREESTANDING_POH, (logic->IsChild || (logic->CanUse(RG_HOVER_BOOTS) || (logic->IsAdult && (bool)ctx->GetTrickOption(RT_ZR_LOWER))))),
	LOCATION(RC_ZR_NEAR_DOMAIN_FREESTANDING_POH, (logic->IsChild || (logic->CanUse(RG_HOVER_BOOTS) || (logic->IsAdult && (bool)ctx->GetTrickOption(RT_ZR_UPPER))))),
	LOCATION(RC_ZR_GS_LADDER, (logic->IsChild && (logic->CanAttack() && logic->CanGetNightTimeGS()))),
	LOCATION(RC_ZR_GS_NEAR_RAISED_GROTTOS, (logic->IsAdult && (logic->HookshotOrBoomerang() && logic->CanGetNightTimeGS()))),
	LOCATION(RC_ZR_GS_ABOVE_BRIDGE, (logic->IsAdult && (logic->CanUse(RG_HOOKSHOT) && logic->CanGetNightTimeGS()))),
	LOCATION(RC_ZR_BEAN_SPROUT_FAIRY_1, (logic->IsChild && (logic->CanUse(RG_MAGIC_BEAN) && logic->CanUse(RG_SONG_OF_STORMS)))),
	LOCATION(RC_ZR_BEAN_SPROUT_FAIRY_2, (logic->IsChild && (logic->CanUse(RG_MAGIC_BEAN) && logic->CanUse(RG_SONG_OF_STORMS)))),
	LOCATION(RC_ZR_BEAN_SPROUT_FAIRY_3, (logic->IsChild && (logic->CanUse(RG_MAGIC_BEAN) && logic->CanUse(RG_SONG_OF_STORMS)))),
	LOCATION(RC_ZR_NEAR_GROTTOS_GOSSIP_STONE_FAIRY, logic->CallGossipFairy()),
	LOCATION(RC_ZR_NEAR_GROTTOS_GOSSIP_STONE_FAIRY_BIG, logic->CanUse(RG_SONG_OF_STORMS)),
	LOCATION(RC_ZR_NEAR_DOMAIN_GOSSIP_STONE_FAIRY, logic->CallGossipFairy()),
	LOCATION(RC_ZR_NEAR_DOMAIN_GOSSIP_STONE_FAIRY_BIG, logic->CanUse(RG_SONG_OF_STORMS)),
	LOCATION(RC_ZR_BENEATH_WATERFALL_LEFT_RUPEE, (logic->IsAdult && (logic->HasItem(RG_BRONZE_SCALE) || (logic->CanUse(RG_IRON_BOOTS) || logic->CanUse(RG_BOOMERANG))))),
	LOCATION(RC_ZR_BENEATH_WATERFALL_MIDDLE_LEFT_RUPEE, (logic->IsAdult && (logic->HasItem(RG_BRONZE_SCALE) || (logic->CanUse(RG_IRON_BOOTS) || logic->CanUse(RG_BOOMERANG))))),
	LOCATION(RC_ZR_BENEATH_WATERFALL_MIDDLE_RIGHT_RUPEE, (logic->IsAdult && (logic->HasItem(RG_BRONZE_SCALE) || (logic->CanUse(RG_IRON_BOOTS) || logic->CanUse(RG_BOOMERANG))))),
	LOCATION(RC_ZR_BENEATH_WATERFALL_RIGHT_RUPEE, (logic->IsAdult && (logic->HasItem(RG_BRONZE_SCALE) || (logic->CanUse(RG_IRON_BOOTS) || logic->CanUse(RG_BOOMERANG))))),
	LOCATION(RC_ZR_NEAR_GROTTOS_GOSSIP_STONE, true),
	LOCATION(RC_ZR_NEAR_DOMAIN_GOSSIP_STONE, true),
	LOCATION(RC_ZR_NEAR_FREESTANDING_POH_GRASS, logic->CanCutShrubs()),
}, {
	Entrance(RR_ZR_FRONT, []{return true;}),
	Entrance(RR_ZR_OPEN_GROTTO, []{return true;}),
	Entrance(RR_ZR_FAIRY_GROTTO, []{return Here(RR_ZORAS_RIVER, []{return logic->BlastOrSmash();});}),
	Entrance(RR_THE_LOST_WOODS, []{return (logic->HasItem(RG_SILVER_SCALE) || logic->CanUse(RG_IRON_BOOTS));}),
	Entrance(RR_ZR_STORMS_GROTTO, []{return logic->CanOpenStormsGrotto();}),
	Entrance(RR_ZR_BEHIND_WATERFALL, []{return (ctx->GetOption(RSK_SLEEPING_WATERFALL).Is(RO_WATERFALL_OPEN) || (Here(RR_ZORAS_RIVER, []{return logic->CanUse(RG_ZELDAS_LULLABY);}) || ((logic->IsChild && (bool)ctx->GetTrickOption(RT_ZR_CUCCO)) || (logic->IsAdult && (logic->CanUse(RG_HOVER_BOOTS) && (bool)ctx->GetTrickOption(RT_ZR_HOVERS))))));}),
});
areaTable[RR_ZR_FROM_SHORTCUT] = Region("ZR From Shortcut", SCENE_ZORAS_RIVER, false, {RA_ZORAS_RIVER}, {}, {}, {
	Entrance(RR_ZORAS_RIVER, []{return ((logic->Hearts() > 1) || (logic->HasItem(RG_BOTTLE_WITH_FAIRY) || logic->HasItem(RG_BRONZE_SCALE)));}),
	Entrance(RR_THE_LOST_WOODS, []{return (logic->HasItem(RG_SILVER_SCALE) || logic->CanUse(RG_IRON_BOOTS));}),
});
areaTable[RR_ZR_BEHIND_WATERFALL] = Region("ZR Behind Waterfall", SCENE_ZORAS_RIVER, true, {RA_ZORAS_RIVER}, {}, {}, {
	Entrance(RR_ZORAS_RIVER, []{return true;}),
	Entrance(RR_ZORAS_DOMAIN, []{return true;}),
});
areaTable[RR_ZR_OPEN_GROTTO] = Region("ZR Open Grotto", SCENE_GROTTOS, false, {}, {
	EventAccess(&logic->GossipStoneFairy, []{return logic->CallGossipFairy();}),
	EventAccess(&logic->ButterflyFairy, []{return logic->CanUse(RG_STICKS);}),
	EventAccess(&logic->BugShrub, []{return logic->CanCutShrubs();}),
	EventAccess(&logic->LoneFish, []{return true;}),
}, {
	LOCATION(RC_ZR_OPEN_GROTTO_CHEST, true),
	LOCATION(RC_ZR_OPEN_GROTTO_FISH, logic->HasBottle()),
	LOCATION(RC_ZR_OPEN_GROTTO_GOSSIP_STONE_FAIRY, logic->CallGossipFairy()),
	LOCATION(RC_ZR_OPEN_GROTTO_GOSSIP_STONE_FAIRY_BIG, logic->CanUse(RG_SONG_OF_STORMS)),
	LOCATION(RC_ZR_OPEN_GROTTO_GOSSIP_STONE, true),
	LOCATION(RC_ZR_OPEN_GROTTO_BEEHIVE_LEFT, logic->CanBreakLowerBeehives()),
	LOCATION(RC_ZR_OPEN_GROTTO_BEEHIVE_RIGHT, logic->CanBreakLowerBeehives()),
	LOCATION(RC_ZR_OPEN_GROTTO_GRASS_1, logic->CanCutShrubs()),
	LOCATION(RC_ZR_OPEN_GROTTO_GRASS_2, logic->CanCutShrubs()),
	LOCATION(RC_ZR_OPEN_GROTTO_GRASS_3, logic->CanCutShrubs()),
	LOCATION(RC_ZR_OPEN_GROTTO_GRASS_4, logic->CanCutShrubs()),
}, {
	Entrance(RR_ZORAS_RIVER, []{return true;}),
});
areaTable[RR_ZR_FAIRY_GROTTO] = Region("ZR Fairy Grotto", SCENE_GROTTOS, false, {}, {
	EventAccess(&logic->FreeFairies, []{return true;}),
}, {
	LOCATION(RC_ZR_FAIRY_GROTTO_FAIRY_1, true),
	LOCATION(RC_ZR_FAIRY_GROTTO_FAIRY_2, true),
	LOCATION(RC_ZR_FAIRY_GROTTO_FAIRY_3, true),
	LOCATION(RC_ZR_FAIRY_GROTTO_FAIRY_4, true),
	LOCATION(RC_ZR_FAIRY_GROTTO_FAIRY_5, true),
	LOCATION(RC_ZR_FAIRY_GROTTO_FAIRY_6, true),
	LOCATION(RC_ZR_FAIRY_GROTTO_FAIRY_7, true),
	LOCATION(RC_ZR_FAIRY_GROTTO_FAIRY_8, true),
}, {
	Entrance(RR_ZORAS_RIVER, []{return true;}),
});
areaTable[RR_ZR_STORMS_GROTTO] = Region("ZR Storms Grotto", SCENE_GROTTOS, false, {}, {}, {
	LOCATION(RC_ZR_DEKU_SCRUB_GROTTO_REAR, logic->CanStunDeku()),
	LOCATION(RC_ZR_DEKU_SCRUB_GROTTO_FRONT, logic->CanStunDeku()),
	LOCATION(RC_ZR_STORMS_GROTTO_BEEHIVE, logic->CanBreakUpperBeehives()),
}, {
	Entrance(RR_ZORAS_RIVER, []{return true;}),
});
areaTable[RR_ZORAS_DOMAIN] = Region("Zoras Domain", SCENE_ZORAS_DOMAIN, false, {RA_ZORAS_DOMAIN}, {
	EventAccess(&logic->GossipStoneFairy, []{return logic->CallGossipFairyExceptSuns();}),
	EventAccess(&logic->NutPot, []{return true;}),
	EventAccess(&logic->StickPot, []{return logic->IsChild;}),
	EventAccess(&logic->FishGroup, []{return logic->IsChild;}),
	EventAccess(&logic->KingZoraThawed, []{return (logic->IsAdult && logic->BlueFire());}),
	EventAccess(&logic->DeliverLetter, []{return (logic->CanUse(RG_RUTOS_LETTER) && (logic->IsChild && ctx->GetOption(RSK_ZORAS_FOUNTAIN).IsNot(RO_ZF_OPEN)));}),
}, {
	LOCATION(RC_ZD_DIVING_MINIGAME, (logic->HasItem(RG_BRONZE_SCALE) && (logic->HasItem(RG_CHILD_WALLET) && logic->IsChild))),
	LOCATION(RC_ZD_CHEST, (logic->IsChild && logic->CanUse(RG_STICKS))),
	LOCATION(RC_ZD_KING_ZORA_THAWED, (logic->IsAdult && logic->KingZoraThawed)),
	LOCATION(RC_ZD_TRADE_PRESCRIPTION, (logic->IsAdult && (logic->KingZoraThawed && logic->CanUse(RG_PRESCRIPTION)))),
	LOCATION(RC_ZD_GS_FROZEN_WATERFALL, (logic->IsAdult && ((logic->HookshotOrBoomerang() || (logic->CanUse(RG_FAIRY_SLINGSHOT) || (logic->CanUse(RG_FAIRY_BOW) || ((logic->CanUse(RG_MAGIC_SINGLE) && (logic->CanUse(RG_MASTER_SWORD) || (logic->CanUse(RG_KOKIRI_SWORD) || logic->CanUse(RG_BIGGORON_SWORD)))) || ((bool)ctx->GetTrickOption(RT_ZD_GS) && logic->CanJumpslashExceptHammer()))))) && logic->CanGetNightTimeGS()))),
	LOCATION(RC_ZD_FISH_1, (logic->IsChild && logic->HasBottle())),
	LOCATION(RC_ZD_FISH_2, (logic->IsChild && logic->HasBottle())),
	LOCATION(RC_ZD_FISH_3, (logic->IsChild && logic->HasBottle())),
	LOCATION(RC_ZD_FISH_4, (logic->IsChild && logic->HasBottle())),
	LOCATION(RC_ZD_FISH_5, (logic->IsChild && logic->HasBottle())),
	LOCATION(RC_ZD_GOSSIP_STONE_FAIRY, logic->CallGossipFairyExceptSuns()),
	LOCATION(RC_ZD_GOSSIP_STONE_FAIRY_BIG, logic->CanUse(RG_SONG_OF_STORMS)),
	LOCATION(RC_ZD_GOSSIP_STONE, true),
	LOCATION(RC_ZD_IN_FRONT_OF_KING_ZORA_BEEHIVE_LEFT, (logic->IsChild && logic->CanBreakUpperBeehives())),
	LOCATION(RC_ZD_IN_FRONT_OF_KING_ZORA_BEEHIVE_RIGHT, (logic->IsChild && logic->CanBreakUpperBeehives())),
	LOCATION(RC_ZD_NEAR_SHOP_POT_1, logic->CanBreakPots()),
	LOCATION(RC_ZD_NEAR_SHOP_POT_2, logic->CanBreakPots()),
	LOCATION(RC_ZD_NEAR_SHOP_POT_3, logic->CanBreakPots()),
	LOCATION(RC_ZD_NEAR_SHOP_POT_4, logic->CanBreakPots()),
	LOCATION(RC_ZD_NEAR_SHOP_POT_5, logic->CanBreakPots()),
}, {
	Entrance(RR_ZR_BEHIND_WATERFALL, []{return true;}),
	Entrance(RR_LH_FROM_SHORTCUT, []{return (logic->IsChild && (logic->HasItem(RG_SILVER_SCALE) || logic->CanUse(RG_IRON_BOOTS)));}),
	Entrance(RR_ZD_BEHIND_KING_ZORA, []{return (logic->DeliverLetter || (ctx->GetOption(RSK_ZORAS_FOUNTAIN).Is(RO_ZF_OPEN) || ((ctx->GetOption(RSK_ZORAS_FOUNTAIN).Is(RO_ZF_CLOSED_CHILD) && logic->IsAdult) || ((bool)ctx->GetTrickOption(RT_ZD_KING_ZORA_SKIP) && logic->IsAdult))));}),
	Entrance(RR_ZD_SHOP, []{return (logic->IsChild || logic->BlueFire());}),
	Entrance(RR_ZORAS_DOMAIN_ISLAND, []{return true;}),
});
areaTable[RR_ZORAS_DOMAIN_ISLAND] = Region("Zoras Domain Island", SCENE_ZORAS_DOMAIN, false, {RA_ZORAS_DOMAIN}, {}, {}, {
	Entrance(RR_ZORAS_DOMAIN, []{return (logic->IsAdult || logic->HasItem(RG_BRONZE_SCALE));}),
	Entrance(RR_ZD_STORMS_GROTTO, []{return logic->CanOpenStormsGrotto();}),
});
areaTable[RR_ZD_BEHIND_KING_ZORA] = Region("ZD Behind King Zora", SCENE_ZORAS_DOMAIN, false, {RA_ZORAS_DOMAIN}, {
	EventAccess(&logic->KingZoraThawed, []{return (logic->IsAdult && logic->BlueFire());}),
}, {
	LOCATION(RC_ZD_BEHIND_KING_ZORA_BEEHIVE, (logic->IsChild && logic->CanBreakUpperBeehives())),
}, {
	Entrance(RR_ZORAS_DOMAIN, []{return (logic->DeliverLetter || (ctx->GetOption(RSK_ZORAS_FOUNTAIN).Is(RO_ZF_OPEN) || (ctx->GetOption(RSK_ZORAS_FOUNTAIN).Is(RO_ZF_CLOSED_CHILD) && logic->IsAdult)));}),
	Entrance(RR_ZORAS_FOUNTAIN, []{return true;}),
});
areaTable[RR_ZD_SHOP] = Region("ZD Shop", SCENE_ZORA_SHOP, false, {}, {}, {
	LOCATION(RC_ZD_SHOP_ITEM_1, true),
	LOCATION(RC_ZD_SHOP_ITEM_2, true),
	LOCATION(RC_ZD_SHOP_ITEM_3, true),
	LOCATION(RC_ZD_SHOP_ITEM_4, true),
	LOCATION(RC_ZD_SHOP_ITEM_5, true),
	LOCATION(RC_ZD_SHOP_ITEM_6, true),
	LOCATION(RC_ZD_SHOP_ITEM_7, true),
	LOCATION(RC_ZD_SHOP_ITEM_8, true),
}, {
	Entrance(RR_ZORAS_DOMAIN, []{return true;}),
});
areaTable[RR_ZD_STORMS_GROTTO] = Region("ZD Storms Grotto", SCENE_GROTTOS, false, {}, {
	EventAccess(&logic->FreeFairies, []{return true;}),
}, {
	LOCATION(RC_ZD_FAIRY_GROTTO_FAIRY_1, true),
	LOCATION(RC_ZD_FAIRY_GROTTO_FAIRY_2, true),
	LOCATION(RC_ZD_FAIRY_GROTTO_FAIRY_3, true),
	LOCATION(RC_ZD_FAIRY_GROTTO_FAIRY_4, true),
	LOCATION(RC_ZD_FAIRY_GROTTO_FAIRY_5, true),
	LOCATION(RC_ZD_FAIRY_GROTTO_FAIRY_6, true),
	LOCATION(RC_ZD_FAIRY_GROTTO_FAIRY_7, true),
	LOCATION(RC_ZD_FAIRY_GROTTO_FAIRY_8, true),
}, {
	Entrance(RR_ZORAS_DOMAIN_ISLAND, []{return true;}),
});
areaTable[RR_ZORAS_FOUNTAIN] = Region("Zoras Fountain", SCENE_ZORAS_FOUNTAIN, false, {RA_ZORAS_FOUNTAIN}, {
	EventAccess(&logic->GossipStoneFairy, []{return logic->CallGossipFairyExceptSuns();}),
	EventAccess(&logic->ButterflyFairy, []{return (logic->CanUse(RG_STICKS) && logic->AtDay);}),
}, {
	LOCATION(RC_ZF_GS_TREE, logic->IsChild),
	LOCATION(RC_ZF_GS_ABOVE_THE_LOG, (logic->IsChild && (logic->HookshotOrBoomerang() && logic->CanGetNightTimeGS()))),
	LOCATION(RC_ZF_FAIRY_GOSSIP_STONE_FAIRY, logic->CallGossipFairyExceptSuns()),
	LOCATION(RC_ZF_FAIRY_GOSSIP_STONE_FAIRY_BIG, logic->CanUse(RG_SONG_OF_STORMS)),
	LOCATION(RC_ZF_JABU_GOSSIP_STONE_FAIRY, logic->CallGossipFairyExceptSuns()),
	LOCATION(RC_ZF_JABU_GOSSIP_STONE_FAIRY_BIG, logic->CanUse(RG_SONG_OF_STORMS)),
	LOCATION(RC_ZF_FAIRY_GOSSIP_STONE, true),
	LOCATION(RC_ZF_JABU_GOSSIP_STONE, true),
	LOCATION(RC_ZF_NEAR_JABU_POT_1, (logic->IsChild && logic->CanBreakPots())),
	LOCATION(RC_ZF_NEAR_JABU_POT_2, (logic->IsChild && logic->CanBreakPots())),
	LOCATION(RC_ZF_NEAR_JABU_POT_3, (logic->IsChild && logic->CanBreakPots())),
	LOCATION(RC_ZF_NEAR_JABU_POT_4, (logic->IsChild && logic->CanBreakPots())),
}, {
	Entrance(RR_ZD_BEHIND_KING_ZORA, []{return true;}),
	Entrance(RR_ZF_ICEBERGS, []{return logic->IsAdult;}),
	Entrance(RR_ZF_LAKEBED, []{return logic->CanUse(RG_IRON_BOOTS);}),
	Entrance(RR_ZF_HIDDEN_CAVE, []{return (logic->CanUse(RG_SILVER_GAUNTLETS) && logic->BlastOrSmash());}),
	Entrance(RR_ZF_ROCK, []{return (logic->IsAdult && logic->CanUse(RG_SCARECROW));}),
	Entrance(RR_JABU_JABUS_BELLY_ENTRYWAY, []{return (logic->IsChild && (ctx->GetOption(RSK_JABU_OPEN).Is(RO_JABU_OPEN) || logic->CanUse(RG_BOTTLE_WITH_FISH)));}),
	Entrance(RR_ZF_GREAT_FAIRY_FOUNTAIN, []{return (logic->HasExplosives() || ((bool)ctx->GetTrickOption(RT_ZF_GREAT_FAIRY_WITHOUT_EXPLOSIVES) && (logic->CanUse(RG_MEGATON_HAMMER) && logic->CanUse(RG_SILVER_GAUNTLETS))));}),
});
areaTable[RR_ZF_ICEBERGS] = Region("ZF Icebergs", SCENE_ZORAS_FOUNTAIN, false, {RA_ZORAS_FOUNTAIN}, {}, {
	LOCATION(RC_ZF_ICEBERG_FREESTANDING_POH, logic->IsAdult),
}, {
	Entrance(RR_ZORAS_FOUNTAIN, []{return (logic->HasItem(RG_BRONZE_SCALE) || logic->CanUse(RG_HOVER_BOOTS));}),
	Entrance(RR_ZF_LAKEBED, []{return logic->CanUse(RG_IRON_BOOTS);}),
	Entrance(RR_ZF_LEDGE, []{return true;}),
});
areaTable[RR_ZF_LAKEBED] = Region("ZF Lakebed", SCENE_ZORAS_FOUNTAIN, false, {RA_ZORAS_FOUNTAIN}, {}, {
	LOCATION(RC_ZF_BOTTOM_FREESTANDING_POH, (logic->IsAdult && (logic->CanUse(RG_IRON_BOOTS) && (logic->WaterTimer() >= 16)))),
	LOCATION(RC_ZF_BOTTOM_NORTH_INNER_RUPEE, (logic->IsAdult && (logic->CanUse(RG_IRON_BOOTS) && (logic->WaterTimer() >= 16)))),
	LOCATION(RC_ZF_BOTTOM_NORTHEAST_INNER_RUPEE, (logic->IsAdult && (logic->CanUse(RG_IRON_BOOTS) && (logic->WaterTimer() >= 16)))),
	LOCATION(RC_ZF_BOTTOM_SOUTHEAST_INNER_RUPEE, (logic->IsAdult && (logic->CanUse(RG_IRON_BOOTS) && (logic->WaterTimer() >= 16)))),
	LOCATION(RC_ZF_BOTTOM_SOUTH_INNER_RUPEE, (logic->IsAdult && (logic->CanUse(RG_IRON_BOOTS) && (logic->WaterTimer() >= 16)))),
	LOCATION(RC_ZF_BOTTOM_SOUTHWEST_INNER_RUPEE, (logic->IsAdult && (logic->CanUse(RG_IRON_BOOTS) && (logic->WaterTimer() >= 16)))),
	LOCATION(RC_ZF_BOTTOM_NORTHWEST_INNER_RUPEE, (logic->IsAdult && (logic->CanUse(RG_IRON_BOOTS) && (logic->WaterTimer() >= 16)))),
	LOCATION(RC_ZF_BOTTOM_NORTH_MIDDLE_RUPEE, (logic->IsAdult && (logic->CanUse(RG_IRON_BOOTS) && (logic->WaterTimer() >= 16)))),
	LOCATION(RC_ZF_BOTTOM_NORTHEAST_MIDDLE_RUPEE, (logic->IsAdult && (logic->CanUse(RG_IRON_BOOTS) && (logic->WaterTimer() >= 16)))),
	LOCATION(RC_ZF_BOTTOM_SOUTHEAST_MIDDLE_RUPEE, (logic->IsAdult && (logic->CanUse(RG_IRON_BOOTS) && (logic->WaterTimer() >= 16)))),
	LOCATION(RC_ZF_BOTTOM_SOUTH_MIDDLE_RUPEE, (logic->IsAdult && (logic->CanUse(RG_IRON_BOOTS) && (logic->WaterTimer() >= 16)))),
	LOCATION(RC_ZF_BOTTOM_SOUTHWEST_MIDDLE_RUPEE, (logic->IsAdult && (logic->CanUse(RG_IRON_BOOTS) && (logic->WaterTimer() >= 16)))),
	LOCATION(RC_ZF_BOTTOM_NORTHWEST_MIDDLE_RUPEE, (logic->IsAdult && (logic->CanUse(RG_IRON_BOOTS) && (logic->WaterTimer() >= 16)))),
	LOCATION(RC_ZF_BOTTOM_NORTH_OUTER_RUPEE, (logic->IsAdult && (logic->CanUse(RG_IRON_BOOTS) && (logic->WaterTimer() >= 16)))),
	LOCATION(RC_ZF_BOTTOM_NORTHEAST_OUTER_RUPEE, (logic->IsAdult && (logic->CanUse(RG_IRON_BOOTS) && (logic->WaterTimer() >= 16)))),
	LOCATION(RC_ZF_BOTTOM_SOUTHEAST_OUTER_RUPEE, (logic->IsAdult && (logic->CanUse(RG_IRON_BOOTS) && (logic->WaterTimer() >= 16)))),
	LOCATION(RC_ZF_BOTTOM_SOUTH_OUTER_RUPEE, (logic->IsAdult && (logic->CanUse(RG_IRON_BOOTS) && (logic->WaterTimer() >= 16)))),
	LOCATION(RC_ZF_BOTTOM_SOUTHWEST_OUTER_RUPEE, (logic->IsAdult && (logic->CanUse(RG_IRON_BOOTS) && (logic->WaterTimer() >= 16)))),
	LOCATION(RC_ZF_BOTTOM_NORTHWEST_OUTER_RUPEE, (logic->IsAdult && (logic->CanUse(RG_IRON_BOOTS) && (logic->WaterTimer() >= 16)))),
}, {
	Entrance(RR_ZORAS_FOUNTAIN, []{return logic->HasItem(RG_BRONZE_SCALE);}),
});
areaTable[RR_ZF_LEDGE] = Region("ZF Ledge", SCENE_ZORAS_FOUNTAIN, false, {RA_ZORAS_FOUNTAIN}, {}, {}, {
	Entrance(RR_ZORAS_FOUNTAIN, []{return logic->HasItem(RG_BRONZE_SCALE);}),
	Entrance(RR_ZF_ICEBERGS, []{return logic->IsAdult;}),
	Entrance(RR_ZF_LAKEBED, []{return logic->CanUse(RG_IRON_BOOTS);}),
	Entrance(RR_ICE_CAVERN_ENTRYWAY, []{return true;}),
});
areaTable[RR_ZF_HIDDEN_CAVE] = Region("ZF Hidden Cave", SCENE_ZORAS_FOUNTAIN, false, {RA_ZORAS_FOUNTAIN}, {}, {
	LOCATION(RC_ZF_HIDDEN_CAVE_POT_1, (logic->IsAdult && logic->CanBreakPots())),
	LOCATION(RC_ZF_HIDDEN_CAVE_POT_2, (logic->IsAdult && logic->CanBreakPots())),
	LOCATION(RC_ZF_HIDDEN_CAVE_POT_3, (logic->IsAdult && logic->CanBreakPots())),
}, {
	Entrance(RR_ZF_HIDDEN_LEDGE, []{return true;}),
});
areaTable[RR_ZF_HIDDEN_LEDGE] = Region("ZF Hidden Ledge", SCENE_ZORAS_FOUNTAIN, false, {RA_ZORAS_FOUNTAIN}, {}, {
	LOCATION(RC_ZF_GS_HIDDEN_CAVE, (logic->IsAdult && (logic->CanGetEnemyDrop(RE_GOLD_SKULLTULA, ED_BOMB_THROW) && logic->CanGetNightTimeGS()))),
}, {
	Entrance(RR_ZORAS_FOUNTAIN, []{return (logic->HasItem(RG_BRONZE_SCALE) || logic->TakeDamage());}),
	Entrance(RR_ZF_HIDDEN_CAVE, []{return true;}),
});
areaTable[RR_ZF_ROCK] = Region("ZF Rock", SCENE_ZORAS_FOUNTAIN, false, {RA_ZORAS_FOUNTAIN}, {}, {}, {
	Entrance(RR_ZORAS_FOUNTAIN, []{return true;}),
});
areaTable[RR_ZF_GREAT_FAIRY_FOUNTAIN] = Region("ZF Great Fairy Fountain", SCENE_GREAT_FAIRYS_FOUNTAIN_SPELLS, false, {}, {}, {
	LOCATION(RC_ZF_GREAT_FAIRY_REWARD, logic->CanUse(RG_ZELDAS_LULLABY)),
}, {
	Entrance(RR_ZORAS_FOUNTAIN, []{return true;}),
});
areaTable[RR_LON_LON_RANCH] = Region("Lon Lon Ranch", SCENE_LON_LON_RANCH, true, {RA_LON_LON_RANCH}, {
	EventAccess(&logic->FreedEpona, []{return ((logic->HasItem(RG_CHILD_WALLET) || ctx->GetOption(RSK_SKIP_EPONA_RACE)) && (logic->CanUse(RG_EPONAS_SONG) && (logic->IsAdult && logic->AtDay)));}),
	EventAccess(&logic->LinksCow, []{return (logic->HasItem(RG_CHILD_WALLET) && (logic->CanUse(RG_EPONAS_SONG) && (logic->IsAdult && logic->AtDay)));}),
}, {
	LOCATION(RC_SONG_FROM_MALON, (logic->IsChild && (logic->HasItem(RG_ZELDAS_LETTER) && (logic->HasItem(RG_FAIRY_OCARINA) && logic->AtDay)))),
	LOCATION(RC_LLR_GS_TREE, logic->IsChild),
	LOCATION(RC_LLR_GS_RAIN_SHED, (logic->IsChild && logic->CanGetNightTimeGS())),
	LOCATION(RC_LLR_GS_HOUSE_WINDOW, (logic->IsChild && (logic->HookshotOrBoomerang() && logic->CanGetNightTimeGS()))),
	LOCATION(RC_LLR_GS_BACK_WALL, (logic->IsChild && (logic->HookshotOrBoomerang() && logic->CanGetNightTimeGS()))),
	LOCATION(RC_LLR_FRONT_POT_1, (logic->IsChild && logic->CanBreakPots())),
	LOCATION(RC_LLR_FRONT_POT_2, (logic->IsChild && logic->CanBreakPots())),
	LOCATION(RC_LLR_FRONT_POT_3, (logic->IsChild && logic->CanBreakPots())),
	LOCATION(RC_LLR_FRONT_POT_4, (logic->IsChild && logic->CanBreakPots())),
	LOCATION(RC_LLR_RAIN_SHED_POT_1, (logic->IsChild && logic->CanBreakPots())),
	LOCATION(RC_LLR_RAIN_SHED_POT_2, (logic->IsChild && logic->CanBreakPots())),
	LOCATION(RC_LLR_RAIN_SHED_POT_3, (logic->IsChild && logic->CanBreakPots())),
	LOCATION(RC_LLR_NEAR_TREE_CRATE, (logic->IsChild && logic->CanBreakCrates())),
}, {
	Entrance(RR_HYRULE_FIELD, []{return true;}),
	Entrance(RR_LLR_TALONS_HOUSE, []{return logic->CanOpenOverworldDoor(RG_TALONS_HOUSE_KEY);}),
	Entrance(RR_LLR_STABLES, []{return logic->CanOpenOverworldDoor(RG_STABLES_KEY);}),
	Entrance(RR_LLR_TOWER, []{return logic->CanOpenOverworldDoor(RG_BACK_TOWER_KEY);}),
	Entrance(RR_LLR_GROTTO, []{return logic->IsChild;}),
});
areaTable[RR_LLR_TALONS_HOUSE] = Region("LLR Talons House", SCENE_LON_LON_BUILDINGS, false, {}, {}, {
	LOCATION(RC_LLR_TALONS_CHICKENS, (logic->HasItem(RG_CHILD_WALLET) && (logic->IsChild && (logic->AtDay && logic->HasItem(RG_ZELDAS_LETTER))))),
	LOCATION(RC_LLR_TALONS_HOUSE_POT_1, logic->CanBreakPots()),
	LOCATION(RC_LLR_TALONS_HOUSE_POT_2, logic->CanBreakPots()),
	LOCATION(RC_LLR_TALONS_HOUSE_POT_3, logic->CanBreakPots()),
}, {
	Entrance(RR_LON_LON_RANCH, []{return true;}),
});
areaTable[RR_LLR_STABLES] = Region("LLR Stables", SCENE_STABLE, false, {}, {}, {
	LOCATION(RC_LLR_STABLES_LEFT_COW, logic->CanUse(RG_EPONAS_SONG)),
	LOCATION(RC_LLR_STABLES_RIGHT_COW, logic->CanUse(RG_EPONAS_SONG)),
}, {
	Entrance(RR_LON_LON_RANCH, []{return true;}),
});
areaTable[RR_LLR_TOWER] = Region("LLR Tower", SCENE_LON_LON_BUILDINGS, false, {}, {}, {
	LOCATION(RC_LLR_FREESTANDING_POH, logic->IsChild),
	LOCATION(RC_LLR_TOWER_LEFT_COW, logic->CanUse(RG_EPONAS_SONG)),
	LOCATION(RC_LLR_TOWER_RIGHT_COW, logic->CanUse(RG_EPONAS_SONG)),
}, {
	Entrance(RR_LON_LON_RANCH, []{return true;}),
});
areaTable[RR_LLR_GROTTO] = Region("LLR Grotto", SCENE_GROTTOS, false, {}, {}, {
	LOCATION(RC_LLR_DEKU_SCRUB_GROTTO_LEFT, logic->CanStunDeku()),
	LOCATION(RC_LLR_DEKU_SCRUB_GROTTO_RIGHT, logic->CanStunDeku()),
	LOCATION(RC_LLR_DEKU_SCRUB_GROTTO_CENTER, logic->CanStunDeku()),
	LOCATION(RC_LLR_GROTTO_BEEHIVE, logic->CanBreakUpperBeehives()),
}, {
	Entrance(RR_LON_LON_RANCH, []{return true;}),
});
areaTable[RR_DEKU_TREE_ENTRYWAY] = Region("Deku Tree Entryway", SCENE_DEKU_TREE, false, {RA_DEKU_TREE}, {}, {}, {
	Entrance(RR_DEKU_TREE_LOBBY, []{return ctx->GetDungeon(Rando::DEKU_TREE)->IsVanilla();}),
	Entrance(RR_DEKU_TREE_MQ_1F, []{return ctx->GetDungeon(Rando::DEKU_TREE)->IsMQ();}),
	Entrance(RR_KF_OUTSIDE_DEKU_TREE, []{return true;}),
});
areaTable[RR_DODONGOS_CAVERN_ENTRYWAY] = Region("Dodongos Cavern Entryway", SCENE_DODONGOS_CAVERN, false, {RA_DODONGOS_CAVERN}, {}, {}, {
	Entrance(RR_DODONGOS_CAVERN_BEGINNING, []{return ctx->GetDungeon(Rando::DODONGOS_CAVERN)->IsVanilla();}),
	Entrance(RR_DODONGOS_CAVERN_MQ_BEGINNING, []{return ctx->GetDungeon(Rando::DODONGOS_CAVERN)->IsMQ();}),
	Entrance(RR_DEATH_MOUNTAIN_TRAIL, []{return true;}),
});
areaTable[RR_JABU_JABUS_BELLY_ENTRYWAY] = Region("Jabu Jabus Belly Entryway", SCENE_JABU_JABU, false, {RA_JABU_JABUS_BELLY}, {}, {}, {
	Entrance(RR_JABU_JABUS_BELLY_BEGINNING, []{return ctx->GetDungeon(Rando::JABU_JABUS_BELLY)->IsVanilla();}),
	Entrance(RR_JABU_JABUS_BELLY_MQ_BEGINNING, []{return ctx->GetDungeon(Rando::JABU_JABUS_BELLY)->IsMQ();}),
	Entrance(RR_ZORAS_FOUNTAIN, []{return true;}),
});
areaTable[RR_FOREST_TEMPLE_ENTRYWAY] = Region("Forest Temple Entryway", SCENE_FOREST_TEMPLE, false, {RA_FOREST_TEMPLE}, {}, {}, {
	Entrance(RR_FOREST_TEMPLE_FIRST_ROOM, []{return ctx->GetDungeon(Rando::FOREST_TEMPLE)->IsVanilla();}),
	Entrance(RR_FOREST_TEMPLE_MQ_LOBBY, []{return ctx->GetDungeon(Rando::FOREST_TEMPLE)->IsMQ();}),
	Entrance(RR_SACRED_FOREST_MEADOW, []{return true;}),
});
areaTable[RR_FIRE_TEMPLE_ENTRYWAY] = Region("Fire Temple Entryway", SCENE_FIRE_TEMPLE, false, {RA_FIRE_TEMPLE}, {}, {}, {
	Entrance(RR_FIRE_TEMPLE_FIRST_ROOM, []{return ctx->GetDungeon(Rando::FIRE_TEMPLE)->IsVanilla();}),
	Entrance(RR_FIRE_TEMPLE_MQ_FIRST_ROOM_LOWER, []{return ctx->GetDungeon(Rando::FIRE_TEMPLE)->IsMQ();}),
	Entrance(RR_DMC_CENTRAL_LOCAL, []{return true;}),
});
areaTable[RR_WATER_TEMPLE_ENTRYWAY] = Region("Water Temple Entryway", SCENE_WATER_TEMPLE, false, {RA_WATER_TEMPLE}, {}, {}, {
	Entrance(RR_WATER_TEMPLE_LOBBY, []{return (logic->HasItem(RG_BRONZE_SCALE) && ctx->GetDungeon(Rando::WATER_TEMPLE)->IsVanilla());}),
	Entrance(RR_WATER_TEMPLE_MQ_3F_CENTRAL, []{return (logic->HasItem(RG_BRONZE_SCALE) && ctx->GetDungeon(Rando::WATER_TEMPLE)->IsMQ());}),
	Entrance(RR_LH_FROM_WATER_TEMPLE, []{return true;}),
});
areaTable[RR_SPIRIT_TEMPLE_ENTRYWAY] = Region("Spirit Temple Entryway", SCENE_SPIRIT_TEMPLE, false, {RA_SPIRIT_TEMPLE}, {}, {}, {
	Entrance(RR_SPIRIT_TEMPLE_LOBBY, []{return ctx->GetDungeon(Rando::SPIRIT_TEMPLE)->IsVanilla();}),
	Entrance(RR_SPIRIT_TEMPLE_MQ_LOBBY, []{return ctx->GetDungeon(Rando::SPIRIT_TEMPLE)->IsMQ();}),
	Entrance(RR_DESERT_COLOSSUS_OUTSIDE_TEMPLE, []{return true;}),
});
areaTable[RR_SHADOW_TEMPLE_ENTRYWAY] = Region("Shadow Temple Entryway", SCENE_SHADOW_TEMPLE, false, {RA_SHADOW_TEMPLE}, {}, {}, {
	Entrance(RR_SHADOW_TEMPLE_BEGINNING, []{return (ctx->GetDungeon(Rando::SHADOW_TEMPLE)->IsVanilla() && (((bool)ctx->GetTrickOption(RT_LENS_SHADOW) || logic->CanUse(RG_LENS_OF_TRUTH)) && (logic->CanUse(RG_HOVER_BOOTS) || logic->CanUse(RG_HOOKSHOT))));}),
	Entrance(RR_SHADOW_TEMPLE_MQ_BEGINNING, []{return ctx->GetDungeon(Rando::SHADOW_TEMPLE)->IsMQ();}),
	Entrance(RR_GRAVEYARD_WARP_PAD_REGION, []{return true;}),
});
areaTable[RR_BOTTOM_OF_THE_WELL_ENTRYWAY] = Region("Bottom of the Well Entryway", SCENE_BOTTOM_OF_THE_WELL, false, {RA_BOTTOM_OF_THE_WELL}, {}, {}, {
	Entrance(RR_BOTTOM_OF_THE_WELL_PERIMETER, []{return (ctx->GetDungeon(Rando::BOTTOM_OF_THE_WELL)->IsVanilla() && (logic->IsChild && logic->CanPassEnemy(RE_BIG_SKULLTULA)));}),
	Entrance(RR_BOTTOM_OF_THE_WELL_MQ_PERIMETER, []{return (ctx->GetDungeon(Rando::BOTTOM_OF_THE_WELL)->IsMQ() && logic->IsChild);}),
	Entrance(RR_KAK_WELL, []{return true;}),
});
areaTable[RR_ICE_CAVERN_ENTRYWAY] = Region("Ice Cavern Entryway", SCENE_ICE_CAVERN, false, {RA_ICE_CAVERN}, {}, {}, {
	Entrance(RR_ICE_CAVERN_BEGINNING, []{return ctx->GetDungeon(Rando::ICE_CAVERN)->IsVanilla();}),
	Entrance(RR_ICE_CAVERN_MQ_BEGINNING, []{return (ctx->GetDungeon(Rando::ICE_CAVERN)->IsMQ() && logic->CanUseProjectile());}),
	Entrance(RR_ZF_LEDGE, []{return true;}),
});
areaTable[RR_GERUDO_TRAINING_GROUND_ENTRYWAY] = Region("Gerudo Training Ground Entryway", SCENE_GERUDO_TRAINING_GROUND, false, {RA_GERUDO_TRAINING_GROUND}, {}, {}, {
	Entrance(RR_GERUDO_TRAINING_GROUND_LOBBY, []{return ctx->GetDungeon(Rando::GERUDO_TRAINING_GROUND)->IsVanilla();}),
	Entrance(RR_GERUDO_TRAINING_GROUND_MQ_LOBBY, []{return ctx->GetDungeon(Rando::GERUDO_TRAINING_GROUND)->IsMQ();}),
	Entrance(RR_GF_EXITING_GTG, []{return true;}),
});
areaTable[RR_GANONS_CASTLE_ENTRYWAY] = Region("Ganon's Castle Entryway", SCENE_INSIDE_GANONS_CASTLE, false, {RA_GANONS_CASTLE}, {}, {}, {
	Entrance(RR_GANONS_CASTLE_LOBBY, []{return ctx->GetDungeon(Rando::GANONS_CASTLE)->IsVanilla();}),
	Entrance(RR_GANONS_CASTLE_MQ_LOBBY, []{return ctx->GetDungeon(Rando::GANONS_CASTLE)->IsMQ();}),
	Entrance(RR_CASTLE_GROUNDS_FROM_GANONS_CASTLE, []{return true;}),
});
areaTable[RR_DEKU_TREE_LOBBY] = Region("Deku Tree Lobby", SCENE_DEKU_TREE, false, {RA_DEKU_TREE}, {
	EventAccess(&logic->DekuBabaSticks, []{return logic->CanGetDekuBabaSticks();}),
	EventAccess(&logic->DekuBabaNuts, []{return logic->CanGetDekuBabaNuts();}),
}, {
	LOCATION(RC_DEKU_TREE_MAP_CHEST, true),
	LOCATION(RC_DEKU_TREE_LOBBY_LOWER_HEART, true),
	LOCATION(RC_DEKU_TREE_LOBBY_UPPER_HEART, logic->CanPassEnemy(RE_BIG_SKULLTULA)),
	LOCATION(RC_DEKU_TREE_LOBBY_GRASS_1, logic->CanCutShrubs()),
	LOCATION(RC_DEKU_TREE_LOBBY_GRASS_2, logic->CanCutShrubs()),
	LOCATION(RC_DEKU_TREE_LOBBY_GRASS_3, logic->CanCutShrubs()),
	LOCATION(RC_DEKU_TREE_LOBBY_GRASS_4, logic->CanCutShrubs()),
	LOCATION(RC_DEKU_TREE_LOBBY_GRASS_5, logic->CanCutShrubs()),
}, {
	Entrance(RR_DEKU_TREE_ENTRYWAY, []{return true;}),
	Entrance(RR_DEKU_TREE_2F_MIDDLE_ROOM, []{return true;}),
	Entrance(RR_DEKU_TREE_COMPASS_ROOM, []{return true;}),
	Entrance(RR_DEKU_TREE_BASEMENT_LOWER, []{return Here(RR_DEKU_TREE_LOBBY, []{return (logic->CanAttack() || logic->CanUse(RG_NUTS));});}),
	Entrance(RR_DEKU_TREE_OUTSIDE_BOSS_ROOM, []{return false;}),
	Entrance(RR_DEKU_TREE_BOSS_ENTRYWAY, []{return false;}),
});
areaTable[RR_DEKU_TREE_2F_MIDDLE_ROOM] = Region("Deku Tree 2F Middle Room", SCENE_DEKU_TREE, false, {RA_DEKU_TREE}, {}, {}, {
	Entrance(RR_DEKU_TREE_LOBBY, []{return Here(RR_DEKU_TREE_2F_MIDDLE_ROOM, []{return (logic->CanReflectNuts() || logic->CanUse(RG_MEGATON_HAMMER));});}),
	Entrance(RR_DEKU_TREE_SLINGSHOT_ROOM, []{return Here(RR_DEKU_TREE_2F_MIDDLE_ROOM, []{return (logic->CanReflectNuts() || logic->CanUse(RG_MEGATON_HAMMER));});}),
});
areaTable[RR_DEKU_TREE_SLINGSHOT_ROOM] = Region("Deku Tree Slingshot Room", SCENE_DEKU_TREE, false, {RA_DEKU_TREE}, {}, {
	LOCATION(RC_DEKU_TREE_SLINGSHOT_CHEST, true),
	LOCATION(RC_DEKU_TREE_SLINGSHOT_ROOM_SIDE_CHEST, true),
	LOCATION(RC_DEKU_TREE_SLINGSHOT_GRASS_1, (logic->CanCutShrubs() && logic->CanReflectNuts())),
	LOCATION(RC_DEKU_TREE_SLINGSHOT_GRASS_2, (logic->CanCutShrubs() && logic->CanReflectNuts())),
	LOCATION(RC_DEKU_TREE_SLINGSHOT_GRASS_3, (logic->CanCutShrubs() && logic->CanReflectNuts())),
	LOCATION(RC_DEKU_TREE_SLINGSHOT_GRASS_4, (logic->CanCutShrubs() && logic->CanReflectNuts())),
}, {
	Entrance(RR_DEKU_TREE_2F_MIDDLE_ROOM, []{return (logic->CanUse(RG_FAIRY_SLINGSHOT) || logic->CanUse(RG_HOVER_BOOTS));}),
});
areaTable[RR_DEKU_TREE_COMPASS_ROOM] = Region("Deku Tree Compass Room", SCENE_DEKU_TREE, false, {RA_DEKU_TREE}, {
	EventAccess(&logic->DekuBabaSticks, []{return logic->CanGetDekuBabaSticks();}),
	EventAccess(&logic->DekuBabaNuts, []{return logic->CanGetDekuBabaNuts();}),
}, {
	LOCATION(RC_DEKU_TREE_COMPASS_CHEST, true),
	LOCATION(RC_DEKU_TREE_COMPASS_ROOM_SIDE_CHEST, true),
	LOCATION(RC_DEKU_TREE_GS_COMPASS_ROOM, logic->CanAttack()),
	LOCATION(RC_DEKU_TREE_COMPASS_GRASS_1, logic->CanCutShrubs()),
	LOCATION(RC_DEKU_TREE_COMPASS_GRASS_2, logic->CanCutShrubs()),
}, {
	Entrance(RR_DEKU_TREE_LOBBY, []{return (logic->HasFireSourceWithTorch() || logic->CanUse(RG_FAIRY_BOW));}),
	Entrance(RR_DEKU_TREE_BOSS_ENTRYWAY, []{return false;}),
});
areaTable[RR_DEKU_TREE_BASEMENT_LOWER] = Region("Deku Tree Basement Lower", SCENE_DEKU_TREE, false, {RA_DEKU_TREE}, {
	EventAccess(&logic->DekuBabaSticks, []{return logic->CanGetDekuBabaSticks();}),
	EventAccess(&logic->DekuBabaNuts, []{return logic->CanGetDekuBabaNuts();}),
}, {
	LOCATION(RC_DEKU_TREE_BASEMENT_CHEST, true),
	LOCATION(RC_DEKU_TREE_GS_BASEMENT_GATE, logic->CanKillEnemy(RE_GOLD_SKULLTULA, ED_SHORT_JUMPSLASH)),
	LOCATION(RC_DEKU_TREE_GS_BASEMENT_VINES, logic->CanKillEnemy(RE_GOLD_SKULLTULA, ((bool)ctx->GetTrickOption(RT_DEKU_MQ_COMPASS_GS) ? ED_SHORT_JUMPSLASH : ED_BOMB_THROW))),
	LOCATION(RC_DEKU_TREE_BASEMENT_GRASS_1, logic->CanCutShrubs()),
	LOCATION(RC_DEKU_TREE_BASEMENT_GRASS_2, logic->CanCutShrubs()),
}, {
	Entrance(RR_DEKU_TREE_LOBBY, []{return true;}),
	Entrance(RR_DEKU_TREE_BASEMENT_SCRUB_ROOM, []{return Here(RR_DEKU_TREE_BASEMENT_LOWER, []{return (logic->HasFireSourceWithTorch() || logic->CanUse(RG_FAIRY_BOW));});}),
	Entrance(RR_DEKU_TREE_BASEMENT_UPPER, []{return (logic->IsAdult || ((bool)ctx->GetTrickOption(RT_DEKU_B1_SKIP) || HasAccessTo(RR_DEKU_TREE_BASEMENT_UPPER)));}),
	Entrance(RR_DEKU_TREE_OUTSIDE_BOSS_ROOM, []{return false;}),
});
areaTable[RR_DEKU_TREE_BASEMENT_SCRUB_ROOM] = Region("Deku Tree Basement Scrub Room", SCENE_DEKU_TREE, false, {RA_DEKU_TREE}, {}, {
	LOCATION(RC_DEKU_TREE_BASEMENT_SCRUB_ROOM_GRASS_1, logic->CanCutShrubs()),
	LOCATION(RC_DEKU_TREE_BASEMENT_SCRUB_ROOM_GRASS_2, logic->CanCutShrubs()),
	LOCATION(RC_DEKU_TREE_BASEMENT_SCRUB_ROOM_GRASS_3, logic->CanCutShrubs()),
	LOCATION(RC_DEKU_TREE_BASEMENT_SCRUB_ROOM_GRASS_4, logic->CanCutShrubs()),
}, {
	Entrance(RR_DEKU_TREE_BASEMENT_LOWER, []{return true;}),
	Entrance(RR_DEKU_TREE_BASEMENT_WATER_ROOM_FRONT, []{return Here(RR_DEKU_TREE_BASEMENT_SCRUB_ROOM, []{return logic->CanHitEyeTargets();});}),
});
areaTable[RR_DEKU_TREE_BASEMENT_WATER_ROOM_FRONT] = Region("Deku Tree Basement Water Room Front", SCENE_DEKU_TREE, false, {RA_DEKU_TREE}, {}, {}, {
	Entrance(RR_DEKU_TREE_BASEMENT_SCRUB_ROOM, []{return true;}),
	Entrance(RR_DEKU_TREE_BASEMENT_WATER_ROOM_BACK, []{return (logic->HasItem(RG_BRONZE_SCALE) || (bool)ctx->GetTrickOption(RT_DEKU_B1_BACKFLIP_OVER_SPIKED_LOG));}),
});
areaTable[RR_DEKU_TREE_BASEMENT_WATER_ROOM_BACK] = Region("Deku Tree Basement Water Room Back", SCENE_DEKU_TREE, false, {RA_DEKU_TREE}, {}, {
	LOCATION(RC_DEKU_TREE_BASEMENT_SPIKE_ROLLER_GRASS_1, logic->CanCutShrubs()),
	LOCATION(RC_DEKU_TREE_BASEMENT_SPIKE_ROLLER_GRASS_2, logic->CanCutShrubs()),
}, {
	Entrance(RR_DEKU_TREE_BASEMENT_WATER_ROOM_FRONT, []{return (logic->HasItem(RG_BRONZE_SCALE) || (bool)ctx->GetTrickOption(RT_DEKU_B1_BACKFLIP_OVER_SPIKED_LOG));}),
	Entrance(RR_DEKU_TREE_BASEMENT_TORCH_ROOM, []{return true;}),
});
areaTable[RR_DEKU_TREE_BASEMENT_TORCH_ROOM] = Region("Deku Tree Basement Torch Room", SCENE_DEKU_TREE, false, {RA_DEKU_TREE}, {
	EventAccess(&logic->DekuBabaSticks, []{return logic->CanGetDekuBabaSticks();}),
	EventAccess(&logic->DekuBabaNuts, []{return logic->CanGetDekuBabaNuts();}),
}, {
	LOCATION(RC_DEKU_TREE_BASEMENT_TORCHES_GRASS_1, logic->CanCutShrubs()),
	LOCATION(RC_DEKU_TREE_BASEMENT_TORCHES_GRASS_2, logic->CanCutShrubs()),
}, {
	Entrance(RR_DEKU_TREE_BASEMENT_WATER_ROOM_BACK, []{return true;}),
	Entrance(RR_DEKU_TREE_BASEMENT_BACK_LOBBY, []{return Here(RR_DEKU_TREE_BASEMENT_TORCH_ROOM, []{return (logic->HasFireSourceWithTorch() || logic->CanUse(RG_FAIRY_BOW));});}),
});
areaTable[RR_DEKU_TREE_BASEMENT_BACK_LOBBY] = Region("Deku Tree Basement Back Lobby", SCENE_DEKU_TREE, false, {RA_DEKU_TREE}, {
	EventAccess(&logic->DekuBabaSticks, []{return logic->CanGetDekuBabaSticks();}),
	EventAccess(&logic->DekuBabaNuts, []{return logic->CanGetDekuBabaNuts();}),
}, {
	LOCATION(RC_DEKU_TREE_BASEMENT_LARVAE_GRASS_1, logic->CanCutShrubs()),
	LOCATION(RC_DEKU_TREE_BASEMENT_LARVAE_GRASS_2, logic->CanCutShrubs()),
}, {
	Entrance(RR_DEKU_TREE_BASEMENT_TORCH_ROOM, []{return true;}),
	Entrance(RR_DEKU_TREE_BASEMENT_BACK_ROOM, []{return (Here(RR_DEKU_TREE_BASEMENT_BACK_LOBBY, []{return (logic->HasFireSourceWithTorch() || logic->CanUse(RG_FAIRY_BOW));}) && Here(RR_DEKU_TREE_BASEMENT_BACK_LOBBY, []{return logic->BlastOrSmash();}));}),
	Entrance(RR_DEKU_TREE_BASEMENT_UPPER, []{return (Here(RR_DEKU_TREE_BASEMENT_BACK_LOBBY, []{return (logic->HasFireSourceWithTorch() || logic->CanUse(RG_FAIRY_BOW));}) && logic->IsChild);}),
});
areaTable[RR_DEKU_TREE_BASEMENT_BACK_ROOM] = Region("Deku Tree Basement Back Room", SCENE_DEKU_TREE, false, {RA_DEKU_TREE}, {}, {
	LOCATION(RC_DEKU_TREE_GS_BASEMENT_BACK_ROOM, logic->HookshotOrBoomerang()),
}, {
	Entrance(RR_DEKU_TREE_BASEMENT_BACK_LOBBY, []{return true;}),
});
areaTable[RR_DEKU_TREE_BASEMENT_UPPER] = Region("Deku Tree Basement Upper", SCENE_DEKU_TREE, false, {RA_DEKU_TREE}, {
	EventAccess(&logic->DekuBabaSticks, []{return logic->CanGetDekuBabaSticks();}),
	EventAccess(&logic->DekuBabaNuts, []{return logic->CanGetDekuBabaNuts();}),
}, {}, {
	Entrance(RR_DEKU_TREE_BASEMENT_LOWER, []{return true;}),
	Entrance(RR_DEKU_TREE_BASEMENT_BACK_LOBBY, []{return logic->IsChild;}),
	Entrance(RR_DEKU_TREE_OUTSIDE_BOSS_ROOM, []{return Here(RR_DEKU_TREE_BASEMENT_UPPER, []{return (logic->HasFireSourceWithTorch() || ((bool)ctx->GetTrickOption(RT_DEKU_B1_BOW_WEBS) && (logic->IsAdult && logic->CanUse(RG_FAIRY_BOW))));});}),
});
areaTable[RR_DEKU_TREE_OUTSIDE_BOSS_ROOM] = Region("Deku Tree Outside Boss Room", SCENE_DEKU_TREE, false, {RA_DEKU_TREE}, {}, {
	LOCATION(RC_DEKU_TREE_BEFORE_BOSS_LEFT_HEART, (logic->HasItem(RG_BRONZE_SCALE) || (logic->CanUse(RG_IRON_BOOTS) || logic->CanUse(RG_BOOMERANG)))),
	LOCATION(RC_DEKU_TREE_BEFORE_BOSS_MIDDLE_HEART, (logic->HasItem(RG_BRONZE_SCALE) || (logic->CanUse(RG_IRON_BOOTS) || logic->CanUse(RG_BOOMERANG)))),
	LOCATION(RC_DEKU_TREE_BEFORE_BOSS_RIGHT_HEART, (logic->HasItem(RG_BRONZE_SCALE) || (logic->CanUse(RG_IRON_BOOTS) || logic->CanUse(RG_BOOMERANG)))),
	LOCATION(RC_DEKU_TREE_BEFORE_BOSS_GRASS_1, (logic->CanCutShrubs() && logic->HasFireSourceWithTorch())),
	LOCATION(RC_DEKU_TREE_BEFORE_BOSS_GRASS_2, (logic->CanCutShrubs() && logic->HasFireSourceWithTorch())),
	LOCATION(RC_DEKU_TREE_BEFORE_BOSS_GRASS_3, (logic->CanCutShrubs() && logic->HasFireSourceWithTorch())),
}, {
	Entrance(RR_DEKU_TREE_BASEMENT_UPPER, []{return true;}),
	Entrance(RR_DEKU_TREE_BOSS_ENTRYWAY, []{return ((logic->HasItem(RG_BRONZE_SCALE) || Here(RR_DEKU_TREE_OUTSIDE_BOSS_ROOM, []{return logic->CanUse(RG_IRON_BOOTS);})) && Here(RR_DEKU_TREE_OUTSIDE_BOSS_ROOM, []{return logic->CanReflectNuts();}));}),
});
areaTable[RR_DEKU_TREE_MQ_1F] = Region("Deku Tree MQ 1F", SCENE_DEKU_TREE, false, {RA_DEKU_TREE}, {
	EventAccess(&logic->DekuBabaSticks, []{return logic->CanKillEnemy(RE_WITHERED_DEKU_BABA);}),
	EventAccess(&logic->BrokeDeku1FWeb, []{return logic->HasFireSource();}),
}, {
	LOCATION(RC_DEKU_TREE_MQ_LOBBY_GRASS_1, logic->CanCutShrubs()),
	LOCATION(RC_DEKU_TREE_MQ_LOBBY_GRASS_2, logic->CanCutShrubs()),
	LOCATION(RC_DEKU_TREE_MQ_LOBBY_GRASS_3, logic->CanCutShrubs()),
	LOCATION(RC_DEKU_TREE_MQ_LOBBY_GRASS_4, logic->CanCutShrubs()),
	LOCATION(RC_DEKU_TREE_MQ_LOBBY_GRASS_5, logic->CanCutShrubs()),
}, {
	Entrance(RR_DEKU_TREE_ENTRYWAY, []{return true;}),
	Entrance(RR_DEKU_TREE_MQ_2F, []{return true;}),
	Entrance(RR_DEKU_TREE_MQ_BASEMENT, []{return logic->BrokeDeku1FWeb;}),
});
areaTable[RR_DEKU_TREE_MQ_2F] = Region("Deku Tree MQ 2F", SCENE_DEKU_TREE, false, {RA_DEKU_TREE}, {}, {
	LOCATION(RC_DEKU_TREE_MQ_MAP_CHEST, true),
	LOCATION(RC_DEKU_TREE_MQ_GS_LOBBY, logic->CanGetEnemyDrop(RE_GOLD_SKULLTULA)),
	LOCATION(RC_DEKU_TREE_MQ_LOBBY_HEART, true),
	LOCATION(RC_DEKU_TREE_MQ_LOBBY_GRASS_6, logic->CanCutShrubs()),
	LOCATION(RC_DEKU_TREE_MQ_LOBBY_GRASS_7, logic->CanCutShrubs()),
	LOCATION(RC_DEKU_TREE_MQ_LOBBY_CRATE, logic->CanBreakCrates()),
}, {
	Entrance(RR_DEKU_TREE_MQ_1F, []{return true;}),
	Entrance(RR_DEKU_TREE_MQ_3F, []{return true;}),
	Entrance(RR_DEKU_TREE_MQ_EYE_TARGET_ROOM, []{return Here(RR_DEKU_TREE_MQ_2F, []{return logic->HasFireSource();});}),
});
areaTable[RR_DEKU_TREE_MQ_3F] = Region("Deku Tree MQ 3F", SCENE_DEKU_TREE, false, {RA_DEKU_TREE}, {
	EventAccess(&logic->DekuBabaSticks, []{return logic->CanGetDekuBabaSticks();}),
	EventAccess(&logic->DekuBabaNuts, []{return logic->CanGetDekuBabaNuts();}),
	EventAccess(&logic->BrokeDeku1FWeb, []{return true;}),
}, {
	LOCATION(RC_DEKU_TREE_MQ_SLINGSHOT_CHEST, logic->CanKillEnemy(RE_DEKU_BABA)),
	LOCATION(RC_DEKU_TREE_MQ_SLINGSHOT_ROOM_BACK_CHEST, (logic->HasFireSourceWithTorch() || (logic->IsAdult && logic->CanUse(RG_FAIRY_BOW)))),
	LOCATION(RC_DEKU_TREE_MQ_SLINGSHOT_ROOM_HEART, true),
	LOCATION(RC_DEKU_TREE_MQ_SLINGSHOT_GRASS_1, logic->CanCutShrubs()),
	LOCATION(RC_DEKU_TREE_MQ_SLINGSHOT_GRASS_2, logic->CanCutShrubs()),
	LOCATION(RC_DEKU_TREE_MQ_SLINGSHOT_GRASS_3, logic->CanCutShrubs()),
	LOCATION(RC_DEKU_TREE_MQ_SLINGSHOT_GRASS_4, logic->CanCutShrubs()),
	LOCATION(RC_DEKU_TREE_MQ_SLINGSHOT_ROOM_CRATE_1, logic->CanBreakCrates()),
	LOCATION(RC_DEKU_TREE_MQ_SLINGSHOT_ROOM_CRATE_2, logic->CanBreakCrates()),
}, {
	Entrance(RR_DEKU_TREE_MQ_2F, []{return true;}),
	Entrance(RR_DEKU_TREE_MQ_EYE_TARGET_ROOM, []{return Here(RR_DEKU_TREE_MQ_3F, []{return (logic->CanUse(RG_STICKS) || logic->CanUse(RG_FAIRY_BOW));});}),
	Entrance(RR_DEKU_TREE_MQ_BASEMENT, []{return true;}),
});
areaTable[RR_DEKU_TREE_MQ_EYE_TARGET_ROOM] = Region("Deku Tree MQ Eye Target Room", SCENE_DEKU_TREE, false, {RA_DEKU_TREE}, {}, {
	LOCATION(RC_DEKU_TREE_MQ_DEKU_BABA_HEART, true),
	LOCATION(RC_DEKU_TREE_MQ_BEFORE_COMPASS_GRASS_1, logic->CanCutShrubs()),
	LOCATION(RC_DEKU_TREE_MQ_BEFORE_COMPASS_GRASS_2, logic->CanCutShrubs()),
	LOCATION(RC_DEKU_TREE_MQ_BEFORE_COMPASS_GRASS_3, logic->CanCutShrubs()),
	LOCATION(RC_DEKU_TREE_MQ_BEFORE_COMPASS_GRASS_4, logic->CanCutShrubs()),
	LOCATION(RC_DEKU_TREE_MQ_BEFORE_COMPASS_GRASS_5, logic->CanCutShrubs()),
	LOCATION(RC_DEKU_TREE_MQ_BEFORE_COMPASS_GRASS_6, logic->CanCutShrubs()),
	LOCATION(RC_DEKU_TREE_MQ_BEFORE_COMPASS_GRASS_7, logic->CanCutShrubs()),
}, {
	Entrance(RR_DEKU_TREE_MQ_COMPASS_ROOM, []{return Here(RR_DEKU_TREE_MQ_EYE_TARGET_ROOM, []{return logic->CanHitEyeTargets();});}),
	Entrance(RR_DEKU_TREE_MQ_2F, []{return true;}),
});
areaTable[RR_DEKU_TREE_MQ_COMPASS_ROOM] = Region("Deku Tree MQ Compass Room", SCENE_DEKU_TREE, false, {RA_DEKU_TREE}, {}, {
	LOCATION(RC_DEKU_TREE_MQ_COMPASS_CHEST, true),
	LOCATION(RC_DEKU_TREE_MQ_COMPASS_GRASS_1, logic->CanCutShrubs()),
	LOCATION(RC_DEKU_TREE_MQ_COMPASS_GRASS_2, logic->CanCutShrubs()),
	LOCATION(RC_DEKU_TREE_MQ_COMPASS_GRASS_3, logic->CanCutShrubs()),
	LOCATION(RC_DEKU_TREE_MQ_COMPASS_GRASS_4, logic->CanCutShrubs()),
}, {
	Entrance(RR_DEKU_TREE_MQ_EYE_TARGET_ROOM, []{return (logic->CanUse(RG_FAIRY_SLINGSHOT) || logic->CanUse(RG_HOVER_BOOTS));}),
	Entrance(RR_DEKU_TREE_MQ_PAST_BOULDER_VINES, []{return Here(RR_DEKU_TREE_MQ_COMPASS_ROOM, []{return (logic->CanUse(RG_BOMBCHU_5) || ((logic->CanUse(RG_BOMB_BAG) && (logic->CanUse(RG_SONG_OF_TIME) || (logic->IsAdult || logic->CanUse(RG_HOVER_BOOTS)))) || (logic->CanUse(RG_MEGATON_HAMMER) && (logic->CanUse(RG_SONG_OF_TIME) || (bool)ctx->GetTrickOption(RT_DEKU_MQ_COMPASS_GS)))));});}),
});
areaTable[RR_DEKU_TREE_MQ_PAST_BOULDER_VINES] = Region("Deku Tree MQ Past Boulder Vines", SCENE_DEKU_TREE, false, {RA_DEKU_TREE}, {}, {
	LOCATION(RC_DEKU_TREE_MQ_GS_PAST_BOULDER_VINES, logic->CanGetEnemyDrop(RE_GOLD_SKULLTULA, ED_BOOMERANG)),
	LOCATION(RC_DEKU_TREE_MQ_COMPASS_ROOM_HEART, true),
}, {
	Entrance(RR_DEKU_TREE_MQ_COMPASS_ROOM, []{return logic->BlastOrSmash();}),
});
areaTable[RR_DEKU_TREE_MQ_BASEMENT] = Region("Deku Tree MQ Basement", SCENE_DEKU_TREE, false, {RA_DEKU_TREE}, {
	EventAccess(&logic->DekuBabaSticks, []{return logic->CanGetDekuBabaSticks();}),
	EventAccess(&logic->DekuBabaNuts, []{return logic->CanGetDekuBabaNuts();}),
}, {
	LOCATION(RC_DEKU_TREE_MQ_BASEMENT_CHEST, (logic->HasFireSourceWithTorch() || logic->CanUse(RG_FAIRY_BOW))),
	LOCATION(RC_DEKU_TREE_MQ_BASEMENT_LOWER_GRASS_1, logic->CanCutShrubs()),
	LOCATION(RC_DEKU_TREE_MQ_BASEMENT_LOWER_GRASS_2, logic->CanCutShrubs()),
	LOCATION(RC_DEKU_TREE_MQ_BASEMENT_LOWER_GRASS_3, logic->CanCutShrubs()),
	LOCATION(RC_DEKU_TREE_MQ_BASEMENT_LOWER_GRASS_4, logic->CanCutShrubs()),
}, {
	Entrance(RR_DEKU_TREE_MQ_1F, []{return true;}),
	Entrance(RR_DEKU_TREE_MQ_BASEMENT_SOUTHEAST_ROOM, []{return Here(RR_DEKU_TREE_MQ_BASEMENT, []{return logic->CanHitEyeTargets();});}),
	Entrance(RR_DEKU_TREE_MQ_BASEMENT_WATER_ROOM_FRONT, []{return (Here(RR_DEKU_TREE_MQ_BASEMENT, []{return logic->CanHitEyeTargets();}) && (logic->ClearedMQDekuSERoom && Here(RR_DEKU_TREE_MQ_BASEMENT, []{return logic->CanUse(RG_STICKS);})));}),
	Entrance(RR_DEKU_TREE_MQ_BASEMENT_LEDGE, []{return ((bool)ctx->GetTrickOption(RT_DEKU_B1_SKIP) || (logic->PushedDekuBasementBlock || (logic->IsAdult || logic->CanUse(RG_HOVER_BOOTS))));}),
});
areaTable[RR_DEKU_TREE_MQ_BASEMENT_SOUTHEAST_ROOM] = Region("Deku Tree MQ Southeast Room", SCENE_DEKU_TREE, false, {RA_DEKU_TREE}, {
	EventAccess(&logic->ClearedMQDekuSERoom, []{return logic->CanKillEnemy(RE_MAD_SCRUB);}),
}, {
	LOCATION(RC_DEKU_TREE_MQ_BASEMENT_TORCHES_GRASS_1, logic->CanCutShrubs()),
	LOCATION(RC_DEKU_TREE_MQ_BASEMENT_TORCHES_GRASS_2, logic->CanCutShrubs()),
	LOCATION(RC_DEKU_TREE_MQ_BASEMENT_TORCHES_GRASS_3, logic->CanCutShrubs()),
	LOCATION(RC_DEKU_TREE_MQ_BASEMENT_TORCHES_GRASS_4, logic->CanCutShrubs()),
}, {
	Entrance(RR_DEKU_TREE_MQ_BASEMENT_WATER_ROOM_FRONT, []{return logic->HasFireSource();}),
	Entrance(RR_DEKU_TREE_MQ_BASEMENT, []{return logic->ClearedMQDekuSERoom;}),
});
areaTable[RR_DEKU_TREE_MQ_BASEMENT_WATER_ROOM_FRONT] = Region("Deku Tree MQ Basement Water Room Front", SCENE_DEKU_TREE, false, {RA_DEKU_TREE}, {
	EventAccess(&logic->MQDekuWaterRoomTorches, []{return (logic->CanUse(RG_FIRE_ARROWS) || (logic->CanUse(RG_STICKS) && ((bool)ctx->GetTrickOption(RT_DEKU_MQ_LOG) || (logic->IsChild && logic->CanShield()))));}),
}, {
	LOCATION(RC_DEKU_TREE_MQ_BEFORE_SPINNING_LOG_CHEST, true),
	LOCATION(RC_DEKU_TREE_MQ_BASEMENT_SPIKE_ROLLER_FRONT_GRASS_1, logic->CanCutShrubs()),
	LOCATION(RC_DEKU_TREE_MQ_BASEMENT_SPIKE_ROLLER_FRONT_GRASS_2, logic->CanCutShrubs()),
	LOCATION(RC_DEKU_TREE_MQ_BASEMENT_SPIKE_ROLLER_FRONT_GRASS_3, logic->CanCutShrubs()),
}, {
	Entrance(RR_DEKU_TREE_MQ_BASEMENT_WATER_ROOM_BACK, []{return ((bool)ctx->GetTrickOption(RT_DEKU_MQ_LOG) || ((logic->IsChild && logic->CanShield()) || (logic->CanUse(RG_LONGSHOT) || (logic->CanUse(RG_HOOKSHOT) && logic->CanUse(RG_IRON_BOOTS)))));}),
	Entrance(RR_DEKU_TREE_MQ_BASEMENT_SOUTHEAST_ROOM, []{return true;}),
});
areaTable[RR_DEKU_TREE_MQ_BASEMENT_WATER_ROOM_BACK] = Region("Deku Tree MQ Basement Water Room Back", SCENE_DEKU_TREE, false, {RA_DEKU_TREE}, {
	EventAccess(&logic->DekuBabaSticks, []{return logic->CanKillEnemy(RE_WITHERED_DEKU_BABA);}),
	EventAccess(&logic->MQDekuWaterRoomTorches, []{return logic->HasFireSource();}),
}, {
	LOCATION(RC_DEKU_TREE_MQ_AFTER_SPINNING_LOG_CHEST, (logic->CanUse(RG_SONG_OF_TIME) && logic->CanPassEnemy(RE_BIG_SKULLTULA))),
	LOCATION(RC_DEKU_TREE_MQ_BASEMENT_SPIKE_ROLLER_BACK_GRASS_1, logic->CanCutShrubs()),
	LOCATION(RC_DEKU_TREE_MQ_BASEMENT_SPIKE_ROLLER_BACK_GRASS_2, logic->CanCutShrubs()),
}, {
	Entrance(RR_DEKU_TREE_MQ_BASEMENT_SOUTHWEST_ROOM, []{return (logic->MQDekuWaterRoomTorches && logic->CanPassEnemy(RE_BIG_SKULLTULA, (logic->CanUse(RG_SONG_OF_TIME) ? ED_CLOSE : ED_SHORT_JUMPSLASH)));}),
	Entrance(RR_DEKU_TREE_MQ_BASEMENT_WATER_ROOM_FRONT, []{return ((bool)ctx->GetTrickOption(RT_DEKU_MQ_LOG) || ((logic->IsChild && logic->CanShield()) || (logic->CanUse(RG_LONGSHOT) || (logic->HasItem(RG_BRONZE_SCALE) || (logic->CanUse(RG_IRON_BOOTS) && (logic->IsAdult || logic->CanUse(RG_HOOKSHOT)))))));}),
});
areaTable[RR_DEKU_TREE_MQ_BASEMENT_SOUTHWEST_ROOM] = Region("Deku Tree MQ Basement Southwest Room", SCENE_DEKU_TREE, false, {RA_DEKU_TREE}, {}, {
	LOCATION(RC_DEKU_TREE_MQ_BASEMENT_LARVAE_GRASS_1, logic->CanCutShrubs()),
	LOCATION(RC_DEKU_TREE_MQ_BASEMENT_LARVAE_GRASS_2, logic->CanCutShrubs()),
}, {
	Entrance(RR_DEKU_TREE_MQ_BASEMENT_GRAVE_ROOM, []{return Here(RR_DEKU_TREE_MQ_BASEMENT_SOUTHWEST_ROOM, []{return (logic->CanKillEnemy(RE_MAD_SCRUB) && logic->CanKillEnemy(RE_KEESE));});}),
	Entrance(RR_DEKU_TREE_MQ_BASEMENT_WATER_ROOM_BACK, []{return Here(RR_DEKU_TREE_MQ_BASEMENT_SOUTHWEST_ROOM, []{return (logic->CanKillEnemy(RE_MAD_SCRUB) && logic->CanKillEnemy(RE_KEESE));});}),
});
areaTable[RR_DEKU_TREE_MQ_BASEMENT_GRAVE_ROOM] = Region("Deku Tree MQ Basement Grave Room", SCENE_DEKU_TREE, false, {RA_DEKU_TREE}, {
	EventAccess(&logic->DekuBabaSticks, []{return logic->CanGetDekuBabaSticks();}),
	EventAccess(&logic->DekuBabaNuts, []{return logic->CanGetDekuBabaNuts();}),
}, {
	LOCATION(RC_DEKU_TREE_MQ_GS_BASEMENT_GRAVES_ROOM, (logic->CanUse(RG_LONGSHOT) || (logic->CanUse(RG_SONG_OF_TIME) && logic->CanGetEnemyDrop(RE_GOLD_SKULLTULA, ED_BOOMERANG)))),
	LOCATION(RC_DEKU_TREE_MQ_BASEMENT_GRAVES_GRASS_1, logic->CanCutShrubs()),
	LOCATION(RC_DEKU_TREE_MQ_BASEMENT_GRAVES_GRASS_2, logic->CanCutShrubs()),
	LOCATION(RC_DEKU_TREE_MQ_BASEMENT_GRAVES_GRASS_3, logic->CanCutShrubs()),
	LOCATION(RC_DEKU_TREE_MQ_BASEMENT_GRAVES_GRASS_4, logic->CanCutShrubs()),
	LOCATION(RC_DEKU_TREE_MQ_BASEMENT_GRAVES_GRASS_5, logic->CanCutShrubs()),
}, {
	Entrance(RR_DEKU_TREE_MQ_BASEMENT_LEDGE, []{return (logic->IsChild && Here(RR_DEKU_TREE_MQ_BASEMENT_GRAVE_ROOM, []{return (logic->HasFireSourceWithTorch() || logic->CanUse(RG_FAIRY_BOW));}));}),
	Entrance(RR_DEKU_TREE_MQ_BASEMENT_SOUTHWEST_ROOM, []{return true;}),
	Entrance(RR_DEKU_TREE_MQ_BASEMENT_BACK_ROOM, []{return Here(RR_DEKU_TREE_MQ_BASEMENT_GRAVE_ROOM, []{return (logic->HasFireSourceWithTorch() || logic->CanUse(RG_FAIRY_BOW));});}),
});
areaTable[RR_DEKU_TREE_MQ_BASEMENT_BACK_ROOM] = Region("Deku Tree MQ Basement Back Room", SCENE_DEKU_TREE, false, {RA_DEKU_TREE}, {}, {
	LOCATION(RC_DEKU_TREE_MQ_GS_BASEMENT_BACK_ROOM, logic->CanGetEnemyDrop(RE_GOLD_SKULLTULA, ED_BOOMERANG)),
	LOCATION(RC_DEKU_TREE_MQ_BASEMENT_BACK_GRASS_1, logic->CanCutShrubs()),
	LOCATION(RC_DEKU_TREE_MQ_BASEMENT_BACK_GRASS_2, logic->CanCutShrubs()),
	LOCATION(RC_DEKU_TREE_MQ_BASEMENT_BACK_GRASS_3, logic->CanCutShrubs()),
}, {
	Entrance(RR_DEKU_TREE_MQ_BASEMENT_GRAVE_ROOM, []{return true;}),
});
areaTable[RR_DEKU_TREE_MQ_BASEMENT_LEDGE] = Region("Deku Tree MQ Basement Ledge", SCENE_DEKU_TREE, false, {RA_DEKU_TREE}, {
	EventAccess(&logic->PushedDekuBasementBlock, []{return true;}),
}, {
	LOCATION(RC_DEKU_TREE_MQ_DEKU_SCRUB, logic->CanStunDeku()),
	LOCATION(RC_DEKU_TREE_MQ_BASEMENT_UPPER_GRASS_1, logic->CanCutShrubs()),
	LOCATION(RC_DEKU_TREE_MQ_BASEMENT_UPPER_GRASS_2, logic->CanCutShrubs()),
	LOCATION(RC_DEKU_TREE_MQ_BASEMENT_UPPER_GRASS_3, logic->CanCutShrubs()),
}, {
	Entrance(RR_DEKU_TREE_MQ_BASEMENT_GRAVE_ROOM, []{return logic->IsChild;}),
	Entrance(RR_DEKU_TREE_MQ_BASEMENT, []{return true;}),
	Entrance(RR_DEKU_TREE_MQ_OUTSIDE_BOSS_ROOM, []{return (Here(RR_DEKU_TREE_MQ_BASEMENT_LEDGE, []{return (logic->HasFireSource() || logic->CanUse(RG_STICKS));}) && (logic->HasItem(RG_BRONZE_SCALE) || logic->CanUse(RG_IRON_BOOTS)));}),
});
areaTable[RR_DEKU_TREE_MQ_OUTSIDE_BOSS_ROOM] = Region("Deku Tree MQ Outside Boss Room", SCENE_DEKU_TREE, false, {RA_DEKU_TREE}, {}, {
	LOCATION(RC_DEKU_TREE_MQ_BEFORE_BOSS_LEFT_HEART, (logic->HasItem(RG_BRONZE_SCALE) || (logic->CanUse(RG_IRON_BOOTS) || logic->CanUse(RG_BOOMERANG)))),
	LOCATION(RC_DEKU_TREE_MQ_BEFORE_BOSS_MIDDLE_HEART, (logic->HasItem(RG_BRONZE_SCALE) || (logic->CanUse(RG_IRON_BOOTS) || logic->CanUse(RG_BOOMERANG)))),
	LOCATION(RC_DEKU_TREE_MQ_BEFORE_BOSS_RIGHT_HEART, (logic->HasItem(RG_BRONZE_SCALE) || (logic->CanUse(RG_IRON_BOOTS) || logic->CanUse(RG_BOOMERANG)))),
	LOCATION(RC_DEKU_TREE_MQ_BEFORE_BOSS_GRASS_1, logic->CanCutShrubs()),
	LOCATION(RC_DEKU_TREE_MQ_BEFORE_BOSS_GRASS_2, logic->CanCutShrubs()),
	LOCATION(RC_DEKU_TREE_MQ_BEFORE_BOSS_GRASS_3, logic->CanCutShrubs()),
}, {
	Entrance(RR_DEKU_TREE_MQ_BASEMENT_LEDGE, []{return (logic->HasItem(RG_BRONZE_SCALE) || logic->CanUse(RG_HOOKSHOT));}),
	Entrance(RR_DEKU_TREE_BOSS_ENTRYWAY, []{return Here(RR_DEKU_TREE_MQ_OUTSIDE_BOSS_ROOM, []{return logic->CanReflectNuts();});}),
});
areaTable[RR_DEKU_TREE_BOSS_ENTRYWAY] = Region("Deku Tree Boss Entryway", SCENE_DEKU_TREE, false, {RA_DEKU_TREE}, {}, {}, {
	Entrance(RR_DEKU_TREE_BOSS_ROOM, []{return true;}),
});
areaTable[RR_DEKU_TREE_BOSS_EXIT] = Region("Deku Tree Boss Exit", SCENE_DEKU_TREE, false, {RA_DEKU_TREE}, {}, {}, {
	Entrance(RR_DEKU_TREE_OUTSIDE_BOSS_ROOM, []{return ctx->GetDungeon(Rando::DEKU_TREE)->IsVanilla();}),
	Entrance(RR_DEKU_TREE_MQ_OUTSIDE_BOSS_ROOM, []{return ctx->GetDungeon(Rando::DEKU_TREE)->IsMQ();}),
});
areaTable[RR_DEKU_TREE_BOSS_ROOM] = Region("Deku Tree Boss Room", SCENE_DEKU_TREE_BOSS, false, {}, {
	EventAccess(&logic->DekuTreeClear, []{return logic->CanKillEnemy(RE_GOHMA);}),
}, {
	LOCATION(RC_QUEEN_GOHMA, logic->DekuTreeClear),
	LOCATION(RC_DEKU_TREE_QUEEN_GOHMA_HEART, logic->DekuTreeClear),
	LOCATION(RC_DEKU_TREE_QUEEN_GOHMA_GRASS_1, logic->CanCutShrubs()),
	LOCATION(RC_DEKU_TREE_QUEEN_GOHMA_GRASS_2, logic->CanCutShrubs()),
	LOCATION(RC_DEKU_TREE_QUEEN_GOHMA_GRASS_3, logic->CanCutShrubs()),
	LOCATION(RC_DEKU_TREE_QUEEN_GOHMA_GRASS_4, logic->CanCutShrubs()),
	LOCATION(RC_DEKU_TREE_QUEEN_GOHMA_GRASS_5, logic->CanCutShrubs()),
	LOCATION(RC_DEKU_TREE_QUEEN_GOHMA_GRASS_6, logic->CanCutShrubs()),
	LOCATION(RC_DEKU_TREE_QUEEN_GOHMA_GRASS_7, logic->CanCutShrubs()),
	LOCATION(RC_DEKU_TREE_QUEEN_GOHMA_GRASS_8, logic->CanCutShrubs()),
}, {
	Entrance(RR_DEKU_TREE_BOSS_EXIT, []{return true;}),
	Entrance(RR_KF_OUTSIDE_DEKU_TREE, []{return logic->DekuTreeClear;}, "", false),
});
areaTable[RR_DODONGOS_CAVERN_BEGINNING] = Region("Dodongos Cavern Beginning", SCENE_DODONGOS_CAVERN, false, {RA_DODONGOS_CAVERN}, {}, {}, {
	Entrance(RR_DODONGOS_CAVERN_ENTRYWAY, []{return true;}),
	Entrance(RR_DODONGOS_CAVERN_LOBBY, []{return Here(RR_DODONGOS_CAVERN_BEGINNING, []{return (logic->CanBreakMudWalls() || logic->HasItem(RG_GORONS_BRACELET));});}),
});
areaTable[RR_DODONGOS_CAVERN_LOBBY] = Region("Dodongos Cavern Lobby", SCENE_DODONGOS_CAVERN, false, {RA_DODONGOS_CAVERN}, {
	EventAccess(&logic->GossipStoneFairy, []{return ((Here(RR_DODONGOS_CAVERN_LOBBY, []{return logic->CanBreakMudWalls();}) || logic->HasItem(RG_GORONS_BRACELET)) && logic->CallGossipFairy());}),
}, {
	LOCATION(RC_DODONGOS_CAVERN_MAP_CHEST, Here(RR_DODONGOS_CAVERN_LOBBY, []{return (logic->CanBreakMudWalls() || logic->HasItem(RG_GORONS_BRACELET));})),
	LOCATION(RC_DODONGOS_CAVERN_DEKU_SCRUB_LOBBY, (logic->CanStunDeku() || logic->HasItem(RG_GORONS_BRACELET))),
	LOCATION(RC_DODONGOS_CAVERN_GOSSIP_STONE_FAIRY, (Here(RR_DODONGOS_CAVERN_LOBBY, []{return (logic->CanBreakMudWalls() || logic->HasItem(RG_GORONS_BRACELET));}) && logic->CallGossipFairy())),
	LOCATION(RC_DODONGOS_CAVERN_GOSSIP_STONE_FAIRY_BIG, (Here(RR_DODONGOS_CAVERN_LOBBY, []{return (logic->CanBreakMudWalls() || logic->HasItem(RG_GORONS_BRACELET));}) && logic->CanUse(RG_SONG_OF_STORMS))),
	LOCATION(RC_DODONGOS_CAVERN_GOSSIP_STONE, Here(RR_DODONGOS_CAVERN_LOBBY, []{return (logic->CanBreakMudWalls() || logic->HasItem(RG_GORONS_BRACELET));})),
}, {
	Entrance(RR_DODONGOS_CAVERN_BEGINNING, []{return true;}),
	Entrance(RR_DODONGOS_CAVERN_LOBBY_SWITCH, []{return logic->IsAdult;}),
	Entrance(RR_DODONGOS_CAVERN_SE_CORRIDOR, []{return Here(RR_DODONGOS_CAVERN_LOBBY, []{return (logic->CanBreakMudWalls() || logic->HasItem(RG_GORONS_BRACELET));});}),
	Entrance(RR_DODONGOS_CAVERN_STAIRS_LOWER, []{return HasAccessTo(RR_DODONGOS_CAVERN_LOBBY_SWITCH);}),
	Entrance(RR_DODONGOS_CAVERN_FAR_BRIDGE, []{return HasAccessTo(RR_DODONGOS_CAVERN_FAR_BRIDGE);}),
	Entrance(RR_DODONGOS_CAVERN_BOSS_AREA, []{return Here(RR_DODONGOS_CAVERN_LOBBY, []{return logic->HasExplosives();});}),
	Entrance(RR_DODONGOS_CAVERN_BOSS_ENTRYWAY, []{return false;}),
});
areaTable[RR_DODONGOS_CAVERN_LOBBY_SWITCH] = Region("Dodongos Cavern Lobby Switch", SCENE_DODONGOS_CAVERN, false, {RA_DODONGOS_CAVERN}, {}, {}, {
	Entrance(RR_DODONGOS_CAVERN_LOBBY, []{return true;}),
	Entrance(RR_DODONGOS_CAVERN_DODONGO_ROOM, []{return true;}),
});
areaTable[RR_DODONGOS_CAVERN_SE_CORRIDOR] = Region("Dodongos Cavern SE Corridor", SCENE_DODONGOS_CAVERN, false, {RA_DODONGOS_CAVERN}, {}, {
	LOCATION(RC_DODONGOS_CAVERN_GS_SCARECROW, (logic->CanUse(RG_SCARECROW) || ((logic->IsAdult && logic->CanUse(RG_LONGSHOT)) || ((bool)ctx->GetTrickOption(RT_DC_SCARECROW_GS) && logic->CanAttack())))),
	LOCATION(RC_DODONGOS_CAVERN_SIDE_ROOM_POT_1, logic->CanBreakPots()),
	LOCATION(RC_DODONGOS_CAVERN_SIDE_ROOM_POT_2, logic->CanBreakPots()),
	LOCATION(RC_DODONGOS_CAVERN_SIDE_ROOM_POT_3, logic->CanBreakPots()),
	LOCATION(RC_DODONGOS_CAVERN_SIDE_ROOM_POT_4, logic->CanBreakPots()),
	LOCATION(RC_DODONGOS_CAVERN_SIDE_ROOM_POT_5, logic->CanBreakPots()),
	LOCATION(RC_DODONGOS_CAVERN_SIDE_ROOM_POT_6, logic->CanBreakPots()),
}, {
	Entrance(RR_DODONGOS_CAVERN_LOBBY, []{return true;}),
	Entrance(RR_DODONGOS_CAVERN_SE_ROOM, []{return Here(RR_DODONGOS_CAVERN_SE_CORRIDOR, []{return (logic->CanBreakMudWalls() || (logic->CanAttack() || (logic->TakeDamage() && logic->CanShield())));});}),
	Entrance(RR_DODONGOS_CAVERN_NEAR_LOWER_LIZALFOS, []{return true;}),
});
areaTable[RR_DODONGOS_CAVERN_SE_ROOM] = Region("Dodongos Cavern SE Room", SCENE_DODONGOS_CAVERN, false, {RA_DODONGOS_CAVERN}, {}, {
	LOCATION(RC_DODONGOS_CAVERN_GS_SIDE_ROOM_NEAR_LOWER_LIZALFOS, logic->CanAttack()),
}, {
	Entrance(RR_DODONGOS_CAVERN_SE_CORRIDOR, []{return true;}),
});
areaTable[RR_DODONGOS_CAVERN_NEAR_LOWER_LIZALFOS] = Region("Dodongos Cavern Near Lower Lizalfos", SCENE_DODONGOS_CAVERN, false, {RA_DODONGOS_CAVERN}, {}, {}, {
	Entrance(RR_DODONGOS_CAVERN_SE_CORRIDOR, []{return true;}),
	Entrance(RR_DODONGOS_CAVERN_LOWER_LIZALFOS, []{return true;}),
});
areaTable[RR_DODONGOS_CAVERN_LOWER_LIZALFOS] = Region("Dodongos Cavern Lower Lizalfos", SCENE_DODONGOS_CAVERN, false, {RA_DODONGOS_CAVERN}, {}, {
	LOCATION(RC_DODONGOS_CAVERN_LIZALFOS_POT_1, logic->CanBreakPots()),
	LOCATION(RC_DODONGOS_CAVERN_LIZALFOS_POT_2, logic->CanBreakPots()),
	LOCATION(RC_DODONGOS_CAVERN_LIZALFOS_POT_3, logic->CanBreakPots()),
	LOCATION(RC_DODONGOS_CAVERN_LIZALFOS_POT_4, logic->CanBreakPots()),
	LOCATION(RC_DODONGOS_CAVERN_LOWER_LIZALFOS_HEART, true),
}, {
	Entrance(RR_DODONGOS_CAVERN_NEAR_LOWER_LIZALFOS, []{return Here(RR_DODONGOS_CAVERN_LOWER_LIZALFOS, []{return logic->CanKillEnemy(RE_LIZALFOS, ED_CLOSE, true, 2);});}),
	Entrance(RR_DODONGOS_CAVERN_DODONGO_ROOM, []{return Here(RR_DODONGOS_CAVERN_LOWER_LIZALFOS, []{return logic->CanKillEnemy(RE_LIZALFOS, ED_CLOSE, true, 2);});}),
});
areaTable[RR_DODONGOS_CAVERN_DODONGO_ROOM] = Region("Dodongos Cavern Dodongo Room", SCENE_DODONGOS_CAVERN, false, {RA_DODONGOS_CAVERN}, {}, {
	LOCATION(RC_DODONGOS_CAVERN_TORCH_ROOM_POT_1, logic->CanBreakPots()),
	LOCATION(RC_DODONGOS_CAVERN_TORCH_ROOM_POT_2, logic->CanBreakPots()),
	LOCATION(RC_DODONGOS_CAVERN_TORCH_ROOM_POT_3, logic->CanBreakPots()),
	LOCATION(RC_DODONGOS_CAVERN_TORCH_ROOM_POT_4, logic->CanBreakPots()),
}, {
	Entrance(RR_DODONGOS_CAVERN_LOBBY_SWITCH, []{return logic->HasFireSourceWithTorch();}),
	Entrance(RR_DODONGOS_CAVERN_LOWER_LIZALFOS, []{return true;}),
	Entrance(RR_DODONGOS_CAVERN_NEAR_DODONGO_ROOM, []{return Here(RR_DODONGOS_CAVERN_DODONGO_ROOM, []{return (logic->CanBreakMudWalls() || logic->HasItem(RG_GORONS_BRACELET));});}),
});
areaTable[RR_DODONGOS_CAVERN_NEAR_DODONGO_ROOM] = Region("Dodongos Cavern Near Dodongo Room", SCENE_DODONGOS_CAVERN, false, {RA_DODONGOS_CAVERN}, {}, {
	LOCATION(RC_DODONGOS_CAVERN_DEKU_SCRUB_SIDE_ROOM_NEAR_DODONGOS, logic->CanStunDeku()),
}, {
	Entrance(RR_DODONGOS_CAVERN_DODONGO_ROOM, []{return true;}),
});
areaTable[RR_DODONGOS_CAVERN_STAIRS_LOWER] = Region("Dodongos Cavern Stairs Lower", SCENE_DODONGOS_CAVERN, false, {RA_DODONGOS_CAVERN}, {}, {}, {
	Entrance(RR_DODONGOS_CAVERN_LOBBY, []{return true;}),
	Entrance(RR_DODONGOS_CAVERN_STAIRS_UPPER, []{return (logic->HasExplosives() || (logic->HasItem(RG_GORONS_BRACELET) || (logic->CanUse(RG_DINS_FIRE) || ((bool)ctx->GetTrickOption(RT_DC_STAIRS_WITH_BOW) && logic->CanUse(RG_FAIRY_BOW)))));}),
	Entrance(RR_DODONGOS_CAVERN_COMPASS_ROOM, []{return Here(RR_DODONGOS_CAVERN_STAIRS_LOWER, []{return (logic->CanBreakMudWalls() || logic->HasItem(RG_GORONS_BRACELET));});}),
});
areaTable[RR_DODONGOS_CAVERN_STAIRS_UPPER] = Region("Dodongos Cavern Stairs Upper", SCENE_DODONGOS_CAVERN, false, {RA_DODONGOS_CAVERN}, {}, {
	LOCATION(RC_DODONGOS_CAVERN_GS_ALCOVE_ABOVE_STAIRS, (Here(RR_DODONGOS_CAVERN_STAIRS_UPPER, []{return logic->HookshotOrBoomerang();}) || logic->CanUse(RG_LONGSHOT))),
	LOCATION(RC_DODONGOS_CAVERN_GS_VINES_ABOVE_STAIRS, (logic->IsAdult || (logic->CanAttack() || (HasAccessTo(RR_DODONGOS_CAVERN_STAIRS_LOWER) && (logic->CanUse(RG_LONGSHOT) && (bool)ctx->GetTrickOption(RT_DC_VINES_GS)))))),
	LOCATION(RC_DODONGOS_CAVERN_STAIRCASE_POT_1, logic->CanBreakPots()),
	LOCATION(RC_DODONGOS_CAVERN_STAIRCASE_POT_2, logic->CanBreakPots()),
	LOCATION(RC_DODONGOS_CAVERN_STAIRCASE_POT_3, logic->CanBreakPots()),
	LOCATION(RC_DODONGOS_CAVERN_STAIRCASE_POT_4, logic->CanBreakPots()),
}, {
	Entrance(RR_DODONGOS_CAVERN_STAIRS_LOWER, []{return true;}),
	Entrance(RR_DODONGOS_CAVERN_ARMOS_ROOM, []{return true;}),
});
areaTable[RR_DODONGOS_CAVERN_COMPASS_ROOM] = Region("Dodongos Cavern Compass Room", SCENE_DODONGOS_CAVERN, false, {RA_DODONGOS_CAVERN}, {}, {
	LOCATION(RC_DODONGOS_CAVERN_COMPASS_CHEST, true),
}, {
	Entrance(RR_DODONGOS_CAVERN_STAIRS_LOWER, []{return (logic->CanUse(RG_MASTER_SWORD) || (logic->CanUse(RG_BIGGORON_SWORD) || (logic->CanUse(RG_MEGATON_HAMMER) || (logic->HasExplosives() || logic->HasItem(RG_GORONS_BRACELET)))));}),
});
areaTable[RR_DODONGOS_CAVERN_ARMOS_ROOM] = Region("Dodongos Cavern Armos Room", SCENE_DODONGOS_CAVERN, false, {RA_DODONGOS_CAVERN}, {}, {}, {
	Entrance(RR_DODONGOS_CAVERN_STAIRS_UPPER, []{return true;}),
	Entrance(RR_DODONGOS_CAVERN_BOMB_ROOM_LOWER, []{return true;}),
});
areaTable[RR_DODONGOS_CAVERN_BOMB_ROOM_LOWER] = Region("Dodongos Cavern Bomb Room Lower", SCENE_DODONGOS_CAVERN, false, {RA_DODONGOS_CAVERN}, {}, {
	LOCATION(RC_DODONGOS_CAVERN_BOMB_FLOWER_PLATFORM_CHEST, true),
	LOCATION(RC_DODONGOS_CAVERN_BLADE_ROOM_HEART, true),
	LOCATION(RC_DODONGOS_CAVERN_FIRST_BRIDGE_GRASS, logic->CanCutShrubs()),
	LOCATION(RC_DODONGOS_CAVERN_BLADE_GRASS, logic->CanCutShrubs()),
}, {
	Entrance(RR_DODONGOS_CAVERN_ARMOS_ROOM, []{return true;}),
	Entrance(RR_DODONGOS_CAVERN_2F_SIDE_ROOM, []{return Here(RR_DODONGOS_CAVERN_BOMB_ROOM_LOWER, []{return (logic->CanBreakMudWalls() || ((bool)ctx->GetTrickOption(RT_DC_SCRUB_ROOM) && logic->HasItem(RG_GORONS_BRACELET)));});}),
	Entrance(RR_DODONGOS_CAVERN_FIRST_SLINGSHOT_ROOM, []{return Here(RR_DODONGOS_CAVERN_BOMB_ROOM_LOWER, []{return (logic->CanBreakMudWalls() || logic->HasItem(RG_GORONS_BRACELET));});}),
	Entrance(RR_DODONGOS_CAVERN_BOMB_ROOM_UPPER, []{return ((logic->IsAdult && (bool)ctx->GetTrickOption(RT_DC_JUMP)) || (logic->CanUse(RG_HOVER_BOOTS) || ((logic->IsAdult && logic->CanUse(RG_LONGSHOT)) || ((bool)ctx->GetTrickOption(RT_DAMAGE_BOOST_SIMPLE) && (logic->HasExplosives() && logic->CanJumpslash())))));}),
});
areaTable[RR_DODONGOS_CAVERN_2F_SIDE_ROOM] = Region("Dodongos Cavern 2F Side Room", SCENE_DODONGOS_CAVERN, false, {RA_DODONGOS_CAVERN}, {}, {
	LOCATION(RC_DODONGOS_CAVERN_DEKU_SCRUB_NEAR_BOMB_BAG_LEFT, logic->CanStunDeku()),
	LOCATION(RC_DODONGOS_CAVERN_DEKU_SCRUB_NEAR_BOMB_BAG_RIGHT, logic->CanStunDeku()),
}, {
	Entrance(RR_DODONGOS_CAVERN_BOMB_ROOM_LOWER, []{return true;}),
});
areaTable[RR_DODONGOS_CAVERN_FIRST_SLINGSHOT_ROOM] = Region("Dodongos Cavern First Slingshot Room", SCENE_DODONGOS_CAVERN, false, {RA_DODONGOS_CAVERN}, {}, {
	LOCATION(RC_DODONGOS_CAVERN_SINGLE_EYE_POT_1, logic->CanBreakPots()),
	LOCATION(RC_DODONGOS_CAVERN_SINGLE_EYE_POT_2, logic->CanBreakPots()),
	LOCATION(RC_DODONGOS_CAVERN_SINGLE_EYE_GRASS, logic->CanCutShrubs()),
}, {
	Entrance(RR_DODONGOS_CAVERN_BOMB_ROOM_LOWER, []{return true;}),
	Entrance(RR_DODONGOS_CAVERN_UPPER_LIZALFOS, []{return (logic->CanUse(RG_FAIRY_SLINGSHOT) || (logic->CanUse(RG_FAIRY_BOW) || (bool)ctx->GetTrickOption(RT_DC_SLINGSHOT_SKIP)));}),
});
areaTable[RR_DODONGOS_CAVERN_UPPER_LIZALFOS] = Region("Dodongos Cavern Upper Lizalfos", SCENE_DODONGOS_CAVERN, false, {RA_DODONGOS_CAVERN}, {}, {
	LOCATION(RC_DODONGOS_CAVERN_LOWER_LIZALFOS_HEART, true),
	LOCATION(RC_DODONGOS_CAVERN_UPPER_LIZALFOS_LEFT_HEART, true),
	LOCATION(RC_DODONGOS_CAVERN_UPPER_LIZALFOS_RIGHT_HEART, true),
}, {
	Entrance(RR_DODONGOS_CAVERN_LOWER_LIZALFOS, []{return true;}),
	Entrance(RR_DODONGOS_CAVERN_FIRST_SLINGSHOT_ROOM, []{return Here(RR_DODONGOS_CAVERN_UPPER_LIZALFOS, []{return logic->CanKillEnemy(RE_LIZALFOS, ED_CLOSE, true, 2);});}),
	Entrance(RR_DODONGOS_CAVERN_SECOND_SLINGSHOT_ROOM, []{return Here(RR_DODONGOS_CAVERN_UPPER_LIZALFOS, []{return logic->CanKillEnemy(RE_LIZALFOS, ED_CLOSE, true, 2);});}),
});
areaTable[RR_DODONGOS_CAVERN_SECOND_SLINGSHOT_ROOM] = Region("Dodongos Cavern Second Slingshot Room", SCENE_DODONGOS_CAVERN, false, {RA_DODONGOS_CAVERN}, {}, {
	LOCATION(RC_DODONGOS_CAVERN_DOUBLE_EYE_POT_1, logic->CanBreakPots()),
	LOCATION(RC_DODONGOS_CAVERN_DOUBLE_EYE_POT_2, logic->CanBreakPots()),
}, {
	Entrance(RR_DODONGOS_CAVERN_UPPER_LIZALFOS, []{return true;}),
	Entrance(RR_DODONGOS_CAVERN_BOMB_ROOM_UPPER, []{return (logic->CanUse(RG_FAIRY_SLINGSHOT) || (logic->CanUse(RG_FAIRY_BOW) || (bool)ctx->GetTrickOption(RT_DC_SLINGSHOT_SKIP)));}),
});
areaTable[RR_DODONGOS_CAVERN_BOMB_ROOM_UPPER] = Region("Dodongos Cavern Bomb Room Upper", SCENE_DODONGOS_CAVERN, false, {RA_DODONGOS_CAVERN}, {}, {
	LOCATION(RC_DODONGOS_CAVERN_BOMB_BAG_CHEST, true),
	LOCATION(RC_DODONGOS_CAVERN_BLADE_POT_1, logic->CanBreakPots()),
	LOCATION(RC_DODONGOS_CAVERN_BLADE_POT_2, logic->CanBreakPots()),
}, {
	Entrance(RR_DODONGOS_CAVERN_BOMB_ROOM_LOWER, []{return true;}),
	Entrance(RR_DODONGOS_CAVERN_SECOND_SLINGSHOT_ROOM, []{return true;}),
	Entrance(RR_DODONGOS_CAVERN_FAR_BRIDGE, []{return true;}),
});
areaTable[RR_DODONGOS_CAVERN_FAR_BRIDGE] = Region("Dodongos Cavern Far Bridge", SCENE_DODONGOS_CAVERN, false, {RA_DODONGOS_CAVERN}, {}, {
	LOCATION(RC_DODONGOS_CAVERN_END_OF_BRIDGE_CHEST, Here(RR_DODONGOS_CAVERN_FAR_BRIDGE, []{return logic->CanBreakMudWalls();})),
}, {
	Entrance(RR_DODONGOS_CAVERN_LOBBY, []{return true;}),
	Entrance(RR_DODONGOS_CAVERN_BOMB_ROOM_UPPER, []{return true;}),
});
areaTable[RR_DODONGOS_CAVERN_BOSS_AREA] = Region("Dodongos Cavern Boss Region", SCENE_DODONGOS_CAVERN, false, {RA_DODONGOS_CAVERN}, {
	EventAccess(&logic->FairyPot, []{return true;}),
}, {
	LOCATION(RC_DODONGOS_CAVERN_BEFORE_BOSS_GRASS, logic->CanCutShrubs()),
}, {
	Entrance(RR_DODONGOS_CAVERN_LOBBY, []{return true;}),
	Entrance(RR_DODONGOS_CAVERN_BACK_ROOM, []{return Here(RR_DODONGOS_CAVERN_BOSS_AREA, []{return logic->CanBreakMudWalls();});}),
	Entrance(RR_DODONGOS_CAVERN_BOSS_ENTRYWAY, []{return true;}),
});
areaTable[RR_DODONGOS_CAVERN_BACK_ROOM] = Region("Dodongos Cavern Back Room", SCENE_DODONGOS_CAVERN, false, {RA_DODONGOS_CAVERN}, {}, {
	LOCATION(RC_DODONGOS_CAVERN_GS_BACK_ROOM, logic->CanAttack()),
	LOCATION(RC_DODONGOS_CAVERN_BACK_ROOM_POT_1, logic->CanBreakPots()),
	LOCATION(RC_DODONGOS_CAVERN_BACK_ROOM_POT_2, logic->CanBreakPots()),
	LOCATION(RC_DODONGOS_CAVERN_BACK_ROOM_POT_3, logic->CanBreakPots()),
	LOCATION(RC_DODONGOS_CAVERN_BACK_ROOM_POT_4, logic->CanBreakPots()),
}, {
	Entrance(RR_DODONGOS_CAVERN_BOSS_AREA, []{return true;}),
});
areaTable[RR_DODONGOS_CAVERN_MQ_BEGINNING] = Region("Dodongos Cavern MQ Beginning", SCENE_DODONGOS_CAVERN, false, {RA_DODONGOS_CAVERN}, {}, {}, {
	Entrance(RR_DODONGOS_CAVERN_ENTRYWAY, []{return true;}),
	Entrance(RR_DODONGOS_CAVERN_MQ_LOBBY, []{return Here(RR_DODONGOS_CAVERN_MQ_BEGINNING, []{return (logic->CanBreakMudWalls() || logic->HasItem(RG_GORONS_BRACELET));});}),
});
areaTable[RR_DODONGOS_CAVERN_MQ_LOBBY] = Region("Dodongos Cavern MQ Lobby", SCENE_DODONGOS_CAVERN, false, {RA_DODONGOS_CAVERN}, {}, {
	LOCATION(RC_DODONGOS_CAVERN_MQ_MAP_CHEST, (logic->CanBreakMudWalls() || logic->HasItem(RG_GORONS_BRACELET))),
	LOCATION(RC_DODONGOS_CAVERN_MQ_DEKU_SCRUB_LOBBY_REAR, logic->CanStunDeku()),
	LOCATION(RC_DODONGOS_CAVERN_MQ_DEKU_SCRUB_LOBBY_FRONT, logic->CanStunDeku()),
}, {
	Entrance(RR_DODONGOS_CAVERN_MQ_BEGINNING, []{return true;}),
	Entrance(RR_DODONGOS_CAVERN_MQ_GOSSIP_STONE, []{return Here(RR_DODONGOS_CAVERN_MQ_LOBBY, []{return (logic->CanBreakMudWalls() || logic->HasItem(RG_GORONS_BRACELET));});}),
	Entrance(RR_DODONGOS_CAVERN_MQ_MOUTH_SIDE_BRIDGE, []{return Here(RR_DODONGOS_CAVERN_MQ_LOBBY, []{return (logic->BlastOrSmash() || logic->HasItem(RG_GORONS_BRACELET));});}),
	Entrance(RR_DODONGOS_CAVERN_MQ_STAIRS_LOWER, []{return Here(RR_DODONGOS_CAVERN_MQ_LOBBY, []{return (logic->BlastOrSmash() || logic->HasItem(RG_GORONS_BRACELET));});}),
	Entrance(RR_DODONGOS_CAVERN_MQ_LOWER_RIGHT_SIDE, []{return (Here(RR_DODONGOS_CAVERN_MQ_LOBBY, []{return logic->CanBreakMudWalls();}) || Here(RR_DODONGOS_CAVERN_MQ_LOBBY, []{return (logic->HasItem(RG_GORONS_BRACELET) && logic->TakeDamage());}));}),
	Entrance(RR_DODONGOS_CAVERN_MQ_POES_ROOM, []{return logic->IsAdult;}),
	Entrance(RR_DODONGOS_CAVERN_MQ_BEHIND_MOUTH, []{return Here(RR_DODONGOS_CAVERN_MQ_LOBBY, []{return (logic->HasExplosives() || (logic->ClearMQDCUpperLobbyRocks && (logic->HasItem(RG_GORONS_BRACELET) && ((logic->IsAdult && (bool)ctx->GetTrickOption(RT_DC_MQ_ADULT_EYES)) || (logic->IsChild && (bool)ctx->GetTrickOption(RT_DC_MQ_CHILD_EYES))))));});}),
});
areaTable[RR_DODONGOS_CAVERN_MQ_GOSSIP_STONE] = Region("Dodongos Cavern MQ Gossip Stone", SCENE_DODONGOS_CAVERN, false, {RA_DODONGOS_CAVERN}, {
	EventAccess(&logic->GossipStoneFairy, []{return logic->CallGossipFairy();}),
}, {
	LOCATION(RC_DODONGOS_CAVERN_GOSSIP_STONE, true),
	LOCATION(RC_DODONGOS_CAVERN_MQ_GOSSIP_STONE_FAIRY, logic->CallGossipFairy()),
	LOCATION(RC_DODONGOS_CAVERN_MQ_GOSSIP_STONE_FAIRY_BIG, logic->CanUse(RG_SONG_OF_STORMS)),
}, {
	Entrance(RR_DODONGOS_CAVERN_MQ_LOBBY, []{return true;}),
});
areaTable[RR_DODONGOS_CAVERN_MQ_MOUTH_SIDE_BRIDGE] = Region("Dodongos Cavern MQ Mouth Side Bridge", SCENE_DODONGOS_CAVERN, false, {RA_DODONGOS_CAVERN}, {
	EventAccess(&logic->ClearMQDCUpperLobbyRocks, []{return (logic->BlastOrSmash() || logic->CanUse(RG_DINS_FIRE));}),
}, {}, {
	Entrance(RR_DODONGOS_CAVERN_MQ_LOBBY, []{return true;}),
	Entrance(RR_DODONGOS_CAVERN_MQ_TORCH_PUZZLE_UPPER, []{return logic->ClearMQDCUpperLobbyRocks;}),
	Entrance(RR_DODONGOS_CAVERN_MQ_POES_ROOM, []{return (logic->CanUse(RG_HOVER_BOOTS) || ((bool)ctx->GetTrickOption(RT_DC_MQ_CHILD_BOMBS) && (logic->CanJumpslashExceptHammer() && logic->TakeDamage())));}),
});
areaTable[RR_DODONGOS_CAVERN_MQ_STAIRS_PAST_MUD_WALL] = Region("Dodongos Cavern MQ Stairs Past Mud Wall", SCENE_DODONGOS_CAVERN, false, {RA_DODONGOS_CAVERN}, {
	EventAccess(&logic->DekuBabaSticks, []{return logic->CanGetDekuBabaSticks();}),
}, {
	LOCATION(RC_DODONGOS_CAVERN_MQ_GS_SONG_OF_TIME_BLOCK_ROOM, (logic->CanUse(RG_SONG_OF_TIME) && logic->CanGetEnemyDrop(RE_GOLD_SKULLTULA))),
}, {
	Entrance(RR_DODONGOS_CAVERN_MQ_STAIRS_UPPER, []{return (logic->HasExplosives() || ((logic->HasItem(RG_GORONS_BRACELET) && (logic->CanUse(RG_STICKS) || (bool)ctx->GetTrickOption(RT_DC_MQ_STAIRS_WITH_ONLY_STRENGTH))) || (logic->CanUse(RG_DINS_FIRE) || ((bool)ctx->GetTrickOption(RT_DC_STAIRS_WITH_BOW) && logic->CanUse(RG_FAIRY_BOW)))));}),
	Entrance(RR_DODONGOS_CAVERN_MQ_STAIRS_LOWER, []{return true;}),
});
areaTable[RR_DODONGOS_CAVERN_MQ_STAIRS_LOWER] = Region("Dodongos Cavern MQ Stairs Lower", SCENE_DODONGOS_CAVERN, false, {RA_DODONGOS_CAVERN}, {}, {
	LOCATION(RC_DODONGOS_CAVERN_MQ_STAIRCASE_POT_1, logic->CanBreakPots()),
	LOCATION(RC_DODONGOS_CAVERN_MQ_STAIRCASE_POT_2, logic->CanBreakPots()),
	LOCATION(RC_DODONGOS_CAVERN_MQ_STAIRCASE_POT_3, logic->CanBreakPots()),
	LOCATION(RC_DODONGOS_CAVERN_MQ_STAIRCASE_POT_4, logic->CanBreakPots()),
	LOCATION(RC_DODONGOS_CAVERN_MQ_STAIRCASE_LOWER_CRATE_1, logic->CanBreakCrates()),
	LOCATION(RC_DODONGOS_CAVERN_MQ_STAIRCASE_LOWER_CRATE_2, logic->CanBreakCrates()),
}, {
	Entrance(RR_DODONGOS_CAVERN_MQ_LOBBY, []{return true;}),
	Entrance(RR_DODONGOS_CAVERN_MQ_STAIRS_UPPER, []{return Here(RR_DODONGOS_CAVERN_MQ_STAIRS_LOWER, []{return (logic->HasExplosives() || (logic->CanUse(RG_DINS_FIRE) || ((bool)ctx->GetTrickOption(RT_DC_STAIRS_WITH_BOW) && logic->CanUse(RG_FAIRY_BOW))));});}),
	Entrance(RR_DODONGOS_CAVERN_MQ_STAIRS_PAST_MUD_WALL, []{return Here(RR_DODONGOS_CAVERN_MQ_STAIRS_LOWER, []{return logic->CanBreakMudWalls();});}),
});
areaTable[RR_DODONGOS_CAVERN_MQ_STAIRS_UPPER] = Region("Dodongos Cavern MQ Stairs Upper", SCENE_DODONGOS_CAVERN, false, {RA_DODONGOS_CAVERN}, {}, {
	LOCATION(RC_DODONGOS_CAVERN_MQ_DEKU_SCRUB_STAIRCASE, logic->CanStunDeku()),
	LOCATION(RC_DODONGOS_CAVERN_MQ_STAIRCASE_UPPER_CRATE_1, logic->CanBreakCrates()),
	LOCATION(RC_DODONGOS_CAVERN_MQ_STAIRCASE_UPPER_CRATE_2, logic->CanBreakCrates()),
	LOCATION(RC_DODONGOS_CAVERN_MQ_STAIRCASE_UPPER_CRATE_3, logic->CanBreakCrates()),
	LOCATION(RC_DODONGOS_CAVERN_MQ_STAIRCASE_UPPER_CRATE_4, logic->CanBreakCrates()),
}, {
	Entrance(RR_DODONGOS_CAVERN_MQ_STAIRS_LOWER, []{return true;}),
	Entrance(RR_DODONGOS_CAVERN_MQ_STAIRS_PAST_BIG_SKULLTULAS, []{return (logic->CanPassEnemy(RE_BIG_SKULLTULA) || logic->CanUse(RG_HOVER_BOOTS));}),
});
areaTable[RR_DODONGOS_CAVERN_MQ_STAIRS_PAST_BIG_SKULLTULAS] = Region("Dodongos Cavern MQ Past Big Skulltulas", SCENE_DODONGOS_CAVERN, false, {RA_DODONGOS_CAVERN}, {}, {}, {
	Entrance(RR_DODONGOS_CAVERN_MQ_STAIRS_UPPER, []{return (logic->CanPassEnemy(RE_BIG_SKULLTULA) || logic->CanUse(RG_HOVER_BOOTS));}),
	Entrance(RR_DODONGOS_CAVERN_MQ_STAIRS_LOWER, []{return logic->TakeDamage();}),
	Entrance(RR_DODONGOS_CAVERN_MQ_DODONGO_ROOM, []{return true;}),
});
areaTable[RR_DODONGOS_CAVERN_MQ_DODONGO_ROOM] = Region("Dodongos Cavern MQ Dodongo Room", SCENE_DODONGOS_CAVERN, false, {RA_DODONGOS_CAVERN}, {}, {
	LOCATION(RC_DODONGOS_CAVERN_MQ_COMPASS_CHEST, (logic->CanKillEnemy(RE_DODONGO) || logic->HasItem(RG_GORONS_BRACELET))),
	LOCATION(RC_DODONGOS_CAVERN_MQ_COMPASS_GRASS_1, logic->CanCutShrubs()),
	LOCATION(RC_DODONGOS_CAVERN_MQ_COMPASS_GRASS_2, logic->CanCutShrubs()),
	LOCATION(RC_DODONGOS_CAVERN_MQ_COMPASS_GRASS_3, logic->CanCutShrubs()),
	LOCATION(RC_DODONGOS_CAVERN_MQ_COMPASS_GRASS_4, logic->CanCutShrubs()),
}, {
	Entrance(RR_DODONGOS_CAVERN_MQ_STAIRS_PAST_BIG_SKULLTULAS, []{return true;}),
	Entrance(RR_DODONGOS_CAVERN_MQ_TORCH_PUZZLE_LOWER, []{return Here(RR_DODONGOS_CAVERN_MQ_DODONGO_ROOM, []{return (logic->CanKillEnemy(RE_DODONGO) || logic->HasItem(RG_GORONS_BRACELET));});}),
});
areaTable[RR_DODONGOS_CAVERN_MQ_TORCH_PUZZLE_LOWER] = Region("Dodongos Cavern MQ Torch Puzzle Lower", SCENE_DODONGOS_CAVERN, false, {RA_DODONGOS_CAVERN}, {
	EventAccess(&logic->ClearMQDCUpperLobbyRocks, []{return (((logic->IsAdult && (bool)ctx->GetTrickOption(RT_DC_JUMP)) || logic->CanUse(RG_HOVER_BOOTS)) && logic->CanUse(RG_STICKS));}),
}, {
	LOCATION(RC_DODONGOS_CAVERN_MQ_TORCH_PUZZLE_MIDDLE_POT, logic->CanUse(RG_BOOMERANG)),
	LOCATION(RC_DODONGOS_CAVERN_MQ_TORCH_PUZZLE_ROOM_HEART, true),
}, {
	Entrance(RR_DODONGOS_CAVERN_MQ_LOBBY, []{return logic->TakeDamage();}),
	Entrance(RR_DODONGOS_CAVERN_MQ_DODONGO_ROOM, []{return true;}),
	Entrance(RR_DODONGOS_CAVERN_MQ_LARVAE_ROOM, []{return logic->HasFireSourceWithTorch();}),
	Entrance(RR_DODONGOS_CAVERN_MQ_BIG_BLOCK_ROOM, []{return Here(RR_DODONGOS_CAVERN_MQ_TORCH_PUZZLE_LOWER, []{return logic->HasFireSourceWithTorch();});}),
	Entrance(RR_DODONGOS_CAVERN_MQ_TORCH_PUZZLE_UPPER, []{return ((logic->IsAdult && (bool)ctx->GetTrickOption(RT_DC_JUMP)) || (logic->CanUse(RG_HOVER_BOOTS) || logic->CanUse(RG_HOOKSHOT)));}),
	Entrance(RR_DODONGOS_CAVERN_MQ_UPPER_LIZALFOS, []{return (logic->CanUse(RG_STICKS) && logic->HasItem(RG_GORONS_BRACELET));}),
});
areaTable[RR_DODONGOS_CAVERN_MQ_BIG_BLOCK_ROOM] = Region("Dodongos Cavern MQ Torch Puzzle Lower", SCENE_DODONGOS_CAVERN, false, {RA_DODONGOS_CAVERN}, {}, {
	LOCATION(RC_DODONGOS_CAVERN_MQ_BIG_BLOCK_POT_1, logic->CanBreakPots()),
	LOCATION(RC_DODONGOS_CAVERN_MQ_BIG_BLOCK_POT_2, logic->CanBreakPots()),
}, {
	Entrance(RR_DODONGOS_CAVERN_MQ_TORCH_PUZZLE_LOWER, []{return logic->CanPassEnemy(RE_BIG_SKULLTULA);}),
	Entrance(RR_DODONGOS_CAVERN_MQ_UPPER_LIZALFOS, []{return ((logic->HasFireSource() && logic->HasItem(RG_GORONS_BRACELET)) || logic->CanBreakMudWalls());}),
});
areaTable[RR_DODONGOS_CAVERN_MQ_LARVAE_ROOM] = Region("Dodongos Cavern MQ Larvae Room", SCENE_DODONGOS_CAVERN, false, {RA_DODONGOS_CAVERN}, {}, {
	LOCATION(RC_DODONGOS_CAVERN_MQ_LARVAE_ROOM_CHEST, true),
	LOCATION(RC_DODONGOS_CAVERN_MQ_GS_LARVAE_ROOM, logic->CanBreakCrates()),
	LOCATION(RC_DODONGOS_CAVERN_MQ_LARVAE_ROOM_CRATE_1, logic->CanBreakCrates()),
	LOCATION(RC_DODONGOS_CAVERN_MQ_LARVAE_ROOM_CRATE_2, logic->CanBreakCrates()),
	LOCATION(RC_DODONGOS_CAVERN_MQ_LARVAE_ROOM_CRATE_3, logic->CanBreakCrates()),
	LOCATION(RC_DODONGOS_CAVERN_MQ_LARVAE_ROOM_CRATE_4, logic->CanBreakCrates()),
	LOCATION(RC_DODONGOS_CAVERN_MQ_LARVAE_ROOM_CRATE_5, logic->CanBreakCrates()),
	LOCATION(RC_DODONGOS_CAVERN_MQ_LARVAE_ROOM_CRATE_6, logic->CanBreakCrates()),
}, {
	Entrance(RR_DODONGOS_CAVERN_MQ_TORCH_PUZZLE_LOWER, []{return true;}),
});
areaTable[RR_DODONGOS_CAVERN_MQ_UPPER_LIZALFOS] = Region("Dodongos Cavern MQ Before Upper Lizalfos", SCENE_DODONGOS_CAVERN, false, {RA_DODONGOS_CAVERN}, {}, {
	LOCATION(RC_DODONGOS_CAVERN_MQ_GS_LIZALFOS_ROOM, logic->BlastOrSmash()),
	LOCATION(RC_DODONGOS_CAVERN_MQ_UPPER_LIZALFOS_POT_1, logic->CanBreakPots()),
	LOCATION(RC_DODONGOS_CAVERN_MQ_UPPER_LIZALFOS_POT_2, logic->CanBreakPots()),
	LOCATION(RC_DODONGOS_CAVERN_MQ_UPPER_LIZALFOS_POT_3, logic->CanBreakPots()),
	LOCATION(RC_DODONGOS_CAVERN_MQ_UPPER_LIZALFOS_POT_4, logic->CanBreakPots()),
	LOCATION(RC_DODONGOS_CAVERN_MQ_LIZALFOS_ROOM_HEART, logic->BlastOrSmash()),
}, {
	Entrance(RR_DODONGOS_CAVERN_MQ_BIG_BLOCK_ROOM, []{return Here(RR_DODONGOS_CAVERN_MQ_UPPER_LIZALFOS, []{return logic->CanKillEnemy(RE_LIZALFOS);});}),
	Entrance(RR_DODONGOS_CAVERN_MQ_TWO_FIRES_ROOM, []{return Here(RR_DODONGOS_CAVERN_MQ_UPPER_LIZALFOS, []{return logic->CanKillEnemy(RE_LIZALFOS);});}),
});
areaTable[RR_DODONGOS_CAVERN_MQ_TWO_FIRES_ROOM] = Region("Dodongos Cavern MQ Before Upper Lizalfos", SCENE_DODONGOS_CAVERN, false, {RA_DODONGOS_CAVERN}, {}, {
	LOCATION(RC_DODONGOS_CAVERN_MQ_TWO_FLAMES_POT_1, logic->CanBreakPots()),
	LOCATION(RC_DODONGOS_CAVERN_MQ_TWO_FLAMES_POT_2, logic->CanBreakPots()),
	LOCATION(RC_DODONGOS_CAVERN_MQ_TWO_FLAMES_CRATE_1, logic->CanBreakCrates()),
	LOCATION(RC_DODONGOS_CAVERN_MQ_TWO_FLAMES_CRATE_2, logic->CanBreakCrates()),
}, {
	Entrance(RR_DODONGOS_CAVERN_MQ_UPPER_LIZALFOS, []{return true;}),
	Entrance(RR_DODONGOS_CAVERN_MQ_TORCH_PUZZLE_UPPER, []{return (logic->IsAdult || Here(RR_DODONGOS_CAVERN_MQ_TWO_FIRES_ROOM, []{return (logic->BlastOrSmash() || (logic->CanAttack() && logic->HasItem(RG_GORONS_BRACELET)));}));}),
});
areaTable[RR_DODONGOS_CAVERN_MQ_TORCH_PUZZLE_UPPER] = Region("Dodongos Cavern MQ Torch Puzzle Upper", SCENE_DODONGOS_CAVERN, false, {RA_DODONGOS_CAVERN}, {
	EventAccess(&logic->ClearMQDCUpperLobbyRocks, []{return (logic->CanDetonateUprightBombFlower() || logic->CanUse(RG_MEGATON_HAMMER));}),
}, {
	LOCATION(RC_DODONGOS_CAVERN_MQ_TORCH_PUZZLE_ROOM_CHEST, true),
	LOCATION(RC_DODONGOS_CAVERN_MQ_TORCH_PUZZLE_CORNER_POT, logic->CanBreakPots()),
	LOCATION(RC_DODONGOS_CAVERN_MQ_TORCH_PUZZLE_MIDDLE_POT, logic->CanBreakPots()),
}, {
	Entrance(RR_DODONGOS_CAVERN_MQ_MOUTH_SIDE_BRIDGE, []{return logic->ClearMQDCUpperLobbyRocks;}),
	Entrance(RR_DODONGOS_CAVERN_MQ_TORCH_PUZZLE_LOWER, []{return true;}),
	Entrance(RR_DODONGOS_CAVERN_MQ_TWO_FIRES_ROOM, []{return true;}),
});
areaTable[RR_DODONGOS_CAVERN_MQ_LOWER_RIGHT_SIDE] = Region("Dodongos Cavern MQ Lower Right Side", SCENE_DODONGOS_CAVERN, false, {RA_DODONGOS_CAVERN}, {}, {
	LOCATION(RC_DODONGOS_CAVERN_MQ_DEKU_SCRUB_SIDE_ROOM_NEAR_LOWER_LIZALFOS, ((logic->CanBreakMudWalls() || logic->HasItem(RG_GORONS_BRACELET)) && logic->CanStunDeku())),
	LOCATION(RC_DODONGOS_CAVERN_MQ_RIGHT_SIDE_POT_1, logic->CanBreakPots()),
	LOCATION(RC_DODONGOS_CAVERN_MQ_RIGHT_SIDE_POT_2, logic->CanBreakPots()),
	LOCATION(RC_DODONGOS_CAVERN_MQ_RIGHT_SIDE_POT_3, logic->CanBreakPots()),
	LOCATION(RC_DODONGOS_CAVERN_MQ_RIGHT_SIDE_POT_4, logic->CanBreakPots()),
}, {
	Entrance(RR_DODONGOS_CAVERN_MQ_LOBBY, []{return true;}),
	Entrance(RR_DODONGOS_CAVERN_MQ_LOWER_LIZALFOS, []{return (Here(RR_DODONGOS_CAVERN_MQ_LOWER_RIGHT_SIDE, []{return (logic->CanDetonateBombFlowers() || logic->HasItem(RG_GORONS_BRACELET));}) && logic->CanHitEyeTargets());}),
});
areaTable[RR_DODONGOS_CAVERN_MQ_LOWER_LIZALFOS] = Region("Dodongos Cavern MQ Lower Lizalfos", SCENE_DODONGOS_CAVERN, false, {RA_DODONGOS_CAVERN}, {}, {
	LOCATION(RC_DODONGOS_CAVERN_MQ_LIZALFOS_ROOM_HEART, true),
}, {
	Entrance(RR_DODONGOS_CAVERN_MQ_LOWER_RIGHT_SIDE, []{return Here(RR_DODONGOS_CAVERN_MQ_LOWER_LIZALFOS, []{return logic->CanKillEnemy(RE_LIZALFOS);});}),
	Entrance(RR_DODONGOS_CAVERN_MQ_POES_ROOM, []{return Here(RR_DODONGOS_CAVERN_MQ_LOWER_LIZALFOS, []{return logic->CanKillEnemy(RE_LIZALFOS);});}),
});
areaTable[RR_DODONGOS_CAVERN_MQ_POES_ROOM] = Region("Dodongos Cavern MQ Poes Room", SCENE_DODONGOS_CAVERN, false, {RA_DODONGOS_CAVERN}, {}, {
	LOCATION(RC_DODONGOS_CAVERN_MQ_BOMB_BAG_CHEST, true),
	LOCATION(RC_DODONGOS_CAVERN_MQ_GS_SCRUB_ROOM, (Here(RR_DODONGOS_CAVERN_MQ_POES_ROOM, []{return (logic->CanDetonateBombFlowers() || logic->HasItem(RG_GORONS_BRACELET));}) && logic->CanGetEnemyDrop(RE_GOLD_SKULLTULA, ED_BOOMERANG, true))),
	LOCATION(RC_DODONGOS_CAVERN_MQ_POE_ROOM_POT_1, logic->CanBreakPots()),
	LOCATION(RC_DODONGOS_CAVERN_MQ_POE_ROOM_POT_2, logic->CanBreakPots()),
	LOCATION(RC_DODONGOS_CAVERN_MQ_POE_ROOM_POT_3, logic->CanBreakPots()),
	LOCATION(RC_DODONGOS_CAVERN_MQ_POE_ROOM_POT_4, logic->CanBreakPots()),
	LOCATION(RC_DODONGOS_CAVERN_MQ_POE_ROOM_CRATE_1, logic->CanBreakCrates()),
	LOCATION(RC_DODONGOS_CAVERN_MQ_POE_ROOM_CRATE_2, logic->CanBreakCrates()),
	LOCATION(RC_DODONGOS_CAVERN_MQ_POE_ROOM_CRATE_3, logic->CanBreakCrates()),
	LOCATION(RC_DODONGOS_CAVERN_MQ_POE_ROOM_CRATE_4, logic->CanBreakCrates()),
	LOCATION(RC_DODONGOS_CAVERN_MQ_POE_ROOM_CRATE_5, logic->CanBreakCrates()),
	LOCATION(RC_DODONGOS_CAVERN_MQ_POE_ROOM_CRATE_6, logic->CanBreakCrates()),
	LOCATION(RC_DODONGOS_CAVERN_MQ_POE_ROOM_CRATE_7, logic->CanBreakCrates()),
	LOCATION(RC_DODONGOS_CAVERN_MQ_POE_ROOM_CRATE_8, logic->CanBreakCrates()),
}, {
	Entrance(RR_DODONGOS_CAVERN_MQ_LOBBY, []{return Here(RR_DODONGOS_CAVERN_MQ_POES_ROOM, []{return (logic->CanDetonateBombFlowers() || logic->HasItem(RG_GORONS_BRACELET));});}),
	Entrance(RR_DODONGOS_CAVERN_MQ_LOWER_LIZALFOS, []{return true;}),
	Entrance(RR_DODONGOS_CAVERN_MQ_MAD_SCRUB_ROOM, []{return Here(RR_DODONGOS_CAVERN_MQ_POES_ROOM, []{return (logic->CanDetonateBombFlowers() || logic->HasItem(RG_GORONS_BRACELET));});}),
});
areaTable[RR_DODONGOS_CAVERN_MQ_MAD_SCRUB_ROOM] = Region("Dodongos Cavern Mad Scrub Room", SCENE_DODONGOS_CAVERN, false, {RA_DODONGOS_CAVERN}, {}, {
	LOCATION(RC_DODONGOS_CAVERN_MQ_GS_SCRUB_ROOM, logic->CanGetEnemyDrop(RE_GOLD_SKULLTULA, ED_BOOMERANG, true)),
	LOCATION(RC_DODONGOS_CAVERN_MQ_SCRUB_GRASS_1, logic->CanCutShrubs()),
	LOCATION(RC_DODONGOS_CAVERN_MQ_SCRUB_GRASS_2, logic->CanCutShrubs()),
}, {
	Entrance(RR_DODONGOS_CAVERN_MQ_POES_ROOM, []{return Here(RR_DODONGOS_CAVERN_MQ_MAD_SCRUB_ROOM, []{return (logic->CanKillEnemy(RE_FIRE_KEESE) && logic->CanKillEnemy(RE_MAD_SCRUB));});}),
});
areaTable[RR_DODONGOS_CAVERN_MQ_BEHIND_MOUTH] = Region("Dodongos Cavern MQ Behind Mouth", SCENE_DODONGOS_CAVERN, false, {RA_DODONGOS_CAVERN}, {}, {
	LOCATION(RC_DODONGOS_CAVERN_MQ_BEFORE_BOSS_SW_POT, logic->CanBreakPots()),
	LOCATION(RC_DODONGOS_CAVERN_MQ_BEFORE_BOSS_NE_POT, logic->CanBreakPots()),
	LOCATION(RC_DODONGOS_CAVERN_MQ_ARMOS_ROOM_SE_POT, logic->CanBreakPots()),
	LOCATION(RC_DODONGOS_CAVERN_MQ_ARMOS_ROOM_SW_POT, logic->CanBreakPots()),
}, {
	Entrance(RR_DODONGOS_CAVERN_MQ_LOBBY, []{return true;}),
	Entrance(RR_DODONGOS_CAVERN_MQ_BACK_BEHIND_FIRE, []{return true;}),
	Entrance(RR_DODONGOS_CAVERN_MQ_BACK_SWITCH_GRAVE, []{return logic->IsAdult;}),
});
areaTable[RR_DODONGOS_CAVERN_MQ_BACK_BEHIND_FIRE] = Region("Dodongos Cavern MQ Back Behind Fire", SCENE_DODONGOS_CAVERN, false, {RA_DODONGOS_CAVERN}, {}, {
	LOCATION(RC_DODONGOS_CAVERN_MQ_UNDER_GRAVE_CHEST, true),
	LOCATION(RC_DODONGOS_CAVERN_MQ_BACKROOM_POT_1, logic->CanBreakPots()),
	LOCATION(RC_DODONGOS_CAVERN_MQ_BACKROOM_POT_2, logic->CanBreakPots()),
	LOCATION(RC_DODONGOS_CAVERN_MQ_BACK_POE_GRASS, logic->CanCutShrubs()),
}, {
	Entrance(RR_DODONGOS_CAVERN_MQ_BEHIND_MOUTH, []{return logic->CanAttack();}),
	Entrance(RR_DODONGOS_CAVERN_MQ_BACK_SWITCH_GRAVE, []{return (Here(RR_DODONGOS_CAVERN_MQ_BACK_BEHIND_FIRE, []{return logic->CanDetonateBombFlowers();}) || Here(RR_DODONGOS_CAVERN_MQ_BACK_BEHIND_FIRE, []{return logic->CanAttack();}));}),
});
areaTable[RR_DODONGOS_CAVERN_MQ_BACK_SWITCH_GRAVE] = Region("Dodongos Cavern MQ BossArea", SCENE_DODONGOS_CAVERN, false, {RA_DODONGOS_CAVERN}, {
	EventAccess(&logic->FairyPot, []{return true;}),
}, {
	LOCATION(RC_DODONGOS_CAVERN_MQ_GS_BACK_AREA, (logic->CanGetEnemyDrop(RE_GOLD_SKULLTULA) || (logic->HasItem(RG_GORONS_BRACELET) || Here(RR_DODONGOS_CAVERN_MQ_BACK_SWITCH_GRAVE, []{return (logic->CanGetEnemyDrop(RE_GOLD_SKULLTULA, ED_BOOMERANG) || (logic->IsAdult && logic->CanUse(RG_HOVER_BOOTS)));})))),
	LOCATION(RC_DODONGOS_CAVERN_MQ_ARMOS_ROOM_NW_POT, logic->CanBreakPots()),
	LOCATION(RC_DODONGOS_CAVERN_MQ_ARMOS_ROOM_NE_POT, logic->CanBreakPots()),
	LOCATION(RC_DODONGOS_CAVERN_MQ_ARMOS_GRASS, logic->CanCutShrubs()),
}, {
	Entrance(RR_DODONGOS_CAVERN_MQ_BACK_BEHIND_FIRE, []{return true;}),
	Entrance(RR_DODONGOS_CAVERN_BOSS_ENTRYWAY, []{return true;}),
});
areaTable[RR_DODONGOS_CAVERN_BOSS_ENTRYWAY] = Region("Dodongos Cavern Boss Entryway", SCENE_DODONGOS_CAVERN, false, {RA_DODONGOS_CAVERN}, {}, {}, {
	Entrance(RR_DODONGOS_CAVERN_BOSS_ROOM, []{return true;}),
});
areaTable[RR_DODONGOS_CAVERN_BOSS_EXIT] = Region("Dodongos Cavern Boss Exit", SCENE_DODONGOS_CAVERN, false, {RA_DODONGOS_CAVERN}, {}, {}, {
	Entrance(RR_DODONGOS_CAVERN_BOSS_AREA, []{return ctx->GetDungeon(Rando::DODONGOS_CAVERN)->IsVanilla();}),
	Entrance(RR_DODONGOS_CAVERN_MQ_BEHIND_MOUTH, []{return ctx->GetDungeon(Rando::DODONGOS_CAVERN)->IsMQ();}),
});
areaTable[RR_DODONGOS_CAVERN_BOSS_ROOM] = Region("Dodongos Cavern Boss Room", SCENE_DODONGOS_CAVERN_BOSS, false, {}, {
	EventAccess(&logic->DodongosCavernClear, []{return (Here(RR_DODONGOS_CAVERN_BOSS_ROOM, []{return (logic->HasExplosives() || ((bool)ctx->GetTrickOption(RT_DC_HAMMER_FLOOR) ? (logic->CanUse(RG_MEGATON_HAMMER) || ((bool)ctx->GetTrickOption(RT_BLUE_FIRE_MUD_WALLS) && logic->BlueFire())) : ((bool)ctx->GetTrickOption(RT_BLUE_FIRE_MUD_WALLS) && logic->CanUse(RG_BOTTLE_WITH_BLUE_FIRE))));}) && logic->CanKillEnemy(RE_KING_DODONGO));}),
}, {
	LOCATION(RC_DODONGOS_CAVERN_BOSS_ROOM_CHEST, true),
	LOCATION(RC_DODONGOS_CAVERN_KING_DODONGO_HEART, logic->DodongosCavernClear),
	LOCATION(RC_KING_DODONGO, logic->DodongosCavernClear),
}, {
	Entrance(RR_DODONGOS_CAVERN_BOSS_EXIT, []{return true;}),
	Entrance(RR_DEATH_MOUNTAIN_TRAIL, []{return logic->DodongosCavernClear;}, "", false),
});
areaTable[RR_JABU_JABUS_BELLY_BEGINNING] = Region("Jabu Jabus Belly Beginning", SCENE_JABU_JABU, false, {RA_JABU_JABUS_BELLY}, {}, {}, {
	Entrance(RR_JABU_JABUS_BELLY_ENTRYWAY, []{return true;}),
	Entrance(RR_JABU_JABUS_BELLY_MAIN, []{return logic->CanUseProjectile();}),
});
areaTable[RR_JABU_JABUS_BELLY_MAIN] = Region("Jabu Jabus Belly Main", SCENE_JABU_JABU, false, {RA_JABU_JABUS_BELLY}, {
	EventAccess(&logic->JabuWestTentacle, []{return (logic->JabuRutoIn1F && logic->CanKillEnemy(RE_TENTACLE, ED_BOOMERANG));}),
}, {
	LOCATION(RC_JABU_JABUS_BELLY_DEKU_SCRUB, (logic->HasItem(RG_BRONZE_SCALE) && ((logic->IsChild || (logic->HasItem(RG_SILVER_SCALE) || ((bool)ctx->GetTrickOption(RT_JABU_ALCOVE_JUMP_DIVE) || logic->CanUse(RG_IRON_BOOTS)))) && logic->CanStunDeku()))),
	LOCATION(RC_JABU_JABUS_BELLY_BOOMERANG_CHEST, logic->JabuRutoIn1F),
	LOCATION(RC_JABU_JABUS_BELLY_MAP_CHEST, logic->JabuWestTentacle),
	LOCATION(RC_JABU_JABUS_BELLY_PLATFORM_ROOM_SMALL_CRATE_1, logic->CanBreakSmallCrates()),
	LOCATION(RC_JABU_JABUS_BELLY_PLATFORM_ROOM_SMALL_CRATE_2, logic->CanBreakSmallCrates()),
}, {
	Entrance(RR_JABU_JABUS_BELLY_BEGINNING, []{return true;}),
	Entrance(RR_JABU_JABUS_BELLY_B1_NORTH, []{return true;}),
	Entrance(RR_JABU_JABUS_BELLY_COMPASS_ROOM, []{return logic->JabuWestTentacle;}),
	Entrance(RR_JABU_JABUS_BELLY_BLUE_TENTACLE, []{return logic->JabuWestTentacle;}),
	Entrance(RR_JABU_JABUS_BELLY_GREEN_TENTACLE, []{return logic->JabuEastTentacle;}),
	Entrance(RR_JABU_JABUS_BELLY_BIGOCTO_LEDGE, []{return logic->JabuNorthTentacle;}),
	Entrance(RR_JABU_JABUS_BELLY_NEAR_BOSS_ROOM, []{return (logic->LoweredJabuPath || ((bool)ctx->GetTrickOption(RT_JABU_BOSS_HOVER) && logic->CanUse(RG_HOVER_BOOTS)));}),
});
areaTable[RR_JABU_JABUS_BELLY_B1_NORTH] = Region("Jabu Jabus Belly B1 North", SCENE_JABU_JABU, false, {RA_JABU_JABUS_BELLY}, {
	EventAccess(&logic->JabuRutoIn1F, []{return (logic->IsAdult || logic->HasItem(RG_BRONZE_SCALE));}),
	EventAccess(&logic->FairyPot, []{return (logic->CanUse(RG_BOOMERANG) || (logic->CanUse(RG_HOVER_BOOTS) && logic->CanKillEnemy(RE_OCTOROK)));}),
}, {
	LOCATION(RC_JABU_JABUS_BELLY_GS_LOBBY_BASEMENT_LOWER, logic->HookshotOrBoomerang()),
	LOCATION(RC_JABU_JABUS_BELLY_GS_LOBBY_BASEMENT_UPPER, logic->HookshotOrBoomerang()),
	LOCATION(RC_JABU_JABUS_BELLY_GS_WATER_SWITCH_ROOM, logic->HookshotOrBoomerang()),
	LOCATION(RC_JABU_JABUS_BELLY_TWO_OCTOROK_POT_1, (logic->CanBreakPots() && (logic->CanUse(RG_BOOMERANG) || (logic->CanUse(RG_HOVER_BOOTS) && logic->CanKillEnemy(RE_OCTOROK, ED_BOOMERANG, false))))),
	LOCATION(RC_JABU_JABUS_BELLY_TWO_OCTOROK_POT_2, (logic->CanBreakPots() && (logic->CanUse(RG_BOOMERANG) || (logic->CanUse(RG_HOVER_BOOTS) && logic->CanKillEnemy(RE_OCTOROK, ED_BOOMERANG, false))))),
	LOCATION(RC_JABU_JABUS_BELLY_TWO_OCTOROK_POT_3, (logic->CanBreakPots() && (logic->CanUse(RG_BOOMERANG) || (logic->CanUse(RG_HOVER_BOOTS) && logic->CanKillEnemy(RE_OCTOROK, ED_BOOMERANG, false))))),
	LOCATION(RC_JABU_JABUS_BELLY_TWO_OCTOROK_POT_4, (logic->CanBreakPots() && (logic->CanUse(RG_BOOMERANG) || (logic->CanUse(RG_HOVER_BOOTS) && logic->CanKillEnemy(RE_OCTOROK, ED_BOOMERANG, false))))),
	LOCATION(RC_JABU_JABUS_BELLY_TWO_OCTOROK_POT_5, (logic->CanBreakPots() && (logic->CanUse(RG_BOOMERANG) || (logic->CanUse(RG_HOVER_BOOTS) && logic->CanKillEnemy(RE_OCTOROK, ED_BOOMERANG, false))))),
}, {
	Entrance(RR_JABU_JABUS_BELLY_MAIN, []{return true;}),
	Entrance(RR_JABU_JABUS_BELLY_WATER_SWITCH_ROOM_LEDGE, []{return (logic->HasItem(RG_BRONZE_SCALE) || logic->CanUse(RG_HOVER_BOOTS));}),
	Entrance(RR_JABU_JABUS_BELLY_WATER_SWITCH_ROOM_SOUTH, []{return (logic->IsAdult || logic->HasItem(RG_BRONZE_SCALE));}),
});
areaTable[RR_JABU_JABUS_BELLY_WATER_SWITCH_ROOM_SOUTH] = Region("Jabu Jabus Belly Water Switch Room South", SCENE_JABU_JABU, false, {RA_JABU_JABUS_BELLY}, {}, {
	LOCATION(RC_JABU_JABUS_BELLY_GS_WATER_SWITCH_ROOM, logic->HookshotOrBoomerang()),
}, {
	Entrance(RR_JABU_JABUS_BELLY_B1_NORTH, []{return (logic->IsAdult || logic->HasItem(RG_BRONZE_SCALE));}),
	Entrance(RR_JABU_JABUS_BELLY_WATER_SWITCH_ROOM_LEDGE, []{return (logic->HasItem(RG_BRONZE_SCALE) || logic->CanUse(RG_HOVER_BOOTS));}),
	Entrance(RR_JABU_JABUS_BELLY_MAIN, []{return logic->CanUseProjectile();}),
});
areaTable[RR_JABU_JABUS_BELLY_WATER_SWITCH_ROOM_LEDGE] = Region("Jabu Jabus Belly Water Switch Room Ledge", SCENE_JABU_JABU, false, {RA_JABU_JABUS_BELLY}, {
	EventAccess(&logic->FairyPot, []{return true;}),
}, {
	LOCATION(RC_JABU_JABUS_BELLY_GS_WATER_SWITCH_ROOM, (logic->HasItem(RG_BRONZE_SCALE) || ((logic->IsAdult && logic->CanUse(RG_HOVER_BOOTS)) || logic->CanKillEnemy(RE_GOLD_SKULLTULA, ED_BOMB_THROW)))),
	LOCATION(RC_JABU_JABUS_BELLY_BASEMENT_POT_1, logic->CanBreakPots()),
	LOCATION(RC_JABU_JABUS_BELLY_BASEMENT_POT_2, logic->CanBreakPots()),
	LOCATION(RC_JABU_JABUS_BELLY_BASEMENT_POT_3, logic->CanBreakPots()),
}, {
	Entrance(RR_JABU_JABUS_BELLY_B1_NORTH, []{return true;}),
	Entrance(RR_JABU_JABUS_BELLY_WATER_SWITCH_ROOM_SOUTH, []{return true;}),
});
areaTable[RR_JABU_JABUS_BELLY_COMPASS_ROOM] = Region("Jabu Jabus Belly Compass Room", SCENE_JABU_JABU, false, {RA_JABU_JABUS_BELLY}, {}, {
	LOCATION(RC_JABU_JABUS_BELLY_COMPASS_CHEST, logic->CanKillEnemy(RE_SHABOM)),
}, {
	Entrance(RR_JABU_JABUS_BELLY_MAIN, []{return Here(RR_JABU_JABUS_BELLY_COMPASS_ROOM, []{return logic->CanKillEnemy(RE_SHABOM);});}),
});
areaTable[RR_JABU_JABUS_BELLY_BLUE_TENTACLE] = Region("Jabu Jabus Belly Blue Tentacle", SCENE_JABU_JABU, false, {RA_JABU_JABUS_BELLY}, {
	EventAccess(&logic->JabuEastTentacle, []{return logic->CanKillEnemy(RE_TENTACLE, ED_BOOMERANG);}),
}, {}, {
	Entrance(RR_JABU_JABUS_BELLY_MAIN, []{return logic->JabuEastTentacle;}),
});
areaTable[RR_JABU_JABUS_BELLY_GREEN_TENTACLE] = Region("Jabu Jabus Belly Green Tentacle", SCENE_JABU_JABU, false, {RA_JABU_JABUS_BELLY}, {
	EventAccess(&logic->JabuNorthTentacle, []{return logic->CanKillEnemy(RE_TENTACLE, ED_BOOMERANG);}),
}, {}, {
	Entrance(RR_JABU_JABUS_BELLY_MAIN, []{return logic->JabuNorthTentacle;}),
});
areaTable[RR_JABU_JABUS_BELLY_BIGOCTO_LEDGE] = Region("Jabu Jabus Belly Bigocto Room", SCENE_JABU_JABU, false, {RA_JABU_JABUS_BELLY}, {}, {
	LOCATION(RC_JABU_JABUS_BELLY_GS_LOBBY_BASEMENT_UPPER, (logic->IsAdult && logic->CanGetEnemyDrop(RE_GOLD_SKULLTULA, ED_SHORT_JUMPSLASH))),
}, {
	Entrance(RR_JABU_JABUS_BELLY_B1_NORTH, []{return true;}),
	Entrance(RR_JABU_JABUS_BELLY_ABOVE_BIGOCTO, []{return (logic->JabuRutoIn1F && Here(RR_JABU_JABUS_BELLY_BIGOCTO_LEDGE, []{return logic->CanKillEnemy(RE_BIG_OCTO);}));}),
});
areaTable[RR_JABU_JABUS_BELLY_ABOVE_BIGOCTO] = Region("Jabu Jabus Belly Above Bigocto", SCENE_JABU_JABU, false, {RA_JABU_JABUS_BELLY}, {
	EventAccess(&logic->FairyPot, []{return true;}),
	EventAccess(&logic->NutPot, []{return true;}),
}, {
	LOCATION(RC_JABU_JABUS_BELLY_ABOVE_BIG_OCTO_POT_1, logic->CanBreakPots()),
	LOCATION(RC_JABU_JABUS_BELLY_ABOVE_BIG_OCTO_POT_2, logic->CanBreakPots()),
	LOCATION(RC_JABU_JABUS_BELLY_ABOVE_BIG_OCTO_POT_3, logic->CanBreakPots()),
}, {
	Entrance(RR_JABU_JABUS_BELLY_LIFT_UPPER, []{return logic->CanUse(RG_BOOMERANG);}),
});
areaTable[RR_JABU_JABUS_BELLY_LIFT_UPPER] = Region("Jabu Jabus Belly Lift Upper", SCENE_JABU_JABU, false, {RA_JABU_JABUS_BELLY}, {
	EventAccess(&logic->LoweredJabuPath, []{return true;}),
}, {}, {
	Entrance(RR_JABU_JABUS_BELLY_MAIN, []{return true;}),
});
areaTable[RR_JABU_JABUS_BELLY_NEAR_BOSS_ROOM] = Region("Jabu Jabus Belly Near Boss Room", SCENE_JABU_JABU, false, {RA_JABU_JABUS_BELLY}, {}, {
	LOCATION(RC_JABU_JABUS_BELLY_GS_NEAR_BOSS, logic->CanKillEnemy(RE_GOLD_SKULLTULA, ED_BOMB_THROW)),
}, {
	Entrance(RR_JABU_JABUS_BELLY_MAIN, []{return true;}),
	Entrance(RR_JABU_JABUS_BELLY_BOSS_ENTRYWAY, []{return (logic->CanUse(RG_BOOMERANG) || (((bool)ctx->GetTrickOption(RT_JABU_NEAR_BOSS_RANGED) && (logic->CanUse(RG_HOOKSHOT) || (logic->CanUse(RG_FAIRY_BOW) || logic->CanUse(RG_FAIRY_SLINGSHOT)))) || ((bool)ctx->GetTrickOption(RT_JABU_NEAR_BOSS_EXPLOSIVES) && (logic->CanUse(RG_BOMBCHU_5) || (logic->CanUse(RG_HOVER_BOOTS) && logic->CanUse(RG_BOMB_BAG))))));}),
});
areaTable[RR_JABU_JABUS_BELLY_MQ_BEGINNING] = Region("Jabu Jabus Belly MQ Beginning", SCENE_JABU_JABU, false, {RA_JABU_JABUS_BELLY}, {
	EventAccess(&logic->NutPot, []{return true;}),
}, {
	LOCATION(RC_JABU_JABUS_BELLY_MQ_MAP_CHEST, logic->BlastOrSmash()),
	LOCATION(RC_JABU_JABUS_BELLY_MQ_FIRST_ROOM_SIDE_CHEST, logic->CanUse(RG_FAIRY_SLINGSHOT)),
	LOCATION(RC_JABU_JABUS_BELLY_MQ_ENTRANCE_POT_1, logic->CanBreakPots()),
	LOCATION(RC_JABU_JABUS_BELLY_MQ_ENTRANCE_POT_2, logic->CanBreakPots()),
	LOCATION(RC_JABU_JABUS_BELLY_MQ_FIRST_GRASS_1, logic->CanCutShrubs()),
	LOCATION(RC_JABU_JABUS_BELLY_MQ_FIRST_GRASS_2, logic->CanCutShrubs()),
}, {
	Entrance(RR_JABU_JABUS_BELLY_ENTRYWAY, []{return true;}),
	Entrance(RR_JABU_JABUS_BELLY_MQ_LIFT_ROOM, []{return Here(RR_JABU_JABUS_BELLY_MQ_BEGINNING, []{return logic->CanUse(RG_FAIRY_SLINGSHOT);});}),
});
areaTable[RR_JABU_JABUS_BELLY_MQ_LIFT_ROOM] = Region("Jabu Jabus Belly MQ Lift Room", SCENE_JABU_JABU, false, {RA_JABU_JABUS_BELLY}, {
	EventAccess(&logic->MQJabuLiftRoomCow, []{return logic->CanUse(RG_FAIRY_SLINGSHOT);}),
}, {
	LOCATION(RC_JABU_JABUS_BELLY_MQ_SECOND_ROOM_LOWER_CHEST, true),
	LOCATION(RC_JABU_JABUS_BELLY_MQ_LIFT_HEART_1, true),
	LOCATION(RC_JABU_JABUS_BELLY_MQ_LIFT_HEART_2, true),
	LOCATION(RC_JABU_JABUS_BELLY_MQ_LIFT_RUPEE_1, logic->CanUse(RG_IRON_BOOTS)),
	LOCATION(RC_JABU_JABUS_BELLY_MQ_LIFT_RUPEE_2, logic->CanUse(RG_IRON_BOOTS)),
	LOCATION(RC_JABU_JABUS_BELLY_MQ_LIFT_RUPEE_3, logic->CanUse(RG_IRON_BOOTS)),
}, {
	Entrance(RR_JABU_JABUS_BELLY_MQ_BEGINNING, []{return true;}),
	Entrance(RR_JABU_JABUS_BELLY_MQ_UNDERWATER_ALCOVE, []{return (logic->HasItem(RG_SILVER_SCALE) || (logic->HasItem(RG_BRONZE_SCALE) && (logic->IsChild || (logic->CanUse(RG_IRON_BOOTS) || (bool)ctx->GetTrickOption(RT_JABU_ALCOVE_JUMP_DIVE)))));}),
	Entrance(RR_JABU_JABUS_BELLY_MQ_HOLES_ROOM, []{return logic->MQJabuHolesRoomDoor;}),
	Entrance(RR_JABU_JABUS_BELLY_MQ_LIFT_ROOM_EAST_LEDGE, []{return (logic->LoweredJabuPath || (logic->CanUse(RG_HOVER_BOOTS) || (logic->CanUse(RG_HOOKSHOT) && logic->MQJabuLiftRoomCow)));}),
});
areaTable[RR_JABU_JABUS_BELLY_MQ_LIFT_ROOM_EAST_LEDGE] = Region("Jabu Jabus Belly MQ Lift Room East Ledge", SCENE_JABU_JABU, false, {RA_JABU_JABUS_BELLY}, {}, {
	LOCATION(RC_JABU_JABUS_BELLY_MQ_SECOND_ROOM_UPPER_CHEST, logic->MQJabuLiftRoomCow),
}, {
	Entrance(RR_JABU_JABUS_BELLY_MQ_LIFT_ROOM, []{return true;}),
	Entrance(RR_JABU_JABUS_BELLY_MQ_EAST_ROOM, []{return logic->JabuNorthTentacle;}),
});
areaTable[RR_JABU_JABUS_BELLY_MQ_UNDERWATER_ALCOVE] = Region("Jabu Jabus Belly MQ Underwater Alcove", SCENE_JABU_JABU, false, {RA_JABU_JABUS_BELLY}, {
	EventAccess(&logic->MQJabuHolesRoomDoor, []{return true;}),
}, {
	LOCATION(RC_JABU_JABUS_BELLY_MQ_COMPASS_CHEST, (logic->CanHitSwitch(ED_HOOKSHOT, true) || ((bool)ctx->GetTrickOption(RT_JABU_MQ_RANG_JUMP) && (logic->CanUse(RG_BOOMERANG) && logic->HasItem(RG_BRONZE_SCALE))))),
	LOCATION(RC_JABU_JABUS_BELLY_MQ_GEYSER_POT_1, logic->CanBreakPots()),
	LOCATION(RC_JABU_JABUS_BELLY_MQ_GEYSER_POT_2, logic->CanBreakPots()),
	LOCATION(RC_JABU_JABUS_BELLY_MQ_LIFT_RUPEE_1, (logic->HasItem(RG_GOLDEN_SCALE) || logic->CanUse(RG_BOOMERANG))),
	LOCATION(RC_JABU_JABUS_BELLY_MQ_LIFT_RUPEE_2, (logic->HasItem(RG_SILVER_SCALE) || logic->CanUse(RG_BOOMERANG))),
	LOCATION(RC_JABU_JABUS_BELLY_MQ_LIFT_RUPEE_3, (logic->HasItem(RG_BRONZE_SCALE) || logic->CanUse(RG_BOOMERANG))),
}, {
	Entrance(RR_JABU_JABUS_BELLY_MQ_LIFT_ROOM, []{return logic->HasItem(RG_BRONZE_SCALE);}),
});
areaTable[RR_JABU_JABUS_BELLY_MQ_HOLES_ROOM] = Region("Jabu Jabus Belly MQ Holes Room", SCENE_JABU_JABU, false, {RA_JABU_JABUS_BELLY}, {}, {
	LOCATION(RC_JABU_JABUS_BELLY_MQ_BASEMENT_NEAR_VINES_CHEST, logic->CanUse(RG_FAIRY_SLINGSHOT)),
	LOCATION(RC_JABU_JABUS_BELLY_MQ_BASEMENT_NEAR_SWITCHES_CHEST, logic->CanUse(RG_FAIRY_SLINGSHOT)),
	LOCATION(RC_JABU_JABUS_BELLY_MQ_PIT_GRASS_1, (logic->CanCutShrubs() && logic->HasExplosives())),
	LOCATION(RC_JABU_JABUS_BELLY_MQ_PIT_GRASS_2, (logic->CanCutShrubs() && logic->HasExplosives())),
	LOCATION(RC_JABU_JABUS_BELLY_MQ_BASEMENT_GRASS_1, logic->CanCutShrubs()),
	LOCATION(RC_JABU_JABUS_BELLY_MQ_BASEMENT_GRASS_2, logic->CanCutShrubs()),
	LOCATION(RC_JABU_JABUS_BELLY_MQ_BASEMENT_GRASS_3, logic->CanCutShrubs()),
}, {
	Entrance(RR_JABU_JABUS_BELLY_MQ_LIFT_ROOM, []{return true;}),
	Entrance(RR_JABU_JABUS_BELLY_MQ_WATER_SWITCH_ROOM, []{return true;}),
	Entrance(RR_JABU_JABUS_BELLY_MQ_FORKED_CORRIDOR, []{return (logic->CanUse(RG_BOOMERANG) && (logic->HasExplosives() && Here(RR_JABU_JABUS_BELLY_MQ_HOLES_ROOM, []{return logic->CanUse(RG_FAIRY_SLINGSHOT);})));}),
	Entrance(RR_JABU_JABUS_BELLY_MQ_INVISIBLE_KEESE_ROOM, []{return logic->JabuNorthTentacle;}),
	Entrance(RR_JABU_JABUS_BELLY_MQ_PAST_OCTO, []{return (logic->JabuWestTentacle && (Here(RR_JABU_JABUS_BELLY_MQ_HOLES_ROOM, []{return logic->CanKillEnemy(RE_BIG_OCTO);}) && logic->CanUse(RG_FAIRY_SLINGSHOT)));}),
});
areaTable[RR_JABU_JABUS_BELLY_MQ_WATER_SWITCH_ROOM] = Region("Jabu Jabus Belly MQ Water Switch Room", SCENE_JABU_JABU, false, {RA_JABU_JABUS_BELLY}, {}, {
	LOCATION(RC_JABU_JABUS_BELLY_MQ_BOOMERANG_ROOM_SMALL_CHEST, true),
	LOCATION(RC_JABU_JABUS_BELLY_MQ_BOOMERANG_CHEST, logic->CanKillEnemy(RE_LIZALFOS)),
	LOCATION(RC_JABU_JABUS_BELLY_MQ_GS_BOOMERANG_CHEST_ROOM, ((logic->CanUse(RG_SONG_OF_TIME) && logic->CanGetEnemyDrop(RE_GOLD_SKULLTULA)) || ((bool)ctx->GetTrickOption(RT_JABU_MQ_SOT_GS) && logic->CanUse(RG_BOOMERANG)))),
	LOCATION(RC_JABU_JABUS_BELLY_MQ_TIME_BLOCK_POT_1, logic->CanBreakPots()),
	LOCATION(RC_JABU_JABUS_BELLY_MQ_TIME_BLOCK_POT_2, logic->CanBreakPots()),
	LOCATION(RC_JABU_JABUS_BELLY_MQ_BASEMENT_BOOMERANG_GRASS, logic->CanCutShrubs()),
}, {
	Entrance(RR_JABU_JABUS_BELLY_MQ_BEGINNING, []{return Here(RR_JABU_JABUS_BELLY_MQ_WATER_SWITCH_ROOM, []{return logic->CanKillEnemy(RE_LIZALFOS);});}),
	Entrance(RR_JABU_JABUS_BELLY_MQ_HOLES_ROOM, []{return ((logic->IsAdult || logic->HasItem(RG_BRONZE_SCALE)) && Here(RR_JABU_JABUS_BELLY_MQ_WATER_SWITCH_ROOM, []{return logic->CanKillEnemy(RE_LIZALFOS);}));}),
});
areaTable[RR_JABU_JABUS_BELLY_MQ_FORKED_CORRIDOR] = Region("Jabu Jabus Belly MQ Forked Corridor", SCENE_JABU_JABU, false, {RA_JABU_JABUS_BELLY}, {
	EventAccess(&logic->JabuNorthTentacle, []{return (Here(RR_JABU_JABUS_BELLY_MQ_FORKED_CORRIDOR, []{return logic->BlastOrSmash();}) && logic->CanUse(RG_BOOMERANG));}),
}, {
	LOCATION(RC_JABU_JABUS_BELLY_MQ_FALLING_LIKE_LIKE_ROOM_CHEST, logic->CanUse(RG_FAIRY_SLINGSHOT)),
	LOCATION(RC_JABU_JABUS_BELLY_MQ_LIKE_LIKES_POT_1, logic->CanBreakPots()),
	LOCATION(RC_JABU_JABUS_BELLY_MQ_LIKE_LIKES_POT_2, logic->CanBreakPots()),
	LOCATION(RC_JABU_JABUS_BELLY_MQ_FALLING_LIKE_LIKE_GRASS, logic->CanCutShrubs()),
	LOCATION(RC_JABU_JABUS_BELLY_MQ_TRIPLE_HALLWAY_SMALL_CRATE_1, logic->CanBreakSmallCrates()),
	LOCATION(RC_JABU_JABUS_BELLY_MQ_TRIPLE_HALLWAY_SMALL_CRATE_2, logic->CanBreakSmallCrates()),
}, {
	Entrance(RR_JABU_JABUS_BELLY_MQ_HOLES_ROOM, []{return logic->CanUse(RG_BOOMERANG);}),
	Entrance(RR_JABU_JABUS_BELLY_MQ_WEST_FORKED_ROOMS, []{return (Here(RR_JABU_JABUS_BELLY_MQ_FORKED_CORRIDOR, []{return logic->CanUse(RG_BOOMERANG);}) && (Here(RR_JABU_JABUS_BELLY_MQ_FORKED_CORRIDOR, []{return (logic->CanUse(RG_FAIRY_SLINGSHOT) && logic->CanUse(RG_STICKS));}) || Here(RR_JABU_JABUS_BELLY_MQ_FORKED_CORRIDOR, []{return logic->HasFireSource();})));}),
});
areaTable[RR_JABU_JABUS_BELLY_MQ_WEST_FORKED_ROOMS] = Region("Jabu Jabus Belly MQ West Forked Rooms", SCENE_JABU_JABU, false, {RA_JABU_JABUS_BELLY}, {
	EventAccess(&logic->JabuWestTentacle, []{return logic->CanKillEnemy(RE_TENTACLE, ED_BOOMERANG);}),
}, {
	LOCATION(RC_JABU_JABUS_BELLY_MQ_GS_TAILPASARAN_ROOM, (Here(RR_JABU_JABUS_BELLY_MQ_WEST_FORKED_ROOMS, []{return logic->HasExplosives();}) && logic->CanGetEnemyDrop(RE_GOLD_SKULLTULA, ED_BOOMERANG))),
}, {
	Entrance(RR_JABU_JABUS_BELLY_MQ_FORKED_CORRIDOR, []{return true;}),
});
areaTable[RR_JABU_JABUS_BELLY_MQ_INVISIBLE_KEESE_ROOM] = Region("Jabu Jabus Belly MQ Invisible Keese Room", SCENE_JABU_JABU, false, {RA_JABU_JABUS_BELLY}, {}, {
	LOCATION(RC_JABU_JABUS_BELLY_MQ_GS_INVISIBLE_ENEMIES_ROOM, ((logic->CanUse(RG_FIRE_ARROWS) && logic->CanGetEnemyDrop(RE_GOLD_SKULLTULA, ED_LONGSHOT)) || (logic->CanGetEnemyDrop(RE_GOLD_SKULLTULA, ED_BOOMERANG) && ((logic->CanUse(RG_HOVER_BOOTS) || Here(RR_JABU_JABUS_BELLY_MQ_INVISIBLE_KEESE_ROOM, []{return (((bool)ctx->GetTrickOption(RT_LENS_JABU_MQ) || logic->CanUse(RG_LENS_OF_TRUTH)) && (logic->CanKillEnemy(RE_STINGER, ED_BOOMERANG, false, 2, false, true) && (logic->CanKillEnemy(RE_KEESE, ED_LONGSHOT, false) || ((bool)ctx->GetTrickOption(RT_LENS_JABU_MQ) && (logic->CanUse(RG_HOOKSHOT) && logic->CanUse(RG_IRON_BOOTS))))));})) && ((logic->IsChild && logic->HasItem(RG_BRONZE_SCALE)) || (logic->IsAdult && logic->CanUse(RG_IRON_BOOTS))))))),
}, {
	Entrance(RR_JABU_JABUS_BELLY_MQ_HOLES_ROOM, []{return ((logic->JabuNorthTentacle || logic->TakeDamage()) && logic->HasItem(RG_BRONZE_SCALE));}),
});
areaTable[RR_JABU_JABUS_BELLY_MQ_PAST_OCTO] = Region("Jabu Jabus Belly MQ Past Octo", SCENE_JABU_JABU, false, {RA_JABU_JABUS_BELLY}, {
	EventAccess(&logic->LoweredJabuPath, []{return (logic->CanUse(RG_BOOMERANG) && logic->CanUse(RG_FAIRY_SLINGSHOT));}),
}, {
	LOCATION(RC_JABU_JABUS_BELLY_MQ_COW, (logic->CanUse(RG_EPONAS_SONG) && logic->CanUse(RG_FAIRY_SLINGSHOT))),
	LOCATION(RC_JABU_JABUS_BELLY_MQ_JIGGLIES_GRASS, logic->CanCutShrubs()),
	LOCATION(RC_JABU_JABUS_BELLY_MQ_AFTER_BIG_OCTO_GRASS_1, logic->CanCutShrubs()),
	LOCATION(RC_JABU_JABUS_BELLY_MQ_AFTER_BIG_OCTO_GRASS_2, logic->CanCutShrubs()),
	LOCATION(RC_JABU_JABUS_BELLY_MQ_JIGGLIES_SMALL_CRATE_1, (logic->CanUse(RG_FAIRY_SLINGSHOT) && logic->CanBreakSmallCrates())),
	LOCATION(RC_JABU_JABUS_BELLY_MQ_JIGGLIES_SMALL_CRATE_2, (logic->CanUse(RG_FAIRY_SLINGSHOT) && logic->CanBreakSmallCrates())),
}, {
	Entrance(RR_JABU_JABUS_BELLY_MQ_LIFT_ROOM, []{return (logic->CanUse(RG_BOOMERANG) && logic->CanUse(RG_FAIRY_SLINGSHOT));}),
	Entrance(RR_JABU_JABUS_BELLY_MQ_HOLES_ROOM, []{return (logic->TakeDamage() && Here(RR_JABU_JABUS_BELLY_MQ_PAST_OCTO, []{return logic->CanKillEnemy(RE_BIG_OCTO);}));}),
});
areaTable[RR_JABU_JABUS_BELLY_MQ_EAST_ROOM] = Region("Jabu Jabus Belly MQ Boss Region", SCENE_JABU_JABU, false, {RA_JABU_JABUS_BELLY}, {
	EventAccess(&logic->FairyPot, []{return true;}),
}, {
	LOCATION(RC_JABU_JABUS_BELLY_MQ_NEAR_BOSS_CHEST, logic->CanUse(RG_FAIRY_SLINGSHOT)),
	LOCATION(RC_JABU_JABUS_BELLY_MQ_GS_NEAR_BOSS, (logic->CanUse(RG_BOOMERANG) || ((bool)ctx->GetTrickOption(RT_JABU_NEAR_BOSS_RANGED) && logic->CanUse(RG_HOOKSHOT)))),
	LOCATION(RC_JABU_JABUS_BELLY_MQ_BEFORE_BOSS_POT_1, logic->CanBreakPots()),
	LOCATION(RC_JABU_JABUS_BELLY_MQ_BEFORE_BOSS_GRASS_1, logic->CanCutShrubs()),
	LOCATION(RC_JABU_JABUS_BELLY_MQ_BEFORE_BOSS_GRASS_2, logic->CanCutShrubs()),
}, {
	Entrance(RR_JABU_JABUS_BELLY_MQ_LIFT_ROOM_EAST_LEDGE, []{return true;}),
	Entrance(RR_JABU_JABUS_BELLY_BOSS_ENTRYWAY, []{return Here(RR_JABU_JABUS_BELLY_MQ_EAST_ROOM, []{return logic->CanUse(RG_FAIRY_SLINGSHOT);});}),
});
areaTable[RR_JABU_JABUS_BELLY_BOSS_ENTRYWAY] = Region("Jabu Jabus Belly Boss Entryway", SCENE_JABU_JABU, false, {RA_JABU_JABUS_BELLY}, {}, {}, {
	Entrance(RR_JABU_JABUS_BELLY_BOSS_ROOM, []{return true;}),
});
areaTable[RR_JABU_JABUS_BELLY_BOSS_EXIT] = Region("Jabu Jabus Belly Boss Exit", SCENE_JABU_JABU, false, {RA_JABU_JABUS_BELLY}, {}, {}, {
	Entrance(RR_JABU_JABUS_BELLY_NEAR_BOSS_ROOM, []{return ctx->GetDungeon(Rando::JABU_JABUS_BELLY)->IsVanilla();}),
	Entrance(RR_JABU_JABUS_BELLY_MQ_EAST_ROOM, []{return ctx->GetDungeon(Rando::JABU_JABUS_BELLY)->IsMQ();}),
});
areaTable[RR_JABU_JABUS_BELLY_BOSS_ROOM] = Region("Jabu Jabus Belly Boss Room", SCENE_JABU_JABU_BOSS, false, {}, {
	EventAccess(&logic->JabuJabusBellyClear, []{return logic->CanKillEnemy(RE_BARINADE);}),
}, {
	LOCATION(RC_JABU_JABUS_BELLY_BARINADE_POT_1, logic->CanBreakPots()),
	LOCATION(RC_JABU_JABUS_BELLY_BARINADE_POT_2, logic->CanBreakPots()),
	LOCATION(RC_JABU_JABUS_BELLY_BARINADE_POT_3, logic->CanBreakPots()),
	LOCATION(RC_JABU_JABUS_BELLY_BARINADE_POT_4, logic->CanBreakPots()),
	LOCATION(RC_JABU_JABUS_BELLY_BARINADE_POT_5, logic->CanBreakPots()),
	LOCATION(RC_JABU_JABUS_BELLY_BARINADE_POT_6, logic->CanBreakPots()),
	LOCATION(RC_JABU_JABUS_BELLY_BARINADE_HEART, logic->JabuJabusBellyClear),
	LOCATION(RC_BARINADE, logic->JabuJabusBellyClear),
}, {
	Entrance(RR_JABU_JABUS_BELLY_BOSS_EXIT, []{return false;}),
	Entrance(RR_ZORAS_FOUNTAIN, []{return logic->JabuJabusBellyClear;}, "", false),
});
areaTable[RR_FOREST_TEMPLE_FIRST_ROOM] = Region("Forest Temple First Room", SCENE_FOREST_TEMPLE, false, {RA_FOREST_TEMPLE}, {}, {
	LOCATION(RC_FOREST_TEMPLE_FIRST_ROOM_CHEST, true),
	LOCATION(RC_FOREST_TEMPLE_GS_FIRST_ROOM, ((logic->IsAdult && logic->CanUse(RG_BOMB_BAG)) || (logic->CanUse(RG_FAIRY_BOW) || (logic->CanUse(RG_HOOKSHOT) || (logic->CanUse(RG_BOOMERANG) || (logic->CanUse(RG_FAIRY_SLINGSHOT) || (logic->CanUse(RG_BOMBCHU_5) || (logic->CanUse(RG_DINS_FIRE) || ((bool)ctx->GetTrickOption(RT_FOREST_FIRST_GS) && (logic->CanJumpslashExceptHammer() || (logic->IsChild && logic->CanUse(RG_BOMB_BAG)))))))))))),
}, {
	Entrance(RR_FOREST_TEMPLE_ENTRYWAY, []{return true;}),
	Entrance(RR_FOREST_TEMPLE_SOUTH_CORRIDOR, []{return true;}),
});
areaTable[RR_FOREST_TEMPLE_SOUTH_CORRIDOR] = Region("Forest Temple South Corridor", SCENE_FOREST_TEMPLE, false, {RA_FOREST_TEMPLE}, {}, {}, {
	Entrance(RR_FOREST_TEMPLE_FIRST_ROOM, []{return true;}),
	Entrance(RR_FOREST_TEMPLE_LOBBY, []{return logic->CanPassEnemy(RE_BIG_SKULLTULA);}),
});
areaTable[RR_FOREST_TEMPLE_LOBBY] = Region("Forest Temple Lobby", SCENE_FOREST_TEMPLE, false, {RA_FOREST_TEMPLE}, {
	EventAccess(&logic->ForestTempleMeg, []{return (logic->ForestTempleJoelle && (logic->ForestTempleBeth && (logic->ForestTempleAmy && logic->CanUse(RG_FAIRY_BOW))));}),
}, {
	LOCATION(RC_FOREST_TEMPLE_GS_LOBBY, logic->HookshotOrBoomerang()),
	LOCATION(RC_FOREST_TEMPLE_LOBBY_POT_1, logic->CanBreakPots()),
	LOCATION(RC_FOREST_TEMPLE_LOBBY_POT_2, logic->CanBreakPots()),
	LOCATION(RC_FOREST_TEMPLE_LOBBY_POT_3, logic->CanBreakPots()),
	LOCATION(RC_FOREST_TEMPLE_LOBBY_POT_4, logic->CanBreakPots()),
	LOCATION(RC_FOREST_TEMPLE_LOBBY_POT_5, logic->CanBreakPots()),
	LOCATION(RC_FOREST_TEMPLE_LOBBY_POT_6, logic->CanBreakPots()),
}, {
	Entrance(RR_FOREST_TEMPLE_SOUTH_CORRIDOR, []{return true;}),
	Entrance(RR_FOREST_TEMPLE_NORTH_CORRIDOR, []{return true;}),
	Entrance(RR_FOREST_TEMPLE_NW_OUTDOORS_LOWER, []{return (logic->CanUse(RG_SONG_OF_TIME) || logic->IsChild);}),
	Entrance(RR_FOREST_TEMPLE_NE_OUTDOORS_LOWER, []{return (logic->CanUse(RG_FAIRY_BOW) || logic->CanUse(RG_FAIRY_SLINGSHOT));}),
	Entrance(RR_FOREST_TEMPLE_WEST_CORRIDOR, []{return logic->SmallKeys(RR_FOREST_TEMPLE, 1, 5);}),
	Entrance(RR_FOREST_TEMPLE_EAST_CORRIDOR, []{return false;}),
	Entrance(RR_FOREST_TEMPLE_BOSS_REGION, []{return logic->ForestTempleMeg;}),
	Entrance(RR_FOREST_TEMPLE_BOSS_ENTRYWAY, []{return false;}),
});
areaTable[RR_FOREST_TEMPLE_NORTH_CORRIDOR] = Region("Forest Temple North Corridor", SCENE_FOREST_TEMPLE, false, {RA_FOREST_TEMPLE}, {}, {}, {
	Entrance(RR_FOREST_TEMPLE_LOBBY, []{return true;}),
	Entrance(RR_FOREST_TEMPLE_LOWER_STALFOS, []{return true;}),
});
areaTable[RR_FOREST_TEMPLE_LOWER_STALFOS] = Region("Forest Temple Lower Stalfos", SCENE_FOREST_TEMPLE, false, {RA_FOREST_TEMPLE}, {
	EventAccess(&logic->FairyPot, []{return true;}),
}, {
	LOCATION(RC_FOREST_TEMPLE_FIRST_STALFOS_CHEST, logic->CanKillEnemy(RE_STALFOS, ED_CLOSE, true, 2)),
	LOCATION(RC_FOREST_TEMPLE_LOWER_STALFOS_POT_1, logic->CanBreakPots()),
	LOCATION(RC_FOREST_TEMPLE_LOWER_STALFOS_POT_2, logic->CanBreakPots()),
}, {
	Entrance(RR_FOREST_TEMPLE_NORTH_CORRIDOR, []{return true;}),
});
areaTable[RR_FOREST_TEMPLE_NW_OUTDOORS_LOWER] = Region("Forest Temple NW Outdoors Lower", SCENE_FOREST_TEMPLE, false, {RA_FOREST_TEMPLE}, {
	EventAccess(&logic->DekuBabaSticks, []{return logic->CanGetDekuBabaSticks();}),
	EventAccess(&logic->DekuBabaNuts, []{return logic->CanGetDekuBabaNuts();}),
}, {
	LOCATION(RC_FOREST_TEMPLE_GS_LEVEL_ISLAND_COURTYARD, (logic->CanUse(RG_LONGSHOT) || Here(RR_FOREST_TEMPLE_NW_OUTDOORS_LOWER, []{return logic->HookshotOrBoomerang();}))),
	LOCATION(RC_FOREST_TEMPLE_COURTYARD_RIGHT_HEART, (logic->CanUse(RG_BOOMERANG) && (bool)ctx->GetTrickOption(RT_FOREST_OUTDOORS_HEARTS_BOOMERANG))),
	LOCATION(RC_FOREST_TEMPLE_COURTYARD_LEFT_HEART, (logic->CanUse(RG_BOOMERANG) && (bool)ctx->GetTrickOption(RT_FOREST_OUTDOORS_HEARTS_BOOMERANG))),
}, {
	Entrance(RR_FOREST_TEMPLE_LOBBY, []{return logic->CanUse(RG_SONG_OF_TIME);}),
	Entrance(RR_FOREST_TEMPLE_NW_OUTDOORS_UPPER, []{return ((bool)ctx->GetTrickOption(RT_HOVER_BOOST_SIMPLE) && ((bool)ctx->GetTrickOption(RT_DAMAGE_BOOST_SIMPLE) && (logic->HasExplosives() && logic->CanUse(RG_HOVER_BOOTS))));}),
	Entrance(RR_FOREST_TEMPLE_MAP_ROOM, []{return true;}),
	Entrance(RR_FOREST_TEMPLE_SEWER, []{return (logic->HasItem(RG_GOLDEN_SCALE) || (logic->CanUse(RG_IRON_BOOTS) || HasAccessTo(RR_FOREST_TEMPLE_NE_OUTDOORS_UPPER)));}),
	Entrance(RR_FOREST_TEMPLE_BOSS_ENTRYWAY, []{return false;}),
});
areaTable[RR_FOREST_TEMPLE_NW_OUTDOORS_UPPER] = Region("Forest Temple NW Outdoors Upper", SCENE_FOREST_TEMPLE, false, {RA_FOREST_TEMPLE}, {
	EventAccess(&logic->DekuBabaSticks, []{return logic->CanGetDekuBabaSticks();}),
	EventAccess(&logic->DekuBabaNuts, []{return logic->CanGetDekuBabaNuts();}),
}, {
	LOCATION(RC_FOREST_TEMPLE_COURTYARD_RIGHT_HEART, true),
	LOCATION(RC_FOREST_TEMPLE_COURTYARD_LEFT_HEART, true),
}, {
	Entrance(RR_FOREST_TEMPLE_NW_OUTDOORS_LOWER, []{return true;}),
	Entrance(RR_FOREST_TEMPLE_BELOW_BOSS_KEY_CHEST, []{return true;}),
	Entrance(RR_FOREST_TEMPLE_FLOORMASTER_ROOM, []{return true;}),
	Entrance(RR_FOREST_TEMPLE_BLOCK_PUSH_ROOM, []{return true;}),
});
areaTable[RR_FOREST_TEMPLE_NE_OUTDOORS_LOWER] = Region("Forest Temple NE Outdoors Lower", SCENE_FOREST_TEMPLE, false, {RA_FOREST_TEMPLE}, {
	EventAccess(&logic->DekuBabaSticks, []{return logic->CanGetDekuBabaSticks();}),
	EventAccess(&logic->DekuBabaNuts, []{return logic->CanGetDekuBabaNuts();}),
}, {
	LOCATION(RC_FOREST_TEMPLE_RAISED_ISLAND_COURTYARD_CHEST, (logic->CanUse(RG_HOOKSHOT) || (HasAccessTo(RR_FOREST_TEMPLE_FALLING_ROOM) || (HasAccessTo(RR_FOREST_TEMPLE_NE_OUTDOORS_UPPER) && (logic->IsAdult && ((bool)ctx->GetTrickOption(RT_FOREST_OUTDOORS_LEDGE) && logic->CanUse(RG_HOVER_BOOTS))))))),
	LOCATION(RC_FOREST_TEMPLE_GS_RAISED_ISLAND_COURTYARD, (logic->CanUse(RG_HOOKSHOT) || (((bool)ctx->GetTrickOption(RT_FOREST_OUTDOORS_EAST_GS) && logic->CanUse(RG_BOOMERANG)) || Here(RR_FOREST_TEMPLE_NE_OUTDOORS_LOWER, []{return (logic->CanUse(RG_FAIRY_BOW) || (logic->CanUse(RG_FAIRY_SLINGSHOT) || (logic->CanUse(RG_DINS_FIRE) || logic->HasExplosives())));})))),
}, {
	Entrance(RR_FOREST_TEMPLE_LOBBY, []{return true;}),
	Entrance(RR_FOREST_TEMPLE_NE_OUTDOORS_UPPER, []{return (logic->CanUse(RG_LONGSHOT) || ((bool)ctx->GetTrickOption(RT_FOREST_VINES) && logic->CanUse(RG_HOOKSHOT)));}),
	Entrance(RR_FOREST_TEMPLE_SEWER, []{return (logic->HasItem(RG_GOLDEN_SCALE) || (logic->CanUse(RG_IRON_BOOTS) || HasAccessTo(RR_FOREST_TEMPLE_NE_OUTDOORS_UPPER)));}),
	Entrance(RR_FOREST_TEMPLE_FALLING_ROOM, []{return false;}),
});
areaTable[RR_FOREST_TEMPLE_NE_OUTDOORS_UPPER] = Region("Forest Temple NE Outdoors Upper", SCENE_FOREST_TEMPLE, false, {RA_FOREST_TEMPLE}, {
	EventAccess(&logic->DekuBabaSticks, []{return logic->CanGetDekuBabaSticks();}),
	EventAccess(&logic->DekuBabaNuts, []{return logic->CanGetDekuBabaNuts();}),
}, {}, {
	Entrance(RR_FOREST_TEMPLE_NE_OUTDOORS_LOWER, []{return true;}),
	Entrance(RR_FOREST_TEMPLE_MAP_ROOM, []{return true;}),
	Entrance(RR_FOREST_TEMPLE_FALLING_ROOM, []{return ((bool)ctx->GetTrickOption(RT_FOREST_DOORFRAME) && (logic->CanJumpslashExceptHammer() && (logic->CanUse(RG_HOVER_BOOTS) && logic->CanUse(RG_SCARECROW))));}),
});
areaTable[RR_FOREST_TEMPLE_MAP_ROOM] = Region("Forest Temple Map Room", SCENE_FOREST_TEMPLE, false, {RA_FOREST_TEMPLE}, {}, {
	LOCATION(RC_FOREST_TEMPLE_MAP_CHEST, logic->CanKillEnemy(RE_BLUE_BUBBLE)),
}, {
	Entrance(RR_FOREST_TEMPLE_NW_OUTDOORS_LOWER, []{return Here(RR_FOREST_TEMPLE_MAP_ROOM, []{return logic->CanKillEnemy(RE_BLUE_BUBBLE);});}),
	Entrance(RR_FOREST_TEMPLE_NE_OUTDOORS_UPPER, []{return Here(RR_FOREST_TEMPLE_MAP_ROOM, []{return logic->CanKillEnemy(RE_BLUE_BUBBLE);});}),
});
areaTable[RR_FOREST_TEMPLE_SEWER] = Region("Forest Temple Sewer", SCENE_FOREST_TEMPLE, false, {RA_FOREST_TEMPLE}, {}, {
	LOCATION(RC_FOREST_TEMPLE_WELL_CHEST, (HasAccessTo(RR_FOREST_TEMPLE_NE_OUTDOORS_UPPER) || (logic->CanOpenUnderwaterChest() && (logic->WaterTimer() >= 8)))),
	LOCATION(RC_FOREST_TEMPLE_WELL_WEST_HEART, (HasAccessTo(RR_FOREST_TEMPLE_NE_OUTDOORS_UPPER) || (logic->CanUse(RG_IRON_BOOTS) && (logic->WaterTimer() >= 8)))),
	LOCATION(RC_FOREST_TEMPLE_WELL_EAST_HEART, (HasAccessTo(RR_FOREST_TEMPLE_NE_OUTDOORS_UPPER) || (logic->CanUse(RG_IRON_BOOTS) && (logic->WaterTimer() >= 8)))),
}, {
	Entrance(RR_FOREST_TEMPLE_NW_OUTDOORS_LOWER, []{return true;}),
	Entrance(RR_FOREST_TEMPLE_NE_OUTDOORS_LOWER, []{return true;}),
});
areaTable[RR_FOREST_TEMPLE_BELOW_BOSS_KEY_CHEST] = Region("Forest Temple Below Boss Key Chest", SCENE_FOREST_TEMPLE, false, {RA_FOREST_TEMPLE}, {}, {}, {
	Entrance(RR_FOREST_TEMPLE_NW_OUTDOORS_UPPER, []{return Here(RR_FOREST_TEMPLE_BELOW_BOSS_KEY_CHEST, []{return logic->CanKillEnemy(RE_BLUE_BUBBLE);});}),
});
areaTable[RR_FOREST_TEMPLE_FLOORMASTER_ROOM] = Region("Forest Temple Floormaster Room", SCENE_FOREST_TEMPLE, false, {RA_FOREST_TEMPLE}, {}, {
	LOCATION(RC_FOREST_TEMPLE_FLOORMASTER_CHEST, logic->CanDamage()),
}, {
	Entrance(RR_FOREST_TEMPLE_NW_OUTDOORS_UPPER, []{return true;}),
});
areaTable[RR_FOREST_TEMPLE_WEST_CORRIDOR] = Region("Forest Temple West Corridor", SCENE_FOREST_TEMPLE, false, {RA_FOREST_TEMPLE}, {}, {}, {
	Entrance(RR_FOREST_TEMPLE_LOBBY, []{return logic->SmallKeys(RR_FOREST_TEMPLE, 1, 5);}),
	Entrance(RR_FOREST_TEMPLE_BLOCK_PUSH_ROOM, []{return (logic->CanAttack() || logic->CanUse(RG_NUTS));}),
});
areaTable[RR_FOREST_TEMPLE_BLOCK_PUSH_ROOM] = Region("Forest Temple Block Push Room", SCENE_FOREST_TEMPLE, false, {RA_FOREST_TEMPLE}, {}, {
	LOCATION(RC_FOREST_TEMPLE_EYE_SWITCH_CHEST, (logic->HasItem(RG_GORONS_BRACELET) && (logic->CanUse(RG_FAIRY_BOW) || logic->CanUse(RG_FAIRY_SLINGSHOT)))),
}, {
	Entrance(RR_FOREST_TEMPLE_WEST_CORRIDOR, []{return true;}),
	Entrance(RR_FOREST_TEMPLE_NW_OUTDOORS_UPPER, []{return (logic->CanUse(RG_HOVER_BOOTS) || ((bool)ctx->GetTrickOption(RT_FOREST_OUTSIDE_BACKDOOR) && (logic->CanJumpslashExceptHammer() && logic->HasItem(RG_GORONS_BRACELET))));}),
	Entrance(RR_FOREST_TEMPLE_NW_CORRIDOR_TWISTED, []{return (logic->IsAdult && (logic->HasItem(RG_GORONS_BRACELET) && logic->SmallKeys(RR_FOREST_TEMPLE, 2)));}),
	Entrance(RR_FOREST_TEMPLE_NW_CORRIDOR_STRAIGHTENED, []{return (logic->IsAdult && ((logic->CanUse(RG_FAIRY_BOW) || logic->CanUse(RG_FAIRY_SLINGSHOT)) && (logic->HasItem(RG_GORONS_BRACELET) && logic->SmallKeys(RR_FOREST_TEMPLE, 2))));}),
});
areaTable[RR_FOREST_TEMPLE_NW_CORRIDOR_TWISTED] = Region("Forest Temple NW Corridor Twisted", SCENE_FOREST_TEMPLE, false, {RA_FOREST_TEMPLE}, {}, {}, {
	Entrance(RR_FOREST_TEMPLE_BLOCK_PUSH_ROOM, []{return logic->SmallKeys(RR_FOREST_TEMPLE, 2);}),
	Entrance(RR_FOREST_TEMPLE_RED_POE_ROOM, []{return logic->SmallKeys(RR_FOREST_TEMPLE, 3);}),
});
areaTable[RR_FOREST_TEMPLE_NW_CORRIDOR_STRAIGHTENED] = Region("Forest Temple NW Corridor Straightened", SCENE_FOREST_TEMPLE, false, {RA_FOREST_TEMPLE}, {}, {
	LOCATION(RC_FOREST_TEMPLE_BOSS_KEY_CHEST, true),
}, {
	Entrance(RR_FOREST_TEMPLE_BELOW_BOSS_KEY_CHEST, []{return true;}),
	Entrance(RR_FOREST_TEMPLE_BLOCK_PUSH_ROOM, []{return logic->SmallKeys(RR_FOREST_TEMPLE, 2);}),
});
areaTable[RR_FOREST_TEMPLE_RED_POE_ROOM] = Region("Forest Temple Red Poe Room", SCENE_FOREST_TEMPLE, false, {RA_FOREST_TEMPLE}, {
	EventAccess(&logic->ForestTempleJoelle, []{return logic->CanUse(RG_FAIRY_BOW);}),
}, {
	LOCATION(RC_FOREST_TEMPLE_RED_POE_CHEST, logic->ForestTempleJoelle),
}, {
	Entrance(RR_FOREST_TEMPLE_NW_CORRIDOR_TWISTED, []{return logic->SmallKeys(RR_FOREST_TEMPLE, 3);}),
	Entrance(RR_FOREST_TEMPLE_UPPER_STALFOS, []{return true;}),
});
areaTable[RR_FOREST_TEMPLE_UPPER_STALFOS] = Region("Forest Temple Upper Stalfos", SCENE_FOREST_TEMPLE, false, {RA_FOREST_TEMPLE}, {}, {
	LOCATION(RC_FOREST_TEMPLE_BOW_CHEST, logic->CanKillEnemy(RE_STALFOS, ED_CLOSE, true, 3)),
	LOCATION(RC_FOREST_TEMPLE_UPPER_STALFOS_POT_1, logic->CanBreakPots()),
	LOCATION(RC_FOREST_TEMPLE_UPPER_STALFOS_POT_2, logic->CanBreakPots()),
	LOCATION(RC_FOREST_TEMPLE_UPPER_STALFOS_POT_3, logic->CanBreakPots()),
	LOCATION(RC_FOREST_TEMPLE_UPPER_STALFOS_POT_4, logic->CanBreakPots()),
}, {
	Entrance(RR_FOREST_TEMPLE_RED_POE_ROOM, []{return logic->CanKillEnemy(RE_STALFOS, ED_CLOSE, true, 3);}),
	Entrance(RR_FOREST_TEMPLE_BLUE_POE_ROOM, []{return logic->CanKillEnemy(RE_STALFOS, ED_CLOSE, true, 3);}),
});
areaTable[RR_FOREST_TEMPLE_BLUE_POE_ROOM] = Region("Forest Temple Blue Poe Room", SCENE_FOREST_TEMPLE, false, {RA_FOREST_TEMPLE}, {
	EventAccess(&logic->ForestTempleBeth, []{return logic->CanUse(RG_FAIRY_BOW);}),
}, {
	LOCATION(RC_FOREST_TEMPLE_BLUE_POE_CHEST, logic->ForestTempleBeth),
	LOCATION(RC_FOREST_TEMPLE_BLUE_POE_POT_1, logic->CanBreakPots()),
	LOCATION(RC_FOREST_TEMPLE_BLUE_POE_POT_2, logic->CanBreakPots()),
	LOCATION(RC_FOREST_TEMPLE_BLUE_POE_POT_3, logic->CanBreakPots()),
}, {
	Entrance(RR_FOREST_TEMPLE_UPPER_STALFOS, []{return true;}),
	Entrance(RR_FOREST_TEMPLE_NE_CORRIDOR_STRAIGHTENED, []{return logic->SmallKeys(RR_FOREST_TEMPLE, 4);}),
});
areaTable[RR_FOREST_TEMPLE_NE_CORRIDOR_STRAIGHTENED] = Region("Forest Temple NE Corridor Straightened", SCENE_FOREST_TEMPLE, false, {RA_FOREST_TEMPLE}, {}, {}, {
	Entrance(RR_FOREST_TEMPLE_BLUE_POE_ROOM, []{return logic->SmallKeys(RR_FOREST_TEMPLE, 4);}),
	Entrance(RR_FOREST_TEMPLE_FROZEN_EYE_ROOM, []{return logic->SmallKeys(RR_FOREST_TEMPLE, 5);}),
});
areaTable[RR_FOREST_TEMPLE_NE_CORRIDOR_TWISTED] = Region("Forest Temple NE Corridor Twisted", SCENE_FOREST_TEMPLE, false, {RA_FOREST_TEMPLE}, {}, {}, {
	Entrance(RR_FOREST_TEMPLE_FROZEN_EYE_ROOM, []{return logic->SmallKeys(RR_FOREST_TEMPLE, 5);}),
	Entrance(RR_FOREST_TEMPLE_FALLING_ROOM, []{return true;}),
});
areaTable[RR_FOREST_TEMPLE_FROZEN_EYE_ROOM] = Region("Forest Temple Frozen Eye Room", SCENE_FOREST_TEMPLE, false, {RA_FOREST_TEMPLE}, {}, {
	LOCATION(RC_FOREST_TEMPLE_FROZEN_EYE_POT_1, logic->CanBreakPots()),
	LOCATION(RC_FOREST_TEMPLE_FROZEN_EYE_POT_2, logic->CanBreakPots()),
}, {
	Entrance(RR_FOREST_TEMPLE_NE_CORRIDOR_STRAIGHTENED, []{return logic->SmallKeys(RR_FOREST_TEMPLE, 5);}),
	Entrance(RR_FOREST_TEMPLE_NE_CORRIDOR_TWISTED, []{return (logic->SmallKeys(RR_FOREST_TEMPLE, 5) && (logic->CanUse(RG_FAIRY_BOW) || logic->CanUse(RG_DINS_FIRE)));}),
});
areaTable[RR_FOREST_TEMPLE_FALLING_ROOM] = Region("Forest Temple Falling Room", SCENE_FOREST_TEMPLE, false, {RA_FOREST_TEMPLE}, {}, {
	LOCATION(RC_FOREST_TEMPLE_FALLING_CEILING_ROOM_CHEST, true),
}, {
	Entrance(RR_FOREST_TEMPLE_NE_OUTDOORS_LOWER, []{return true;}),
	Entrance(RR_FOREST_TEMPLE_GREEN_POE_ROOM, []{return true;}),
});
areaTable[RR_FOREST_TEMPLE_GREEN_POE_ROOM] = Region("Forest Temple Green Poe Room", SCENE_FOREST_TEMPLE, false, {RA_FOREST_TEMPLE}, {
	EventAccess(&logic->ForestTempleAmy, []{return logic->CanUse(RG_FAIRY_BOW);}),
}, {
	LOCATION(RC_FOREST_TEMPLE_GREEN_POE_POT_1, logic->CanBreakPots()),
	LOCATION(RC_FOREST_TEMPLE_GREEN_POE_POT_2, logic->CanBreakPots()),
}, {
	Entrance(RR_FOREST_TEMPLE_FALLING_ROOM, []{return true;}),
	Entrance(RR_FOREST_TEMPLE_EAST_CORRIDOR, []{return logic->ForestTempleAmy;}),
});
areaTable[RR_FOREST_TEMPLE_EAST_CORRIDOR] = Region("Forest Temple East Corridor", SCENE_FOREST_TEMPLE, false, {RA_FOREST_TEMPLE}, {}, {}, {
	Entrance(RR_FOREST_TEMPLE_LOBBY, []{return (logic->CanAttack() || logic->CanUse(RG_NUTS));}),
	Entrance(RR_FOREST_TEMPLE_GREEN_POE_ROOM, []{return (logic->CanAttack() || logic->CanUse(RG_NUTS));}),
});
areaTable[RR_FOREST_TEMPLE_BOSS_REGION] = Region("Forest Temple Boss Region", SCENE_FOREST_TEMPLE, false, {RA_FOREST_TEMPLE}, {}, {
	LOCATION(RC_FOREST_TEMPLE_BASEMENT_CHEST, true),
	LOCATION(RC_FOREST_TEMPLE_GS_BASEMENT, logic->HookshotOrBoomerang()),
}, {
	Entrance(RR_FOREST_TEMPLE_LOBBY, []{return true;}),
	Entrance(RR_FOREST_TEMPLE_BOSS_ENTRYWAY, []{return true;}),
});
areaTable[RR_FOREST_TEMPLE_MQ_LOBBY] = Region("Forest Temple MQ Lobby", SCENE_FOREST_TEMPLE, false, {RA_FOREST_TEMPLE}, {}, {
	LOCATION(RC_FOREST_TEMPLE_MQ_FIRST_ROOM_CHEST, (logic->CanPassEnemy(RE_BIG_SKULLTULA, ED_SHORT_JUMPSLASH, false) || logic->CanUse(RG_HOVER_BOOTS))),
	LOCATION(RC_FOREST_TEMPLE_MQ_GS_FIRST_HALLWAY, logic->HookshotOrBoomerang()),
}, {
	Entrance(RR_FOREST_TEMPLE_ENTRYWAY, []{return true;}),
	Entrance(RR_FOREST_TEMPLE_MQ_CENTRAL_AREA, []{return (logic->SmallKeys(RR_FOREST_TEMPLE, 1) && logic->CanPassEnemy(RE_BIG_SKULLTULA));}),
});
areaTable[RR_FOREST_TEMPLE_MQ_CENTRAL_AREA] = Region("Forest Temple MQ Central Region", SCENE_FOREST_TEMPLE, false, {RA_FOREST_TEMPLE}, {
	EventAccess(&logic->ForestTempleMeg, []{return (logic->ForestTempleJoelle && (logic->ForestTempleBeth && (logic->ForestTempleAmy && logic->CanKillEnemy(RE_MEG))));}),
}, {
	LOCATION(RC_FOREST_TEMPLE_MQ_LOBBY_POT_1, logic->CanBreakPots()),
	LOCATION(RC_FOREST_TEMPLE_MQ_LOBBY_POT_2, logic->CanBreakPots()),
	LOCATION(RC_FOREST_TEMPLE_MQ_LOBBY_POT_3, logic->CanBreakPots()),
	LOCATION(RC_FOREST_TEMPLE_MQ_LOBBY_POT_4, logic->CanBreakPots()),
	LOCATION(RC_FOREST_TEMPLE_MQ_LOBBY_POT_5, logic->CanBreakPots()),
	LOCATION(RC_FOREST_TEMPLE_MQ_LOBBY_POT_6, logic->CanBreakPots()),
}, {
	Entrance(RR_FOREST_TEMPLE_MQ_WOLFOS_ROOM, []{return (logic->IsChild || logic->CanUse(RG_SONG_OF_TIME));}),
	Entrance(RR_FOREST_TEMPLE_MQ_NW_OUTDOORS, []{return logic->CanHitEyeTargets();}),
	Entrance(RR_FOREST_TEMPLE_MQ_NE_OUTDOORS, []{return logic->CanHitEyeTargets();}),
	Entrance(RR_FOREST_TEMPLE_MQ_LOWER_BLOCK_PUZZLE, []{return Here(RR_FOREST_TEMPLE_MQ_CENTRAL_AREA, []{return logic->CanKillEnemy(RE_STALFOS);});}),
	Entrance(RR_FOREST_TEMPLE_MQ_BASEMENT, []{return logic->ForestTempleMeg;}),
});
areaTable[RR_FOREST_TEMPLE_MQ_WOLFOS_ROOM] = Region("Forest Temple MQ Wolfos Room", SCENE_FOREST_TEMPLE, false, {RA_FOREST_TEMPLE}, {
	EventAccess(&logic->FairyPot, []{return true;}),
	EventAccess(&logic->ForestClearBelowBowChest, []{return logic->CanKillEnemy(RE_WOLFOS);}),
}, {
	LOCATION(RC_FOREST_TEMPLE_MQ_WOLFOS_CHEST, logic->ForestClearBelowBowChest),
	LOCATION(RC_FOREST_TEMPLE_MQ_WOLFOS_POT_1, logic->CanBreakPots()),
	LOCATION(RC_FOREST_TEMPLE_MQ_WOLFOS_POT_2, logic->CanBreakPots()),
}, {
	Entrance(RR_FOREST_TEMPLE_MQ_CENTRAL_AREA, []{return (logic->ForestClearBelowBowChest && (logic->IsChild || logic->CanUse(RG_SONG_OF_TIME)));}),
});
areaTable[RR_FOREST_TEMPLE_MQ_LOWER_BLOCK_PUZZLE] = Region("Forest Temple MQ Lower Block Puzzle", SCENE_FOREST_TEMPLE, false, {RA_FOREST_TEMPLE}, {
	EventAccess(&logic->MQForestBlockRoomTargets, []{return ((bool)ctx->GetTrickOption(RT_FOREST_MQ_BLOCK_PUZZLE) && logic->CanUse(RG_BOMBCHU_5));}),
	EventAccess(&logic->ForestCanTwistHallway, []{return ((((bool)ctx->GetTrickOption(RT_FOREST_MQ_JS_HALLWAY_SWITCH) && (logic->CanUse(RG_HOVER_BOOTS) && (logic->IsAdult && logic->CanJumpslash()))) || (logic->CanUse(RG_STICKS) || (logic->CanUse(RG_BIGGORON_SWORD) || (logic->MQForestBlockRoomTargets && logic->CanUse(RG_MASTER_SWORD))))) || (((bool)ctx->GetTrickOption(RT_FOREST_MQ_RANG_HALLWAY_SWITCH) && logic->CanUse(RG_BOOMERANG)) || ((bool)ctx->GetTrickOption(RT_FOREST_MQ_HOOKSHOT_HALLWAY_SWITCH) && logic->CanUse(RG_HOOKSHOT))));}),
}, {
	LOCATION(RC_FOREST_TEMPLE_MQ_GS_BLOCK_PUSH_ROOM, logic->CanGetEnemyDrop(RE_GOLD_SKULLTULA)),
}, {
	Entrance(RR_FOREST_TEMPLE_MQ_CENTRAL_AREA, []{return Here(RR_FOREST_TEMPLE_MQ_LOWER_BLOCK_PUZZLE, []{return logic->CanKillEnemy(RE_STALFOS);});}),
	Entrance(RR_FOREST_TEMPLE_MQ_MIDDLE_BLOCK_PUZZLE, []{return (logic->HasItem(RG_GORONS_BRACELET) || (logic->MQForestBlockRoomTargets && logic->CanUse(RG_HOOKSHOT)));}),
	Entrance(RR_FOREST_TEMPLE_MQ_UPPER_BLOCK_PUZZLE, []{return ((logic->IsAdult && logic->HasItem(RG_GORONS_BRACELET)) || (logic->MQForestBlockRoomTargets && logic->CanUse(RG_HOOKSHOT)));}),
	Entrance(RR_FOREST_TEMPLE_MQ_OUTDOOR_LEDGE, []{return (logic->ForestCanTwistHallway && (logic->CanUse(RG_HOOKSHOT) || logic->CanUse(RG_HOVER_BOOTS)));}),
});
areaTable[RR_FOREST_TEMPLE_MQ_MIDDLE_BLOCK_PUZZLE] = Region("Forest Temple MQ Middle Block Puzzle", SCENE_FOREST_TEMPLE, false, {RA_FOREST_TEMPLE}, {
	EventAccess(&logic->MQForestBlockRoomTargets, []{return (logic->CanUse(RG_FAIRY_BOW) || (logic->CanUse(RG_FAIRY_SLINGSHOT) || logic->CanUse(RG_LONGSHOT)));}),
	EventAccess(&logic->ForestCanTwistHallway, []{return (((bool)ctx->GetTrickOption(RT_FOREST_MQ_JS_HALLWAY_SWITCH) && (logic->IsAdult && logic->CanJumpslash())) || (logic->CanUse(RG_HOVER_BOOTS) && (logic->CanUse(RG_STICKS) || (logic->CanUse(RG_BIGGORON_SWORD) || logic->CanUse(RG_MASTER_SWORD)))));}),
}, {}, {
	Entrance(RR_FOREST_TEMPLE_MQ_LOWER_BLOCK_PUZZLE, []{return true;}),
	Entrance(RR_FOREST_TEMPLE_MQ_UPPER_BLOCK_PUZZLE, []{return ((logic->IsAdult && logic->HasItem(RG_GORONS_BRACELET)) || (logic->MQForestBlockRoomTargets && logic->CanUse(RG_HOOKSHOT)));}),
	Entrance(RR_FOREST_TEMPLE_MQ_OUTDOOR_LEDGE, []{return ((logic->ForestCanTwistHallway && logic->CanUse(RG_HOVER_BOOTS)) || ((bool)ctx->GetTrickOption(RT_FOREST_OUTSIDE_BACKDOOR) && (logic->CanJumpslashExceptHammer() || (logic->IsAdult && logic->CanUse(RG_MEGATON_HAMMER)))));}),
});
areaTable[RR_FOREST_TEMPLE_MQ_UPPER_BLOCK_PUZZLE] = Region("Forest Temple MQ After Block Puzzle", SCENE_FOREST_TEMPLE, false, {RA_FOREST_TEMPLE}, {}, {
	LOCATION(RC_FOREST_TEMPLE_MQ_BOSS_KEY_CHEST, logic->SmallKeys(RR_FOREST_TEMPLE, 3)),
}, {
	Entrance(RR_FOREST_TEMPLE_MQ_STRAIGHT_HALLWAY, []{return logic->SmallKeys(RR_FOREST_TEMPLE, 3);}),
	Entrance(RR_FOREST_TEMPLE_MQ_JOELLE_ROOM, []{return (logic->ForestCanTwistHallway && logic->SmallKeys(RR_FOREST_TEMPLE, 4));}),
	Entrance(RR_FOREST_TEMPLE_MQ_NW_OUTDOORS, []{return (logic->SmallKeys(RR_FOREST_TEMPLE, 2) && Here(RR_FOREST_TEMPLE_MQ_UPPER_BLOCK_PUZZLE, []{return logic->CanKillEnemy(RE_FLOORMASTER);}));}),
});
areaTable[RR_FOREST_TEMPLE_MQ_STRAIGHT_HALLWAY] = Region("Forest Temple MQ Straight Hallway", SCENE_FOREST_TEMPLE, false, {RA_FOREST_TEMPLE}, {}, {
	LOCATION(RC_FOREST_TEMPLE_MQ_BOSS_KEY_CHEST, logic->SmallKeys(RR_FOREST_TEMPLE, 3)),
}, {
	Entrance(RR_FOREST_TEMPLE_MQ_FLOORMASTER_ROOM, []{return true;}),
});
areaTable[RR_FOREST_TEMPLE_MQ_FLOORMASTER_ROOM] = Region("Forest Temple MQ Floormaster Room", SCENE_FOREST_TEMPLE, false, {RA_FOREST_TEMPLE}, {}, {}, {
	Entrance(RR_FOREST_TEMPLE_MQ_OUTDOOR_LEDGE, []{return Here(RR_FOREST_TEMPLE_MQ_FLOORMASTER_ROOM, []{return logic->CanKillEnemy(RE_FLOORMASTER);});}),
});
areaTable[RR_FOREST_TEMPLE_MQ_OUTDOOR_LEDGE] = Region("Forest Temple MQ Outdoor Ledge", SCENE_FOREST_TEMPLE, false, {RA_FOREST_TEMPLE}, {
	EventAccess(&logic->ForestCanTwistHallway, []{return logic->CanHitSwitch();}),
}, {
	LOCATION(RC_FOREST_TEMPLE_MQ_REDEAD_CHEST, logic->CanKillEnemy(RE_REDEAD)),
	LOCATION(RC_FOREST_TEMPLE_MQ_COURTYARD_RIGHT_HEART, true),
	LOCATION(RC_FOREST_TEMPLE_MQ_COURTYARD_MIDDLE_HEART, true),
	LOCATION(RC_FOREST_TEMPLE_MQ_COURTYARD_LEFT_HEART, true),
}, {
	Entrance(RR_FOREST_TEMPLE_MQ_NW_OUTDOORS, []{return true;}),
});
areaTable[RR_FOREST_TEMPLE_MQ_NW_OUTDOORS] = Region("Forest Temple MQ NW Outdoors", SCENE_FOREST_TEMPLE, false, {RA_FOREST_TEMPLE}, {}, {
	LOCATION(RC_FOREST_TEMPLE_MQ_GS_LEVEL_ISLAND_COURTYARD, logic->CanGetEnemyDrop(RE_GOLD_SKULLTULA)),
	LOCATION(RC_FOREST_TEMPLE_MQ_GS_WELL, (logic->CanUse(RG_IRON_BOOTS) && ((logic->WaterTimer() >= 8) && logic->CanUse(RG_HOOKSHOT)))),
	LOCATION(RC_FOREST_TEMPLE_MQ_COURTYARD_RIGHT_HEART, (logic->CanUse(RG_BOOMERANG) && (bool)ctx->GetTrickOption(RT_FOREST_OUTDOORS_HEARTS_BOOMERANG))),
	LOCATION(RC_FOREST_TEMPLE_MQ_COURTYARD_MIDDLE_HEART, (logic->CanUse(RG_BOOMERANG) && (bool)ctx->GetTrickOption(RT_FOREST_OUTDOORS_HEARTS_BOOMERANG))),
	LOCATION(RC_FOREST_TEMPLE_MQ_COURTYARD_LEFT_HEART, (logic->CanUse(RG_BOOMERANG) && (bool)ctx->GetTrickOption(RT_FOREST_OUTDOORS_HEARTS_BOOMERANG))),
	LOCATION(RC_FOREST_TEMPLE_MQ_WELL_WEST_HEART, (logic->CanUse(RG_IRON_BOOTS) && (logic->WaterTimer() >= 8))),
	LOCATION(RC_FOREST_TEMPLE_MQ_WELL_MIDDLE_HEART, (logic->CanUse(RG_IRON_BOOTS) && (logic->WaterTimer() >= 8))),
	LOCATION(RC_FOREST_TEMPLE_MQ_WELL_EAST_HEART, (logic->CanUse(RG_IRON_BOOTS) && (logic->WaterTimer() >= 8))),
}, {
	Entrance(RR_FOREST_TEMPLE_MQ_NE_OUTDOORS, []{return ((((logic->CanUse(RG_IRON_BOOTS) || (logic->CanUse(RG_LONGSHOT) || ((bool)ctx->GetTrickOption(RT_FOREST_MQ_WELL_SWIM) && logic->CanUse(RG_HOOKSHOT)))) && logic->HasItem(RG_BRONZE_SCALE)) || logic->HasItem(RG_GOLDEN_SCALE)) && (logic->WaterTimer() >= 16));}),
	Entrance(RR_FOREST_TEMPLE_MQ_OUTDOORS_TOP_LEDGES, []{return logic->CanUse(RG_FIRE_ARROWS);}),
});
areaTable[RR_FOREST_TEMPLE_MQ_NE_OUTDOORS] = Region("Forest Temple MQ NE Outdoors", SCENE_FOREST_TEMPLE, false, {RA_FOREST_TEMPLE}, {
	EventAccess(&logic->DekuBabaSticks, []{return logic->CanGetDekuBabaSticks();}),
	EventAccess(&logic->DekuBabaNuts, []{return logic->CanGetDekuBabaNuts();}),
}, {
	LOCATION(RC_FOREST_TEMPLE_MQ_WELL_CHEST, (logic->CanHitEyeTargets() || (logic->CanOpenUnderwaterChest() && (logic->WaterTimer() >= 8)))),
	LOCATION(RC_FOREST_TEMPLE_MQ_GS_RAISED_ISLAND_COURTYARD, logic->CanGetEnemyDrop(RE_GOLD_SKULLTULA)),
	LOCATION(RC_FOREST_TEMPLE_MQ_GS_WELL, (logic->CanHitEyeTargets() || (logic->CanUse(RG_IRON_BOOTS) && logic->CanUse(RG_HOOKSHOT)))),
	LOCATION(RC_FOREST_TEMPLE_MQ_WELL_WEST_HEART, ((logic->CanUse(RG_IRON_BOOTS) && (logic->WaterTimer() >= 8)) || logic->CanHitEyeTargets())),
	LOCATION(RC_FOREST_TEMPLE_MQ_WELL_MIDDLE_HEART, ((logic->CanUse(RG_IRON_BOOTS) && (logic->WaterTimer() >= 8)) || logic->CanHitEyeTargets())),
	LOCATION(RC_FOREST_TEMPLE_MQ_WELL_EAST_HEART, ((logic->CanUse(RG_IRON_BOOTS) && (logic->WaterTimer() >= 8)) || logic->CanHitEyeTargets())),
}, {
	Entrance(RR_FOREST_TEMPLE_MQ_NW_OUTDOORS, []{return ((((logic->CanUse(RG_IRON_BOOTS) || logic->CanUse(RG_LONGSHOT)) && logic->HasItem(RG_BRONZE_SCALE)) || logic->HasItem(RG_GOLDEN_SCALE)) && (logic->WaterTimer() >= 16));}),
	Entrance(RR_FOREST_TEMPLE_MQ_OUTDOORS_TOP_LEDGES, []{return (logic->CanUse(RG_LONGSHOT) || (logic->CanUse(RG_HOOKSHOT) && ((logic->IsAdult && logic->CanUse(RG_HOVER_BOOTS)) || logic->CanUse(RG_SONG_OF_TIME))));}),
	Entrance(RR_FOREST_TEMPLE_MQ_NE_OUTDOORS_LEDGE, []{return logic->CanUse(RG_LONGSHOT);}),
});
areaTable[RR_FOREST_TEMPLE_MQ_OUTDOORS_TOP_LEDGES] = Region("Forest Temple MQ Outdoors Top Ledges", SCENE_FOREST_TEMPLE, false, {RA_FOREST_TEMPLE}, {}, {
	LOCATION(RC_FOREST_TEMPLE_MQ_RAISED_ISLAND_COURTYARD_UPPER_CHEST, true),
	LOCATION(RC_FOREST_TEMPLE_MQ_GS_RAISED_ISLAND_COURTYARD, (((logic->IsAdult && logic->CanUse(RG_SONG_OF_TIME)) || (logic->CanUse(RG_HOVER_BOOTS) && (bool)ctx->GetTrickOption(RT_FOREST_DOORFRAME))) && (logic->CanJumpslash() && (logic->CanUse(RG_FAIRY_SLINGSHOT) || (logic->BlastOrSmash() || (logic->CanUse(RG_DINS_FIRE) || (logic->CanUse(RG_FAIRY_BOW) || (logic->HookshotOrBoomerang() || (logic->CanStandingShield() && (logic->CanUse(RG_STICKS) || (logic->CanUse(RG_BIGGORON_SWORD) || (logic->CanUse(RG_MASTER_SWORD) || (logic->IsChild && logic->CanUse(RG_KOKIRI_SWORD)))))))))))))),
}, {
	Entrance(RR_FOREST_TEMPLE_MQ_NW_OUTDOORS, []{return logic->HasFireSourceWithTorch();}),
	Entrance(RR_FOREST_TEMPLE_MQ_NE_OUTDOORS, []{return true;}),
	Entrance(RR_FOREST_TEMPLE_MQ_NE_OUTDOORS_LEDGE, []{return ((bool)ctx->GetTrickOption(RT_FOREST_OUTDOORS_LEDGE) && (logic->CanUse(RG_HOVER_BOOTS) && (logic->CanJumpslash() && logic->TakeDamage())));}),
});
areaTable[RR_FOREST_TEMPLE_MQ_NE_OUTDOORS_LEDGE] = Region("Forest Temple MQ NE Outdoors Ledge", SCENE_FOREST_TEMPLE, false, {RA_FOREST_TEMPLE}, {}, {
	LOCATION(RC_FOREST_TEMPLE_MQ_RAISED_ISLAND_COURTYARD_LOWER_CHEST, true),
}, {
	Entrance(RR_FOREST_TEMPLE_MQ_NE_OUTDOORS, []{return true;}),
	Entrance(RR_FOREST_TEMPLE_MQ_FALLING_ROOM, []{return logic->CanUse(RG_SONG_OF_TIME);}),
});
areaTable[RR_FOREST_TEMPLE_MQ_JOELLE_ROOM] = Region("Forest Temple MQ Joelle room", SCENE_FOREST_TEMPLE, false, {RA_FOREST_TEMPLE}, {
	EventAccess(&logic->ForestTempleJoelle, []{return logic->CanUse(RG_FAIRY_BOW);}),
}, {
	LOCATION(RC_FOREST_TEMPLE_MQ_MAP_CHEST, logic->ForestTempleJoelle),
}, {
	Entrance(RR_FOREST_TEMPLE_MQ_UPPER_BLOCK_PUZZLE, []{return logic->SmallKeys(RR_FOREST_TEMPLE, 4);}),
	Entrance(RR_FOREST_TEMPLE_MQ_3_STALFOS_ROOM, []{return true;}),
});
areaTable[RR_FOREST_TEMPLE_MQ_3_STALFOS_ROOM] = Region("Forest Temple MQ 3 Stalfos Room", SCENE_FOREST_TEMPLE, false, {RA_FOREST_TEMPLE}, {
	EventAccess(&logic->ForestClearBelowBowChest, []{return logic->CanKillEnemy(RE_WOLFOS);}),
}, {
	LOCATION(RC_FOREST_TEMPLE_MQ_BOW_CHEST, (logic->ForestClearBelowBowChest && logic->CanKillEnemy(RE_STALFOS, ED_CLOSE, true, 3))),
	LOCATION(RC_FOREST_TEMPLE_MQ_UPPER_STALFOS_POT_1, logic->CanBreakPots()),
	LOCATION(RC_FOREST_TEMPLE_MQ_UPPER_STALFOS_POT_2, logic->CanBreakPots()),
	LOCATION(RC_FOREST_TEMPLE_MQ_UPPER_STALFOS_POT_3, logic->CanBreakPots()),
	LOCATION(RC_FOREST_TEMPLE_MQ_UPPER_STALFOS_POT_4, logic->CanBreakPots()),
}, {
	Entrance(RR_FOREST_TEMPLE_MQ_JOELLE_ROOM, []{return (logic->ForestClearBelowBowChest && logic->CanKillEnemy(RE_STALFOS, ED_CLOSE, true, 3));}),
	Entrance(RR_FOREST_TEMPLE_MQ_BETH_ROOM, []{return (logic->ForestClearBelowBowChest && logic->CanKillEnemy(RE_STALFOS, ED_CLOSE, true, 3));}),
});
areaTable[RR_FOREST_TEMPLE_MQ_BETH_ROOM] = Region("Forest Temple MQ Beth Room", SCENE_FOREST_TEMPLE, false, {RA_FOREST_TEMPLE}, {
	EventAccess(&logic->ForestTempleBeth, []{return logic->CanUse(RG_FAIRY_BOW);}),
}, {
	LOCATION(RC_FOREST_TEMPLE_MQ_COMPASS_CHEST, logic->ForestTempleBeth),
	LOCATION(RC_FOREST_TEMPLE_MQ_BLUE_POE_POT_1, logic->CanBreakPots()),
	LOCATION(RC_FOREST_TEMPLE_MQ_BLUE_POE_POT_2, logic->CanBreakPots()),
	LOCATION(RC_FOREST_TEMPLE_MQ_BLUE_POE_POT_3, logic->CanBreakPots()),
}, {
	Entrance(RR_FOREST_TEMPLE_MQ_FALLING_ROOM, []{return (logic->SmallKeys(RR_FOREST_TEMPLE, 5) && Here(RR_FOREST_TEMPLE_MQ_BETH_ROOM, []{return (logic->CanUse(RG_FAIRY_BOW) || logic->CanUse(RG_DINS_FIRE));}));}),
	Entrance(RR_FOREST_TEMPLE_MQ_TORCH_SHOT_ROOM, []{return logic->SmallKeys(RR_FOREST_TEMPLE, 6);}),
	Entrance(RR_FOREST_TEMPLE_MQ_3_STALFOS_ROOM, []{return true;}),
});
areaTable[RR_FOREST_TEMPLE_MQ_TORCH_SHOT_ROOM] = Region("Forest Temple MQ Torch Shot Room", SCENE_FOREST_TEMPLE, false, {RA_FOREST_TEMPLE}, {}, {
	LOCATION(RC_FOREST_TEMPLE_MQ_FROZEN_EYE_SWITCH_SMALL_CRATE_1, logic->CanBreakSmallCrates()),
	LOCATION(RC_FOREST_TEMPLE_MQ_FROZEN_EYE_SWITCH_SMALL_CRATE_2, logic->CanBreakSmallCrates()),
	LOCATION(RC_FOREST_TEMPLE_MQ_FROZEN_EYE_SWITCH_SMALL_CRATE_3, logic->CanBreakSmallCrates()),
}, {
	Entrance(RR_FOREST_TEMPLE_MQ_FALLING_ROOM, []{return (logic->CanUse(RG_FAIRY_BOW) || logic->CanUse(RG_DINS_FIRE));}),
	Entrance(RR_FOREST_TEMPLE_MQ_BETH_ROOM, []{return logic->SmallKeys(RR_FOREST_TEMPLE, 6);}),
});
areaTable[RR_FOREST_TEMPLE_MQ_FALLING_ROOM] = Region("Forest Temple MQ Falling Room", SCENE_FOREST_TEMPLE, false, {RA_FOREST_TEMPLE}, {}, {
	LOCATION(RC_FOREST_TEMPLE_MQ_FALLING_CEILING_ROOM_CHEST, true),
}, {
	Entrance(RR_FOREST_TEMPLE_MQ_NE_OUTDOORS_LEDGE, []{return true;}),
	Entrance(RR_FOREST_TEMPLE_MQ_AMY_ROOM, []{return logic->SmallKeys(RR_FOREST_TEMPLE, 6);}),
});
areaTable[RR_FOREST_TEMPLE_MQ_AMY_ROOM] = Region("Forest Temple MQ Amy Room", SCENE_FOREST_TEMPLE, false, {RA_FOREST_TEMPLE}, {
	EventAccess(&logic->ForestTempleAmy, []{return logic->CanUse(RG_FAIRY_BOW);}),
}, {
	LOCATION(RC_FOREST_TEMPLE_MQ_GREEN_POE_POT_1, logic->CanBreakPots()),
	LOCATION(RC_FOREST_TEMPLE_MQ_GREEN_POE_POT_2, logic->CanBreakPots()),
}, {
	Entrance(RR_FOREST_TEMPLE_MQ_CENTRAL_AREA, []{return logic->ForestTempleAmy;}),
	Entrance(RR_FOREST_TEMPLE_MQ_FALLING_ROOM, []{return true;}),
});
areaTable[RR_FOREST_TEMPLE_MQ_BASEMENT] = Region("Forest Temple MQ Basement", SCENE_FOREST_TEMPLE, false, {RA_FOREST_TEMPLE}, {
	EventAccess(&logic->ForestOpenBossCorridor, []{return logic->CanHitEyeTargets();}),
}, {
	LOCATION(RC_FOREST_TEMPLE_MQ_BASEMENT_CHEST, true),
}, {
	Entrance(RR_FOREST_TEMPLE_MQ_CENTRAL_AREA, []{return logic->ForestTempleMeg;}),
	Entrance(RR_FOREST_TEMPLE_MQ_BASEMENT_POT_ROOM, []{return (logic->CanPassEnemy(RE_BIG_SKULLTULA) || logic->TakeDamage());}),
	Entrance(RR_FOREST_TEMPLE_MQ_BOSS_REGION, []{return logic->ForestOpenBossCorridor;}),
});
areaTable[RR_FOREST_TEMPLE_MQ_BASEMENT_POT_ROOM] = Region("Forest Temple MQ Basement Pot Room", SCENE_FOREST_TEMPLE, false, {RA_FOREST_TEMPLE}, {}, {
	LOCATION(RC_FOREST_TEMPLE_MQ_BASEMENT_POT_1, logic->CanBreakPots()),
	LOCATION(RC_FOREST_TEMPLE_MQ_BASEMENT_POT_2, logic->CanBreakPots()),
	LOCATION(RC_FOREST_TEMPLE_MQ_BASEMENT_POT_3, logic->CanBreakPots()),
	LOCATION(RC_FOREST_TEMPLE_MQ_BASEMENT_POT_4, logic->CanBreakPots()),
}, {
	Entrance(RR_FOREST_TEMPLE_MQ_BASEMENT, []{return logic->CanPassEnemy(RE_BIG_SKULLTULA);}),
});
areaTable[RR_FOREST_TEMPLE_MQ_BOSS_REGION] = Region("Forest Temple MQ Boss Region", SCENE_FOREST_TEMPLE, false, {RA_FOREST_TEMPLE}, {}, {}, {
	Entrance(RR_FOREST_TEMPLE_MQ_BASEMENT, []{return logic->ForestOpenBossCorridor;}),
	Entrance(RR_FOREST_TEMPLE_BOSS_ENTRYWAY, []{return true;}),
});
areaTable[RR_FOREST_TEMPLE_BOSS_ENTRYWAY] = Region("Forest Temple Boss Entryway", SCENE_FOREST_TEMPLE, false, {RA_FOREST_TEMPLE}, {}, {}, {
	Entrance(RR_FOREST_TEMPLE_BOSS_REGION, []{return (ctx->GetDungeon(Rando::FOREST_TEMPLE)->IsVanilla() && false);}),
	Entrance(RR_FOREST_TEMPLE_MQ_BOSS_REGION, []{return (ctx->GetDungeon(Rando::FOREST_TEMPLE)->IsMQ() && false);}),
	Entrance(RR_FOREST_TEMPLE_BOSS_ROOM, []{return logic->HasItem(RG_FOREST_TEMPLE_BOSS_KEY);}),
});
areaTable[RR_FOREST_TEMPLE_BOSS_ROOM] = Region("Forest Temple Boss Room", SCENE_FOREST_TEMPLE_BOSS, false, {}, {
	EventAccess(&logic->ForestTempleClear, []{return logic->CanKillEnemy(RE_PHANTOM_GANON);}),
}, {
	LOCATION(RC_FOREST_TEMPLE_PHANTOM_GANON_HEART, logic->ForestTempleClear),
	LOCATION(RC_PHANTOM_GANON, logic->ForestTempleClear),
}, {
	Entrance(RR_FOREST_TEMPLE_BOSS_ENTRYWAY, []{return false;}),
	Entrance(RR_SACRED_FOREST_MEADOW, []{return logic->ForestTempleClear;}, "", false),
});
areaTable[RR_FIRE_TEMPLE_FIRST_ROOM] = Region("Fire Temple First Room", SCENE_FIRE_TEMPLE, false, {RA_FIRE_TEMPLE}, {}, {}, {
	Entrance(RR_FIRE_TEMPLE_ENTRYWAY, []{return true;}),
	Entrance(RR_FIRE_TEMPLE_NEAR_BOSS_ROOM, []{return (logic->FireTimer() >= 24);}),
	Entrance(RR_FIRE_TEMPLE_LOOP_ENEMIES, []{return (Here(RR_FIRE_TEMPLE_FIRST_ROOM, []{return logic->CanUse(RG_MEGATON_HAMMER);}) && (logic->SmallKeys(RR_FIRE_TEMPLE, 8) || !logic->IsFireLoopLocked));}),
	Entrance(RR_FIRE_TEMPLE_LOOP_EXIT, []{return true;}),
	Entrance(RR_FIRE_TEMPLE_BIG_LAVA_ROOM, []{return (logic->SmallKeys(RR_FIRE_TEMPLE, 2) && (logic->FireTimer() >= 24));}),
});
areaTable[RR_FIRE_TEMPLE_NEAR_BOSS_ROOM] = Region("Fire Temple Near Boss Room", SCENE_FIRE_TEMPLE, false, {RA_FIRE_TEMPLE}, {
	EventAccess(&logic->FairyPot, []{return (logic->CanUse(RG_HOVER_BOOTS) || logic->CanUse(RG_HOOKSHOT));}),
}, {
	LOCATION(RC_FIRE_TEMPLE_NEAR_BOSS_CHEST, true),
	LOCATION(RC_FIRE_TEMPLE_NEAR_BOSS_POT_1, (logic->CanBreakPots() && (logic->CanUse(RG_HOVER_BOOTS) || logic->CanUse(RG_HOOKSHOT)))),
	LOCATION(RC_FIRE_TEMPLE_NEAR_BOSS_POT_2, (logic->CanBreakPots() && (logic->CanUse(RG_HOVER_BOOTS) || logic->CanUse(RG_HOOKSHOT)))),
	LOCATION(RC_FIRE_TEMPLE_NEAR_BOSS_POT_3, (logic->CanBreakPots() && (logic->CanUse(RG_HOVER_BOOTS) || logic->CanUse(RG_HOOKSHOT)))),
	LOCATION(RC_FIRE_TEMPLE_NEAR_BOSS_POT_4, (logic->CanBreakPots() && (logic->CanUse(RG_HOVER_BOOTS) || logic->CanUse(RG_HOOKSHOT)))),
}, {
	Entrance(RR_FIRE_TEMPLE_FIRST_ROOM, []{return true;}),
	Entrance(RR_FIRE_TEMPLE_BOSS_ENTRYWAY, []{return (logic->IsAdult && ((bool)ctx->GetTrickOption(RT_FIRE_BOSS_DOOR_JUMP) || (Here(RR_FIRE_TEMPLE_NEAR_BOSS_ROOM, []{return logic->CanUse(RG_MEGATON_HAMMER);}) || logic->CanUse(RG_HOVER_BOOTS))));}),
});
areaTable[RR_FIRE_TEMPLE_LOOP_ENEMIES] = Region("Fire Temple Loop Enemies", SCENE_FIRE_TEMPLE, false, {RA_FIRE_TEMPLE}, {}, {}, {
	Entrance(RR_FIRE_TEMPLE_FIRST_ROOM, []{return (logic->SmallKeys(RR_FIRE_TEMPLE, 8) || !logic->IsFireLoopLocked);}),
	Entrance(RR_FIRE_TEMPLE_LOOP_TILES, []{return Here(RR_FIRE_TEMPLE_LOOP_ENEMIES, []{return (logic->CanKillEnemy(RE_TORCH_SLUG) && logic->CanKillEnemy(RE_FIRE_KEESE));});}),
});
areaTable[RR_FIRE_TEMPLE_LOOP_TILES] = Region("Fire Temple Loop Tiles", SCENE_FIRE_TEMPLE, false, {RA_FIRE_TEMPLE}, {}, {
	LOCATION(RC_FIRE_TEMPLE_GS_BOSS_KEY_LOOP, logic->CanAttack()),
}, {
	Entrance(RR_FIRE_TEMPLE_LOOP_ENEMIES, []{return true;}),
	Entrance(RR_FIRE_TEMPLE_LOOP_FLARE_DANCER, []{return true;}),
});
areaTable[RR_FIRE_TEMPLE_LOOP_FLARE_DANCER] = Region("Fire Temple Loop Flare Dancer", SCENE_FIRE_TEMPLE, false, {RA_FIRE_TEMPLE}, {}, {
	LOCATION(RC_FIRE_TEMPLE_FLARE_DANCER_CHEST, ((logic->HasExplosives() || logic->CanUse(RG_MEGATON_HAMMER)) && logic->IsAdult)),
}, {
	Entrance(RR_FIRE_TEMPLE_LOOP_TILES, []{return true;}),
	Entrance(RR_FIRE_TEMPLE_LOOP_HAMMER_SWITCH, []{return Here(RR_FIRE_TEMPLE_LOOP_FLARE_DANCER, []{return logic->CanKillEnemy(RE_FLARE_DANCER);});}),
});
areaTable[RR_FIRE_TEMPLE_LOOP_HAMMER_SWITCH] = Region("Fire Temple Loop Hammer Switch", SCENE_FIRE_TEMPLE, false, {RA_FIRE_TEMPLE}, {
	EventAccess(&logic->FireLoopSwitch, []{return logic->CanUse(RG_MEGATON_HAMMER);}),
}, {}, {
	Entrance(RR_FIRE_TEMPLE_LOOP_FLARE_DANCER, []{return true;}),
	Entrance(RR_FIRE_TEMPLE_LOOP_GORON_ROOM, []{return logic->FireLoopSwitch;}),
});
areaTable[RR_FIRE_TEMPLE_LOOP_GORON_ROOM] = Region("Fire Temple Loop Goron Room", SCENE_FIRE_TEMPLE, false, {RA_FIRE_TEMPLE}, {}, {
	LOCATION(RC_FIRE_TEMPLE_BOSS_KEY_CHEST, true),
}, {
	Entrance(RR_FIRE_TEMPLE_LOOP_HAMMER_SWITCH, []{return logic->FireLoopSwitch;}),
	Entrance(RR_FIRE_TEMPLE_LOOP_EXIT, []{return logic->FireLoopSwitch;}),
});
areaTable[RR_FIRE_TEMPLE_LOOP_EXIT] = Region("Fire Temple Loop Exit", SCENE_FIRE_TEMPLE, false, {RA_FIRE_TEMPLE}, {}, {}, {
	Entrance(RR_FIRE_TEMPLE_FIRST_ROOM, []{return true;}),
	Entrance(RR_FIRE_TEMPLE_LOOP_GORON_ROOM, []{return logic->FireLoopSwitch;}),
});
areaTable[RR_FIRE_TEMPLE_BIG_LAVA_ROOM] = Region("Fire Temple Big Lava Room", SCENE_FIRE_TEMPLE, false, {RA_FIRE_TEMPLE}, {}, {
	LOCATION(RC_FIRE_TEMPLE_BIG_LAVA_POT_1, logic->CanBreakPots()),
	LOCATION(RC_FIRE_TEMPLE_BIG_LAVA_POT_2, logic->CanBreakPots()),
	LOCATION(RC_FIRE_TEMPLE_BIG_LAVA_POT_3, logic->CanBreakPots()),
}, {
	Entrance(RR_FIRE_TEMPLE_FIRST_ROOM, []{return logic->SmallKeys(RR_FIRE_TEMPLE, 2);}),
	Entrance(RR_FIRE_TEMPLE_BIG_LAVA_ROOM_NORTH_GORON, []{return true;}),
	Entrance(RR_FIRE_TEMPLE_BIG_LAVA_ROOM_NORTH_TILES, []{return (logic->IsAdult && (logic->CanUse(RG_SONG_OF_TIME) || (bool)ctx->GetTrickOption(RT_FIRE_SOT)));}),
	Entrance(RR_FIRE_TEMPLE_BIG_LAVA_ROOM_SOUTH_GORON, []{return (logic->IsAdult && logic->HasExplosives());}),
	Entrance(RR_FIRE_TEMPLE_FIRE_PILLAR_ROOM, []{return logic->SmallKeys(RR_FIRE_TEMPLE, 3);}),
});
areaTable[RR_FIRE_TEMPLE_BIG_LAVA_ROOM_NORTH_GORON] = Region("Fire Temple Big Lava Room North Goron", SCENE_FIRE_TEMPLE, false, {RA_FIRE_TEMPLE}, {}, {
	LOCATION(RC_FIRE_TEMPLE_BIG_LAVA_ROOM_LOWER_OPEN_DOOR_CHEST, true),
}, {
	Entrance(RR_FIRE_TEMPLE_BIG_LAVA_ROOM, []{return true;}),
});
areaTable[RR_FIRE_TEMPLE_BIG_LAVA_ROOM_NORTH_TILES] = Region("Fire Temple Big Lava Room North Tiles", SCENE_FIRE_TEMPLE, false, {RA_FIRE_TEMPLE}, {}, {
	LOCATION(RC_FIRE_TEMPLE_GS_SONG_OF_TIME_ROOM, ((logic->IsAdult && logic->CanAttack()) || logic->HookshotOrBoomerang())),
}, {
	Entrance(RR_FIRE_TEMPLE_BIG_LAVA_ROOM, []{return true;}),
});
areaTable[RR_FIRE_TEMPLE_BIG_LAVA_ROOM_SOUTH_GORON] = Region("Fire Temple Big Lava Room South Goron", SCENE_FIRE_TEMPLE, false, {RA_FIRE_TEMPLE}, {}, {
	LOCATION(RC_FIRE_TEMPLE_BIG_LAVA_ROOM_BLOCKED_DOOR_CHEST, true),
}, {
	Entrance(RR_FIRE_TEMPLE_BIG_LAVA_ROOM, []{return true;}),
});
areaTable[RR_FIRE_TEMPLE_FIRE_PILLAR_ROOM] = Region("Fire Temple Fire Pillar Room", SCENE_FIRE_TEMPLE, false, {RA_FIRE_TEMPLE}, {}, {
	LOCATION(RC_FIRE_TEMPLE_FIRE_PILLAR_LEFT_HEART, (logic->FireTimer() >= 56)),
	LOCATION(RC_FIRE_TEMPLE_FIRE_PILLAR_RIGHT_HEART, (logic->FireTimer() >= 56)),
	LOCATION(RC_FIRE_TEMPLE_FIRE_PILLAR_BACK_HEART, (logic->FireTimer() >= 56)),
}, {
	Entrance(RR_FIRE_TEMPLE_BIG_LAVA_ROOM, []{return logic->SmallKeys(RR_FIRE_TEMPLE, 3);}),
	Entrance(RR_FIRE_TEMPLE_SHORTCUT_ROOM, []{return ((logic->FireTimer() >= 56) && logic->SmallKeys(RR_FIRE_TEMPLE, 4));}),
});
areaTable[RR_FIRE_TEMPLE_SHORTCUT_ROOM] = Region("Fire Temple Shortcut Room", SCENE_FIRE_TEMPLE, false, {RA_FIRE_TEMPLE}, {}, {
	LOCATION(RC_FIRE_TEMPLE_BOULDER_MAZE_SHORTCUT_CHEST, Here(RR_FIRE_TEMPLE_SHORTCUT_ROOM, []{return true;})),
}, {
	Entrance(RR_FIRE_TEMPLE_FIRE_PILLAR_ROOM, []{return logic->SmallKeys(RR_FIRE_TEMPLE, 4);}),
	Entrance(RR_FIRE_TEMPLE_SHORTCUT_CLIMB, []{return Here(RR_FIRE_TEMPLE_SHORTCUT_ROOM, []{return true;});}),
	Entrance(RR_FIRE_TEMPLE_BOULDER_MAZE_LOWER, []{return (logic->IsAdult && ((logic->HasItem(RG_GORONS_BRACELET) || (bool)ctx->GetTrickOption(RT_FIRE_STRENGTH)) && (logic->HasExplosives() || (logic->CanUse(RG_FAIRY_BOW) || (logic->CanUse(RG_HOOKSHOT) || logic->CanUse(RG_FAIRY_SLINGSHOT))))));}),
});
areaTable[RR_FIRE_TEMPLE_SHORTCUT_CLIMB] = Region("Fire Temple Shortcut Climb", SCENE_FIRE_TEMPLE, false, {RA_FIRE_TEMPLE}, {}, {}, {
	Entrance(RR_FIRE_TEMPLE_SHORTCUT_ROOM, []{return true;}),
	Entrance(RR_FIRE_TEMPLE_BOULDER_MAZE_UPPER, []{return true;}),
});
areaTable[RR_FIRE_TEMPLE_BOULDER_MAZE_LOWER] = Region("Fire Temple Boulder Maze Lower", SCENE_FIRE_TEMPLE, false, {RA_FIRE_TEMPLE}, {}, {
	LOCATION(RC_FIRE_TEMPLE_BOULDER_MAZE_LOWER_CHEST, true),
	LOCATION(RC_FIRE_TEMPLE_GS_BOULDER_MAZE, (logic->HasExplosives() && (logic->IsAdult || logic->HookshotOrBoomerang()))),
}, {
	Entrance(RR_FIRE_TEMPLE_SHORTCUT_ROOM, []{return true;}),
	Entrance(RR_FIRE_TEMPLE_BOULDER_MAZE_LOWER_SIDE_ROOM, []{return true;}),
	Entrance(RR_FIRE_TEMPLE_EAST_CENTRAL_ROOM, []{return logic->SmallKeys(RR_FIRE_TEMPLE, 5, 7);}),
	Entrance(RR_FIRE_TEMPLE_BOULDER_MAZE_UPPER, []{return false;}),
});
areaTable[RR_FIRE_TEMPLE_BOULDER_MAZE_LOWER_SIDE_ROOM] = Region("Fire Temple Boulder Maze Lower Side Room", SCENE_FIRE_TEMPLE, false, {RA_FIRE_TEMPLE}, {}, {
	LOCATION(RC_FIRE_TEMPLE_BOULDER_MAZE_SIDE_ROOM_CHEST, true),
}, {
	Entrance(RR_FIRE_TEMPLE_BOULDER_MAZE_LOWER, []{return true;}),
});
areaTable[RR_FIRE_TEMPLE_EAST_CENTRAL_ROOM] = Region("Fire Temple East Central Room", SCENE_FIRE_TEMPLE, false, {RA_FIRE_TEMPLE}, {}, {
	LOCATION(RC_FIRE_TEMPLE_EAST_CENTRAL_LEFT_HEART, true),
	LOCATION(RC_FIRE_TEMPLE_EAST_CENTRAL_RIGHT_HEART, true),
	LOCATION(RC_FIRE_TEMPLE_EAST_CENTRAL_MIDDLE_HEART, true),
}, {
	Entrance(RR_FIRE_TEMPLE_BIG_LAVA_ROOM, []{return logic->TakeDamage();}),
	Entrance(RR_FIRE_TEMPLE_BOULDER_MAZE_LOWER, []{return logic->SmallKeys(RR_FIRE_TEMPLE, 5, 8);}),
	Entrance(RR_FIRE_TEMPLE_FIRE_WALL_CHASE, []{return logic->SmallKeys(RR_FIRE_TEMPLE, 6, 8);}),
	Entrance(RR_FIRE_TEMPLE_MAP_AREA, []{return (logic->CanUse(RG_FAIRY_SLINGSHOT) || logic->CanUse(RG_FAIRY_BOW));}),
});
areaTable[RR_FIRE_TEMPLE_FIRE_WALL_CHASE] = Region("Fire Temple Fire Wall Chase", SCENE_FIRE_TEMPLE, false, {RA_FIRE_TEMPLE}, {}, {
	LOCATION(RC_FIRE_TEMPLE_FIRE_WALL_EAST_HEART, ((logic->FireTimer() >= 24) && (logic->IsAdult || logic->CanUse(RG_BOOMERANG)))),
	LOCATION(RC_FIRE_TEMPLE_FIRE_WALL_WEST_HEART, ((logic->FireTimer() >= 24) && (logic->IsAdult || logic->CanUse(RG_BOOMERANG)))),
	LOCATION(RC_FIRE_TEMPLE_FIRE_WALL_EXIT_HEART, (logic->FireTimer() >= 24)),
}, {
	Entrance(RR_FIRE_TEMPLE_EAST_CENTRAL_ROOM, []{return ((logic->FireTimer() >= 24) && logic->SmallKeys(RR_FIRE_TEMPLE, 6, 8));}),
	Entrance(RR_FIRE_TEMPLE_MAP_AREA, []{return logic->IsAdult;}),
	Entrance(RR_FIRE_TEMPLE_BOULDER_MAZE_UPPER, []{return ((logic->FireTimer() >= 24) && logic->IsAdult);}),
	Entrance(RR_FIRE_TEMPLE_CORRIDOR, []{return ((logic->FireTimer() >= 24) && (logic->IsAdult && logic->SmallKeys(RR_FIRE_TEMPLE, 7)));}),
});
areaTable[RR_FIRE_TEMPLE_MAP_AREA] = Region("Fire Temple Map Region", SCENE_FIRE_TEMPLE, false, {RA_FIRE_TEMPLE}, {}, {
	LOCATION(RC_FIRE_TEMPLE_MAP_CHEST, true),
}, {
	Entrance(RR_FIRE_TEMPLE_EAST_CENTRAL_ROOM, []{return true;}),
});
areaTable[RR_FIRE_TEMPLE_BOULDER_MAZE_UPPER] = Region("Fire Temple Boulder Maze Upper", SCENE_FIRE_TEMPLE, false, {RA_FIRE_TEMPLE}, {}, {
	LOCATION(RC_FIRE_TEMPLE_BOULDER_MAZE_UPPER_CHEST, true),
}, {
	Entrance(RR_FIRE_TEMPLE_SHORTCUT_CLIMB, []{return logic->HasExplosives();}),
	Entrance(RR_FIRE_TEMPLE_BOULDER_MAZE_LOWER, []{return true;}),
	Entrance(RR_FIRE_TEMPLE_FIRE_WALL_CHASE, []{return true;}),
	Entrance(RR_FIRE_TEMPLE_SCARECROW_ROOM, []{return (logic->CanUse(RG_SCARECROW) || ((bool)ctx->GetTrickOption(RT_FIRE_SCARECROW) && (logic->IsAdult && logic->CanUse(RG_LONGSHOT))));}),
});
areaTable[RR_FIRE_TEMPLE_SCARECROW_ROOM] = Region("Fire Temple Scarecrow Room", SCENE_FIRE_TEMPLE, false, {RA_FIRE_TEMPLE}, {}, {
	LOCATION(RC_FIRE_TEMPLE_GS_SCARECROW_CLIMB, (logic->CanJumpslashExceptHammer() || (logic->CanUse(RG_FAIRY_SLINGSHOT) || (logic->CanUse(RG_BOOMERANG) || (logic->HasExplosives() || (logic->CanUse(RG_FAIRY_BOW) || (logic->CanUse(RG_HOOKSHOT) || logic->CanUse(RG_DINS_FIRE)))))))),
}, {
	Entrance(RR_FIRE_TEMPLE_BOULDER_MAZE_UPPER, []{return true;}),
	Entrance(RR_FIRE_TEMPLE_EAST_PEAK, []{return true;}),
});
areaTable[RR_FIRE_TEMPLE_EAST_PEAK] = Region("Fire Temple East Peak", SCENE_FIRE_TEMPLE, false, {RA_FIRE_TEMPLE}, {}, {
	LOCATION(RC_FIRE_TEMPLE_SCARECROW_CHEST, true),
	LOCATION(RC_FIRE_TEMPLE_GS_SCARECROW_TOP, logic->CanUseProjectile()),
}, {
	Entrance(RR_FIRE_TEMPLE_SCARECROW_ROOM, []{return true;}),
	Entrance(RR_FIRE_TEMPLE_EAST_CENTRAL_ROOM, []{return logic->TakeDamage();}),
});
areaTable[RR_FIRE_TEMPLE_CORRIDOR] = Region("Fire Temple Corridor", SCENE_FIRE_TEMPLE, false, {RA_FIRE_TEMPLE}, {}, {}, {
	Entrance(RR_FIRE_TEMPLE_FIRE_WALL_CHASE, []{return logic->SmallKeys(RR_FIRE_TEMPLE, 7);}),
	Entrance(RR_FIRE_TEMPLE_FIRE_MAZE_ROOM, []{return true;}),
});
areaTable[RR_FIRE_TEMPLE_FIRE_MAZE_ROOM] = Region("Fire Temple Fire Maze Room", SCENE_FIRE_TEMPLE, false, {RA_FIRE_TEMPLE}, {}, {
	LOCATION(RC_FIRE_TEMPLE_FLAME_MAZE_LEFT_POT_1, logic->CanBreakPots()),
	LOCATION(RC_FIRE_TEMPLE_FLAME_MAZE_LEFT_POT_2, logic->CanBreakPots()),
	LOCATION(RC_FIRE_TEMPLE_FLAME_MAZE_LEFT_POT_3, logic->CanBreakPots()),
	LOCATION(RC_FIRE_TEMPLE_FLAME_MAZE_LEFT_POT_4, logic->CanBreakPots()),
}, {
	Entrance(RR_FIRE_TEMPLE_CORRIDOR, []{return true;}),
	Entrance(RR_FIRE_TEMPLE_FIRE_MAZE_UPPER, []{return logic->CanUse(RG_HOVER_BOOTS);}),
	Entrance(RR_FIRE_TEMPLE_FIRE_MAZE_SIDE_ROOM, []{return true;}),
	Entrance(RR_FIRE_TEMPLE_WEST_CENTRAL_LOWER, []{return logic->SmallKeys(RR_FIRE_TEMPLE, 8);}),
	Entrance(RR_FIRE_TEMPLE_LATE_FIRE_MAZE, []{return ((bool)ctx->GetTrickOption(RT_FIRE_FLAME_MAZE) || false);}),
});
areaTable[RR_FIRE_TEMPLE_FIRE_MAZE_UPPER] = Region("Fire Temple Fire Maze Upper", SCENE_FIRE_TEMPLE, false, {RA_FIRE_TEMPLE}, {}, {}, {
	Entrance(RR_FIRE_TEMPLE_NEAR_BOSS_ROOM, []{return logic->CanUse(RG_MEGATON_HAMMER);}),
	Entrance(RR_FIRE_TEMPLE_FIRE_MAZE_ROOM, []{return true;}),
	Entrance(RR_FIRE_TEMPLE_WEST_CENTRAL_UPPER, []{return logic->CanUse(RG_MEGATON_HAMMER);}),
});
areaTable[RR_FIRE_TEMPLE_FIRE_MAZE_SIDE_ROOM] = Region("Fire Temple Fire Maze Side Room", SCENE_FIRE_TEMPLE, false, {RA_FIRE_TEMPLE}, {}, {
	LOCATION(RC_FIRE_TEMPLE_COMPASS_CHEST, true),
}, {
	Entrance(RR_FIRE_TEMPLE_FIRE_MAZE_ROOM, []{return true;}),
});
areaTable[RR_FIRE_TEMPLE_WEST_CENTRAL_LOWER] = Region("Fire Temple West Central Lower", SCENE_FIRE_TEMPLE, false, {RA_FIRE_TEMPLE}, {}, {
	LOCATION(RC_FIRE_TEMPLE_HIGHEST_GORON_CHEST, Here(RR_FIRE_TEMPLE_WEST_CENTRAL_LOWER, []{return ((logic->CanUse(RG_SONG_OF_TIME) || (bool)ctx->GetTrickOption(RT_RUSTED_SWITCHES)) && logic->CanUse(RG_MEGATON_HAMMER));})),
}, {
	Entrance(RR_FIRE_TEMPLE_FIRE_MAZE_ROOM, []{return logic->SmallKeys(RR_FIRE_TEMPLE, 8);}),
	Entrance(RR_FIRE_TEMPLE_WEST_CENTRAL_UPPER, []{return (logic->IsAdult && logic->CanUse(RG_SONG_OF_TIME));}),
	Entrance(RR_FIRE_TEMPLE_LATE_FIRE_MAZE, []{return true;}),
});
areaTable[RR_FIRE_TEMPLE_WEST_CENTRAL_UPPER] = Region("Fire Temple West Central Upper", SCENE_FIRE_TEMPLE, false, {RA_FIRE_TEMPLE}, {}, {}, {
	Entrance(RR_FIRE_TEMPLE_BOSS_ENTRYWAY, []{return false;}),
	Entrance(RR_FIRE_TEMPLE_FIRE_MAZE_UPPER, []{return true;}),
	Entrance(RR_FIRE_TEMPLE_WEST_CENTRAL_LOWER, []{return true;}),
});
areaTable[RR_FIRE_TEMPLE_LATE_FIRE_MAZE] = Region("Fire Temple Late Fire Maze", SCENE_FIRE_TEMPLE, false, {RA_FIRE_TEMPLE}, {}, {
	LOCATION(RC_FIRE_TEMPLE_FLAME_MAZE_RIGHT_POT_1, logic->CanBreakPots()),
	LOCATION(RC_FIRE_TEMPLE_FLAME_MAZE_RIGHT_POT_2, logic->CanBreakPots()),
	LOCATION(RC_FIRE_TEMPLE_FLAME_MAZE_RIGHT_POT_3, logic->CanBreakPots()),
	LOCATION(RC_FIRE_TEMPLE_FLAME_MAZE_RIGHT_POT_4, logic->CanBreakPots()),
}, {
	Entrance(RR_FIRE_TEMPLE_FIRE_MAZE_ROOM, []{return false;}),
	Entrance(RR_FIRE_TEMPLE_WEST_CENTRAL_LOWER, []{return true;}),
	Entrance(RR_FIRE_TEMPLE_UPPER_FLARE_DANCER, []{return logic->HasExplosives();}),
});
areaTable[RR_FIRE_TEMPLE_UPPER_FLARE_DANCER] = Region("Fire Temple Upper Flare Dancer", SCENE_FIRE_TEMPLE, false, {RA_FIRE_TEMPLE}, {}, {}, {
	Entrance(RR_FIRE_TEMPLE_LATE_FIRE_MAZE, []{return Here(RR_FIRE_TEMPLE_UPPER_FLARE_DANCER, []{return logic->CanKillEnemy(RE_FLARE_DANCER);});}),
	Entrance(RR_FIRE_TEMPLE_WEST_CLIMB, []{return Here(RR_FIRE_TEMPLE_UPPER_FLARE_DANCER, []{return logic->CanKillEnemy(RE_FLARE_DANCER);});}),
});
areaTable[RR_FIRE_TEMPLE_WEST_CLIMB] = Region("Fire Temple West Climb", SCENE_FIRE_TEMPLE, false, {RA_FIRE_TEMPLE}, {}, {}, {
	Entrance(RR_FIRE_TEMPLE_UPPER_FLARE_DANCER, []{return true;}),
	Entrance(RR_FIRE_TEMPLE_WEST_PEAK, []{return logic->CanUseProjectile();}),
});
areaTable[RR_FIRE_TEMPLE_WEST_PEAK] = Region("Fire Temple West Peak", SCENE_FIRE_TEMPLE, false, {RA_FIRE_TEMPLE}, {}, {
	LOCATION(RC_FIRE_TEMPLE_MEGATON_HAMMER_CHEST, true),
}, {
	Entrance(RR_FIRE_TEMPLE_WEST_CENTRAL_UPPER, []{return logic->TakeDamage();}),
	Entrance(RR_FIRE_TEMPLE_WEST_CLIMB, []{return true;}),
	Entrance(RR_FIRE_TEMPLE_HAMMER_RETURN_PATH, []{return logic->CanUse(RG_MEGATON_HAMMER);}),
});
areaTable[RR_FIRE_TEMPLE_HAMMER_RETURN_PATH] = Region("Fire Temple Hammer Return Path", SCENE_FIRE_TEMPLE, false, {RA_FIRE_TEMPLE}, {}, {
	LOCATION(RC_FIRE_TEMPLE_AFTER_HAMMER_SMALL_CRATE_1, logic->CanBreakSmallCrates()),
	LOCATION(RC_FIRE_TEMPLE_AFTER_HAMMER_SMALL_CRATE_2, logic->CanBreakSmallCrates()),
}, {
	Entrance(RR_FIRE_TEMPLE_ABOVE_FIRE_MAZE, []{return logic->CanUse(RG_MEGATON_HAMMER);}),
});
areaTable[RR_FIRE_TEMPLE_ABOVE_FIRE_MAZE] = Region("Fire Temple Above Fire Maze", SCENE_FIRE_TEMPLE, false, {RA_FIRE_TEMPLE}, {}, {}, {
	Entrance(RR_FIRE_TEMPLE_HAMMER_RETURN_PATH, []{return true;}),
	Entrance(RR_FIRE_TEMPLE_FIRE_MAZE_UPPER, []{return logic->CanUse(RG_MEGATON_HAMMER);}),
});
areaTable[RR_FIRE_TEMPLE_MQ_FIRST_ROOM_LOWER] = Region("Fire Temple MQ First Room Lower", SCENE_FIRE_TEMPLE, false, {RA_FIRE_TEMPLE}, {}, {
	LOCATION(RC_FIRE_TEMPLE_MQ_ENTRANCE_POT_1, logic->CanBreakPots()),
	LOCATION(RC_FIRE_TEMPLE_MQ_ENTRANCE_POT_2, logic->CanBreakPots()),
}, {
	Entrance(RR_FIRE_TEMPLE_ENTRYWAY, []{return true;}),
	Entrance(RR_FIRE_TEMPLE_MQ_MAP_ROOM_SOUTH, []{return true;}),
	Entrance(RR_FIRE_TEMPLE_MQ_FIRST_ROOM_UPPER, []{return (logic->IsAdult || logic->CanUse(RG_HOOKSHOT));}),
	Entrance(RR_FIRE_TEMPLE_MQ_STALFOS_ROOM, []{return logic->SmallKeys(RR_FIRE_TEMPLE, 5);}),
});
areaTable[RR_FIRE_TEMPLE_MQ_FIRST_ROOM_UPPER] = Region("Fire Temple MQ First Room Upper", SCENE_FIRE_TEMPLE, false, {RA_FIRE_TEMPLE}, {}, {}, {
	Entrance(RR_FIRE_TEMPLE_MQ_FIRST_ROOM_LOWER, []{return true;}),
	Entrance(RR_FIRE_TEMPLE_MQ_NEAR_BOSS_ROOM, []{return logic->HasFireSource();}),
	Entrance(RR_FIRE_TEMPLE_MQ_BIG_LAVA_ROOM, []{return Here(RR_FIRE_TEMPLE_MQ_FIRST_ROOM_UPPER, []{return logic->CanUse(RG_MEGATON_HAMMER);});}),
});
areaTable[RR_FIRE_TEMPLE_MQ_MAP_ROOM_SOUTH] = Region("Fire Temple MQ Map Room South", SCENE_FIRE_TEMPLE, false, {RA_FIRE_TEMPLE}, {}, {
	LOCATION(RC_FIRE_TEMPLE_MQ_MAP_ROOM_SIDE_CHEST, logic->CanKillEnemy(RE_LIKE_LIKE)),
}, {
	Entrance(RR_FIRE_TEMPLE_MQ_FIRST_ROOM_LOWER, []{return Here(RR_FIRE_TEMPLE_MQ_MAP_ROOM_SOUTH, []{return logic->CanKillEnemy(RE_LIKE_LIKE);});}),
	Entrance(RR_FIRE_TEMPLE_MQ_MAP_ROOM_CAGE, []{return logic->OpenedLowestGoronCage;}),
});
areaTable[RR_FIRE_TEMPLE_MQ_STALFOS_ROOM] = Region("Fire Temple MQ Stalfos Room", SCENE_FIRE_TEMPLE, false, {RA_FIRE_TEMPLE}, {}, {
	LOCATION(RC_FIRE_TEMPLE_MQ_LOOP_STALFOS_SUN_FAIRY, logic->CanUse(RG_SUNS_SONG)),
}, {
	Entrance(RR_FIRE_TEMPLE_MQ_FIRST_ROOM_LOWER, []{return true;}),
	Entrance(RR_FIRE_TEMPLE_MQ_IRON_KNUCKLE_ROOM, []{return Here(RR_FIRE_TEMPLE_MQ_STALFOS_ROOM, []{return logic->CanKillEnemy(RE_STALFOS, ED_CLOSE, true, 2);});}),
});
areaTable[RR_FIRE_TEMPLE_MQ_IRON_KNUCKLE_ROOM] = Region("Fire Temple MQ Iron Knuckle Room", SCENE_FIRE_TEMPLE, false, {RA_FIRE_TEMPLE}, {
	EventAccess(&logic->FairyPot, []{return true;}),
}, {
	LOCATION(RC_FIRE_TEMPLE_MQ_LOOP_KNUCKLE_SUN_FAIRY, logic->CanUse(RG_SUNS_SONG)),
	LOCATION(RC_FIRE_TEMPLE_MQ_BEFORE_MINI_BOSS_POT_1, logic->CanBreakPots()),
	LOCATION(RC_FIRE_TEMPLE_MQ_BEFORE_MINI_BOSS_POT_2, logic->CanBreakPots()),
	LOCATION(RC_FIRE_TEMPLE_MQ_BEFORE_MINI_BOSS_POT_3, logic->CanBreakPots()),
	LOCATION(RC_FIRE_TEMPLE_MQ_BEFORE_MINI_BOSS_POT_4, logic->CanBreakPots()),
	LOCATION(RC_FIRE_TEMPLE_MQ_BEFORE_MINI_BOSS_POT_5, logic->CanBreakPots()),
	LOCATION(RC_FIRE_TEMPLE_MQ_BEFORE_MINI_BOSS_POT_6, logic->CanBreakPots()),
	LOCATION(RC_FIRE_TEMPLE_MQ_BEFORE_MINI_BOSS_POT_7, logic->CanBreakPots()),
	LOCATION(RC_FIRE_TEMPLE_MQ_BEFORE_MINI_BOSS_POT_8, logic->CanBreakPots()),
}, {
	Entrance(RR_FIRE_TEMPLE_MQ_STALFOS_ROOM, []{return true;}),
	Entrance(RR_FIRE_TEMPLE_MQ_LOWER_FLARE_DANCER, []{return Here(RR_FIRE_TEMPLE_MQ_IRON_KNUCKLE_ROOM, []{return logic->CanKillEnemy(RE_IRON_KNUCKLE);});}),
});
areaTable[RR_FIRE_TEMPLE_MQ_LOWER_FLARE_DANCER] = Region("Fire Temple MQ Lower Flare Dancer", SCENE_FIRE_TEMPLE, false, {RA_FIRE_TEMPLE}, {}, {
	LOCATION(RC_FIRE_TEMPLE_MQ_MEGATON_HAMMER_CHEST, ((logic->IsAdult || logic->CanUse(RG_HOOKSHOT)) && Here(RR_FIRE_TEMPLE_MQ_LOWER_FLARE_DANCER, []{return logic->CanKillEnemy(RE_FLARE_DANCER);}))),
}, {
	Entrance(RR_FIRE_TEMPLE_MQ_IRON_KNUCKLE_ROOM, []{return true;}),
	Entrance(RR_FIRE_TEMPLE_MQ_MAP_ROOM_NORTH, []{return Here(RR_FIRE_TEMPLE_MQ_LOWER_FLARE_DANCER, []{return logic->CanKillEnemy(RE_FLARE_DANCER);});}),
});
areaTable[RR_FIRE_TEMPLE_MQ_MAP_ROOM_NORTH] = Region("Fire Temple MQ Map Room North", SCENE_FIRE_TEMPLE, false, {RA_FIRE_TEMPLE}, {
	EventAccess(&logic->OpenedLowestGoronCage, []{return logic->CanUse(RG_MEGATON_HAMMER);}),
}, {}, {
	Entrance(RR_FIRE_TEMPLE_MQ_LOWER_FLARE_DANCER, []{return true;}),
	Entrance(RR_FIRE_TEMPLE_MQ_MAP_ROOM_CAGE, []{return logic->OpenedLowestGoronCage;}),
});
areaTable[RR_FIRE_TEMPLE_MQ_MAP_ROOM_CAGE] = Region("Fire Temple MQ Map Room Cage", SCENE_FIRE_TEMPLE, false, {RA_FIRE_TEMPLE}, {}, {
	LOCATION(RC_FIRE_TEMPLE_MQ_MAP_CHEST, true),
}, {
	Entrance(RR_FIRE_TEMPLE_MQ_MAP_ROOM_NORTH, []{return logic->OpenedLowestGoronCage;}),
	Entrance(RR_FIRE_TEMPLE_MQ_MAP_ROOM_SOUTH, []{return logic->OpenedLowestGoronCage;}),
});
areaTable[RR_FIRE_TEMPLE_MQ_NEAR_BOSS_ROOM] = Region("Fire Temple MQ Near Boss Room", SCENE_FIRE_TEMPLE, false, {RA_FIRE_TEMPLE}, {}, {
	LOCATION(RC_FIRE_TEMPLE_MQ_NEAR_BOSS_CHEST, ((logic->FireTimer() > 25) && ((bool)ctx->GetTrickOption(RT_FIRE_MQ_NEAR_BOSS) && (logic->CanUse(RG_FIRE_ARROWS) || (logic->IsAdult && (logic->CanUse(RG_DINS_FIRE) && logic->CanUse(RG_FAIRY_BOW))))))),
	LOCATION(RC_FIRE_TEMPLE_MQ_OUTSIDE_BOSS_CRATE_1, ((logic->FireTimer() > 25) && logic->CanBreakCrates())),
	LOCATION(RC_FIRE_TEMPLE_MQ_OUTSIDE_BOSS_CRATE_2, ((logic->FireTimer() > 25) && logic->CanBreakCrates())),
}, {
	Entrance(RR_FIRE_TEMPLE_MQ_FIRST_ROOM_UPPER, []{return true;}),
	Entrance(RR_FIRE_TEMPLE_MQ_NEAR_BOSS_ROOM_NORTH, []{return ((logic->FireTimer() > 32) && (logic->CanUse(RG_HOOKSHOT) || (logic->IsAdult && logic->CanUse(RG_HOVER_BOOTS))));}),
	Entrance(RR_FIRE_TEMPLE_BOSS_ENTRYWAY, []{return ((logic->FireTimer() >= 15) && ((logic->IsAdult && ((bool)ctx->GetTrickOption(RT_FIRE_BOSS_DOOR_JUMP) || logic->CanUse(RG_HOVER_BOOTS))) || ((logic->IsAdult && logic->HitFireTemplePlatform) || (logic->HitFireTemplePlatform && logic->CanUse(RG_HOVER_BOOTS)))));}),
});
areaTable[RR_FIRE_TEMPLE_MQ_NEAR_BOSS_ROOM_NORTH] = Region("Fire Temple MQ Near Boss Room North", SCENE_FIRE_TEMPLE, false, {RA_FIRE_TEMPLE}, {}, {
	LOCATION(RC_FIRE_TEMPLE_MQ_NEAR_BOSS_CHEST, (logic->CanUse(RG_FIRE_ARROWS) || (logic->CanUse(RG_DINS_FIRE) && (logic->CanUse(RG_FAIRY_BOW) || (logic->CanUse(RG_LONGSHOT) || (logic->IsAdult && (logic->CanUse(RG_HOVER_BOOTS) || (logic->CanUse(RG_GORON_TUNIC) || ((logic->EffectiveHealth() >= 2) || (logic->CanUse(RG_NAYRUS_LOVE) && logic->CanUse(RG_STICKS))))))))))),
	LOCATION(RC_FIRE_TEMPLE_MQ_OUTSIDE_BOSS_POT_1, logic->CanBreakPots()),
	LOCATION(RC_FIRE_TEMPLE_MQ_OUTSIDE_BOSS_POT_2, logic->CanBreakPots()),
	LOCATION(RC_FIRE_TEMPLE_MQ_OUTSIDE_BOSS_CRATE_1, ((logic->FireTimer() > 25) && logic->CanBreakCrates())),
	LOCATION(RC_FIRE_TEMPLE_MQ_OUTSIDE_BOSS_CRATE_2, ((logic->FireTimer() > 25) && logic->CanBreakCrates())),
	LOCATION(RC_FIRE_TEMPLE_MQ_OUTSIDE_BOSS_CRATE_3, logic->CanBreakCrates()),
	LOCATION(RC_FIRE_TEMPLE_MQ_OUTSIDE_BOSS_CRATE_4, logic->CanBreakCrates()),
	LOCATION(RC_FIRE_TEMPLE_MQ_OUTSIDE_BOSS_CRATE_5, logic->CanBreakCrates()),
	LOCATION(RC_FIRE_TEMPLE_MQ_OUTSIDE_BOSS_CRATE_6, logic->CanBreakCrates()),
}, {
	Entrance(RR_FIRE_TEMPLE_NEAR_BOSS_ROOM, []{return true;}),
});
areaTable[RR_FIRE_TEMPLE_MQ_BIG_LAVA_ROOM] = Region("Fire Temple MQ Big Lava Room", SCENE_FIRE_TEMPLE, false, {RA_FIRE_TEMPLE}, {}, {
	LOCATION(RC_FIRE_TEMPLE_MQ_BIG_LAVA_ROOM_BLOCKED_DOOR_CHEST, ((logic->FireTimer() >= 40) && (logic->HasFireSource() && (logic->HasExplosives() && (logic->CanUse(RG_HOOKSHOT) || (logic->IsAdult && (bool)ctx->GetTrickOption(RT_FIRE_MQ_BLOCKED_CHEST))))))),
	LOCATION(RC_FIRE_TEMPLE_MQ_GS_BIG_LAVA_ROOM_OPEN_DOOR, ((logic->FireTimer() >= 20) && logic->CanUse(RG_MEGATON_HAMMER))),
	LOCATION(RC_FIRE_TEMPLE_MQ_LAVA_ROOM_NORTH_POT, logic->CanBreakPots()),
	LOCATION(RC_FIRE_TEMPLE_MQ_LAVA_ROOM_HIGH_POT, logic->CanBreakPots()),
	LOCATION(RC_FIRE_TEMPLE_MQ_LAVA_ROOM_SOUTH_POT, ((logic->FireTimer() >= 40) && (logic->CanUse(RG_HOOKSHOT) || ((bool)ctx->GetTrickOption(RT_FIRE_MQ_BLOCKED_CHEST) && ((logic->IsAdult && logic->CanBreakPots()) || logic->CanUse(RG_BOOMERANG)))))),
}, {
	Entrance(RR_FIRE_TEMPLE_MQ_FIRST_ROOM_UPPER, []{return (logic->FireTimer() >= 20);}),
	Entrance(RR_FIRE_TEMPLE_MQ_ELEVATOR_ROOM, []{return (logic->CanUse(RG_GORON_TUNIC) && logic->SmallKeys(RR_FIRE_TEMPLE, 2));}),
	Entrance(RR_FIRE_TEMPLE_MQ_TORCH_FIREWALL_ROOM, []{return (logic->HasFireSource() && (((logic->CanUse(RG_FAIRY_BOW) && (logic->FireTimer() >= 25)) || ((bool)ctx->GetTrickOption(RT_FIRE_MQ_BK_CHEST) && (logic->FireTimer() >= 50))) && (logic->CanUse(RG_HOOKSHOT) || (logic->IsAdult && (bool)ctx->GetTrickOption(RT_FIRE_SOT)))));}),
});
areaTable[RR_FIRE_TEMPLE_MQ_TORCH_FIREWALL_ROOM] = Region("Fire Temple MQ Torch Firewall Room", SCENE_FIRE_TEMPLE, false, {RA_FIRE_TEMPLE}, {
	EventAccess(&logic->FairyPot, []{return logic->CanUse(RG_HOOKSHOT);}),
}, {
	LOCATION(RC_FIRE_TEMPLE_MQ_BOSS_KEY_CHEST, logic->CanUse(RG_HOOKSHOT)),
	LOCATION(RC_FIRE_TEMPLE_MQ_LAVA_TORCH_POT_1, logic->HookshotOrBoomerang()),
	LOCATION(RC_FIRE_TEMPLE_MQ_LAVA_TORCH_POT_2, logic->HookshotOrBoomerang()),
}, {
	Entrance(RR_FIRE_TEMPLE_MQ_BIG_LAVA_ROOM, []{return true;}),
});
areaTable[RR_FIRE_TEMPLE_MQ_ELEVATOR_ROOM] = Region("Fire Temple MQ Elevator Room", SCENE_FIRE_TEMPLE, false, {RA_FIRE_TEMPLE}, {}, {
	LOCATION(RC_FIRE_TEMPLE_MQ_FIRE_PILLAR_LEFT_HEART, true),
	LOCATION(RC_FIRE_TEMPLE_MQ_FIRE_PILLAR_RIGHT_HEART, true),
	LOCATION(RC_FIRE_TEMPLE_MQ_FIRE_PILLAR_LOWER_HEART, true),
}, {
	Entrance(RR_FIRE_TEMPLE_MQ_BIG_LAVA_ROOM, []{return true;}),
	Entrance(RR_FIRE_TEMPLE_MQ_BIG_TORCH_ROOM, []{return true;}),
});
areaTable[RR_FIRE_TEMPLE_MQ_BIG_TORCH_ROOM] = Region("Fire Temple MQ Big Torch Room", SCENE_FIRE_TEMPLE, false, {RA_FIRE_TEMPLE}, {}, {}, {
	Entrance(RR_FIRE_TEMPLE_MQ_LOWER_MAZE, []{return ((logic->HasFireSource() && logic->CanUse(RG_HOOKSHOT)) || ((bool)ctx->GetTrickOption(RT_FIRE_MQ_CLIMB) && logic->CanUse(RG_HOVER_BOOTS)));}),
	Entrance(RR_FIRE_TEMPLE_MQ_ELEVATOR_ROOM, []{return logic->CanUse(RG_GORON_TUNIC);}),
	Entrance(RR_FIRE_TEMPLE_MQ_MAZE_SHORTCUT_CAGE, []{return logic->OpenedUpperFireShortcut;}),
});
areaTable[RR_FIRE_TEMPLE_MQ_LOWER_MAZE] = Region("Fire Temple MQ Lower Maze", SCENE_FIRE_TEMPLE, false, {RA_FIRE_TEMPLE}, {}, {
	LOCATION(RC_FIRE_TEMPLE_MQ_LIZALFOS_MAZE_SIDE_ROOM_CHEST, (logic->HasExplosives() && (bool)ctx->GetTrickOption(RT_FIRE_MQ_MAZE_SIDE_ROOM))),
}, {
	Entrance(RR_FIRE_TEMPLE_MQ_BIG_TORCH_ROOM, []{return true;}),
	Entrance(RR_FIRE_TEMPLE_MQ_LOWER_MAZE_CRATE_CAGE, []{return Here(RR_FIRE_TEMPLE_MQ_LOWER_MAZE, []{return logic->CanJumpslash();});}),
	Entrance(RR_FIRE_TEMPLE_MQ_UPPER_MAZE, []{return (logic->HasExplosives() && (logic->CanUse(RG_MEGATON_HAMMER) && logic->CanUse(RG_HOOKSHOT)));}),
});
areaTable[RR_FIRE_TEMPLE_MQ_LOWER_MAZE_CRATE_CAGE] = Region("Fire Temple MQ Lower Maze Crate Cage", SCENE_FIRE_TEMPLE, false, {RA_FIRE_TEMPLE}, {}, {
	LOCATION(RC_FIRE_TEMPLE_MQ_LIZALFOS_MAZE_LOWER_CHEST, true),
	LOCATION(RC_FIRE_TEMPLE_MQ_LIZALFOS_MAZE_LOWER_CRATE_1, logic->CanBreakCrates()),
	LOCATION(RC_FIRE_TEMPLE_MQ_LIZALFOS_MAZE_LOWER_CRATE_2, logic->CanBreakCrates()),
	LOCATION(RC_FIRE_TEMPLE_MQ_LIZALFOS_MAZE_LOWER_CRATE_3, logic->CanBreakCrates()),
}, {
	Entrance(RR_FIRE_TEMPLE_MQ_LOWER_MAZE, []{return true;}),
	Entrance(RR_FIRE_TEMPLE_MQ_UPPER_MAZE, []{return (logic->IsAdult && (((bool)ctx->GetTrickOption(RT_FIRE_MQ_MAZE_HOVERS) && logic->CanUse(RG_HOVER_BOOTS)) || (bool)ctx->GetTrickOption(RT_FIRE_MQ_MAZE_JUMP)));}),
});
areaTable[RR_FIRE_TEMPLE_MQ_UPPER_MAZE] = Region("Fire Temple MQ Upper Maze", SCENE_FIRE_TEMPLE, false, {RA_FIRE_TEMPLE}, {}, {}, {
	Entrance(RR_FIRE_TEMPLE_MQ_LOWER_MAZE, []{return true;}),
	Entrance(RR_FIRE_TEMPLE_MQ_UPPER_MAZE_BOX_CAGE, []{return Here(RR_FIRE_TEMPLE_MQ_UPPER_MAZE, []{return (logic->CanJumpslash() || logic->HasExplosives());});}),
	Entrance(RR_FIRE_TEMPLE_MQ_MAZE_SHORTCUT, []{return logic->HasExplosives();}),
	Entrance(RR_FIRE_TEMPLE_MQ_BURNING_BLOCK_CLIMB, []{return (logic->HasExplosives() && (logic->CanUse(RG_MEGATON_HAMMER) && (logic->CanUse(RG_LONGSHOT) || (logic->CanUse(RG_HOOKSHOT) && logic->CanUse(RG_SONG_OF_TIME)))));}),
	Entrance(RR_FIRE_TEMPLE_MQ_HIGH_TORCH_ROOM, []{return (logic->SmallKeys(RR_FIRE_TEMPLE, 3) && logic->CanUse(RG_GORON_TUNIC));}),
});
areaTable[RR_FIRE_TEMPLE_MQ_UPPER_MAZE_BOX_CAGE] = Region("Fire Temple MQ Upper Maze Box Cage", SCENE_FIRE_TEMPLE, false, {RA_FIRE_TEMPLE}, {}, {
	LOCATION(RC_FIRE_TEMPLE_MQ_LIZALFOS_MAZE_UPPER_CHEST, true),
	LOCATION(RC_FIRE_TEMPLE_MQ_LIZALFOS_MAZE_UPPER_CRATE_1, logic->CanBreakCrates()),
	LOCATION(RC_FIRE_TEMPLE_MQ_LIZALFOS_MAZE_UPPER_CRATE_2, logic->CanBreakCrates()),
	LOCATION(RC_FIRE_TEMPLE_MQ_LIZALFOS_MAZE_UPPER_CRATE_3, logic->CanBreakCrates()),
	LOCATION(RC_FIRE_TEMPLE_MQ_LIZALFOS_MAZE_UPPER_SMALL_CRATE_1, logic->CanBreakSmallCrates()),
	LOCATION(RC_FIRE_TEMPLE_MQ_LIZALFOS_MAZE_UPPER_SMALL_CRATE_2, logic->CanBreakSmallCrates()),
	LOCATION(RC_FIRE_TEMPLE_MQ_LIZALFOS_MAZE_SIDE_ROOM_CHEST, logic->HasExplosives()),
}, {
	Entrance(RR_FIRE_TEMPLE_MQ_UPPER_MAZE, []{return true;}),
});
areaTable[RR_FIRE_TEMPLE_MQ_MAZE_SHORTCUT] = Region("Fire Temple MQ Maze Shortcut", SCENE_FIRE_TEMPLE, false, {RA_FIRE_TEMPLE}, {
	EventAccess(&logic->OpenedUpperFireShortcut, []{return logic->CanUse(RG_MEGATON_HAMMER);}),
}, {}, {
	Entrance(RR_FIRE_TEMPLE_MQ_UPPER_MAZE, []{return true;}),
	Entrance(RR_FIRE_TEMPLE_MQ_MAZE_SHORTCUT_CAGE, []{return logic->OpenedUpperFireShortcut;}),
});
areaTable[RR_FIRE_TEMPLE_MQ_MAZE_SHORTCUT_CAGE] = Region("Fire Temple MQ Maze Shortcut Cage", SCENE_FIRE_TEMPLE, false, {RA_FIRE_TEMPLE}, {}, {
	LOCATION(RC_FIRE_TEMPLE_MQ_COMPASS_CHEST, logic->OpenedUpperFireShortcut),
	LOCATION(RC_FIRE_TEMPLE_MQ_SHORTCUT_CRATE_1, (logic->OpenedUpperFireShortcut && logic->CanBreakCrates())),
	LOCATION(RC_FIRE_TEMPLE_MQ_SHORTCUT_CRATE_2, (logic->OpenedUpperFireShortcut && logic->CanBreakCrates())),
	LOCATION(RC_FIRE_TEMPLE_MQ_SHORTCUT_CRATE_3, (logic->OpenedUpperFireShortcut && logic->CanBreakCrates())),
	LOCATION(RC_FIRE_TEMPLE_MQ_SHORTCUT_CRATE_4, (logic->OpenedUpperFireShortcut && logic->CanBreakCrates())),
	LOCATION(RC_FIRE_TEMPLE_MQ_SHORTCUT_CRATE_5, (logic->OpenedUpperFireShortcut && logic->CanBreakCrates())),
	LOCATION(RC_FIRE_TEMPLE_MQ_SHORTCUT_CRATE_6, (logic->OpenedUpperFireShortcut && logic->CanBreakCrates())),
}, {
	Entrance(RR_FIRE_TEMPLE_MQ_MAZE_SHORTCUT, []{return logic->OpenedUpperFireShortcut;}),
	Entrance(RR_FIRE_TEMPLE_MQ_BIG_TORCH_ROOM, []{return logic->OpenedUpperFireShortcut;}),
});
areaTable[RR_FIRE_TEMPLE_MQ_BURNING_BLOCK_CLIMB] = Region("Fire Temple MQ Burning Block Climb", SCENE_FIRE_TEMPLE, false, {RA_FIRE_TEMPLE}, {}, {
	LOCATION(RC_FIRE_TEMPLE_MQ_GS_SKULL_ON_FIRE, (logic->CanUse(RG_HOOKSHOT) && logic->CanUse(RG_MEGATON_HAMMER))),
}, {
	Entrance(RR_FIRE_TEMPLE_MQ_UPPER_MAZE, []{return true;}),
	Entrance(RR_FIRE_TEMPLE_MQ_NARROW_PATH_ROOM, []{return logic->TakeDamage();}),
});
areaTable[RR_FIRE_TEMPLE_MQ_NARROW_PATH_ROOM] = Region("Fire Temple MQ Narrow Path Room", SCENE_FIRE_TEMPLE, false, {RA_FIRE_TEMPLE}, {
	EventAccess(&logic->FairyPot, []{return true;}),
}, {
	LOCATION(RC_FIRE_TEMPLE_MQ_ABOVE_LAVA_POT_1, logic->CanBreakPots()),
	LOCATION(RC_FIRE_TEMPLE_MQ_ABOVE_LAVA_POT_2, logic->CanBreakPots()),
	LOCATION(RC_FIRE_TEMPLE_MQ_ABOVE_LAVA_POT_3, logic->CanBreakPots()),
}, {
	Entrance(RR_FIRE_TEMPLE_MQ_LOWER_MAZE, []{return true;}),
	Entrance(RR_FIRE_TEMPLE_MQ_BIG_LAVA_ROOM, []{return logic->TakeDamage();}),
});
areaTable[RR_FIRE_TEMPLE_MQ_HIGH_TORCH_ROOM] = Region("Fire Temple MQ High Torch Room", SCENE_FIRE_TEMPLE, false, {RA_FIRE_TEMPLE}, {}, {
	LOCATION(RC_FIRE_TEMPLE_MQ_FLAME_WALL_POT_1, logic->CanBreakPots()),
	LOCATION(RC_FIRE_TEMPLE_MQ_FLAME_WALL_POT_2, logic->CanBreakPots()),
	LOCATION(RC_FIRE_TEMPLE_MQ_LAVA_TORCH_CRATE_1, logic->CanBreakCrates()),
	LOCATION(RC_FIRE_TEMPLE_MQ_LAVA_TORCH_CRATE_2, logic->CanBreakCrates()),
	LOCATION(RC_FIRE_TEMPLE_MQ_LAVA_TORCH_CRATE_3, logic->CanBreakCrates()),
	LOCATION(RC_FIRE_TEMPLE_MQ_LAVA_TORCH_CRATE_4, logic->CanBreakCrates()),
	LOCATION(RC_FIRE_TEMPLE_MQ_LAVA_TORCH_CRATE_5, logic->CanBreakCrates()),
	LOCATION(RC_FIRE_TEMPLE_MQ_LAVA_TORCH_SMALL_CRATE_1, logic->CanBreakSmallCrates()),
	LOCATION(RC_FIRE_TEMPLE_MQ_LAVA_TORCH_SMALL_CRATE_2, logic->CanBreakSmallCrates()),
	LOCATION(RC_FIRE_TEMPLE_MQ_LAVA_TORCH_SMALL_CRATE_3, logic->CanBreakSmallCrates()),
	LOCATION(RC_FIRE_TEMPLE_MQ_LAVA_TORCH_SMALL_CRATE_4, logic->CanBreakSmallCrates()),
	LOCATION(RC_FIRE_TEMPLE_MQ_LAVA_TORCH_SMALL_CRATE_5, logic->CanBreakSmallCrates()),
}, {
	Entrance(RR_FIRE_TEMPLE_MQ_UPPER_MAZE, []{return logic->SmallKeys(RR_FIRE_TEMPLE, 3);}),
	Entrance(RR_FIRE_TEMPLE_MQ_NARROW_PATH_ROOM, []{return true;}),
	Entrance(RR_FIRE_TEMPLE_MQ_SOUTH_FIRE_MAZE, []{return (Here(RR_FIRE_TEMPLE_MQ_HIGH_TORCH_ROOM, []{return (logic->CanUse(RG_FIRE_ARROWS) || (logic->CanUse(RG_FAIRY_BOW) && logic->CanUse(RG_HOOKSHOT)));}) && (logic->IsAdult || logic->CanUse(RG_HOOKSHOT)));}),
});
areaTable[RR_FIRE_TEMPLE_MQ_SOUTH_FIRE_MAZE] = Region("Fire Temple MQ South Fire Maze", SCENE_FIRE_TEMPLE, false, {RA_FIRE_TEMPLE}, {}, {
	LOCATION(RC_FIRE_TEMPLE_MQ_GS_FIRE_WALL_MAZE_CENTER, logic->HasExplosives()),
	LOCATION(RC_FIRE_TEMPLE_MQ_SOUTH_FIRE_MAZE_WEST_POT, logic->CanBreakPots()),
	LOCATION(RC_FIRE_TEMPLE_MQ_SOUTH_FIRE_MAZE_EAST_POT, logic->CanBreakPots()),
}, {
	Entrance(RR_FIRE_TEMPLE_MQ_NEAR_BOSS_ROOM, []{return logic->HitFireTemplePlatform;}),
	Entrance(RR_FIRE_TEMPLE_MQ_HIGH_TORCH_ROOM, []{return true;}),
	Entrance(RR_FIRE_TEMPLE_MQ_FIRE_MAZE_PLATFORMS, []{return (logic->IsAdult || (logic->CanUse(RG_SONG_OF_TIME) || logic->CanUse(RG_HOVER_BOOTS)));}),
	Entrance(RR_FIRE_TEMPLE_MQ_NORTH_FIRE_MAZE, []{return (bool)ctx->GetTrickOption(RT_FIRE_MQ_FLAME_MAZE);}),
	Entrance(RR_FIRE_TEMPLE_MQ_WEST_FIRE_MAZE, []{return logic->OpenedFireMQFireMazeDoor;}),
});
areaTable[RR_FIRE_TEMPLE_MQ_FIRE_MAZE_PLATFORMS] = Region("Fire Temple MQ Fire Maze Platforms", SCENE_FIRE_TEMPLE, false, {RA_FIRE_TEMPLE}, {
	EventAccess(&logic->HitFireTemplePlatform, []{return logic->CanUse(RG_MEGATON_HAMMER);}),
	EventAccess(&logic->OpenedFireMQFireMazeDoor, []{return (logic->CanUse(RG_MEGATON_HAMMER) && logic->CanUse(RG_HOOKSHOT));}),
}, {}, {
	Entrance(RR_FIRE_TEMPLE_MQ_SOUTH_FIRE_MAZE, []{return true;}),
	Entrance(RR_FIRE_TEMPLE_MQ_NORTH_FIRE_MAZE, []{return (logic->CanUse(RG_SONG_OF_TIME) || logic->CanUse(RG_HOVER_BOOTS));}),
});
areaTable[RR_FIRE_TEMPLE_MQ_NORTH_FIRE_MAZE] = Region("Fire Temple MQ North Fire Maze", SCENE_FIRE_TEMPLE, false, {RA_FIRE_TEMPLE}, {}, {
	LOCATION(RC_FIRE_TEMPLE_MQ_GS_FIRE_WALL_MAZE_SIDE_ROOM, logic->CanGetEnemyDrop(RE_GOLD_SKULLTULA)),
	LOCATION(RC_FIRE_TEMPLE_MQ_PAST_FIRE_MAZE_SOUTH_POT, logic->CanUse(RG_BOOMERANG)),
	LOCATION(RC_FIRE_TEMPLE_MQ_FIRE_MAZE_NORTHMOST_POT, logic->CanBreakPots()),
	LOCATION(RC_FIRE_TEMPLE_MQ_FIRE_MAZE_NORTHWEST_POT, logic->CanBreakPots()),
}, {
	Entrance(RR_FIRE_TEMPLE_MQ_SOUTH_FIRE_MAZE, []{return (logic->IsAdult || (bool)ctx->GetTrickOption(RT_FIRE_MQ_FLAME_MAZE));}),
	Entrance(RR_FIRE_TEMPLE_MQ_WEST_FIRE_MAZE, []{return (bool)ctx->GetTrickOption(RT_FIRE_MQ_FLAME_MAZE);}),
});
areaTable[RR_FIRE_TEMPLE_MQ_WEST_FIRE_MAZE] = Region("Fire Temple MQ West Fire Maze", SCENE_FIRE_TEMPLE, false, {RA_FIRE_TEMPLE}, {}, {}, {
	Entrance(RR_FIRE_TEMPLE_MQ_FIRE_MAZE_PAST_WALL, []{return true;}),
	Entrance(RR_FIRE_TEMPLE_MQ_NORTH_FIRE_MAZE, []{return (bool)ctx->GetTrickOption(RT_FIRE_MQ_FLAME_MAZE);}),
});
areaTable[RR_FIRE_TEMPLE_MQ_FIRE_MAZE_PAST_WALL] = Region("Fire Temple MQ Fire Maze Past Wall", SCENE_FIRE_TEMPLE, false, {RA_FIRE_TEMPLE}, {}, {
	LOCATION(RC_FIRE_TEMPLE_MQ_PAST_FIRE_MAZE_SOUTH_POT, logic->CanBreakPots()),
	LOCATION(RC_FIRE_TEMPLE_MQ_PAST_FIRE_MAZE_NORTH_POT, logic->CanBreakPots()),
	LOCATION(RC_FIRE_TEMPLE_MQ_FIRE_MAZE_NORTHWEST_POT, logic->CanUse(RG_BOOMERANG)),
}, {
	Entrance(RR_FIRE_TEMPLE_MQ_UPPER_FLARE_DANCER, []{return true;}),
});
areaTable[RR_FIRE_TEMPLE_MQ_UPPER_FLARE_DANCER] = Region("Fire Temple MQ North Fire Maze", SCENE_FIRE_TEMPLE, false, {RA_FIRE_TEMPLE}, {}, {
	LOCATION(RC_FIRE_TEMPLE_MQ_FREESTANDING_KEY, logic->CanKillEnemy(RE_FLARE_DANCER)),
}, {
	Entrance(RR_FIRE_TEMPLE_MQ_FIRE_MAZE_PAST_WALL, []{return logic->CanKillEnemy(RE_FLARE_DANCER);}),
	Entrance(RR_FIRE_TEMPLE_MQ_SCARECROW_ROOM, []{return (logic->CanKillEnemy(RE_FLARE_DANCER) && logic->SmallKeys(RR_FIRE_TEMPLE, 4));}),
});
areaTable[RR_FIRE_TEMPLE_MQ_SCARECROW_ROOM] = Region("Fire Temple MQ Scarecrow Room", SCENE_FIRE_TEMPLE, false, {RA_FIRE_TEMPLE}, {}, {
	LOCATION(RC_FIRE_TEMPLE_MQ_CHEST_ON_FIRE, (logic->IsAdult || logic->CanUse(RG_SCARECROW))),
}, {
	Entrance(RR_FIRE_TEMPLE_MQ_UPPER_FLARE_DANCER, []{return logic->SmallKeys(RR_FIRE_TEMPLE, 4);}),
	Entrance(RR_FIRE_TEMPLE_MQ_COLLAPSED_STAIRS, []{return (Here(RR_FIRE_TEMPLE_MQ_SCARECROW_ROOM, []{return logic->CanUse(RG_MEGATON_HAMMER);}) && logic->SmallKeys(RR_FIRE_TEMPLE, 5));}),
});
areaTable[RR_FIRE_TEMPLE_MQ_COLLAPSED_STAIRS] = Region("Fire Temple MQ Collapsed Stairs", SCENE_FIRE_TEMPLE, false, {RA_FIRE_TEMPLE}, {}, {
	LOCATION(RC_FIRE_TEMPLE_MQ_GS_ABOVE_FIRE_MAZE, logic->CanUse(RG_HOOKSHOT)),
}, {
	Entrance(RR_FIRE_TEMPLE_MQ_FIRE_MAZE_PLATFORMS, []{return (logic->CanUse(RG_HOOKSHOT) && Here(RR_FIRE_TEMPLE_MQ_COLLAPSED_STAIRS, []{return logic->CanUse(RG_MEGATON_HAMMER);}));}),
	Entrance(RR_FIRE_TEMPLE_MQ_SCARECROW_ROOM, []{return (logic->IsAdult && logic->CanUse(RG_HOOKSHOT));}),
});
areaTable[RR_FIRE_TEMPLE_BOSS_ENTRYWAY] = Region("Fire Temple Boss Entryway", SCENE_FIRE_TEMPLE, false, {RA_FIRE_TEMPLE}, {}, {}, {
	Entrance(RR_FIRE_TEMPLE_NEAR_BOSS_ROOM, []{return (ctx->GetDungeon(Rando::FIRE_TEMPLE)->IsVanilla() && false);}),
	Entrance(RR_FIRE_TEMPLE_MQ_NEAR_BOSS_ROOM, []{return (ctx->GetDungeon(Rando::FIRE_TEMPLE)->IsMQ() && false);}),
	Entrance(RR_FIRE_TEMPLE_BOSS_ROOM, []{return logic->HasItem(RG_FIRE_TEMPLE_BOSS_KEY);}),
});
areaTable[RR_FIRE_TEMPLE_BOSS_ROOM] = Region("Fire Temple Boss Room", SCENE_FIRE_TEMPLE_BOSS, false, {}, {
	EventAccess(&logic->FireTempleClear, []{return ((logic->FireTimer() >= 64) && logic->CanKillEnemy(RE_VOLVAGIA));}),
}, {
	LOCATION(RC_FIRE_TEMPLE_VOLVAGIA_HEART, logic->FireTempleClear),
	LOCATION(RC_VOLVAGIA, logic->FireTempleClear),
}, {
	Entrance(RR_FIRE_TEMPLE_BOSS_ENTRYWAY, []{return false;}),
	Entrance(RR_DMC_CENTRAL_LOCAL, []{return logic->FireTempleClear;}, "", false),
});
areaTable[RR_WATER_TEMPLE_LOBBY] = Region("Water Temple Lobby", SCENE_WATER_TEMPLE, false, {RA_WATER_TEMPLE}, {}, {
	LOCATION(RC_WATER_TEMPLE_MAIN_LEVEL_2_POT_1, (logic->CanBreakPots() && (logic->CanWaterTempleLowFromHigh || (logic->CanWaterTempleMiddle || (logic->CanUse(RG_IRON_BOOTS) && logic->CanUse(RG_HOOKSHOT)))))),
	LOCATION(RC_WATER_TEMPLE_MAIN_LEVEL_2_POT_2, (logic->CanBreakPots() && (logic->CanWaterTempleLowFromHigh || (logic->CanWaterTempleMiddle || (logic->CanUse(RG_IRON_BOOTS) && logic->CanUse(RG_HOOKSHOT)))))),
}, {
	Entrance(RR_WATER_TEMPLE_ENTRYWAY, []{return true;}),
	Entrance(RR_WATER_TEMPLE_EAST_LOWER, []{return (logic->CanWaterTempleLowFromHigh || (((bool)ctx->GetTrickOption(RT_FEWER_TUNIC_REQUIREMENTS) || logic->CanUse(RG_ZORA_TUNIC)) && (logic->CanUse(RG_IRON_BOOTS) || (logic->CanUse(RG_LONGSHOT) && (bool)ctx->GetTrickOption(RT_WATER_LONGSHOT_TORCH)))));}),
	Entrance(RR_WATER_TEMPLE_NORTH_LOWER, []{return (logic->CanWaterTempleLowFromHigh || (((bool)ctx->GetTrickOption(RT_FEWER_TUNIC_REQUIREMENTS) || logic->CanUse(RG_ZORA_TUNIC)) && logic->CanUse(RG_IRON_BOOTS)));}),
	Entrance(RR_WATER_TEMPLE_SOUTH_LOWER, []{return (logic->CanWaterTempleLowFromHigh && (logic->HasExplosives() && ((logic->HasItem(RG_SILVER_SCALE) || logic->CanUse(RG_IRON_BOOTS)) && ((bool)ctx->GetTrickOption(RT_FEWER_TUNIC_REQUIREMENTS) || logic->CanUse(RG_ZORA_TUNIC)))));}),
	Entrance(RR_WATER_TEMPLE_WEST_LOWER, []{return (logic->CanWaterTempleLowFromHigh && (logic->HasItem(RG_GORONS_BRACELET) && ((logic->IsChild || (logic->HasItem(RG_SILVER_SCALE) || logic->CanUse(RG_IRON_BOOTS))) && ((bool)ctx->GetTrickOption(RT_FEWER_TUNIC_REQUIREMENTS) || logic->CanUse(RG_ZORA_TUNIC)))));}),
	Entrance(RR_WATER_TEMPLE_CENTRAL_PILLAR_LOWER, []{return (logic->CanWaterTempleLowFromHigh && logic->SmallKeys(RR_WATER_TEMPLE, 5));}),
	Entrance(RR_WATER_TEMPLE_CENTRAL_PILLAR_UPPER, []{return ((logic->CanWaterTempleLowFromHigh || logic->CanWaterTempleMiddle) && (logic->HasFireSourceWithTorch() || logic->CanUse(RG_FAIRY_BOW)));}),
	Entrance(RR_WATER_TEMPLE_EAST_MIDDLE, []{return ((logic->CanWaterTempleLowFromHigh || (logic->CanWaterTempleMiddle || (logic->CanUse(RG_IRON_BOOTS) && (logic->WaterTimer() >= 16)))) && logic->CanUse(RG_HOOKSHOT));}),
	Entrance(RR_WATER_TEMPLE_WEST_MIDDLE, []{return logic->CanWaterTempleMiddle;}),
	Entrance(RR_WATER_TEMPLE_HIGH_WATER, []{return (logic->IsAdult && (logic->CanUse(RG_HOVER_BOOTS) || ((bool)ctx->GetTrickOption(RT_DAMAGE_BOOST) && (logic->CanUse(RG_BOMB_BAG) && logic->TakeDamage()))));}),
	Entrance(RR_WATER_TEMPLE_BLOCK_CORRIDOR, []{return ((logic->CanWaterTempleLowFromHigh || logic->CanWaterTempleMiddle) && ((logic->CanUse(RG_FAIRY_SLINGSHOT) || logic->CanUse(RG_FAIRY_BOW)) && (logic->CanUse(RG_LONGSHOT) || (logic->CanUse(RG_HOVER_BOOTS) || ((bool)ctx->GetTrickOption(RT_WATER_CENTRAL_BOW) && (logic->IsAdult || logic->CanWaterTempleMiddle))))));}),
	Entrance(RR_WATER_TEMPLE_FALLING_PLATFORM_ROOM, []{return (logic->CanWaterTempleHigh && logic->SmallKeys(RR_WATER_TEMPLE, 4));}),
	Entrance(RR_WATER_TEMPLE_PRE_BOSS_ROOM, []{return ((logic->CanWaterTempleHigh && logic->CanUse(RG_LONGSHOT)) || ((bool)ctx->GetTrickOption(RT_HOVER_BOOST_SIMPLE) && ((bool)ctx->GetTrickOption(RT_DAMAGE_BOOST_SIMPLE) && (logic->HasExplosives() && logic->CanUse(RG_HOVER_BOOTS)))));}),
});
areaTable[RR_WATER_TEMPLE_EAST_LOWER] = Region("Water Temple East Lower", SCENE_WATER_TEMPLE, false, {RA_WATER_TEMPLE}, {
	EventAccess(&logic->CanWaterTempleLowFromHigh, []{return logic->CanUse(RG_ZELDAS_LULLABY);}),
}, {
	LOCATION(RC_WATER_TEMPLE_TORCH_POT_1, (logic->CanBreakPots() && (logic->CanWaterTempleLowFromHigh || (logic->CanUse(RG_HOOKSHOT) && logic->CanUse(RG_IRON_BOOTS))))),
	LOCATION(RC_WATER_TEMPLE_TORCH_POT_2, (logic->CanBreakPots() && (logic->CanWaterTempleLowFromHigh || (logic->CanUse(RG_HOOKSHOT) && logic->CanUse(RG_IRON_BOOTS))))),
}, {
	Entrance(RR_WATER_TEMPLE_LOBBY, []{return (logic->CanWaterTempleLowFromHigh || (((bool)ctx->GetTrickOption(RT_FEWER_TUNIC_REQUIREMENTS) || logic->CanUse(RG_ZORA_TUNIC)) && logic->CanUse(RG_IRON_BOOTS)));}),
	Entrance(RR_WATER_TEMPLE_MAP_ROOM, []{return logic->CanWaterTempleHigh;}),
	Entrance(RR_WATER_TEMPLE_CRACKED_WALL, []{return (logic->CanWaterTempleMiddle || (logic->CanWaterTempleHigh && (logic->CanWaterTempleLowFromHigh && ((logic->CanUse(RG_HOVER_BOOTS) && (bool)ctx->GetTrickOption(RT_WATER_CRACKED_WALL_HOVERS)) || (bool)ctx->GetTrickOption(RT_WATER_CRACKED_WALL)))));}),
	Entrance(RR_WATER_TEMPLE_TORCH_ROOM, []{return (logic->CanWaterTempleLowFromHigh && (logic->HasFireSourceWithTorch() || logic->CanUse(RG_FAIRY_BOW)));}),
});
areaTable[RR_WATER_TEMPLE_MAP_ROOM] = Region("Water Temple Map Room", SCENE_WATER_TEMPLE, false, {RA_WATER_TEMPLE}, {}, {
	LOCATION(RC_WATER_TEMPLE_MAP_CHEST, logic->CanKillEnemy(RE_SPIKE, ED_CLOSE, true, 3)),
}, {
	Entrance(RR_WATER_TEMPLE_EAST_LOWER, []{return logic->CanKillEnemy(RE_SPIKE, ED_CLOSE, true, 3);}),
});
areaTable[RR_WATER_TEMPLE_CRACKED_WALL] = Region("Water Temple Cracked Wall", SCENE_WATER_TEMPLE, false, {RA_WATER_TEMPLE}, {}, {
	LOCATION(RC_WATER_TEMPLE_CRACKED_WALL_CHEST, logic->HasExplosives()),
}, {
	Entrance(RR_WATER_TEMPLE_EAST_LOWER, []{return true;}),
});
areaTable[RR_WATER_TEMPLE_TORCH_ROOM] = Region("Water Temple Torch Room", SCENE_WATER_TEMPLE, false, {RA_WATER_TEMPLE}, {}, {
	LOCATION(RC_WATER_TEMPLE_TORCHES_CHEST, logic->CanKillEnemy(RE_SHELL_BLADE, ED_CLOSE, true, 3)),
}, {
	Entrance(RR_WATER_TEMPLE_EAST_LOWER, []{return logic->CanKillEnemy(RE_SHELL_BLADE, ED_CLOSE, true, 3);}),
});
areaTable[RR_WATER_TEMPLE_NORTH_LOWER] = Region("Water Temple North Lower", SCENE_WATER_TEMPLE, false, {RA_WATER_TEMPLE}, {}, {}, {
	Entrance(RR_WATER_TEMPLE_LOBBY, []{return true;}),
	Entrance(RR_WATER_TEMPLE_BOULDERS_LOWER, []{return ((logic->CanUse(RG_LONGSHOT) || ((bool)ctx->GetTrickOption(RT_WATER_BK_REGION) && logic->CanUse(RG_HOVER_BOOTS))) && logic->SmallKeys(RR_WATER_TEMPLE, 4));}),
});
areaTable[RR_WATER_TEMPLE_BOULDERS_LOWER] = Region("Water Temple Boulders Lower", SCENE_WATER_TEMPLE, false, {RA_WATER_TEMPLE}, {}, {
	LOCATION(RC_WATER_TEMPLE_GS_NEAR_BOSS_KEY_CHEST, (logic->CanUse(RG_LONGSHOT) || Here(RR_WATER_TEMPLE_BOULDERS_LOWER, []{return ((logic->IsAdult && logic->HookshotOrBoomerang()) || (logic->CanUse(RG_IRON_BOOTS) && logic->CanUse(RG_HOOKSHOT)));}))),
}, {
	Entrance(RR_WATER_TEMPLE_NORTH_LOWER, []{return logic->SmallKeys(RR_WATER_TEMPLE, 4);}),
	Entrance(RR_WATER_TEMPLE_BLOCK_ROOM, []{return true;}),
	Entrance(RR_WATER_TEMPLE_BOULDERS_UPPER, []{return ((logic->IsAdult && (logic->CanUse(RG_HOVER_BOOTS) || (bool)ctx->GetTrickOption(RT_WATER_NORTH_BASEMENT_LEDGE_JUMP))) || (logic->CanUse(RG_HOVER_BOOTS) && logic->CanUse(RG_IRON_BOOTS)));}),
});
areaTable[RR_WATER_TEMPLE_BLOCK_ROOM] = Region("Water Temple Block Room", SCENE_WATER_TEMPLE, false, {RA_WATER_TEMPLE}, {}, {
	LOCATION(RC_WATER_TEMPLE_BASEMENT_BLOCK_PUZZLE_POT_1, logic->CanBreakPots()),
	LOCATION(RC_WATER_TEMPLE_BASEMENT_BLOCK_PUZZLE_POT_2, logic->CanBreakPots()),
}, {
	Entrance(RR_WATER_TEMPLE_BOULDERS_LOWER, []{return ((logic->HasItem(RG_GORONS_BRACELET) && logic->HasExplosives()) || logic->CanUse(RG_HOOKSHOT));}),
	Entrance(RR_WATER_TEMPLE_JETS_ROOM, []{return ((logic->HasItem(RG_GORONS_BRACELET) && logic->HasExplosives()) || (logic->CanUse(RG_HOOKSHOT) && logic->CanUse(RG_HOVER_BOOTS)));}),
});
areaTable[RR_WATER_TEMPLE_JETS_ROOM] = Region("Water Temple Jets Room", SCENE_WATER_TEMPLE, false, {RA_WATER_TEMPLE}, {}, {}, {
	Entrance(RR_WATER_TEMPLE_BLOCK_ROOM, []{return logic->CanUse(RG_HOOKSHOT);}),
	Entrance(RR_WATER_TEMPLE_BOULDERS_UPPER, []{return true;}),
});
areaTable[RR_WATER_TEMPLE_BOULDERS_UPPER] = Region("Water Temple Boulders Upper", SCENE_WATER_TEMPLE, false, {RA_WATER_TEMPLE}, {}, {}, {
	Entrance(RR_WATER_TEMPLE_BOULDERS_LOWER, []{return true;}),
	Entrance(RR_WATER_TEMPLE_JETS_ROOM, []{return logic->IsAdult;}),
	Entrance(RR_WATER_TEMPLE_BOSS_KEY_ROOM, []{return ((logic->CanUse(RG_IRON_BOOTS) || (logic->IsAdult && (bool)ctx->GetTrickOption(RT_WATER_BK_JUMP_DIVE))) && logic->SmallKeys(RR_WATER_TEMPLE, 5));}),
});
areaTable[RR_WATER_TEMPLE_BOSS_KEY_ROOM] = Region("Water Temple Boss Key Room", SCENE_WATER_TEMPLE, false, {RA_WATER_TEMPLE}, {
	EventAccess(&logic->FairyPot, []{return true;}),
}, {
	LOCATION(RC_WATER_TEMPLE_BOSS_KEY_CHEST, true),
	LOCATION(RC_WATER_TEMPLE_BOSS_KEY_POT_1, logic->CanBreakPots()),
	LOCATION(RC_WATER_TEMPLE_BOSS_KEY_POT_2, logic->CanBreakPots()),
}, {
	Entrance(RR_WATER_TEMPLE_BOULDERS_UPPER, []{return ((logic->CanUse(RG_IRON_BOOTS) || ((logic->IsAdult && (bool)ctx->GetTrickOption(RT_WATER_BK_JUMP_DIVE)) || (logic->IsChild || logic->HasItem(RG_SILVER_SCALE)))) && logic->SmallKeys(RR_WATER_TEMPLE, 5));}),
});
areaTable[RR_WATER_TEMPLE_SOUTH_LOWER] = Region("Water Temple South Lower", SCENE_WATER_TEMPLE, false, {RA_WATER_TEMPLE}, {}, {
	LOCATION(RC_WATER_TEMPLE_GS_BEHIND_GATE, (logic->CanJumpslash() && (logic->CanUse(RG_HOOKSHOT) || (logic->IsAdult && logic->CanUse(RG_HOVER_BOOTS))))),
	LOCATION(RC_WATER_TEMPLE_BEHIND_GATE_POT_1, (logic->CanJumpslash() && (logic->CanUse(RG_HOOKSHOT) || (logic->IsAdult && logic->CanUse(RG_HOVER_BOOTS))))),
	LOCATION(RC_WATER_TEMPLE_BEHIND_GATE_POT_2, (logic->CanJumpslash() && (logic->CanUse(RG_HOOKSHOT) || (logic->IsAdult && logic->CanUse(RG_HOVER_BOOTS))))),
	LOCATION(RC_WATER_TEMPLE_BEHIND_GATE_POT_3, (logic->CanJumpslash() && (logic->CanUse(RG_HOOKSHOT) || (logic->IsAdult && logic->CanUse(RG_HOVER_BOOTS))))),
	LOCATION(RC_WATER_TEMPLE_BEHIND_GATE_POT_4, (logic->CanJumpslash() && (logic->CanUse(RG_HOOKSHOT) || (logic->IsAdult && logic->CanUse(RG_HOVER_BOOTS))))),
}, {
	Entrance(RR_WATER_TEMPLE_LOBBY, []{return logic->CanUse(RG_IRON_BOOTS);}),
});
areaTable[RR_WATER_TEMPLE_WEST_LOWER] = Region("Water Temple West Lower", SCENE_WATER_TEMPLE, false, {RA_WATER_TEMPLE}, {}, {}, {
	Entrance(RR_WATER_TEMPLE_LOBBY, []{return (logic->CanUse(RG_HOOKSHOT) && (logic->CanUse(RG_IRON_BOOTS) && logic->HasItem(RG_GORONS_BRACELET)));}),
	Entrance(RR_WATER_TEMPLE_DRAGON_ROOM, []{return (logic->CanJumpslashExceptHammer() || logic->CanUseProjectile());}),
});
areaTable[RR_WATER_TEMPLE_DRAGON_ROOM] = Region("Water Temple Dragon Room", SCENE_WATER_TEMPLE, false, {RA_WATER_TEMPLE}, {}, {
	LOCATION(RC_WATER_TEMPLE_DRAGON_CHEST, ((logic->CanUse(RG_HOOKSHOT) && logic->CanUse(RG_IRON_BOOTS)) || ((((logic->IsAdult && ((bool)ctx->GetTrickOption(RT_WATER_ADULT_DRAGON) && (logic->CanUse(RG_HOOKSHOT) || (logic->CanUse(RG_FAIRY_BOW) || logic->CanUse(RG_BOMBCHU_5))))) || (logic->IsChild && ((bool)ctx->GetTrickOption(RT_WATER_CHILD_DRAGON) && (logic->CanUse(RG_FAIRY_SLINGSHOT) || (logic->CanUse(RG_BOOMERANG) || logic->CanUse(RG_BOMBCHU_5)))))) && (logic->HasItem(RG_SILVER_SCALE) || logic->CanUse(RG_IRON_BOOTS))) || Here(RR_WATER_TEMPLE_DRAGON_ROOM, []{return (logic->IsAdult && (logic->CanUse(RG_FAIRY_BOW) && (((bool)ctx->GetTrickOption(RT_WATER_ADULT_DRAGON) && (logic->HasItem(RG_SILVER_SCALE) || logic->CanUse(RG_IRON_BOOTS))) || (bool)ctx->GetTrickOption(RT_WATER_DRAGON_JUMP_DIVE))));})))),
}, {
	Entrance(RR_WATER_TEMPLE_WEST_LOWER, []{return true;}),
});
areaTable[RR_WATER_TEMPLE_CENTRAL_PILLAR_LOWER] = Region("Water Temple Central Pillar Lower", SCENE_WATER_TEMPLE, false, {RA_WATER_TEMPLE}, {}, {}, {
	Entrance(RR_WATER_TEMPLE_LOBBY, []{return logic->SmallKeys(RR_WATER_TEMPLE, 5);}),
	Entrance(RR_WATER_TEMPLE_CENTRAL_PILLAR_UPPER, []{return logic->CanUse(RG_HOOKSHOT);}),
	Entrance(RR_WATER_TEMPLE_CENTRAL_PILLAR_BASEMENT, []{return (logic->CanWaterTempleMiddle && (logic->CanUse(RG_IRON_BOOTS) && (logic->WaterTimer() >= 40)));}),
});
areaTable[RR_WATER_TEMPLE_CENTRAL_PILLAR_UPPER] = Region("Water Temple Central Pillar Upper", SCENE_WATER_TEMPLE, false, {RA_WATER_TEMPLE}, {
	EventAccess(&logic->CanWaterTempleMiddle, []{return logic->CanUse(RG_ZELDAS_LULLABY);}),
}, {
	LOCATION(RC_WATER_TEMPLE_GS_CENTRAL_PILLAR, (logic->CanUse(RG_LONGSHOT) || ((((bool)ctx->GetTrickOption(RT_WATER_FW_CENTRAL_GS) && (logic->CanUse(RG_FARORES_WIND) && (logic->CanUse(RG_FAIRY_BOW) || (logic->CanUse(RG_DINS_FIRE) || logic->SmallKeys(RR_WATER_TEMPLE, 5))))) || ((bool)ctx->GetTrickOption(RT_WATER_IRONS_CENTRAL_GS) && (logic->CanUse(RG_IRON_BOOTS) && ((logic->CanUse(RG_HOOKSHOT) && logic->CanUse(RG_FAIRY_BOW)) || logic->CanUse(RG_DINS_FIRE))))) && (logic->CanWaterTempleHigh && logic->HookshotOrBoomerang())))),
}, {
	Entrance(RR_WATER_TEMPLE_LOBBY, []{return true;}),
	Entrance(RR_WATER_TEMPLE_CENTRAL_PILLAR_LOWER, []{return true;}),
});
areaTable[RR_WATER_TEMPLE_CENTRAL_PILLAR_BASEMENT] = Region("Water Temple Central Pillar Basement", SCENE_WATER_TEMPLE, false, {RA_WATER_TEMPLE}, {}, {
	LOCATION(RC_WATER_TEMPLE_CENTRAL_PILLAR_CHEST, (logic->CanUse(RG_HOOKSHOT) && (logic->CanUse(RG_IRON_BOOTS) && (logic->WaterTimer() >= 40)))),
}, {
	Entrance(RR_WATER_TEMPLE_CENTRAL_PILLAR_LOWER, []{return (logic->CanUse(RG_IRON_BOOTS) && (logic->WaterTimer() >= 16));}),
});
areaTable[RR_WATER_TEMPLE_EAST_MIDDLE] = Region("Water Temple East Middle", SCENE_WATER_TEMPLE, false, {RA_WATER_TEMPLE}, {}, {
	LOCATION(RC_WATER_TEMPLE_COMPASS_CHEST, logic->CanUseProjectile()),
	LOCATION(RC_WATER_TEMPLE_NEAR_COMPASS_POT_1, logic->CanBreakPots()),
	LOCATION(RC_WATER_TEMPLE_NEAR_COMPASS_POT_2, logic->CanBreakPots()),
	LOCATION(RC_WATER_TEMPLE_NEAR_COMPASS_POT_3, logic->CanBreakPots()),
}, {
	Entrance(RR_WATER_TEMPLE_LOBBY, []{return logic->CanUse(RG_IRON_BOOTS);}),
});
areaTable[RR_WATER_TEMPLE_WEST_MIDDLE] = Region("Water Temple West Middle", SCENE_WATER_TEMPLE, false, {RA_WATER_TEMPLE}, {}, {}, {
	Entrance(RR_WATER_TEMPLE_LOBBY, []{return true;}),
	Entrance(RR_WATER_TEMPLE_HIGH_WATER, []{return logic->CanUseProjectile();}),
});
areaTable[RR_WATER_TEMPLE_HIGH_WATER] = Region("Water Temple High Water", SCENE_WATER_TEMPLE, false, {RA_WATER_TEMPLE}, {
	EventAccess(&logic->CanWaterTempleHigh, []{return logic->CanUse(RG_ZELDAS_LULLABY);}),
}, {}, {
	Entrance(RR_WATER_TEMPLE_LOBBY, []{return true;}),
});
areaTable[RR_WATER_TEMPLE_BLOCK_CORRIDOR] = Region("Water Temple Block Corridor", SCENE_WATER_TEMPLE, false, {RA_WATER_TEMPLE}, {}, {
	LOCATION(RC_WATER_TEMPLE_CENTRAL_BOW_TARGET_CHEST, (logic->HasItem(RG_GORONS_BRACELET) && (logic->CanWaterTempleLowFromHigh || logic->CanWaterTempleMiddle))),
	LOCATION(RC_WATER_TEMPLE_CENTRAL_BOW_POT_1, (logic->CanBreakPots() && (logic->HasItem(RG_GORONS_BRACELET) && (logic->CanWaterTempleLowFromHigh || logic->CanWaterTempleMiddle)))),
	LOCATION(RC_WATER_TEMPLE_CENTRAL_BOW_POT_2, (logic->CanBreakPots() && (logic->HasItem(RG_GORONS_BRACELET) && (logic->CanWaterTempleLowFromHigh || logic->CanWaterTempleMiddle)))),
}, {
	Entrance(RR_WATER_TEMPLE_LOBBY, []{return logic->CanUse(RG_HOOKSHOT);}),
});
areaTable[RR_WATER_TEMPLE_FALLING_PLATFORM_ROOM] = Region("Water Temple Falling Platform Room", SCENE_WATER_TEMPLE, false, {RA_WATER_TEMPLE}, {}, {
	LOCATION(RC_WATER_TEMPLE_GS_FALLING_PLATFORM_ROOM, (logic->CanUse(RG_LONGSHOT) || (((bool)ctx->GetTrickOption(RT_WATER_RANG_FALLING_PLATFORM_GS) && (logic->IsChild && logic->CanUse(RG_BOOMERANG))) || ((bool)ctx->GetTrickOption(RT_WATER_HOOKSHOT_FALLING_PLATFORM_GS) && (logic->IsAdult && logic->CanUse(RG_HOOKSHOT)))))),
}, {
	Entrance(RR_WATER_TEMPLE_LOBBY, []{return (logic->CanUse(RG_HOOKSHOT) && logic->SmallKeys(RR_WATER_TEMPLE, 4));}),
	Entrance(RR_WATER_TEMPLE_DRAGON_PILLARS_ROOM, []{return (logic->CanUse(RG_HOOKSHOT) && logic->SmallKeys(RR_WATER_TEMPLE, 5));}),
});
areaTable[RR_WATER_TEMPLE_DRAGON_PILLARS_ROOM] = Region("Water Temple Dragon Pillars Room", SCENE_WATER_TEMPLE, false, {RA_WATER_TEMPLE}, {}, {
	LOCATION(RC_WATER_TEMPLE_LIKE_LIKE_POT_1, logic->CanUse(RG_HOOKSHOT)),
	LOCATION(RC_WATER_TEMPLE_LIKE_LIKE_POT_2, logic->CanUse(RG_HOOKSHOT)),
}, {
	Entrance(RR_WATER_TEMPLE_FALLING_PLATFORM_ROOM, []{return logic->CanUseProjectile();}),
	Entrance(RR_WATER_TEMPLE_DARK_LINK_ROOM, []{return logic->CanUse(RG_HOOKSHOT);}),
});
areaTable[RR_WATER_TEMPLE_DARK_LINK_ROOM] = Region("Water Temple Dark Link Room", SCENE_WATER_TEMPLE, false, {RA_WATER_TEMPLE}, {}, {}, {
	Entrance(RR_WATER_TEMPLE_DRAGON_PILLARS_ROOM, []{return logic->CanKillEnemy(RE_DARK_LINK);}),
	Entrance(RR_WATER_TEMPLE_LONGSHOT_ROOM, []{return logic->CanKillEnemy(RE_DARK_LINK);}),
});
areaTable[RR_WATER_TEMPLE_LONGSHOT_ROOM] = Region("Water Temple Longshot Room", SCENE_WATER_TEMPLE, false, {RA_WATER_TEMPLE}, {}, {
	LOCATION(RC_WATER_TEMPLE_LONGSHOT_CHEST, true),
}, {
	Entrance(RR_WATER_TEMPLE_DARK_LINK_ROOM, []{return true;}),
	Entrance(RR_WATER_TEMPLE_RIVER, []{return (logic->IsChild || logic->CanUse(RG_SONG_OF_TIME));}),
});
areaTable[RR_WATER_TEMPLE_RIVER] = Region("Water Temple River", SCENE_WATER_TEMPLE, false, {RA_WATER_TEMPLE}, {}, {
	LOCATION(RC_WATER_TEMPLE_RIVER_CHEST, ((logic->CanUse(RG_FAIRY_SLINGSHOT) || logic->CanUse(RG_FAIRY_BOW)) && (logic->IsAdult || (logic->CanUse(RG_HOVER_BOOTS) || logic->CanUse(RG_HOOKSHOT))))),
	LOCATION(RC_WATER_TEMPLE_GS_RIVER, ((logic->CanUse(RG_IRON_BOOTS) && logic->CanUse(RG_HOOKSHOT)) || ((bool)ctx->GetTrickOption(RT_WATER_RIVER_GS) && logic->CanUse(RG_LONGSHOT)))),
	LOCATION(RC_WATER_TEMPLE_RIVER_POT_1, logic->CanBreakPots()),
	LOCATION(RC_WATER_TEMPLE_RIVER_POT_2, logic->CanBreakPots()),
	LOCATION(RC_WATER_TEMPLE_RIVER_HEART_1, ((logic->CanUse(RG_IRON_BOOTS) && (logic->WaterTimer() >= 16)) || logic->HasItem(RG_BRONZE_SCALE))),
	LOCATION(RC_WATER_TEMPLE_RIVER_HEART_2, ((logic->CanUse(RG_IRON_BOOTS) && (logic->WaterTimer() >= 16)) || logic->HasItem(RG_BRONZE_SCALE))),
	LOCATION(RC_WATER_TEMPLE_RIVER_HEART_3, ((logic->CanUse(RG_IRON_BOOTS) && (logic->WaterTimer() >= 16)) || logic->HasItem(RG_BRONZE_SCALE))),
	LOCATION(RC_WATER_TEMPLE_RIVER_HEART_4, ((logic->CanUse(RG_IRON_BOOTS) && (logic->WaterTimer() >= 24)) || logic->HasItem(RG_BRONZE_SCALE))),
}, {
	Entrance(RR_WATER_TEMPLE_DRAGON_ROOM, []{return ((logic->CanUse(RG_FAIRY_SLINGSHOT) || logic->CanUse(RG_FAIRY_BOW)) && (logic->IsAdult || (logic->CanUse(RG_HOVER_BOOTS) || logic->CanUse(RG_HOOKSHOT))));}),
});
areaTable[RR_WATER_TEMPLE_PRE_BOSS_ROOM] = Region("Water Temple Pre Boss Room", SCENE_WATER_TEMPLE, false, {RA_WATER_TEMPLE}, {
	EventAccess(&logic->FairyPot, []{return true;}),
}, {
	LOCATION(RC_WATER_TEMPLE_MAIN_LEVEL_1_POT_1, logic->CanBreakPots()),
	LOCATION(RC_WATER_TEMPLE_MAIN_LEVEL_1_POT_2, logic->CanBreakPots()),
}, {
	Entrance(RR_WATER_TEMPLE_LOBBY, []{return true;}),
	Entrance(RR_WATER_TEMPLE_BOSS_ENTRYWAY, []{return true;}),
});
areaTable[RR_WATER_TEMPLE_MQ_3F_SOUTH_LEDGE] = Region("Water Temple MQ 3F South Ledge", SCENE_WATER_TEMPLE, false, {RA_WATER_TEMPLE}, {}, {}, {
	Entrance(RR_WATER_TEMPLE_ENTRYWAY, []{return (logic->HasItem(RG_BRONZE_SCALE) || logic->CanUse(RG_IRON_BOOTS));}),
	Entrance(RR_WATER_TEMPLE_MQ_MAIN, []{return true;}),
	Entrance(RR_WATER_TEMPLE_MQ_3F_CENTRAL, []{return (logic->CanUse(RG_HOOKSHOT) || logic->CanUse(RG_HOVER_BOOTS));}),
	Entrance(RR_WATER_TEMPLE_MQ_2F_CENTRAL, []{return logic->MQWaterLevel(WL_LOW_OR_MID);}),
});
areaTable[RR_WATER_TEMPLE_MQ_MAIN] = Region("Water Temple MQ Main", SCENE_WATER_TEMPLE, false, {RA_WATER_TEMPLE}, {}, {}, {
	Entrance(RR_WATER_TEMPLE_MQ_3F_SOUTH_LEDGE, []{return (logic->HasItem(RG_BRONZE_SCALE) && logic->MQWaterLevel(WL_HIGH));}),
	Entrance(RR_WATER_TEMPLE_MQ_EAST_TOWER, []{return (((logic->WaterTimer() >= 24) && logic->CanUse(RG_IRON_BOOTS)) || ((logic->MQWaterLevel(WL_MID) && (logic->HasItem(RG_GOLDEN_SCALE) && (logic->WaterTimer() >= 16))) || logic->MQWaterLevel(WL_LOW)));}),
	Entrance(RR_WATER_TEMPLE_MQ_3F_CENTRAL, []{return (logic->MQWaterLevel(WL_HIGH) && logic->HasItem(RG_BRONZE_SCALE));}),
	Entrance(RR_WATER_TEMPLE_MQ_2F_CENTRAL, []{return (((logic->MQWaterLevel(WL_LOW) || (logic->CanUse(RG_IRON_BOOTS) && (logic->MQWaterLevel(WL_MID) || (logic->WaterTimer() >= 16)))) && logic->CanUse(RG_LONGSHOT)) || ((logic->MQWaterLevel(WL_MID) || (logic->MQWaterLevel(WL_HIGH_OR_MID) && (logic->CanUse(RG_IRON_BOOTS) && (logic->WaterTimer() >= 8)))) && logic->HasItem(RG_BRONZE_SCALE)));}),
	Entrance(RR_WATER_TEMPLE_MQ_CENTRAL_PILLAR_1F, []{return logic->MQWaterLevel(WL_LOW);}),
	Entrance(RR_WATER_TEMPLE_MQ_CENTRAL_PILLAR_HIGH, []{return (logic->MQWaterLevel(WL_HIGH) && (logic->CanUse(RG_IRON_BOOTS) && ((logic->WaterTimer() >= 16) && (logic->HasItem(RG_BRONZE_SCALE) || logic->CanUse(RG_LONGSHOT)))));}),
	Entrance(RR_WATER_TEMPLE_MQ_LIZALFOS_HALLWAY, []{return ((logic->MQWaterLevel(WL_MID) || (logic->MQWaterLevel(WL_HIGH_OR_MID) && (logic->CanUse(RG_IRON_BOOTS) && (logic->WaterTimer() >= 16)))) && logic->HasItem(RG_BRONZE_SCALE));}),
	Entrance(RR_WATER_TEMPLE_MQ_B1_GATE_SWITCH, []{return (logic->MQWaterB1Switch && (logic->MQWaterLevel(WL_LOW) || ((logic->CanUse(RG_IRON_BOOTS) && (logic->WaterTimer() >= 24)) && logic->HasItem(RG_BRONZE_SCALE))));}),
	Entrance(RR_WATER_TEMPLE_MQ_TRIANGLE_TORCH_ROOM, []{return (logic->MQWaterB1Switch && ((logic->MQWaterLevel(WL_LOW) && logic->HasItem(RG_SILVER_SCALE)) || (logic->CanUse(RG_IRON_BOOTS) && ((logic->WaterTimer() >= 16) && (logic->HasItem(RG_BRONZE_SCALE) || logic->CanUse(RG_LONGSHOT))))));}),
	Entrance(RR_WATER_TEMPLE_MQ_CRATES_WHIRLPOOLS_ROOM, []{return (logic->MQWaterB1Switch && (((logic->MQWaterLevel(WL_LOW) && logic->HasItem(RG_BRONZE_SCALE)) || (logic->CanUse(RG_IRON_BOOTS) && ((logic->WaterTimer() >= 16) && logic->CanUse(RG_HOOKSHOT)))) && (logic->CanUse(RG_LONGSHOT) || ((bool)ctx->GetTrickOption(RT_WATER_BK_REGION) && logic->CanUse(RG_HOVER_BOOTS)))));}),
});
areaTable[RR_WATER_TEMPLE_MQ_3F_CENTRAL] = Region("Water Temple MQ 3F Central", SCENE_WATER_TEMPLE, false, {RA_WATER_TEMPLE}, {}, {}, {
	Entrance(RR_WATER_TEMPLE_MQ_MAIN, []{return true;}),
	Entrance(RR_WATER_TEMPLE_MQ_3F_SOUTH_LEDGE, []{return (logic->CanUse(RG_LONGSHOT) || logic->CanUse(RG_HOVER_BOOTS));}),
	Entrance(RR_WATER_TEMPLE_MQ_2F_CENTRAL, []{return ((logic->MQWaterLevel(WL_LOW_OR_MID) || (logic->CanUse(RG_IRON_BOOTS) && (logic->WaterTimer() >= 16))) && logic->CanUse(RG_HOOKSHOT));}),
	Entrance(RR_WATER_TEMPLE_MQ_CENTRAL_PILLAR_HIGH, []{return (logic->MQWaterLevel(WL_HIGH) && (logic->CanUse(RG_IRON_BOOTS) && ((logic->WaterTimer() >= 16) && logic->CanUse(RG_HOOKSHOT))));}),
	Entrance(RR_WATER_TEMPLE_MQ_3F_NORTH_LEDGE, []{return ((logic->MQWaterLevel(WL_HIGH) && logic->CanUse(RG_LONGSHOT)) || ((bool)ctx->GetTrickOption(RT_HOVER_BOOST_SIMPLE) && ((bool)ctx->GetTrickOption(RT_DAMAGE_BOOST_SIMPLE) && (logic->HasExplosives() && logic->CanUse(RG_HOVER_BOOTS)))));}),
	Entrance(RR_WATER_TEMPLE_MQ_HIGH_EMBLEM, []{return (logic->CanUse(RG_HOOKSHOT) || (logic->IsAdult && logic->CanUse(RG_HOVER_BOOTS)));}),
	Entrance(RR_WATER_TEMPLE_MQ_WATERFALL, []{return (logic->SmallKeys(RR_WATER_TEMPLE, 1) && (logic->MQWaterLevel(WL_HIGH) && logic->CanUse(RG_LONGSHOT)));}),
	Entrance(RR_WATER_TEMPLE_MQ_LIZALFOS_HALLWAY, []{return ((logic->CanUse(RG_IRON_BOOTS) && (logic->WaterTimer() >= 16)) || logic->MQWaterLevel(WL_LOW_OR_MID));}),
});
areaTable[RR_WATER_TEMPLE_MQ_2F_CENTRAL] = Region("Water Temple MQ 2F Central", SCENE_WATER_TEMPLE, false, {RA_WATER_TEMPLE}, {}, {}, {
	Entrance(RR_WATER_TEMPLE_MQ_MAIN, []{return true;}),
	Entrance(RR_WATER_TEMPLE_MQ_3F_CENTRAL, []{return logic->CanUse(RG_HOOKSHOT);}),
	Entrance(RR_WATER_TEMPLE_MQ_CENTRAL_PILLAR_2F, []{return logic->MQWaterLevel(WL_LOW_OR_MID);}),
	Entrance(RR_WATER_TEMPLE_MQ_STORAGE_ROOM, []{return logic->CanUse(RG_HOOKSHOT);}),
	Entrance(RR_WATER_TEMPLE_MQ_BEHIND_BLUE_SWITCH_2F, []{return (logic->MQWaterLevel(WL_LOW_OR_MID) && ((logic->IsAdult || logic->CanUse(RG_HOVER_BOOTS)) && logic->CanUse(RG_HOOKSHOT)));}),
	Entrance(RR_WATER_TEMPLE_MQ_LIZALFOS_HALLWAY, []{return (logic->MQWaterLevel(WL_LOW_OR_MID) && logic->CanUse(RG_HOVER_BOOTS));}),
});
areaTable[RR_WATER_TEMPLE_MQ_2F_CENTRAL_HIGH] = Region("Invalid Region", SCENE_ID_MAX, false, {}, {}, {}, {});
areaTable[RR_WATER_TEMPLE_MQ_HIGH_EMBLEM] = Region("Water Temple MQ High Emblem", SCENE_WATER_TEMPLE, false, {RA_WATER_TEMPLE}, {
	EventAccess(&logic->ReachedWaterHighEmblem, []{return true;}),
	EventAccess(&logic->CanWaterTempleHigh, []{return logic->CanUse(RG_ZELDAS_LULLABY);}),
}, {}, {
	Entrance(RR_WATER_TEMPLE_MQ_3F_CENTRAL, []{return true;}),
	Entrance(RR_WATER_TEMPLE_MQ_MAIN, []{return true;}),
});
areaTable[RR_WATER_TEMPLE_MQ_3F_NORTH_LEDGE] = Region("Water Temple MQ 3F North Ledge", SCENE_WATER_TEMPLE, false, {RA_WATER_TEMPLE}, {}, {}, {
	Entrance(RR_WATER_TEMPLE_MQ_MAIN, []{return (logic->HasItem(RG_BRONZE_SCALE) || logic->TakeDamage());}),
	Entrance(RR_WATER_TEMPLE_MQ_3F_CENTRAL, []{return logic->CanUse(RG_LONGSHOT);}),
	Entrance(RR_WATER_TEMPLE_MQ_BOSS_DOOR, []{return (logic->CanUse(RG_LONGSHOT) || (logic->CanUse(RG_ICE_ARROWS) || logic->CanUse(RG_NAYRUS_LOVE)));}),
});
areaTable[RR_WATER_TEMPLE_MQ_BOSS_DOOR] = Region("Water Temple MQ Main", SCENE_WATER_TEMPLE, false, {RA_WATER_TEMPLE}, {}, {}, {
	Entrance(RR_WATER_TEMPLE_MQ_3F_NORTH_LEDGE, []{return (logic->CanUse(RG_ICE_ARROWS) || logic->TakeDamage());}),
	Entrance(RR_WATER_TEMPLE_BOSS_ENTRYWAY, []{return true;}),
});
areaTable[RR_WATER_TEMPLE_MQ_EAST_TOWER] = Region("Water Temple MQ East Tower", SCENE_WATER_TEMPLE, false, {RA_WATER_TEMPLE}, {
	EventAccess(&logic->CouldWaterTempleLow, []{return true;}),
	EventAccess(&logic->CanWaterTempleLowFromHigh, []{return logic->CanUse(RG_ZELDAS_LULLABY);}),
}, {
	LOCATION(RC_WATER_TEMPLE_MQ_MAP_CHEST, (logic->MQWaterLevel(WL_HIGH) && (logic->HasFireSource() && logic->CanUse(RG_HOOKSHOT)))),
	LOCATION(RC_WATER_TEMPLE_MQ_LONGSHOT_CHEST, ((logic->MQWaterLevel(WL_MID) && logic->CanUse(RG_HOOKSHOT)) || (logic->MQWaterLevel(WL_HIGH_OR_MID) && logic->CanOpenUnderwaterChest()))),
	LOCATION(RC_WATER_TEMPLE_MQ_LOWER_TORCHES_POT_1, ((logic->MQWaterLevel(WL_LOW) && logic->CanBreakPots()) || (logic->CanUse(RG_IRON_BOOTS) && (logic->CanUse(RG_HOOKSHOT) && (logic->WaterTimer() >= 16))))),
	LOCATION(RC_WATER_TEMPLE_MQ_LOWER_TORCHES_POT_2, ((logic->MQWaterLevel(WL_LOW) && logic->CanBreakPots()) || (logic->CanUse(RG_IRON_BOOTS) && (logic->CanUse(RG_HOOKSHOT) && (logic->WaterTimer() >= 16))))),
}, {
	Entrance(RR_WATER_TEMPLE_MQ_EAST_TOWER_1F_ROOM, []{return (logic->MQWaterLevel(WL_LOW) && (logic->CanUse(RG_FAIRY_BOW) || (logic->CanUse(RG_DINS_FIRE) || logic->CanUse(RG_STICKS))));}),
});
areaTable[RR_WATER_TEMPLE_MQ_EAST_TOWER_1F_ROOM] = Region("Water Temple MQ East Tower 1F Room", SCENE_WATER_TEMPLE, false, {RA_WATER_TEMPLE}, {}, {
	LOCATION(RC_WATER_TEMPLE_MQ_COMPASS_CHEST, (logic->CanKillEnemy(RE_LIZALFOS) && logic->CanKillEnemy(RE_SPIKE))),
}, {
	Entrance(RR_WATER_TEMPLE_MQ_EAST_TOWER, []{return true;}),
});
areaTable[RR_WATER_TEMPLE_MQ_CENTRAL_PILLAR_1F] = Region("Water Temple MQ Central Pillar 1F", SCENE_WATER_TEMPLE, false, {RA_WATER_TEMPLE}, {
	EventAccess(&logic->MQWaterB1Switch, []{return ((bool)ctx->GetTrickOption(RT_WATER_MQ_CENTRAL_PILLAR) && logic->CanUse(RG_FIRE_ARROWS));}),
}, {}, {
	Entrance(RR_WATER_TEMPLE_MQ_CENTRAL_PILLAR_HIGH, []{return (logic->MQWaterLevel(WL_HIGH) && ((bool)ctx->GetTrickOption(RT_WATER_FW_CENTRAL_GS) && (logic->CanUse(RG_FARORES_WIND) && logic->HasItem(RG_BRONZE_SCALE))));}),
	Entrance(RR_WATER_TEMPLE_MQ_CENTRAL_PILLAR_2F, []{return (logic->CanUse(RG_HOOKSHOT) || (logic->MQWaterLevel(WL_MID) && ((bool)ctx->GetTrickOption(RT_WATER_FW_CENTRAL_GS) && (logic->CanUse(RG_FARORES_WIND) && logic->HasItem(RG_BRONZE_SCALE)))));}),
	Entrance(RR_WATER_TEMPLE_MQ_CENTRAL_PILLAR_B1, []{return (logic->MQWaterOpenedPillarB1 && (logic->MQWaterLevel(WL_HIGH_OR_MID) && ((bool)ctx->GetTrickOption(RT_WATER_FW_CENTRAL_GS) && (logic->CanUse(RG_FARORES_WIND) && (logic->CanUse(RG_IRON_BOOTS) && logic->CanUse(RG_ZORA_TUNIC))))));}),
});
areaTable[RR_WATER_TEMPLE_MQ_CENTRAL_PILLAR_2F] = Region("Water Temple MQ Central Pillar 2F", SCENE_WATER_TEMPLE, false, {RA_WATER_TEMPLE}, {
	EventAccess(&logic->CouldWaterTempleMiddle, []{return true;}),
	EventAccess(&logic->CanWaterTempleMiddle, []{return logic->CanUse(RG_ZELDAS_LULLABY);}),
	EventAccess(&logic->MQWaterOpenedPillarB1, []{return ((bool)ctx->GetTrickOption(RT_WATER_MQ_CENTRAL_PILLAR) && logic->CanUse(RG_FIRE_ARROWS));}),
}, {}, {
	Entrance(RR_WATER_TEMPLE_MQ_CENTRAL_PILLAR_HIGH, []{return (logic->MQWaterLevel(WL_HIGH) && (logic->CanUse(RG_FARORES_WIND) && (logic->HasItem(RG_BRONZE_SCALE) || logic->CanUse(RG_IRON_BOOTS))));}),
	Entrance(RR_WATER_TEMPLE_MQ_CENTRAL_PILLAR_B1, []{return (logic->MQWaterOpenedPillarB1 && (logic->MQWaterLevel(WL_MID) && (logic->CanUse(RG_IRON_BOOTS) && logic->CanUse(RG_ZORA_TUNIC))));}),
});
areaTable[RR_WATER_TEMPLE_MQ_CENTRAL_PILLAR_HIGH] = Region("Water Temple MQ Central Pillar High", SCENE_WATER_TEMPLE, false, {RA_WATER_TEMPLE}, {
	EventAccess(&logic->MQWaterOpenedPillarB1, []{return (((logic->CanUse(RG_SONG_OF_TIME) && logic->CanUse(RG_DINS_FIRE)) || ((bool)ctx->GetTrickOption(RT_WATER_MQ_CENTRAL_PILLAR) && logic->CanUse(RG_FIRE_ARROWS))) && (logic->HasItem(RG_BRONZE_SCALE) || (logic->CanUse(RG_IRON_BOOTS) && (logic->CanUse(RG_LONGSHOT) && logic->CanJumpslash()))));}),
}, {
	LOCATION(RC_WATER_TEMPLE_MQ_CENTRAL_PILLAR_UPPER_CRATE_1, logic->CanBreakCrates()),
	LOCATION(RC_WATER_TEMPLE_MQ_CENTRAL_PILLAR_UPPER_CRATE_2, logic->CanBreakCrates()),
}, {
	Entrance(RR_WATER_TEMPLE_MQ_CENTRAL_PILLAR_B1, []{return (logic->MQWaterB1Switch && (logic->CanUse(RG_IRON_BOOTS) && logic->CanUse(RG_ZORA_TUNIC)));}),
});
areaTable[RR_WATER_TEMPLE_MQ_CENTRAL_PILLAR_B1] = Region("Water Temple MQ Central Pillar B1", SCENE_WATER_TEMPLE, false, {RA_WATER_TEMPLE}, {}, {}, {
	Entrance(RR_WATER_TEMPLE_MQ_MAIN, []{return (logic->MQWaterOpenedPillarB1 && (logic->CanUse(RG_IRON_BOOTS) && logic->HasItem(RG_BRONZE_SCALE)));}),
	Entrance(RR_WATER_TEMPLE_MQ_CENTRAL_PILLAR_B1_FINAL, []{return ((logic->IsAdult && logic->CanUse(RG_LONGSHOT)) || (logic->CanUse(RG_HOOKSHOT) && logic->HasItem(RG_BRONZE_SCALE)));}),
});
areaTable[RR_WATER_TEMPLE_MQ_CENTRAL_PILLAR_B1_FINAL] = Region("Water Temple MQ Central Pillar B1 Final", SCENE_WATER_TEMPLE, false, {RA_WATER_TEMPLE}, {}, {
	LOCATION(RC_WATER_TEMPLE_MQ_CENTRAL_PILLAR_CHEST, logic->CanUse(RG_HOOKSHOT)),
	LOCATION(RC_WATER_TEMPLE_MQ_CENTRAL_PILLAR_LOWER_CRATE_1, logic->CanBreakCrates()),
	LOCATION(RC_WATER_TEMPLE_MQ_CENTRAL_PILLAR_LOWER_CRATE_2, logic->CanBreakCrates()),
	LOCATION(RC_WATER_TEMPLE_MQ_CENTRAL_PILLAR_LOWER_CRATE_3, logic->CanBreakCrates()),
	LOCATION(RC_WATER_TEMPLE_MQ_CENTRAL_PILLAR_LOWER_CRATE_4, logic->CanBreakCrates()),
	LOCATION(RC_WATER_TEMPLE_MQ_CENTRAL_PILLAR_LOWER_CRATE_5, logic->CanBreakCrates()),
	LOCATION(RC_WATER_TEMPLE_MQ_CENTRAL_PILLAR_LOWER_CRATE_6, logic->CanBreakCrates()),
	LOCATION(RC_WATER_TEMPLE_MQ_CENTRAL_PILLAR_LOWER_CRATE_7, logic->CanBreakCrates()),
	LOCATION(RC_WATER_TEMPLE_MQ_CENTRAL_PILLAR_LOWER_CRATE_8, logic->CanBreakCrates()),
	LOCATION(RC_WATER_TEMPLE_MQ_CENTRAL_PILLAR_LOWER_CRATE_9, logic->CanBreakCrates()),
	LOCATION(RC_WATER_TEMPLE_MQ_CENTRAL_PILLAR_LOWER_CRATE_10, logic->CanBreakCrates()),
	LOCATION(RC_WATER_TEMPLE_MQ_CENTRAL_PILLAR_LOWER_CRATE_11, logic->CanBreakCrates()),
	LOCATION(RC_WATER_TEMPLE_MQ_CENTRAL_PILLAR_LOWER_CRATE_12, logic->CanBreakCrates()),
	LOCATION(RC_WATER_TEMPLE_MQ_CENTRAL_PILLAR_LOWER_CRATE_13, logic->CanBreakCrates()),
	LOCATION(RC_WATER_TEMPLE_MQ_CENTRAL_PILLAR_LOWER_CRATE_14, logic->CanBreakCrates()),
}, {});
areaTable[RR_WATER_TEMPLE_MQ_BEHIND_BLUE_SWITCH_2F] = Region("Water Temple MQ Behind Blue Switch 2F", SCENE_WATER_TEMPLE, false, {RA_WATER_TEMPLE}, {}, {
	LOCATION(RC_WATER_TEMPLE_MQ_GS_STORAGE_ROOM_POT_1, logic->CanBreakPots()),
	LOCATION(RC_WATER_TEMPLE_MQ_GS_STORAGE_ROOM_POT_2, logic->CanBreakPots()),
	LOCATION(RC_WATER_TEMPLE_MQ_GS_STORAGE_ROOM_POT_3, logic->CanBreakPots()),
	LOCATION(RC_WATER_TEMPLE_MQ_GS_STORAGE_ROOM_LOWER_CRATE_1, logic->CanBreakCrates()),
	LOCATION(RC_WATER_TEMPLE_MQ_GS_STORAGE_ROOM_LOWER_CRATE_2, logic->CanBreakCrates()),
	LOCATION(RC_WATER_TEMPLE_MQ_GS_STORAGE_ROOM_LOWER_CRATE_3, logic->CanBreakCrates()),
	LOCATION(RC_WATER_TEMPLE_MQ_GS_STORAGE_ROOM_LOWER_CRATE_4, logic->CanBreakCrates()),
	LOCATION(RC_WATER_TEMPLE_MQ_GS_STORAGE_ROOM_LOWER_CRATE_5, logic->CanBreakCrates()),
	LOCATION(RC_WATER_TEMPLE_MQ_GS_STORAGE_ROOM_LOWER_CRATE_6, logic->CanBreakCrates()),
	LOCATION(RC_WATER_TEMPLE_MQ_GS_STORAGE_ROOM_LOWER_SMALL_CRATE, logic->CanBreakSmallCrates()),
	LOCATION(RC_WATER_TEMPLE_MQ_GS_STORAGE_ROOM_UPPER_CRATE_1, logic->CanBreakCrates()),
	LOCATION(RC_WATER_TEMPLE_MQ_GS_STORAGE_ROOM_UPPER_CRATE_2, logic->CanBreakCrates()),
	LOCATION(RC_WATER_TEMPLE_MQ_GS_STORAGE_ROOM_UPPER_SMALL_CRATE, logic->CanBreakSmallCrates()),
}, {
	Entrance(RR_WATER_TEMPLE_MQ_MAIN, []{return true;}),
	Entrance(RR_WATER_TEMPLE_MQ_BEHIND_BLUE_SWITCH_3F, []{return logic->CanUse(RG_LONGSHOT);}),
});
areaTable[RR_WATER_TEMPLE_MQ_BEHIND_BLUE_SWITCH_3F] = Region("Water Temple MQ Behind Blue Switch 2F", SCENE_WATER_TEMPLE, false, {RA_WATER_TEMPLE}, {}, {
	LOCATION(RC_WATER_TEMPLE_MQ_GS_BEFORE_UPPER_WATER_SWITCH, logic->CanGetEnemyDrop(RE_GOLD_SKULLTULA)),
}, {
	Entrance(RR_WATER_TEMPLE_MQ_BEHIND_BLUE_SWITCH_2F, []{return true;}),
	Entrance(RR_WATER_TEMPLE_MQ_HIGH_EMBLEM, []{return true;}),
});
areaTable[RR_WATER_TEMPLE_MQ_STORAGE_ROOM] = Region("Water Temple MQ Storage Room", SCENE_WATER_TEMPLE, false, {RA_WATER_TEMPLE}, {}, {
	LOCATION(RC_WATER_TEMPLE_MQ_STORAGE_ROOM_A_POT_1, logic->CanBreakPots()),
	LOCATION(RC_WATER_TEMPLE_MQ_STORAGE_ROOM_A_POT_2, logic->CanBreakPots()),
	LOCATION(RC_WATER_TEMPLE_MQ_STORAGE_ROOM_A_POT_3, logic->CanBreakPots()),
	LOCATION(RC_WATER_TEMPLE_MQ_STORAGE_ROOM_A_CRATE_1, logic->CanBreakCrates()),
	LOCATION(RC_WATER_TEMPLE_MQ_STORAGE_ROOM_A_CRATE_2, logic->CanBreakCrates()),
	LOCATION(RC_WATER_TEMPLE_MQ_STORAGE_ROOM_A_CRATE_3, logic->CanBreakCrates()),
	LOCATION(RC_WATER_TEMPLE_MQ_STORAGE_ROOM_A_CRATE_4, logic->CanBreakCrates()),
	LOCATION(RC_WATER_TEMPLE_MQ_STORAGE_ROOM_A_CRATE_5, logic->CanBreakCrates()),
	LOCATION(RC_WATER_TEMPLE_MQ_STORAGE_ROOM_A_CRATE_6, logic->CanBreakCrates()),
	LOCATION(RC_WATER_TEMPLE_MQ_STORAGE_ROOM_A_CRATE_7, logic->CanBreakCrates()),
	LOCATION(RC_WATER_TEMPLE_MQ_STORAGE_ROOM_A_SMALL_CRATE_1, logic->CanBreakSmallCrates()),
	LOCATION(RC_WATER_TEMPLE_MQ_STORAGE_ROOM_A_SMALL_CRATE_2, logic->CanBreakSmallCrates()),
	LOCATION(RC_WATER_TEMPLE_MQ_STORAGE_ROOM_A_SMALL_CRATE_3, logic->CanBreakSmallCrates()),
	LOCATION(RC_WATER_TEMPLE_MQ_STORAGE_ROOM_A_SMALL_CRATE_4, logic->CanBreakSmallCrates()),
}, {
	Entrance(RR_WATER_TEMPLE_MQ_MAIN, []{return (logic->MQWaterLevel(WL_LOW_OR_MID) || (logic->CanUse(RG_IRON_BOOTS) && (logic->WaterTimer() >= 8)));}),
});
areaTable[RR_WATER_TEMPLE_MQ_LIZALFOS_HALLWAY] = Region("Water Temple MQ Lizalfos Hallway", SCENE_WATER_TEMPLE, false, {RA_WATER_TEMPLE}, {}, {
	LOCATION(RC_WATER_TEMPLE_MQ_LIZALFOS_HALLWAY_WEST_POT, logic->CanBreakPots()),
	LOCATION(RC_WATER_TEMPLE_MQ_LIZALFOS_HALLWAY_SOUTH_POT, logic->CanBreakPots()),
	LOCATION(RC_WATER_TEMPLE_MQ_LIZALFOS_HALLWAY_SE_POT, logic->CanBreakPots()),
	LOCATION(RC_WATER_TEMPLE_MQ_LIZALFOS_HALLWAY_CRATE_1, logic->CanBreakCrates()),
	LOCATION(RC_WATER_TEMPLE_MQ_LIZALFOS_HALLWAY_CRATE_2, logic->CanBreakCrates()),
	LOCATION(RC_WATER_TEMPLE_MQ_LIZALFOS_HALLWAY_CRATE_3, logic->CanBreakCrates()),
	LOCATION(RC_WATER_TEMPLE_MQ_LIZALFOS_HALLWAY_ROOM_CRATE_1, logic->CanBreakCrates()),
	LOCATION(RC_WATER_TEMPLE_MQ_LIZALFOS_HALLWAY_ROOM_CRATE_2, logic->CanBreakCrates()),
	LOCATION(RC_WATER_TEMPLE_MQ_LIZALFOS_HALLWAY_ROOM_CRATE_3, logic->CanBreakCrates()),
	LOCATION(RC_WATER_TEMPLE_MQ_LIZALFOS_HALLWAY_ROOM_CRATE_4, logic->CanBreakCrates()),
	LOCATION(RC_WATER_TEMPLE_MQ_LIZALFOS_HALLWAY_ROOM_CRATE_5, logic->CanBreakCrates()),
}, {
	Entrance(RR_WATER_TEMPLE_MQ_LIZALFOS_CAGE, []{return (logic->MQWaterLevel(WL_LOW_OR_MID) && logic->CanUse(RG_DINS_FIRE));}),
});
areaTable[RR_WATER_TEMPLE_MQ_LIZALFOS_CAGE] = Region("Water Temple MQ Lizalfos Cage", SCENE_WATER_TEMPLE, false, {RA_WATER_TEMPLE}, {}, {
	LOCATION(RC_WATER_TEMPLE_MQ_GS_LIZALFOS_HALLWAY, logic->CanKillEnemy(RE_GOLD_SKULLTULA)),
	LOCATION(RC_WATER_TEMPLE_MQ_LIZALFOS_CAGE_SOUTH_POT, logic->CanBreakPots()),
	LOCATION(RC_WATER_TEMPLE_MQ_LIZALFOS_CAGE_NORTH_POT, logic->CanBreakPots()),
	LOCATION(RC_WATER_TEMPLE_MQ_LIZALFOS_HALLWAY_GATE_CRATE_1, logic->CanBreakCrates()),
	LOCATION(RC_WATER_TEMPLE_MQ_LIZALFOS_HALLWAY_GATE_CRATE_2, logic->CanBreakCrates()),
}, {});
areaTable[RR_WATER_TEMPLE_MQ_3F_EAST_LEDGE] = Region("Invalid Region", SCENE_ID_MAX, false, {}, {}, {}, {});
areaTable[RR_WATER_TEMPLE_MQ_WATERFALL] = Region("Water Temple Waterfall", SCENE_WATER_TEMPLE, false, {RA_WATER_TEMPLE}, {}, {}, {
	Entrance(RR_WATER_TEMPLE_MQ_3F_CENTRAL, []{return (logic->SmallKeys(RR_WATER_TEMPLE, 1) && logic->CanUse(RG_LONGSHOT));}),
	Entrance(RR_WATER_TEMPLE_MQ_STALFOS_PIT, []{return true;}),
	Entrance(RR_WATER_TEMPLE_MQ_STALFOS_PIT_POTS, []{return ((logic->MQWaterStalfosPit && (logic->IsAdult && logic->CanUse(RG_HOOKSHOT))) || logic->CanUse(RG_HOVER_BOOTS));}),
	Entrance(RR_WATER_TEMPLE_MQ_STALFOS_PIT_UPPER, []{return (logic->MQWaterStalfosPit && logic->CanUse(RG_LONGSHOT));}),
});
areaTable[RR_WATER_TEMPLE_MQ_STALFOS_PIT] = Region("Water Temple MQ Stalfos Pit", SCENE_WATER_TEMPLE, false, {RA_WATER_TEMPLE}, {
	EventAccess(&logic->MQWaterStalfosPit, []{return ((logic->IsAdult && logic->CanKillEnemy(RE_STALFOS, ED_CLOSE, true, 3, false, true)) || (logic->CanUse(RG_IRON_BOOTS) && (logic->CanUse(RG_HOOKSHOT) && logic->CanKillEnemy(RE_STALFOS, ED_BOMB_THROW, true, 3, false, true))));}),
}, {}, {
	Entrance(RR_WATER_TEMPLE_MQ_WATERFALL, []{return (logic->MQWaterStalfosPit && (logic->CanUse(RG_HOOKSHOT) && (logic->IsAdult || (logic->CanUse(RG_IRON_BOOTS) && (logic->WaterTimer() >= 8)))));}),
	Entrance(RR_WATER_TEMPLE_MQ_STALFOS_PIT_POTS, []{return ((logic->IsAdult && logic->CanUse(RG_HOOKSHOT)) || (logic->CanUse(RG_HOOKSHOT) && ((logic->IsAdult || (logic->CanUse(RG_IRON_BOOTS) && (logic->WaterTimer() >= 8))) && (logic->CanUse(RG_HOVER_BOOTS) || logic->MQWaterStalfosPit))));}),
	Entrance(RR_WATER_TEMPLE_MQ_STALFOS_PIT_UPPER, []{return (logic->MQWaterStalfosPit && ((logic->IsAdult || (logic->CanUse(RG_IRON_BOOTS) && (logic->WaterTimer() >= 8))) && logic->CanUse(RG_HOOKSHOT)));}),
});
areaTable[RR_WATER_TEMPLE_MQ_STALFOS_PIT_POTS] = Region("Water Temple MQ Stalfos Pit Pots", SCENE_WATER_TEMPLE, false, {RA_WATER_TEMPLE}, {
	EventAccess(&logic->FairyPot, []{return true;}),
	EventAccess(&logic->NutPot, []{return true;}),
}, {
	LOCATION(RC_WATER_TEMPLE_MQ_STALFOS_PIT_SOUTH_POT, logic->CanBreakPots()),
	LOCATION(RC_WATER_TEMPLE_MQ_STALFOS_PIT_MIDDLE_POT, logic->CanBreakPots()),
	LOCATION(RC_WATER_TEMPLE_MQ_STALFOS_PIT_NORTH_POT, logic->CanBreakPots()),
	LOCATION(RC_WATER_TEMPLE_MQ_DARK_LINK_PILAR_SUN_FAIRY, logic->CanUse(RG_SUNS_SONG)),
}, {
	Entrance(RR_WATER_TEMPLE_MQ_WATERFALL, []{return (logic->MQWaterStalfosPit && (logic->CanUse(RG_HOVER_BOOTS) || logic->CanUse(RG_LONGSHOT)));}),
	Entrance(RR_WATER_TEMPLE_MQ_STALFOS_PIT, []{return true;}),
	Entrance(RR_WATER_TEMPLE_MQ_STALFOS_PIT_UPPER, []{return (logic->MQWaterStalfosPit && logic->CanUse(RG_HOOKSHOT));}),
});
areaTable[RR_WATER_TEMPLE_MQ_STALFOS_PIT_UPPER] = Region("Water Temple MQ Stalfos Pit Upper", SCENE_WATER_TEMPLE, false, {RA_WATER_TEMPLE}, {}, {
	LOCATION(RC_WATER_TEMPLE_MQ_BEFORE_DARK_LINK_POT_1, logic->CanBreakPots()),
	LOCATION(RC_WATER_TEMPLE_MQ_BEFORE_DARK_LINK_POT_2, logic->CanBreakPots()),
	LOCATION(RC_WATER_TEMPLE_MQ_DARK_LINK_LEFT_STORM_FAIRY, logic->CanUse(RG_SONG_OF_STORMS)),
	LOCATION(RC_WATER_TEMPLE_MQ_DARK_LINK_RIGHT_SUN_FAIRY, logic->CanUse(RG_SUNS_SONG)),
}, {
	Entrance(RR_WATER_TEMPLE_MQ_STALFOS_PIT, []{return (logic->IsAdult || logic->TakeDamage());}),
	Entrance(RR_WATER_TEMPLE_MQ_STALFOS_PIT_POTS, []{return (logic->IsAdult || logic->TakeDamage());}),
	Entrance(RR_WATER_TEMPLE_MQ_AFTER_DARK_LINK, []{return logic->CanKillEnemy(RE_DARK_LINK);}),
});
areaTable[RR_WATER_TEMPLE_MQ_AFTER_DARK_LINK] = Region("Water Temple MQ After Dark Link", SCENE_WATER_TEMPLE, false, {RA_WATER_TEMPLE}, {
	EventAccess(&logic->FairyPot, []{return true;}),
}, {
	LOCATION(RC_WATER_TEMPLE_MQ_AFTER_DARK_LINK_POT_1, logic->CanBreakPots()),
	LOCATION(RC_WATER_TEMPLE_MQ_AFTER_DARK_LINK_POT_2, logic->CanBreakPots()),
}, {
	Entrance(RR_WATER_TEMPLE_MQ_STALFOS_PIT_UPPER, []{return logic->CanKillEnemy(RE_DARK_LINK);}),
	Entrance(RR_WATER_TEMPLE_MQ_RIVER_SKULL, []{return (logic->CanUse(RG_HOOKSHOT) && (logic->HasItem(RG_BRONZE_SCALE) || ((logic->CanUse(RG_IRON_BOOTS) && (logic->WaterTimer() >= 8)) || logic->CanUse(RG_LONGSHOT))));}),
});
areaTable[RR_WATER_TEMPLE_MQ_RIVER_SKULL] = Region("Water Temple MQ River Skull", SCENE_WATER_TEMPLE, false, {RA_WATER_TEMPLE}, {}, {
	LOCATION(RC_WATER_TEMPLE_MQ_GS_RIVER, (logic->CanUse(RG_LONGSHOT) || (logic->CanUse(RG_IRON_BOOTS) && logic->CanUse(RG_HOOKSHOT)))),
}, {
	Entrance(RR_WATER_TEMPLE_MQ_RIVER_POTS, []{return (logic->HasItem(RG_BRONZE_SCALE) || logic->CanUse(RG_LONGSHOT));}),
});
areaTable[RR_WATER_TEMPLE_MQ_RIVER_POTS] = Region("Water Temple MQ River Pots", SCENE_WATER_TEMPLE, false, {RA_WATER_TEMPLE}, {
	EventAccess(&logic->FairyPot, []{return true;}),
}, {
	LOCATION(RC_WATER_TEMPLE_MQ_RIVER_POT_1, logic->CanBreakPots()),
	LOCATION(RC_WATER_TEMPLE_MQ_RIVER_POT_2, logic->CanBreakPots()),
}, {
	Entrance(RR_WATER_TEMPLE_MQ_RIVER_SKULL, []{return (logic->CanUse(RG_LONGSHOT) || (logic->CanUse(RG_IRON_BOOTS) && ((logic->WaterTimer() >= 8) && logic->CanUse(RG_HOOKSHOT))));}),
	Entrance(RR_WATER_TEMPLE_MQ_DRAGON_ROOM_TUNNEL, []{return (logic->CanUse(RG_IRON_BOOTS) && (logic->WaterTimer() >= 16));}),
	Entrance(RR_WATER_TEMPLE_MQ_DRAGON_ROOM_ALCOVE, []{return (logic->HasItem(RG_SILVER_SCALE) || (logic->IsAdult && (logic->HasItem(RG_BRONZE_SCALE) && (bool)ctx->GetTrickOption(RT_WATER_DRAGON_JUMP_DIVE))));}),
	Entrance(RR_WATER_TEMPLE_MQ_DRAGON_ROOM_DOOR, []{return (logic->HasItem(RG_BRONZE_SCALE) || (logic->CanUse(RG_LONGSHOT) || (logic->CanUse(RG_HOVER_BOOTS) && logic->CanJumpslash())));}),
});
areaTable[RR_WATER_TEMPLE_MQ_DRAGON_ROOM_DOOR] = Region("Water Temple MQ Dragon Room Door", SCENE_WATER_TEMPLE, false, {RA_WATER_TEMPLE}, {}, {
	LOCATION(RC_WATER_TEMPLE_MQ_DRAGON_ROOM_DOOR_CRATE_1, logic->CanBreakCrates()),
	LOCATION(RC_WATER_TEMPLE_MQ_DRAGON_ROOM_DOOR_CRATE_2, logic->CanBreakCrates()),
}, {
	Entrance(RR_WATER_TEMPLE_MQ_RIVER_POTS, []{return logic->CanUse(RG_LONGSHOT);}),
	Entrance(RR_WATER_TEMPLE_MQ_DRAGON_ROOM_TUNNEL, []{return (logic->CanUse(RG_IRON_BOOTS) && ((logic->WaterTimer() >= 16) && logic->CanUse(RG_HOOKSHOT)));}),
	Entrance(RR_WATER_TEMPLE_MQ_DRAGON_ROOM_ALCOVE, []{return logic->HasItem(RG_SILVER_SCALE);}),
	Entrance(RR_WATER_TEMPLE_MQ_BOSS_KEY_ROOM_SWITCH, []{return logic->MQWaterDragonTorches;}),
});
areaTable[RR_WATER_TEMPLE_MQ_DRAGON_ROOM_TUNNEL] = Region("Water Temple MQ Dragon Room Tunnel", SCENE_WATER_TEMPLE, false, {RA_WATER_TEMPLE}, {}, {
	LOCATION(RC_WATER_TEMPLE_MQ_DRAGON_ROOM_SUBMERGED_CRATE_1, logic->CanBreakCrates()),
	LOCATION(RC_WATER_TEMPLE_MQ_DRAGON_ROOM_SUBMERGED_CRATE_2, logic->CanBreakCrates()),
	LOCATION(RC_WATER_TEMPLE_MQ_DRAGON_ROOM_SUBMERGED_CRATE_3, logic->CanBreakCrates()),
	LOCATION(RC_WATER_TEMPLE_MQ_DRAGON_ROOM_SUBMERGED_CRATE_4, logic->CanBreakCrates()),
}, {
	Entrance(RR_WATER_TEMPLE_MQ_RIVER_POTS, []{return logic->CanUse(RG_LONGSHOT);}),
	Entrance(RR_WATER_TEMPLE_MQ_DRAGON_ROOM_ALCOVE, []{return (logic->HasItem(RG_BRONZE_SCALE) || logic->CanUse(RG_HOOKSHOT));}),
	Entrance(RR_WATER_TEMPLE_MQ_DRAGON_ROOM_DOOR, []{return (logic->HasItem(RG_BRONZE_SCALE) || logic->CanUse(RG_LONGSHOT));}),
});
areaTable[RR_WATER_TEMPLE_MQ_DRAGON_ROOM_ALCOVE] = Region("Water Temple MQ Dragon Room Alcove", SCENE_WATER_TEMPLE, false, {RA_WATER_TEMPLE}, {
	EventAccess(&logic->MQWaterDragonTorches, []{return logic->HasFireSource();}),
}, {
	LOCATION(RC_WATER_TEMPLE_MQ_DRAGON_ROOM_TORCHES_CRATE_1, logic->CanBreakCrates()),
	LOCATION(RC_WATER_TEMPLE_MQ_DRAGON_ROOM_TORCHES_CRATE_2, logic->CanBreakCrates()),
	LOCATION(RC_WATER_TEMPLE_MQ_DRAGON_ROOM_TORCHES_SMALL_CRATE_1, logic->CanBreakSmallCrates()),
	LOCATION(RC_WATER_TEMPLE_MQ_DRAGON_ROOM_TORCHES_SMALL_CRATE_2, logic->CanBreakSmallCrates()),
	LOCATION(RC_WATER_TEMPLE_MQ_DRAGON_ROOM_TORCHES_SMALL_CRATE_3, logic->CanBreakSmallCrates()),
}, {
	Entrance(RR_WATER_TEMPLE_MQ_DRAGON_ROOM_TUNNEL, []{return (logic->CanUse(RG_IRON_BOOTS) && (logic->WaterTimer() >= 16));}),
	Entrance(RR_WATER_TEMPLE_MQ_DRAGON_ROOM_DOOR, []{return logic->HasItem(RG_SILVER_SCALE);}),
});
areaTable[RR_WATER_TEMPLE_MQ_BOSS_KEY_ROOM_SWITCH] = Region("Water Temple MQ Boss Key Room Switch", SCENE_WATER_TEMPLE, false, {RA_WATER_TEMPLE}, {}, {
	LOCATION(RC_WATER_TEMPLE_MQ_BOSS_KEY_POT, logic->CanBreakPots()),
	LOCATION(RC_WATER_TEMPLE_MQ_BK_ROOM_UPPER_CRATE, logic->CanBreakCrates()),
}, {
	Entrance(RR_WATER_TEMPLE_MQ_DRAGON_ROOM_DOOR, []{return true;}),
	Entrance(RR_WATER_TEMPLE_MQ_BOSS_KEY_ROOM_PIT, []{return true;}),
	Entrance(RR_WATER_TEMPLE_MQ_BOSS_KEY_ROOM_CHEST, []{return (logic->CanHitSwitch() && Here(RR_WATER_TEMPLE_MQ_BOSS_KEY_ROOM_SWITCH, []{return logic->CanUse(RG_DINS_FIRE);}));}),
});
areaTable[RR_WATER_TEMPLE_MQ_BOSS_KEY_ROOM_PIT] = Region("Water Temple MQ Boss Key Room Pit", SCENE_WATER_TEMPLE, false, {RA_WATER_TEMPLE}, {}, {
	LOCATION(RC_WATER_TEMPLE_MQ_BK_ROOM_LOWER_CRATE_1, logic->CanBreakCrates()),
	LOCATION(RC_WATER_TEMPLE_MQ_BK_ROOM_LOWER_CRATE_2, logic->CanBreakCrates()),
	LOCATION(RC_WATER_TEMPLE_MQ_BK_ROOM_LOWER_CRATE_3, logic->CanBreakCrates()),
	LOCATION(RC_WATER_TEMPLE_MQ_BK_ROOM_LOWER_CRATE_4, logic->CanBreakCrates()),
}, {
	Entrance(RR_WATER_TEMPLE_MQ_BOSS_KEY_ROOM_SWITCH, []{return logic->CanHitSwitch(ED_BOOMERANG);}),
});
areaTable[RR_WATER_TEMPLE_MQ_BOSS_KEY_ROOM_CHEST] = Region("Water Temple MQ Boss Key Room Chest", SCENE_WATER_TEMPLE, false, {RA_WATER_TEMPLE}, {}, {
	LOCATION(RC_WATER_TEMPLE_MQ_BOSS_KEY_CHEST, true),
}, {
	Entrance(RR_WATER_TEMPLE_MQ_BOSS_KEY_ROOM_SWITCH, []{return (logic->CanHitSwitch(ED_BOMB_THROW) || logic->CanUse(RG_HOVER_BOOTS));}),
	Entrance(RR_WATER_TEMPLE_MQ_BOSS_KEY_ROOM_PIT, []{return true;}),
	Entrance(RR_WATER_TEMPLE_MQ_B1_GATE_SWITCH, []{return (logic->HasItem(RG_SILVER_SCALE) || (logic->CanUse(RG_IRON_BOOTS) && (logic->HasItem(RG_BRONZE_SCALE) || ((logic->WaterTimer() >= 24) && logic->CanUse(RG_LONGSHOT)))));}),
});
areaTable[RR_WATER_TEMPLE_MQ_B1_GATE_SWITCH] = Region("Water Temple MQ B1 Gate Switch", SCENE_WATER_TEMPLE, false, {RA_WATER_TEMPLE}, {
	EventAccess(&logic->MQWaterB1Switch, []{return logic->CanUse(RG_IRON_BOOTS);}),
}, {}, {
	Entrance(RR_WATER_TEMPLE_MQ_MAIN, []{return (logic->MQWaterB1Switch && (logic->MQWaterLevel(WL_LOW) || (logic->CanUse(RG_IRON_BOOTS) && (logic->WaterTimer() >= 16))));}),
	Entrance(RR_WATER_TEMPLE_MQ_BOSS_KEY_ROOM_CHEST, []{return (logic->CanUse(RG_IRON_BOOTS) && (logic->HasItem(RG_BRONZE_SCALE) && (logic->MQWaterLevel(WL_LOW) || (logic->WaterTimer() >= 24))));}),
});
areaTable[RR_WATER_TEMPLE_MQ_TRIANGLE_TORCH_ROOM] = Region("Water Temple MQ Triangle Torch Room", SCENE_WATER_TEMPLE, false, {RA_WATER_TEMPLE}, {}, {
	LOCATION(RC_WATER_TEMPLE_MQ_TRIPLE_TORCH_ROOM_SUBMERGED_CRATE_1, (logic->CanUse(RG_IRON_BOOTS) && ((logic->WaterTimer() >= 16) && logic->CanBreakCrates()))),
	LOCATION(RC_WATER_TEMPLE_MQ_TRIPLE_TORCH_ROOM_SUBMERGED_CRATE_2, (logic->CanUse(RG_IRON_BOOTS) && ((logic->WaterTimer() >= 16) && logic->CanBreakCrates()))),
	LOCATION(RC_WATER_TEMPLE_MQ_TRIPLE_TORCH_ROOM_SUBMERGED_CRATE_3, (logic->CanUse(RG_IRON_BOOTS) && ((logic->WaterTimer() >= 16) && logic->CanBreakCrates()))),
	LOCATION(RC_WATER_TEMPLE_MQ_TRIPLE_TORCH_ROOM_SUBMERGED_CRATE_4, (logic->CanUse(RG_IRON_BOOTS) && ((logic->WaterTimer() >= 16) && logic->CanBreakCrates()))),
	LOCATION(RC_WATER_TEMPLE_MQ_TRIPLE_TORCH_ROOM_SUBMERGED_CRATE_5, (logic->CanUse(RG_IRON_BOOTS) && ((logic->WaterTimer() >= 16) && logic->CanBreakCrates()))),
	LOCATION(RC_WATER_TEMPLE_MQ_TRIPLE_TORCH_ROOM_SUBMERGED_CRATE_6, (logic->CanUse(RG_IRON_BOOTS) && ((logic->WaterTimer() >= 16) && logic->CanBreakCrates()))),
}, {
	Entrance(RR_WATER_TEMPLE_MQ_MAIN, []{return (logic->MQWaterB1Switch && ((logic->MQWaterLevel(WL_LOW) && logic->HasItem(RG_GOLDEN_SCALE)) || (logic->CanUse(RG_IRON_BOOTS) && ((logic->WaterTimer() >= 40) && (logic->HasItem(RG_BRONZE_SCALE) || logic->CanUse(RG_LONGSHOT))))));}),
	Entrance(RR_WATER_TEMPLE_MQ_TRIANGLE_TORCH_CAGE, []{return (logic->CanUse(RG_FIRE_ARROWS) && ((logic->IsAdult && logic->CanUse(RG_HOVER_BOOTS)) || (logic->CanUse(RG_LONGSHOT) && Here(RR_WATER_TEMPLE_MQ_TRIANGLE_TORCH_ROOM, []{return logic->ScarecrowsSong();}))));}),
});
areaTable[RR_WATER_TEMPLE_MQ_TRIANGLE_TORCH_CAGE] = Region("Water Temple MQ Triangle Torch Cage", SCENE_WATER_TEMPLE, false, {RA_WATER_TEMPLE}, {}, {
	LOCATION(RC_WATER_TEMPLE_MQ_GS_TRIPLE_WALL_TORCH, logic->CanGetEnemyDrop(RE_GOLD_SKULLTULA, ED_BOOMERANG)),
	LOCATION(RC_WATER_TEMPLE_MQ_LOWEST_GS_POT_1, logic->CanBreakPots()),
	LOCATION(RC_WATER_TEMPLE_MQ_LOWEST_GS_POT_2, logic->CanBreakPots()),
	LOCATION(RC_WATER_TEMPLE_MQ_LOWEST_GS_POT_3, logic->CanBreakPots()),
	LOCATION(RC_WATER_TEMPLE_MQ_LOWEST_GS_POT_4, logic->CanBreakPots()),
	LOCATION(RC_WATER_TEMPLE_MQ_TRIPLE_TORCH_ROOM_GATE_CRATE_3, logic->CanBreakCrates()),
	LOCATION(RC_WATER_TEMPLE_MQ_TRIPLE_TORCH_ROOM_GATE_CRATE_1, logic->CanBreakCrates()),
	LOCATION(RC_WATER_TEMPLE_MQ_TRIPLE_TORCH_ROOM_GATE_CRATE_2, logic->CanBreakCrates()),
}, {});
areaTable[RR_WATER_TEMPLE_MQ_CRATES_WHIRLPOOLS_ROOM] = Region("Water Temple MQ Crates Whirlpools Room", SCENE_WATER_TEMPLE, false, {RA_WATER_TEMPLE}, {}, {
	LOCATION(RC_WATER_TEMPLE_MQ_WHIRLPOOL_FRONT_CRATE_1, logic->CanBreakCrates()),
	LOCATION(RC_WATER_TEMPLE_MQ_WHIRLPOOL_FRONT_CRATE_2, logic->CanBreakCrates()),
	LOCATION(RC_WATER_TEMPLE_MQ_WHIRLPOOL_SUBMERGED_CRATE_1, (logic->CanUse(RG_IRON_BOOTS) && ((logic->WaterTimer() >= 16) && logic->CanBreakCrates()))),
	LOCATION(RC_WATER_TEMPLE_MQ_WHIRLPOOL_SUBMERGED_CRATE_2, (logic->CanUse(RG_IRON_BOOTS) && ((logic->WaterTimer() >= 16) && logic->CanBreakCrates()))),
	LOCATION(RC_WATER_TEMPLE_MQ_WHIRLPOOL_SUBMERGED_CRATE_3, (logic->CanUse(RG_IRON_BOOTS) && ((logic->WaterTimer() >= 16) && logic->CanBreakCrates()))),
	LOCATION(RC_WATER_TEMPLE_MQ_WHIRLPOOL_SUBMERGED_CRATE_4, (logic->CanUse(RG_IRON_BOOTS) && ((logic->WaterTimer() >= 16) && logic->CanBreakCrates()))),
	LOCATION(RC_WATER_TEMPLE_MQ_WHIRLPOOL_SUBMERGED_CRATE_5, (logic->CanUse(RG_IRON_BOOTS) && ((logic->WaterTimer() >= 16) && logic->CanBreakCrates()))),
	LOCATION(RC_WATER_TEMPLE_MQ_WHIRLPOOL_SUBMERGED_CRATE_6, (logic->CanUse(RG_IRON_BOOTS) && ((logic->WaterTimer() >= 16) && logic->CanBreakCrates()))),
}, {
	Entrance(RR_WATER_TEMPLE_MQ_MAIN, []{return (logic->MQWaterB1Switch && (logic->CanUse(RG_IRON_BOOTS) && ((logic->WaterTimer() >= 24) && (logic->CanUse(RG_LONGSHOT) || logic->HasItem(RG_BRONZE_SCALE)))));}),
	Entrance(RR_WATER_TEMPLE_MQ_SINGLE_STALFOS_ROOM, []{return (logic->CanUse(RG_IRON_BOOTS) && ((logic->WaterTimer() >= 8) && ((logic->IsAdult && ((logic->CanUse(RG_HOVER_BOOTS) || (bool)ctx->GetTrickOption(RT_WATER_NORTH_BASEMENT_LEDGE_JUMP)) && (logic->CanUse(RG_HOOKSHOT) || logic->HasItem(RG_BRONZE_SCALE)))) || (Here(RR_WATER_TEMPLE_MQ_CRATES_WHIRLPOOLS_ROOM, []{return logic->ScarecrowsSong();}) && logic->CanUse(RG_HOOKSHOT)))));}),
	Entrance(RR_WATER_TEMPLE_MQ_4_TORCH_ROOM, []{return (logic->IsAdult && (logic->CanUse(RG_HOVER_BOOTS) || ((bool)ctx->GetTrickOption(RT_WATER_NORTH_BASEMENT_LEDGE_JUMP) || (Here(RR_WATER_TEMPLE_MQ_CRATES_WHIRLPOOLS_ROOM, []{return logic->ScarecrowsSong();}) && logic->CanUse(RG_HOOKSHOT)))));}),
	Entrance(RR_WATER_TEMPLE_MQ_CRATES_WHIRLPOOLS_CAGE, []{return ((bool)ctx->GetTrickOption(RT_WATER_MQ_LOCKED_GS) && (logic->CanUse(RG_IRON_BOOTS) && logic->CanUse(RG_HOOKSHOT)));}),
});
areaTable[RR_WATER_TEMPLE_MQ_SINGLE_STALFOS_ROOM] = Region("Water Temple MQ Single Stalfos Room", SCENE_WATER_TEMPLE, false, {RA_WATER_TEMPLE}, {}, {
	LOCATION(RC_WATER_TEMPLE_MQ_FREESTANDING_KEY, logic->CanBreakCrates()),
	LOCATION(RC_WATER_TEMPLE_MQ_STORAGE_ROOM_B_POT_1, logic->CanBreakPots()),
	LOCATION(RC_WATER_TEMPLE_MQ_STORAGE_ROOM_B_POT_2, logic->CanBreakPots()),
	LOCATION(RC_WATER_TEMPLE_MQ_STORAGE_ROOM_B_CRATE_1, logic->CanBreakCrates()),
	LOCATION(RC_WATER_TEMPLE_MQ_STORAGE_ROOM_B_CRATE_2, logic->CanBreakCrates()),
	LOCATION(RC_WATER_TEMPLE_MQ_STORAGE_ROOM_B_CRATE_3, logic->CanBreakCrates()),
	LOCATION(RC_WATER_TEMPLE_MQ_STORAGE_ROOM_B_CRATE_4, logic->CanBreakCrates()),
	LOCATION(RC_WATER_TEMPLE_MQ_STORAGE_ROOM_B_CRATE_5, logic->CanBreakCrates()),
}, {
	Entrance(RR_WATER_TEMPLE_MQ_CRATES_WHIRLPOOLS_ROOM, []{return (logic->HasItem(RG_SILVER_SCALE) || ((logic->IsChild && logic->HasItem(RG_BRONZE_SCALE)) || (logic->CanUse(RG_IRON_BOOTS) && ((logic->WaterTimer() >= 8) && (logic->HasItem(RG_BRONZE_SCALE) || logic->CanUse(RG_HOOKSHOT))))));}),
});
areaTable[RR_WATER_TEMPLE_MQ_4_TORCH_ROOM] = Region("Water Temple MQ 4 Torch Room", SCENE_WATER_TEMPLE, false, {RA_WATER_TEMPLE}, {}, {}, {
	Entrance(RR_WATER_TEMPLE_MQ_CRATES_WHIRLPOOLS_ROOM, []{return ((logic->IsAdult && (logic->CanUse(RG_HOVER_BOOTS) || logic->CanJumpslash())) || (logic->HasItem(RG_BRONZE_SCALE) || (logic->CanUse(RG_IRON_BOOTS) && ((logic->WaterTimer() >= 8) && logic->CanUse(RG_HOOKSHOT)))));}),
	Entrance(RR_WATER_TEMPLE_MQ_DODONGO_ROOM, []{return (logic->CanHitSwitch() && logic->HasFireSource());}),
});
areaTable[RR_WATER_TEMPLE_MQ_DODONGO_ROOM] = Region("Water Temple MQ Dodongo Room", SCENE_WATER_TEMPLE, false, {RA_WATER_TEMPLE}, {}, {
	LOCATION(RC_WATER_TEMPLE_MQ_MINI_DODONGO_POT_1, logic->CanBreakPots()),
	LOCATION(RC_WATER_TEMPLE_MQ_MINI_DODONGO_POT_2, logic->CanBreakPots()),
	LOCATION(RC_WATER_TEMPLE_MQ_DODONGO_ROOM_UPPER_CRATE, logic->CanBreakCrates()),
	LOCATION(RC_WATER_TEMPLE_MQ_DODONGO_ROOM_HALL_CRATE, logic->CanBreakCrates()),
	LOCATION(RC_WATER_TEMPLE_MQ_DODONGO_ROOM_LOWER_CRATE_1, logic->CanBreakCrates()),
	LOCATION(RC_WATER_TEMPLE_MQ_DODONGO_ROOM_LOWER_CRATE_2, logic->CanBreakCrates()),
	LOCATION(RC_WATER_TEMPLE_MQ_DODONGO_ROOM_LOWER_CRATE_3, logic->CanBreakCrates()),
}, {
	Entrance(RR_WATER_TEMPLE_MQ_4_TORCH_ROOM, []{return ((logic->CanUse(RG_HOOKSHOT) || logic->CanUse(RG_HOVER_BOOTS)) && Here(RR_WATER_TEMPLE_MQ_DODONGO_ROOM, []{return logic->CanKillEnemy(RE_DODONGO, ED_CLOSE, true, 5);}));}),
	Entrance(RR_WATER_TEMPLE_MQ_CRATES_WHIRLPOOLS_CAGE, []{return ((logic->CanUse(RG_HOOKSHOT) || logic->CanUse(RG_HOVER_BOOTS)) && Here(RR_WATER_TEMPLE_MQ_DODONGO_ROOM, []{return logic->CanKillEnemy(RE_DODONGO, ED_CLOSE, true, 5);}));}),
});
areaTable[RR_WATER_TEMPLE_MQ_CRATES_WHIRLPOOLS_CAGE] = Region("Water Temple MQ Basement Gated Areas", SCENE_WATER_TEMPLE, false, {RA_WATER_TEMPLE}, {}, {
	LOCATION(RC_WATER_TEMPLE_MQ_GS_FREESTANDING_KEY_AREA, (logic->CanGetEnemyDrop(RE_GOLD_SKULLTULA) && logic->CanBreakCrates())),
	LOCATION(RC_WATER_TEMPLE_MQ_WHIRLPOOL_BEHIND_GATE_CRATE_1, logic->CanBreakCrates()),
	LOCATION(RC_WATER_TEMPLE_MQ_WHIRLPOOL_BEHIND_GATE_CRATE_2, logic->CanBreakCrates()),
	LOCATION(RC_WATER_TEMPLE_MQ_WHIRLPOOL_BEHIND_GATE_CRATE_3, logic->CanBreakCrates()),
	LOCATION(RC_WATER_TEMPLE_MQ_WHIRLPOOL_BEHIND_GATE_CRATE_4, logic->CanBreakCrates()),
}, {
	Entrance(RR_WATER_TEMPLE_MQ_DODONGO_ROOM, []{return true;}),
});
areaTable[RR_WATER_TEMPLE_BOSS_ENTRYWAY] = Region("Water Temple Boss Entryway", SCENE_WATER_TEMPLE, false, {RA_WATER_TEMPLE}, {}, {}, {
	Entrance(RR_WATER_TEMPLE_PRE_BOSS_ROOM, []{return (ctx->GetDungeon(Rando::WATER_TEMPLE)->IsVanilla() && false);}),
	Entrance(RR_WATER_TEMPLE_MQ_BOSS_DOOR, []{return (ctx->GetDungeon(Rando::WATER_TEMPLE)->IsMQ() && false);}),
	Entrance(RR_WATER_TEMPLE_BOSS_ROOM, []{return logic->HasItem(RG_WATER_TEMPLE_BOSS_KEY);}),
});
areaTable[RR_WATER_TEMPLE_BOSS_ROOM] = Region("Water Temple Boss Room", SCENE_WATER_TEMPLE_BOSS, false, {}, {
	EventAccess(&logic->WaterTempleClear, []{return logic->CanKillEnemy(RE_MORPHA);}),
}, {
	LOCATION(RC_WATER_TEMPLE_MORPHA_HEART, logic->WaterTempleClear),
	LOCATION(RC_MORPHA, logic->WaterTempleClear),
}, {
	Entrance(RR_WATER_TEMPLE_BOSS_ENTRYWAY, []{return false;}),
	Entrance(RR_LAKE_HYLIA, []{return logic->WaterTempleClear;}, "", false),
});
areaTable[RR_SPIRIT_TEMPLE_LOBBY] = Region("Spirit Temple Lobby", SCENE_SPIRIT_TEMPLE, false, {RA_SPIRIT_TEMPLE}, {}, {
	LOCATION(RC_SPIRIT_TEMPLE_LOBBY_POT_1, logic->CanBreakPots()),
	LOCATION(RC_SPIRIT_TEMPLE_LOBBY_POT_2, logic->CanBreakPots()),
}, {
	Entrance(RR_SPIRIT_TEMPLE_ENTRYWAY, []{return true;}),
	Entrance(RR_SPIRIT_TEMPLE_CHILD, []{return logic->IsChild;}),
	Entrance(RR_SPIRIT_TEMPLE_EARLY_ADULT, []{return logic->CanUse(RG_SILVER_GAUNTLETS);}),
});
areaTable[RR_SPIRIT_TEMPLE_CHILD] = Region("Child Spirit Temple", SCENE_SPIRIT_TEMPLE, false, {RA_SPIRIT_TEMPLE}, {
	EventAccess(&logic->NutCrate, []{return true;}),
}, {
	LOCATION(RC_SPIRIT_TEMPLE_CHILD_BRIDGE_CHEST, ((logic->CanUse(RG_BOOMERANG) || (logic->CanUse(RG_FAIRY_SLINGSHOT) || (logic->CanUse(RG_BOMBCHU_5) && (bool)ctx->GetTrickOption(RT_SPIRIT_CHILD_CHU)))) && (logic->HasExplosives() || ((logic->CanUse(RG_NUTS) || logic->CanUse(RG_BOOMERANG)) && (logic->CanUse(RG_STICKS) || (logic->CanUse(RG_KOKIRI_SWORD) || logic->CanUse(RG_FAIRY_SLINGSHOT))))))),
	LOCATION(RC_SPIRIT_TEMPLE_CHILD_EARLY_TORCHES_CHEST, ((logic->CanUse(RG_BOOMERANG) || (logic->CanUse(RG_FAIRY_SLINGSHOT) || (logic->CanUse(RG_BOMBCHU_5) && (bool)ctx->GetTrickOption(RT_SPIRIT_CHILD_CHU)))) && ((logic->HasExplosives() || ((logic->CanUse(RG_NUTS) || logic->CanUse(RG_BOOMERANG)) && (logic->CanUse(RG_STICKS) || (logic->CanUse(RG_KOKIRI_SWORD) || logic->CanUse(RG_FAIRY_SLINGSHOT))))) && (logic->CanUse(RG_STICKS) || logic->CanUse(RG_DINS_FIRE))))),
	LOCATION(RC_SPIRIT_TEMPLE_GS_METAL_FENCE, ((logic->CanUse(RG_BOOMERANG) || (logic->CanUse(RG_FAIRY_SLINGSHOT) || (logic->CanUse(RG_BOMBCHU_5) && (bool)ctx->GetTrickOption(RT_SPIRIT_CHILD_CHU)))) && (logic->HasExplosives() || ((logic->CanUse(RG_NUTS) || logic->CanUse(RG_BOOMERANG)) && (logic->CanUse(RG_STICKS) || (logic->CanUse(RG_KOKIRI_SWORD) || logic->CanUse(RG_FAIRY_SLINGSHOT))))))),
	LOCATION(RC_SPIRIT_TEMPLE_ANUBIS_POT_1, ((logic->CanUse(RG_BOOMERANG) || (logic->CanUse(RG_FAIRY_SLINGSHOT) || (logic->CanUse(RG_BOMBCHU_5) && (bool)ctx->GetTrickOption(RT_SPIRIT_CHILD_CHU)))) && (logic->HasExplosives() || ((logic->CanUse(RG_NUTS) || logic->CanUse(RG_BOOMERANG)) && (logic->CanUse(RG_STICKS) || (logic->CanUse(RG_KOKIRI_SWORD) || logic->CanUse(RG_FAIRY_SLINGSHOT))))))),
	LOCATION(RC_SPIRIT_TEMPLE_ANUBIS_POT_2, ((logic->CanUse(RG_BOOMERANG) || (logic->CanUse(RG_FAIRY_SLINGSHOT) || (logic->CanUse(RG_BOMBCHU_5) && (bool)ctx->GetTrickOption(RT_SPIRIT_CHILD_CHU)))) && (logic->HasExplosives() || ((logic->CanUse(RG_NUTS) || logic->CanUse(RG_BOOMERANG)) && (logic->CanUse(RG_STICKS) || (logic->CanUse(RG_KOKIRI_SWORD) || logic->CanUse(RG_FAIRY_SLINGSHOT))))))),
	LOCATION(RC_SPIRIT_TEMPLE_ANUBIS_POT_3, ((logic->CanUse(RG_BOOMERANG) || (logic->CanUse(RG_FAIRY_SLINGSHOT) || (logic->CanUse(RG_BOMBCHU_5) && (bool)ctx->GetTrickOption(RT_SPIRIT_CHILD_CHU)))) && (logic->HasExplosives() || ((logic->CanUse(RG_NUTS) || logic->CanUse(RG_BOOMERANG)) && (logic->CanUse(RG_STICKS) || (logic->CanUse(RG_KOKIRI_SWORD) || logic->CanUse(RG_FAIRY_SLINGSHOT))))))),
	LOCATION(RC_SPIRIT_TEMPLE_ANUBIS_POT_4, ((logic->CanUse(RG_BOOMERANG) || (logic->CanUse(RG_FAIRY_SLINGSHOT) || (logic->CanUse(RG_BOMBCHU_5) && (bool)ctx->GetTrickOption(RT_SPIRIT_CHILD_CHU)))) && (logic->HasExplosives() || ((logic->CanUse(RG_NUTS) || logic->CanUse(RG_BOOMERANG)) && (logic->CanUse(RG_STICKS) || (logic->CanUse(RG_KOKIRI_SWORD) || logic->CanUse(RG_FAIRY_SLINGSHOT))))))),
	LOCATION(RC_SPIRIT_TEMPLE_BEFORE_CHILD_CLIMB_SMALL_CRATE_1, logic->CanBreakSmallCrates()),
	LOCATION(RC_SPIRIT_TEMPLE_BEFORE_CHILD_CLIMB_SMALL_CRATE_2, logic->CanBreakSmallCrates()),
}, {
	Entrance(RR_SPIRIT_TEMPLE_CHILD_CLIMB, []{return logic->SmallKeys(RR_SPIRIT_TEMPLE, 1);}),
});
areaTable[RR_SPIRIT_TEMPLE_CHILD_CLIMB] = Region("Child Spirit Temple Climb", SCENE_SPIRIT_TEMPLE, false, {RA_SPIRIT_TEMPLE}, {}, {
	LOCATION(RC_SPIRIT_TEMPLE_CHILD_CLIMB_NORTH_CHEST, (logic->HasProjectile(HasProjectileAge::Both) || ((logic->SmallKeys(RR_SPIRIT_TEMPLE, 2) && (logic->CanUse(RG_SILVER_GAUNTLETS) && logic->HasProjectile(HasProjectileAge::Adult))) || (logic->SmallKeys(RR_SPIRIT_TEMPLE, 5) && (logic->IsChild && logic->HasProjectile(HasProjectileAge::Child)))))),
	LOCATION(RC_SPIRIT_TEMPLE_CHILD_CLIMB_EAST_CHEST, (logic->HasProjectile(HasProjectileAge::Both) || ((logic->SmallKeys(RR_SPIRIT_TEMPLE, 2) && (logic->CanUse(RG_SILVER_GAUNTLETS) && logic->HasProjectile(HasProjectileAge::Adult))) || (logic->SmallKeys(RR_SPIRIT_TEMPLE, 5) && (logic->IsChild && logic->HasProjectile(HasProjectileAge::Child)))))),
	LOCATION(RC_SPIRIT_TEMPLE_GS_SUN_ON_FLOOR_ROOM, (logic->HasProjectile(HasProjectileAge::Both) || (logic->CanUse(RG_DINS_FIRE) || ((logic->TakeDamage() && (logic->CanJumpslashExceptHammer() || logic->HasProjectile(HasProjectileAge::Child))) || ((logic->IsChild && (logic->SmallKeys(RR_SPIRIT_TEMPLE, 5) && logic->HasProjectile(HasProjectileAge::Child))) || (logic->SmallKeys(RR_SPIRIT_TEMPLE, 2) && (logic->CanUse(RG_SILVER_GAUNTLETS) && (logic->HasProjectile(HasProjectileAge::Adult) || (logic->TakeDamage() && logic->CanJumpslashExceptHammer()))))))))),
	LOCATION(RC_SPIRIT_TEMPLE_CHILD_CLIMB_POT_1, logic->CanBreakPots()),
}, {
	Entrance(RR_SPIRIT_TEMPLE_CENTRAL_CHAMBER, []{return (logic->HasExplosives() || (ctx->GetOption(RSK_SUNLIGHT_ARROWS) && logic->CanUse(RG_LIGHT_ARROWS)));}),
});
areaTable[RR_SPIRIT_TEMPLE_EARLY_ADULT] = Region("Early Adult Spirit Temple", SCENE_SPIRIT_TEMPLE, false, {RA_SPIRIT_TEMPLE}, {}, {
	LOCATION(RC_SPIRIT_TEMPLE_COMPASS_CHEST, (logic->CanUse(RG_HOOKSHOT) && logic->CanUse(RG_ZELDAS_LULLABY))),
	LOCATION(RC_SPIRIT_TEMPLE_EARLY_ADULT_RIGHT_CHEST, ((logic->CanUse(RG_FAIRY_BOW) || (logic->CanUse(RG_HOOKSHOT) || (logic->CanUse(RG_FAIRY_SLINGSHOT) || (logic->CanUse(RG_BOOMERANG) || (logic->CanUse(RG_BOMBCHU_5) || (logic->CanUse(RG_BOMB_BAG) && (logic->IsAdult && (bool)ctx->GetTrickOption(RT_SPIRIT_LOWER_ADULT_SWITCH)))))))) && (logic->CanUse(RG_HOVER_BOOTS) || logic->CanJumpslashExceptHammer()))),
	LOCATION(RC_SPIRIT_TEMPLE_FIRST_MIRROR_LEFT_CHEST, logic->SmallKeys(RR_SPIRIT_TEMPLE, 3)),
	LOCATION(RC_SPIRIT_TEMPLE_FIRST_MIRROR_RIGHT_CHEST, logic->SmallKeys(RR_SPIRIT_TEMPLE, 3)),
	LOCATION(RC_SPIRIT_TEMPLE_GS_BOULDER_ROOM, (logic->CanUse(RG_SONG_OF_TIME) && (logic->CanUse(RG_FAIRY_BOW) || (logic->CanUse(RG_HOOKSHOT) || (logic->CanUse(RG_BOMBCHU_5) || (logic->CanUse(RG_BOMB_BAG) && (bool)ctx->GetTrickOption(RT_SPIRIT_LOWER_ADULT_SWITCH))))))),
	LOCATION(RC_SPIRIT_TEMPLE_BOULDER_ROOM_SUN_FAIRY, (logic->CanUse(RG_SUNS_SONG) && ((logic->CanUse(RG_FAIRY_BOW) || (logic->CanUse(RG_HOOKSHOT) || (logic->CanUse(RG_FAIRY_SLINGSHOT) || (logic->CanUse(RG_BOOMERANG) || (logic->CanUse(RG_BOMBCHU_5) || (logic->CanUse(RG_BOMB_BAG) && (logic->IsAdult && (bool)ctx->GetTrickOption(RT_SPIRIT_LOWER_ADULT_SWITCH)))))))) && (logic->CanUse(RG_HOVER_BOOTS) || logic->CanJumpslash())))),
}, {
	Entrance(RR_SPIRIT_TEMPLE_CENTRAL_CHAMBER, []{return logic->SmallKeys(RR_SPIRIT_TEMPLE, 1);}),
});
areaTable[RR_SPIRIT_TEMPLE_CENTRAL_CHAMBER] = Region("Spirit Temple Central Chamber", SCENE_SPIRIT_TEMPLE, false, {RA_SPIRIT_TEMPLE}, {}, {
	LOCATION(RC_SPIRIT_TEMPLE_MAP_CHEST, (((logic->HasExplosives() || logic->SmallKeys(RR_SPIRIT_TEMPLE, 2)) && (logic->CanUse(RG_DINS_FIRE) || ((logic->CanUse(RG_FIRE_ARROWS) || (bool)ctx->GetTrickOption(RT_SPIRIT_MAP_CHEST)) && (logic->CanUse(RG_FAIRY_BOW) && logic->CanUse(RG_STICKS))))) || ((logic->SmallKeys(RR_SPIRIT_TEMPLE, 5) && (logic->HasExplosives() && logic->CanUse(RG_STICKS))) || (logic->SmallKeys(RR_SPIRIT_TEMPLE, 3) && ((logic->CanUse(RG_FIRE_ARROWS) || ((bool)ctx->GetTrickOption(RT_SPIRIT_MAP_CHEST) && logic->CanUse(RG_FAIRY_BOW))) && logic->CanUse(RG_SILVER_GAUNTLETS)))))),
	LOCATION(RC_SPIRIT_TEMPLE_SUN_BLOCK_ROOM_CHEST, (((logic->HasExplosives() || logic->SmallKeys(RR_SPIRIT_TEMPLE, 2)) && (logic->CanUse(RG_DINS_FIRE) || ((logic->CanUse(RG_FIRE_ARROWS) || (bool)ctx->GetTrickOption(RT_SPIRIT_SUN_CHEST)) && (logic->CanUse(RG_FAIRY_BOW) && logic->CanUse(RG_STICKS))))) || ((logic->SmallKeys(RR_SPIRIT_TEMPLE, 5) && (logic->HasExplosives() && logic->CanUse(RG_STICKS))) || (logic->SmallKeys(RR_SPIRIT_TEMPLE, 3) && ((logic->CanUse(RG_FIRE_ARROWS) || ((bool)ctx->GetTrickOption(RT_SPIRIT_SUN_CHEST) && logic->CanUse(RG_FAIRY_BOW))) && logic->CanUse(RG_SILVER_GAUNTLETS)))))),
	LOCATION(RC_SPIRIT_TEMPLE_STATUE_ROOM_HAND_CHEST, (logic->SmallKeys(RR_SPIRIT_TEMPLE, 3) && (logic->CanUse(RG_SILVER_GAUNTLETS) && logic->CanUse(RG_ZELDAS_LULLABY)))),
	LOCATION(RC_SPIRIT_TEMPLE_STATUE_ROOM_NORTHEAST_CHEST, (logic->SmallKeys(RR_SPIRIT_TEMPLE, 3) && (logic->CanUse(RG_SILVER_GAUNTLETS) && (logic->CanUse(RG_ZELDAS_LULLABY) && (logic->CanUse(RG_HOOKSHOT) || (logic->CanUse(RG_HOVER_BOOTS) || (bool)ctx->GetTrickOption(RT_SPIRIT_LOBBY_JUMP))))))),
	LOCATION(RC_SPIRIT_TEMPLE_GS_HALL_AFTER_SUN_BLOCK_ROOM, ((logic->HasExplosives() && (logic->CanUse(RG_BOOMERANG) && logic->CanUse(RG_HOOKSHOT))) || ((logic->CanUse(RG_BOOMERANG) && (logic->SmallKeys(RR_SPIRIT_TEMPLE, 5) && logic->HasExplosives())) || (logic->CanUse(RG_HOOKSHOT) && (logic->CanUse(RG_SILVER_GAUNTLETS) && logic->SmallKeys(RR_SPIRIT_TEMPLE, 2)))))),
	LOCATION(RC_SPIRIT_TEMPLE_GS_LOBBY, (((logic->HasExplosives() || logic->SmallKeys(RR_SPIRIT_TEMPLE, 2)) && ((bool)ctx->GetTrickOption(RT_SPIRIT_LOBBY_GS) && (logic->CanUse(RG_BOOMERANG) && (logic->CanUse(RG_HOOKSHOT) || (logic->CanUse(RG_HOVER_BOOTS) || (bool)ctx->GetTrickOption(RT_SPIRIT_LOBBY_JUMP)))))) || (((bool)ctx->GetTrickOption(RT_SPIRIT_LOBBY_GS) && (logic->SmallKeys(RR_SPIRIT_TEMPLE, 5) && (logic->HasExplosives() && logic->CanUse(RG_BOOMERANG)))) || (logic->SmallKeys(RR_SPIRIT_TEMPLE, 3) && (logic->CanUse(RG_SILVER_GAUNTLETS) && (logic->CanUse(RG_HOOKSHOT) || (logic->CanUse(RG_HOVER_BOOTS) || (bool)ctx->GetTrickOption(RT_SPIRIT_LOBBY_JUMP)))))))),
	LOCATION(RC_SPIRIT_TEMPLE_AFTER_SUN_BLOCK_POT_1, (logic->CanBreakPots() && logic->SmallKeys(RR_SPIRIT_TEMPLE, 2))),
	LOCATION(RC_SPIRIT_TEMPLE_AFTER_SUN_BLOCK_POT_2, (logic->CanBreakPots() && logic->SmallKeys(RR_SPIRIT_TEMPLE, 2))),
	LOCATION(RC_SPIRIT_TEMPLE_CENTRAL_CHAMBER_POT_1, (logic->CanBreakPots() && logic->SmallKeys(RR_SPIRIT_TEMPLE, 2))),
	LOCATION(RC_SPIRIT_TEMPLE_CENTRAL_CHAMBER_POT_2, (logic->CanBreakPots() && logic->SmallKeys(RR_SPIRIT_TEMPLE, 2))),
	LOCATION(RC_SPIRIT_TEMPLE_CENTRAL_CHAMBER_POT_3, (logic->CanBreakPots() && logic->SmallKeys(RR_SPIRIT_TEMPLE, 2))),
	LOCATION(RC_SPIRIT_TEMPLE_CENTRAL_CHAMBER_POT_4, (logic->CanBreakPots() && logic->SmallKeys(RR_SPIRIT_TEMPLE, 2))),
	LOCATION(RC_SPIRIT_TEMPLE_CENTRAL_CHAMBER_POT_5, (logic->CanBreakPots() && logic->SmallKeys(RR_SPIRIT_TEMPLE, 2))),
	LOCATION(RC_SPIRIT_TEMPLE_CENTRAL_CHAMBER_POT_6, (logic->CanBreakPots() && logic->SmallKeys(RR_SPIRIT_TEMPLE, 2))),
}, {
	Entrance(RR_SPIRIT_TEMPLE_OUTDOOR_HANDS, []{return (logic->CanJumpslashExceptHammer() || logic->HasExplosives());}),
	Entrance(RR_SPIRIT_TEMPLE_BEYOND_CENTRAL_LOCKED_DOOR, []{return (logic->SmallKeys(RR_SPIRIT_TEMPLE, 4) && logic->CanUse(RG_SILVER_GAUNTLETS));}),
	Entrance(RR_SPIRIT_TEMPLE_CHILD_CLIMB, []{return true;}),
	Entrance(RR_SPIRIT_TEMPLE_INSIDE_STATUE_HEAD, []{return ((bool)ctx->GetTrickOption(RT_SPIRIT_PLATFORM_HOOKSHOT) && logic->CanUse(RG_HOOKSHOT));}),
});
areaTable[RR_SPIRIT_TEMPLE_OUTDOOR_HANDS] = Region("Spirit Temple Outdoor Hands", SCENE_SPIRIT_TEMPLE, false, {RA_SPIRIT_TEMPLE}, {}, {
	LOCATION(RC_SPIRIT_TEMPLE_SILVER_GAUNTLETS_CHEST, ((logic->SmallKeys(RR_SPIRIT_TEMPLE, 3) && (logic->CanUse(RG_LONGSHOT) && logic->HasExplosives())) || logic->SmallKeys(RR_SPIRIT_TEMPLE, 5))),
	LOCATION(RC_SPIRIT_TEMPLE_MIRROR_SHIELD_CHEST, (logic->SmallKeys(RR_SPIRIT_TEMPLE, 4) && (logic->CanUse(RG_SILVER_GAUNTLETS) && logic->HasExplosives()))),
}, {
	Entrance(RR_DESERT_COLOSSUS, []{return ((logic->IsChild && logic->SmallKeys(RR_SPIRIT_TEMPLE, 5)) || (logic->CanUse(RG_SILVER_GAUNTLETS) && ((logic->SmallKeys(RR_SPIRIT_TEMPLE, 3) && logic->HasExplosives()) || logic->SmallKeys(RR_SPIRIT_TEMPLE, 5))));}),
});
areaTable[RR_SPIRIT_TEMPLE_BEYOND_CENTRAL_LOCKED_DOOR] = Region("Spirit Temple Beyond Central Locked Door", SCENE_SPIRIT_TEMPLE, false, {RA_SPIRIT_TEMPLE}, {}, {
	LOCATION(RC_SPIRIT_TEMPLE_NEAR_FOUR_ARMOS_CHEST, ((logic->CanUse(RG_MIRROR_SHIELD) || (ctx->GetOption(RSK_SUNLIGHT_ARROWS) && logic->CanUse(RG_LIGHT_ARROWS))) && logic->HasExplosives())),
	LOCATION(RC_SPIRIT_TEMPLE_HALLWAY_LEFT_INVISIBLE_CHEST, (((bool)ctx->GetTrickOption(RT_LENS_SPIRIT) || logic->CanUse(RG_LENS_OF_TRUTH)) && logic->HasExplosives())),
	LOCATION(RC_SPIRIT_TEMPLE_HALLWAY_RIGHT_INVISIBLE_CHEST, (((bool)ctx->GetTrickOption(RT_LENS_SPIRIT) || logic->CanUse(RG_LENS_OF_TRUTH)) && logic->HasExplosives())),
	LOCATION(RC_SPIRIT_TEMPLE_BEAMOS_HALL_POT_1, logic->CanBreakPots()),
	LOCATION(RC_SPIRIT_TEMPLE_ARMOS_ROOM_SUN_FAIRY, (logic->HasExplosives() && logic->CanUse(RG_SUNS_SONG))),
}, {
	Entrance(RR_SPIRIT_TEMPLE_BEYOND_FINAL_LOCKED_DOOR, []{return (logic->SmallKeys(RR_SPIRIT_TEMPLE, 5) && ((bool)ctx->GetTrickOption(RT_SPIRIT_WALL) || (logic->CanUse(RG_LONGSHOT) || (logic->CanUse(RG_BOMBCHU_5) || ((logic->CanUse(RG_BOMB_BAG) || (logic->CanUse(RG_NUTS) || logic->CanUse(RG_DINS_FIRE))) && (logic->CanUse(RG_FAIRY_BOW) || (logic->CanUse(RG_HOOKSHOT) || logic->CanUse(RG_MEGATON_HAMMER))))))));}),
});
areaTable[RR_SPIRIT_TEMPLE_BEYOND_FINAL_LOCKED_DOOR] = Region("Spirit Temple Beyond Final Locked Door", SCENE_SPIRIT_TEMPLE, false, {RA_SPIRIT_TEMPLE}, {}, {
	LOCATION(RC_SPIRIT_TEMPLE_BOSS_KEY_CHEST, (logic->CanUse(RG_ZELDAS_LULLABY) && ((logic->TakeDamage() && (bool)ctx->GetTrickOption(RT_FLAMING_CHESTS)) || (logic->CanUse(RG_FAIRY_BOW) && logic->CanUse(RG_HOOKSHOT))))),
	LOCATION(RC_SPIRIT_TEMPLE_TOPMOST_CHEST, ((logic->CanUse(RG_MIRROR_SHIELD) && logic->CanAttack()) || (ctx->GetOption(RSK_SUNLIGHT_ARROWS) && logic->CanUse(RG_LIGHT_ARROWS)))),
	LOCATION(RC_SPIRIT_TEMPLE_ADULT_CLIMB_LEFT_HEART, logic->CanUse(RG_HOOKSHOT)),
	LOCATION(RC_SPIRIT_TEMPLE_ADULT_CLIMB_RIGHT_HEART, logic->CanUse(RG_HOOKSHOT)),
}, {
	Entrance(RR_SPIRIT_TEMPLE_INSIDE_STATUE_HEAD, []{return (logic->CanUse(RG_MIRROR_SHIELD) && (logic->HasExplosives() && logic->CanUse(RG_HOOKSHOT)));}),
});
areaTable[RR_SPIRIT_TEMPLE_INSIDE_STATUE_HEAD] = Region("Spirit Temple Inside Statue Head", SCENE_SPIRIT_TEMPLE, false, {RA_SPIRIT_TEMPLE}, {}, {}, {
	Entrance(RR_SPIRIT_TEMPLE_CENTRAL_CHAMBER, []{return true;}),
	Entrance(RR_SPIRIT_TEMPLE_BOSS_ENTRYWAY, []{return true;}),
});
areaTable[RR_SPIRIT_TEMPLE_MQ_LOBBY] = Region("Spirit Temple MQ Lobby", SCENE_SPIRIT_TEMPLE, false, {RA_SPIRIT_TEMPLE}, {}, {
	LOCATION(RC_SPIRIT_TEMPLE_MQ_ENTRANCE_FRONT_LEFT_CHEST, true),
	LOCATION(RC_SPIRIT_TEMPLE_MQ_ENTRANCE_BACK_LEFT_CHEST, (Here(RR_SPIRIT_TEMPLE_MQ_LOBBY, []{return logic->BlastOrSmash();}) && logic->CanHitEyeTargets())),
	LOCATION(RC_SPIRIT_TEMPLE_MQ_ENTRANCE_BACK_RIGHT_CHEST, logic->CanHitSwitch(ED_BOOMERANG)),
	LOCATION(RC_SPIRIT_TEMPLE_MQ_ENTRANCE_FRONT_RIGHT_CHEST, logic->Spirit1FSilverRupees),
	LOCATION(RC_SPIRIT_TEMPLE_MQ_ENTRANCE_POT_1, logic->CanBreakPots()),
	LOCATION(RC_SPIRIT_TEMPLE_MQ_ENTRANCE_POT_2, logic->CanBreakPots()),
	LOCATION(RC_SPIRIT_TEMPLE_MQ_ENTRANCE_POT_3, logic->CanBreakPots()),
	LOCATION(RC_SPIRIT_TEMPLE_MQ_ENTRANCE_POT_4, logic->CanBreakPots()),
}, {
	Entrance(RR_SPIRIT_TEMPLE_ENTRYWAY, []{return true;}),
	Entrance(RR_SPIRIT_TEMPLE_MQ_1F_WEST, []{return logic->IsChild;}),
	Entrance(RR_SPIRIT_TEMPLE_MQ_BIG_BLOCK_ROOM_SOUTH, []{return (logic->CanUse(RG_LONGSHOT) && logic->CanUse(RG_BOMBCHU_5));}),
});
areaTable[RR_SPIRIT_TEMPLE_MQ_1F_WEST] = Region("Spirit Temple MQ 1F West", SCENE_SPIRIT_TEMPLE, false, {RA_SPIRIT_TEMPLE}, {
	EventAccess(&logic->MQSpiritCrawlBoulder, []{return (logic->CanUse(RG_BOMBCHU_5) || ((bool)ctx->GetTrickOption(RT_RUSTED_SWITCHES) && logic->CanUse(RG_MEGATON_HAMMER)));}),
}, {
	LOCATION(RC_SPIRIT_TEMPLE_MQ_CHILD_HAMMER_SWITCH_CHEST, logic->MQSpiritTimeTravelChest),
	LOCATION(RC_SPIRIT_TEMPLE_MQ_CHILD_SLUGMA_POT, logic->CanBreakPots()),
	LOCATION(RC_SPIRIT_TEMPLE_MQ_CHILD_LEFT_HEART, logic->CanHitEyeTargets()),
	LOCATION(RC_SPIRIT_TEMPLE_MQ_CHILD_RIGHT_HEART, logic->CanHitEyeTargets()),
}, {
	Entrance(RR_SPIRIT_TEMPLE_MQ_1F_GIBDO_ROOM_SOUTH, []{return Here(RR_SPIRIT_TEMPLE_MQ_1F_WEST, []{return logic->CanKillEnemy(RE_TORCH_SLUG);});}),
	Entrance(RR_SPIRIT_TEMPLE_MQ_MAP_ROOM_SOUTH, []{return Here(RR_SPIRIT_TEMPLE_MQ_1F_WEST, []{return logic->CanKillEnemy(RE_TORCH_SLUG);});}),
	Entrance(RR_SPIRIT_TEMPLE_MQ_WEST_1F_RUSTED_SWITCH, []{return (logic->IsChild && logic->MQSpiritCrawlBoulder);}),
});
areaTable[RR_SPIRIT_TEMPLE_MQ_1F_GIBDO_ROOM_NORTH] = Region("Spirit Temple MQ Gibdo Room North", SCENE_SPIRIT_TEMPLE, false, {RA_SPIRIT_TEMPLE}, {}, {
	LOCATION(RC_SPIRIT_TEMPLE_MQ_CHILD_GIBDO_POT_1, logic->CanBreakPots()),
	LOCATION(RC_SPIRIT_TEMPLE_MQ_CHILD_GIBDO_POT_2, logic->CanBreakPots()),
}, {});
areaTable[RR_SPIRIT_TEMPLE_MQ_1F_GIBDO_ROOM_SOUTH] = Region("Spirit Temple MQ 1F Gibdo Room South", SCENE_SPIRIT_TEMPLE, false, {RA_SPIRIT_TEMPLE}, {}, {}, {
	Entrance(RR_SPIRIT_TEMPLE_MQ_1F_WEST, []{return true;}),
	Entrance(RR_SPIRIT_TEMPLE_MQ_1F_GIBDO_ROOM_NORTH, []{return (logic->CanUse(RG_BOMBCHU_5) && logic->CanHitEyeTargets());}),
	Entrance(RR_SPIRIT_TEMPLE_MQ_TURNTABLE_ROOM, []{return (logic->CanUse(RG_BOMBCHU_5) && (logic->CanHitEyeTargets() && logic->CanKillEnemy(RE_GIBDO)));}),
});
areaTable[RR_SPIRIT_TEMPLE_MQ_TURNTABLE_ROOM] = Region("Spirit Temple Turntable Room", SCENE_SPIRIT_TEMPLE, false, {RA_SPIRIT_TEMPLE}, {
	EventAccess(&logic->FairyPot, []{return Here(RR_SPIRIT_TEMPLE_MQ_TURNTABLE_ROOM, []{return logic->CanKillEnemy(RE_STALFOS);});}),
}, {
	LOCATION(RC_SPIRIT_TEMPLE_MQ_CHILD_STALFOS_POT_1, (logic->CanUse(RG_BOOMERANG) || logic->CanKillEnemy(RE_STALFOS))),
	LOCATION(RC_SPIRIT_TEMPLE_MQ_CHILD_STALFOS_POT_2, (logic->CanUse(RG_BOOMERANG) || logic->CanKillEnemy(RE_STALFOS))),
	LOCATION(RC_SPIRIT_TEMPLE_MQ_CHILD_STALFOS_POT_3, (logic->CanUse(RG_BOOMERANG) || logic->CanKillEnemy(RE_STALFOS))),
	LOCATION(RC_SPIRIT_TEMPLE_MQ_CHILD_STALFOS_POT_4, (logic->CanUse(RG_BOOMERANG) || logic->CanKillEnemy(RE_STALFOS))),
}, {
	Entrance(RR_SPIRIT_TEMPLE_MQ_1F_GIBDO_ROOM_NORTH, []{return true;}),
	Entrance(RR_SPIRIT_TEMPLE_MQ_MAP_ROOM_NORTH, []{return Here(RR_SPIRIT_TEMPLE_MQ_TURNTABLE_ROOM, []{return logic->CanKillEnemy(RE_STALFOS);});}),
});
areaTable[RR_SPIRIT_TEMPLE_MQ_MAP_ROOM_NORTH] = Region("Spirit Temple MQ Map Room North", SCENE_SPIRIT_TEMPLE, false, {RA_SPIRIT_TEMPLE}, {
	EventAccess(&logic->MQSpiritMapRoomEnemies, []{return (logic->CanKillEnemy(RE_ANUBIS) && logic->CanKillEnemy(RE_KEESE));}),
}, {
	LOCATION(RC_SPIRIT_TEMPLE_MQ_MAP_ROOM_ENEMY_CHEST, logic->MQSpiritMapRoomEnemies),
}, {
	Entrance(RR_SPIRIT_TEMPLE_MQ_MAP_ROOM_SOUTH, []{return true;}),
});
areaTable[RR_SPIRIT_TEMPLE_MQ_MAP_ROOM_SOUTH] = Region("Spirit Temple MQ Map Room South", SCENE_SPIRIT_TEMPLE, false, {RA_SPIRIT_TEMPLE}, {
	EventAccess(&logic->MQSpiritMapRoomEnemies, []{return (logic->CanKillEnemy(RE_ANUBIS) && logic->CanKillEnemy(RE_KEESE, ED_BOOMERANG));}),
}, {
	LOCATION(RC_SPIRIT_TEMPLE_MQ_MAP_CHEST, true),
}, {
	Entrance(RR_SPIRIT_TEMPLE_MQ_MAP_ROOM_NORTH, []{return logic->CanUse(RG_HOOKSHOT);}),
	Entrance(RR_SPIRIT_TEMPLE_MQ_1F_WEST, []{return true;}),
});
areaTable[RR_SPIRIT_TEMPLE_MQ_WEST_1F_RUSTED_SWITCH] = Region("Spirit Temple MQ West 1F Rusted Switch", SCENE_SPIRIT_TEMPLE, false, {RA_SPIRIT_TEMPLE}, {
	EventAccess(&logic->MQSpiritTimeTravelChest, []{return logic->CanUse(RG_MEGATON_HAMMER);}),
	EventAccess(&logic->MQSpiritCrawlBoulder, []{return (logic->CanUse(RG_BOMBCHU_5) || ((bool)ctx->GetTrickOption(RT_RUSTED_SWITCHES) && logic->CanUse(RG_MEGATON_HAMMER)));}),
}, {}, {
	Entrance(RR_SPIRIT_TEMPLE_MQ_1F_WEST, []{return (logic->IsChild && logic->MQSpiritCrawlBoulder);}),
	Entrance(RR_SPIRIT_TEMPLE_MQ_UNDER_LIKE_LIKE, []{return logic->SmallKeys(RR_SPIRIT_TEMPLE, 1);}),
});
areaTable[RR_SPIRIT_TEMPLE_MQ_UNDER_LIKE_LIKE] = Region("Spirit Temple MQ Under Like Like", SCENE_SPIRIT_TEMPLE, false, {RA_SPIRIT_TEMPLE}, {}, {
	LOCATION(RC_SPIRIT_TEMPLE_MQ_CHILD_LIKE_LIKE_POT, MQSpiritSharedBrokenWallRoom(RR_SPIRIT_TEMPLE_MQ_UNDER_LIKE_LIKE, []{return logic->CanBreakPots();})),
}, {
	Entrance(RR_SPIRIT_TEMPLE_MQ_WEST_1F_RUSTED_SWITCH, []{return logic->SmallKeys(RR_SPIRIT_TEMPLE, 7);}),
	Entrance(RR_SPIRIT_TEMPLE_MQ_BROKEN_WALL_ROOM, []{return logic->CanHitSwitch();}),
});
areaTable[RR_SPIRIT_TEMPLE_MQ_BROKEN_WALL_ROOM] = Region("Spirit Temple MQ Broken Wall Room", SCENE_SPIRIT_TEMPLE, false, {RA_SPIRIT_TEMPLE}, {}, {
	LOCATION(RC_SPIRIT_TEMPLE_MQ_CHILD_CLIMB_NORTH_CHEST, MQSpiritSharedBrokenWallRoom(RR_SPIRIT_TEMPLE_MQ_BROKEN_WALL_ROOM, []{return logic->CanKillEnemy(RE_BEAMOS);})),
	LOCATION(RC_SPIRIT_TEMPLE_MQ_CHILD_CLIMB_SOUTH_CHEST, (logic->IsAdult && ((logic->HasExplosives() || (ctx->GetOption(RSK_SUNLIGHT_ARROWS) && logic->CanUse(RG_LIGHT_ARROWS))) && logic->CanUse(RG_HOOKSHOT)))),
}, {
	Entrance(RR_SPIRIT_TEMPLE_MQ_UNDER_LIKE_LIKE, []{return logic->CanHitSwitch();}),
	Entrance(RR_SPIRIT_TEMPLE_MQ_STATUE_ROOM, []{return logic->SmallKeys(RR_SPIRIT_TEMPLE, 2);}),
});
areaTable[RR_SPIRIT_TEMPLE_MQ_STATUE_ROOM] = Region("Spirit Temple MQ Statue Room", SCENE_SPIRIT_TEMPLE, false, {RA_SPIRIT_TEMPLE}, {}, {
	LOCATION(RC_SPIRIT_TEMPLE_MQ_COMPASS_CHEST, MQSpiritSharedStatueRoom(RR_SPIRIT_TEMPLE_MQ_STATUE_ROOM, []{return logic->CanHitEyeTargets();})),
	LOCATION(RC_SPIRIT_TEMPLE_MQ_STATUE_3F_EAST_POT, MQSpiritSharedStatueRoom(RR_SPIRIT_TEMPLE_MQ_STATUE_ROOM, []{return (((logic->IsAdult || logic->CanJumpslash()) && logic->CanUse(RG_BOOMERANG)) || ((logic->CanUse(RG_HOVER_BOOTS) || (logic->CanUse(RG_SONG_OF_TIME) || (logic->IsAdult && (bool)ctx->GetTrickOption(RT_SPIRIT_LOBBY_JUMP)))) && logic->CanBreakPots()));})),
	LOCATION(RC_SPIRIT_TEMPLE_MQ_STATUE_3F_WEST_POT, MQSpiritSharedStatueRoom(RR_SPIRIT_TEMPLE_MQ_STATUE_ROOM, []{return (logic->CanUse(RG_HOVER_BOOTS) || (logic->CanUse(RG_SONG_OF_TIME) || ((logic->IsAdult && (bool)ctx->GetTrickOption(RT_SPIRIT_LOBBY_JUMP)) && logic->CanBreakPots())));})),
	LOCATION(RC_SPIRIT_TEMPLE_MQ_STATUE_2F_CENTER_EAST_POT, MQSpiritSharedStatueRoom(RR_SPIRIT_TEMPLE_MQ_STATUE_ROOM, []{return logic->CanBreakPots();})),
	LOCATION(RC_SPIRIT_TEMPLE_MQ_STATUE_2F_WEST_POT, MQSpiritSharedStatueRoom(RR_SPIRIT_TEMPLE_MQ_STATUE_ROOM, []{return logic->CanBreakPots();})),
	LOCATION(RC_SPIRIT_TEMPLE_MQ_STATUE_2F_EASTMOST_POT, MQSpiritSharedStatueRoom(RR_SPIRIT_TEMPLE_MQ_STATUE_ROOM, []{return logic->CanBreakPots();})),
	LOCATION(RC_SPIRIT_TEMPLE_MQ_STATUE_CRATE_1, MQSpiritSharedStatueRoom(RR_SPIRIT_TEMPLE_MQ_STATUE_ROOM, []{return logic->CanBreakCrates();})),
	LOCATION(RC_SPIRIT_TEMPLE_MQ_STATUE_CRATE_2, MQSpiritSharedStatueRoom(RR_SPIRIT_TEMPLE_MQ_STATUE_ROOM, []{return logic->CanBreakCrates();})),
	LOCATION(RC_SPIRIT_TEMPLE_MQ_STATUE_SMALL_CRATE, MQSpiritSharedStatueRoom(RR_SPIRIT_TEMPLE_MQ_STATUE_ROOM, []{return logic->CanBreakSmallCrates();})),
}, {
	Entrance(RR_SPIRIT_TEMPLE_MQ_BROKEN_WALL_ROOM, []{return logic->SmallKeys(RR_SPIRIT_TEMPLE, 7);}),
	Entrance(RR_SPIRIT_TEMPLE_MQ_BIG_BLOCK_ROOM_NORTH, []{return Here(RR_SPIRIT_TEMPLE_MQ_STATUE_ROOM, []{return (logic->HasFireSource() || ((bool)ctx->GetTrickOption(RT_SPIRIT_MQ_FROZEN_EYE) && (logic->CanUse(RG_FAIRY_BOW) && logic->CanUse(RG_SONG_OF_TIME))));});}),
	Entrance(RR_SPIRIT_TEMPLE_MQ_SUN_BLOCK_ROOM, []{return (logic->IsAdult || ((bool)ctx->GetTrickOption(RT_SPIRIT_MQ_SUN_BLOCK_SOT) || logic->CanUse(RG_SONG_OF_TIME)));}),
	Entrance(RR_SPIRIT_TEMPLE_MQ_STATUE_ROOM_EAST, []{return (logic->IsAdult && logic->CanUse(RG_HOOKSHOT));}),
});
areaTable[RR_SPIRIT_TEMPLE_MQ_SUN_BLOCK_ROOM] = Region("Spirit Temple MQ Sun Block Room", SCENE_SPIRIT_TEMPLE, false, {RA_SPIRIT_TEMPLE}, {}, {
	LOCATION(RC_SPIRIT_TEMPLE_MQ_SUN_BLOCK_ROOM_CHEST, true),
	LOCATION(RC_SPIRIT_TEMPLE_MQ_GS_SUN_BLOCK_ROOM, MQSpiritSharedStatueRoom(RR_SPIRIT_TEMPLE_MQ_SUN_BLOCK_ROOM, []{return (logic->CanUse(RG_HOOKSHOT) || ((bool)ctx->GetTrickOption(RT_SPIRIT_MQ_SUN_BLOCK_GS) && logic->CanUse(RG_BOOMERANG)));})),
	LOCATION(RC_SPIRIT_TEMPLE_MQ_SUN_BLOCKS_POT_1, MQSpiritSharedStatueRoom(RR_SPIRIT_TEMPLE_MQ_SUN_BLOCK_ROOM, []{return logic->CanBreakPots();})),
	LOCATION(RC_SPIRIT_TEMPLE_MQ_SUN_BLOCKS_POT_2, MQSpiritSharedStatueRoom(RR_SPIRIT_TEMPLE_MQ_SUN_BLOCK_ROOM, []{return logic->CanBreakPots();})),
}, {
	Entrance(RR_SPIRIT_TEMPLE_MQ_STATUE_ROOM, []{return true;}),
	Entrance(RR_SPIRIT_TEMPLE_MQ_WEST_IRON_KNUCKLE, []{return logic->SmallKeys(RR_SPIRIT_TEMPLE, 7);}),
});
areaTable[RR_SPIRIT_TEMPLE_MQ_WEST_IRON_KNUCKLE] = Region("Spirit Temple MQ East Iron Knuckle", SCENE_SPIRIT_TEMPLE, false, {RA_SPIRIT_TEMPLE}, {}, {}, {
	Entrance(RR_SPIRIT_TEMPLE_MQ_SUN_BLOCK_ROOM, []{return logic->SmallKeys(RR_SPIRIT_TEMPLE, 7);}),
	Entrance(RR_SPIRIT_TEMPLE_MQ_SILVER_GAUNTLETS_HAND, []{return logic->CanKillEnemy(RE_IRON_KNUCKLE);}),
});
areaTable[RR_SPIRIT_TEMPLE_MQ_SILVER_GAUNTLETS_HAND] = Region("Spirit Temple MQ Silver Gauntlets Hand", SCENE_SPIRIT_TEMPLE, false, {RA_SPIRIT_TEMPLE}, {}, {
	LOCATION(RC_SPIRIT_TEMPLE_SILVER_GAUNTLETS_CHEST, true),
}, {
	Entrance(RR_SPIRIT_TEMPLE_MQ_WEST_IRON_KNUCKLE, []{return true;}),
	Entrance(RR_DESERT_COLOSSUS, []{return true;}),
});
areaTable[RR_SPIRIT_TEMPLE_MQ_BIG_BLOCK_ROOM_SOUTH] = Region("Spirit Temple MQ Block Room South", SCENE_SPIRIT_TEMPLE, false, {RA_SPIRIT_TEMPLE}, {}, {}, {
	Entrance(RR_SPIRIT_TEMPLE_MQ_LOBBY, []{return true;}),
	Entrance(RR_SPIRIT_TEMPLE_MQ_BIG_BLOCK_ROOM_NORTH, []{return (logic->IsChild ? logic->CanUse(RG_SILVER_GAUNTLETS) : Here(RR_SPIRIT_TEMPLE_MQ_BIG_BLOCK_ROOM_SOUTH, []{return logic->CanUse(RG_SILVER_GAUNTLETS);}));}),
});
areaTable[RR_SPIRIT_TEMPLE_MQ_BIG_BLOCK_ROOM_NORTH] = Region("Spirit Temple MQ Block Room North", SCENE_SPIRIT_TEMPLE, false, {RA_SPIRIT_TEMPLE}, {}, {
	LOCATION(RC_SPIRIT_TEMPLE_MQ_SILVER_BLOCK_HALLWAY_CHEST, (logic->IsChild && (logic->SmallKeys(RR_SPIRIT_TEMPLE, 7) && logic->CanHitEyeTargets()))),
}, {
	Entrance(RR_SPIRIT_TEMPLE_MQ_STATUE_ROOM, []{return true;}),
});
areaTable[RR_SPIRIT_TEMPLE_MQ_STATUE_ROOM_EAST] = Region("Spirit Temple MQ Statue Room East", SCENE_SPIRIT_TEMPLE, false, {RA_SPIRIT_TEMPLE}, {}, {
	LOCATION(RC_SPIRIT_TEMPLE_MQ_STATUE_ROOM_LULLABY_CHEST, (logic->CanUse(RG_HOOKSHOT) && (logic->CanUse(RG_ZELDAS_LULLABY) && (logic->CanJumpslash() || logic->CanUse(RG_HOVER_BOOTS))))),
	LOCATION(RC_SPIRIT_TEMPLE_MQ_STATUE_ROOM_INVISIBLE_CHEST, (((bool)ctx->GetTrickOption(RT_LENS_SPIRIT_MQ) || logic->CanUse(RG_LENS_OF_TRUTH)) && (logic->CanUse(RG_HOOKSHOT) || logic->CanUse(RG_HOVER_BOOTS)))),
}, {
	Entrance(RR_SPIRIT_TEMPLE_MQ_STATUE_ROOM, []{return true;}),
	Entrance(RR_SPIRIT_TEMPLE_MQ_SILVER_GAUNTLETS_HAND, []{return (logic->SmallKeys(RR_SPIRIT_TEMPLE, 4) && (logic->CanAvoidEnemy(RE_BEAMOS, true, 4) && (logic->CanUse(RG_SONG_OF_TIME) && (logic->CanJumpslash() && (((bool)ctx->GetTrickOption(RT_LENS_SPIRIT_MQ) || logic->CanUse(RG_LENS_OF_TRUTH)) && (logic->CanKillEnemy(RE_IRON_KNUCKLE) && logic->CanUse(RG_LONGSHOT)))))));}),
	Entrance(RR_SPIRIT_TEMPLE_MQ_FOUR_BEAMOS_ROOM, []{return (logic->SmallKeys(RR_SPIRIT_TEMPLE, 5) && logic->CanUse(RG_HOOKSHOT));}),
	Entrance(RR_SPIRIT_TEMPLE_MQ_THREE_SUNS_ROOM_2F, []{return (logic->CanUse(RG_FIRE_ARROWS) || ((bool)ctx->GetTrickOption(RT_SPIRIT_MQ_LOWER_ADULT) && logic->CanUse(RG_DINS_FIRE)));}),
});
areaTable[RR_SPIRIT_TEMPLE_MQ_THREE_SUNS_ROOM_2F] = Region("Spirit Temple MQ Three Suns Room 2F", SCENE_SPIRIT_TEMPLE, false, {RA_SPIRIT_TEMPLE}, {
	EventAccess(&logic->MQSpirit3SunsEnemies, []{return ((logic->CanUse(RG_MIRROR_SHIELD) && logic->CanKillEnemy(RE_STALFOS, ED_CLOSE, true, 2)) || (ctx->GetOption(RSK_SUNLIGHT_ARROWS) && logic->CanUse(RG_LIGHT_ARROWS)));}),
}, {}, {
	Entrance(RR_SPIRIT_TEMPLE_MQ_STATUE_ROOM_EAST, []{return true;}),
	Entrance(RR_SPIRIT_TEMPLE_MQ_THREE_SUNS_ROOM_1F, []{return logic->MQSpirit3SunsEnemies;}),
});
areaTable[RR_SPIRIT_TEMPLE_MQ_THREE_SUNS_ROOM_1F] = Region("Spirit Temple MQ Three Suns Room 1F", SCENE_SPIRIT_TEMPLE, false, {RA_SPIRIT_TEMPLE}, {}, {}, {
	Entrance(RR_SPIRIT_TEMPLE_MQ_THREE_SUNS_ROOM_2F, []{return logic->MQSpirit3SunsEnemies;}),
	Entrance(RR_SPIRIT_TEMPLE_MQ_1F_EAST, []{return true;}),
});
areaTable[RR_SPIRIT_TEMPLE_MQ_1F_EAST] = Region("Spirit Temple MQ 1F East", SCENE_SPIRIT_TEMPLE, false, {RA_SPIRIT_TEMPLE}, {
	EventAccess(&logic->Spirit1FSilverRupees, []{return logic->CanUse(RG_MEGATON_HAMMER);}),
}, {
	LOCATION(RC_SPIRIT_TEMPLE_MQ_EARLY_ADULT_POT_1, logic->CanBreakPots()),
	LOCATION(RC_SPIRIT_TEMPLE_MQ_EARLY_ADULT_POT_2, logic->CanBreakPots()),
}, {
	Entrance(RR_SPIRIT_TEMPLE_MQ_LOBBY, []{return logic->CanUse(RG_MEGATON_HAMMER);}),
	Entrance(RR_SPIRIT_TEMPLE_MQ_THREE_SUNS_ROOM_1F, []{return true;}),
	Entrance(RR_SPIRIT_TEMPLE_MQ_LEEVER_ROOM, []{return true;}),
	Entrance(RR_SPIRIT_TEMPLE_MQ_SYMPHONY_ROOM, []{return logic->SmallKeys(RR_SPIRIT_TEMPLE, 7);}),
});
areaTable[RR_SPIRIT_TEMPLE_MQ_LEEVER_ROOM] = Region("Spirit Temple MQ Leever Room", SCENE_SPIRIT_TEMPLE, false, {RA_SPIRIT_TEMPLE}, {}, {
	LOCATION(RC_SPIRIT_TEMPLE_MQ_LEEVER_ROOM_CHEST, (logic->CanKillEnemy(RE_PURPLE_LEEVER) && logic->CanUse(RG_HOOKSHOT))),
	LOCATION(RC_SPIRIT_TEMPLE_MQ_GS_LEEVER_ROOM, logic->CanGetEnemyDrop(RE_GOLD_SKULLTULA, ED_BOOMERANG)),
}, {
	Entrance(RR_SPIRIT_TEMPLE_MQ_1F_EAST, []{return logic->CanUse(RG_ZELDAS_LULLABY);}),
});
areaTable[RR_SPIRIT_TEMPLE_MQ_SYMPHONY_ROOM] = Region("Spirit Temple MQ Symphony Room", SCENE_SPIRIT_TEMPLE, false, {RA_SPIRIT_TEMPLE}, {}, {}, {
	Entrance(RR_SPIRIT_TEMPLE_MQ_1F_EAST, []{return logic->SmallKeys(RR_SPIRIT_TEMPLE, 7);}),
	Entrance(RR_SPIRIT_TEMPLE_MQ_AFTER_SYMPHONY_ROOM, []{return (logic->CanUse(RG_MEGATON_HAMMER) && (logic->CanUse(RG_SONG_OF_TIME) && (logic->CanUse(RG_EPONAS_SONG) && (logic->CanUse(RG_SUNS_SONG) && (logic->CanUse(RG_SONG_OF_STORMS) && logic->CanUse(RG_ZELDAS_LULLABY))))));}),
});
areaTable[RR_SPIRIT_TEMPLE_MQ_AFTER_SYMPHONY_ROOM] = Region("Spirit Temple MQ After Symphony Room", SCENE_SPIRIT_TEMPLE, false, {RA_SPIRIT_TEMPLE}, {}, {
	LOCATION(RC_SPIRIT_TEMPLE_MQ_SYMPHONY_ROOM_CHEST, logic->CanPassEnemy(RE_BIG_SKULLTULA)),
	LOCATION(RC_SPIRIT_TEMPLE_MQ_GS_SYMPHONY_ROOM, logic->CanGetEnemyDrop(RE_GOLD_SKULLTULA, ED_BOOMERANG)),
}, {
	Entrance(RR_SPIRIT_TEMPLE_MQ_SYMPHONY_ROOM, []{return true;}),
});
areaTable[RR_SPIRIT_TEMPLE_MQ_FOUR_BEAMOS_ROOM] = Region("Spirit Temple MQ Four Beamos Room", SCENE_SPIRIT_TEMPLE, false, {RA_SPIRIT_TEMPLE}, {}, {
	LOCATION(RC_SPIRIT_TEMPLE_MQ_BEAMOS_ROOM_CHEST, logic->CanKillEnemy(RE_BEAMOS)),
	LOCATION(RC_SPIRIT_TEMPLE_MQ_BEAMOS_SMALL_CRATE, (logic->CanKillEnemy(RE_BEAMOS) && (logic->CanUse(RG_SONG_OF_TIME) && logic->CanBreakSmallCrates()))),
}, {
	Entrance(RR_SPIRIT_TEMPLE_MQ_STATUE_ROOM_EAST, []{return (logic->CanAvoidEnemy(RE_BEAMOS, true, 4) && (logic->CanUse(RG_SONG_OF_TIME) && (logic->SmallKeys(RR_SPIRIT_TEMPLE, 5) && logic->CanUse(RG_HOOKSHOT))));}),
	Entrance(RR_SPIRIT_TEMPLE_MQ_SOT_SUN_ROOM, []{return (logic->CanAvoidEnemy(RE_BEAMOS, true, 4) && logic->CanUse(RG_SONG_OF_TIME));}),
	Entrance(RR_SPIRIT_TEMPLE_MQ_BIG_WALL, []{return logic->SmallKeys(RR_SPIRIT_TEMPLE, 6);}),
});
areaTable[RR_SPIRIT_TEMPLE_MQ_SOT_SUN_ROOM] = Region("Spirit Temple MQ SoT Sun Room", SCENE_SPIRIT_TEMPLE, false, {RA_SPIRIT_TEMPLE}, {}, {
	LOCATION(RC_SPIRIT_TEMPLE_MQ_CHEST_SWITCH_CHEST, true),
	LOCATION(RC_SPIRIT_TEMPLE_MQ_DINALFOS_ROOM_SUN_FAIRY, logic->CanUse(RG_SUNS_SONG)),
}, {
	Entrance(RR_SPIRIT_TEMPLE_MQ_FOUR_BEAMOS_ROOM, []{return true;}),
	Entrance(RR_SPIRIT_TEMPLE_MQ_EAST_STAIRS_TO_HAND, []{return logic->CanJumpslash();}),
	Entrance(RR_SPIRIT_TEMPLE_MQ_3F_GIBDO_ROOM, []{return Here(RR_SPIRIT_TEMPLE_MQ_SOT_SUN_ROOM, []{return ((logic->IsAdult || logic->CanUse(RG_SONG_OF_TIME)) && logic->CanUse(RG_MIRROR_SHIELD));});}),
});
areaTable[RR_SPIRIT_TEMPLE_MQ_EAST_STAIRS_TO_HAND] = Region("Spirit Temple MQ East Stairs to Hand", SCENE_SPIRIT_TEMPLE, false, {RA_SPIRIT_TEMPLE}, {}, {}, {
	Entrance(RR_SPIRIT_TEMPLE_MQ_SOT_SUN_ROOM, []{return true;}),
	Entrance(RR_SPIRIT_TEMPLE_MQ_EAST_IRON_KNUCKLE, []{return (((bool)ctx->GetTrickOption(RT_LENS_SPIRIT_MQ) || logic->CanUse(RG_LENS_OF_TRUTH)) && Here(RR_SPIRIT_TEMPLE_MQ_EAST_STAIRS_TO_HAND, []{return logic->CanKillEnemy(RE_FLOORMASTER);}));}),
});
areaTable[RR_SPIRIT_TEMPLE_MQ_EAST_IRON_KNUCKLE] = Region("Spirit Temple MQ East Iron Knuckle", SCENE_SPIRIT_TEMPLE, false, {RA_SPIRIT_TEMPLE}, {}, {}, {
	Entrance(RR_SPIRIT_TEMPLE_MQ_EAST_STAIRS_TO_HAND, []{return true;}),
	Entrance(RR_SPIRIT_TEMPLE_MQ_MIRROR_SHIELD_HAND, []{return Here(RR_SPIRIT_TEMPLE_MQ_EAST_IRON_KNUCKLE, []{return logic->CanKillEnemy(RE_IRON_KNUCKLE);});}),
});
areaTable[RR_SPIRIT_TEMPLE_MQ_MIRROR_SHIELD_HAND] = Region("Spirit Temple MQ Mirror Shield Hand", SCENE_SPIRIT_TEMPLE, false, {RA_SPIRIT_TEMPLE}, {}, {
	LOCATION(RC_SPIRIT_TEMPLE_MIRROR_SHIELD_CHEST, true),
}, {
	Entrance(RR_SPIRIT_TEMPLE_MQ_SILVER_GAUNTLETS_HAND, []{return logic->CanUse(RG_LONGSHOT);}),
	Entrance(RR_SPIRIT_TEMPLE_MQ_EAST_IRON_KNUCKLE, []{return true;}),
	Entrance(RR_DESERT_COLOSSUS, []{return true;}),
});
areaTable[RR_SPIRIT_TEMPLE_MQ_3F_GIBDO_ROOM] = Region("Spirit Temple MQ 3F Gibdo Room", SCENE_SPIRIT_TEMPLE, false, {RA_SPIRIT_TEMPLE}, {}, {
	LOCATION(RC_SPIRIT_TEMPLE_MQ_BOSS_KEY_CHEST, true),
}, {
	Entrance(RR_SPIRIT_TEMPLE_MQ_SOT_SUN_ROOM, []{return true;}),
});
areaTable[RR_SPIRIT_TEMPLE_MQ_BIG_WALL] = Region("Spirit Temple MQ Big Wall", SCENE_SPIRIT_TEMPLE, false, {RA_SPIRIT_TEMPLE}, {}, {
	LOCATION(RC_SPIRIT_TEMPLE_MQ_LONG_CLIMB_POT_1, logic->CanBreakPots()),
	LOCATION(RC_SPIRIT_TEMPLE_MQ_LONG_CLIMB_POT_2, logic->CanBreakPots()),
}, {
	Entrance(RR_SPIRIT_TEMPLE_MQ_FOUR_BEAMOS_ROOM, []{return true;}),
	Entrance(RR_SPIRIT_TEMPLE_MQ_4F_CENTRAL, []{return logic->CanKillEnemy(RE_KEESE);}),
});
areaTable[RR_SPIRIT_TEMPLE_MQ_4F_CENTRAL] = Region("Spirit Temple MQ 4F Central", SCENE_SPIRIT_TEMPLE, false, {RA_SPIRIT_TEMPLE}, {}, {
	LOCATION(RC_SPIRIT_TEMPLE_MQ_BEFORE_MIRROR_POT_1, logic->CanBreakPots()),
	LOCATION(RC_SPIRIT_TEMPLE_MQ_BEFORE_MIRROR_POT_2, logic->CanBreakPots()),
}, {
	Entrance(RR_SPIRIT_TEMPLE_MQ_BIG_WALL, []{return true;}),
	Entrance(RR_SPIRIT_TEMPLE_MQ_NINE_CHAIRS_ROOM, []{return logic->SmallKeys(RR_SPIRIT_TEMPLE, 7);}),
	Entrance(RR_SPIRIT_TEMPLE_MQ_BIG_MIRROR_ROOM, []{return logic->CanUse(RG_ZELDAS_LULLABY);}),
});
areaTable[RR_SPIRIT_TEMPLE_MQ_NINE_CHAIRS_ROOM] = Region("Spirit Temple MQ Nine Chairs Room", SCENE_SPIRIT_TEMPLE, false, {RA_SPIRIT_TEMPLE}, {}, {
	LOCATION(RC_SPIRIT_TEMPLE_MQ_GS_NINE_THRONES_ROOM_WEST, logic->CanGetEnemyDrop(RE_GOLD_SKULLTULA, ED_BOOMERANG)),
	LOCATION(RC_SPIRIT_TEMPLE_MQ_GS_NINE_THRONES_ROOM_NORTH, logic->CanGetEnemyDrop(RE_GOLD_SKULLTULA)),
}, {
	Entrance(RR_SPIRIT_TEMPLE_MQ_4F_CENTRAL, []{return true;}),
});
areaTable[RR_SPIRIT_TEMPLE_MQ_BIG_MIRROR_ROOM] = Region("Spirit Temple MQ Big Mirror Room", SCENE_SPIRIT_TEMPLE, false, {RA_SPIRIT_TEMPLE}, {}, {
	LOCATION(RC_SPIRIT_TEMPLE_MQ_BIG_MIRROR_POT_1, logic->CanBreakPots()),
	LOCATION(RC_SPIRIT_TEMPLE_MQ_BIG_MIRROR_POT_2, logic->CanBreakPots()),
	LOCATION(RC_SPIRIT_TEMPLE_MQ_BIG_MIRROR_POT_3, logic->CanBreakPots()),
	LOCATION(RC_SPIRIT_TEMPLE_MQ_BIG_MIRROR_POT_4, logic->CanBreakPots()),
	LOCATION(RC_SPIRIT_TEMPLE_MQ_BIG_MIRROR_CRATE_1, logic->CanBreakCrates()),
	LOCATION(RC_SPIRIT_TEMPLE_MQ_BIG_MIRROR_CRATE_4, logic->CanBreakCrates()),
	LOCATION(RC_SPIRIT_TEMPLE_MQ_BIG_MIRROR_CRATE_2, logic->CanBreakCrates()),
	LOCATION(RC_SPIRIT_TEMPLE_MQ_BIG_MIRROR_CRATE_3, logic->CanBreakCrates()),
}, {
	Entrance(RR_SPIRIT_TEMPLE_MQ_4F_CENTRAL, []{return true;}),
	Entrance(RR_SPIRIT_TEMPLE_MQ_BIG_MIRROR_CAVE, []{return Here(RR_SPIRIT_TEMPLE_MQ_BIG_MIRROR_ROOM, []{return logic->CanUse(RG_MEGATON_HAMMER);});}),
});
areaTable[RR_SPIRIT_TEMPLE_MQ_BIG_MIRROR_CAVE] = Region("Spirit Temple MQ Big Mirror Cave", SCENE_SPIRIT_TEMPLE, false, {RA_SPIRIT_TEMPLE}, {}, {
	LOCATION(RC_SPIRIT_TEMPLE_MQ_MIRROR_PUZZLE_INVISIBLE_CHEST, ((bool)ctx->GetTrickOption(RT_LENS_SPIRIT_MQ) || logic->CanUse(RG_LENS_OF_TRUTH))),
}, {
	Entrance(RR_SPIRIT_TEMPLE_MQ_INSIDE_STATUE_HEAD, []{return (Here(RR_SPIRIT_TEMPLE_MQ_BIG_MIRROR_CAVE, []{return logic->CanUse(RG_MIRROR_SHIELD);}) && logic->CanUse(RG_HOOKSHOT));}),
	Entrance(RR_SPIRIT_TEMPLE_MQ_STATUE_ROOM, []{return Here(RR_SPIRIT_TEMPLE_MQ_BIG_MIRROR_CAVE, []{return logic->CanUse(RG_MIRROR_SHIELD);});}),
});
areaTable[RR_SPIRIT_TEMPLE_MQ_INSIDE_STATUE_HEAD] = Region("Spirit Temple MQ Inside Statue Head", SCENE_SPIRIT_TEMPLE, false, {RA_SPIRIT_TEMPLE}, {}, {}, {
	Entrance(RR_SPIRIT_TEMPLE_MQ_LOBBY, []{return true;}),
	Entrance(RR_SPIRIT_TEMPLE_BOSS_ENTRYWAY, []{return true;}),
});
areaTable[RR_SPIRIT_TEMPLE_BOSS_ENTRYWAY] = Region("Spirit Temple Boss Entryway", SCENE_SPIRIT_TEMPLE, false, {RA_SPIRIT_TEMPLE}, {}, {}, {
	Entrance(RR_SPIRIT_TEMPLE_INSIDE_STATUE_HEAD, []{return (ctx->GetDungeon(Rando::SPIRIT_TEMPLE)->IsVanilla() && false);}),
	Entrance(RR_SPIRIT_TEMPLE_MQ_INSIDE_STATUE_HEAD, []{return (ctx->GetDungeon(Rando::SPIRIT_TEMPLE)->IsMQ() && false);}),
	Entrance(RR_SPIRIT_TEMPLE_BOSS_ROOM, []{return logic->HasItem(RG_SPIRIT_TEMPLE_BOSS_KEY);}),
});
areaTable[RR_SPIRIT_TEMPLE_BOSS_ROOM] = Region("Spirit Temple Boss Room", SCENE_SPIRIT_TEMPLE_BOSS, false, {}, {
	EventAccess(&logic->SpiritTempleClear, []{return logic->CanKillEnemy(RE_TWINROVA);}),
}, {
	LOCATION(RC_SPIRIT_TEMPLE_TWINROVA_HEART, logic->SpiritTempleClear),
	LOCATION(RC_TWINROVA, logic->SpiritTempleClear),
}, {
	Entrance(RR_SPIRIT_TEMPLE_BOSS_ENTRYWAY, []{return false;}),
	Entrance(RR_DESERT_COLOSSUS, []{return logic->SpiritTempleClear;}, "", false),
});
areaTable[RR_SHADOW_TEMPLE_BEGINNING] = Region("Shadow Temple Beginning", SCENE_SHADOW_TEMPLE, false, {RA_SHADOW_TEMPLE}, {
	EventAccess(&logic->NutPot, []{return true;}),
}, {
	LOCATION(RC_SHADOW_TEMPLE_MAP_CHEST, logic->CanJumpslashExceptHammer()),
	LOCATION(RC_SHADOW_TEMPLE_HOVER_BOOTS_CHEST, logic->CanKillEnemy(RE_DEAD_HAND)),
	LOCATION(RC_SHADOW_TEMPLE_NEAR_DEAD_HAND_POT_1, logic->CanBreakPots()),
	LOCATION(RC_SHADOW_TEMPLE_WHISPERING_WALLS_POT_1, logic->CanBreakPots()),
	LOCATION(RC_SHADOW_TEMPLE_WHISPERING_WALLS_POT_2, logic->CanBreakPots()),
	LOCATION(RC_SHADOW_TEMPLE_WHISPERING_WALLS_POT_3, logic->CanBreakPots()),
	LOCATION(RC_SHADOW_TEMPLE_WHISPERING_WALLS_POT_4, logic->CanBreakPots()),
	LOCATION(RC_SHADOW_TEMPLE_WHISPERING_WALLS_POT_5, logic->CanBreakPots()),
	LOCATION(RC_SHADOW_TEMPLE_MAP_CHEST_POT_1, logic->CanBreakPots()),
	LOCATION(RC_SHADOW_TEMPLE_MAP_CHEST_POT_2, logic->CanBreakPots()),
}, {
	Entrance(RR_SHADOW_TEMPLE_ENTRYWAY, []{return true;}),
	Entrance(RR_SHADOW_TEMPLE_FIRST_BEAMOS, []{return logic->CanUse(RG_HOVER_BOOTS);}),
});
areaTable[RR_SHADOW_TEMPLE_FIRST_BEAMOS] = Region("Shadow Temple First Beamos", SCENE_SHADOW_TEMPLE, false, {RA_SHADOW_TEMPLE}, {
	EventAccess(&logic->FairyPot, []{return true;}),
}, {
	LOCATION(RC_SHADOW_TEMPLE_COMPASS_CHEST, logic->CanJumpslashExceptHammer()),
	LOCATION(RC_SHADOW_TEMPLE_EARLY_SILVER_RUPEE_CHEST, (logic->CanUse(RG_HOVER_BOOTS) || logic->CanUse(RG_HOOKSHOT))),
	LOCATION(RC_SHADOW_TEMPLE_GS_NEAR_SHIP, false),
	LOCATION(RC_SHADOW_TEMPLE_BEAMOS_STORM_FAIRY, logic->CanUse(RG_SONG_OF_STORMS)),
}, {
	Entrance(RR_SHADOW_TEMPLE_HUGE_PIT, []{return (logic->HasExplosives() && (logic->IsAdult && logic->SmallKeys(RR_SHADOW_TEMPLE, 1, 2)));}),
	Entrance(RR_SHADOW_TEMPLE_BEYOND_BOAT, []{return false;}),
});
areaTable[RR_SHADOW_TEMPLE_HUGE_PIT] = Region("Shadow Temple Huge Pit", SCENE_SHADOW_TEMPLE, false, {RA_SHADOW_TEMPLE}, {}, {
	LOCATION(RC_SHADOW_TEMPLE_INVISIBLE_BLADES_VISIBLE_CHEST, logic->CanJumpslashExceptHammer()),
	LOCATION(RC_SHADOW_TEMPLE_INVISIBLE_BLADES_INVISIBLE_CHEST, logic->CanJumpslashExceptHammer()),
	LOCATION(RC_SHADOW_TEMPLE_FALLING_SPIKES_LOWER_CHEST, true),
	LOCATION(RC_SHADOW_TEMPLE_FALLING_SPIKES_UPPER_CHEST, (((bool)ctx->GetTrickOption(RT_SHADOW_UMBRELLA) && logic->CanUse(RG_HOVER_BOOTS)) || logic->HasItem(RG_GORONS_BRACELET))),
	LOCATION(RC_SHADOW_TEMPLE_FALLING_SPIKES_SWITCH_CHEST, (((bool)ctx->GetTrickOption(RT_SHADOW_UMBRELLA) && logic->CanUse(RG_HOVER_BOOTS)) || logic->HasItem(RG_GORONS_BRACELET))),
	LOCATION(RC_SHADOW_TEMPLE_INVISIBLE_SPIKES_CHEST, (logic->SmallKeys(RR_SHADOW_TEMPLE, 2, 3) && (((bool)ctx->GetTrickOption(RT_LENS_SHADOW_PLATFORM) && (bool)ctx->GetTrickOption(RT_LENS_SHADOW)) || logic->CanUse(RG_LENS_OF_TRUTH)))),
	LOCATION(RC_SHADOW_TEMPLE_FREESTANDING_KEY, (logic->SmallKeys(RR_SHADOW_TEMPLE, 2, 3) && ((((bool)ctx->GetTrickOption(RT_LENS_SHADOW_PLATFORM) && (bool)ctx->GetTrickOption(RT_LENS_SHADOW)) || logic->CanUse(RG_LENS_OF_TRUTH)) && (logic->CanUse(RG_HOOKSHOT) && (logic->CanUse(RG_BOMB_BAG) || (logic->HasItem(RG_GORONS_BRACELET) || ((bool)ctx->GetTrickOption(RT_SHADOW_FREESTANDING_KEY) && logic->CanUse(RG_BOMBCHU_5)))))))),
	LOCATION(RC_SHADOW_TEMPLE_GS_LIKE_LIKE_ROOM, logic->CanJumpslashExceptHammer()),
	LOCATION(RC_SHADOW_TEMPLE_GS_FALLING_SPIKES_ROOM, (logic->CanUse(RG_HOOKSHOT) || ((bool)ctx->GetTrickOption(RT_SHADOW_UMBRELLA_GS) && logic->CanUse(RG_HOVER_BOOTS)))),
	LOCATION(RC_SHADOW_TEMPLE_GS_SINGLE_GIANT_POT, (logic->SmallKeys(RR_SHADOW_TEMPLE, 2, 3) && ((((bool)ctx->GetTrickOption(RT_LENS_SHADOW_PLATFORM) && (bool)ctx->GetTrickOption(RT_LENS_SHADOW)) || logic->CanUse(RG_LENS_OF_TRUTH)) && logic->CanUse(RG_HOOKSHOT)))),
	LOCATION(RC_SHADOW_TEMPLE_FALLING_SPIKES_POT_1, logic->CanBreakPots()),
	LOCATION(RC_SHADOW_TEMPLE_FALLING_SPIKES_POT_2, logic->CanBreakPots()),
	LOCATION(RC_SHADOW_TEMPLE_FALLING_SPIKES_POT_3, ((logic->CanBreakPots() && ((bool)ctx->GetTrickOption(RT_SHADOW_UMBRELLA) && logic->CanUse(RG_HOVER_BOOTS))) || logic->HasItem(RG_GORONS_BRACELET))),
	LOCATION(RC_SHADOW_TEMPLE_FALLING_SPIKES_POT_4, ((logic->CanBreakPots() && ((bool)ctx->GetTrickOption(RT_SHADOW_UMBRELLA) && logic->CanUse(RG_HOVER_BOOTS))) || logic->HasItem(RG_GORONS_BRACELET))),
	LOCATION(RC_SHADOW_TEMPLE_INVISIBLE_BLADES_LEFT_HEART, ((logic->CanUse(RG_SONG_OF_TIME) && logic->IsAdult) || logic->CanUse(RG_BOOMERANG))),
	LOCATION(RC_SHADOW_TEMPLE_INVISIBLE_BLADES_RIGHT_HEART, ((logic->CanUse(RG_SONG_OF_TIME) && logic->IsAdult) || logic->CanUse(RG_BOOMERANG))),
	LOCATION(RC_SHADOW_TEMPLE_PIT_STORM_FAIRY, logic->CanUse(RG_SONG_OF_STORMS)),
}, {
	Entrance(RR_SHADOW_TEMPLE_WIND_TUNNEL, []{return ((((bool)ctx->GetTrickOption(RT_LENS_SHADOW_PLATFORM) && (bool)ctx->GetTrickOption(RT_LENS_SHADOW)) || logic->CanUse(RG_LENS_OF_TRUTH)) && (logic->CanUse(RG_HOOKSHOT) && logic->SmallKeys(RR_SHADOW_TEMPLE, 3, 4)));}),
});
areaTable[RR_SHADOW_TEMPLE_WIND_TUNNEL] = Region("Shadow Temple Wind Tunnel", SCENE_SHADOW_TEMPLE, false, {RA_SHADOW_TEMPLE}, {}, {
	LOCATION(RC_SHADOW_TEMPLE_WIND_HINT_CHEST, true),
	LOCATION(RC_SHADOW_TEMPLE_AFTER_WIND_ENEMY_CHEST, logic->CanKillEnemy(RE_GIBDO, ED_CLOSE, true, 2)),
	LOCATION(RC_SHADOW_TEMPLE_AFTER_WIND_HIDDEN_CHEST, logic->HasExplosives()),
	LOCATION(RC_SHADOW_TEMPLE_GS_NEAR_SHIP, (logic->CanUse(RG_LONGSHOT) && logic->SmallKeys(RR_SHADOW_TEMPLE, 4, 5))),
	LOCATION(RC_SHADOW_TEMPLE_WIND_HINT_SUN_FAIRY, logic->CanUse(RG_SUNS_SONG)),
	LOCATION(RC_SHADOW_TEMPLE_AFTER_WIND_POT_1, logic->CanBreakPots()),
	LOCATION(RC_SHADOW_TEMPLE_AFTER_WIND_POT_2, logic->CanBreakPots()),
	LOCATION(RC_SHADOW_TEMPLE_SCARECROW_NORTH_HEART, (logic->CanUse(RG_DISTANT_SCARECROW) && logic->SmallKeys(RR_SHADOW_TEMPLE, 4, 5))),
	LOCATION(RC_SHADOW_TEMPLE_SCARECROW_SOUTH_HEART, (logic->CanUse(RG_DISTANT_SCARECROW) && logic->SmallKeys(RR_SHADOW_TEMPLE, 4, 5))),
}, {
	Entrance(RR_SHADOW_TEMPLE_BEYOND_BOAT, []{return (logic->CanJumpslashExceptHammer() && (logic->CanUse(RG_ZELDAS_LULLABY) && logic->SmallKeys(RR_SHADOW_TEMPLE, 4, 5)));}),
});
areaTable[RR_SHADOW_TEMPLE_BEYOND_BOAT] = Region("Shadow Temple Beyond Boat", SCENE_SHADOW_TEMPLE, false, {RA_SHADOW_TEMPLE}, {}, {
	LOCATION(RC_SHADOW_TEMPLE_SPIKE_WALLS_LEFT_CHEST, logic->CanUse(RG_DINS_FIRE)),
	LOCATION(RC_SHADOW_TEMPLE_BOSS_KEY_CHEST, logic->CanUse(RG_DINS_FIRE)),
	LOCATION(RC_SHADOW_TEMPLE_INVISIBLE_FLOORMASTER_CHEST, logic->CanKillEnemy(RE_FLOORMASTER)),
	LOCATION(RC_SHADOW_TEMPLE_GS_TRIPLE_GIANT_POT, (logic->IsAdult && logic->CanAttack())),
	LOCATION(RC_SHADOW_TEMPLE_AFTER_BOAT_POT_1, logic->CanBreakPots()),
	LOCATION(RC_SHADOW_TEMPLE_AFTER_BOAT_POT_2, logic->CanBreakPots()),
	LOCATION(RC_SHADOW_TEMPLE_AFTER_BOAT_POT_3, (logic->CanBreakPots() && (logic->CanUse(RG_FAIRY_BOW) || (logic->CanUse(RG_DISTANT_SCARECROW) || ((bool)ctx->GetTrickOption(RT_SHADOW_STATUE) && logic->CanUse(RG_BOMBCHU_5)))))),
	LOCATION(RC_SHADOW_TEMPLE_AFTER_BOAT_POT_4, (logic->CanBreakPots() && (logic->CanUse(RG_FAIRY_BOW) || (logic->CanUse(RG_DISTANT_SCARECROW) || ((bool)ctx->GetTrickOption(RT_SHADOW_STATUE) && logic->CanUse(RG_BOMBCHU_5)))))),
	LOCATION(RC_SHADOW_TEMPLE_SPIKE_WALLS_POT_1, logic->CanBreakPots()),
	LOCATION(RC_SHADOW_TEMPLE_FLOORMASTER_POT_1, logic->CanBreakPots()),
	LOCATION(RC_SHADOW_TEMPLE_FLOORMASTER_POT_2, logic->CanBreakPots()),
	LOCATION(RC_SHADOW_TEMPLE_AFTER_SHIP_UPPER_LEFT_HEART, logic->CanUse(RG_DISTANT_SCARECROW)),
	LOCATION(RC_SHADOW_TEMPLE_AFTER_SHIP_UPPER_RIGHT_HEART, logic->CanUse(RG_DISTANT_SCARECROW)),
	LOCATION(RC_SHADOW_TEMPLE_AFTER_SHIP_LOWER_HEART, (((logic->CanUse(RG_FAIRY_BOW) || (logic->CanUse(RG_DISTANT_SCARECROW) || ((bool)ctx->GetTrickOption(RT_SHADOW_STATUE) && logic->CanUse(RG_BOMBCHU_5)))) && logic->CanUse(RG_SONG_OF_TIME)) || (logic->CanUse(RG_DISTANT_SCARECROW) && logic->CanUse(RG_HOVER_BOOTS)))),
}, {
	Entrance(RR_SHADOW_TEMPLE_BOSS_ENTRYWAY, []{return ((logic->CanUse(RG_FAIRY_BOW) || (logic->CanUse(RG_DISTANT_SCARECROW) || ((bool)ctx->GetTrickOption(RT_SHADOW_STATUE) && logic->CanUse(RG_BOMBCHU_5)))) && (logic->SmallKeys(RR_SHADOW_TEMPLE, 5) && logic->CanUse(RG_HOVER_BOOTS)));}),
});
areaTable[RR_SHADOW_TEMPLE_MQ_ENTRYWAY] = Region("Invalid Region", SCENE_ID_MAX, false, {}, {}, {}, {});
areaTable[RR_SHADOW_TEMPLE_MQ_BEGINNING] = Region("Shadow Temple MQ Beginning", SCENE_SHADOW_TEMPLE, false, {RA_SHADOW_TEMPLE}, {}, {}, {
	Entrance(RR_SHADOW_TEMPLE_ENTRYWAY, []{return true;}),
	Entrance(RR_SHADOW_TEMPLE_MQ_SPINNER_ROOM, []{return (logic->CanUse(RG_HOVER_BOOTS) || logic->CanUse(RG_HOOKSHOT));}),
});
areaTable[RR_SHADOW_TEMPLE_MQ_SPINNER_ROOM] = Region("Shadow Temple MQ Spinner Room", SCENE_SHADOW_TEMPLE, false, {RA_SHADOW_TEMPLE}, {}, {
	LOCATION(RC_SHADOW_TEMPLE_MQ_TRUTH_SPINNER_SMALL_CRATE_1, logic->CanBreakSmallCrates()),
	LOCATION(RC_SHADOW_TEMPLE_MQ_TRUTH_SPINNER_SMALL_CRATE_2, logic->CanBreakSmallCrates()),
	LOCATION(RC_SHADOW_TEMPLE_MQ_TRUTH_SPINNER_SMALL_CRATE_3, logic->CanBreakSmallCrates()),
	LOCATION(RC_SHADOW_TEMPLE_MQ_TRUTH_SPINNER_SMALL_CRATE_4, logic->CanBreakSmallCrates()),
}, {
	Entrance(RR_SHADOW_TEMPLE_ENTRYWAY, []{return true;}),
	Entrance(RR_SHADOW_TEMPLE_MQ_FIRST_BEAMOS, []{return (Here(RR_SHADOW_TEMPLE_MQ_SPINNER_ROOM, []{return (logic->CanUse(RG_HOVER_BOOTS) || ((bool)ctx->GetTrickOption(RT_LENS_SHADOW_MQ) || logic->CanUse(RG_LENS_OF_TRUTH)));}) && (logic->CanUse(RG_HOVER_BOOTS) || (Here(RR_SHADOW_TEMPLE_MQ_SPINNER_ROOM, []{return logic->CanUse(RG_FIRE_ARROWS);}) || ((bool)ctx->GetTrickOption(RT_SHADOW_MQ_GAP) && (logic->CanUse(RG_LONGSHOT) && logic->CanJumpslashExceptHammer())))));}),
	Entrance(RR_SHADOW_TEMPLE_MQ_DEAD_HAND_AREA, []{return (Here(RR_SHADOW_TEMPLE_MQ_SPINNER_ROOM, []{return logic->HasExplosives();}) && (logic->SmallKeys(RR_SHADOW_TEMPLE, 6) && ((bool)ctx->GetTrickOption(RT_LENS_SHADOW_MQ) || logic->CanUse(RG_LENS_OF_TRUTH))));}),
});
areaTable[RR_SHADOW_TEMPLE_MQ_DEAD_HAND_AREA] = Region("Shadow Temple MQ Dead Hand Region", SCENE_SHADOW_TEMPLE, false, {RA_SHADOW_TEMPLE}, {}, {
	LOCATION(RC_SHADOW_TEMPLE_MQ_COMPASS_CHEST, logic->CanKillEnemy(RE_REDEAD)),
	LOCATION(RC_SHADOW_TEMPLE_MQ_HOVER_BOOTS_CHEST, (logic->CanKillEnemy(RE_DEAD_HAND) && ((logic->IsChild || logic->CanUse(RG_SONG_OF_TIME)) && logic->CanHitEyeTargets()))),
	LOCATION(RC_SHADOW_TEMPLE_MQ_WHISPERING_WALLS_POT_1, logic->CanBreakPots()),
	LOCATION(RC_SHADOW_TEMPLE_MQ_WHISPERING_WALLS_POT_2, logic->CanBreakPots()),
	LOCATION(RC_SHADOW_TEMPLE_MQ_ENTRANCE_REDEAD_POT_1, logic->CanBreakPots()),
	LOCATION(RC_SHADOW_TEMPLE_MQ_ENTRANCE_REDEAD_POT_2, logic->CanBreakPots()),
}, {
	Entrance(RR_SHADOW_TEMPLE_MQ_SPINNER_ROOM, []{return true;}),
});
areaTable[RR_SHADOW_TEMPLE_MQ_FIRST_BEAMOS] = Region("Shadow Temple MQ First Beamos", SCENE_SHADOW_TEMPLE, false, {RA_SHADOW_TEMPLE}, {}, {
	LOCATION(RC_SHADOW_TEMPLE_MQ_EARLY_GIBDOS_CHEST, (logic->CanKillEnemy(RE_GIBDO) && ((bool)ctx->GetTrickOption(RT_LENS_SHADOW_MQ) || logic->CanUse(RG_LENS_OF_TRUTH)))),
	LOCATION(RC_SHADOW_TEMPLE_MQ_BEAMOS_STORM_FAIRY, logic->CanUse(RG_SONG_OF_STORMS)),
}, {
	Entrance(RR_SHADOW_TEMPLE_MQ_UPPER_HUGE_PIT, []{return (logic->HasExplosives() && logic->SmallKeys(RR_SHADOW_TEMPLE, 2));}),
	Entrance(RR_SHADOW_TEMPLE_MQ_B2_SPINNING_BLADE_ROOM, []{return ((bool)ctx->GetTrickOption(RT_LENS_SHADOW_MQ) || logic->CanUse(RG_LENS_OF_TRUTH));}),
});
areaTable[RR_SHADOW_TEMPLE_MQ_B2_SPINNING_BLADE_ROOM] = Region("Shadow Temple MQ B2 Spinning Blade Room", SCENE_SHADOW_TEMPLE, false, {RA_SHADOW_TEMPLE}, {}, {
	LOCATION(RC_SHADOW_TEMPLE_MQ_MAP_CHEST, (logic->CanPassEnemy(RE_BIG_SKULLTULA) && (logic->CanUse(RG_HOOKSHOT) || (logic->IsAdult && logic->CanUse(RG_HOVER_BOOTS))))),
}, {
	Entrance(RR_SHADOW_TEMPLE_MQ_FIRST_BEAMOS, []{return Here(RR_SHADOW_TEMPLE_MQ_B2_SPINNING_BLADE_ROOM, []{return (logic->CanKillEnemy(RE_BIG_SKULLTULA) && (logic->CanUse(RG_HOOKSHOT) || (logic->IsAdult && logic->CanUse(RG_HOVER_BOOTS))));});}),
	Entrance(RR_SHADOW_TEMPLE_MQ_SHORTCUT_PATH, []{return logic->CanPassEnemy(RE_BIG_SKULLTULA);}),
});
areaTable[RR_SHADOW_TEMPLE_MQ_SHORTCUT_PATH] = Region("Shadow Temple MQ Shortcut Path", SCENE_SHADOW_TEMPLE, false, {RA_SHADOW_TEMPLE}, {}, {
	LOCATION(RC_SHADOW_TEMPLE_MQ_NEAR_SHIP_INVISIBLE_CHEST, ((bool)ctx->GetTrickOption(RT_LENS_SHADOW_MQ) || logic->CanUse(RG_LENS_OF_TRUTH))),
}, {
	Entrance(RR_SHADOW_TEMPLE_MQ_B2_SPINNING_BLADE_ROOM, []{return logic->CanPassEnemy(RE_BIG_SKULLTULA);}),
	Entrance(RR_SHADOW_TEMPLE_MQ_DOCK, []{return logic->ShadowShortcutBlock;}),
});
areaTable[RR_SHADOW_TEMPLE_MQ_B2_TO_B3_CORRIDOR] = Region("Shadow Temple MQ B2 to B3 Corridor", SCENE_SHADOW_TEMPLE, false, {RA_SHADOW_TEMPLE}, {}, {}, {
	Entrance(RR_SHADOW_TEMPLE_MQ_FIRST_BEAMOS, []{return logic->SmallKeys(RR_SHADOW_TEMPLE, 2);}),
	Entrance(RR_SHADOW_TEMPLE_MQ_UPPER_HUGE_PIT, []{return true;}),
});
areaTable[RR_SHADOW_TEMPLE_MQ_UPPER_HUGE_PIT] = Region("Shadow Temple MQ Upper Huge Pit", SCENE_SHADOW_TEMPLE, false, {RA_SHADOW_TEMPLE}, {}, {
	LOCATION(RC_SHADOW_TEMPLE_MQ_PIT_STORM_FAIRY, logic->CanUse(RG_SONG_OF_STORMS)),
}, {
	Entrance(RR_SHADOW_TEMPLE_MQ_LOWER_HUGE_PIT, []{return ((logic->HasFireSource() && ((bool)ctx->GetTrickOption(RT_LENS_SHADOW_MQ) || logic->CanUse(RG_LENS_OF_TRUTH))) || (bool)ctx->GetTrickOption(RT_SHADOW_MQ_HUGE_PIT));}),
	Entrance(RR_SHADOW_TEMPLE_MQ_INVISIBLE_BLADES_ROOM, []{return ((bool)ctx->GetTrickOption(RT_LENS_SHADOW_MQ) || logic->CanUse(RG_LENS_OF_TRUTH));}),
});
areaTable[RR_SHADOW_TEMPLE_MQ_INVISIBLE_BLADES_ROOM] = Region("Shadow Temple MQ Invisible Blades Room", SCENE_SHADOW_TEMPLE, false, {RA_SHADOW_TEMPLE}, {}, {
	LOCATION(RC_SHADOW_TEMPLE_MQ_INVISIBLE_BLADES_VISIBLE_CHEST, ((logic->CanUse(RG_SONG_OF_TIME) || ((bool)ctx->GetTrickOption(RT_SHADOW_MQ_INVISIBLE_BLADES) && (logic->EffectiveHealth() > 1))) && ((bool)ctx->GetTrickOption(RT_LENS_SHADOW_MQ_INVISIBLE_BLADES) || (logic->IsChild || (logic->CanUse(RG_NAYRUS_LOVE) || logic->CanUse(RG_LENS_OF_TRUTH)))))),
	LOCATION(RC_SHADOW_TEMPLE_MQ_INVISIBLE_BLADES_INVISIBLE_CHEST, ((logic->CanUse(RG_SONG_OF_TIME) || ((bool)ctx->GetTrickOption(RT_SHADOW_MQ_INVISIBLE_BLADES) && (logic->EffectiveHealth() > 1))) && (((bool)ctx->GetTrickOption(RT_LENS_SHADOW_MQ) && ((bool)ctx->GetTrickOption(RT_LENS_SHADOW_MQ_INVISIBLE_BLADES) || (logic->IsChild || logic->CanUse(RG_NAYRUS_LOVE)))) || logic->CanUse(RG_LENS_OF_TRUTH)))),
	LOCATION(RC_SHADOW_TEMPLE_MQ_INVISIBLE_BLADES_LEFT_HEART, ((logic->CanUse(RG_SONG_OF_TIME) && logic->IsAdult) || (((bool)ctx->GetTrickOption(RT_SHADOW_MQ_INVISIBLE_BLADES) && (logic->EffectiveHealth() > 1)) || logic->CanUse(RG_BOOMERANG)))),
	LOCATION(RC_SHADOW_TEMPLE_MQ_INVISIBLE_BLADES_RIGHT_HEART, ((logic->CanUse(RG_SONG_OF_TIME) && logic->IsAdult) || (((bool)ctx->GetTrickOption(RT_SHADOW_MQ_INVISIBLE_BLADES) && (logic->EffectiveHealth() > 1)) || logic->CanUse(RG_BOOMERANG)))),
}, {
	Entrance(RR_SHADOW_TEMPLE_MQ_UPPER_HUGE_PIT, []{return true;}),
});
areaTable[RR_SHADOW_TEMPLE_MQ_LOWER_HUGE_PIT] = Region("Shadow Temple MQ Lower Huge Pit", SCENE_SHADOW_TEMPLE, false, {RA_SHADOW_TEMPLE}, {}, {
	LOCATION(RC_SHADOW_TEMPLE_MQ_BEAMOS_SILVER_RUPEES_CHEST, logic->CanUse(RG_LONGSHOT)),
}, {
	Entrance(RR_SHADOW_TEMPLE_MQ_STONE_UMBRELLA_ROOM, []{return Here(RR_SHADOW_TEMPLE_MQ_LOWER_HUGE_PIT, []{return (logic->CanJumpslash() || logic->HasExplosives());});}),
	Entrance(RR_SHADOW_TEMPLE_MQ_FLOOR_SPIKES_ROOM, []{return (logic->CanUse(RG_HOVER_BOOTS) && (((bool)ctx->GetTrickOption(RT_LENS_SHADOW_MQ_PLATFORM) || logic->CanUse(RG_LENS_OF_TRUTH)) && logic->SmallKeys(RR_SHADOW_TEMPLE, 3)));}),
});
areaTable[RR_SHADOW_TEMPLE_MQ_STONE_UMBRELLA_ROOM] = Region("Shadow Temple MQ Stone Umbrella Room", SCENE_SHADOW_TEMPLE, false, {RA_SHADOW_TEMPLE}, {}, {
	LOCATION(RC_SHADOW_TEMPLE_MQ_FALLING_SPIKES_LOWER_CHEST, true),
	LOCATION(RC_SHADOW_TEMPLE_MQ_GS_FALLING_SPIKES_ROOM, (logic->CanGetEnemyDrop(RE_GOLD_SKULLTULA, ED_BOOMERANG) || ((bool)ctx->GetTrickOption(RT_SHADOW_UMBRELLA_GS) && ((bool)ctx->GetTrickOption(RT_SHADOW_UMBRELLA) && (logic->CanUse(RG_HOVER_BOOTS) && (logic->CanStandingShield() && logic->CanUse(RG_MASTER_SWORD))))))),
	LOCATION(RC_SHADOW_TEMPLE_MQ_LOWER_UMBRELLA_WEST_POT, logic->CanBreakPots()),
	LOCATION(RC_SHADOW_TEMPLE_MQ_LOWER_UMBRELLA_EAST_POT, logic->CanBreakPots()),
	LOCATION(RC_SHADOW_TEMPLE_MQ_UPPER_UMBRELLA_SOUTH_POT, logic->CanUse(RG_BOOMERANG)),
}, {
	Entrance(RR_SHADOW_TEMPLE_MQ_LOWER_HUGE_PIT, []{return Here(RR_SHADOW_TEMPLE_MQ_STONE_UMBRELLA_ROOM, []{return ((bool)ctx->GetTrickOption(RT_VISIBLE_COLLISION) || logic->CanHitSwitch());});}),
	Entrance(RR_SHADOW_TEMPLE_MQ_UPPER_STONE_UMBRELLA, []{return (logic->IsAdult && (logic->HasItem(RG_GORONS_BRACELET) || ((bool)ctx->GetTrickOption(RT_SHADOW_UMBRELLA) && (logic->CanUse(RG_HOVER_BOOTS) && (logic->CanStandingShield() && logic->CanUse(RG_MASTER_SWORD))))));}),
});
areaTable[RR_SHADOW_TEMPLE_MQ_UPPER_STONE_UMBRELLA] = Region("Shadow Temple MQ Upper Stone Umbrella", SCENE_SHADOW_TEMPLE, false, {RA_SHADOW_TEMPLE}, {}, {
	LOCATION(RC_SHADOW_TEMPLE_MQ_FALLING_SPIKES_UPPER_CHEST, true),
	LOCATION(RC_SHADOW_TEMPLE_MQ_FALLING_SPIKES_SWITCH_CHEST, true),
	LOCATION(RC_SHADOW_TEMPLE_MQ_UPPER_UMBRELLA_NORTH_POT, logic->CanBreakPots()),
	LOCATION(RC_SHADOW_TEMPLE_MQ_UPPER_UMBRELLA_SOUTH_POT, logic->CanBreakPots()),
}, {
	Entrance(RR_SHADOW_TEMPLE_MQ_STONE_UMBRELLA_ROOM, []{return true;}),
});
areaTable[RR_SHADOW_TEMPLE_MQ_FLOOR_SPIKES_ROOM] = Region("Shadow Temple MQ Floor Spikes Room", SCENE_SHADOW_TEMPLE, false, {RA_SHADOW_TEMPLE}, {
	EventAccess(&logic->MQShadowFloorSpikeRupees, []{return (((bool)ctx->GetTrickOption(RT_LENS_SHADOW_MQ) || logic->CanUse(RG_LENS_OF_TRUTH)) && ((logic->CanUse(RG_LONGSHOT) || (logic->IsAdult && (logic->CanUse(RG_HOOKSHOT) && (logic->CanJumpslash() || (logic->CanUse(RG_HOVER_BOOTS) && Here(RR_SHADOW_TEMPLE_MQ_FLOOR_SPIKES_ROOM, []{return logic->CanKillEnemy(RE_REDEAD);})))))) && (logic->TakeDamage() || logic->CanUse(RG_HOVER_BOOTS))));}),
}, {
	LOCATION(RC_SHADOW_TEMPLE_MQ_INVISIBLE_SPIKES_CHEST, (logic->CanKillEnemy(RE_REDEAD) && ((bool)ctx->GetTrickOption(RT_LENS_SHADOW_MQ) || (logic->TakeDamage() || logic->CanUse(RG_LENS_OF_TRUTH))))),
}, {
	Entrance(RR_SHADOW_TEMPLE_MQ_STALFOS_ROOM, []{return logic->MQShadowFloorSpikeRupees;}),
	Entrance(RR_SHADOW_TEMPLE_MQ_WIND_TUNNEL, []{return (logic->SmallKeys(RR_SHADOW_TEMPLE, 4) && ((logic->CanUse(RG_LONGSHOT) || (logic->IsAdult && (logic->CanUse(RG_HOOKSHOT) && (logic->MQShadowFloorSpikeRupees || Here(RR_SHADOW_TEMPLE_MQ_FLOOR_SPIKES_ROOM, []{return logic->CanKillEnemy(RE_REDEAD);}))))) && (logic->CanJumpslash() || logic->CanUse(RG_HOVER_BOOTS))));}),
});
areaTable[RR_SHADOW_TEMPLE_MQ_STALFOS_ROOM] = Region("Shadow Temple MQ Stalfos Room", SCENE_SHADOW_TEMPLE, false, {RA_SHADOW_TEMPLE}, {}, {
	LOCATION(RC_SHADOW_TEMPLE_MQ_STALFOS_ROOM_CHEST, logic->CanKillEnemy(RE_STALFOS, ED_CLOSE, true, 2)),
}, {
	Entrance(RR_SHADOW_TEMPLE_MQ_FLOOR_SPIKES_ROOM, []{return Here(RR_SHADOW_TEMPLE_MQ_STALFOS_ROOM, []{return logic->CanKillEnemy(RE_STALFOS, ED_CLOSE, true, 2);});}),
});
areaTable[RR_SHADOW_TEMPLE_MQ_WIND_TUNNEL] = Region("Shadow Temple MQ Wind Tunnel", SCENE_SHADOW_TEMPLE, false, {RA_SHADOW_TEMPLE}, {}, {}, {
	Entrance(RR_SHADOW_TEMPLE_MQ_FLOOR_SPIKES_ROOM, []{return (logic->SmallKeys(RR_SHADOW_TEMPLE, 4) && (logic->CanPassEnemy(RE_BIG_SKULLTULA) && logic->CanUse(RG_HOOKSHOT)));}),
	Entrance(RR_SHADOW_TEMPLE_MQ_WIND_HINT_ROOM, []{return (logic->CanPassEnemy(RE_BIG_SKULLTULA) && (logic->CanUse(RG_HOOKSHOT) || logic->CanUse(RG_HOVER_BOOTS)));}),
	Entrance(RR_SHADOW_TEMPLE_MQ_B4_GIBDO_ROOM, []{return (logic->CanPassEnemy(RE_BIG_SKULLTULA) && (logic->CanUse(RG_HOOKSHOT) || logic->CanUse(RG_HOVER_BOOTS)));}),
});
areaTable[RR_SHADOW_TEMPLE_MQ_WIND_HINT_ROOM] = Region("Shadow Temple MQ Wind Hint Room", SCENE_SHADOW_TEMPLE, false, {RA_SHADOW_TEMPLE}, {}, {
	LOCATION(RC_SHADOW_TEMPLE_MQ_WIND_HINT_CHEST, (((bool)ctx->GetTrickOption(RT_LENS_SHADOW_MQ) || logic->CanUse(RG_LENS_OF_TRUTH)) && logic->CanPassEnemy(RE_REDEAD))),
	LOCATION(RC_SHADOW_TEMPLE_MQ_GS_WIND_HINT_ROOM, logic->CanGetEnemyDrop(RE_GOLD_SKULLTULA, ED_BOOMERANG)),
	LOCATION(RC_SHADOW_TEMPLE_MQ_WIND_HINT_SUN_FAIRY, logic->CanUse(RG_SUNS_SONG)),
}, {
	Entrance(RR_SHADOW_TEMPLE_MQ_WIND_TUNNEL, []{return true;}),
});
areaTable[RR_SHADOW_TEMPLE_MQ_B4_GIBDO_ROOM] = Region("Shadow Temple MQ B4 Gibdo Room", SCENE_SHADOW_TEMPLE, false, {RA_SHADOW_TEMPLE}, {
	EventAccess(&logic->NutPot, []{return true;}),
}, {
	LOCATION(RC_SHADOW_TEMPLE_MQ_AFTER_WIND_ENEMY_CHEST, logic->CanKillEnemy(RE_GIBDO)),
	LOCATION(RC_SHADOW_TEMPLE_MQ_AFTER_WIND_HIDDEN_CHEST, (logic->HasExplosives() && ((bool)ctx->GetTrickOption(RT_LENS_SHADOW_MQ) || logic->CanUse(RG_LENS_OF_TRUTH)))),
	LOCATION(RC_SHADOW_TEMPLE_MQ_GS_AFTER_WIND, logic->HasExplosives()),
	LOCATION(RC_SHADOW_TEMPLE_MQ_BEFORE_BOAT_POT_1, logic->CanBreakPots()),
	LOCATION(RC_SHADOW_TEMPLE_MQ_BEFORE_BOAT_POT_2, logic->CanBreakPots()),
}, {
	Entrance(RR_SHADOW_TEMPLE_MQ_WIND_TUNNEL, []{return ((bool)ctx->GetTrickOption(RT_SHADOW_MQ_WINDY_WALKWAY) || logic->CanUse(RG_HOVER_BOOTS));}),
	Entrance(RR_SHADOW_TEMPLE_MQ_DOCK, []{return logic->SmallKeys(RR_SHADOW_TEMPLE, 5);}),
});
areaTable[RR_SHADOW_TEMPLE_MQ_DOCK] = Region("Shadow Temple MQ Dock", SCENE_SHADOW_TEMPLE, false, {RA_SHADOW_TEMPLE}, {
	EventAccess(&logic->ShadowShortcutBlock, []{return logic->HasItem(RG_GORONS_BRACELET);}),
}, {
	LOCATION(RC_SHADOW_TEMPLE_MQ_SCARECROW_NORTH_HEART, logic->CanUse(RG_DISTANT_SCARECROW)),
	LOCATION(RC_SHADOW_TEMPLE_MQ_SCARECROW_SOUTH_HEART, logic->CanUse(RG_DISTANT_SCARECROW)),
}, {
	Entrance(RR_SHADOW_TEMPLE_MQ_SHORTCUT_PATH, []{return logic->ShadowShortcutBlock;}),
	Entrance(RR_SHADOW_TEMPLE_MQ_B4_GIBDO_ROOM, []{return logic->SmallKeys(RR_SHADOW_TEMPLE, 5);}),
	Entrance(RR_SHADOW_TEMPLE_MQ_BEYOND_BOAT, []{return ((logic->IsAdult || logic->CanUse(RG_HOOKSHOT)) && logic->CanUse(RG_ZELDAS_LULLABY));}),
});
areaTable[RR_SHADOW_TEMPLE_MQ_BEYOND_BOAT] = Region("Shadow Temple MQ Beyond Boat", SCENE_SHADOW_TEMPLE, false, {RA_SHADOW_TEMPLE}, {}, {
	LOCATION(RC_SHADOW_TEMPLE_MQ_GS_AFTER_SHIP, logic->CanGetEnemyDrop(RE_GOLD_SKULLTULA, ED_BOOMERANG)),
	LOCATION(RC_SHADOW_TEMPLE_MQ_BEFORE_CHASM_WEST_POT, logic->CanBreakPots()),
	LOCATION(RC_SHADOW_TEMPLE_MQ_BEFORE_CHASM_EAST_POT, logic->CanBreakPots()),
}, {
	Entrance(RR_SHADOW_TEMPLE_MQ_ACROSS_CHASM, []{return Here(RR_SHADOW_TEMPLE_MQ_BEYOND_BOAT, []{return (logic->CanUse(RG_FAIRY_BOW) || ((bool)ctx->GetTrickOption(RT_SHADOW_STATUE) && logic->CanUse(RG_BOMBCHU_5)));});}),
});
areaTable[RR_SHADOW_TEMPLE_MQ_ACROSS_CHASM] = Region("Shadow Temple MQ Across Chasm", SCENE_SHADOW_TEMPLE, false, {RA_SHADOW_TEMPLE}, {}, {
	LOCATION(RC_SHADOW_TEMPLE_MQ_AFTER_CHASM_WEST_POT, logic->CanBreakPots()),
	LOCATION(RC_SHADOW_TEMPLE_MQ_AFTER_CHASM_EAST_POT, logic->CanBreakPots()),
	LOCATION(RC_SHADOW_TEMPLE_MQ_AFTER_SHIP_UPPER_LEFT_HEART, (logic->CanUse(RG_SONG_OF_TIME) && (logic->CanHitEyeTargets() && logic->CanUse(RG_LONGSHOT)))),
	LOCATION(RC_SHADOW_TEMPLE_MQ_AFTER_SHIP_UPPER_RIGHT_HEART, (logic->CanUse(RG_SONG_OF_TIME) && (logic->CanHitEyeTargets() && logic->CanUse(RG_LONGSHOT)))),
	LOCATION(RC_SHADOW_TEMPLE_MQ_AFTER_SHIP_LOWER_HEART, logic->IsAdult),
}, {
	Entrance(RR_SHADOW_TEMPLE_MQ_BEYOND_BOAT, []{return (Here(RR_SHADOW_TEMPLE_MQ_ACROSS_CHASM, []{return logic->CanDetonateUprightBombFlower();}) && logic->IsAdult);}),
	Entrance(RR_SHADOW_TEMPLE_MQ_INVISIBLE_MAZE, []{return Here(RR_SHADOW_TEMPLE_MQ_ACROSS_CHASM, []{return (logic->CanHitEyeTargets() && (logic->CanUse(RG_SONG_OF_TIME) && logic->CanUse(RG_LONGSHOT)));});}),
	Entrance(RR_SHADOW_TEMPLE_MQ_BOSS_DOOR, []{return (logic->CanUse(RG_HOVER_BOOTS) && ((bool)ctx->GetTrickOption(RT_LENS_SHADOW_MQ) || logic->CanUse(RG_LENS_OF_TRUTH)));}),
});
areaTable[RR_SHADOW_TEMPLE_MQ_BOSS_DOOR] = Region("Shadow Temple MQ Boss Door", SCENE_SHADOW_TEMPLE, false, {RA_SHADOW_TEMPLE}, {}, {
	LOCATION(RC_SHADOW_TEMPLE_MQ_GS_NEAR_BOSS, ((logic->CanKillEnemy(RE_GOLD_SKULLTULA, ED_BOMB_THROW) || logic->CanUse(RG_MEGATON_HAMMER)) && ((bool)ctx->GetTrickOption(RT_LENS_SHADOW_MQ) || logic->CanUse(RG_LENS_OF_TRUTH)))),
}, {
	Entrance(RR_SHADOW_TEMPLE_MQ_ACROSS_CHASM, []{return (logic->CanUse(RG_HOVER_BOOTS) && ((bool)ctx->GetTrickOption(RT_LENS_SHADOW_MQ) || logic->CanUse(RG_LENS_OF_TRUTH)));}),
	Entrance(RR_SHADOW_TEMPLE_BOSS_ENTRYWAY, []{return true;}),
});
areaTable[RR_SHADOW_TEMPLE_MQ_INVISIBLE_MAZE] = Region("Shadow Temple MQ Invisible Maze", SCENE_SHADOW_TEMPLE, false, {RA_SHADOW_TEMPLE}, {}, {
	LOCATION(RC_SHADOW_TEMPLE_MQ_BOMB_FLOWER_CHEST, ((logic->CanUse(RG_LENS_OF_TRUTH) || (bool)ctx->GetTrickOption(RT_LENS_SHADOW_MQ_DEADHAND)) && (logic->CanKillEnemy(RE_DEAD_HAND) && (logic->CanDetonateBombFlowers() || logic->HasItem(RG_GORONS_BRACELET))))),
	LOCATION(RC_SHADOW_TEMPLE_MQ_FREESTANDING_KEY, true),
	LOCATION(RC_SHADOW_TEMPLE_MQ_DEAD_HAND_POT_1, logic->CanBreakPots()),
	LOCATION(RC_SHADOW_TEMPLE_MQ_DEAD_HAND_POT_2, logic->CanBreakPots()),
}, {
	Entrance(RR_SHADOW_TEMPLE_MQ_BEYOND_BOAT, []{return true;}),
	Entrance(RR_SHADOW_TEMPLE_MQ_SPIKE_WALLS_ROOM, []{return logic->SmallKeys(RR_SHADOW_TEMPLE, 6);}),
});
areaTable[RR_SHADOW_TEMPLE_MQ_SPIKE_WALLS_ROOM] = Region("Shadow Temple MQ Spike Walls Room", SCENE_SHADOW_TEMPLE, false, {RA_SHADOW_TEMPLE}, {}, {
	LOCATION(RC_SHADOW_TEMPLE_MQ_SPIKE_WALLS_LEFT_CHEST, logic->CanUse(RG_DINS_FIRE)),
	LOCATION(RC_SHADOW_TEMPLE_MQ_BOSS_KEY_CHEST, logic->CanUse(RG_DINS_FIRE)),
	LOCATION(RC_SHADOW_TEMPLE_MQ_SPIKE_BARICADE_POT, logic->CanBreakPots()),
}, {
	Entrance(RR_SHADOW_TEMPLE_MQ_INVISIBLE_MAZE, []{return (logic->SmallKeys(RR_SHADOW_TEMPLE, 6) && ((bool)ctx->GetTrickOption(RT_LENS_SHADOW_MQ) || logic->CanUse(RG_LENS_OF_TRUTH)));}),
});
areaTable[RR_SHADOW_TEMPLE_BOSS_ENTRYWAY] = Region("Shadow Temple Boss Entryway", SCENE_SHADOW_TEMPLE, false, {RA_SHADOW_TEMPLE}, {}, {}, {
	Entrance(RR_SHADOW_TEMPLE_BEYOND_BOAT, []{return (ctx->GetDungeon(Rando::SHADOW_TEMPLE)->IsVanilla() && false);}),
	Entrance(RR_SHADOW_TEMPLE_MQ_BEYOND_BOAT, []{return (ctx->GetDungeon(Rando::SHADOW_TEMPLE)->IsMQ() && false);}),
	Entrance(RR_SHADOW_TEMPLE_BOSS_ROOM, []{return logic->HasItem(RG_SHADOW_TEMPLE_BOSS_KEY);}),
});
areaTable[RR_SHADOW_TEMPLE_BOSS_ROOM] = Region("Shadow Temple Boss Room", SCENE_SHADOW_TEMPLE_BOSS, false, {}, {
	EventAccess(&logic->ShadowTempleClear, []{return logic->CanKillEnemy(RE_BONGO_BONGO);}),
}, {
	LOCATION(RC_SHADOW_TEMPLE_BONGO_BONGO_HEART, logic->ShadowTempleClear),
	LOCATION(RC_BONGO_BONGO, logic->ShadowTempleClear),
}, {
	Entrance(RR_SHADOW_TEMPLE_BOSS_ENTRYWAY, []{return false;}),
	Entrance(RR_GRAVEYARD_WARP_PAD_REGION, []{return logic->ShadowTempleClear;}),
});
areaTable[RR_BOTTOM_OF_THE_WELL_PERIMETER] = Region("Bottom of the Well Perimeter", SCENE_BOTTOM_OF_THE_WELL, false, {RA_BOTTOM_OF_THE_WELL}, {
	EventAccess(&logic->StickPot, []{return true;}),
	EventAccess(&logic->NutPot, []{return true;}),
	EventAccess(&logic->LoweredWaterInsideBotw, []{return logic->CanUse(RG_ZELDAS_LULLABY);}),
}, {
	LOCATION(RC_BOTTOM_OF_THE_WELL_FRONT_CENTER_BOMBABLE_CHEST, logic->HasExplosives()),
	LOCATION(RC_BOTTOM_OF_THE_WELL_UNDERWATER_FRONT_CHEST, (logic->LoweredWaterInsideBotw || logic->CanOpenUnderwaterChest())),
	LOCATION(RC_BOTTOM_OF_THE_WELL_UNDERWATER_LEFT_CHEST, (logic->LoweredWaterInsideBotw || logic->CanOpenUnderwaterChest())),
	LOCATION(RC_BOTTOM_OF_THE_WELL_NEAR_ENTRANCE_POT_1, logic->CanBreakPots()),
	LOCATION(RC_BOTTOM_OF_THE_WELL_NEAR_ENTRANCE_POT_2, logic->CanBreakPots()),
	LOCATION(RC_BOTTOM_OF_THE_WELL_UNDERWATER_POT, ((logic->CanBreakPots() && logic->LoweredWaterInsideBotw) || logic->CanUse(RG_BOOMERANG))),
}, {
	Entrance(RR_BOTTOM_OF_THE_WELL_ENTRYWAY, []{return (logic->IsChild && logic->CanPassEnemy(RE_BIG_SKULLTULA));}),
	Entrance(RR_BOTTOM_OF_THE_WELL_BEHIND_FAKE_WALLS, []{return ((bool)ctx->GetTrickOption(RT_LENS_BOTW) || logic->CanUse(RG_LENS_OF_TRUTH));}),
	Entrance(RR_BOTTOM_OF_THE_WELL_SOUTHWEST_ROOM, []{return ((bool)ctx->GetTrickOption(RT_LENS_BOTW) || logic->CanUse(RG_LENS_OF_TRUTH));}),
	Entrance(RR_BOTTOM_OF_THE_WELL_KEESE_BEAMOS_ROOM, []{return (logic->IsChild && logic->SmallKeys(RR_BOTTOM_OF_THE_WELL, 3));}),
	Entrance(RR_BOTTOM_OF_THE_WELL_COFFIN_ROOM, []{return (logic->LoweredWaterInsideBotw || logic->HasItem(RG_BRONZE_SCALE));}),
	Entrance(RR_BOTTOM_OF_THE_WELL_DEAD_HAND_ROOM, []{return (logic->LoweredWaterInsideBotw && logic->IsChild);}),
	Entrance(RR_BOTTOM_OF_THE_WELL_BASEMENT, []{return true;}),
});
areaTable[RR_BOTTOM_OF_THE_WELL_BEHIND_FAKE_WALLS] = Region("Bottom of the Well Behind Fake Walls", SCENE_BOTTOM_OF_THE_WELL, false, {RA_BOTTOM_OF_THE_WELL}, {}, {
	LOCATION(RC_BOTTOM_OF_THE_WELL_FRONT_LEFT_FAKE_WALL_CHEST, true),
	LOCATION(RC_BOTTOM_OF_THE_WELL_RIGHT_BOTTOM_FAKE_WALL_CHEST, true),
	LOCATION(RC_BOTTOM_OF_THE_WELL_COMPASS_CHEST, true),
	LOCATION(RC_BOTTOM_OF_THE_WELL_CENTER_SKULLTULA_CHEST, (logic->CanPassEnemy(RE_BIG_SKULLTULA) || logic->TakeDamage())),
	LOCATION(RC_BOTTOM_OF_THE_WELL_BACK_LEFT_BOMBABLE_CHEST, logic->HasExplosives()),
}, {
	Entrance(RR_BOTTOM_OF_THE_WELL_PERIMETER, []{return ((bool)ctx->GetTrickOption(RT_LENS_BOTW) || logic->CanUse(RG_LENS_OF_TRUTH));}),
	Entrance(RR_BOTTOM_OF_THE_WELL_INNER_ROOMS, []{return logic->SmallKeys(RR_BOTTOM_OF_THE_WELL, 3);}),
	Entrance(RR_BOTTOM_OF_THE_WELL_BASEMENT, []{return true;}),
	Entrance(RR_BOTTOM_OF_THE_WELL_BASEMENT_PLATFORM, []{return ((bool)ctx->GetTrickOption(RT_LENS_BOTW) || logic->CanUse(RG_LENS_OF_TRUTH));}),
});
areaTable[RR_BOTTOM_OF_THE_WELL_SOUTHWEST_ROOM] = Region("Bottom of the Well Southwest Room", SCENE_BOTTOM_OF_THE_WELL, false, {RA_BOTTOM_OF_THE_WELL}, {}, {
	LOCATION(RC_BOTTOM_OF_THE_WELL_LEFT_SIDE_POT_1, logic->CanBreakPots()),
	LOCATION(RC_BOTTOM_OF_THE_WELL_LEFT_SIDE_POT_2, logic->CanBreakPots()),
	LOCATION(RC_BOTTOM_OF_THE_WELL_LEFT_SIDE_POT_3, logic->CanBreakPots()),
}, {
	Entrance(RR_BOTTOM_OF_THE_WELL_PERIMETER, []{return ((bool)ctx->GetTrickOption(RT_LENS_BOTW) || logic->CanUse(RG_LENS_OF_TRUTH));}),
});
areaTable[RR_BOTTOM_OF_THE_WELL_KEESE_BEAMOS_ROOM] = Region("Bottom of the Well Keese-Beamos Room", SCENE_BOTTOM_OF_THE_WELL, false, {RA_BOTTOM_OF_THE_WELL}, {}, {
	LOCATION(RC_BOTTOM_OF_THE_WELL_FIRE_KEESE_CHEST, ((bool)ctx->GetTrickOption(RT_LENS_BOTW) || logic->CanUse(RG_LENS_OF_TRUTH))),
	LOCATION(RC_BOTTOM_OF_THE_WELL_FIRE_KEESE_POT_1, (logic->CanBreakPots() && ((bool)ctx->GetTrickOption(RT_LENS_BOTW) || logic->CanUse(RG_LENS_OF_TRUTH)))),
}, {
	Entrance(RR_BOTTOM_OF_THE_WELL_PERIMETER, []{return (logic->IsChild && (logic->SmallKeys(RR_BOTTOM_OF_THE_WELL, 3) && ((bool)ctx->GetTrickOption(RT_LENS_BOTW) || logic->CanUse(RG_LENS_OF_TRUTH))));}),
	Entrance(RR_BOTTOM_OF_THE_WELL_LIKE_LIKE_CAGE, []{return ((bool)ctx->GetTrickOption(RT_LENS_BOTW) || logic->CanUse(RG_LENS_OF_TRUTH));}),
	Entrance(RR_BOTTOM_OF_THE_WELL_BASEMENT_USEFUL_BOMB_FLOWERS, []{return ((bool)ctx->GetTrickOption(RT_LENS_BOTW) || logic->CanUse(RG_LENS_OF_TRUTH));}),
});
areaTable[RR_BOTTOM_OF_THE_WELL_LIKE_LIKE_CAGE] = Region("Bottom of the Well Like-Like Cage", SCENE_BOTTOM_OF_THE_WELL, false, {RA_BOTTOM_OF_THE_WELL}, {}, {
	LOCATION(RC_BOTTOM_OF_THE_WELL_LIKE_LIKE_CHEST, true),
	LOCATION(RC_BOTTOM_OF_THE_WELL_GS_LIKE_LIKE_CAGE, logic->CanGetEnemyDrop(RE_GOLD_SKULLTULA, ED_BOOMERANG)),
}, {
	Entrance(RR_BOTTOM_OF_THE_WELL_KEESE_BEAMOS_ROOM, []{return true;}),
});
areaTable[RR_BOTTOM_OF_THE_WELL_INNER_ROOMS] = Region("Bottom of the Well Inner Rooms", SCENE_BOTTOM_OF_THE_WELL, false, {RA_BOTTOM_OF_THE_WELL}, {
	EventAccess(&logic->DekuBabaSticks, []{return logic->CanGetDekuBabaSticks();}),
	EventAccess(&logic->DekuBabaNuts, []{return logic->CanGetDekuBabaNuts();}),
}, {
	LOCATION(RC_BOTTOM_OF_THE_WELL_GS_WEST_INNER_ROOM, logic->CanGetEnemyDrop(RE_GOLD_SKULLTULA, ED_BOOMERANG)),
	LOCATION(RC_BOTTOM_OF_THE_WELL_GS_EAST_INNER_ROOM, logic->CanGetEnemyDrop(RE_GOLD_SKULLTULA, ED_BOOMERANG)),
}, {
	Entrance(RR_BOTTOM_OF_THE_WELL_BEHIND_FAKE_WALLS, []{return logic->SmallKeys(RR_BOTTOM_OF_THE_WELL, 3);}),
});
areaTable[RR_BOTTOM_OF_THE_WELL_COFFIN_ROOM] = Region("Bottom of the Well Coffin Room", SCENE_BOTTOM_OF_THE_WELL, false, {RA_BOTTOM_OF_THE_WELL}, {}, {
	LOCATION(RC_BOTTOM_OF_THE_WELL_FREESTANDING_KEY, (logic->HasFireSourceWithTorch() || logic->CanUse(RG_FAIRY_BOW))),
	LOCATION(RC_BOTTOM_OF_THE_WELL_COFFIN_ROOM_FRONT_LEFT_HEART, true),
	LOCATION(RC_BOTTOM_OF_THE_WELL_COFFIN_ROOM_MIDDLE_RIGHT_HEART, (logic->HasFireSourceWithTorch() || logic->CanUse(RG_FAIRY_BOW))),
}, {
	Entrance(RR_BOTTOM_OF_THE_WELL_PERIMETER, []{return (logic->LoweredWaterInsideBotw || logic->HasItem(RG_BRONZE_SCALE));}),
});
areaTable[RR_BOTTOM_OF_THE_WELL_DEAD_HAND_ROOM] = Region("Bottom of the Well Dead Hand Room", SCENE_BOTTOM_OF_THE_WELL, false, {RA_BOTTOM_OF_THE_WELL}, {}, {
	LOCATION(RC_BOTTOM_OF_THE_WELL_LENS_OF_TRUTH_CHEST, logic->CanKillEnemy(RE_DEAD_HAND)),
	LOCATION(RC_BOTTOM_OF_THE_WELL_INVISIBLE_CHEST, ((bool)ctx->GetTrickOption(RT_LENS_BOTW) || logic->CanUse(RG_LENS_OF_TRUTH))),
}, {
	Entrance(RR_BOTTOM_OF_THE_WELL_PERIMETER, []{return (logic->IsChild && logic->CanKillEnemy(RE_DEAD_HAND));}),
});
areaTable[RR_BOTTOM_OF_THE_WELL_BASEMENT] = Region("Bottom of the Well Basement", SCENE_BOTTOM_OF_THE_WELL, false, {RA_BOTTOM_OF_THE_WELL}, {}, {
	LOCATION(RC_BOTTOM_OF_THE_WELL_MAP_CHEST, logic->BlastOrSmash()),
	LOCATION(RC_BOTTOM_OF_THE_WELL_BASEMENT_POT_1, logic->CanBreakPots()),
	LOCATION(RC_BOTTOM_OF_THE_WELL_BASEMENT_POT_2, logic->CanBreakPots()),
	LOCATION(RC_BOTTOM_OF_THE_WELL_BASEMENT_POT_3, logic->CanBreakPots()),
	LOCATION(RC_BOTTOM_OF_THE_WELL_BASEMENT_POT_4, logic->CanBreakPots()),
	LOCATION(RC_BOTTOM_OF_THE_WELL_BASEMENT_POT_5, logic->CanBreakPots()),
	LOCATION(RC_BOTTOM_OF_THE_WELL_BASEMENT_POT_6, logic->CanBreakPots()),
	LOCATION(RC_BOTTOM_OF_THE_WELL_BASEMENT_POT_7, logic->CanBreakPots()),
	LOCATION(RC_BOTTOM_OF_THE_WELL_BASEMENT_POT_8, logic->CanBreakPots()),
	LOCATION(RC_BOTTOM_OF_THE_WELL_BASEMENT_POT_9, logic->CanBreakPots()),
	LOCATION(RC_BOTTOM_OF_THE_WELL_BASEMENT_POT_10, logic->CanBreakPots()),
	LOCATION(RC_BOTTOM_OF_THE_WELL_BASEMENT_POT_11, logic->CanBreakPots()),
	LOCATION(RC_BOTTOM_OF_THE_WELL_BASEMENT_POT_12, logic->CanBreakPots()),
	LOCATION(RC_BOTTOM_OF_THE_WELL_BASEMENT_SUN_FAIRY, logic->CanUse(RG_SUNS_SONG)),
	LOCATION(RC_BOTTOM_OF_THE_WELL_BASEMENT_GRASS_1, logic->CanCutShrubs()),
	LOCATION(RC_BOTTOM_OF_THE_WELL_BASEMENT_GRASS_2, logic->CanCutShrubs()),
	LOCATION(RC_BOTTOM_OF_THE_WELL_BASEMENT_GRASS_3, logic->CanCutShrubs()),
	LOCATION(RC_BOTTOM_OF_THE_WELL_BASEMENT_BEHIND_ROCKS_GRASS_1, (logic->CanCutShrubs() && logic->BlastOrSmash())),
	LOCATION(RC_BOTTOM_OF_THE_WELL_BASEMENT_BEHIND_ROCKS_GRASS_2, (logic->CanCutShrubs() && logic->BlastOrSmash())),
	LOCATION(RC_BOTTOM_OF_THE_WELL_BASEMENT_BEHIND_ROCKS_GRASS_3, (logic->CanCutShrubs() && logic->BlastOrSmash())),
	LOCATION(RC_BOTTOM_OF_THE_WELL_BASEMENT_BEHIND_ROCKS_GRASS_4, (logic->CanCutShrubs() && logic->BlastOrSmash())),
	LOCATION(RC_BOTTOM_OF_THE_WELL_BASEMENT_BEHIND_ROCKS_GRASS_5, (logic->CanCutShrubs() && logic->BlastOrSmash())),
	LOCATION(RC_BOTTOM_OF_THE_WELL_BASEMENT_BEHIND_ROCKS_GRASS_6, (logic->CanCutShrubs() && logic->BlastOrSmash())),
	LOCATION(RC_BOTTOM_OF_THE_WELL_BASEMENT_BEHIND_ROCKS_GRASS_7, (logic->CanCutShrubs() && logic->BlastOrSmash())),
	LOCATION(RC_BOTTOM_OF_THE_WELL_BASEMENT_BEHIND_ROCKS_GRASS_8, (logic->CanCutShrubs() && logic->BlastOrSmash())),
	LOCATION(RC_BOTTOM_OF_THE_WELL_BASEMENT_BEHIND_ROCKS_GRASS_9, (logic->CanCutShrubs() && logic->BlastOrSmash())),
}, {
	Entrance(RR_BOTTOM_OF_THE_WELL_SOUTHWEST_ROOM, []{return (logic->IsChild && logic->CanPassEnemy(RE_BIG_SKULLTULA));}),
	Entrance(RR_BOTTOM_OF_THE_WELL_BASEMENT_USEFUL_BOMB_FLOWERS, []{return Here(RR_BOTTOM_OF_THE_WELL_BASEMENT, []{return (logic->BlastOrSmash() || (logic->CanUse(RG_DINS_FIRE) || (logic->CanUse(RG_STICKS) && (bool)ctx->GetTrickOption(RT_BOTW_BASEMENT))));});}),
});
areaTable[RR_BOTTOM_OF_THE_WELL_BASEMENT_USEFUL_BOMB_FLOWERS] = Region("Bottom of the Well Basement Useful Bomb Flowers", SCENE_BOTTOM_OF_THE_WELL, false, {RA_BOTTOM_OF_THE_WELL}, {}, {
	LOCATION(RC_BOTTOM_OF_THE_WELL_MAP_CHEST, logic->HasItem(RG_GORONS_BRACELET)),
}, {
	Entrance(RR_BOTTOM_OF_THE_WELL_BASEMENT, []{return logic->CanDetonateUprightBombFlower();}),
});
areaTable[RR_BOTTOM_OF_THE_WELL_BASEMENT_PLATFORM] = Region("Bottom of the Well Basement Platform", SCENE_BOTTOM_OF_THE_WELL, false, {RA_BOTTOM_OF_THE_WELL}, {}, {
	LOCATION(RC_BOTTOM_OF_THE_WELL_BASEMENT_PLATFORM_LEFT_RUPEE, true),
	LOCATION(RC_BOTTOM_OF_THE_WELL_BASEMENT_PLATFORM_BACK_LEFT_RUPEE, true),
	LOCATION(RC_BOTTOM_OF_THE_WELL_BASEMENT_PLATFORM_MIDDLE_RUPEE, true),
	LOCATION(RC_BOTTOM_OF_THE_WELL_BASEMENT_PLATFORM_BACK_RIGHT_RUPEE, true),
	LOCATION(RC_BOTTOM_OF_THE_WELL_BASEMENT_PLATFORM_RIGHT_RUPEE, true),
}, {
	Entrance(RR_BOTTOM_OF_THE_WELL_BASEMENT, []{return true;}),
});
areaTable[RR_BOTTOM_OF_THE_WELL_MQ_PERIMETER] = Region("Bottom of the Well MQ Perimeter", SCENE_BOTTOM_OF_THE_WELL, false, {RA_BOTTOM_OF_THE_WELL}, {
	EventAccess(&logic->FairyPot, []{return (Here(RR_BOTTOM_OF_THE_WELL_MQ_PERIMETER, []{return logic->BlastOrSmash();}) && logic->CanHitEyeTargets());}),
	EventAccess(&logic->LoweredWaterInsideBotw, []{return (logic->CanJumpslash() || logic->CanUseProjectile());}),
}, {
	LOCATION(RC_BOTTOM_OF_THE_WELL_MQ_OUTER_LOBBY_POT, (Here(RR_BOTTOM_OF_THE_WELL_MQ_PERIMETER, []{return logic->BlastOrSmash();}) && logic->CanHitEyeTargets())),
	LOCATION(RC_BOTTOM_OF_THE_WELL_MQ_BOMB_LEFT_HEART, logic->HasExplosives()),
	LOCATION(RC_BOTTOM_OF_THE_WELL_MQ_BOMB_RIGHT_HEART, logic->HasExplosives()),
}, {
	Entrance(RR_BOTTOM_OF_THE_WELL_ENTRYWAY, []{return logic->IsChild;}),
	Entrance(RR_BOTTOM_OF_THE_WELL_MQ_WEST_ROOM_SWITCH, []{return (Here(RR_BOTTOM_OF_THE_WELL_MQ_PERIMETER, []{return logic->BlastOrSmash();}) && logic->CanPassEnemy(RE_BIG_SKULLTULA));}),
	Entrance(RR_BOTTOM_OF_THE_WELL_MQ_COFFIN_ROOM, []{return ((logic->LoweredWaterInsideBotw || logic->HasItem(RG_BRONZE_SCALE)) && logic->SmallKeys(RR_BOTTOM_OF_THE_WELL, 2));}),
	Entrance(RR_BOTTOM_OF_THE_WELL_MQ_LOCKED_CAGE, []{return (logic->IsChild && (logic->SmallKeys(RR_BOTTOM_OF_THE_WELL, 2) && logic->CanUseProjectile()));}),
	Entrance(RR_BOTTOM_OF_THE_WELL_MQ_DEAD_HAND_ROOM, []{return (logic->IsChild && logic->LoweredWaterInsideBotw);}),
	Entrance(RR_BOTTOM_OF_THE_WELL_MQ_MIDDLE, []{return logic->CanUse(RG_ZELDAS_LULLABY);}),
	Entrance(RR_BOTTOM_OF_THE_WELL_MQ_BASEMENT, []{return true;}),
});
areaTable[RR_BOTTOM_OF_THE_WELL_MQ_WEST_ROOM_SWITCH] = Region("Bottom of the Well MQ West Room Switch", SCENE_BOTTOM_OF_THE_WELL, false, {RA_BOTTOM_OF_THE_WELL}, {
	EventAccess(&logic->OpenedWestRoomMQBotw, []{return true;}),
}, {}, {
	Entrance(RR_BOTTOM_OF_THE_WELL_MQ_PERIMETER, []{return (logic->BlastOrSmash() && (logic->CanPassEnemy(RE_BIG_SKULLTULA) || (bool)ctx->GetTrickOption(RT_BOTW_MQ_PITS)));}),
	Entrance(RR_BOTTOM_OF_THE_WELL_MQ_MIDDLE, []{return (bool)ctx->GetTrickOption(RT_BOTW_MQ_PITS);}),
	Entrance(RR_BOTTOM_OF_THE_WELL_MQ_BASEMENT, []{return true;}),
});
areaTable[RR_BOTTOM_OF_THE_WELL_MQ_COFFIN_ROOM] = Region("Bottom of the Well MQ Coffin Room", SCENE_BOTTOM_OF_THE_WELL, false, {RA_BOTTOM_OF_THE_WELL}, {}, {
	LOCATION(RC_BOTTOM_OF_THE_WELL_MQ_GS_COFFIN_ROOM, logic->CanGetEnemyDrop(RE_GOLD_SKULLTULA)),
	LOCATION(RC_BOTTOM_OF_THE_WELL_MQ_COFFIN_ROOM_FRONT_RIGHT_HEART, (logic->HasFireSourceWithTorch() || logic->CanUse(RG_FAIRY_BOW))),
	LOCATION(RC_BOTTOM_OF_THE_WELL_MQ_COFFIN_ROOM_MIDDLE_LEFT_HEART, (logic->HasFireSourceWithTorch() || logic->CanUse(RG_FAIRY_BOW))),
}, {
	Entrance(RR_BOTTOM_OF_THE_WELL_MQ_PERIMETER, []{return ((logic->LoweredWaterInsideBotw || logic->HasItem(RG_BRONZE_SCALE)) && logic->SmallKeys(RR_BOTTOM_OF_THE_WELL, 2));}),
});
areaTable[RR_BOTTOM_OF_THE_WELL_MQ_LOCKED_CAGE] = Region("Bottom of the Well MQ Locked Cage", SCENE_BOTTOM_OF_THE_WELL, false, {RA_BOTTOM_OF_THE_WELL}, {
	EventAccess(&logic->OpenedMiddleHoleMQBotw, []{return logic->HasExplosives();}),
}, {}, {
	Entrance(RR_BOTTOM_OF_THE_WELL_MQ_PERIMETER, []{return (logic->IsChild && logic->SmallKeys(RR_BOTTOM_OF_THE_WELL, 2));}),
});
areaTable[RR_BOTTOM_OF_THE_WELL_MQ_DEAD_HAND_ROOM] = Region("Bottom of the Well MQ Dead Hand Room", SCENE_BOTTOM_OF_THE_WELL, false, {RA_BOTTOM_OF_THE_WELL}, {}, {
	LOCATION(RC_BOTTOM_OF_THE_WELL_MQ_COMPASS_CHEST, logic->CanKillEnemy(RE_DEAD_HAND)),
	LOCATION(RC_BOTTOM_OF_THE_WELL_MQ_DEAD_HAND_FREESTANDING_KEY, (logic->HasExplosives() || ((bool)ctx->GetTrickOption(RT_BOTW_MQ_DEADHAND_KEY) && logic->CanUse(RG_BOOMERANG)))),
	LOCATION(RC_BOTTOM_OF_THE_WELL_MQ_DEAD_HAND_GRASS_1, logic->CanCutShrubs()),
	LOCATION(RC_BOTTOM_OF_THE_WELL_MQ_DEAD_HAND_GRASS_2, logic->CanCutShrubs()),
	LOCATION(RC_BOTTOM_OF_THE_WELL_MQ_DEAD_HAND_GRASS_3, logic->CanCutShrubs()),
	LOCATION(RC_BOTTOM_OF_THE_WELL_MQ_DEAD_HAND_GRASS_4, logic->CanCutShrubs()),
}, {
	Entrance(RR_BOTTOM_OF_THE_WELL_MQ_PERIMETER, []{return (logic->IsChild && logic->CanKillEnemy(RE_DEAD_HAND));}),
});
areaTable[RR_BOTTOM_OF_THE_WELL_MQ_MIDDLE] = Region("Bottom of the Well MQ Middle", SCENE_BOTTOM_OF_THE_WELL, false, {RA_BOTTOM_OF_THE_WELL}, {}, {
	LOCATION(RC_BOTTOM_OF_THE_WELL_MQ_MAP_CHEST, true),
	LOCATION(RC_BOTTOM_OF_THE_WELL_MQ_EAST_INNER_ROOM_FREESTANDING_KEY, true),
	LOCATION(RC_BOTTOM_OF_THE_WELL_MQ_GS_WEST_INNER_ROOM, (logic->OpenedWestRoomMQBotw && ((logic->TakeDamage() || logic->CanUse(RG_NUTS)) && logic->CanGetEnemyDrop(RE_GOLD_SKULLTULA)))),
	LOCATION(RC_BOTTOM_OF_THE_WELL_MQ_INNER_LOBBY_POT_1, logic->CanBreakPots()),
	LOCATION(RC_BOTTOM_OF_THE_WELL_MQ_INNER_LOBBY_POT_2, logic->CanBreakPots()),
	LOCATION(RC_BOTTOM_OF_THE_WELL_MQ_INNER_LOBBY_POT_3, logic->CanBreakPots()),
	LOCATION(RC_BOTTOM_OF_THE_WELL_MQ_EAST_INNER_ROOM_POT_1, logic->CanBreakPots()),
	LOCATION(RC_BOTTOM_OF_THE_WELL_MQ_EAST_INNER_ROOM_POT_2, logic->CanBreakPots()),
	LOCATION(RC_BOTTOM_OF_THE_WELL_MQ_EAST_INNER_ROOM_POT_3, logic->CanBreakPots()),
	LOCATION(RC_BOTTOM_OF_THE_WELL_MQ_CELL_SUN_FAIRY, logic->CanUse(RG_SUNS_SONG)),
}, {
	Entrance(RR_BOTTOM_OF_THE_WELL_MQ_BASEMENT_SWITCH_PLATFORM, []{return logic->OpenedMiddleHoleMQBotw;}),
	Entrance(RR_BOTTOM_OF_THE_WELL_MQ_BASEMENT, []{return true;}),
});
areaTable[RR_BOTTOM_OF_THE_WELL_MQ_BASEMENT] = Region("Bottom of the Well MQ Basement", SCENE_BOTTOM_OF_THE_WELL, false, {RA_BOTTOM_OF_THE_WELL}, {}, {
	LOCATION(RC_BOTTOM_OF_THE_WELL_MQ_GS_BASEMENT, logic->CanGetEnemyDrop(RE_GOLD_SKULLTULA)),
	LOCATION(RC_BOTTOM_OF_THE_WELL_MQ_BASEMENT_HALLWAY_FRONT_HEART, true),
	LOCATION(RC_BOTTOM_OF_THE_WELL_MQ_BASEMENT_HALLWAY_LEFT_HEART, true),
	LOCATION(RC_BOTTOM_OF_THE_WELL_MQ_BASEMENT_HALLWAY_RIGHT_HEART, true),
	LOCATION(RC_BOTTOM_OF_THE_WELL_MQ_BASEMENT_SUN_FAIRY, logic->CanUse(RG_SUNS_SONG)),
}, {
	Entrance(RR_BOTTOM_OF_THE_WELL_MQ_PERIMETER, []{return true;}),
});
areaTable[RR_BOTTOM_OF_THE_WELL_MQ_BASEMENT_SWITCH_PLATFORM] = Region("Bottom of the Well MQ Basement Switch Platform", SCENE_BOTTOM_OF_THE_WELL, false, {RA_BOTTOM_OF_THE_WELL}, {}, {
	LOCATION(RC_BOTTOM_OF_THE_WELL_MQ_LENS_OF_TRUTH_CHEST, true),
}, {
	Entrance(RR_BOTTOM_OF_THE_WELL_MQ_BASEMENT, []{return true;}),
});
areaTable[RR_ICE_CAVERN_BEGINNING] = Region("Ice Cavern Beginning", SCENE_ICE_CAVERN, false, {RA_ICE_CAVERN}, {}, {
	LOCATION(RC_ICE_CAVERN_ENTRANCE_STORMS_FAIRY, logic->CanUse(RG_SONG_OF_STORMS)),
}, {
	Entrance(RR_ICE_CAVERN_ENTRYWAY, []{return true;}),
	Entrance(RR_ICE_CAVERN_MAIN, []{return Here(RR_ICE_CAVERN_BEGINNING, []{return logic->CanKillEnemy(RE_FREEZARD, ED_CLOSE, true, 4);});}),
});
areaTable[RR_ICE_CAVERN_MAIN] = Region("Ice Cavern", SCENE_ICE_CAVERN, false, {RA_ICE_CAVERN}, {
	EventAccess(&logic->BlueFireAccess, []{return logic->IsAdult;}),
}, {
	LOCATION(RC_ICE_CAVERN_MAP_CHEST, (logic->BlueFire() && logic->IsAdult)),
	LOCATION(RC_ICE_CAVERN_COMPASS_CHEST, logic->BlueFire()),
	LOCATION(RC_ICE_CAVERN_IRON_BOOTS_CHEST, (logic->BlueFire() && logic->CanKillEnemy(RE_WOLFOS))),
	LOCATION(RC_SHEIK_IN_ICE_CAVERN, (logic->BlueFire() && (logic->CanKillEnemy(RE_WOLFOS) && logic->IsAdult))),
	LOCATION(RC_ICE_CAVERN_FREESTANDING_POH, logic->BlueFire()),
	LOCATION(RC_ICE_CAVERN_GS_SPINNING_SCYTHE_ROOM, logic->HookshotOrBoomerang()),
	LOCATION(RC_ICE_CAVERN_GS_HEART_PIECE_ROOM, (logic->BlueFire() && logic->HookshotOrBoomerang())),
	LOCATION(RC_ICE_CAVERN_GS_PUSH_BLOCK_ROOM, (logic->BlueFire() && (logic->HookshotOrBoomerang() || ((bool)ctx->GetTrickOption(RT_ICE_BLOCK_GS) && (logic->IsAdult && logic->CanUse(RG_HOVER_BOOTS)))))),
	LOCATION(RC_ICE_CAVERN_HALL_POT_1, logic->CanBreakPots()),
	LOCATION(RC_ICE_CAVERN_HALL_POT_2, logic->CanBreakPots()),
	LOCATION(RC_ICE_CAVERN_SPINNING_BLADE_POT_1, logic->CanBreakPots()),
	LOCATION(RC_ICE_CAVERN_SPINNING_BLADE_POT_2, logic->CanBreakPots()),
	LOCATION(RC_ICE_CAVERN_SPINNING_BLADE_POT_3, logic->CanBreakPots()),
	LOCATION(RC_ICE_CAVERN_NEAR_END_POT_1, (logic->CanBreakPots() && logic->BlueFire())),
	LOCATION(RC_ICE_CAVERN_NEAR_END_POT_2, (logic->CanBreakPots() && logic->BlueFire())),
	LOCATION(RC_ICE_CAVERN_FROZEN_POT_1, (logic->CanBreakPots() && (logic->BlueFire() && logic->IsAdult))),
	LOCATION(RC_ICE_CAVERN_LOBBY_RUPEE, logic->BlueFire()),
	LOCATION(RC_ICE_CAVERN_MAP_ROOM_LEFT_HEART, logic->IsAdult),
	LOCATION(RC_ICE_CAVERN_MAP_ROOM_MIDDLE_HEART, logic->IsAdult),
	LOCATION(RC_ICE_CAVERN_MAP_ROOM_RIGHT_HEART, logic->IsAdult),
	LOCATION(RC_ICE_CAVERN_SLIDING_BLOCK_RUPEE_1, (logic->BlueFire() && (logic->CanUse(RG_SONG_OF_TIME) || logic->CanUse(RG_BOOMERANG)))),
	LOCATION(RC_ICE_CAVERN_SLIDING_BLOCK_RUPEE_2, (logic->BlueFire() && (logic->CanUse(RG_SONG_OF_TIME) || logic->CanUse(RG_BOOMERANG)))),
	LOCATION(RC_ICE_CAVERN_SLIDING_BLOCK_RUPEE_3, (logic->BlueFire() && (logic->CanUse(RG_SONG_OF_TIME) || logic->CanUse(RG_BOOMERANG)))),
}, {});
areaTable[RR_ICE_CAVERN_MQ_BEGINNING] = Region("Ice Cavern MQ Beginning", SCENE_ICE_CAVERN, false, {RA_ICE_CAVERN}, {}, {
	LOCATION(RC_ICE_CAVERN_MQ_ENTRANCE_POT, logic->CanBreakPots()),
}, {
	Entrance(RR_ICE_CAVERN_ENTRYWAY, []{return true;}),
	Entrance(RR_ICE_CAVERN_MQ_HUB, []{return true;}),
});
areaTable[RR_ICE_CAVERN_MQ_HUB] = Region("Ice Cavern MQ Hub", SCENE_ICE_CAVERN, false, {RA_ICE_CAVERN}, {
	EventAccess(&logic->FairyPot, []{return true;}),
}, {
	LOCATION(RC_ICE_CAVERN_MQ_FIRST_CRYSTAL_POT_1, logic->CanBreakPots()),
	LOCATION(RC_ICE_CAVERN_MQ_FIRST_CRYSTAL_POT_2, logic->CanBreakPots()),
	LOCATION(RC_ICE_CAVERN_MQ_EARLY_WOLFOS_POT_1, logic->CanBreakPots()),
	LOCATION(RC_ICE_CAVERN_MQ_EARLY_WOLFOS_POT_2, logic->CanBreakPots()),
	LOCATION(RC_ICE_CAVERN_MQ_EARLY_WOLFOS_POT_3, logic->CanBreakPots()),
	LOCATION(RC_ICE_CAVERN_MQ_EARLY_WOLFOS_POT_4, logic->CanBreakPots()),
}, {
	Entrance(RR_ICE_CAVERN_MQ_BEGINNING, []{return logic->BlueFire();}),
	Entrance(RR_ICE_CAVERN_MQ_MAP_ROOM, []{return Here(RR_ICE_CAVERN_MQ_HUB, []{return (logic->CanKillEnemy(RE_WHITE_WOLFOS) && logic->CanKillEnemy(RE_FREEZARD));});}),
	Entrance(RR_ICE_CAVERN_MQ_COMPASS_ROOM, []{return (logic->IsAdult && logic->BlueFire());}),
	Entrance(RR_ICE_CAVERN_MQ_SCARECROW_ROOM, []{return logic->BlueFire();}),
});
areaTable[RR_ICE_CAVERN_MQ_MAP_ROOM] = Region("Ice Cavern MQ Map Room", SCENE_ICE_CAVERN, false, {RA_ICE_CAVERN}, {
	EventAccess(&logic->BlueFireAccess, []{return (logic->IsChild || (logic->CanJumpslash() || logic->HasExplosives()));}),
}, {
	LOCATION(RC_ICE_CAVERN_MQ_MAP_CHEST, (logic->BlueFire() && Here(RR_ICE_CAVERN_MQ_MAP_ROOM, []{return logic->CanHitSwitch();}))),
}, {});
areaTable[RR_ICE_CAVERN_MQ_SCARECROW_ROOM] = Region("Ice Cavern MQ Scarecrow Room", SCENE_ICE_CAVERN, false, {RA_ICE_CAVERN}, {}, {
	LOCATION(RC_ICE_CAVERN_MQ_GS_ICE_BLOCK, ((logic->BlueFire() && logic->CanGetEnemyDrop(RE_GOLD_SKULLTULA)) || (logic->IsAdult && logic->CanHitSwitch(ED_LONG_JUMPSLASH)))),
	LOCATION(RC_ICE_CAVERN_MQ_GS_SCARECROW, (logic->CanUse(RG_SCARECROW) || (logic->IsAdult && (logic->CanUse(RG_LONGSHOT) || (bool)ctx->GetTrickOption(RT_ICE_MQ_SCARECROW))))),
}, {
	Entrance(RR_ICE_CAVERN_MQ_HUB, []{return logic->BlueFire();}),
	Entrance(RR_ICE_CAVERN_MQ_WEST_CORRIDOR, []{return (logic->IsAdult && logic->BlueFire());}),
});
areaTable[RR_ICE_CAVERN_MQ_STALFOS_ROOM] = Region("Ice Cavern MQ Stalfos Room", SCENE_ICE_CAVERN, false, {RA_ICE_CAVERN}, {}, {
	LOCATION(RC_ICE_CAVERN_MQ_IRON_BOOTS_CHEST, logic->CanKillEnemy(RE_STALFOS)),
	LOCATION(RC_SHEIK_IN_ICE_CAVERN, logic->CanKillEnemy(RE_STALFOS)),
}, {
	Entrance(RR_ICE_CAVERN_MQ_WEST_CORRIDOR, []{return Here(RR_ICE_CAVERN_MQ_STALFOS_ROOM, []{return logic->CanKillEnemy(RE_STALFOS);});}),
	Entrance(RR_ICE_CAVERN_MQ_BEGINNING, []{return (logic->CanUse(RG_IRON_BOOTS) && Here(RR_ICE_CAVERN_MQ_STALFOS_ROOM, []{return logic->CanKillEnemy(RE_STALFOS);}));}),
});
areaTable[RR_ICE_CAVERN_MQ_WEST_CORRIDOR] = Region("Ice Cavern MQ West Corridor", SCENE_ICE_CAVERN, false, {RA_ICE_CAVERN}, {}, {
	LOCATION(RC_ICE_CAVERN_MQ_PUSH_BLOCK_POT_1, logic->CanBreakPots()),
	LOCATION(RC_ICE_CAVERN_MQ_PUSH_BLOCK_POT_2, logic->CanBreakPots()),
}, {
	Entrance(RR_ICE_CAVERN_MQ_SCARECROW_ROOM, []{return logic->BlueFire();}),
	Entrance(RR_ICE_CAVERN_MQ_STALFOS_ROOM, []{return true;}),
});
areaTable[RR_ICE_CAVERN_MQ_COMPASS_ROOM] = Region("Ice Cavern MQ Compass Room", SCENE_ICE_CAVERN, false, {RA_ICE_CAVERN}, {
	EventAccess(&logic->BlueFireAccess, []{return true;}),
}, {
	LOCATION(RC_ICE_CAVERN_MQ_COMPASS_CHEST, true),
	LOCATION(RC_ICE_CAVERN_MQ_FREESTANDING_POH, logic->HasExplosives()),
	LOCATION(RC_ICE_CAVERN_MQ_GS_RED_ICE, ((ctx->GetOption(RSK_BLUE_FIRE_ARROWS) && logic->CanUse(RG_ICE_ARROWS)) || (logic->CanUse(RG_BOTTLE_WITH_BLUE_FIRE) && ((logic->CanUse(RG_SONG_OF_TIME) || (logic->IsAdult && (bool)ctx->GetTrickOption(RT_ICE_MQ_RED_ICE_GS))) && logic->CanGetEnemyDrop(RE_GOLD_SKULLTULA))))),
	LOCATION(RC_ICE_CAVERN_MQ_COMPASS_POT_1, logic->CanBreakPots()),
	LOCATION(RC_ICE_CAVERN_MQ_COMPASS_POT_2, logic->CanBreakPots()),
}, {});
areaTable[RR_GERUDO_TRAINING_GROUND_LOBBY] = Region("Gerudo Training Ground Lobby", SCENE_GERUDO_TRAINING_GROUND, false, {RA_GERUDO_TRAINING_GROUND}, {}, {
	LOCATION(RC_GERUDO_TRAINING_GROUND_LOBBY_LEFT_CHEST, logic->CanHitEyeTargets()),
	LOCATION(RC_GERUDO_TRAINING_GROUND_LOBBY_RIGHT_CHEST, logic->CanHitEyeTargets()),
	LOCATION(RC_GERUDO_TRAINING_GROUND_STALFOS_CHEST, logic->CanKillEnemy(RE_STALFOS, ED_CLOSE, true, 2, true)),
	LOCATION(RC_GERUDO_TRAINING_GROUND_BEAMOS_CHEST, (logic->CanKillEnemy(RE_BEAMOS) && logic->CanKillEnemy(RE_DINOLFOS, ED_CLOSE, true, 2, true))),
	LOCATION(RC_GERUDO_TRAINING_GROUND_ENTRANCE_STORMS_FAIRY, logic->CanUse(RG_SONG_OF_STORMS)),
	LOCATION(RC_GERUDO_TRAINING_GROUND_BEAMOS_SOUTH_HEART, true),
	LOCATION(RC_GERUDO_TRAINING_GROUND_BEAMOS_EAST_HEART, true),
}, {
	Entrance(RR_GERUDO_TRAINING_GROUND_ENTRYWAY, []{return true;}),
	Entrance(RR_GERUDO_TRAINING_GROUND_HEAVY_BLOCK_ROOM, []{return (logic->CanKillEnemy(RE_STALFOS, ED_CLOSE, true, 2, true) && (logic->CanUse(RG_HOOKSHOT) || (bool)ctx->GetTrickOption(RT_GTG_WITHOUT_HOOKSHOT)));}),
	Entrance(RR_GERUDO_TRAINING_GROUND_LAVA_ROOM, []{return Here(RR_GERUDO_TRAINING_GROUND_LOBBY, []{return (logic->CanKillEnemy(RE_BEAMOS) && logic->CanKillEnemy(RE_DINOLFOS, ED_CLOSE, true, 2, true));});}),
	Entrance(RR_GERUDO_TRAINING_GROUND_CENTRAL_MAZE, []{return true;}),
});
areaTable[RR_GERUDO_TRAINING_GROUND_CENTRAL_MAZE] = Region("Gerudo Training Ground Central Maze", SCENE_GERUDO_TRAINING_GROUND, false, {RA_GERUDO_TRAINING_GROUND}, {}, {
	LOCATION(RC_GERUDO_TRAINING_GROUND_HIDDEN_CEILING_CHEST, (logic->SmallKeys(RR_GERUDO_TRAINING_GROUND, 3) && ((bool)ctx->GetTrickOption(RT_LENS_GTG) || logic->CanUse(RG_LENS_OF_TRUTH)))),
	LOCATION(RC_GERUDO_TRAINING_GROUND_MAZE_PATH_FIRST_CHEST, logic->SmallKeys(RR_GERUDO_TRAINING_GROUND, 4)),
	LOCATION(RC_GERUDO_TRAINING_GROUND_MAZE_PATH_SECOND_CHEST, logic->SmallKeys(RR_GERUDO_TRAINING_GROUND, 6)),
	LOCATION(RC_GERUDO_TRAINING_GROUND_MAZE_PATH_THIRD_CHEST, logic->SmallKeys(RR_GERUDO_TRAINING_GROUND, 7)),
	LOCATION(RC_GERUDO_TRAINING_GROUND_MAZE_PATH_FINAL_CHEST, logic->SmallKeys(RR_GERUDO_TRAINING_GROUND, 9)),
}, {
	Entrance(RR_GERUDO_TRAINING_GROUND_CENTRAL_MAZE_RIGHT, []{return logic->SmallKeys(RR_GERUDO_TRAINING_GROUND, 9);}),
});
areaTable[RR_GERUDO_TRAINING_GROUND_CENTRAL_MAZE_RIGHT] = Region("Gerudo Training Ground Central Maze Right", SCENE_GERUDO_TRAINING_GROUND, false, {RA_GERUDO_TRAINING_GROUND}, {}, {
	LOCATION(RC_GERUDO_TRAINING_GROUND_MAZE_RIGHT_CENTRAL_CHEST, true),
	LOCATION(RC_GERUDO_TRAINING_GROUND_MAZE_RIGHT_SIDE_CHEST, true),
	LOCATION(RC_GERUDO_TRAINING_GROUND_FREESTANDING_KEY, true),
}, {
	Entrance(RR_GERUDO_TRAINING_GROUND_HAMMER_ROOM, []{return logic->CanUse(RG_HOOKSHOT);}),
	Entrance(RR_GERUDO_TRAINING_GROUND_LAVA_ROOM, []{return true;}),
});
areaTable[RR_GERUDO_TRAINING_GROUND_LAVA_ROOM] = Region("Gerudo Training Ground Lava Room", SCENE_GERUDO_TRAINING_GROUND, false, {RA_GERUDO_TRAINING_GROUND}, {}, {
	LOCATION(RC_GERUDO_TRAINING_GROUND_UNDERWATER_SILVER_RUPEE_CHEST, (logic->CanUse(RG_HOOKSHOT) && (logic->CanUse(RG_SONG_OF_TIME) && (logic->CanUse(RG_IRON_BOOTS) && (logic->WaterTimer() >= 24))))),
}, {
	Entrance(RR_GERUDO_TRAINING_GROUND_CENTRAL_MAZE_RIGHT, []{return (logic->CanUse(RG_SONG_OF_TIME) || logic->IsChild);}),
	Entrance(RR_GERUDO_TRAINING_GROUND_HAMMER_ROOM, []{return (logic->CanUse(RG_LONGSHOT) || (logic->CanUse(RG_HOVER_BOOTS) && logic->CanUse(RG_HOOKSHOT)));}),
});
areaTable[RR_GERUDO_TRAINING_GROUND_HAMMER_ROOM] = Region("Gerudo Training Ground Hammer Room", SCENE_GERUDO_TRAINING_GROUND, false, {RA_GERUDO_TRAINING_GROUND}, {}, {
	LOCATION(RC_GERUDO_TRAINING_GROUND_HAMMER_ROOM_CLEAR_CHEST, logic->CanAttack()),
	LOCATION(RC_GERUDO_TRAINING_GROUND_HAMMER_ROOM_SWITCH_CHEST, (logic->CanUse(RG_MEGATON_HAMMER) || (logic->TakeDamage() && (bool)ctx->GetTrickOption(RT_FLAMING_CHESTS)))),
}, {
	Entrance(RR_GERUDO_TRAINING_GROUND_EYE_STATUE_LOWER, []{return (logic->CanUse(RG_MEGATON_HAMMER) && logic->CanUse(RG_FAIRY_BOW));}),
	Entrance(RR_GERUDO_TRAINING_GROUND_LAVA_ROOM, []{return true;}),
});
areaTable[RR_GERUDO_TRAINING_GROUND_EYE_STATUE_LOWER] = Region("Gerudo Training Ground Eye Statue Lower", SCENE_GERUDO_TRAINING_GROUND, false, {RA_GERUDO_TRAINING_GROUND}, {}, {
	LOCATION(RC_GERUDO_TRAINING_GROUND_EYE_STATUE_CHEST, logic->CanUse(RG_FAIRY_BOW)),
}, {
	Entrance(RR_GERUDO_TRAINING_GROUND_HAMMER_ROOM, []{return true;}),
});
areaTable[RR_GERUDO_TRAINING_GROUND_EYE_STATUE_UPPER] = Region("Gerudo Training Ground Eye Statue Upper", SCENE_GERUDO_TRAINING_GROUND, false, {RA_GERUDO_TRAINING_GROUND}, {}, {
	LOCATION(RC_GERUDO_TRAINING_GROUND_NEAR_SCARECROW_CHEST, logic->CanUse(RG_FAIRY_BOW)),
}, {
	Entrance(RR_GERUDO_TRAINING_GROUND_EYE_STATUE_LOWER, []{return true;}),
});
areaTable[RR_GERUDO_TRAINING_GROUND_HEAVY_BLOCK_ROOM] = Region("Gerudo Training Ground Heavy Block Room", SCENE_GERUDO_TRAINING_GROUND, false, {RA_GERUDO_TRAINING_GROUND}, {}, {
	LOCATION(RC_GERUDO_TRAINING_GROUND_BEFORE_HEAVY_BLOCK_CHEST, logic->CanKillEnemy(RE_WOLFOS, ED_CLOSE, true, 4, true)),
}, {
	Entrance(RR_GERUDO_TRAINING_GROUND_EYE_STATUE_UPPER, []{return (((bool)ctx->GetTrickOption(RT_LENS_GTG) || logic->CanUse(RG_LENS_OF_TRUTH)) && (logic->CanUse(RG_HOOKSHOT) || ((bool)ctx->GetTrickOption(RT_GTG_FAKE_WALL) && logic->CanUse(RG_HOVER_BOOTS))));}),
	Entrance(RR_GERUDO_TRAINING_GROUND_LIKE_LIKE_ROOM, []{return (((bool)ctx->GetTrickOption(RT_LENS_GTG) || logic->CanUse(RG_LENS_OF_TRUTH)) && ((logic->CanUse(RG_HOOKSHOT) || ((bool)ctx->GetTrickOption(RT_GTG_FAKE_WALL) && logic->CanUse(RG_HOVER_BOOTS))) && logic->CanUse(RG_SILVER_GAUNTLETS)));}),
});
areaTable[RR_GERUDO_TRAINING_GROUND_LIKE_LIKE_ROOM] = Region("Gerudo Training Ground Like Like Room", SCENE_GERUDO_TRAINING_GROUND, false, {RA_GERUDO_TRAINING_GROUND}, {}, {
	LOCATION(RC_GERUDO_TRAINING_GROUND_HEAVY_BLOCK_FIRST_CHEST, logic->CanJumpslashExceptHammer()),
	LOCATION(RC_GERUDO_TRAINING_GROUND_HEAVY_BLOCK_SECOND_CHEST, logic->CanJumpslashExceptHammer()),
	LOCATION(RC_GERUDO_TRAINING_GROUND_HEAVY_BLOCK_THIRD_CHEST, logic->CanJumpslashExceptHammer()),
	LOCATION(RC_GERUDO_TRAINING_GROUND_HEAVY_BLOCK_FOURTH_CHEST, logic->CanJumpslashExceptHammer()),
}, {});
areaTable[RR_GERUDO_TRAINING_GROUND_MQ_LOBBY] = Region("Gerudo Training Ground MQ Lobby", SCENE_GERUDO_TRAINING_GROUND, false, {RA_GERUDO_TRAINING_GROUND}, {}, {
	LOCATION(RC_GERUDO_TRAINING_GROUND_MQ_LOBBY_LEFT_CHEST, true),
	LOCATION(RC_GERUDO_TRAINING_GROUND_MQ_LOBBY_RIGHT_CHEST, true),
	LOCATION(RC_GERUDO_TRAINING_GROUND_MQ_MAZE_PATH_FIRST_CHEST, true),
	LOCATION(RC_GERUDO_TRAINING_GROUND_MQ_MAZE_PATH_SECOND_CHEST, true),
	LOCATION(RC_GERUDO_TRAINING_GROUND_MQ_LOBBY_LEFT_POT_1, logic->CanBreakPots()),
	LOCATION(RC_GERUDO_TRAINING_GROUND_MQ_LOBBY_LEFT_POT_2, logic->CanBreakPots()),
	LOCATION(RC_GERUDO_TRAINING_GROUND_MQ_LOBBY_RIGHT_POT_1, logic->CanBreakPots()),
	LOCATION(RC_GERUDO_TRAINING_GROUND_MQ_LOBBY_RIGHT_POT_2, logic->CanBreakPots()),
}, {
	Entrance(RR_GERUDO_TRAINING_GROUND_ENTRYWAY, []{return true;}),
	Entrance(RR_GERUDO_TRAINING_GROUND_MQ_MAZE_HIDDEN_ROOM, []{return ((bool)ctx->GetTrickOption(RT_LENS_GTG_MQ) || logic->CanUse(RG_LENS_OF_TRUTH));}),
	Entrance(RR_GERUDO_TRAINING_GROUND_MQ_MAZE_FIRST_LOCK, []{return logic->SmallKeys(RR_GERUDO_TRAINING_GROUND, 1);}),
	Entrance(RR_GERUDO_TRAINING_GROUND_MQ_SAND_ROOM, []{return Here(RR_GERUDO_TRAINING_GROUND_MQ_LOBBY, []{return logic->HasFireSource();});}),
	Entrance(RR_GERUDO_TRAINING_GROUND_MQ_DINOLFOS_ROOM, []{return Here(RR_GERUDO_TRAINING_GROUND_MQ_LOBBY, []{return ((logic->IsAdult && logic->CanUse(RG_FAIRY_BOW)) || (logic->IsChild && logic->CanUse(RG_FAIRY_SLINGSHOT)));});}),
});
areaTable[RR_GERUDO_TRAINING_GROUND_MQ_MAZE_HIDDEN_ROOM] = Region("Gerudo Training Ground MQ Maze Hidden Room", SCENE_GERUDO_TRAINING_GROUND, false, {RA_GERUDO_TRAINING_GROUND}, {}, {
	LOCATION(RC_GERUDO_TRAINING_GROUND_MQ_HIDDEN_CEILING_CHEST, true),
}, {
	Entrance(RR_GERUDO_TRAINING_GROUND_MQ_LOBBY, []{return true;}),
});
areaTable[RR_GERUDO_TRAINING_GROUND_MQ_MAZE_FIRST_LOCK] = Region("Gerudo Training Ground MQ Maze First Lock", SCENE_GERUDO_TRAINING_GROUND, false, {RA_GERUDO_TRAINING_GROUND}, {}, {
	LOCATION(RC_GERUDO_TRAINING_GROUND_MQ_MAZE_PATH_THIRD_CHEST, true),
}, {
	Entrance(RR_GERUDO_TRAINING_GROUND_MQ_LOBBY, []{return logic->SmallKeys(RR_GERUDO_TRAINING_GROUND, 1);}),
	Entrance(RR_GERUDO_TRAINING_GROUND_MQ_MAZE_CENTER, []{return logic->SmallKeys(RR_GERUDO_TRAINING_GROUND, 3);}),
});
areaTable[RR_GERUDO_TRAINING_GROUND_MQ_MAZE_CENTER] = Region("Gerudo Training Ground MQ Center", SCENE_GERUDO_TRAINING_GROUND, false, {RA_GERUDO_TRAINING_GROUND}, {
	EventAccess(&logic->MQGTGMazeSwitch, []{return logic->CanUse(RG_MEGATON_HAMMER);}),
}, {
	LOCATION(RC_GERUDO_TRAINING_GROUND_MQ_MAZE_CRATE, logic->CanBreakCrates()),
}, {
	Entrance(RR_GERUDO_TRAINING_GROUND_MQ_MAZE_FIRST_LOCK, []{return logic->SmallKeys(RR_GERUDO_TRAINING_GROUND, 3);}),
});
areaTable[RR_GERUDO_TRAINING_GROUND_MQ_SAND_ROOM] = Region("Gerudo Training Ground MQ Sand Room", SCENE_GERUDO_TRAINING_GROUND, false, {RA_GERUDO_TRAINING_GROUND}, {}, {
	LOCATION(RC_GERUDO_TRAINING_GROUND_MQ_FIRST_IRON_KNUCKLE_CHEST, logic->CanKillEnemy(RE_IRON_KNUCKLE)),
}, {
	Entrance(RR_GERUDO_TRAINING_GROUND_MQ_LOBBY, []{return true;}),
	Entrance(RR_GERUDO_TRAINING_GROUND_MQ_LEFT_SIDE, []{return Here(RR_GERUDO_TRAINING_GROUND_MQ_SAND_ROOM, []{return logic->CanKillEnemy(RE_IRON_KNUCKLE);});}),
});
areaTable[RR_GERUDO_TRAINING_GROUND_MQ_LEFT_SIDE] = Region("Gerudo Training Ground MQ Left Side", SCENE_GERUDO_TRAINING_GROUND, false, {RA_GERUDO_TRAINING_GROUND}, {}, {}, {
	Entrance(RR_GERUDO_TRAINING_GROUND_MQ_SAND_ROOM, []{return true;}),
	Entrance(RR_GERUDO_TRAINING_GROUND_MQ_STALFOS_ROOM, []{return Here(RR_GERUDO_TRAINING_GROUND_MQ_LEFT_SIDE, []{return (logic->CanUse(RG_LONGSHOT) || ((bool)ctx->GetTrickOption(RT_GTG_MQ_WITHOUT_HOOKSHOT) || ((bool)ctx->GetTrickOption(RT_GTG_MQ_WITH_HOOKSHOT) && (logic->IsAdult && (logic->CanJumpslash() && logic->CanUse(RG_HOOKSHOT))))));});}),
});
areaTable[RR_GERUDO_TRAINING_GROUND_MQ_STALFOS_ROOM] = Region("Gerudo Training Ground MQ Stalfos Room", SCENE_GERUDO_TRAINING_GROUND, false, {RA_GERUDO_TRAINING_GROUND}, {
	EventAccess(&logic->BlueFireAccess, []{return true;}),
}, {
	LOCATION(RC_GERUDO_TRAINING_GROUND_MQ_BEFORE_HEAVY_BLOCK_CHEST, logic->CanKillEnemy(RE_STALFOS, ED_CLOSE, true, 2, true)),
}, {
	Entrance(RR_GERUDO_TRAINING_GROUND_MQ_BEHIND_BLOCK, []{return (Here(RR_GERUDO_TRAINING_GROUND_MQ_STALFOS_ROOM, []{return logic->CanKillEnemy(RE_STALFOS, ED_CLOSE, true, 2, true);}) && logic->CanUse(RG_SILVER_GAUNTLETS));}),
	Entrance(RR_GERUDO_TRAINING_GROUND_MQ_STATUE_ROOM_LEDGE, []{return (logic->IsAdult && (Here(RR_GERUDO_TRAINING_GROUND_MQ_STALFOS_ROOM, []{return logic->CanKillEnemy(RE_STALFOS, ED_CLOSE, true, 2, true);}) && (((bool)ctx->GetTrickOption(RT_LENS_GTG_MQ) || logic->CanUse(RG_LENS_OF_TRUTH)) && (logic->BlueFire() && (logic->CanUse(RG_SONG_OF_TIME) || ((bool)ctx->GetTrickOption(RT_GTG_FAKE_WALL) && logic->CanUse(RG_HOVER_BOOTS)))))));}),
});
areaTable[RR_GERUDO_TRAINING_GROUND_MQ_BEHIND_BLOCK] = Region("Gerudo Training Ground MQ Behind Block", SCENE_GERUDO_TRAINING_GROUND, false, {RA_GERUDO_TRAINING_GROUND}, {}, {
	LOCATION(RC_GERUDO_TRAINING_GROUND_MQ_HEAVY_BLOCK_CHEST, logic->CanKillEnemy(RE_FREEZARD)),
}, {});
areaTable[RR_GERUDO_TRAINING_GROUND_MQ_STATUE_ROOM_LEDGE] = Region("Gerudo Training Ground MQ Statue Room Ledge", SCENE_GERUDO_TRAINING_GROUND, false, {RA_GERUDO_TRAINING_GROUND}, {}, {}, {
	Entrance(RR_GERUDO_TRAINING_GROUND_MQ_STALFOS_ROOM, []{return true;}),
	Entrance(RR_GERUDO_TRAINING_GROUND_MQ_MAGENTA_FIRE_ROOM, []{return Here(RR_GERUDO_TRAINING_GROUND_MQ_STATUE_ROOM_LEDGE, []{return (logic->CanUse(RG_HOOKSHOT) || (logic->CanUse(RG_FAIRY_BOW) || (logic->CanUse(RG_MASTER_SWORD) || (logic->CanUse(RG_BIGGORON_SWORD) || (logic->CanUse(RG_STICKS) || (logic->CanUse(RG_FAIRY_SLINGSHOT) || logic->CanUse(RG_BOOMERANG)))))));});}),
	Entrance(RR_GERUDO_TRAINING_GROUND_MQ_STATUE_ROOM, []{return true;}),
});
areaTable[RR_GERUDO_TRAINING_GROUND_MQ_MAGENTA_FIRE_ROOM] = Region("Gerudo Training Ground MQ Magenta Fire Room", SCENE_GERUDO_TRAINING_GROUND, false, {RA_GERUDO_TRAINING_GROUND}, {}, {
	LOCATION(RC_GERUDO_TRAINING_GROUND_MQ_ICE_ARROWS_CHEST, logic->MQGTGMazeSwitch),
}, {
	Entrance(RR_GERUDO_TRAINING_GROUND_MQ_STATUE_ROOM_LEDGE, []{return true;}),
});
areaTable[RR_GERUDO_TRAINING_GROUND_MQ_STATUE_ROOM] = Region("Gerudo Training Ground MQ Statue ROom", SCENE_GERUDO_TRAINING_GROUND, false, {RA_GERUDO_TRAINING_GROUND}, {}, {
	LOCATION(RC_GERUDO_TRAINING_GROUND_MQ_EYE_STATUE_CHEST, logic->CanUse(RG_FAIRY_BOW)),
}, {
	Entrance(RR_GERUDO_TRAINING_GROUND_MQ_STATUE_ROOM_LEDGE, []{return logic->CanUse(RG_LONGSHOT);}),
	Entrance(RR_GERUDO_TRAINING_GROUND_MQ_TORCH_SLUG_ROOM, []{return true;}),
});
areaTable[RR_GERUDO_TRAINING_GROUND_MQ_TORCH_SLUG_ROOM] = Region("Gerudo Training Ground MQ Torch Slug Room", SCENE_GERUDO_TRAINING_GROUND, false, {RA_GERUDO_TRAINING_GROUND}, {}, {
	LOCATION(RC_GERUDO_TRAINING_GROUND_MQ_SECOND_IRON_KNUCKLE_CHEST, logic->CanKillEnemy(RE_IRON_KNUCKLE)),
	LOCATION(RC_GERUDO_TRAINING_GROUND_MQ_FLAME_CIRCLE_CHEST, logic->CanHitSwitch(ED_BOMB_THROW)),
}, {
	Entrance(RR_GERUDO_TRAINING_GROUND_MQ_STATUE_ROOM, []{return Here(RR_GERUDO_TRAINING_GROUND_MQ_TORCH_SLUG_ROOM, []{return logic->CanKillEnemy(RE_IRON_KNUCKLE);});}),
	Entrance(RR_GERUDO_TRAINING_GROUND_MQ_SWITCH_LEDGE, []{return Here(RR_GERUDO_TRAINING_GROUND_MQ_TORCH_SLUG_ROOM, []{return logic->CanKillEnemy(RE_IRON_KNUCKLE);});}),
});
areaTable[RR_GERUDO_TRAINING_GROUND_MQ_SWITCH_LEDGE] = Region("Gerudo Training Ground MQ Switch Ledge", SCENE_GERUDO_TRAINING_GROUND, false, {RA_GERUDO_TRAINING_GROUND}, {
	EventAccess(&logic->MQGTGRightSideSwitch, []{return logic->CanUse(RG_MEGATON_HAMMER);}),
	EventAccess(&logic->GTGPlatformSilverRupees, []{return (logic->CanUse(RG_FIRE_ARROWS) && logic->CanUse(RG_HOVER_BOOTS));}),
}, {}, {
	Entrance(RR_GERUDO_TRAINING_GROUND_MQ_LEDGE_SIDE_PLATFORMS, []{return logic->CanUse(RG_FIRE_ARROWS);}),
	Entrance(RR_GERUDO_TRAINING_GROUND_MQ_PLATFORMS_UNLIT_TORCH, []{return (logic->CanUse(RG_LONGSHOT) || ((logic->GTGPlatformSilverRupees && logic->CanUse(RG_HOOKSHOT)) || ((logic->CanUse(RG_FIRE_ARROWS) && logic->GTGPlatformSilverRupees) && logic->CanUse(RG_HOVER_BOOTS))));}),
	Entrance(RR_GERUDO_TRAINING_GROUND_MQ_MAZE_RIGHT, []{return (logic->MQGTGRightSideSwitch && logic->CanUse(RG_LONGSHOT));}),
});
areaTable[RR_GERUDO_TRAINING_GROUND_MQ_LEDGE_SIDE_PLATFORMS] = Region("Gerudo Training Ground MQ Ledge Side Platforms", SCENE_GERUDO_TRAINING_GROUND, false, {RA_GERUDO_TRAINING_GROUND}, {}, {}, {
	Entrance(RR_GERUDO_TRAINING_GROUND_MQ_FURTHEST_PLATFORM, []{return logic->CanUse(RG_HOVER_BOOTS);}),
});
areaTable[RR_GERUDO_TRAINING_GROUND_MQ_FURTHEST_PLATFORM] = Region("Gerudo Training Ground MQ Furthest Platform", SCENE_GERUDO_TRAINING_GROUND, false, {RA_GERUDO_TRAINING_GROUND}, {}, {}, {
	Entrance(RR_GERUDO_TRAINING_GROUND_MQ_LEDGE_SIDE_PLATFORMS, []{return logic->CanUse(RG_HOVER_BOOTS);}),
});
areaTable[RR_GERUDO_TRAINING_GROUND_MQ_TORCH_SIDE_PLATFORMS] = Region("Gerudo Training Ground Torch Side Platforms", SCENE_GERUDO_TRAINING_GROUND, false, {RA_GERUDO_TRAINING_GROUND}, {
	EventAccess(&logic->GTGPlatformSilverRupees, []{return (((logic->CanUse(RG_FAIRY_BOW) && logic->IsAdult) || logic->CanUse(RG_FIRE_ARROWS)) && logic->CanUse(RG_HOVER_BOOTS));}),
}, {}, {
	Entrance(RR_GERUDO_TRAINING_GROUND_MQ_LEDGE_SIDE_PLATFORMS, []{return (((logic->CanUse(RG_FAIRY_BOW) && logic->IsAdult) || logic->CanUse(RG_FIRE_ARROWS)) && logic->CanUse(RG_HOVER_BOOTS));}),
	Entrance(RR_GERUDO_TRAINING_GROUND_MQ_PLATFORMS_UNLIT_TORCH, []{return ((logic->CanUse(RG_FAIRY_BOW) && logic->IsAdult) || (logic->CanUse(RG_FIRE_ARROWS) || logic->CanUse(RG_LONGSHOT)));}),
	Entrance(RR_GERUDO_TRAINING_GROUND_MQ_MAZE_RIGHT, []{return (logic->MQGTGRightSideSwitch && ((logic->CanUse(RG_FAIRY_BOW) && logic->IsAdult) || (logic->CanUse(RG_FIRE_ARROWS) || logic->CanUse(RG_LONGSHOT))));}),
	Entrance(RR_GERUDO_TRAINING_GROUND_MQ_DINOLFOS_ROOM, []{return true;}),
});
areaTable[RR_GERUDO_TRAINING_GROUND_MQ_PLATFORMS_UNLIT_TORCH] = Region("Gerudo Training Ground MQ Platforms Unlit Torch", SCENE_GERUDO_TRAINING_GROUND, false, {RA_GERUDO_TRAINING_GROUND}, {
	EventAccess(&logic->GTGPlatformSilverRupees, []{return (logic->HasFireSource() && logic->CanUse(RG_HOVER_BOOTS));}),
}, {}, {
	Entrance(RR_GERUDO_TRAINING_GROUND_MQ_UNDERWATER, []{return logic->GTGPlatformSilverRupees;}),
	Entrance(RR_GERUDO_TRAINING_GROUND_MQ_LEDGE_SIDE_PLATFORMS, []{return (logic->HasFireSource() && logic->CanUse(RG_HOVER_BOOTS));}),
	Entrance(RR_GERUDO_TRAINING_GROUND_MQ_TORCH_SIDE_PLATFORMS, []{return (logic->HasFireSource() || logic->CanUse(RG_LONGSHOT));}),
	Entrance(RR_GERUDO_TRAINING_GROUND_MQ_MAZE_RIGHT, []{return (logic->MQGTGRightSideSwitch && (logic->CanUse(RG_LONGSHOT) || (logic->CanUse(RG_HOOKSHOT) && logic->HasFireSource())));}),
});
areaTable[RR_GERUDO_TRAINING_GROUND_MQ_DINOLFOS_ROOM] = Region("Gerudo Training Ground MQ Dinolfos Room", SCENE_GERUDO_TRAINING_GROUND, false, {RA_GERUDO_TRAINING_GROUND}, {}, {
	LOCATION(RC_GERUDO_TRAINING_GROUND_MQ_DINOLFOS_CHEST, (logic->CanUse(RG_MASTER_SWORD) || (logic->CanUse(RG_BIGGORON_SWORD) || (logic->CanUse(RG_MEGATON_HAMMER) || (logic->CanUse(RG_FAIRY_BOW) || ((logic->CanUse(RG_NUTS) || (logic->CanUse(RG_HOOKSHOT) || logic->CanUse(RG_BOOMERANG))) && (logic->CanUse(RG_KOKIRI_SWORD) || logic->CanUse(RG_FAIRY_SLINGSHOT)))))))),
}, {
	Entrance(RR_GERUDO_TRAINING_GROUND_MQ_TORCH_SIDE_PLATFORMS, []{return Here(RR_GERUDO_TRAINING_GROUND_MQ_DINOLFOS_ROOM, []{return (logic->CanUse(RG_MASTER_SWORD) || (logic->CanUse(RG_BIGGORON_SWORD) || (logic->CanUse(RG_MEGATON_HAMMER) || (logic->CanUse(RG_FAIRY_BOW) || ((logic->CanUse(RG_NUTS) || (logic->CanUse(RG_HOOKSHOT) || logic->CanUse(RG_BOOMERANG))) && (logic->CanUse(RG_KOKIRI_SWORD) || logic->CanUse(RG_FAIRY_SLINGSHOT)))))));});}),
});
areaTable[RR_GERUDO_TRAINING_GROUND_MQ_UNDERWATER] = Region("Gerudo Training Ground MQ Underwater", SCENE_GERUDO_TRAINING_GROUND, false, {RA_GERUDO_TRAINING_GROUND}, {}, {
	LOCATION(RC_GERUDO_TRAINING_GROUND_MQ_UNDERWATER_SILVER_RUPEE_CHEST, (logic->HasFireSource() && (logic->CanUse(RG_IRON_BOOTS) && ((logic->WaterTimer() >= 24) && (logic->HasItem(RG_BRONZE_SCALE) && logic->TakeDamage()))))),
}, {
	Entrance(RR_GERUDO_TRAINING_GROUND_MQ_PLATFORMS_UNLIT_TORCH, []{return true;}),
});
areaTable[RR_GERUDO_TRAINING_GROUND_MQ_MAZE_RIGHT] = Region("Gerudo Training Ground MQ Maze Right", SCENE_GERUDO_TRAINING_GROUND, false, {RA_GERUDO_TRAINING_GROUND}, {
	EventAccess(&logic->GTGPlatformSilverRupees, []{return (logic->CanUse(RG_FIRE_ARROWS) && logic->CanUse(RG_HOVER_BOOTS));}),
}, {
	LOCATION(RC_GERUDO_TRAINING_GROUND_MQ_MAZE_RIGHT_CENTRAL_CHEST, true),
	LOCATION(RC_GERUDO_TRAINING_GROUND_MQ_MAZE_RIGHT_SIDE_CHEST, true),
}, {
	Entrance(RR_GERUDO_TRAINING_GROUND_MQ_LOBBY, []{return true;}),
	Entrance(RR_GERUDO_TRAINING_GROUND_MQ_LEDGE_SIDE_PLATFORMS, []{return (logic->CanUse(RG_FIRE_ARROWS) || logic->CanUse(RG_LONGSHOT));}),
	Entrance(RR_GERUDO_TRAINING_GROUND_MQ_PLATFORMS_UNLIT_TORCH, []{return (logic->CanUse(RG_FIRE_ARROWS) || (logic->CanUse(RG_LONGSHOT) || (logic->GTGPlatformSilverRupees && logic->CanUse(RG_HOVER_BOOTS))));}),
	Entrance(RR_GERUDO_TRAINING_GROUND_MQ_LEDGE_SIDE_PLATFORMS, []{return logic->CanUse(RG_FIRE_ARROWS);}),
	Entrance(RR_GERUDO_TRAINING_GROUND_MQ_FURTHEST_PLATFORM, []{return logic->CanUse(RG_FIRE_ARROWS);}),
});
areaTable[RR_GANONS_CASTLE_LOBBY] = Region("Ganon's Castle Lobby", SCENE_INSIDE_GANONS_CASTLE, false, {RA_GANONS_CASTLE}, {}, {
	LOCATION(RC_SHEIK_HINT_GC, true),
}, {
	Entrance(RR_GANONS_CASTLE_ENTRYWAY, []{return true;}),
	Entrance(RR_GANONS_CASTLE_FOREST_TRIAL, []{return true;}),
	Entrance(RR_GANONS_CASTLE_FIRE_TRIAL, []{return true;}),
	Entrance(RR_GANONS_CASTLE_WATER_TRIAL, []{return true;}),
	Entrance(RR_GANONS_CASTLE_SHADOW_TRIAL, []{return true;}),
	Entrance(RR_GANONS_CASTLE_SPIRIT_TRIAL, []{return true;}),
	Entrance(RR_GANONS_CASTLE_LIGHT_TRIAL, []{return logic->CanUse(RG_GOLDEN_GAUNTLETS);}),
	Entrance(RR_GANONS_TOWER_ENTRYWAY, []{return true;}),
	Entrance(RR_GANONS_CASTLE_DEKU_SCRUBS, []{return ((bool)ctx->GetTrickOption(RT_LENS_GANON) || logic->CanUse(RG_LENS_OF_TRUTH));}),
});
areaTable[RR_GANONS_CASTLE_MAIN] = Region("Invalid Region", SCENE_ID_MAX, false, {}, {}, {}, {});
areaTable[RR_GANONS_CASTLE_DEKU_SCRUBS] = Region("Ganon's Castle Deku Scrubs", SCENE_INSIDE_GANONS_CASTLE, false, {RA_GANONS_CASTLE}, {
	EventAccess(&logic->FreeFairies, []{return true;}),
}, {
	LOCATION(RC_GANONS_CASTLE_DEKU_SCRUB_CENTER_LEFT, logic->CanStunDeku()),
	LOCATION(RC_GANONS_CASTLE_DEKU_SCRUB_CENTER_RIGHT, logic->CanStunDeku()),
	LOCATION(RC_GANONS_CASTLE_DEKU_SCRUB_RIGHT, logic->CanStunDeku()),
	LOCATION(RC_GANONS_CASTLE_DEKU_SCRUB_LEFT, logic->CanStunDeku()),
	LOCATION(RC_GANONS_CASTLE_SCRUBS_FAIRY_1, true),
	LOCATION(RC_GANONS_CASTLE_SCRUBS_FAIRY_2, true),
	LOCATION(RC_GANONS_CASTLE_SCRUBS_FAIRY_3, true),
	LOCATION(RC_GANONS_CASTLE_SCRUBS_FAIRY_4, true),
	LOCATION(RC_GANONS_CASTLE_SCRUBS_FAIRY_5, true),
	LOCATION(RC_GANONS_CASTLE_SCRUBS_FAIRY_6, true),
	LOCATION(RC_GANONS_CASTLE_SCRUBS_FAIRY_7, true),
	LOCATION(RC_GANONS_CASTLE_SCRUBS_FAIRY_8, true),
}, {});
areaTable[RR_GANONS_CASTLE_FOREST_TRIAL] = Region("Ganon's Castle Forest Trial", SCENE_INSIDE_GANONS_CASTLE, false, {RA_GANONS_CASTLE}, {
	EventAccess(&logic->ForestTrialClear, []{return (logic->CanUse(RG_LIGHT_ARROWS) && (logic->CanUse(RG_FIRE_ARROWS) || logic->CanUse(RG_DINS_FIRE)));}),
}, {
	LOCATION(RC_GANONS_CASTLE_FOREST_TRIAL_CHEST, logic->CanKillEnemy(RE_WOLFOS)),
	LOCATION(RC_GANONS_CASTLE_FOREST_TRIAL_POT_1, (logic->CanBreakPots() && (logic->CanUse(RG_FIRE_ARROWS) || (logic->CanUse(RG_DINS_FIRE) && (logic->CanUse(RG_FAIRY_BOW) || logic->CanUse(RG_HOOKSHOT)))))),
	LOCATION(RC_GANONS_CASTLE_FOREST_TRIAL_POT_2, (logic->CanBreakPots() && (logic->CanUse(RG_FIRE_ARROWS) || (logic->CanUse(RG_DINS_FIRE) && (logic->CanUse(RG_FAIRY_BOW) || logic->CanUse(RG_HOOKSHOT)))))),
}, {});
areaTable[RR_GANONS_CASTLE_FIRE_TRIAL] = Region("Ganon's Castle Fire Trial", SCENE_INSIDE_GANONS_CASTLE, false, {RA_GANONS_CASTLE}, {
	EventAccess(&logic->FireTrialClear, []{return (logic->CanUse(RG_GORON_TUNIC) && (logic->CanUse(RG_GOLDEN_GAUNTLETS) && (logic->CanUse(RG_LIGHT_ARROWS) && logic->CanUse(RG_LONGSHOT))));}),
}, {
	LOCATION(RC_GANONS_CASTLE_FIRE_TRIAL_POT_1, (logic->CanBreakPots() && (logic->CanUse(RG_GORON_TUNIC) && (logic->CanUse(RG_GOLDEN_GAUNTLETS) && logic->CanUse(RG_LONGSHOT))))),
	LOCATION(RC_GANONS_CASTLE_FIRE_TRIAL_POT_2, (logic->CanBreakPots() && (logic->CanUse(RG_GORON_TUNIC) && (logic->CanUse(RG_GOLDEN_GAUNTLETS) && logic->CanUse(RG_LONGSHOT))))),
	LOCATION(RC_GANONS_CASTLE_FIRE_TRIAL_HEART, logic->CanUse(RG_GORON_TUNIC)),
}, {});
areaTable[RR_GANONS_CASTLE_WATER_TRIAL] = Region("Ganon's Castle Water Trial", SCENE_INSIDE_GANONS_CASTLE, false, {RA_GANONS_CASTLE}, {
	EventAccess(&logic->BlueFireAccess, []{return true;}),
	EventAccess(&logic->FairyPot, []{return (logic->BlueFire() && logic->CanKillEnemy(RE_FREEZARD));}),
	EventAccess(&logic->WaterTrialClear, []{return (logic->BlueFire() && (logic->IsAdult && (logic->CanUse(RG_MEGATON_HAMMER) && logic->CanUse(RG_LIGHT_ARROWS))));}),
}, {
	LOCATION(RC_GANONS_CASTLE_WATER_TRIAL_LEFT_CHEST, true),
	LOCATION(RC_GANONS_CASTLE_WATER_TRIAL_RIGHT_CHEST, true),
	LOCATION(RC_GANONS_CASTLE_WATER_TRIAL_POT_1, (logic->CanBreakPots() && (logic->BlueFire() && (logic->IsAdult && logic->CanUse(RG_MEGATON_HAMMER))))),
	LOCATION(RC_GANONS_CASTLE_WATER_TRIAL_POT_2, (logic->CanBreakPots() && (logic->BlueFire() && (logic->IsAdult && logic->CanUse(RG_MEGATON_HAMMER))))),
	LOCATION(RC_GANONS_CASTLE_WATER_TRIAL_POT_3, (logic->CanBreakPots() && (logic->BlueFire() && logic->CanKillEnemy(RE_FREEZARD)))),
}, {});
areaTable[RR_GANONS_CASTLE_SHADOW_TRIAL] = Region("Ganon's Castle Shadow Trial", SCENE_INSIDE_GANONS_CASTLE, false, {RA_GANONS_CASTLE}, {
	EventAccess(&logic->ShadowTrialClear, []{return (logic->CanUse(RG_LIGHT_ARROWS) && (logic->CanUse(RG_MEGATON_HAMMER) && ((logic->CanUse(RG_FIRE_ARROWS) && ((bool)ctx->GetTrickOption(RT_LENS_GANON) || logic->CanUse(RG_LENS_OF_TRUTH))) || (logic->CanUse(RG_LONGSHOT) && (logic->CanUse(RG_HOVER_BOOTS) || (logic->CanUse(RG_DINS_FIRE) && ((bool)ctx->GetTrickOption(RT_LENS_GANON) || logic->CanUse(RG_LENS_OF_TRUTH))))))));}),
}, {
	LOCATION(RC_GANONS_CASTLE_SHADOW_TRIAL_FRONT_CHEST, (logic->CanUse(RG_FIRE_ARROWS) || (logic->CanUse(RG_HOOKSHOT) || (logic->CanUse(RG_HOVER_BOOTS) || (logic->CanUse(RG_SONG_OF_TIME) || logic->IsChild))))),
	LOCATION(RC_GANONS_CASTLE_SHADOW_TRIAL_GOLDEN_GAUNTLETS_CHEST, (logic->CanUse(RG_FIRE_ARROWS) || (logic->CanUse(RG_LONGSHOT) && (logic->CanUse(RG_HOVER_BOOTS) || logic->CanUse(RG_DINS_FIRE))))),
	LOCATION(RC_GANONS_CASTLE_SHADOW_TRIAL_POT_1, (logic->CanUse(RG_FIRE_ARROWS) || logic->CanUse(RG_LONGSHOT))),
	LOCATION(RC_GANONS_CASTLE_SHADOW_TRIAL_POT_2, (logic->CanUse(RG_FIRE_ARROWS) || logic->CanUse(RG_LONGSHOT))),
	LOCATION(RC_GANONS_CASTLE_SHADOW_TRIAL_POT_3, (logic->CanBreakPots() && (logic->CanUse(RG_MEGATON_HAMMER) && ((logic->CanUse(RG_FIRE_ARROWS) && ((bool)ctx->GetTrickOption(RT_LENS_GANON) || logic->CanUse(RG_LENS_OF_TRUTH))) || (logic->CanUse(RG_LONGSHOT) && (logic->CanUse(RG_HOVER_BOOTS) || (logic->CanUse(RG_DINS_FIRE) && ((bool)ctx->GetTrickOption(RT_LENS_GANON) || logic->CanUse(RG_LENS_OF_TRUTH))))))))),
	LOCATION(RC_GANONS_CASTLE_SHADOW_TRIAL_POT_4, (logic->CanBreakPots() && (logic->CanUse(RG_MEGATON_HAMMER) && ((logic->CanUse(RG_FIRE_ARROWS) && ((bool)ctx->GetTrickOption(RT_LENS_GANON) || logic->CanUse(RG_LENS_OF_TRUTH))) || (logic->CanUse(RG_LONGSHOT) && (logic->CanUse(RG_HOVER_BOOTS) || (logic->CanUse(RG_DINS_FIRE) && ((bool)ctx->GetTrickOption(RT_LENS_GANON) || logic->CanUse(RG_LENS_OF_TRUTH))))))))),
	LOCATION(RC_GANONS_CASTLE_SHADOW_TRIAL_HEART_1, ((logic->CanUse(RG_FIRE_ARROWS) || (logic->CanUse(RG_LONGSHOT) && (logic->CanUse(RG_HOVER_BOOTS) || logic->CanUse(RG_DINS_FIRE)))) && ((bool)ctx->GetTrickOption(RT_LENS_GANON) || (logic->CanUse(RG_LENS_OF_TRUTH) || logic->CanUse(RG_BOOMERANG))))),
	LOCATION(RC_GANONS_CASTLE_SHADOW_TRIAL_HEART_2, ((logic->CanUse(RG_FIRE_ARROWS) || (logic->CanUse(RG_LONGSHOT) && (logic->CanUse(RG_HOVER_BOOTS) || logic->CanUse(RG_DINS_FIRE)))) && ((bool)ctx->GetTrickOption(RT_LENS_GANON) || (logic->CanUse(RG_LENS_OF_TRUTH) || logic->CanUse(RG_BOOMERANG))))),
	LOCATION(RC_GANONS_CASTLE_SHADOW_TRIAL_HEART_3, ((logic->CanUse(RG_FIRE_ARROWS) || (logic->CanUse(RG_LONGSHOT) && (logic->CanUse(RG_HOVER_BOOTS) || logic->CanUse(RG_DINS_FIRE)))) && ((bool)ctx->GetTrickOption(RT_LENS_GANON) || (logic->CanUse(RG_LENS_OF_TRUTH) || logic->CanUse(RG_BOOMERANG))))),
}, {});
areaTable[RR_GANONS_CASTLE_SPIRIT_TRIAL] = Region("Ganon's Castle Spirit Trial", SCENE_INSIDE_GANONS_CASTLE, false, {RA_GANONS_CASTLE}, {
	EventAccess(&logic->NutPot, []{return ((((bool)ctx->GetTrickOption(RT_GANON_SPIRIT_TRIAL_HOOKSHOT) && logic->CanJumpslashExceptHammer()) || logic->CanUse(RG_HOOKSHOT)) && (logic->CanUse(RG_BOMBCHU_5) && (logic->CanUse(RG_FAIRY_BOW) && (logic->CanUse(RG_MIRROR_SHIELD) || (ctx->GetOption(RSK_SUNLIGHT_ARROWS) && logic->CanUse(RG_LIGHT_ARROWS))))));}),
	EventAccess(&logic->SpiritTrialClear, []{return (logic->CanUse(RG_LIGHT_ARROWS) && ((logic->CanUse(RG_MIRROR_SHIELD) || ctx->GetOption(RSK_SUNLIGHT_ARROWS)) && (logic->CanUse(RG_BOMBCHU_5) && (((bool)ctx->GetTrickOption(RT_GANON_SPIRIT_TRIAL_HOOKSHOT) && logic->CanJumpslashExceptHammer()) || logic->CanUse(RG_HOOKSHOT)))));}),
}, {
	LOCATION(RC_GANONS_CASTLE_SPIRIT_TRIAL_CRYSTAL_SWITCH_CHEST, (((bool)ctx->GetTrickOption(RT_GANON_SPIRIT_TRIAL_HOOKSHOT) || logic->CanUse(RG_HOOKSHOT)) && (logic->CanJumpslashExceptHammer() || logic->CanUse(RG_BOMBCHU_5)))),
	LOCATION(RC_GANONS_CASTLE_SPIRIT_TRIAL_INVISIBLE_CHEST, (((bool)ctx->GetTrickOption(RT_GANON_SPIRIT_TRIAL_HOOKSHOT) || logic->CanUse(RG_HOOKSHOT)) && (logic->CanUse(RG_BOMBCHU_5) && ((bool)ctx->GetTrickOption(RT_LENS_GANON) || logic->CanUse(RG_LENS_OF_TRUTH))))),
	LOCATION(RC_GANONS_CASTLE_SPIRIT_TRIAL_POT_1, ((((bool)ctx->GetTrickOption(RT_GANON_SPIRIT_TRIAL_HOOKSHOT) && logic->CanJumpslashExceptHammer()) || logic->CanUse(RG_HOOKSHOT)) && (logic->CanUse(RG_BOMBCHU_5) && (logic->CanUse(RG_FAIRY_BOW) && (logic->CanUse(RG_MIRROR_SHIELD) || (ctx->GetOption(RSK_SUNLIGHT_ARROWS) && logic->CanUse(RG_LIGHT_ARROWS))))))),
	LOCATION(RC_GANONS_CASTLE_SPIRIT_TRIAL_POT_2, ((((bool)ctx->GetTrickOption(RT_GANON_SPIRIT_TRIAL_HOOKSHOT) && logic->CanJumpslashExceptHammer()) || logic->CanUse(RG_HOOKSHOT)) && (logic->CanUse(RG_BOMBCHU_5) && (logic->CanUse(RG_FAIRY_BOW) && (logic->CanUse(RG_MIRROR_SHIELD) || (ctx->GetOption(RSK_SUNLIGHT_ARROWS) && logic->CanUse(RG_LIGHT_ARROWS))))))),
	LOCATION(RC_GANONS_CASTLE_SPIRIT_TRIAL_SUN_FAIRY, logic->CanUse(RG_SUNS_SONG)),
	LOCATION(RC_GANONS_CASTLE_SPIRIT_TRIAL_HEART, true),
}, {});
areaTable[RR_GANONS_CASTLE_LIGHT_TRIAL] = Region("Ganon's Castle Light Trial", SCENE_INSIDE_GANONS_CASTLE, false, {RA_GANONS_CASTLE}, {
	EventAccess(&logic->LightTrialClear, []{return (logic->CanUse(RG_LIGHT_ARROWS) && (logic->CanUse(RG_HOOKSHOT) && (logic->SmallKeys(RR_GANONS_CASTLE, 2) && ((bool)ctx->GetTrickOption(RT_LENS_GANON) || logic->CanUse(RG_LENS_OF_TRUTH)))));}),
}, {
	LOCATION(RC_GANONS_CASTLE_LIGHT_TRIAL_FIRST_LEFT_CHEST, true),
	LOCATION(RC_GANONS_CASTLE_LIGHT_TRIAL_SECOND_LEFT_CHEST, true),
	LOCATION(RC_GANONS_CASTLE_LIGHT_TRIAL_THIRD_LEFT_CHEST, true),
	LOCATION(RC_GANONS_CASTLE_LIGHT_TRIAL_FIRST_RIGHT_CHEST, true),
	LOCATION(RC_GANONS_CASTLE_LIGHT_TRIAL_SECOND_RIGHT_CHEST, true),
	LOCATION(RC_GANONS_CASTLE_LIGHT_TRIAL_THIRD_RIGHT_CHEST, true),
	LOCATION(RC_GANONS_CASTLE_LIGHT_TRIAL_INVISIBLE_ENEMIES_CHEST, ((bool)ctx->GetTrickOption(RT_LENS_GANON) || logic->CanUse(RG_LENS_OF_TRUTH))),
	LOCATION(RC_GANONS_CASTLE_LIGHT_TRIAL_LULLABY_CHEST, (logic->CanUse(RG_ZELDAS_LULLABY) && logic->SmallKeys(RR_GANONS_CASTLE, 1))),
	LOCATION(RC_GANONS_CASTLE_LIGHT_TRIAL_BOULDER_POT_1, (logic->CanBreakPots() && logic->SmallKeys(RR_GANONS_CASTLE, 2))),
	LOCATION(RC_GANONS_CASTLE_LIGHT_TRIAL_POT_1, (logic->CanBreakPots() && (logic->CanUse(RG_HOOKSHOT) && (logic->SmallKeys(RR_GANONS_CASTLE, 2) && ((bool)ctx->GetTrickOption(RT_LENS_GANON) || logic->CanUse(RG_LENS_OF_TRUTH)))))),
	LOCATION(RC_GANONS_CASTLE_LIGHT_TRIAL_POT_2, (logic->CanBreakPots() && (logic->CanUse(RG_HOOKSHOT) && (logic->SmallKeys(RR_GANONS_CASTLE, 2) && ((bool)ctx->GetTrickOption(RT_LENS_GANON) || logic->CanUse(RG_LENS_OF_TRUTH)))))),
}, {});
areaTable[RR_GANONS_CASTLE_MQ_LOBBY] = Region("Ganon's Castle MQ Lobby", SCENE_INSIDE_GANONS_CASTLE, false, {RA_GANONS_CASTLE}, {}, {}, {
	Entrance(RR_GANONS_CASTLE_ENTRYWAY, []{return (logic->CanPassEnemy(RE_GREEN_BUBBLE) || Here(RR_GANONS_CASTLE_MQ_LOBBY, []{return (logic->CanKillEnemy(RE_IRON_KNUCKLE) && logic->CanKillEnemy(RE_ARMOS));}));}),
	Entrance(RR_GANONS_CASTLE_MQ_MAIN, []{return Here(RR_GANONS_CASTLE_MQ_LOBBY, []{return (logic->CanKillEnemy(RE_IRON_KNUCKLE) && logic->CanKillEnemy(RE_ARMOS));});}),
});
areaTable[RR_GANONS_CASTLE_MQ_MAIN] = Region("Ganon's Castle MQ Main", SCENE_INSIDE_GANONS_CASTLE, false, {RA_GANONS_CASTLE}, {}, {
	LOCATION(RC_SHEIK_HINT_MQ_GC, true),
}, {
	Entrance(RR_GANONS_CASTLE_MQ_LOBBY, []{return true;}),
	Entrance(RR_GANONS_CASTLE_MQ_FOREST_TRIAL_STALFOS_ROOM, []{return true;}),
	Entrance(RR_GANONS_CASTLE_MQ_FIRE_TRIAL_MAIN_ROOM, []{return true;}),
	Entrance(RR_GANONS_CASTLE_MQ_WATER_TRIAL_GEYSER_ROOM, []{return true;}),
	Entrance(RR_GANONS_CASTLE_MQ_SHADOW_TRIAL_STARTING_LEDGE, []{return true;}),
	Entrance(RR_GANONS_CASTLE_MQ_SPIRIT_TRIAL_CHAIRS_ROOM, []{return true;}),
	Entrance(RR_GANONS_CASTLE_MQ_LIGHT_TRIAL_DINOLFOS_ROOM, []{return Here(RR_GANONS_CASTLE_MQ_MAIN, []{return logic->CanUse(RG_GOLDEN_GAUNTLETS);});}),
	Entrance(RR_GANONS_TOWER_ENTRYWAY, []{return true;}),
	Entrance(RR_GANONS_CASTLE_MQ_DEKU_SCRUBS, []{return ((bool)ctx->GetTrickOption(RT_LENS_GANON_MQ) || logic->CanUse(RG_LENS_OF_TRUTH));}),
});
areaTable[RR_GANONS_CASTLE_MQ_DEKU_SCRUBS] = Region("Ganon's Castle MQ Deku Scrubs", SCENE_INSIDE_GANONS_CASTLE, false, {RA_GANONS_CASTLE}, {
	EventAccess(&logic->FreeFairies, []{return true;}),
}, {
	LOCATION(RC_GANONS_CASTLE_MQ_DEKU_SCRUB_CENTER_LEFT, logic->CanStunDeku()),
	LOCATION(RC_GANONS_CASTLE_MQ_DEKU_SCRUB_CENTER, logic->CanStunDeku()),
	LOCATION(RC_GANONS_CASTLE_MQ_DEKU_SCRUB_CENTER_RIGHT, logic->CanStunDeku()),
	LOCATION(RC_GANONS_CASTLE_MQ_DEKU_SCRUB_LEFT, logic->CanStunDeku()),
	LOCATION(RC_GANONS_CASTLE_MQ_DEKU_SCRUB_RIGHT, logic->CanStunDeku()),
	LOCATION(RC_GANONS_CASTLE_MQ_SCRUBS_FAIRY_1, true),
	LOCATION(RC_GANONS_CASTLE_MQ_SCRUBS_FAIRY_2, true),
	LOCATION(RC_GANONS_CASTLE_MQ_SCRUBS_FAIRY_3, true),
	LOCATION(RC_GANONS_CASTLE_MQ_SCRUBS_FAIRY_4, true),
	LOCATION(RC_GANONS_CASTLE_MQ_SCRUBS_FAIRY_5, true),
	LOCATION(RC_GANONS_CASTLE_MQ_SCRUBS_FAIRY_6, true),
	LOCATION(RC_GANONS_CASTLE_MQ_SCRUBS_FAIRY_7, true),
	LOCATION(RC_GANONS_CASTLE_MQ_SCRUBS_FAIRY_8, true),
}, {
	Entrance(RR_GANONS_CASTLE_MQ_MAIN, []{return true;}),
});
areaTable[RR_GANONS_CASTLE_MQ_FOREST_TRIAL_STALFOS_ROOM] = Region("Ganon's Castle MQ Forest Trial Stalfos Room", SCENE_INSIDE_GANONS_CASTLE, false, {RA_GANONS_CASTLE}, {}, {
	LOCATION(RC_GANONS_CASTLE_MQ_FOREST_TRIAL_FREESTANDING_KEY, logic->HookshotOrBoomerang()),
}, {
	Entrance(RR_GANONS_CASTLE_MQ_MAIN, []{return true;}),
	Entrance(RR_GANONS_CASTLE_MQ_FOREST_TRIAL_BEAMOS_ROOM, []{return Here(RR_GANONS_CASTLE_MQ_FOREST_TRIAL_STALFOS_ROOM, []{return logic->CanKillEnemy(RE_STALFOS, ED_CLOSE, true, 2);});}),
});
areaTable[RR_GANONS_CASTLE_MQ_FOREST_TRIAL_BEAMOS_ROOM] = Region("Ganon's Castle MQ Forest Trial Beamos Room", SCENE_INSIDE_GANONS_CASTLE, false, {RA_GANONS_CASTLE}, {}, {
	LOCATION(RC_GANONS_CASTLE_MQ_FOREST_TRIAL_EYE_SWITCH_CHEST, logic->CanHitEyeTargets()),
	LOCATION(RC_GANONS_CASTLE_MQ_FOREST_TRIAL_FROZEN_EYE_SWITCH_CHEST, logic->HasFireSource()),
}, {
	Entrance(RR_GANONS_CASTLE_MQ_FOREST_TRIAL_STALFOS_ROOM, []{return true;}),
	Entrance(RR_GANONS_CASTLE_MQ_FOREST_TRIAL_FINAL_ROOM, []{return (logic->IsAdult && logic->CanUse(RG_SONG_OF_TIME));}),
});
areaTable[RR_GANONS_CASTLE_MQ_FOREST_TRIAL_FINAL_ROOM] = Region("Ganon's Castle MQ Forest Trial Final Room", SCENE_INSIDE_GANONS_CASTLE, false, {RA_GANONS_CASTLE}, {
	EventAccess(&logic->ForestTrialClear, []{return logic->CanUse(RG_LIGHT_ARROWS);}),
}, {
	LOCATION(RC_GANONS_CASTLE_MQ_FOREST_TRIAL_POT_1, logic->CanBreakPots()),
	LOCATION(RC_GANONS_CASTLE_MQ_FOREST_TRIAL_POT_2, logic->CanBreakPots()),
}, {
	Entrance(RR_GANONS_CASTLE_MQ_FOREST_TRIAL_BEAMOS_ROOM, []{return true;}),
});
areaTable[RR_GANONS_CASTLE_MQ_FIRE_TRIAL_MAIN_ROOM] = Region("Ganon's Castle MQ Fire Trial Main Room", SCENE_INSIDE_GANONS_CASTLE, false, {RA_GANONS_CASTLE}, {}, {}, {
	Entrance(RR_GANONS_CASTLE_MQ_MAIN, []{return true;}),
	Entrance(RR_GANONS_CASTLE_MQ_FIRE_TRIAL_FINAL_ROOM, []{return (Here(RR_GANONS_CASTLE_MQ_FIRE_TRIAL_MAIN_ROOM, []{return (logic->CanUse(RG_GORON_TUNIC) && logic->CanUse(RG_GOLDEN_GAUNTLETS));}) && (logic->CanUse(RG_GORON_TUNIC) && (logic->CanUse(RG_LONGSHOT) || (logic->CanUse(RG_GOLDEN_GAUNTLETS) && (logic->CanUse(RG_HOVER_BOOTS) || ((bool)ctx->GetTrickOption(RT_GANON_MQ_FIRE_TRIAL) && (logic->IsAdult && logic->CanUse(RG_HOOKSHOT))))))));}),
});
areaTable[RR_GANONS_CASTLE_MQ_FIRE_TRIAL_FINAL_ROOM] = Region("Ganon's Castle MQ Fire Trial Final Room", SCENE_INSIDE_GANONS_CASTLE, false, {RA_GANONS_CASTLE}, {
	EventAccess(&logic->FireTrialClear, []{return logic->CanUse(RG_LIGHT_ARROWS);}),
}, {
	LOCATION(RC_GANONS_CASTLE_MQ_FIRE_TRIAL_POT_1, logic->CanBreakPots()),
	LOCATION(RC_GANONS_CASTLE_MQ_FIRE_TRIAL_POT_2, logic->CanBreakPots()),
}, {});
areaTable[RR_GANONS_CASTLE_MQ_WATER_TRIAL_GEYSER_ROOM] = Region("Ganon's Castle MQ Water Trial Geyser Room", SCENE_INSIDE_GANONS_CASTLE, false, {RA_GANONS_CASTLE}, {
	EventAccess(&logic->BlueFireAccess, []{return (logic->CanJumpslash() || logic->HasExplosives());}),
}, {
	LOCATION(RC_GANONS_CASTLE_MQ_WATER_TRIAL_CHEST, logic->BlueFire()),
	LOCATION(RC_GANONS_CASTLE_MQ_WATER_TRIAL_HEART, logic->BlueFire()),
}, {
	Entrance(RR_GANONS_CASTLE_MQ_MAIN, []{return true;}),
	Entrance(RR_GANONS_CASTLE_MQ_WATER_TRIAL_BLOCK_ROOM, []{return (logic->SmallKeys(RR_GANONS_CASTLE, 3) && Here(RR_GANONS_CASTLE_MQ_WATER_TRIAL_GEYSER_ROOM, []{return logic->BlueFire();}));}),
});
areaTable[RR_GANONS_CASTLE_MQ_WATER_TRIAL_BLOCK_ROOM] = Region("Ganon's Castle MQ Water Trial Block Room", SCENE_INSIDE_GANONS_CASTLE, false, {RA_GANONS_CASTLE}, {}, {}, {
	Entrance(RR_GANONS_CASTLE_MQ_WATER_TRIAL_GEYSER_ROOM, []{return logic->SmallKeys(RR_GANONS_CASTLE, 3);}),
	Entrance(RR_GANONS_CASTLE_MQ_WATER_TRIAL_FINAL_ROOM, []{return (logic->IsAdult && logic->BlueFire());}),
});
areaTable[RR_GANONS_CASTLE_MQ_WATER_TRIAL_FINAL_ROOM] = Region("Ganon's Castle MQ Water Trial Final Room", SCENE_INSIDE_GANONS_CASTLE, false, {RA_GANONS_CASTLE}, {
	EventAccess(&logic->WaterTrialClear, []{return logic->CanUse(RG_LIGHT_ARROWS);}),
}, {
	LOCATION(RC_GANONS_CASTLE_MQ_WATER_TRIAL_POT_1, logic->CanBreakPots()),
	LOCATION(RC_GANONS_CASTLE_MQ_WATER_TRIAL_POT_2, logic->CanBreakPots()),
}, {
	Entrance(RR_GANONS_CASTLE_MQ_WATER_TRIAL_BLOCK_ROOM, []{return Here(RR_GANONS_CASTLE_MQ_WATER_TRIAL_FINAL_ROOM, []{return logic->BlueFire();});}),
});
areaTable[RR_GANONS_CASTLE_MQ_SHADOW_TRIAL_STARTING_LEDGE] = Region("Ganon's Castle MQ Shadow Trial Starting Ledge", SCENE_INSIDE_GANONS_CASTLE, false, {RA_GANONS_CASTLE}, {
	EventAccess(&logic->ShadowTrialFirstChest, []{return logic->CanUse(RG_FAIRY_BOW);}),
}, {}, {
	Entrance(RR_GANONS_CASTLE_MQ_MAIN, []{return true;}),
	Entrance(RR_GANONS_CASTLE_MQ_SHADOW_TRIAL_CHEST_PLATFORM, []{return ((logic->ShadowTrialFirstChest && logic->CanUse(RG_HOOKSHOT)) || (logic->IsAdult && logic->CanUse(RG_HOVER_BOOTS)));}),
});
areaTable[RR_GANONS_CASTLE_MQ_SHADOW_TRIAL_CHEST_PLATFORM] = Region("Ganon's Castle MQ Shadow Trial Chest Platform", SCENE_INSIDE_GANONS_CASTLE, false, {RA_GANONS_CASTLE}, {
	EventAccess(&logic->ShadowTrialFirstChest, []{return logic->CanUse(RG_FAIRY_BOW);}),
}, {
	LOCATION(RC_GANONS_CASTLE_MQ_SHADOW_TRIAL_BOMB_FLOWER_CHEST, logic->ShadowTrialFirstChest),
}, {
	Entrance(RR_GANONS_CASTLE_MQ_SHADOW_TRIAL_STARTING_LEDGE, []{return (logic->CanUse(RG_LONGSHOT) || (logic->IsAdult && logic->CanUse(RG_HOVER_BOOTS)));}),
	Entrance(RR_GANONS_CASTLE_MQ_SHADOW_TRIAL_MOVING_PLATFORM, []{return (((bool)ctx->GetTrickOption(RT_LENS_GANON_MQ) || logic->CanUse(RG_LENS_OF_TRUTH)) && (logic->IsAdult || logic->CanUse(RG_HOVER_BOOTS)));}),
});
areaTable[RR_GANONS_CASTLE_MQ_SHADOW_TRIAL_MOVING_PLATFORM] = Region("Ganon's Castle MQ Shadow Trial Moving Platform", SCENE_INSIDE_GANONS_CASTLE, false, {RA_GANONS_CASTLE}, {
	EventAccess(&logic->ShadowTrialFirstChest, []{return logic->CanDetonateUprightBombFlower();}),
}, {}, {
	Entrance(RR_GANONS_CASTLE_MQ_SHADOW_TRIAL_CHEST_PLATFORM, []{return (logic->IsAdult || (logic->CanUse(RG_HOOKSHOT) || logic->CanUse(RG_HOVER_BOOTS)));}),
	Entrance(RR_GANONS_CASTLE_MQ_SHADOW_TRIAL_BEAMOS_TORCH, []{return true;}),
});
areaTable[RR_GANONS_CASTLE_MQ_SHADOW_TRIAL_BEAMOS_TORCH] = Region("Ganon's Castle MQ Shadow Trial Beamos Torch", SCENE_INSIDE_GANONS_CASTLE, false, {RA_GANONS_CASTLE}, {}, {}, {
	Entrance(RR_GANONS_CASTLE_MQ_SHADOW_TRIAL_MOVING_PLATFORM, []{return ((bool)ctx->GetTrickOption(RT_LENS_GANON_MQ) || logic->CanUse(RG_LENS_OF_TRUTH));}),
	Entrance(RR_GANONS_CASTLE_MQ_SHADOW_TRIAL_FAR_SIDE, []{return (logic->HasFireSource() || (logic->CanUse(RG_HOVER_BOOTS) || (logic->IsAdult && ((bool)ctx->GetTrickOption(RT_GANON_MQ_SHADOW_TRIAL) && logic->CanUse(RG_FAIRY_BOW)))));}),
});
areaTable[RR_GANONS_CASTLE_MQ_SHADOW_TRIAL_FAR_SIDE] = Region("Ganon's Castle MQ Shadow Trial Far Side", SCENE_INSIDE_GANONS_CASTLE, false, {RA_GANONS_CASTLE}, {}, {
	LOCATION(RC_GANONS_CASTLE_MQ_SHADOW_TRIAL_EYE_SWITCH_CHEST, logic->CanHitEyeTargets()),
}, {
	Entrance(RR_GANONS_CASTLE_MQ_SHADOW_TRIAL_BEAMOS_TORCH, []{return (logic->CanUse(RG_FIRE_ARROWS) || logic->CanUse(RG_HOVER_BOOTS));}),
	Entrance(RR_GANONS_CASTLE_MQ_SHADOW_TRIAL_FINAL_ROOM, []{return ((bool)ctx->GetTrickOption(RT_LENS_GANON_MQ) || logic->CanUse(RG_LENS_OF_TRUTH));}),
});
areaTable[RR_GANONS_CASTLE_MQ_SHADOW_TRIAL_FINAL_ROOM] = Region("Ganon's Castle MQ Shadow Trial Final Room", SCENE_INSIDE_GANONS_CASTLE, false, {RA_GANONS_CASTLE}, {
	EventAccess(&logic->ShadowTrialClear, []{return logic->CanUse(RG_LIGHT_ARROWS);}),
}, {
	LOCATION(RC_GANONS_CASTLE_MQ_SHADOW_TRIAL_POT_1, logic->CanBreakPots()),
	LOCATION(RC_GANONS_CASTLE_MQ_SHADOW_TRIAL_POT_2, logic->CanBreakPots()),
}, {
	Entrance(RR_GANONS_CASTLE_MQ_SHADOW_TRIAL_FAR_SIDE, []{return ((bool)ctx->GetTrickOption(RT_LENS_GANON_MQ) || logic->CanUse(RG_LENS_OF_TRUTH));}),
});
areaTable[RR_GANONS_CASTLE_MQ_SPIRIT_TRIAL_CHAIRS_ROOM] = Region("Ganon's Castle MQ Spirit Trial Chairs Room", SCENE_INSIDE_GANONS_CASTLE, false, {RA_GANONS_CASTLE}, {}, {}, {
	Entrance(RR_GANONS_CASTLE_MQ_MAIN, []{return true;}),
	Entrance(RR_GANONS_CASTLE_MQ_SPIRIT_TRIAL_BEFORE_SWITCH, []{return Here(RR_GANONS_CASTLE_MQ_SPIRIT_TRIAL_CHAIRS_ROOM, []{return ((logic->CanHitEyeTargets() || (bool)ctx->GetTrickOption(RT_RUSTED_SWITCHES)) && logic->CanUse(RG_MEGATON_HAMMER));});}),
});
areaTable[RR_GANONS_CASTLE_MQ_SPIRIT_TRIAL_BEFORE_SWITCH] = Region("Ganon's Castle MQ Spirit Trial Before Switch", SCENE_INSIDE_GANONS_CASTLE, false, {RA_GANONS_CASTLE}, {}, {
	LOCATION(RC_GANONS_CASTLE_MQ_SPIRIT_TRIAL_FIRST_CHEST, logic->CanPassEnemy(RE_GREEN_BUBBLE)),
}, {
	Entrance(RR_GANONS_CASTLE_MQ_SPIRIT_TRIAL_CHAIRS_ROOM, []{return true;}),
	Entrance(RR_GANONS_CASTLE_MQ_SPIRIT_TRIAL_AFTER_SWITCH, []{return Here(RR_GANONS_CASTLE_MQ_SPIRIT_TRIAL_BEFORE_SWITCH, []{return logic->CanUse(RG_BOMBCHU_5);});}),
});
areaTable[RR_GANONS_CASTLE_MQ_SPIRIT_TRIAL_AFTER_SWITCH] = Region("Ganon's Castle MQ Spirit Trial After Switch", SCENE_INSIDE_GANONS_CASTLE, false, {RA_GANONS_CASTLE}, {}, {
	LOCATION(RC_GANONS_CASTLE_MQ_SPIRIT_TRIAL_INVISIBLE_CHEST, ((bool)ctx->GetTrickOption(RT_LENS_GANON_MQ) || logic->CanUse(RG_LENS_OF_TRUTH))),
	LOCATION(RC_GANONS_CASTLE_MQ_SPIRIT_TRIAL_SUN_FRONT_LEFT_CHEST, ((logic->CanUse(RG_FIRE_ARROWS) && logic->CanUse(RG_MIRROR_SHIELD)) || (ctx->GetOption(RSK_SUNLIGHT_ARROWS) && logic->CanUse(RG_LIGHT_ARROWS)))),
	LOCATION(RC_GANONS_CASTLE_MQ_SPIRIT_TRIAL_SUN_BACK_LEFT_CHEST, ((logic->CanUse(RG_FIRE_ARROWS) && logic->CanUse(RG_MIRROR_SHIELD)) || (ctx->GetOption(RSK_SUNLIGHT_ARROWS) && logic->CanUse(RG_LIGHT_ARROWS)))),
	LOCATION(RC_GANONS_CASTLE_MQ_SPIRIT_TRIAL_GOLDEN_GAUNTLETS_CHEST, ((logic->CanUse(RG_FIRE_ARROWS) && logic->CanUse(RG_MIRROR_SHIELD)) || (ctx->GetOption(RSK_SUNLIGHT_ARROWS) && logic->CanUse(RG_LIGHT_ARROWS)))),
	LOCATION(RC_GANONS_CASTLE_MQ_SPIRIT_TRIAL_SUN_BACK_RIGHT_CHEST, ((logic->CanUse(RG_FIRE_ARROWS) && logic->CanUse(RG_MIRROR_SHIELD)) || (ctx->GetOption(RSK_SUNLIGHT_ARROWS) && logic->CanUse(RG_LIGHT_ARROWS)))),
}, {
	Entrance(RR_GANONS_CASTLE_MQ_SPIRIT_TRIAL_BEFORE_SWITCH, []{return Here(RR_GANONS_CASTLE_MQ_SPIRIT_TRIAL_AFTER_SWITCH, []{return logic->CanUse(RG_BOMBCHU_5);});}),
	Entrance(RR_GANONS_CASTLE_MQ_SPIRIT_TRIAL_FINAL_ROOM, []{return (Here(RR_GANONS_CASTLE_MQ_SPIRIT_TRIAL_AFTER_SWITCH, []{return (logic->CanUse(RG_FIRE_ARROWS) && logic->CanUse(RG_MIRROR_SHIELD));}) || (ctx->GetOption(RSK_SUNLIGHT_ARROWS) && logic->CanUse(RG_LIGHT_ARROWS)));}),
});
areaTable[RR_GANONS_CASTLE_MQ_SPIRIT_TRIAL_FINAL_ROOM] = Region("Ganon's Castle MQ Spirit Trial Final Room", SCENE_INSIDE_GANONS_CASTLE, false, {RA_GANONS_CASTLE}, {
	EventAccess(&logic->SpiritTrialClear, []{return logic->CanUse(RG_LIGHT_ARROWS);}),
	EventAccess(&logic->NutPot, []{return true;}),
}, {
	LOCATION(RC_GANONS_CASTLE_MQ_SPIRIT_TRIAL_POT_1, logic->CanBreakPots()),
	LOCATION(RC_GANONS_CASTLE_MQ_SPIRIT_TRIAL_POT_2, logic->CanBreakPots()),
}, {
	Entrance(RR_GANONS_CASTLE_MQ_SPIRIT_TRIAL_AFTER_SWITCH, []{return true;}),
});
areaTable[RR_GANONS_CASTLE_MQ_LIGHT_TRIAL_DINOLFOS_ROOM] = Region("Ganon's Castle MQ Light Trial Dinolfos Room", SCENE_INSIDE_GANONS_CASTLE, false, {RA_GANONS_CASTLE}, {}, {}, {
	Entrance(RR_GANONS_CASTLE_MQ_MAIN, []{return true;}),
	Entrance(RR_GANONS_CASTLE_MQ_LIGHT_TRIAL_TRIFORCE_ROOM, []{return Here(RR_GANONS_CASTLE_MQ_LIGHT_TRIAL_DINOLFOS_ROOM, []{return (logic->CanKillEnemy(RE_DINOLFOS) && logic->CanKillEnemy(RE_TORCH_SLUG));});}),
});
areaTable[RR_GANONS_CASTLE_MQ_LIGHT_TRIAL_TRIFORCE_ROOM] = Region("Ganon's Castle MQ Light Trial Triforce Room", SCENE_INSIDE_GANONS_CASTLE, false, {RA_GANONS_CASTLE}, {}, {
	LOCATION(RC_GANONS_CASTLE_MQ_LIGHT_TRIAL_LULLABY_CHEST, logic->CanUse(RG_ZELDAS_LULLABY)),
}, {
	Entrance(RR_GANONS_CASTLE_MQ_LIGHT_TRIAL_DINOLFOS_ROOM, []{return true;}),
	Entrance(RR_GANONS_CASTLE_MQ_LIGHT_TRIAL_BOULDER_ROOM_FRONT, []{return logic->SmallKeys(RR_GANONS_CASTLE, 2);}),
});
areaTable[RR_GANONS_CASTLE_MQ_LIGHT_TRIAL_BOULDER_ROOM_FRONT] = Region("Ganon's Castle MQ Light Trial Boulder Room Front", SCENE_INSIDE_GANONS_CASTLE, false, {RA_GANONS_CASTLE}, {}, {}, {
	Entrance(RR_GANONS_CASTLE_MQ_LIGHT_TRIAL_TRIFORCE_ROOM, []{return logic->SmallKeys(RR_GANONS_CASTLE, 2);}),
	Entrance(RR_GANONS_CASTLE_MQ_LIGHT_TRIAL_BOULDER_ROOM_BACK, []{return (logic->CanUse(RG_HOOKSHOT) || (bool)ctx->GetTrickOption(RT_GANON_MQ_LIGHT_TRIAL));}),
});
areaTable[RR_GANONS_CASTLE_MQ_LIGHT_TRIAL_BOULDER_ROOM_BACK] = Region("Ganon's Castle MQ Light Trial Boulder Room Back", SCENE_INSIDE_GANONS_CASTLE, false, {RA_GANONS_CASTLE}, {}, {
	LOCATION(RC_GANONS_CASTLE_MQ_LIGHT_TRIAL_LEFT_HEART, true),
	LOCATION(RC_GANONS_CASTLE_MQ_LIGHT_TRIAL_RIGHT_HEART, true),
}, {
	Entrance(RR_GANONS_CASTLE_MQ_LIGHT_TRIAL_BOULDER_ROOM_FRONT, []{return (logic->CanUse(RG_HOOKSHOT) || (bool)ctx->GetTrickOption(RT_GANON_MQ_LIGHT_TRIAL));}),
	Entrance(RR_GANONS_CASTLE_MQ_LIGHT_TRIAL_FINAL_ROOM, []{return (logic->SmallKeys(RR_GANONS_CASTLE, 3) && (((bool)ctx->GetTrickOption(RT_LENS_GANON_MQ) || logic->CanUse(RG_LENS_OF_TRUTH)) && (logic->CanUse(RG_FAIRY_SLINGSHOT) || (logic->CanJumpslash() || (logic->HasExplosives() || (logic->CanUse(RG_FAIRY_BOW) || logic->CanUse(RG_BOOMERANG)))))));}),
});
areaTable[RR_GANONS_CASTLE_MQ_LIGHT_TRIAL_FINAL_ROOM] = Region("Ganon's Castle MQ Light Trial Final Room", SCENE_INSIDE_GANONS_CASTLE, false, {RA_GANONS_CASTLE}, {
	EventAccess(&logic->LightTrialClear, []{return logic->CanUse(RG_LIGHT_ARROWS);}),
}, {
	LOCATION(RC_GANONS_CASTLE_MQ_LIGHT_TRIAL_POT_1, logic->CanBreakPots()),
	LOCATION(RC_GANONS_CASTLE_MQ_LIGHT_TRIAL_POT_2, logic->CanBreakPots()),
}, {});
areaTable[RR_GANONS_TOWER_ENTRYWAY] = Region("Ganon's Tower Entryway", SCENE_INSIDE_GANONS_CASTLE, false, {RA_GANONS_CASTLE}, {}, {}, {
	Entrance(RR_GANONS_CASTLE_LOBBY, []{return ctx->GetDungeon(Rando::GANONS_CASTLE)->IsVanilla();}),
	Entrance(RR_GANONS_CASTLE_MQ_MAIN, []{return ctx->GetDungeon(Rando::GANONS_CASTLE)->IsMQ();}),
	Entrance(RR_GANONS_TOWER_FLOOR_1, []{return ((logic->ForestTrialClear || ctx->GetTrial(TK_FOREST_TRIAL)->IsSkipped()) && ((logic->FireTrialClear || ctx->GetTrial(TK_FIRE_TRIAL)->IsSkipped()) && ((logic->WaterTrialClear || ctx->GetTrial(TK_WATER_TRIAL)->IsSkipped()) && ((logic->ShadowTrialClear || ctx->GetTrial(TK_SHADOW_TRIAL)->IsSkipped()) && ((logic->SpiritTrialClear || ctx->GetTrial(TK_SPIRIT_TRIAL)->IsSkipped()) && (logic->LightTrialClear || ctx->GetTrial(TK_LIGHT_TRIAL)->IsSkipped()))))));}),
});
areaTable[RR_GANONS_TOWER_FLOOR_1] = Region("Ganon's Tower Floor 1", SCENE_GANONS_TOWER, false, {}, {}, {}, {
	Entrance(RR_GANONS_TOWER_ENTRYWAY, []{return Here(RR_GANONS_TOWER_FLOOR_1, []{return logic->CanKillEnemy(RE_DINOLFOS, ED_CLOSE, true, 2);});}),
	Entrance(RR_GANONS_TOWER_FLOOR_2, []{return Here(RR_GANONS_TOWER_FLOOR_1, []{return logic->CanKillEnemy(RE_DINOLFOS, ED_CLOSE, true, 2);});}),
});
areaTable[RR_GANONS_TOWER_FLOOR_2] = Region("Ganon's Tower Floor 2", SCENE_GANONS_TOWER, false, {}, {}, {
	LOCATION(RC_GANONS_TOWER_BOSS_KEY_CHEST, logic->CanKillEnemy(RE_STALFOS, ED_CLOSE, true, 2)),
}, {
	Entrance(RR_GANONS_TOWER_FLOOR_1, []{return Here(RR_GANONS_TOWER_FLOOR_2, []{return logic->CanKillEnemy(RE_STALFOS, ED_CLOSE, true, 2);});}),
	Entrance(RR_GANONS_TOWER_FLOOR_3, []{return Here(RR_GANONS_TOWER_FLOOR_2, []{return logic->CanKillEnemy(RE_STALFOS, ED_CLOSE, true, 2);});}),
});
areaTable[RR_GANONS_TOWER_FLOOR_3] = Region("Ganon's Tower Floor 3", SCENE_GANONS_TOWER, false, {}, {}, {}, {
	Entrance(RR_GANONS_TOWER_FLOOR_2, []{return Here(RR_GANONS_TOWER_FLOOR_3, []{return logic->CanKillEnemy(RE_IRON_KNUCKLE, ED_CLOSE, true, 2);});}),
	Entrance(RR_GANONS_TOWER_BEFORE_GANONDORF_LAIR, []{return Here(RR_GANONS_TOWER_FLOOR_3, []{return logic->CanKillEnemy(RE_IRON_KNUCKLE, ED_CLOSE, true, 2);});}),
});
areaTable[RR_GANONS_TOWER_BEFORE_GANONDORF_LAIR] = Region("Ganon's Tower Before Ganondorf's Lair", SCENE_GANONS_TOWER, false, {}, {}, {
	LOCATION(RC_GANONS_CASTLE_GANONS_TOWER_POT_1, logic->CanBreakPots()),
	LOCATION(RC_GANONS_CASTLE_GANONS_TOWER_POT_2, logic->CanBreakPots()),
	LOCATION(RC_GANONS_CASTLE_GANONS_TOWER_POT_3, logic->CanBreakPots()),
	LOCATION(RC_GANONS_CASTLE_GANONS_TOWER_POT_4, logic->CanBreakPots()),
	LOCATION(RC_GANONS_CASTLE_GANONS_TOWER_POT_5, logic->CanBreakPots()),
	LOCATION(RC_GANONS_CASTLE_GANONS_TOWER_POT_6, logic->CanBreakPots()),
	LOCATION(RC_GANONS_CASTLE_GANONS_TOWER_POT_7, logic->CanBreakPots()),
	LOCATION(RC_GANONS_CASTLE_GANONS_TOWER_POT_8, logic->CanBreakPots()),
	LOCATION(RC_GANONS_CASTLE_GANONS_TOWER_POT_9, logic->CanBreakPots()),
	LOCATION(RC_GANONS_CASTLE_GANONS_TOWER_POT_10, logic->CanBreakPots()),
	LOCATION(RC_GANONS_CASTLE_GANONS_TOWER_POT_11, logic->CanBreakPots()),
	LOCATION(RC_GANONS_CASTLE_GANONS_TOWER_POT_12, logic->CanBreakPots()),
	LOCATION(RC_GANONS_CASTLE_GANONS_TOWER_POT_13, logic->CanBreakPots()),
	LOCATION(RC_GANONS_CASTLE_GANONS_TOWER_POT_14, logic->CanBreakPots()),
	LOCATION(RC_GANONS_CASTLE_GANONS_TOWER_POT_15, logic->CanBreakPots()),
	LOCATION(RC_GANONS_CASTLE_GANONS_TOWER_POT_16, logic->CanBreakPots()),
	LOCATION(RC_GANONS_CASTLE_GANONS_TOWER_POT_17, logic->CanBreakPots()),
	LOCATION(RC_GANONS_CASTLE_GANONS_TOWER_POT_18, logic->CanBreakPots()),
}, {
	Entrance(RR_GANONS_TOWER_FLOOR_3, []{return Here(RR_GANONS_TOWER_BEFORE_GANONDORF_LAIR, []{return true;});}),
	Entrance(RR_GANONS_TOWER_GANONDORF_LAIR, []{return Here(RR_GANONS_TOWER_BEFORE_GANONDORF_LAIR, []{return logic->HasItem(RG_GANONS_CASTLE_BOSS_KEY);});}),
});
areaTable[RR_GANONS_TOWER_GANONDORF_LAIR] = Region("Ganondorf's Lair", SCENE_GANONDORF_BOSS, false, {}, {}, {
	LOCATION(RC_GANONDORF_HINT, logic->HasBossSoul(RG_GANON_SOUL)),
}, {
	Entrance(RR_GANONS_CASTLE_ESCAPE, []{return logic->CanKillEnemy(RE_GANONDORF);}),
});
areaTable[RR_GANONS_CASTLE_ESCAPE] = Region("Ganon's Castle Escape", SCENE_GANONS_TOWER_COLLAPSE_EXTERIOR, false, {}, {}, {}, {
	Entrance(RR_GANONS_CASTLE_GANON_ARENA, []{return true;}),
});
areaTable[RR_GANONS_CASTLE_GANON_ARENA] = Region("Ganon's Arena", SCENE_GANON_BOSS, false, {}, {}, {
	LOCATION(RC_GANON, logic->CanKillEnemy(RE_GANON)),
}, {});
// clang-format on
}
