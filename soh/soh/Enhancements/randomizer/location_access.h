#pragma once

#include <array>
#include <string>
#include <vector>
#include <list>
#include <set>

#include "soh/Enhancements/randomizer/randomizerTypes.h"
#include "soh/Enhancements/randomizer/SeedContext.h"
#include "soh/Enhancements/randomizer/logic.h"

#define TIME_PASSES true
#define TIME_DOESNT_PASS false

typedef bool (*ConditionFn)();
typedef uint16_t (*TimeFn)();
typedef uint8_t (*FairyFn)();

// I hate this but every alternative I can think of right now is worse
extern Rando::Context* ctx;
extern std::shared_ptr<Rando::Logic> logic;

class Region;

// What a path spent getting where it is
struct PathCost {
    // Seconds in hot regions since the last cool one
    uint16_t heat = 0;
    // Health units spent on purpose since the last heal
    uint16_t damage = 0;
    // Bottled fairies the path is still carrying
    uint8_t fairies = 0;

    bool Dominates(const PathCost& other) const {
        return heat <= other.heat && damage <= other.damage && fairies >= other.fairies;
    }
};

// The Pareto minimal costs a region is reachable with at one agetime. Nothing in here dominates
// anything else in here, and a non empty set means reachable.
class PathCostSet {
  public:
    // Only burning down to one health, or paying a fairy for a shortcut, ever splits a path
    static constexpr uint8_t MAX_COSTS = 4;

    bool Empty() const {
        return count == 0;
    }

    void Clear() {
        count = 0;
    }

    uint8_t Count() const {
        return count;
    }

    const PathCost& operator[](uint8_t i) const {
        return costs[i];
    }

    // Is some way in we already know at least as cheap as this one?
    bool Covers(const PathCost& cost) const {
        for (uint8_t i = 0; i < count; i++) {
            if (costs[i].Dominates(cost)) {
                return true;
            }
        }
        return false;
    }

    // Adds a cost unless something already here is at least as cheap. Returns whether the set changed.
    bool Insert(PathCost cost);

  private:
    std::array<PathCost, MAX_COSTS> costs{};
    uint8_t count = 0;
};

