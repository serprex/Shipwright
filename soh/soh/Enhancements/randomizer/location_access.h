#pragma once

#include <string>
#include <vector>
#include <list>
#include <set>

#include "soh/Enhancements/randomizer/randomizerTypes.h"
#include "soh/Enhancements/randomizer/context.h"
#include "soh/Enhancements/randomizer/logic.h"
#include "soh/Enhancements/randomizer/dungeon.h"

typedef bool (*ConditionFn)();

// I hate this but every alternative I can think of right now is worse
extern Rando::Context* ctx;
extern std::shared_ptr<Rando::Logic> logic;

class Region;

class EventAccess {
  public:
    explicit EventAccess(bool* event_, ConditionFn condition_function_)
        : event(event_), condition_function(condition_function_) {
    }

    bool ConditionsMet() const {
        auto ctx = Rando::Context::GetInstance();
        if (ctx->GetOption(RSK_LOGIC_RULES).Is(RO_LOGIC_GLITCHLESS)) {
            return condition_function();
        }
        return true;
    }

    bool CheckConditionAtAgeTime(bool& age, bool& time) {
        logic->IsChild = false;
        logic->IsAdult = false;
        logic->AtDay = false;
        logic->AtNight = false;

        time = true;
        age = true;

        return ConditionsMet();
    }

    void EventOccurred() {
        *event = true;
    }

    bool GetEvent() const {
        return *event;
    }

  private:
    bool* event;
    ConditionFn condition_function;
};

std::string CleanCheckConditionString(std::string condition);

