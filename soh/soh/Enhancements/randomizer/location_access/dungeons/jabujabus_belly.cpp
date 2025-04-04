#include "soh/Enhancements/randomizer/location_access.h"
#include "soh/Enhancements/randomizer/entrance.h"
#include "soh/Enhancements/randomizer/dungeon.h"

using namespace Rando;

void RegionTable_Init_JabuJabusBelly() {
    // clang-format off
    // Vanilla/MQ Decider
    areaTable[RR_JABU_JABUS_BELLY_ENTRYWAY] = Region("Jabu Jabus Belly Entryway", "Jabu Jabus Belly", {RA_JABU_JABUS_BELLY}, NO_DAY_NIGHT_CYCLE, {}, {}, {
        //Exits
        Entrance(RR_JABU_JABUS_BELLY_BEGINNING,    []{return ctx->GetDungeon(JABU_JABUS_BELLY)->IsVanilla();}),
        Entrance(RR_JABU_JABUS_BELLY_MQ_BEGINNING, []{return ctx->GetDungeon(JABU_JABUS_BELLY)->IsMQ();}),
        Entrance(RR_ZORAS_FOUNTAIN,                []{return true;}),
    });

#pragma region Vanilla

    areaTable[RR_JABU_JABUS_BELLY_BEGINNING] = Region("Jabu Jabus Belly Beginning", "Jabu Jabus Belly", {RA_JABU_JABUS_BELLY}, NO_DAY_NIGHT_CYCLE, {}, {}, {
        //Exits
        Entrance(RR_JABU_JABUS_BELLY_ENTRYWAY,  []{return true;}),
        Entrance(RR_JABU_JABUS_BELLY_LIFT_ROOM, []{return logic->CanUseProjectile();}),
    });

    //Combines Lift room middle and lower, 1F holes room, the forked corridor, and it's side rooms
    areaTable[RR_JABU_JABUS_BELLY_LIFT_ROOM] = Region("Jabu Jabus Belly Lift Room", "Jabu Jabus Belly", {RA_JABU_JABUS_BELLY}, NO_DAY_NIGHT_CYCLE, {}, {
        //Locations
        LOCATION(RC_JABU_JABUS_BELLY_DEKU_SCRUB,                  logic->HasItem(RG_BRONZE_SCALE) && (logic->IsChild || logic->HasItem(RG_SILVER_SCALE) || ctx->GetTrickOption(RT_JABU_ALCOVE_JUMP_DIVE) || logic->CanUse(RG_IRON_BOOTS)) && logic->CanStunDeku()),
        LOCATION(RC_JABU_JABUS_BELLY_PLATFORM_ROOM_SMALL_CRATE_1, logic->CanBreakSmallCrates()),
        LOCATION(RC_JABU_JABUS_BELLY_PLATFORM_ROOM_SMALL_CRATE_2, logic->CanBreakSmallCrates()),
    }, {
        //Exits
        Entrance(RR_JABU_JABUS_BELLY_BEGINNING,               []{return true;}),
        Entrance(RR_JABU_JABUS_BELLY_HOLES_ROOM,              []{return true;}),
        Entrance(RR_JABU_JABUS_BELLY_WATER_SWITCH_ROOM_SOUTH, []{return true;}),
        Entrance(RR_JABU_JABUS_BELLY_NEAR_BOSS_ROOM,          []{return logic->LoweredJabuPath || (ctx->GetTrickOption(RT_JABU_BOSS_HOVER) && logic->CanUse(RG_HOVER_BOOTS));}),
    });

    areaTable[RR_JABU_JABUS_BELLY_HOLES_ROOM] = Region("Jabu Jabus Belly Holes Room", "Jabu Jabus Belly", {RA_JABU_JABUS_BELLY}, NO_DAY_NIGHT_CYCLE, {}, {
        //Locations
        LOCATION(RC_JABU_JABUS_BELLY_GS_LOBBY_BASEMENT_LOWER, logic->HookshotOrBoomerang()),
        LOCATION(RC_JABU_JABUS_BELLY_GS_LOBBY_BASEMENT_UPPER, logic->HookshotOrBoomerang()),
    }, {
        //Exits
        Entrance(RR_JABU_JABUS_BELLY_LIFT_ROOM,               []{return true;}),
        Entrance(RR_JABU_JABUS_BELLY_FORKED_CORRIDOR,         []{return true;}),
        Entrance(RR_JABU_JABUS_BELLY_BIGOCTO_LEDGE,           []{return logic->JabuNorthTentacle;}),
        Entrance(RR_JABU_JABUS_BELLY_B1_CUBE,                 []{return true;}),
        Entrance(RR_JABU_JABUS_BELLY_WATER_SWITCH_ROOM_NORTH, []{return true;}),
    });

    //contains B1 of hole room (aside from the ledge leading to big octo), 2 octorock room and north water switch room
    areaTable[RR_JABU_JABUS_BELLY_B1_CUBE] = Region("Jabu Jabus Belly B1 Cube", "Jabu Jabus Belly", {RA_JABU_JABUS_BELLY}, NO_DAY_NIGHT_CYCLE, {
        //Events
        EventAccess(&logic->FairyPot, []{return logic->CanUse(RG_BOOMERANG) || (logic->CanUse(RG_HOVER_BOOTS) && logic->CanKillEnemy(RE_OCTOROK));}),
    }, {
        //Locations
        LOCATION(RC_JABU_JABUS_BELLY_TWO_OCTOROK_POT_1, logic->CanBreakPots() && (logic->CanUse(RG_BOOMERANG) || (logic->CanUse(RG_HOVER_BOOTS) && logic->CanKillEnemy(RE_OCTOROK, ED_BOOMERANG, false)))),
        LOCATION(RC_JABU_JABUS_BELLY_TWO_OCTOROK_POT_2, logic->CanBreakPots() && (logic->CanUse(RG_BOOMERANG) || (logic->CanUse(RG_HOVER_BOOTS) && logic->CanKillEnemy(RE_OCTOROK, ED_BOOMERANG, false)))),
        LOCATION(RC_JABU_JABUS_BELLY_TWO_OCTOROK_POT_3, logic->CanBreakPots() && (logic->CanUse(RG_BOOMERANG) || (logic->CanUse(RG_HOVER_BOOTS) && logic->CanKillEnemy(RE_OCTOROK, ED_BOOMERANG, false)))),
        LOCATION(RC_JABU_JABUS_BELLY_TWO_OCTOROK_POT_4, logic->CanBreakPots() && (logic->CanUse(RG_BOOMERANG) || (logic->CanUse(RG_HOVER_BOOTS) && logic->CanKillEnemy(RE_OCTOROK, ED_BOOMERANG, false)))),
        LOCATION(RC_JABU_JABUS_BELLY_TWO_OCTOROK_POT_5, logic->CanBreakPots() && (logic->CanUse(RG_BOOMERANG) || (logic->CanUse(RG_HOVER_BOOTS) && logic->CanKillEnemy(RE_OCTOROK, ED_BOOMERANG, false)))),
    }, {
        //Exits
        Entrance(RR_JABU_JABUS_BELLY_HOLES_ROOM, []{return true;}),
    });

    areaTable[RR_JABU_JABUS_BELLY_WATER_SWITCH_ROOM_NORTH] = Region("Jabu Jabus Belly Water Switch Room North", "Jabu Jabus Belly", {RA_JABU_JABUS_BELLY}, NO_DAY_NIGHT_CYCLE, {
        EventAccess(&logic->JabuRutoIn1F, []{return logic->IsAdult || logic->HasItem(RG_BRONZE_SCALE);}),
    }, {
        //Locations
        LOCATION(RC_JABU_JABUS_BELLY_GS_WATER_SWITCH_ROOM, logic->HookshotOrBoomerang()),
    }, {
        //Exits
        //there's tricks for getting here with bunny-jumps or just side-hops
        Entrance(RR_JABU_JABUS_BELLY_WATER_SWITCH_ROOM_LEDGE, []{return logic->HasItem(RG_BRONZE_SCALE) || logic->HasItem(RG_HOVER_BOOTS);}),
        Entrance(RR_JABU_JABUS_BELLY_WATER_SWITCH_ROOM_SOUTH, []{return logic->IsAdult || logic->HasItem(RG_BRONZE_SCALE);}),
        Entrance(RR_JABU_JABUS_BELLY_HOLES_ROOM,              []{return true;}),
    });

    areaTable[RR_JABU_JABUS_BELLY_WATER_SWITCH_ROOM_SOUTH] = Region("Jabu Jabus Belly Water Switch Room South", "Jabu Jabus Belly", {RA_JABU_JABUS_BELLY}, NO_DAY_NIGHT_CYCLE, {}, {
        //Locations
        LOCATION(RC_JABU_JABUS_BELLY_GS_WATER_SWITCH_ROOM, logic->HookshotOrBoomerang()),
    }, {
        //Exits
        Entrance(RR_JABU_JABUS_BELLY_WATER_SWITCH_ROOM_NORTH, []{return logic->IsAdult || logic->HasItem(RG_BRONZE_SCALE);}),
        Entrance(RR_JABU_JABUS_BELLY_WATER_SWITCH_ROOM_LEDGE, []{return logic->HasItem(RG_BRONZE_SCALE) || logic->HasItem(RG_HOVER_BOOTS);}),
        Entrance(RR_JABU_JABUS_BELLY_LIFT_ROOM,               []{return logic->CanUseProjectile();}),
    });

    areaTable[RR_JABU_JABUS_BELLY_WATER_SWITCH_ROOM_LEDGE] = Region("Jabu Jabus Belly Water Switch Room Ledge", "Jabu Jabus Belly", {RA_JABU_JABUS_BELLY}, NO_DAY_NIGHT_CYCLE, {
        //Events
        EventAccess(&logic->FairyPot, []{return true;}),
    }, {
        //Locations
        //this is the logic for climbing back and forth to use the pots to kill the skull...                                                       or killing the skull before climbing to grab the token
        LOCATION(RC_JABU_JABUS_BELLY_GS_WATER_SWITCH_ROOM, logic->HasItem(RG_BRONZE_SCALE) || (logic->IsAdult && logic->CanUse(RG_HOVER_BOOTS)) || logic->CanKillEnemy(RE_GOLD_SKULLTULA, ED_BOMB_THROW)),
        LOCATION(RC_JABU_JABUS_BELLY_BASEMENT_POT_1, logic->CanBreakPots()),
        LOCATION(RC_JABU_JABUS_BELLY_BASEMENT_POT_2, logic->CanBreakPots()),
        LOCATION(RC_JABU_JABUS_BELLY_BASEMENT_POT_3, logic->CanBreakPots()),
    }, {
        //Exits
        Entrance(RR_JABU_JABUS_BELLY_WATER_SWITCH_ROOM_NORTH, []{return true;}),
        Entrance(RR_JABU_JABUS_BELLY_WATER_SWITCH_ROOM_SOUTH, []{return true;}),
    });

    areaTable[RR_JABU_JABUS_BELLY_FORKED_CORRIDOR] = Region("Jabu Jabus Belly Forked Corridor", "Jabu Jabus Belly", {RA_JABU_JABUS_BELLY}, NO_DAY_NIGHT_CYCLE, {}, {}, {
        //Exits
        Entrance(RR_JABU_JABUS_BELLY_HOLES_ROOM,      []{return true;}),
        Entrance(RR_JABU_JABUS_BELLY_FORK_WEST,       []{return logic->JabuRutoIn1F;}),
        Entrance(RR_JABU_JABUS_BELLY_FORK_NORTH_WEST, []{return logic->JabuWestTentacle;}),
        Entrance(RR_JABU_JABUS_BELLY_FORK_NORTH,      []{return logic->JabuEastTentacle;}),
        Entrance(RR_JABU_JABUS_BELLY_FORK_NORTH_EAST, []{return logic->JabuWestTentacle;}),
        Entrance(RR_JABU_JABUS_BELLY_FORK_EAST,       []{return logic->JabuRutoIn1F;}),
    });

    areaTable[RR_JABU_JABUS_BELLY_FORK_WEST] = Region("Jabu Jabus Belly Fork West", "Jabu Jabus Belly", {RA_JABU_JABUS_BELLY}, NO_DAY_NIGHT_CYCLE, {
        EventAccess(&logic->JabuWestTentacle, []{return logic->CanKillEnemy(RE_TENTACLE, ED_BOOMERANG);}),
    }, {
        LOCATION(RC_JABU_JABUS_BELLY_MAP_CHEST, logic->JabuWestTentacle),
    }, {
        Entrance(RR_JABU_JABUS_BELLY_FORKED_CORRIDOR, []{return true;}),
    });

    areaTable[RR_JABU_JABUS_BELLY_FORK_NORTH_WEST] = Region("Jabu Jabus Belly Fork North West", "Jabu Jabus Belly", {RA_JABU_JABUS_BELLY}, NO_DAY_NIGHT_CYCLE, {}, {
        //Locations
        //ruto could theoretically clear this room, but it's hard because of the timer and she doesn't appear with you when you respawn after failing, which would force a savewarp
        LOCATION(RC_JABU_JABUS_BELLY_COMPASS_CHEST, logic->CanKillEnemy(RE_SHABOM)),
    }, {
        //Exits
        Entrance(RR_JABU_JABUS_BELLY_FORKED_CORRIDOR, []{return Here(RR_JABU_JABUS_BELLY_FORK_NORTH_WEST, []{return logic->CanKillEnemy(RE_SHABOM);});}),
    });

    areaTable[RR_JABU_JABUS_BELLY_FORK_NORTH] = Region("Jabu Jabus Belly Fork North", "Jabu Jabus Belly", {RA_JABU_JABUS_BELLY}, NO_DAY_NIGHT_CYCLE, {
        //Events
        EventAccess(&logic->JabuNorthTentacle, []{return logic->CanKillEnemy(RE_TENTACLE, ED_BOOMERANG);}),
    }, {}, {
        //Exits
        //implied logic->CanKillEnemy(RE_BARI)
        Entrance(RR_JABU_JABUS_BELLY_FORKED_CORRIDOR, []{return logic->JabuNorthTentacle;}),
    });

    areaTable[RR_JABU_JABUS_BELLY_FORK_NORTH_EAST] = Region("Jabu Jabus Belly Fork North East", "Jabu Jabus Belly", {RA_JABU_JABUS_BELLY}, NO_DAY_NIGHT_CYCLE, {
        //Events
        EventAccess(&logic->JabuEastTentacle, []{return logic->CanKillEnemy(RE_TENTACLE, ED_BOOMERANG);}),
    }, {}, {
        //Exits
        Entrance(RR_JABU_JABUS_BELLY_FORKED_CORRIDOR, []{return logic->JabuEastTentacle;}),
    });

    areaTable[RR_JABU_JABUS_BELLY_FORK_EAST] = Region("Jabu Jabus Belly Fork East", "Jabu Jabus Belly", {RA_JABU_JABUS_BELLY}, NO_DAY_NIGHT_CYCLE, {}, {
        //We can kill the Stingers with ruto
        LOCATION(RC_JABU_JABUS_BELLY_BOOMERANG_CHEST, logic->JabuRutoIn1F || logic->CanKillEnemy(RE_STINGER, ED_CLOSE, true, 4)),
    }, {
        Entrance(RR_JABU_JABUS_BELLY_FORKED_CORRIDOR, []{return true;}),
    });

    areaTable[RR_JABU_JABUS_BELLY_BIGOCTO_LEDGE] = Region("Jabu Jabus Belly Bigocto Ledge", "Jabu Jabus Belly", {RA_JABU_JABUS_BELLY}, NO_DAY_NIGHT_CYCLE, {}, {
        //Locations
        //Only adult can get the token without assistance
        LOCATION(RC_JABU_JABUS_BELLY_GS_LOBBY_BASEMENT_UPPER, logic->IsAdult && logic->CanGetEnemyDrop(RE_GOLD_SKULLTULA, ED_SHORT_JUMPSLASH)),
        //You can get the LOWER skull token from here as adult with hovers backwalk and a backflip, but it's trickworthy and not relevant unless you can beat tentacles without rang
    }, {
        //Exits
        Entrance(RR_JABU_JABUS_BELLY_HOLES_ROOM, []{return true;}),
        Entrance(RR_JABU_JABUS_BELLY_BIGOCTO,    []{return logic->JabuRutoIn1F && Here(RR_JABU_JABUS_BELLY_BIGOCTO_LEDGE, []{return logic->CanKillEnemy(RE_BIG_OCTO);});}),
    });

    areaTable[RR_JABU_JABUS_BELLY_BIGOCTO] = Region("Jabu Jabus Belly Bigocto", "Jabu Jabus Belly", {RA_JABU_JABUS_BELLY}, NO_DAY_NIGHT_CYCLE, {}, {}, {
        //Exits
        Entrance(RR_JABU_JABUS_BELLY_BIGOCTO_LEDGE, []{return true;}),
        Entrance(RR_JABU_JABUS_BELLY_ABOVE_BIGOCTO, []{return logic->JabuRutoIn1F && Here(RR_JABU_JABUS_BELLY_BIGOCTO, []{return logic->CanKillEnemy(RE_BIG_OCTO);});}),
    });

    areaTable[RR_JABU_JABUS_BELLY_ABOVE_BIGOCTO] = Region("Jabu Jabus Belly Above Bigocto", "Jabu Jabus Belly", {RA_JABU_JABUS_BELLY}, NO_DAY_NIGHT_CYCLE, {
        //Events
        EventAccess(&logic->FairyPot, []{return true;}),
        EventAccess(&logic->NutPot,   []{return true;}),
    }, {
        //Locations
        LOCATION(RC_JABU_JABUS_BELLY_ABOVE_BIG_OCTO_POT_1, logic->CanBreakPots()),
        LOCATION(RC_JABU_JABUS_BELLY_ABOVE_BIG_OCTO_POT_2, logic->CanBreakPots()),
        LOCATION(RC_JABU_JABUS_BELLY_ABOVE_BIG_OCTO_POT_3, logic->CanBreakPots()),
    }, {
        //Exits
        Entrance(RR_JABU_JABUS_BELLY_CUBES_ROOM, []{return true;}),
    });

    areaTable[RR_JABU_JABUS_BELLY_CUBES_ROOM] =  Region("Jabu Jabus Belly Cubes Room", "Jabu Jabus Belly", {RA_JABU_JABUS_BELLY}, NO_DAY_NIGHT_CYCLE, {}, {}, {
        //Exits
        Entrance(RR_JABU_JABUS_BELLY_ABOVE_BIGOCTO, []{return true;}),
        Entrance(RR_JABU_JABUS_BELLY_LIFT_UPPER,    []{return logic->CanUse(RG_BOOMERANG);}),
    });

    areaTable[RR_JABU_JABUS_BELLY_LIFT_UPPER] = Region("Jabu Jabus Belly Lift Upper", "Jabu Jabus Belly", {RA_JABU_JABUS_BELLY}, NO_DAY_NIGHT_CYCLE, {
        //Events
        EventAccess(&logic->LoweredJabuPath, []{return true;}),
    }, {}, {
        //Exits
        Entrance(RR_JABU_JABUS_BELLY_LIFT_ROOM,  []{return true;}),
        Entrance(RR_JABU_JABUS_BELLY_CUBES_ROOM, []{return true;}),
    });

    areaTable[RR_JABU_JABUS_BELLY_NEAR_BOSS_ROOM] = Region("Jabu Jabus Belly Near Boss Room", "Jabu Jabus Belly", {RA_JABU_JABUS_BELLY}, NO_DAY_NIGHT_CYCLE, {}, {
        //Locations
        LOCATION(RC_JABU_JABUS_BELLY_GS_NEAR_BOSS, logic->CanKillEnemy(RE_GOLD_SKULLTULA, ED_BOMB_THROW)),
    }, {
        //Exits
        Entrance(RR_JABU_JABUS_BELLY_LIFT_ROOM,     []{return true;}),
        Entrance(RR_JABU_JABUS_BELLY_BOSS_ENTRYWAY, []{return logic->CanUse(RG_BOOMERANG) || (ctx->GetTrickOption(RT_JABU_NEAR_BOSS_RANGED) && (logic->CanUse(RG_HOOKSHOT) || logic->CanUse(RG_FAIRY_BOW) || logic->CanUse(RG_FAIRY_SLINGSHOT))) || (ctx->GetTrickOption(RT_JABU_NEAR_BOSS_EXPLOSIVES) && (logic->CanUse(RG_BOMBCHU_5) || (logic->CanUse(RG_HOVER_BOOTS) && logic->CanUse(RG_BOMB_BAG))));}),
    });

#pragma endregion

#pragma region MQ

    areaTable[RR_JABU_JABUS_BELLY_MQ_BEGINNING] = Region("Jabu Jabus Belly MQ Beginning", "Jabu Jabus Belly", {RA_JABU_JABUS_BELLY}, NO_DAY_NIGHT_CYCLE, {
        //Events
        EventAccess(&logic->NutPot, []{return true;}),
    }, {
        //Locations
        LOCATION(RC_JABU_JABUS_BELLY_MQ_MAP_CHEST,             logic->BlastOrSmash()),
        LOCATION(RC_JABU_JABUS_BELLY_MQ_FIRST_ROOM_SIDE_CHEST, logic->CanUse(RG_FAIRY_SLINGSHOT)),
        LOCATION(RC_JABU_JABUS_BELLY_MQ_ENTRANCE_POT_1,        logic->CanBreakPots()),
        LOCATION(RC_JABU_JABUS_BELLY_MQ_ENTRANCE_POT_2,        logic->CanBreakPots()),
        LOCATION(RC_JABU_JABUS_BELLY_MQ_FIRST_GRASS_1,         logic->CanCutShrubs()),
        LOCATION(RC_JABU_JABUS_BELLY_MQ_FIRST_GRASS_2,         logic->CanCutShrubs()),
    }, {
        //Exits
        Entrance(RR_JABU_JABUS_BELLY_ENTRYWAY,     []{return true;}),
        Entrance(RR_JABU_JABUS_BELLY_MQ_LIFT_ROOM, []{return Here(RR_JABU_JABUS_BELLY_MQ_BEGINNING, []{return logic->CanUse(RG_FAIRY_SLINGSHOT);});}),
    });

    areaTable[RR_JABU_JABUS_BELLY_MQ_LIFT_ROOM] = Region("Jabu Jabus Belly MQ Lift Room", "Jabu Jabus Belly", {RA_JABU_JABUS_BELLY}, NO_DAY_NIGHT_CYCLE, {
        //Events
        EventAccess(&logic->MQJabuLiftRoomCow, []{return logic->CanUse(RG_FAIRY_SLINGSHOT);}),
    }, {
        //Locations
        LOCATION(RC_JABU_JABUS_BELLY_MQ_SECOND_ROOM_LOWER_CHEST,  true),
        LOCATION(RC_JABU_JABUS_BELLY_MQ_LIFT_HEART_1,             true),
        LOCATION(RC_JABU_JABUS_BELLY_MQ_LIFT_HEART_2,             true),
        LOCATION(RC_JABU_JABUS_BELLY_MQ_LIFT_RUPEE_1,             logic->CanUse(RG_IRON_BOOTS)),
        LOCATION(RC_JABU_JABUS_BELLY_MQ_LIFT_RUPEE_2,             logic->CanUse(RG_IRON_BOOTS)),
        LOCATION(RC_JABU_JABUS_BELLY_MQ_LIFT_RUPEE_3,             logic->CanUse(RG_IRON_BOOTS)),
    }, {
        //Exits
        Entrance(RR_JABU_JABUS_BELLY_MQ_BEGINNING,            []{return true;}),
        Entrance(RR_JABU_JABUS_BELLY_MQ_UNDERWATER_ALCOVE,    []{return logic->HasItem(RG_SILVER_SCALE) || (logic->HasItem(RG_BRONZE_SCALE) && ((logic->IsChild || logic->CanUse(RG_IRON_BOOTS) || ctx->GetTrickOption(RT_JABU_ALCOVE_JUMP_DIVE))));}),
        Entrance(RR_JABU_JABUS_BELLY_MQ_HOLES_ROOM,           []{return logic->MQJabuHolesRoomDoor;}),
        Entrance(RR_JABU_JABUS_BELLY_MQ_LIFT_ROOM_EAST_LEDGE, []{return logic->LoweredJabuPath || logic->CanUse(RG_HOVER_BOOTS) || (logic->CanUse(RG_HOOKSHOT) && logic->MQJabuLiftRoomCow);}),
        Entrance(RR_JABU_JABUS_BELLY_MQ_WATER_SWITCH_ROOM_PAST_GEYSER, []{return logic->MQJabuWaterSwitchLiftAccess;}),
    });

    areaTable[RR_JABU_JABUS_BELLY_MQ_UNDERWATER_ALCOVE] = Region("Jabu Jabus Belly MQ Underwater Alcove", "Jabu Jabus Belly", {RA_JABU_JABUS_BELLY}, NO_DAY_NIGHT_CYCLE, {
        //Events
        EventAccess(&logic->MQJabuHolesRoomDoor, []{return true;}),
    }, {
        //Locations
        LOCATION(RC_JABU_JABUS_BELLY_MQ_COMPASS_CHEST, logic->CanHitSwitch(ED_HOOKSHOT, true) || (ctx->GetTrickOption(RT_JABU_MQ_RANG_JUMP) && logic->CanUse(RG_BOOMERANG) && logic->HasItem(RG_BRONZE_SCALE))),
        LOCATION(RC_JABU_JABUS_BELLY_MQ_GEYSER_POT_1,  logic->CanBreakPots()),
        LOCATION(RC_JABU_JABUS_BELLY_MQ_GEYSER_POT_2,  logic->CanBreakPots()),
        //Getting the ones closest to the ledge with rang may be a trick due to the awkward angle without blind shooting through the flesh
        LOCATION(RC_JABU_JABUS_BELLY_MQ_LIFT_RUPEE_1,  logic->HasItem(RG_GOLDEN_SCALE) || logic->CanUse(RG_BOOMERANG)),
        LOCATION(RC_JABU_JABUS_BELLY_MQ_LIFT_RUPEE_2,  logic->HasItem(RG_SILVER_SCALE) || logic->CanUse(RG_BOOMERANG)),
        LOCATION(RC_JABU_JABUS_BELLY_MQ_LIFT_RUPEE_3,  logic->HasItem(RG_BRONZE_SCALE) || logic->CanUse(RG_BOOMERANG)),
    }, {
        //Exits
        Entrance(RR_JABU_JABUS_BELLY_MQ_LIFT_ROOM, []{return logic->HasItem(RG_BRONZE_SCALE);}),
    });

    areaTable[RR_JABU_JABUS_BELLY_MQ_HOLES_ROOM] = Region("Jabu Jabus Belly MQ Holes Room", "Jabu Jabus Belly", {RA_JABU_JABUS_BELLY}, NO_DAY_NIGHT_CYCLE, {}, {
        //Locations
        LOCATION(RC_JABU_JABUS_BELLY_MQ_BASEMENT_NEAR_VINES_CHEST,    logic->CanUse(RG_FAIRY_SLINGSHOT)),
        LOCATION(RC_JABU_JABUS_BELLY_MQ_BASEMENT_NEAR_SWITCHES_CHEST, logic->CanUse(RG_FAIRY_SLINGSHOT)),
        LOCATION(RC_JABU_JABUS_BELLY_MQ_PIT_GRASS_1,                  logic->CanCutShrubs() && logic->HasExplosives()),
        LOCATION(RC_JABU_JABUS_BELLY_MQ_PIT_GRASS_2,                  logic->CanCutShrubs() && logic->HasExplosives()),
        LOCATION(RC_JABU_JABUS_BELLY_MQ_BASEMENT_GRASS_1,             logic->CanCutShrubs()),
        LOCATION(RC_JABU_JABUS_BELLY_MQ_BASEMENT_GRASS_2,             logic->CanCutShrubs()),
        LOCATION(RC_JABU_JABUS_BELLY_MQ_BASEMENT_GRASS_3,             logic->CanCutShrubs()),
    }, {
        //Exits
        Entrance(RR_JABU_JABUS_BELLY_MQ_LIFT_ROOM,            []{return true;}),
        Entrance(RR_JABU_JABUS_BELLY_MQ_WATER_SWITCH_ROOM,    []{return true;}),
        Entrance(RR_JABU_JABUS_BELLY_MQ_FORKED_CORRIDOR,      []{return logic->CanUse(RG_BOOMERANG) && logic->HasExplosives() && Here(RR_JABU_JABUS_BELLY_MQ_HOLES_ROOM, []{return logic->CanUse(RG_FAIRY_SLINGSHOT);});}),
        Entrance(RR_JABU_JABUS_BELLY_MQ_INVISIBLE_KEESE_ROOM, []{return logic->JabuNorthTentacle;}),
        Entrance(RR_JABU_JABUS_BELLY_MQ_BIGOCTO,              []{return logic->JabuWestTentacle && Here(RR_JABU_JABUS_BELLY_MQ_HOLES_ROOM, []{return logic->CanUse(RG_FAIRY_SLINGSHOT);});}),
    });

    areaTable[RR_JABU_JABUS_BELLY_MQ_WATER_SWITCH_ROOM] = Region("Jabu Jabus Belly MQ Water Switch Room", "Jabu Jabus Belly", {RA_JABU_JABUS_BELLY}, NO_DAY_NIGHT_CYCLE, {
        EventAccess(&logic->MQJabuWaterSwitchLiftAccess, []{return logic->MQJabuWaterSwitchLiftAccess || logic->CanKillEnemy(RE_LIZALFOS);}),
    }, {
        //Locations
        LOCATION(RC_JABU_JABUS_BELLY_MQ_BOOMERANG_ROOM_SMALL_CHEST, true),
                                                                                                                                //Implies logic->CanKillEnemy(RE_LIKE_LIKE) && logic->CanKillEnemy(RE_STINGER). Without swim, jump from the song of time block to the vines.
        LOCATION(RC_JABU_JABUS_BELLY_MQ_BOOMERANG_CHEST,          logic->CanKillEnemy(RE_LIZALFOS)),
        LOCATION(RC_JABU_JABUS_BELLY_MQ_GS_BOOMERANG_CHEST_ROOM,  (logic->CanUse(RG_SONG_OF_TIME) && logic->CanGetEnemyDrop(RE_GOLD_SKULLTULA)) || (ctx->GetTrickOption(RT_JABU_MQ_SOT_GS) && logic->CanUse(RG_BOOMERANG))),
        LOCATION(RC_JABU_JABUS_BELLY_MQ_TIME_BLOCK_POT_1,         logic->CanBreakPots()),
        LOCATION(RC_JABU_JABUS_BELLY_MQ_TIME_BLOCK_POT_2,         logic->CanBreakPots()),
        LOCATION(RC_JABU_JABUS_BELLY_MQ_BASEMENT_BOOMERANG_GRASS, logic->CanCutShrubs()),
    }, {
        //Exits
        //without swim, jump from rang chest to the other side
        Entrance(RR_JABU_JABUS_BELLY_MQ_WATER_SWITCH_ROOM_PAST_GEYSER, []{return Here(RR_JABU_JABUS_BELLY_MQ_WATER_SWITCH_ROOM, []{return logic->CanKillEnemy(RE_LIZALFOS);});}),
        Entrance(RR_JABU_JABUS_BELLY_MQ_HOLES_ROOM,                    []{return (logic->IsAdult || logic->HasItem(RG_BRONZE_SCALE)) && Here(RR_JABU_JABUS_BELLY_MQ_WATER_SWITCH_ROOM, []{return logic->CanKillEnemy(RE_LIZALFOS);});}),
    });

    areaTable[RR_JABU_JABUS_BELLY_MQ_WATER_SWITCH_ROOM_PAST_GEYSER] = Region("Jabu Jabus Belly MQ Water Switch Room Past Geyser", "Jabu Jabus Belly", {RA_JABU_JABUS_BELLY}, NO_DAY_NIGHT_CYCLE, {}, {}, {
        Entrance(RR_JABU_JABUS_BELLY_MQ_WATER_SWITCH_ROOM, []{return logic->MQJabuWaterSwitchLiftAccess;}),
        Entrance(RR_JABU_JABUS_BELLY_MQ_LIFT_ROOM,         []{return true;}),
    });

    areaTable[RR_JABU_JABUS_BELLY_MQ_FORKED_CORRIDOR] = Region("Jabu Jabus Belly MQ Forked Corridor", "Jabu Jabus Belly", {RA_JABU_JABUS_BELLY}, NO_DAY_NIGHT_CYCLE, {}, {}, {
        //Exits
        Entrance(RR_JABU_JABUS_BELLY_MQ_HOLES_ROOM,      []{return logic->CanUse(RG_BOOMERANG);}),
        //If some mode lets an age use sticks and not sling, and other use sling and not sticks, this needs changing
        Entrance(RR_JABU_JABUS_BELLY_MQ_FORK_WEST,       []{return logic->JabuEastTentacle;}),
        Entrance(RR_JABU_JABUS_BELLY_MQ_FORK_NORTH_WEST, []{return true;}),
        Entrance(RR_JABU_JABUS_BELLY_MQ_FORK_NORTH,      []{return logic->BlastOrSmash();}),
        Entrance(RR_JABU_JABUS_BELLY_MQ_FORK_NORTH_EAST, []{return logic->JabuWestTentacle;}),
        Entrance(RR_JABU_JABUS_BELLY_MQ_FORK_EAST,       []{return Here(RR_JABU_JABUS_BELLY_MQ_FORKED_CORRIDOR, []{return logic->CanUse(RG_FAIRY_SLINGSHOT) && logic->CanUse(RG_STICKS);}) || Here(RR_JABU_JABUS_BELLY_MQ_FORKED_CORRIDOR, []{return logic->HasFireSource();});}),
    });

    areaTable[RR_JABU_JABUS_BELLY_MQ_FORK_WEST] = Region("Jabu Jabus Belly MQ Fork West", "Jabu Jabus Belly", {RA_JABU_JABUS_BELLY}, NO_DAY_NIGHT_CYCLE, {
        //Events
        EventAccess(&logic->JabuWestTentacle, []{return logic->CanKillEnemy(RE_TENTACLE, ED_BOOMERANG);}),
    }, {}, {
        //Exits
        Entrance(RR_JABU_JABUS_BELLY_MQ_FORKED_CORRIDOR, []{return true;}),
    });
    areaTable[RR_JABU_JABUS_BELLY_MQ_FORK_NORTH_WEST] = Region("Jabu Jabus Belly MQ Fork North West", "Jabu Jabus Belly", {RA_JABU_JABUS_BELLY}, NO_DAY_NIGHT_CYCLE, {}, {
        //Locations
        LOCATION(RC_JABU_JABUS_BELLY_MQ_GS_TAILPASARAN_ROOM, logic->HasExplosives() && logic->CanGetEnemyDrop(RE_GOLD_SKULLTULA, ED_BOOMERANG)),
    }, {
        //Exits
        Entrance(RR_JABU_JABUS_BELLY_MQ_FORKED_CORRIDOR, []{return true;}),
    });
    areaTable[RR_JABU_JABUS_BELLY_MQ_FORK_NORTH] = Region("Jabu Jabus Belly MQ Fork North", "Jabu Jabus Belly", {RA_JABU_JABUS_BELLY}, NO_DAY_NIGHT_CYCLE, {
        //Events
        EventAccess(&logic->JabuNorthTentacle, []{return logic->JabuNorthTentacle || logic->CanUse(RG_BOOMERANG);}),
    }, {}, {
        //Exits
        Entrance(RR_JABU_JABUS_BELLY_MQ_FORKED_CORRIDOR, []{return true;}),
    });
    areaTable[RR_JABU_JABUS_BELLY_MQ_FORK_NORTH_EAST] = Region("Jabu Jabus Belly MQ Fork North East", "Jabu Jabus Belly", {RA_JABU_JABUS_BELLY}, NO_DAY_NIGHT_CYCLE, {}, {
        //Locations
        //Implies CanKillEnemy(RE_LIKE_LIKE)
        LOCATION(RC_JABU_JABUS_BELLY_MQ_FALLING_LIKE_LIKE_ROOM_CHEST, logic->CanUse(RG_FAIRY_SLINGSHOT)),
        LOCATION(RC_JABU_JABUS_BELLY_MQ_LIKE_LIKES_POT_1,             logic->CanBreakPots()),
        LOCATION(RC_JABU_JABUS_BELLY_MQ_LIKE_LIKES_POT_2,             logic->CanBreakPots()),
        LOCATION(RC_JABU_JABUS_BELLY_MQ_FALLING_LIKE_LIKE_GRASS,      logic->CanCutShrubs()),
        LOCATION(RC_JABU_JABUS_BELLY_MQ_TRIPLE_HALLWAY_SMALL_CRATE_1, logic->CanBreakSmallCrates()),
        LOCATION(RC_JABU_JABUS_BELLY_MQ_TRIPLE_HALLWAY_SMALL_CRATE_2, logic->CanBreakSmallCrates()),
    }, {
        //Exits
        Entrance(RR_JABU_JABUS_BELLY_MQ_FORKED_CORRIDOR, []{return true;}),
    });
    areaTable[RR_JABU_JABUS_BELLY_MQ_FORK_EAST] = Region("Jabu Jabus Belly MQ Fork East", "Jabu Jabus Belly", {RA_JABU_JABUS_BELLY}, NO_DAY_NIGHT_CYCLE, {
        //Events
        EventAccess(&logic->JabuEastTentacle, []{return logic->CanKillEnemy(RE_TENTACLE, ED_BOOMERANG);}),
    }, {}, {
        //Exits
        Entrance(RR_JABU_JABUS_BELLY_MQ_FORKED_CORRIDOR, []{return true;}),
    });

    areaTable[RR_JABU_JABUS_BELLY_MQ_INVISIBLE_KEESE_ROOM] = Region("Jabu Jabus Belly MQ Invisible Keese Room", "Jabu Jabus Belly", {RA_JABU_JABUS_BELLY}, NO_DAY_NIGHT_CYCLE, {}, {
        //Locations
        LOCATION(RC_JABU_JABUS_BELLY_MQ_GS_INVISIBLE_ENEMIES_ROOM, //firstly, we can just use FAs to clear the web and then longshot the skull
                                                                   logic->CanUse(RG_FIRE_ARROWS) && logic->CanGetEnemyDrop(RE_GOLD_SKULLTULA, ED_LONGSHOT) ||
                                                                   //Otherwise, we have to cross the gap and kill the skull.
                                                                   (logic->CanGetEnemyDrop(RE_GOLD_SKULLTULA, ED_BOOMERANG) &&
                                                                   //We can cheese the gap with hovers
                                                                    ((logic->CanUse(RG_HOVER_BOOTS) ||
                                                                   //Otherwise we have to kill the enemies to raise the platform. This persists so we can do it as the other age.
                                                                        Here(RR_JABU_JABUS_BELLY_MQ_INVISIBLE_KEESE_ROOM, []{return (ctx->GetTrickOption(RT_LENS_JABU_MQ) || logic->CanUse(RG_LENS_OF_TRUTH)) &&
                                                                                                                                                                                           logic->CanKillEnemy(RE_STINGER, ED_BOOMERANG, false, 2, false, true) && 
                                                                                                                                                                                           //we can hit the keese farthest from the water with irons and hookshot, but we won't be able to see it while doing so
                                                                                                                                                                                           (logic->CanKillEnemy(RE_KEESE, ED_LONGSHOT, false) || (ctx->GetTrickOption(RT_LENS_JABU_MQ) && logic->CanUse(RG_HOOKSHOT) && logic->CanUse(RG_IRON_BOOTS)));}))
                                                                   //If we kill the enemies, we then need to cross the water using the platform. Note that adult cannot do so while swimming because MQ jank.
                                                                        && ((logic->IsChild && logic->HasItem(RG_BRONZE_SCALE)) || (logic->IsAdult && logic->CanUse(RG_IRON_BOOTS)))))),
    }, {
        //Exits
        Entrance(RR_JABU_JABUS_BELLY_MQ_HOLES_ROOM, []{return (logic->JabuNorthTentacle || logic->TakeDamage()) && logic->HasItem(RG_BRONZE_SCALE);}),
    });

    areaTable[RR_JABU_JABUS_BELLY_MQ_BIGOCTO] = Region("Jabu Jabus Belly MQ Big Octo", "Jabu Jabus Belly", {RA_JABU_JABUS_BELLY}, NO_DAY_NIGHT_CYCLE, {}, {}, {
        // Need Ruto here
        Entrance(RR_JABU_JABUS_BELLY_MQ_HOLES_ROOM,     []{return logic->CanKillEnemy(RE_BIG_OCTO);}),
        Entrance(RR_JABU_JABUS_BELLY_MQ_ABOVE_BIGOCTO,  []{return logic->CanKillEnemy(RE_BIG_OCTO);}),
    });

    areaTable[RR_JABU_JABUS_BELLY_MQ_ABOVE_BIGOCTO] = Region("Jabu Jabus Belly MQ Above Big Octo", "Jabu Jabus Belly", {RA_JABU_JABUS_BELLY}, NO_DAY_NIGHT_CYCLE, {}, {}, {
        //Exits
        Entrance(RR_JABU_JABUS_BELLY_MQ_CUBES_ROOM, []{return true;}),
        Entrance(RR_JABU_JABUS_BELLY_MQ_BIGOCTO,    []{return logic->TakeDamage() && Here(RR_JABU_JABUS_BELLY_MQ_ABOVE_BIGOCTO, []{return logic->CanKillEnemy(RE_BIG_OCTO);});}),
    });

    areaTable[RR_JABU_JABUS_BELLY_MQ_CUBES_ROOM] = Region("Jabu Jabus Belly MQ Cubes Room", "Jabu Jabus Belly", {RA_JABU_JABUS_BELLY}, NO_DAY_NIGHT_CYCLE, {}, {
        //Locations
        LOCATION(RC_JABU_JABUS_BELLY_MQ_COW,                    logic->CanUse(RG_EPONAS_SONG) && logic->CanUse(RG_FAIRY_SLINGSHOT)),
        LOCATION(RC_JABU_JABUS_BELLY_MQ_WIGGLERS_GRASS,         logic->CanCutShrubs()),
        LOCATION(RC_JABU_JABUS_BELLY_MQ_AFTER_BIG_OCTO_GRASS_1, logic->CanCutShrubs()),
        LOCATION(RC_JABU_JABUS_BELLY_MQ_AFTER_BIG_OCTO_GRASS_2, logic->CanCutShrubs()),
    }, {
        Entrance(RR_JABU_JABUS_BELLY_MQ_ABOVE_BIGOCTO,  []{return true;}),
        Entrance(RR_JABU_JABUS_BELLY_MQ_ABOVE_LIFT_ROOM, []{return logic->CanUse(RG_BOOMERANG) && logic->CanUse(RG_FAIRY_SLINGSHOT);}),
    });

    areaTable[RR_JABU_JABUS_BELLY_MQ_ABOVE_LIFT_ROOM] = Region("Jabu Jabus Belly MQ Cubes Room", "Jabu Jabus Belly", {RA_JABU_JABUS_BELLY}, NO_DAY_NIGHT_CYCLE, {
        //Events
        EventAccess(&logic->LoweredJabuPath, []{return true;}),
    }, {}, {
        //Exits
        Entrance(RR_JABU_JABUS_BELLY_MQ_CUBES_ROOM, []{return true;}),
        Entrance(RR_JABU_JABUS_BELLY_MQ_LIFT_ROOM,  []{return true;}),
    });

    areaTable[RR_JABU_JABUS_BELLY_MQ_LIFT_ROOM_EAST_LEDGE] = Region("Jabu Jabus Belly MQ Lift Room East Ledge", "Jabu Jabus Belly", {RA_JABU_JABUS_BELLY}, NO_DAY_NIGHT_CYCLE, {}, {
        //Locations
        LOCATION(RC_JABU_JABUS_BELLY_MQ_SECOND_ROOM_UPPER_CHEST, logic->MQJabuLiftRoomCow),
    }, {
        //Exits
        Entrance(RR_JABU_JABUS_BELLY_MQ_LIFT_ROOM, []{return true;}),
        Entrance(RR_JABU_JABUS_BELLY_MQ_EAST_ROOM, []{return logic->JabuNorthTentacle;}),
    });

    areaTable[RR_JABU_JABUS_BELLY_MQ_EAST_ROOM] = Region("Jabu Jabus Belly MQ Boss Region", "Jabu Jabus Belly", {RA_JABU_JABUS_BELLY}, NO_DAY_NIGHT_CYCLE, {
        //Events
        EventAccess(&logic->FairyPot, []{return true;}),
    }, {
        //Locations
        LOCATION(RC_JABU_JABUS_BELLY_MQ_NEAR_BOSS_CHEST,     logic->CanUse(RG_FAIRY_SLINGSHOT)),
        LOCATION(RC_JABU_JABUS_BELLY_MQ_GS_NEAR_BOSS,        logic->CanUse(RG_BOOMERANG) || (ctx->GetTrickOption(RT_JABU_NEAR_BOSS_RANGED) && logic->CanUse(RG_HOOKSHOT))),
        LOCATION(RC_JABU_JABUS_BELLY_MQ_BEFORE_BOSS_POT_1,   logic->CanBreakPots()),
        LOCATION(RC_JABU_JABUS_BELLY_MQ_BEFORE_BOSS_GRASS_1, logic->CanCutShrubs()),
        LOCATION(RC_JABU_JABUS_BELLY_MQ_BEFORE_BOSS_GRASS_2, logic->CanCutShrubs()),
    }, {
        //Exits
        Entrance(RR_JABU_JABUS_BELLY_MQ_LIFT_ROOM_EAST_LEDGE, []{return true;}),
        Entrance(RR_JABU_JABUS_BELLY_BOSS_ENTRYWAY,           []{return Here(RR_JABU_JABUS_BELLY_MQ_EAST_ROOM, []{return logic->CanUse(RG_FAIRY_SLINGSHOT);});}),
    });

#pragma endregion

    // Boss Room
    areaTable[RR_JABU_JABUS_BELLY_BOSS_ENTRYWAY] = Region("Jabu Jabus Belly Boss Entryway", "Jabu Jabus Belly", {RA_JABU_JABUS_BELLY}, NO_DAY_NIGHT_CYCLE, {}, {}, {
        // Exits
        Entrance(RR_JABU_JABUS_BELLY_NEAR_BOSS_ROOM, []{return ctx->GetDungeon(JABU_JABUS_BELLY)->IsVanilla();}),
        Entrance(RR_JABU_JABUS_BELLY_MQ_EAST_ROOM,   []{return ctx->GetDungeon(JABU_JABUS_BELLY)->IsMQ();}),
        Entrance(RR_JABU_JABUS_BELLY_BOSS_ROOM,      []{return true;}),
    });

    areaTable[RR_JABU_JABUS_BELLY_BOSS_ROOM] = Region("Jabu Jabus Belly Boss Room", "Jabu Jabus Belly", {}, NO_DAY_NIGHT_CYCLE, {
        // Events //todo: add pot kill trick
        EventAccess(&logic->JabuJabusBellyClear, []{return logic->JabuJabusBellyClear || logic->CanKillEnemy(RE_BARINADE);}),
    }, {
        // Locations
        LOCATION(RC_JABU_JABUS_BELLY_BARINADE_POT_1, logic->CanBreakPots()),
        LOCATION(RC_JABU_JABUS_BELLY_BARINADE_POT_2, logic->CanBreakPots()),
        LOCATION(RC_JABU_JABUS_BELLY_BARINADE_POT_3, logic->CanBreakPots()),
        LOCATION(RC_JABU_JABUS_BELLY_BARINADE_POT_4, logic->CanBreakPots()),
        LOCATION(RC_JABU_JABUS_BELLY_BARINADE_POT_5, logic->CanBreakPots()),
        LOCATION(RC_JABU_JABUS_BELLY_BARINADE_POT_6, logic->CanBreakPots()),
        LOCATION(RC_JABU_JABUS_BELLY_BARINADE_HEART, logic->JabuJabusBellyClear),
        LOCATION(RC_BARINADE,                        logic->JabuJabusBellyClear),
    }, {
        // Exits
        Entrance(RR_JABU_JABUS_BELLY_BOSS_ENTRYWAY, []{return false;}),
        Entrance(RR_ZORAS_FOUNTAIN,                 []{return logic->JabuJabusBellyClear;}, false),
    });

    // clang-format on
}