#define EVENT_ACCESS(event, condition) \
    EventAccess(                       \
        event, #event, [] { return condition; }, CleanConditionString(#condition))

// An event that costs `time` seconds of hazard exposure to set off
#define TIMED_EVENT_ACCESS(event, time, condition) \
    EventAccess(                                   \
        event, #event, [] { return condition; }, CleanConditionString(#condition), []() -> uint16_t { return time; })

// Somewhere the player can bottle a fairy, filling every bottle they have for logic's purposes
#define FAIRY_REFILL(condition) EventAccess([] { return condition; }, CleanConditionString(#condition))

class EventAccess {
  public:
    explicit EventAccess(LogicVal event_, std::string event_str_, ConditionFn condition_function_,
                         std::string condition_str_, TimeFn time_function_ = nullptr)
        : event(event_), event_str(event_str_), condition_function(condition_function_), condition_str(condition_str_),
          time_function(time_function_) {
    }

    // A fairy refill sets no logic value, the region it sits in refills the path instead
    explicit EventAccess(ConditionFn condition_function_, std::string condition_str_)
        : event(LOGIC_NONE), event_str("FAIRY_REFILL"), condition_function(condition_function_),
          condition_str(condition_str_), fairyRefill(true) {
    }

    uint16_t GetTimeCost() const {
        return time_function == nullptr ? 0 : time_function();
    }

    bool ConditionsMet() const {
        auto ctx = Rando::Context::GetInstance();
        if (ctx->GetOption(RSK_LOGIC_RULES).Is(RO_LOGIC_GLITCHLESS)) {
            return condition_function();
        }
        return true;
    }

    void EventOccurred() {
        logic->Set(event, true);
    }

    bool GetEvent() const {
        return logic->Get(event);
    }

    bool IsFairyRefill() const {
        return fairyRefill;
    }

    const std::string& GetEventStr() const {
        return event_str;
    }

    const std::string& GetConditionStr() const {
        return condition_str;
    }

  private:
    LogicVal event;
    std::string event_str;
    ConditionFn condition_function;
    std::string condition_str;
    // Seconds of hazard exposure setting this event off costs, on top of reaching the region
    TimeFn time_function = nullptr;
    // This is not an event at all, it marks the region as somewhere fairies can be bottled
    bool fairyRefill = false;
};

std::string CleanConditionString(std::string condition);

#define LOCATION(check, condition) \
    LocationAccess(                \
        check, [] { return condition; }, CleanConditionString(#condition))

// A check that costs `time` seconds of hazard exposure to reach from the region's arrival point
#define TIMED_LOCATION(check, time, condition) \
    LocationAccess(                            \
        check, [] { return condition; }, CleanConditionString(#condition), []() -> uint16_t { return time; })

// this class is meant to hold an item location with a boolean function to determine its accessibility from a specific
// area
class LocationAccess {
  public:
    explicit LocationAccess(RandomizerCheck location_, ConditionFn condition_function_)
        : location(location_), condition_function(condition_function_), condition_str("") {
    }

    explicit LocationAccess(RandomizerCheck location_, ConditionFn condition_function_, std::string condition_str_,
                            TimeFn time_function_ = nullptr)
        : location(location_), condition_function(condition_function_), condition_str(condition_str_),
          time_function(time_function_) {
    }

    bool GetConditionsMet() const {
        auto ctx = Rando::Context::GetInstance();
        if (ctx->GetOption(RSK_LOGIC_RULES).Is(RO_LOGIC_GLITCHLESS)) {
            return condition_function();
        }
        return true;
    }

    bool CheckConditionAtAgeTime(bool& age, bool& time) const;

    bool ConditionsMet(Region* parentRegion, bool calculatingAvailableChecks) const;

    bool CheckOnPath(const PathCost& cost, bool& age, bool& time) const;

    uint16_t GetTimeCost() const {
        return time_function == nullptr ? 0 : time_function();
    }

    RandomizerCheck GetLocation() const {
        return location;
    }

    std::string GetConditionStr() const {
        return condition_str;
    }

  protected:
    RandomizerCheck location;
    ConditionFn condition_function;
    std::string condition_str;
    // Seconds of hazard exposure getting to this check costs, on top of reaching the region
    TimeFn time_function = nullptr;
};

uint16_t GetCheckPrice(RandomizerCheck check = RC_UNKNOWN_CHECK);
uint16_t GetWalletCapacity();

namespace Rando {
class Entrance;
enum class EntranceType;
} // namespace Rando

struct SpiritLogicData {
    // the minimum number of keys that guarantees Child can reach this region
    uint8_t childKeys;
    // The minimum number of keys that guarantees Child can reach this region if they have reverse access
    uint8_t childRevKeys;
    // the minimum number of keys that guarantees Adult can reach this region
    uint8_t adultKeys;
    // the minimum number of keys that guarantees Adult can reach this region with reverse entry
    uint8_t adultRevKeys;
    // The area access condition to reach this region as Child, from the first lock,
    // including the minimum number of keys for ambiguous access
    // 1 key is always assumed to be required
    ConditionFn childAccess;
    // The area access condition to reach this region as Adult, from the first lock
    // including the minimum number of keys for ambiguous access
    // 1 key is always assumed to be required on vanilla
    ConditionFn adultAccess;
    // The area access condition to reach this region from the boss door,
    ConditionFn reverseAccess;
};

// Rooms are numbered from 0, so this stands in for "no room given"
#define ROOM_NONE 0xFF

// An access bool the search was seeded with has no costs behind it, which means arriving fresh
void SeedPathCost(bool access, PathCostSet& costs);

class Region {
  public:
    Region();
    Region(std::string regionName_, SceneID scene_, bool timePass, std::set<RandomizerArea> areas,
           std::vector<EventAccess> events_, std::vector<LocationAccess> locations_, std::list<Rando::Entrance> exits_);
    Region(std::string regionName_, SceneID scene_, std::vector<EventAccess> events_,
           std::vector<LocationAccess> locations_, std::list<Rando::Entrance> exits_);
    Region(std::string regionName_, SceneID scene_, uint8_t room_, std::vector<EventAccess> events_,
           std::vector<LocationAccess> locations_, std::list<Rando::Entrance> exits_);
    ~Region();

    std::string regionName;
    SceneID scene;
    bool timePass;
    std::set<RandomizerArea> areas;
    std::vector<EventAccess> events;
    std::vector<LocationAccess> locations;
    std::list<Rando::Entrance> exits;
    std::list<Rando::Entrance*> entrances;
    //^ The above exits are now stored in a list instead of a vector because
    // the entrance randomization algorithm plays around with pointers to these
    // entrances a lot. By putting the entrances in a list, we don't have to
    // worry about a vector potentially reallocating itself and invalidating all our
    // entrance pointers.

    bool childDay = false;
    bool childNight = false;
    bool adultDay = false;
    bool adultNight = false;
    bool addedToPool = false;

    // Which room of the scene this region sits in, for the hot room lookup
    uint8_t room = ROOM_NONE;
    // The hot room timer runs here, so getting here does not clear the heat spent so far
    bool hot = false;
    // There is a fire here the player can stand in to grind down to a sixteenth of a heart
    bool canBurnToOne = false;
    // Being here heals, which puts back any health the path spent
    bool heals = false;
    // The heal here is a Great Fairy, so it only happens with Zelda's Lullaby
    bool healNeedsLullaby = false;
    // A fairy can be bottled here, so the path leaves with full bottles
    bool fairyRefill = false;
    // What the cheapest ways in cost, per agetime. An access bool set without any costs behind it
    // means the search was seeded here, which costs nothing.
    PathCostSet childDayCosts;
    PathCostSet childNightCosts;
    PathCostSet adultDayCosts;
    PathCostSet adultNightCosts;

    RandomizerRegion randomizerRegionKey = RR_NONE;

    bool TimePass();

    // Does the path get its health back here? A Great Fairy wants Zelda's Lullaby first
    bool CanHeal() const;

    // Can the path bottle a fairy here, filling every bottle it has?
    bool CanRefillFairies() const;

    void ApplyTimePass();

    bool UpdateEvents();

    void AddExit(RandomizerRegion parentKey, RandomizerRegion newExitKey, ConditionFn condition,
                 std::string conditionStr);

    void SetFairyRefill();

    void RemoveExit(Rando::Entrance* exitToRemove);

    void SetAsPrimary(RandomizerRegion exitToBePrimary);

    Rando::Entrance* GetExit(RandomizerRegion exit);

    bool Child() const {
        return childDay || childNight;
    }

    bool Adult() const {
        return adultDay || adultNight;
    }

    bool HasAccess() const {
        return Child() || Adult();
    }

    bool AllAccess() const {
        return childDay && childNight && adultDay && adultNight;
    }

    // Check to see if an exit can be access as both ages at both times of day
    bool CheckAllAccess(RandomizerRegion exitKey);

    std::set<RandomizerArea> GetAllAreas() const {
        return areas;
    }

    RandomizerArea GetFirstArea() const {
        if (areas.empty()) {
            assert(false);
            return RA_NONE;
        } else {
            return *areas.begin();
        }
    }

    void ReplaceAreas(std::set<RandomizerArea> newAreas) {
        areas = newAreas;
    }

    // Here checks conditional access based on whether or not both ages have
    // access to this area. For example: if there are rocks that block a path
    // which both child and adult can access, adult having hammer can give
    // both child and adult access to the path.
    bool AnyAgeTime(ConditionFn condition) const {
        // store current age variables
        bool pastAdult = logic->IsAdult;
        bool pastChild = logic->IsChild;

        // set age access as this areas ages
        logic->IsChild = Child();
        logic->IsAdult = Adult();

        // check condition as well as having at least child or adult access
        bool hereVal = condition() && (logic->IsAdult || logic->IsChild);

        // set back age variables
        logic->IsChild = pastChild;
        logic->IsAdult = pastAdult;

        return hereVal;
    }

    bool AllAccountedFor() const;

    void ResetVariables();

    void printAgeTimeAccess();
    static std::map<RandomizerRegion, SpiritLogicData> spiritLogicData;
};

extern std::array<Region, RR_MAX> areaTable;
extern std::vector<EventAccess> grottoEvents;

bool AnyAgeTime(ConditionFn condition);
bool SpiritShared(
    RandomizerRegion region, ConditionFn condition, bool anyAge = false, RandomizerRegion otherRegion = RR_NONE,
    ConditionFn otherCondition = [] { return false; }, RandomizerRegion thirdRegion = RR_NONE,
    ConditionFn thirdCondition = [] { return false; });
bool SpiritCertainAccess(RandomizerRegion region);
bool CanPlantBean(RandomizerGet bean);

namespace Regions {
extern void AccessReset();
extern void ResetAllLocations();
extern bool HasTimePassAccess(uint8_t age);
extern void DumpWorldGraph(std::string str);
} // namespace Regions

void RegionTable_Init();
Region* RegionTable(const RandomizerRegion regionKey);
std::vector<Rando::Entrance*> GetShuffleableEntrances(Rando::EntranceType type, bool onlyPrimary = true);
Rando::Entrance* GetEntrance(RandomizerRegion source, RandomizerRegion destination);

void RegionTable_Init_Root();
// Overworld
void RegionTable_Init_KokiriForest();
void RegionTable_Init_LostWoods();
void RegionTable_Init_SacredForestMeadow();
void RegionTable_Init_HyruleField();
void RegionTable_Init_LakeHylia();
void RegionTable_Init_LonLonRanch();
void RegionTable_Init_Market();
void RegionTable_Init_TempleOfTime();
void RegionTable_Init_CastleGrounds();
void RegionTable_Init_Kakariko();
void RegionTable_Init_Graveyard();
void RegionTable_Init_DeathMountainTrail();
void RegionTable_Init_GoronCity();
void RegionTable_Init_DeathMountainCrater();
void RegionTable_Init_ZoraRiver();
void RegionTable_Init_ZorasDomain();
void RegionTable_Init_ZorasFountain();
void RegionTable_Init_GerudoValley();
void RegionTable_Init_GerudoFortress();
void RegionTable_Init_HauntedWasteland();
void RegionTable_Init_DesertColossus();
// Dungeons
void RegionTable_Init_DekuTree();
void RegionTable_Init_DodongosCavern();
void RegionTable_Init_JabuJabusBelly();
void RegionTable_Init_ForestTemple();
void RegionTable_Init_FireTemple();
void RegionTable_Init_WaterTemple();
void RegionTable_Init_SpiritTemple();
void RegionTable_Init_ShadowTemple();
void RegionTable_Init_BottomOfTheWell();
void RegionTable_Init_IceCavern();
void RegionTable_Init_ThievesHideout();
void RegionTable_Init_GerudoTrainingGround();
void RegionTable_Init_GanonsCastle();