#define LOCATION(check, condition) \
    LocationAccess(                \
        check, [] { return condition; }, CleanCheckConditionString(#condition))

// this class is meant to hold an item location with a boolean function to determine its accessibility from a specific
// area
class LocationAccess {
  public:
    explicit LocationAccess(RandomizerCheck location_, ConditionFn condition_function_)
        : location(location_), condition_function(condition_function_), condition_str("") {
    }

    explicit LocationAccess(RandomizerCheck location_, ConditionFn condition_function_, std::string condition_str_)
        : location(location_), condition_function(condition_function_), condition_str(condition_str_) {
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

    // Makes sure shop locations are buyable
    bool CanBuy() const;
};

bool CanBuyAnother(RandomizerCheck rc);

namespace Rando {
class Entrance;
enum class EntranceType;
} // namespace Rando

class Region {
  public:
    Region();
    Region(std::string regionName_, std::string scene_, std::set<RandomizerArea> areas, bool timePass_,
           std::vector<EventAccess> events_, std::vector<LocationAccess> locations_, std::list<Rando::Entrance> exits_);
    ~Region();

    std::string regionName;
    std::string scene;
    std::set<RandomizerArea> areas;
    bool timePass;
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
    ;

    void ApplyTimePass();

    bool UpdateEvents();

    void AddExit(RandomizerRegion parentKey, RandomizerRegion newExitKey, ConditionFn condition);

    void RemoveExit(Rando::Entrance* exitToRemove);

    void SetAsPrimary(RandomizerRegion exitToBePrimary);

    Rando::Entrance* GetExit(RandomizerRegion exit);

    bool Child() const {
        return childDay || childNight;
    }

    bool Adult() const {
        return adultDay || adultNight;
    }

    bool BothAgesCheck() const {
        return Child() && Adult();
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
    bool Here(ConditionFn condition) {
        // store current age variables
        bool pastAdult = logic->IsAdult;
        bool pastChild = logic->IsChild;

        // set age access as this areas ages
        logic->IsChild = Child();
        logic->IsAdult = Adult();

        // heck condition as well as having at least child or adult access
        bool hereVal = condition() && (logic->IsAdult || logic->IsChild);

        // set back age variables
        logic->IsChild = pastChild;
        logic->IsAdult = pastAdult;

        return hereVal;
    }

    bool CanPlantBeanCheck() const;
    bool AllAccountedFor() const;

    void ResetVariables();

    void printAgeTimeAccess() const {
        auto message = "Child Day:   " + std::to_string(childDay) +
                       "\t"
                       "Child Night: " +
                       std::to_string(childNight) +
                       "\t"
                       "Adult Day:   " +
                       std::to_string(adultDay) +
                       "\t"
                       "Adult Night: " +
                       std::to_string(adultNight);
    }

    /*
     * This logic covers checks that exist in the shared areas of Spirit from a glitchless standpoint.
     * This code will fail if any glitch allows Adult to go in the Child spirit door first or vice versa as it relies on specific ages

     * There are 4 possibilities for passing a check, but first I have to talk about parallel universes.

     * In the first universe, the player enters spirit as child, and spends as many keys as they can to lock adult out
     * In the second, they enter as adult and spend as many keys as they can to lock child out.
     
     * When an Age can no longer be kept out by the other age, that age is said to have Certain Access to a region
     * If both ages have access to a region with a certain number of keys, but there is no Certain Access,
     * then a check is only in logic if both ages can collect the check independently
     
     * If an age has Certain Access then that age can collect checks alone,
     * and there is no reason to check the other age untile the universes converge.
     
     * The universes converge when the player has all the keys, giving both ages Certain Access.
     
     * We must check for these universes manually as we allow technical access with minimum keys for
     * technical reasons as otherwise the code will never run
     */

    bool SpiritShared(ConditionFn condition, ConditionFn childAccess, ConditionFn adultAccess, uint8_t adultKeys, uint8_t childKeys, uint8_t eitherKeys, bool anyAge = false){
        //If we have all of the keys, we know that access is Certain Access
        if (ctx->GetDungeon(Rando::SPIRIT_TEMPLE)->IsMQ() ? logic->SmallKeys(RR_SPIRIT_TEMPLE, 7) : logic->SmallKeys(RR_SPIRIT_TEMPLE, 5)) {
            if (anyAge) {
                return Here(condition);
            }
            return condition();
        // otherwise, we have to check the current age and...
        } else if (Child() && logic->IsChild) {
            bool result = condition();
            //if we have enough keys to have Certain Access, we just run the condition
            if (logic->SmallKeys(RR_SPIRIT_TEMPLE, childKeys)){
                return result;
            //otherwise we need to check both ages if we have enough keys that either can get there
            } else if (result && logic->SmallKeys(RR_SPIRIT_TEMPLE, eitherKeys) && adultAccess) {
                // store current age variables
                bool pastAdult = logic->IsAdult;
                bool pastChild = logic->IsChild;

                logic->IsChild = false;
                logic->IsAdult = true;

                result = condition();

                logic->IsChild = pastChild;
                logic->IsAdult = pastAdult;

                return result;
            }
        } else if (Adult() && logic->IsAdult) {
            bool result = condition();
            //if we have enough keys to have Certain Access, we just run the condition
            if (logic->SmallKeys(RR_SPIRIT_TEMPLE, adultKeys)){
                return result;
            //otherwise we need to check both ages
            } else if (result && logic->SmallKeys(RR_SPIRIT_TEMPLE, eitherKeys) && childAccess) {
                // store current age variables
                bool pastAdult = logic->IsAdult;
                bool pastChild = logic->IsChild;

                logic->IsChild = true;
                logic->IsAdult = false;

                result = condition();

                logic->IsChild = pastChild;
                logic->IsAdult = pastAdult;

                return result;
            }
        }
        return false;
    }
};

extern std::array<Region, RR_MAX> areaTable;
extern std::vector<EventAccess> grottoEvents;

bool Here(const RandomizerRegion region,
          ConditionFn
              condition); // RANDOTODO make a less stupid way to check own at either age than self referencing with this
bool SpiritSharedStatueRoom(const RandomizerRegion region, ConditionFn condition, bool anyAge = false);
bool MQSpiritSharedStatueRoom(const RandomizerRegion region, ConditionFn condition, bool anyAge = false);
bool MQSpiritSharedBrokenWallRoom(const RandomizerRegion region, ConditionFn condition, bool anyAge = false);
bool CanPlantBean(const RandomizerRegion region);
bool BothAges(const RandomizerRegion region);
bool ChildCanAccess(const RandomizerRegion region);
bool AdultCanAccess(const RandomizerRegion region);
bool HasAccessTo(const RandomizerRegion region);

#define DAY_NIGHT_CYCLE true
#define NO_DAY_NIGHT_CYCLE false

namespace Regions {
extern void AccessReset();
extern void ResetAllLocations();
extern bool HasTimePassAccess(uint8_t age);
extern void DumpWorldGraph(std::string str);
} // namespace Regions

void RegionTable_Init();
Region* RegionTable(const RandomizerRegion regionKey);
std::vector<Rando::Entrance*> GetShuffleableEntrances(Rando::EntranceType type, bool onlyPrimary = true);
Rando::Entrance* GetEntrance(const std::string name);

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
void RegionTable_Init_GerudoTrainingGround();
void RegionTable_Init_GanonsCastle();