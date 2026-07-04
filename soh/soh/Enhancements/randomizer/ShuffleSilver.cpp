#include <soh/OTRGlobals.h>
#include "dungeon.h"
#include "SeedContext.h"
#include "draw.h"
#include "static_data.h"
#include "randomizer.h"// IWYU pragma: keep
#include "ShuffleSilver.h"


extern "C" {
#include "overlays/actors/ovl_En_G_Switch/z_en_g_switch.h"
extern PlayState* gPlayState;
extern SaveContext gSaveContext;
}

extern void EnItem00_DrawRandomizedItem(EnItem00* enItem00, PlayState* play);

bool IsSilverInPool(RandomizerGet rg){
    auto ctx = Rando::Context::GetInstance();
    switch (rg) {
        case RG_SHADOW_SILVER_BLADES:
        case RG_SHADOW_SILVER_PIT:
        case RG_SHADOW_SILVER_SPIKES:
        case RG_GTG_SILVER_SLOPE:
        case RG_GTG_SILVER_LAVA:
        case RG_GTG_SILVER_WATER:
        case RG_GANONS_CASTLE_SILVER_FIRE:
            return true;
        case RG_SPIRIT_SILVER_CHILD:
        case RG_SPIRIT_SILVER_SUN:
        case RG_SPIRIT_SILVER_BOULDERS:
            return ctx->GetDungeon(Rando::SPIRIT_TEMPLE)->IsVanilla();
        case RG_BOTW_SILVER:
            return ctx->GetDungeon(Rando::BOTTOM_OF_THE_WELL)->IsVanilla();
        case RG_ICE_CAVERN_SILVER_BLADES:
        case RG_ICE_CAVERN_SILVER_BLOCK:
            return ctx->GetDungeon(Rando::ICE_CAVERN)->IsVanilla();
        case RG_GANONS_CASTLE_SILVER_LIGHT:
        case RG_GANONS_CASTLE_SILVER_FOREST:
        case RG_GANONS_CASTLE_SILVER_SPIRIT:
            return ctx->GetDungeon(Rando::GANONS_CASTLE)->IsVanilla();
        case RG_DODONGOS_CAVERN_MQ_SILVER:
            return ctx->GetDungeon(Rando::DODONGOS_CAVERN)->IsMQ();
        case RG_SHADOW_MQ_SILVER_INVISIBLE_BLADES:
            return ctx->GetDungeon(Rando::SHADOW_TEMPLE)->IsMQ();
        case RG_SPIRIT_MQ_SILVER_LOBBY:
        case RG_SPIRIT_MQ_SILVER_BIG_WALL:
            return ctx->GetDungeon(Rando::SPIRIT_TEMPLE)->IsMQ();
        case RG_GANONS_CASTLE_MQ_SILVER_WATER:
        case RG_GANONS_CASTLE_MQ_SILVER_SHADOW:
            return ctx->GetDungeon(Rando::GANONS_CASTLE)->IsMQ();
        default:
            assert(false);
            return false;
    }
}

std::unordered_map<RandomizerGet, RandomizerCheckArea> Rando::StaticData::silverToArea = {
    { RG_DODONGOS_CAVERN_MQ_SILVER, RCAREA_DODONGOS_CAVERN },
    { RG_SPIRIT_SILVER_CHILD, RCAREA_SPIRIT_TEMPLE },
    { RG_SPIRIT_SILVER_SUN, RCAREA_SPIRIT_TEMPLE },
    { RG_SPIRIT_SILVER_BOULDERS, RCAREA_SPIRIT_TEMPLE },
    { RG_SPIRIT_MQ_SILVER_LOBBY, RCAREA_SPIRIT_TEMPLE },
    { RG_SPIRIT_MQ_SILVER_BIG_WALL, RCAREA_SPIRIT_TEMPLE },
    { RG_SHADOW_SILVER_BLADES, RCAREA_SHADOW_TEMPLE },
    { RG_SHADOW_SILVER_PIT, RCAREA_SHADOW_TEMPLE },
    { RG_SHADOW_SILVER_SPIKES, RCAREA_SHADOW_TEMPLE },
    { RG_SHADOW_MQ_SILVER_INVISIBLE_BLADES, RCAREA_SHADOW_TEMPLE },
    { RG_GANONS_CASTLE_SILVER_LIGHT, RCAREA_GANONS_CASTLE},
    { RG_GANONS_CASTLE_SILVER_FOREST, RCAREA_GANONS_CASTLE },
    { RG_GANONS_CASTLE_SILVER_FIRE, RCAREA_GANONS_CASTLE },
    { RG_GANONS_CASTLE_SILVER_SPIRIT, RCAREA_GANONS_CASTLE },
    { RG_GANONS_CASTLE_MQ_SILVER_WATER, RCAREA_GANONS_CASTLE },
    { RG_GANONS_CASTLE_MQ_SILVER_SHADOW, RCAREA_GANONS_CASTLE },
    { RG_ICE_CAVERN_SILVER_BLADES, RCAREA_ICE_CAVERN },
    { RG_ICE_CAVERN_SILVER_BLOCK, RCAREA_ICE_CAVERN },
    { RG_BOTW_SILVER, RCAREA_BOTTOM_OF_THE_WELL },
    { RG_GTG_SILVER_SLOPE, RCAREA_GERUDO_TRAINING_GROUND },
    { RG_GTG_SILVER_LAVA, RCAREA_GERUDO_TRAINING_GROUND },
    { RG_GTG_SILVER_WATER, RCAREA_GERUDO_TRAINING_GROUND }
};

RandomizerGet SilverFromSwitchFlag(s16 switchFlag){
    bool isMQ = Rando::Context::GetInstance()->GetDungeonFromScene((SceneID)gPlayState->sceneNum)->IsMQ();
    switch (gPlayState->sceneNum) {
        case SCENE_DODONGOS_CAVERN:
            return RG_DODONGOS_CAVERN_MQ_SILVER;
        case SCENE_SHADOW_TEMPLE:
            switch (switchFlag) {
                case 1:
                    return RG_SHADOW_SILVER_BLADES;
                case 3:
                    return RG_SHADOW_MQ_SILVER_INVISIBLE_BLADES;
                case 8:
                    return RG_SHADOW_SILVER_SPIKES;
                case 9:
                    return RG_SHADOW_SILVER_PIT;
                case 17:
                    return RG_SHADOW_SILVER_PIT;
            }
            break;
        case SCENE_SPIRIT_TEMPLE:
            switch (switchFlag) {
                case 0:
                    return RG_SPIRIT_MQ_SILVER_BIG_WALL;
                case 2:
                    return RG_SPIRIT_SILVER_BOULDERS;
                case 5:
                    return RG_SPIRIT_SILVER_CHILD;
                case 10:
                    return RG_SPIRIT_SILVER_SUN;
                case 55: //Likely error
                    return RG_SPIRIT_MQ_SILVER_LOBBY;
            }
            break;
        case SCENE_BOTTOM_OF_THE_WELL:
            return RG_BOTW_SILVER;
        case SCENE_ICE_CAVERN:
            switch (switchFlag) {
                case 8:
                    return RG_ICE_CAVERN_SILVER_BLOCK;
                case 31:
                    return RG_ICE_CAVERN_SILVER_BLADES;
            }
            break;
        case SCENE_GERUDO_TRAINING_GROUND:
            switch (switchFlag) {
                case 12:
                    return RG_GTG_SILVER_LAVA;
                case 27:
                    return RG_GTG_SILVER_WATER;
                case 28:
                    return RG_GTG_SILVER_SLOPE;
            }
            break;
        case SCENE_INSIDE_GANONS_CASTLE:
            switch (switchFlag) {
                case 1:
                    return RG_GANONS_CASTLE_SILVER_FIRE;
                case 2:
                    return RG_GANONS_CASTLE_MQ_SILVER_WATER;
                case 9:
                    return RG_GANONS_CASTLE_SILVER_FIRE;
                case 11:
                    return isMQ ? RG_GANONS_CASTLE_MQ_SILVER_SHADOW
                                : RG_GANONS_CASTLE_SILVER_SPIRIT;
                case 14:
                    return RG_GANONS_CASTLE_SILVER_FOREST;
                case 18:
                    return RG_GANONS_CASTLE_SILVER_LIGHT;
            }
            break;
        assert(false); //no matching silver found
        return RG_NONE;
    }
}

s8* Randomizer::SilverFieldFromSaveContext(SaveContext* saveContext, RandomizerGet rg) {
    switch (rg) {
        case RG_SHADOW_SILVER_BLADES:
            return &saveContext->ship.quest.data.randomizer.silverShadowBlades;
        case RG_SHADOW_SILVER_PIT:
            return &saveContext->ship.quest.data.randomizer.silverShadowPit;
        case RG_SHADOW_SILVER_SPIKES:
            return &saveContext->ship.quest.data.randomizer.silverShadowSpikes;
        case RG_SPIRIT_SILVER_CHILD:
            return &saveContext->ship.quest.data.randomizer.silverSpiritChild;
        case RG_SPIRIT_SILVER_SUN:
            return &saveContext->ship.quest.data.randomizer.silverSpiritSun;
        case RG_SPIRIT_SILVER_BOULDERS:
            return &saveContext->ship.quest.data.randomizer.silverSpiritBoulders;
        case RG_BOTW_SILVER:
            return &saveContext->ship.quest.data.randomizer.silverBotw;
        case RG_ICE_CAVERN_SILVER_BLADES:
            return &saveContext->ship.quest.data.randomizer.silverIceCavernBlades;
        case RG_ICE_CAVERN_SILVER_BLOCK:
            return &saveContext->ship.quest.data.randomizer.silverIceCavernBlock;
        case RG_GTG_SILVER_SLOPE:
            return &saveContext->ship.quest.data.randomizer.silverGtgSlope;
        case RG_GTG_SILVER_LAVA:
            return &saveContext->ship.quest.data.randomizer.silverGtgLava;
        case RG_GTG_SILVER_WATER:
            return &saveContext->ship.quest.data.randomizer.silverGtgWater;
        case RG_GANONS_CASTLE_SILVER_LIGHT:
            return &saveContext->ship.quest.data.randomizer.silverGanonLight;
        case RG_GANONS_CASTLE_SILVER_FOREST:
            return &saveContext->ship.quest.data.randomizer.silverGanonForest;
        case RG_GANONS_CASTLE_SILVER_FIRE:
            return &saveContext->ship.quest.data.randomizer.silverGanonFire;
        case RG_GANONS_CASTLE_SILVER_SPIRIT:
            return &saveContext->ship.quest.data.randomizer.silverGanonSpirit;
        case RG_DODONGOS_CAVERN_MQ_SILVER:
            return &saveContext->ship.quest.data.randomizer.silverMqDodongosCavern;
        case RG_SHADOW_MQ_SILVER_INVISIBLE_BLADES:
            return &saveContext->ship.quest.data.randomizer.silverMqShadowInvisibleBlades;
        case RG_SPIRIT_MQ_SILVER_LOBBY:
            return &saveContext->ship.quest.data.randomizer.silverMqSpiritLobby;
        case RG_SPIRIT_MQ_SILVER_BIG_WALL:
            return &saveContext->ship.quest.data.randomizer.silverMqSpiritBigWall;
        case RG_GANONS_CASTLE_MQ_SILVER_WATER:
            return &saveContext->ship.quest.data.randomizer.silverMqGanonWater;
        case RG_GANONS_CASTLE_MQ_SILVER_SHADOW:
            return &saveContext->ship.quest.data.randomizer.silverMqGanonShadow;
        default:
            return nullptr;
    }
}

s8 SilverTotal(RandomizerGet rg) {
    auto ctx = Rando::Context::GetInstance();
    return rg == RG_SHADOW_MQ_SILVER_INVISIBLE_BLADES ||
           (rg == RG_SHADOW_SILVER_SPIKES && ctx->GetDungeon(Rando::SHADOW_TEMPLE)->IsMQ()) ? 10
           : (rg == RG_GTG_SILVER_LAVA && ctx->GetDungeon(Rando::GERUDO_TRAINING_GROUND)->IsMQ())  ? 6
           : (rg == RG_GTG_SILVER_WATER  && ctx->GetDungeon(Rando::GERUDO_TRAINING_GROUND)->IsMQ())  ? 3
                                                                                          : 5;
}

bool IsSilverCleared(s16 switchFlag) {
    RandomizerGet rg = SilverFromSwitchFlag(switchFlag);
    return *Randomizer::SilverFieldFromSaveContext(&gSaveContext, rg) >= SilverTotal(rg);
}

bool IsSilverCleared(RandomizerGet rg) {
    return *Randomizer::SilverFieldFromSaveContext(&gSaveContext, rg) >= SilverTotal(rg);
}

bool IsSilver(RandomizerGet rg){
    return rg >= RG_SHADOW_SILVER_BLADES && rg <= RG_GANONS_CASTLE_MQ_SILVER_SHADOW;
}

extern "C" void EnGSwitch_RandomizerDraw(Actor* thisx, PlayState* play) {
    EnGSwitch* silver = reinterpret_cast<EnGSwitch*>(thisx);
    Matrix_Push();
    Matrix_Scale(17.5f, 17.5f, 17.5f, MTXMODE_APPLY);
    if (silver->type == ENGSWITCH_SILVER_RUPEE) {
        if (CVarGetInteger(CVAR_RANDOMIZER_ENHANCEMENT("MysteriousShuffle"), 0)) {
            GetItemEntry_Draw(play, GET_ITEM_MYSTERY);
        } else {
            auto silverIdentity =
                OTRGlobals::Instance->gRandomizer->IdentifySilver(gPlayState->sceneNum, silver->actor.world.pos);
            auto itemEntry =
                Rando::Context::GetInstance()->GetFinalGIEntry(silverIdentity.randomizerCheck, true, GI_NONE);
            GetItemEntry_Draw(play, itemEntry);
        }
        Matrix_Pop();
    }
}

void RegisterShuffleSilver() {
    bool shouldRegister = IS_RANDO && RAND_GET_OPTION(RSK_SHUFFLE_SILVER);

    COND_VB_SHOULD(VB_SILVER_COLLECT, shouldRegister, {
        if (*should) {
            EnGSwitch* silver = va_arg(args, EnGSwitch*);
            auto silverIdentity =
                OTRGlobals::Instance->gRandomizer->IdentifySilver(gPlayState->sceneNum, silver->actor.world.pos);
            Flags_SetRandomizerInf(silverIdentity.randomizerInf);
            Actor_Kill(&silver->actor);
            *should = false;
        }
    });

    COND_VB_SHOULD(VB_SILVER_COUNT_CHECK, shouldRegister, {
        EnGSwitch* silver = va_arg(args, EnGSwitch*);
        *should = false;
        if (IsSilverCleared(silver->switchFlag)) {
            Flags_SetSwitch(gPlayState, silver->switchFlag);
            Actor_Kill(&silver->actor);
        }
    });

    COND_VB_SHOULD(VB_SILVER_DESPAWN, shouldRegister, {
        EnGSwitch* silver = va_arg(args, EnGSwitch*);
        if (silver->type == ENGSWITCH_SILVER_RUPEE) {
            auto silverIdentity =
                OTRGlobals::Instance->gRandomizer->IdentifySilver(gPlayState->sceneNum, silver->actor.world.pos);
            *should = silverIdentity.randomizerCheck == RC_UNKNOWN_CHECK ||
                      Flags_GetRandomizerInf(silverIdentity.randomizerInf);
            if (!*should) {
                *should = false;
                silver->actor.draw = EnGSwitch_RandomizerDraw;
            }
        } else if (silver->type == ENGSWITCH_SILVER_TRACKER && IsSilverCleared(silver->switchFlag)) {
            Flags_SetSwitch(gPlayState, silver->switchFlag);
            *should = true;
        }
    });
}

void Rando::StaticData::RegisterSilverLocations() {
    static bool registered = false;
    if (registered)
        return;
    registered = true;
    // clang-format off
    locationTable[RC_SHADOW_SILVER_BLADES_1] =               Location::Collectable(RC_SHADOW_SILVER_BLADES_1,               RCQUEST_VANILLA,    RCTYPE_SILVER, ACTOR_EN_G_SWITCH, SCENE_SHADOW_TEMPLE,                TWO_ACTOR_PARAMS(3243, -1061),     "RC_SHADOW_SILVER_BLADES_1",               RHT_SHADOW_TEMPLE_SILVER,                                RG_BLUE_RUPEE,        SpoilerCollectionCheck::RandomizerInf(RAND_INF_SHADOW_SILVER_BLADES_1));
    locationTable[RC_SHADOW_SILVER_BLADES_2] =               Location::Collectable(RC_SHADOW_SILVER_BLADES_2,               RCQUEST_VANILLA,    RCTYPE_SILVER, ACTOR_EN_G_SWITCH, SCENE_SHADOW_TEMPLE,                TWO_ACTOR_PARAMS(3007, -1222),     "RC_SHADOW_SILVER_BLADES_2",               RHT_SHADOW_TEMPLE_SILVER,                                RG_BLUE_RUPEE,        SpoilerCollectionCheck::RandomizerInf(RAND_INF_SHADOW_SILVER_BLADES_2));
    locationTable[RC_SHADOW_SILVER_BLADES_3] =               Location::Collectable(RC_SHADOW_SILVER_BLADES_3,               RCQUEST_VANILLA,    RCTYPE_SILVER, ACTOR_EN_G_SWITCH, SCENE_SHADOW_TEMPLE,                TWO_ACTOR_PARAMS(3554, -1432),     "RC_SHADOW_SILVER_BLADES_3",               RHT_SHADOW_TEMPLE_SILVER,                                RG_BLUE_RUPEE,        SpoilerCollectionCheck::RandomizerInf(RAND_INF_SHADOW_SILVER_BLADES_3));
    locationTable[RC_SHADOW_SILVER_BLADES_4] =               Location::Collectable(RC_SHADOW_SILVER_BLADES_4,               RCQUEST_VANILLA,    RCTYPE_SILVER, ACTOR_EN_G_SWITCH, SCENE_SHADOW_TEMPLE,                TWO_ACTOR_PARAMS(2869, -948),      "RC_SHADOW_SILVER_BLADES_4",               RHT_SHADOW_TEMPLE_SILVER,                                RG_BLUE_RUPEE,        SpoilerCollectionCheck::RandomizerInf(RAND_INF_SHADOW_SILVER_BLADES_4));
    locationTable[RC_SHADOW_SILVER_BLADES_5] =               Location::Collectable(RC_SHADOW_SILVER_BLADES_5,               RCQUEST_VANILLA,    RCTYPE_SILVER, ACTOR_EN_G_SWITCH, SCENE_SHADOW_TEMPLE,                TWO_ACTOR_PARAMS(3399, -838),      "RC_SHADOW_SILVER_BLADES_5",               RHT_SHADOW_TEMPLE_SILVER,                                RG_BLUE_RUPEE,        SpoilerCollectionCheck::RandomizerInf(RAND_INF_SHADOW_SILVER_BLADES_5));
    locationTable[RC_SHADOW_SILVER_PIT_1] =                  Location::Collectable(RC_SHADOW_SILVER_PIT_1,                  RCQUEST_VANILLA,    RCTYPE_SILVER, ACTOR_EN_G_SWITCH, SCENE_SHADOW_TEMPLE,                TWO_ACTOR_PARAMS(2131, 3030),      "RC_SHADOW_SILVER_PIT_1",                  RHT_SHADOW_TEMPLE_SILVER,                                RG_BLUE_RUPEE,        SpoilerCollectionCheck::RandomizerInf(RAND_INF_SHADOW_SILVER_PIT_1));
    locationTable[RC_SHADOW_SILVER_PIT_2] =                  Location::Collectable(RC_SHADOW_SILVER_PIT_2,                  RCQUEST_VANILLA,    RCTYPE_SILVER, ACTOR_EN_G_SWITCH, SCENE_SHADOW_TEMPLE,                TWO_ACTOR_PARAMS(2115, 3738),      "RC_SHADOW_SILVER_PIT_2",                  RHT_SHADOW_TEMPLE_SILVER,                                RG_BLUE_RUPEE,        SpoilerCollectionCheck::RandomizerInf(RAND_INF_SHADOW_SILVER_PIT_2));
    locationTable[RC_SHADOW_SILVER_PIT_3] =                  Location::Collectable(RC_SHADOW_SILVER_PIT_3,                  RCQUEST_VANILLA,    RCTYPE_SILVER, ACTOR_EN_G_SWITCH, SCENE_SHADOW_TEMPLE,                TWO_ACTOR_PARAMS(2110, 3368),      "RC_SHADOW_SILVER_PIT_3",                  RHT_SHADOW_TEMPLE_SILVER,                                RG_BLUE_RUPEE,        SpoilerCollectionCheck::RandomizerInf(RAND_INF_SHADOW_SILVER_PIT_3));
    locationTable[RC_SHADOW_SILVER_PIT_4] =                  Location::Collectable(RC_SHADOW_SILVER_PIT_4,                  RCQUEST_VANILLA,    RCTYPE_SILVER, ACTOR_EN_G_SWITCH, SCENE_SHADOW_TEMPLE,                TWO_ACTOR_PARAMS(2243, 3361),      "RC_SHADOW_SILVER_PIT_4",                  RHT_SHADOW_TEMPLE_SILVER,                                RG_BLUE_RUPEE,        SpoilerCollectionCheck::RandomizerInf(RAND_INF_SHADOW_SILVER_PIT_4));
    locationTable[RC_SHADOW_SILVER_PIT_5] =                  Location::Collectable(RC_SHADOW_SILVER_PIT_5,                  RCQUEST_VANILLA,    RCTYPE_SILVER, ACTOR_EN_G_SWITCH, SCENE_SHADOW_TEMPLE,                TWO_ACTOR_PARAMS(1998, 3358),      "RC_SHADOW_SILVER_PIT_5",                  RHT_SHADOW_TEMPLE_SILVER,                                RG_BLUE_RUPEE,        SpoilerCollectionCheck::RandomizerInf(RAND_INF_SHADOW_SILVER_PIT_5));
    locationTable[RC_SHADOW_SILVER_SPIKES_1] =               Location::Collectable(RC_SHADOW_SILVER_SPIKES_1,               RCQUEST_VANILLA,    RCTYPE_SILVER, ACTOR_EN_G_SWITCH, SCENE_SHADOW_TEMPLE,                TWO_ACTOR_PARAMS(2042, 849),       "RC_SHADOW_SILVER_SPIKES_1",               RHT_SHADOW_TEMPLE_SILVER,                                RG_BLUE_RUPEE,        SpoilerCollectionCheck::RandomizerInf(RAND_INF_SHADOW_SILVER_SPIKES_1));
    locationTable[RC_SHADOW_SILVER_SPIKES_2] =               Location::Collectable(RC_SHADOW_SILVER_SPIKES_2,               RCQUEST_VANILLA,    RCTYPE_SILVER, ACTOR_EN_G_SWITCH, SCENE_SHADOW_TEMPLE,                TWO_ACTOR_PARAMS(2940, 1069),      "RC_SHADOW_SILVER_SPIKES_2",               RHT_SHADOW_TEMPLE_SILVER,                                RG_BLUE_RUPEE,        SpoilerCollectionCheck::RandomizerInf(RAND_INF_SHADOW_SILVER_SPIKES_2));
    locationTable[RC_SHADOW_SILVER_SPIKES_3] =               Location::Collectable(RC_SHADOW_SILVER_SPIKES_3,               RCQUEST_VANILLA,    RCTYPE_SILVER, ACTOR_EN_G_SWITCH, SCENE_SHADOW_TEMPLE,                TWO_ACTOR_PARAMS(2478, 1208),      "RC_SHADOW_SILVER_SPIKES_3",               RHT_SHADOW_TEMPLE_SILVER,                                RG_BLUE_RUPEE,        SpoilerCollectionCheck::RandomizerInf(RAND_INF_SHADOW_SILVER_SPIKES_3));
    locationTable[RC_SHADOW_SILVER_SPIKES_4] =               Location::Collectable(RC_SHADOW_SILVER_SPIKES_4,               RCQUEST_VANILLA,    RCTYPE_SILVER, ACTOR_EN_G_SWITCH, SCENE_SHADOW_TEMPLE,                TWO_ACTOR_PARAMS(2135, 1297),      "RC_SHADOW_SILVER_SPIKES_4",               RHT_SHADOW_TEMPLE_SILVER,                                RG_BLUE_RUPEE,        SpoilerCollectionCheck::RandomizerInf(RAND_INF_SHADOW_SILVER_SPIKES_4));
    locationTable[RC_SHADOW_SILVER_SPIKES_5] =               Location::Collectable(RC_SHADOW_SILVER_SPIKES_5,               RCQUEST_VANILLA,    RCTYPE_SILVER, ACTOR_EN_G_SWITCH, SCENE_SHADOW_TEMPLE,                TWO_ACTOR_PARAMS(2254, 988),       "RC_SHADOW_SILVER_SPIKES_5",               RHT_SHADOW_TEMPLE_SILVER,                                RG_BLUE_RUPEE,        SpoilerCollectionCheck::RandomizerInf(RAND_INF_SHADOW_SILVER_SPIKES_5));
    locationTable[RC_SPIRIT_SILVER_CHILD_1] =                Location::Collectable(RC_SPIRIT_SILVER_CHILD_1,                RCQUEST_VANILLA,    RCTYPE_SILVER, ACTOR_EN_G_SWITCH, SCENE_SPIRIT_TEMPLE,                TWO_ACTOR_PARAMS(-766, -1075),     "RC_SPIRIT_SILVER_CHILD_1",                RHT_SPIRIT_TEMPLE_SILVER,                                RG_BLUE_RUPEE,        SpoilerCollectionCheck::RandomizerInf(RAND_INF_SPIRIT_SILVER_CHILD_1));
    locationTable[RC_SPIRIT_SILVER_CHILD_2] =                Location::Collectable(RC_SPIRIT_SILVER_CHILD_2,                RCQUEST_VANILLA,    RCTYPE_SILVER, ACTOR_EN_G_SWITCH, SCENE_SPIRIT_TEMPLE,                TWO_ACTOR_PARAMS(-672, -1075),     "RC_SPIRIT_SILVER_CHILD_2",                RHT_SPIRIT_TEMPLE_SILVER,                                RG_BLUE_RUPEE,        SpoilerCollectionCheck::RandomizerInf(RAND_INF_SPIRIT_SILVER_CHILD_2));
    locationTable[RC_SPIRIT_SILVER_CHILD_3] =                Location::Collectable(RC_SPIRIT_SILVER_CHILD_3,                RCQUEST_VANILLA,    RCTYPE_SILVER, ACTOR_EN_G_SWITCH, SCENE_SPIRIT_TEMPLE,                TWO_ACTOR_PARAMS(-511, -1075),     "RC_SPIRIT_SILVER_CHILD_3",                RHT_SPIRIT_TEMPLE_SILVER,                                RG_BLUE_RUPEE,        SpoilerCollectionCheck::RandomizerInf(RAND_INF_SPIRIT_SILVER_CHILD_3));
    locationTable[RC_SPIRIT_SILVER_CHILD_4] =                Location::Collectable(RC_SPIRIT_SILVER_CHILD_4,                RCQUEST_VANILLA,    RCTYPE_SILVER, ACTOR_EN_G_SWITCH, SCENE_SPIRIT_TEMPLE,                TWO_ACTOR_PARAMS(-347, -1075),     "RC_SPIRIT_SILVER_CHILD_4",                RHT_SPIRIT_TEMPLE_SILVER,                                RG_BLUE_RUPEE,        SpoilerCollectionCheck::RandomizerInf(RAND_INF_SPIRIT_SILVER_CHILD_4));
    locationTable[RC_SPIRIT_SILVER_CHILD_5] =                Location::Collectable(RC_SPIRIT_SILVER_CHILD_5,                RCQUEST_VANILLA,    RCTYPE_SILVER, ACTOR_EN_G_SWITCH, SCENE_SPIRIT_TEMPLE,                TWO_ACTOR_PARAMS(-335, -1409),     "RC_SPIRIT_SILVER_CHILD_5",                RHT_SPIRIT_TEMPLE_SILVER,                                RG_BLUE_RUPEE,        SpoilerCollectionCheck::RandomizerInf(RAND_INF_SPIRIT_SILVER_CHILD_5));
    locationTable[RC_SPIRIT_SILVER_SUN_1] =                  Location::Collectable(RC_SPIRIT_SILVER_SUN_1,                  RCQUEST_VANILLA,    RCTYPE_SILVER, ACTOR_EN_G_SWITCH, SCENE_SPIRIT_TEMPLE,                TWO_ACTOR_PARAMS(-1836, -446),     "RC_SPIRIT_SILVER_SUN_1",                  RHT_SPIRIT_TEMPLE_SILVER,                                RG_BLUE_RUPEE,        SpoilerCollectionCheck::RandomizerInf(RAND_INF_SPIRIT_SILVER_SUN_1));
    locationTable[RC_SPIRIT_SILVER_SUN_2] =                  Location::Collectable(RC_SPIRIT_SILVER_SUN_2,                  RCQUEST_VANILLA,    RCTYPE_SILVER, ACTOR_EN_G_SWITCH, SCENE_SPIRIT_TEMPLE,                TWO_ACTOR_PARAMS(-1433, -283),     "RC_SPIRIT_SILVER_SUN_2",                  RHT_SPIRIT_TEMPLE_SILVER,                                RG_BLUE_RUPEE,        SpoilerCollectionCheck::RandomizerInf(RAND_INF_SPIRIT_SILVER_SUN_2));
    locationTable[RC_SPIRIT_SILVER_SUN_3] =                  Location::Collectable(RC_SPIRIT_SILVER_SUN_3,                  RCQUEST_VANILLA,    RCTYPE_SILVER, ACTOR_EN_G_SWITCH, SCENE_SPIRIT_TEMPLE,                TWO_ACTOR_PARAMS(-1275, -247),     "RC_SPIRIT_SILVER_SUN_3",                  RHT_SPIRIT_TEMPLE_SILVER,                                RG_BLUE_RUPEE,        SpoilerCollectionCheck::RandomizerInf(RAND_INF_SPIRIT_SILVER_SUN_3));
    locationTable[RC_SPIRIT_SILVER_SUN_4] =                  Location::Collectable(RC_SPIRIT_SILVER_SUN_4,                  RCQUEST_VANILLA,    RCTYPE_SILVER, ACTOR_EN_G_SWITCH, SCENE_SPIRIT_TEMPLE,                TWO_ACTOR_PARAMS(-1123, 428),      "RC_SPIRIT_SILVER_SUN_4",                  RHT_SPIRIT_TEMPLE_SILVER,                                RG_BLUE_RUPEE,        SpoilerCollectionCheck::RandomizerInf(RAND_INF_SPIRIT_SILVER_SUN_4));
    locationTable[RC_SPIRIT_SILVER_SUN_5] =                  Location::Collectable(RC_SPIRIT_SILVER_SUN_5,                  RCQUEST_VANILLA,    RCTYPE_SILVER, ACTOR_EN_G_SWITCH, SCENE_SPIRIT_TEMPLE,                TWO_ACTOR_PARAMS(-984, -450),      "RC_SPIRIT_SILVER_SUN_5",                  RHT_SPIRIT_TEMPLE_SILVER,                                RG_BLUE_RUPEE,        SpoilerCollectionCheck::RandomizerInf(RAND_INF_SPIRIT_SILVER_SUN_5));
    locationTable[RC_SPIRIT_SILVER_BOULDERS_1] =             Location::Collectable(RC_SPIRIT_SILVER_BOULDERS_1,             RCQUEST_VANILLA,    RCTYPE_SILVER, ACTOR_EN_G_SWITCH, SCENE_SPIRIT_TEMPLE,                TWO_ACTOR_PARAMS(1284, -1355),     "RC_SPIRIT_SILVER_BOULDERS_1",             RHT_SPIRIT_TEMPLE_SILVER,                                RG_BLUE_RUPEE,        SpoilerCollectionCheck::RandomizerInf(RAND_INF_SPIRIT_SILVER_BOULDERS_1));
    locationTable[RC_SPIRIT_SILVER_BOULDERS_2] =             Location::Collectable(RC_SPIRIT_SILVER_BOULDERS_2,             RCQUEST_VANILLA,    RCTYPE_SILVER, ACTOR_EN_G_SWITCH, SCENE_SPIRIT_TEMPLE,                TWO_ACTOR_PARAMS(1284, -813),      "RC_SPIRIT_SILVER_BOULDERS_2",             RHT_SPIRIT_TEMPLE_SILVER,                                RG_BLUE_RUPEE,        SpoilerCollectionCheck::RandomizerInf(RAND_INF_SPIRIT_SILVER_BOULDERS_2));
    locationTable[RC_SPIRIT_SILVER_BOULDERS_3] =             Location::Collectable(RC_SPIRIT_SILVER_BOULDERS_3,             RCQUEST_VANILLA,    RCTYPE_SILVER, ACTOR_EN_G_SWITCH, SCENE_SPIRIT_TEMPLE,                TWO_ACTOR_PARAMS(1856, -944),      "RC_SPIRIT_SILVER_BOULDERS_3",             RHT_SPIRIT_TEMPLE_SILVER,                                RG_BLUE_RUPEE,        SpoilerCollectionCheck::RandomizerInf(RAND_INF_SPIRIT_SILVER_BOULDERS_3));
    locationTable[RC_SPIRIT_SILVER_BOULDERS_4] =             Location::Collectable(RC_SPIRIT_SILVER_BOULDERS_4,             RCQUEST_VANILLA,    RCTYPE_SILVER, ACTOR_EN_G_SWITCH, SCENE_SPIRIT_TEMPLE,                TWO_ACTOR_PARAMS(1856, -1219),     "RC_SPIRIT_SILVER_BOULDERS_4",             RHT_SPIRIT_TEMPLE_SILVER,                                RG_BLUE_RUPEE,        SpoilerCollectionCheck::RandomizerInf(RAND_INF_SPIRIT_SILVER_BOULDERS_4));
    locationTable[RC_SPIRIT_SILVER_BOULDERS_5] =             Location::Collectable(RC_SPIRIT_SILVER_BOULDERS_5,             RCQUEST_VANILLA,    RCTYPE_SILVER, ACTOR_EN_G_SWITCH, SCENE_SPIRIT_TEMPLE,                TWO_ACTOR_PARAMS(1573, -920),      "RC_SPIRIT_SILVER_BOULDERS_5",             RHT_SPIRIT_TEMPLE_SILVER,                                RG_BLUE_RUPEE,        SpoilerCollectionCheck::RandomizerInf(RAND_INF_SPIRIT_SILVER_BOULDERS_5));
    locationTable[RC_BOTW_SILVER_1] =                        Location::Collectable(RC_BOTW_SILVER_1,                        RCQUEST_VANILLA,    RCTYPE_SILVER, ACTOR_EN_G_SWITCH, SCENE_BOTTOM_OF_THE_WELL,           TWO_ACTOR_PARAMS(-796, -150),      "RC_BOTW_SILVER_1",                        RHT_BOTW_SILVER,                                         RG_BLUE_RUPEE,        SpoilerCollectionCheck::RandomizerInf(RAND_INF_BOTW_SILVER_1));
    locationTable[RC_BOTW_SILVER_2] =                        Location::Collectable(RC_BOTW_SILVER_2,                        RCQUEST_VANILLA,    RCTYPE_SILVER, ACTOR_EN_G_SWITCH, SCENE_BOTTOM_OF_THE_WELL,           TWO_ACTOR_PARAMS(-614, -297),      "RC_BOTW_SILVER_2",                        RHT_BOTW_SILVER,                                         RG_BLUE_RUPEE,        SpoilerCollectionCheck::RandomizerInf(RAND_INF_BOTW_SILVER_2));
    locationTable[RC_BOTW_SILVER_3] =                        Location::Collectable(RC_BOTW_SILVER_3,                        RCQUEST_VANILLA,    RCTYPE_SILVER, ACTOR_EN_G_SWITCH, SCENE_BOTTOM_OF_THE_WELL,           TWO_ACTOR_PARAMS(-560, -291),      "RC_BOTW_SILVER_3",                        RHT_BOTW_SILVER,                                         RG_BLUE_RUPEE,        SpoilerCollectionCheck::RandomizerInf(RAND_INF_BOTW_SILVER_3));
    locationTable[RC_BOTW_SILVER_4] =                        Location::Collectable(RC_BOTW_SILVER_4,                        RCQUEST_VANILLA,    RCTYPE_SILVER, ACTOR_EN_G_SWITCH, SCENE_BOTTOM_OF_THE_WELL,           TWO_ACTOR_PARAMS(-402, -401),      "RC_BOTW_SILVER_4",                        RHT_BOTW_SILVER,                                         RG_BLUE_RUPEE,        SpoilerCollectionCheck::RandomizerInf(RAND_INF_BOTW_SILVER_4));
    locationTable[RC_BOTW_SILVER_5] =                        Location::Collectable(RC_BOTW_SILVER_5,                        RCQUEST_VANILLA,    RCTYPE_SILVER, ACTOR_EN_G_SWITCH, SCENE_BOTTOM_OF_THE_WELL,           TWO_ACTOR_PARAMS(-259, -234),      "RC_BOTW_SILVER_5",                        RHT_BOTW_SILVER,                                         RG_BLUE_RUPEE,        SpoilerCollectionCheck::RandomizerInf(RAND_INF_BOTW_SILVER_5));
    locationTable[RC_ICE_CAVERN_SILVER_BLADES_1] =           Location::Collectable(RC_ICE_CAVERN_SILVER_BLADES_1,           RCQUEST_VANILLA,    RCTYPE_SILVER, ACTOR_EN_G_SWITCH, SCENE_ICE_CAVERN,                   TWO_ACTOR_PARAMS(1, -143),         "RC_ICE_CAVERN_SILVER_BLADES_1",           RHT_ICE_CAVERN_SILVER,                                   RG_BLUE_RUPEE,        SpoilerCollectionCheck::RandomizerInf(RAND_INF_ICE_CAVERN_SILVER_BLADES_1));
    locationTable[RC_ICE_CAVERN_SILVER_BLADES_2] =           Location::Collectable(RC_ICE_CAVERN_SILVER_BLADES_2,           RCQUEST_VANILLA,    RCTYPE_SILVER, ACTOR_EN_G_SWITCH, SCENE_ICE_CAVERN,                   TWO_ACTOR_PARAMS(198, -388),       "RC_ICE_CAVERN_SILVER_BLADES_2",           RHT_ICE_CAVERN_SILVER,                                   RG_BLUE_RUPEE,        SpoilerCollectionCheck::RandomizerInf(RAND_INF_ICE_CAVERN_SILVER_BLADES_2));
    locationTable[RC_ICE_CAVERN_SILVER_BLADES_3] =           Location::Collectable(RC_ICE_CAVERN_SILVER_BLADES_3,           RCQUEST_VANILLA,    RCTYPE_SILVER, ACTOR_EN_G_SWITCH, SCENE_ICE_CAVERN,                   TWO_ACTOR_PARAMS(278, -637),       "RC_ICE_CAVERN_SILVER_BLADES_3",           RHT_ICE_CAVERN_SILVER,                                   RG_BLUE_RUPEE,        SpoilerCollectionCheck::RandomizerInf(RAND_INF_ICE_CAVERN_SILVER_BLADES_3));
    locationTable[RC_ICE_CAVERN_SILVER_BLADES_4] =           Location::Collectable(RC_ICE_CAVERN_SILVER_BLADES_4,           RCQUEST_VANILLA,    RCTYPE_SILVER, ACTOR_EN_G_SWITCH, SCENE_ICE_CAVERN,                   TWO_ACTOR_PARAMS(389, -382),       "RC_ICE_CAVERN_SILVER_BLADES_4",           RHT_ICE_CAVERN_SILVER,                                   RG_BLUE_RUPEE,        SpoilerCollectionCheck::RandomizerInf(RAND_INF_ICE_CAVERN_SILVER_BLADES_4));
    locationTable[RC_ICE_CAVERN_SILVER_BLADES_5] =           Location::Collectable(RC_ICE_CAVERN_SILVER_BLADES_5,           RCQUEST_VANILLA,    RCTYPE_SILVER, ACTOR_EN_G_SWITCH, SCENE_ICE_CAVERN,                   TWO_ACTOR_PARAMS(414, -579),       "RC_ICE_CAVERN_SILVER_BLADES_5",           RHT_ICE_CAVERN_SILVER,                                   RG_BLUE_RUPEE,        SpoilerCollectionCheck::RandomizerInf(RAND_INF_ICE_CAVERN_SILVER_BLADES_5));
    locationTable[RC_ICE_CAVERN_SILVER_BLOCK_1] =            Location::Collectable(RC_ICE_CAVERN_SILVER_BLOCK_1,            RCQUEST_VANILLA,    RCTYPE_SILVER, ACTOR_EN_G_SWITCH, SCENE_ICE_CAVERN,                   TWO_ACTOR_PARAMS(-1676, -552),     "RC_ICE_CAVERN_SILVER_BLOCK_1",            RHT_ICE_CAVERN_SILVER,                                   RG_BLUE_RUPEE,        SpoilerCollectionCheck::RandomizerInf(RAND_INF_ICE_CAVERN_SILVER_BLOCK_1));
    locationTable[RC_ICE_CAVERN_SILVER_BLOCK_2] =            Location::Collectable(RC_ICE_CAVERN_SILVER_BLOCK_2,            RCQUEST_VANILLA,    RCTYPE_SILVER, ACTOR_EN_G_SWITCH, SCENE_ICE_CAVERN,                   TWO_ACTOR_PARAMS(-1558, -951),     "RC_ICE_CAVERN_SILVER_BLOCK_2",            RHT_ICE_CAVERN_SILVER,                                   RG_BLUE_RUPEE,        SpoilerCollectionCheck::RandomizerInf(RAND_INF_ICE_CAVERN_SILVER_BLOCK_2));
    locationTable[RC_ICE_CAVERN_SILVER_BLOCK_3] =            Location::Collectable(RC_ICE_CAVERN_SILVER_BLOCK_3,            RCQUEST_VANILLA,    RCTYPE_SILVER, ACTOR_EN_G_SWITCH, SCENE_ICE_CAVERN,                   TWO_ACTOR_PARAMS(-1294, -899),     "RC_ICE_CAVERN_SILVER_BLOCK_3",            RHT_ICE_CAVERN_SILVER,                                   RG_BLUE_RUPEE,        SpoilerCollectionCheck::RandomizerInf(RAND_INF_ICE_CAVERN_SILVER_BLOCK_3));
    locationTable[RC_ICE_CAVERN_SILVER_BLOCK_4] =            Location::Collectable(RC_ICE_CAVERN_SILVER_BLOCK_4,            RCQUEST_VANILLA,    RCTYPE_SILVER, ACTOR_EN_G_SWITCH, SCENE_ICE_CAVERN,                   TWO_ACTOR_PARAMS(-1120, -1577),    "RC_ICE_CAVERN_SILVER_BLOCK_4",            RHT_ICE_CAVERN_SILVER,                                   RG_BLUE_RUPEE,        SpoilerCollectionCheck::RandomizerInf(RAND_INF_ICE_CAVERN_SILVER_BLOCK_4));
    locationTable[RC_ICE_CAVERN_SILVER_BLOCK_5] =            Location::Collectable(RC_ICE_CAVERN_SILVER_BLOCK_5,            RCQUEST_VANILLA,    RCTYPE_SILVER, ACTOR_EN_G_SWITCH, SCENE_ICE_CAVERN,                   TWO_ACTOR_PARAMS(-1040, -485),     "RC_ICE_CAVERN_SILVER_BLOCK_5",            RHT_ICE_CAVERN_SILVER,                                   RG_BLUE_RUPEE,        SpoilerCollectionCheck::RandomizerInf(RAND_INF_ICE_CAVERN_SILVER_BLOCK_5));
    locationTable[RC_GTG_SILVER_SLOPE_1] =                   Location::Collectable(RC_GTG_SILVER_SLOPE_1,                   RCQUEST_VANILLA,    RCTYPE_SILVER, ACTOR_EN_G_SWITCH, SCENE_GERUDO_TRAINING_GROUND,       TWO_ACTOR_PARAMS(-1332, -992),     "RC_GTG_SILVER_SLOPE_1",                   RHT_GTG_SILVER,                                          RG_BLUE_RUPEE,        SpoilerCollectionCheck::RandomizerInf(RAND_INF_GTG_SILVER_SLOPE_1));
    locationTable[RC_GTG_SILVER_SLOPE_2] =                   Location::Collectable(RC_GTG_SILVER_SLOPE_2,                   RCQUEST_VANILLA,    RCTYPE_SILVER, ACTOR_EN_G_SWITCH, SCENE_GERUDO_TRAINING_GROUND,       TWO_ACTOR_PARAMS(-1886, -956),     "RC_GTG_SILVER_SLOPE_2",                   RHT_GTG_SILVER,                                          RG_BLUE_RUPEE,        SpoilerCollectionCheck::RandomizerInf(RAND_INF_GTG_SILVER_SLOPE_2));
    locationTable[RC_GTG_SILVER_SLOPE_3] =                   Location::Collectable(RC_GTG_SILVER_SLOPE_3,                   RCQUEST_VANILLA,    RCTYPE_SILVER, ACTOR_EN_G_SWITCH, SCENE_GERUDO_TRAINING_GROUND,       TWO_ACTOR_PARAMS(-1579, -999),     "RC_GTG_SILVER_SLOPE_3",                   RHT_GTG_SILVER,                                          RG_BLUE_RUPEE,        SpoilerCollectionCheck::RandomizerInf(RAND_INF_GTG_SILVER_SLOPE_3));
    locationTable[RC_GTG_SILVER_SLOPE_4] =                   Location::Collectable(RC_GTG_SILVER_SLOPE_4,                   RCQUEST_VANILLA,    RCTYPE_SILVER, ACTOR_EN_G_SWITCH, SCENE_GERUDO_TRAINING_GROUND,       TWO_ACTOR_PARAMS(-1627, -1462),    "RC_GTG_SILVER_SLOPE_4",                   RHT_GTG_SILVER,                                          RG_BLUE_RUPEE,        SpoilerCollectionCheck::RandomizerInf(RAND_INF_GTG_SILVER_SLOPE_4));
    locationTable[RC_GTG_SILVER_SLOPE_5] =                   Location::Collectable(RC_GTG_SILVER_SLOPE_5,                   RCQUEST_VANILLA,    RCTYPE_SILVER, ACTOR_EN_G_SWITCH, SCENE_GERUDO_TRAINING_GROUND,       TWO_ACTOR_PARAMS(-1887, -2134),    "RC_GTG_SILVER_SLOPE_5",                   RHT_GTG_SILVER,                                          RG_BLUE_RUPEE,        SpoilerCollectionCheck::RandomizerInf(RAND_INF_GTG_SILVER_SLOPE_5));
    locationTable[RC_GTG_SILVER_LAVA_1] =                    Location::Collectable(RC_GTG_SILVER_LAVA_1,                    RCQUEST_VANILLA,    RCTYPE_SILVER, ACTOR_EN_G_SWITCH, SCENE_GERUDO_TRAINING_GROUND,       TWO_ACTOR_PARAMS(1320, -1248),     "RC_GTG_SILVER_LAVA_1",                    RHT_GTG_SILVER,                                          RG_BLUE_RUPEE,        SpoilerCollectionCheck::RandomizerInf(RAND_INF_GTG_SILVER_LAVA_1));
    locationTable[RC_GTG_SILVER_LAVA_2] =                    Location::Collectable(RC_GTG_SILVER_LAVA_2,                    RCQUEST_VANILLA,    RCTYPE_SILVER, ACTOR_EN_G_SWITCH, SCENE_GERUDO_TRAINING_GROUND,       TWO_ACTOR_PARAMS(1558, -1370),     "RC_GTG_SILVER_LAVA_2",                    RHT_GTG_SILVER,                                          RG_BLUE_RUPEE,        SpoilerCollectionCheck::RandomizerInf(RAND_INF_GTG_SILVER_LAVA_2));
    locationTable[RC_GTG_SILVER_LAVA_3] =                    Location::Collectable(RC_GTG_SILVER_LAVA_3,                    RCQUEST_VANILLA,    RCTYPE_SILVER, ACTOR_EN_G_SWITCH, SCENE_GERUDO_TRAINING_GROUND,       TWO_ACTOR_PARAMS(1134, -1841),     "RC_GTG_SILVER_LAVA_3",                    RHT_GTG_SILVER,                                          RG_BLUE_RUPEE,        SpoilerCollectionCheck::RandomizerInf(RAND_INF_GTG_SILVER_LAVA_3));
    locationTable[RC_GTG_SILVER_LAVA_4] =                    Location::Collectable(RC_GTG_SILVER_LAVA_4,                    RCQUEST_VANILLA,    RCTYPE_SILVER, ACTOR_EN_G_SWITCH, SCENE_GERUDO_TRAINING_GROUND,       TWO_ACTOR_PARAMS(1437, -2193),     "RC_GTG_SILVER_LAVA_4",                    RHT_GTG_SILVER,                                          RG_BLUE_RUPEE,        SpoilerCollectionCheck::RandomizerInf(RAND_INF_GTG_SILVER_LAVA_4));
    locationTable[RC_GTG_SILVER_LAVA_5] =                    Location::Collectable(RC_GTG_SILVER_LAVA_5,                    RCQUEST_VANILLA,    RCTYPE_SILVER, ACTOR_EN_G_SWITCH, SCENE_GERUDO_TRAINING_GROUND,       TWO_ACTOR_PARAMS(1560, -1861),     "RC_GTG_SILVER_LAVA_5",                    RHT_GTG_SILVER,                                          RG_BLUE_RUPEE,        SpoilerCollectionCheck::RandomizerInf(RAND_INF_GTG_SILVER_LAVA_5));
    locationTable[RC_GTG_SILVER_WATER_1] =                   Location::Collectable(RC_GTG_SILVER_WATER_1,                   RCQUEST_VANILLA,    RCTYPE_SILVER, ACTOR_EN_G_SWITCH, SCENE_GERUDO_TRAINING_GROUND,       TWO_ACTOR_PARAMS(2308, -1464),     "RC_GTG_SILVER_WATER_1",                   RHT_GTG_SILVER,                                          RG_BLUE_RUPEE,        SpoilerCollectionCheck::RandomizerInf(RAND_INF_GTG_SILVER_WATER_1));
    locationTable[RC_GTG_SILVER_WATER_2] =                   Location::Collectable(RC_GTG_SILVER_WATER_2,                   RCQUEST_VANILLA,    RCTYPE_SILVER, ACTOR_EN_G_SWITCH, SCENE_GERUDO_TRAINING_GROUND,       TWO_ACTOR_PARAMS(2497, -1465),     "RC_GTG_SILVER_WATER_2",                   RHT_GTG_SILVER,                                          RG_BLUE_RUPEE,        SpoilerCollectionCheck::RandomizerInf(RAND_INF_GTG_SILVER_WATER_2));
    locationTable[RC_GTG_SILVER_WATER_3] =                   Location::Collectable(RC_GTG_SILVER_WATER_3,                   RCQUEST_VANILLA,    RCTYPE_SILVER, ACTOR_EN_G_SWITCH, SCENE_GERUDO_TRAINING_GROUND,       TWO_ACTOR_PARAMS(2453, -1612),     "RC_GTG_SILVER_WATER_3",                   RHT_GTG_SILVER,                                          RG_BLUE_RUPEE,        SpoilerCollectionCheck::RandomizerInf(RAND_INF_GTG_SILVER_WATER_3));
    locationTable[RC_GTG_SILVER_WATER_4] =                   Location::Collectable(RC_GTG_SILVER_WATER_4,                   RCQUEST_VANILLA,    RCTYPE_SILVER, ACTOR_EN_G_SWITCH, SCENE_GERUDO_TRAINING_GROUND,       TWO_ACTOR_PARAMS(2078, -1458),     "RC_GTG_SILVER_WATER_4",                   RHT_GTG_SILVER,                                          RG_BLUE_RUPEE,        SpoilerCollectionCheck::RandomizerInf(RAND_INF_GTG_SILVER_WATER_4));
    locationTable[RC_GTG_SILVER_WATER_5] =                   Location::Collectable(RC_GTG_SILVER_WATER_5,                   RCQUEST_VANILLA,    RCTYPE_SILVER, ACTOR_EN_G_SWITCH, SCENE_GERUDO_TRAINING_GROUND,       TWO_ACTOR_PARAMS(2160, -1315),     "RC_GTG_SILVER_WATER_5",                   RHT_GTG_SILVER,                                          RG_BLUE_RUPEE,        SpoilerCollectionCheck::RandomizerInf(RAND_INF_GTG_SILVER_WATER_5));
    locationTable[RC_GANONS_CASTLE_SILVER_LIGHT_1] =         Location::Collectable(RC_GANONS_CASTLE_SILVER_LIGHT_1,         RCQUEST_VANILLA,    RCTYPE_SILVER, ACTOR_EN_G_SWITCH, SCENE_INSIDE_GANONS_CASTLE,         TWO_ACTOR_PARAMS(-2509, -1091),    "RC_GANONS_CASTLE_SILVER_LIGHT_1",         RHT_GANONS_CASTLE_SILVER,                                RG_BLUE_RUPEE,        SpoilerCollectionCheck::RandomizerInf(RAND_INF_GANONS_CASTLE_SILVER_LIGHT_1));
    locationTable[RC_GANONS_CASTLE_SILVER_LIGHT_2] =         Location::Collectable(RC_GANONS_CASTLE_SILVER_LIGHT_2,         RCQUEST_VANILLA,    RCTYPE_SILVER, ACTOR_EN_G_SWITCH, SCENE_INSIDE_GANONS_CASTLE,         TWO_ACTOR_PARAMS(-2649, -545),     "RC_GANONS_CASTLE_SILVER_LIGHT_2",         RHT_GANONS_CASTLE_SILVER,                                RG_BLUE_RUPEE,        SpoilerCollectionCheck::RandomizerInf(RAND_INF_GANONS_CASTLE_SILVER_LIGHT_2));
    locationTable[RC_GANONS_CASTLE_SILVER_LIGHT_3] =         Location::Collectable(RC_GANONS_CASTLE_SILVER_LIGHT_3,         RCQUEST_VANILLA,    RCTYPE_SILVER, ACTOR_EN_G_SWITCH, SCENE_INSIDE_GANONS_CASTLE,         TWO_ACTOR_PARAMS(-2646, -839),     "RC_GANONS_CASTLE_SILVER_LIGHT_3",         RHT_GANONS_CASTLE_SILVER,                                RG_BLUE_RUPEE,        SpoilerCollectionCheck::RandomizerInf(RAND_INF_GANONS_CASTLE_SILVER_LIGHT_3));
    locationTable[RC_GANONS_CASTLE_SILVER_LIGHT_4] =         Location::Collectable(RC_GANONS_CASTLE_SILVER_LIGHT_4,         RCQUEST_VANILLA,    RCTYPE_SILVER, ACTOR_EN_G_SWITCH, SCENE_INSIDE_GANONS_CASTLE,         TWO_ACTOR_PARAMS(-2680, -893),     "RC_GANONS_CASTLE_SILVER_LIGHT_4",         RHT_GANONS_CASTLE_SILVER,                                RG_BLUE_RUPEE,        SpoilerCollectionCheck::RandomizerInf(RAND_INF_GANONS_CASTLE_SILVER_LIGHT_4));
    locationTable[RC_GANONS_CASTLE_SILVER_LIGHT_5] =         Location::Collectable(RC_GANONS_CASTLE_SILVER_LIGHT_5,         RCQUEST_VANILLA,    RCTYPE_SILVER, ACTOR_EN_G_SWITCH, SCENE_INSIDE_GANONS_CASTLE,         TWO_ACTOR_PARAMS(-2674, -777),     "RC_GANONS_CASTLE_SILVER_LIGHT_5",         RHT_GANONS_CASTLE_SILVER,                                RG_BLUE_RUPEE,        SpoilerCollectionCheck::RandomizerInf(RAND_INF_GANONS_CASTLE_SILVER_LIGHT_5));
    locationTable[RC_GANONS_CASTLE_SILVER_FOREST_1] =        Location::Collectable(RC_GANONS_CASTLE_SILVER_FOREST_1,        RCQUEST_VANILLA,    RCTYPE_SILVER, ACTOR_EN_G_SWITCH, SCENE_INSIDE_GANONS_CASTLE,         TWO_ACTOR_PARAMS(1247, 1787),      "RC_GANONS_CASTLE_SILVER_FOREST_1",        RHT_GANONS_CASTLE_SILVER,                                RG_BLUE_RUPEE,        SpoilerCollectionCheck::RandomizerInf(RAND_INF_GANONS_CASTLE_SILVER_FOREST_1));
    locationTable[RC_GANONS_CASTLE_SILVER_FOREST_2] =        Location::Collectable(RC_GANONS_CASTLE_SILVER_FOREST_2,        RCQUEST_VANILLA,    RCTYPE_SILVER, ACTOR_EN_G_SWITCH, SCENE_INSIDE_GANONS_CASTLE,         TWO_ACTOR_PARAMS(1361, 1222),      "RC_GANONS_CASTLE_SILVER_FOREST_2",        RHT_GANONS_CASTLE_SILVER,                                RG_BLUE_RUPEE,        SpoilerCollectionCheck::RandomizerInf(RAND_INF_GANONS_CASTLE_SILVER_FOREST_2));
    locationTable[RC_GANONS_CASTLE_SILVER_FOREST_3] =        Location::Collectable(RC_GANONS_CASTLE_SILVER_FOREST_3,        RCQUEST_VANILLA,    RCTYPE_SILVER, ACTOR_EN_G_SWITCH, SCENE_INSIDE_GANONS_CASTLE,         TWO_ACTOR_PARAMS(1538, 2225),      "RC_GANONS_CASTLE_SILVER_FOREST_3",        RHT_GANONS_CASTLE_SILVER,                                RG_BLUE_RUPEE,        SpoilerCollectionCheck::RandomizerInf(RAND_INF_GANONS_CASTLE_SILVER_FOREST_3));
    locationTable[RC_GANONS_CASTLE_SILVER_FOREST_4] =        Location::Collectable(RC_GANONS_CASTLE_SILVER_FOREST_4,        RCQUEST_VANILLA,    RCTYPE_SILVER, ACTOR_EN_G_SWITCH, SCENE_INSIDE_GANONS_CASTLE,         TWO_ACTOR_PARAMS(1651, 2021),      "RC_GANONS_CASTLE_SILVER_FOREST_4",        RHT_GANONS_CASTLE_SILVER,                                RG_BLUE_RUPEE,        SpoilerCollectionCheck::RandomizerInf(RAND_INF_GANONS_CASTLE_SILVER_FOREST_4));
    locationTable[RC_GANONS_CASTLE_SILVER_FOREST_5] =        Location::Collectable(RC_GANONS_CASTLE_SILVER_FOREST_5,        RCQUEST_VANILLA,    RCTYPE_SILVER, ACTOR_EN_G_SWITCH, SCENE_INSIDE_GANONS_CASTLE,         TWO_ACTOR_PARAMS(1634, 1550),      "RC_GANONS_CASTLE_SILVER_FOREST_5",        RHT_GANONS_CASTLE_SILVER,                                RG_BLUE_RUPEE,        SpoilerCollectionCheck::RandomizerInf(RAND_INF_GANONS_CASTLE_SILVER_FOREST_5));
    locationTable[RC_GANONS_CASTLE_SILVER_FIRE_1] =          Location::Collectable(RC_GANONS_CASTLE_SILVER_FIRE_1,          RCQUEST_VANILLA,    RCTYPE_SILVER, ACTOR_EN_G_SWITCH, SCENE_INSIDE_GANONS_CASTLE,         TWO_ACTOR_PARAMS(-854, -3679),     "RC_GANONS_CASTLE_SILVER_FIRE_1",          RHT_GANONS_CASTLE_SILVER,                                RG_BLUE_RUPEE,        SpoilerCollectionCheck::RandomizerInf(RAND_INF_GANONS_CASTLE_SILVER_FIRE_1));
    locationTable[RC_GANONS_CASTLE_SILVER_FIRE_2] =          Location::Collectable(RC_GANONS_CASTLE_SILVER_FIRE_2,          RCQUEST_VANILLA,    RCTYPE_SILVER, ACTOR_EN_G_SWITCH, SCENE_INSIDE_GANONS_CASTLE,         TWO_ACTOR_PARAMS(-1555, -2317),    "RC_GANONS_CASTLE_SILVER_FIRE_2",          RHT_GANONS_CASTLE_SILVER,                                RG_BLUE_RUPEE,        SpoilerCollectionCheck::RandomizerInf(RAND_INF_GANONS_CASTLE_SILVER_FIRE_2));
    locationTable[RC_GANONS_CASTLE_SILVER_FIRE_3] =          Location::Collectable(RC_GANONS_CASTLE_SILVER_FIRE_3,          RCQUEST_VANILLA,    RCTYPE_SILVER, ACTOR_EN_G_SWITCH, SCENE_INSIDE_GANONS_CASTLE,         TWO_ACTOR_PARAMS(-515, -3253),     "RC_GANONS_CASTLE_SILVER_FIRE_3",          RHT_GANONS_CASTLE_SILVER,                                RG_BLUE_RUPEE,        SpoilerCollectionCheck::RandomizerInf(RAND_INF_GANONS_CASTLE_SILVER_FIRE_3));
    locationTable[RC_GANONS_CASTLE_SILVER_FIRE_4] =          Location::Collectable(RC_GANONS_CASTLE_SILVER_FIRE_4,          RCQUEST_VANILLA,    RCTYPE_SILVER, ACTOR_EN_G_SWITCH, SCENE_INSIDE_GANONS_CASTLE,         TWO_ACTOR_PARAMS(-604, -2592),     "RC_GANONS_CASTLE_SILVER_FIRE_4",          RHT_GANONS_CASTLE_SILVER,                                RG_BLUE_RUPEE,        SpoilerCollectionCheck::RandomizerInf(RAND_INF_GANONS_CASTLE_SILVER_FIRE_4));
    locationTable[RC_GANONS_CASTLE_SILVER_FIRE_5] =          Location::Collectable(RC_GANONS_CASTLE_SILVER_FIRE_5,          RCQUEST_VANILLA,    RCTYPE_SILVER, ACTOR_EN_G_SWITCH, SCENE_INSIDE_GANONS_CASTLE,         TWO_ACTOR_PARAMS(-1867, -2754),    "RC_GANONS_CASTLE_SILVER_FIRE_5",          RHT_GANONS_CASTLE_SILVER,                                RG_BLUE_RUPEE,        SpoilerCollectionCheck::RandomizerInf(RAND_INF_GANONS_CASTLE_SILVER_FIRE_5));
    locationTable[RC_GANONS_CASTLE_SILVER_SPIRIT_1] =        Location::Collectable(RC_GANONS_CASTLE_SILVER_SPIRIT_1,        RCQUEST_VANILLA,    RCTYPE_SILVER, ACTOR_EN_G_SWITCH, SCENE_INSIDE_GANONS_CASTLE,         TWO_ACTOR_PARAMS(-829, 591),       "RC_GANONS_CASTLE_SILVER_SPIRIT_1",        RHT_GANONS_CASTLE_SILVER,                                RG_BLUE_RUPEE,        SpoilerCollectionCheck::RandomizerInf(RAND_INF_GANONS_CASTLE_SILVER_SPIRIT_1));
    locationTable[RC_GANONS_CASTLE_SILVER_SPIRIT_2] =        Location::Collectable(RC_GANONS_CASTLE_SILVER_SPIRIT_2,        RCQUEST_VANILLA,    RCTYPE_SILVER, ACTOR_EN_G_SWITCH, SCENE_INSIDE_GANONS_CASTLE,         TWO_ACTOR_PARAMS(-940, 270),       "RC_GANONS_CASTLE_SILVER_SPIRIT_2",        RHT_GANONS_CASTLE_SILVER,                                RG_BLUE_RUPEE,        SpoilerCollectionCheck::RandomizerInf(RAND_INF_GANONS_CASTLE_SILVER_SPIRIT_2));
    locationTable[RC_GANONS_CASTLE_SILVER_SPIRIT_3] =        Location::Collectable(RC_GANONS_CASTLE_SILVER_SPIRIT_3,        RCQUEST_VANILLA,    RCTYPE_SILVER, ACTOR_EN_G_SWITCH, SCENE_INSIDE_GANONS_CASTLE,         TWO_ACTOR_PARAMS(-865, 656),       "RC_GANONS_CASTLE_SILVER_SPIRIT_3",        RHT_GANONS_CASTLE_SILVER,                                RG_BLUE_RUPEE,        SpoilerCollectionCheck::RandomizerInf(RAND_INF_GANONS_CASTLE_SILVER_SPIRIT_3));
    locationTable[RC_GANONS_CASTLE_SILVER_SPIRIT_4] =        Location::Collectable(RC_GANONS_CASTLE_SILVER_SPIRIT_4,        RCQUEST_VANILLA,    RCTYPE_SILVER, ACTOR_EN_G_SWITCH, SCENE_INSIDE_GANONS_CASTLE,         TWO_ACTOR_PARAMS(-725, 942),       "RC_GANONS_CASTLE_SILVER_SPIRIT_4",        RHT_GANONS_CASTLE_SILVER,                                RG_BLUE_RUPEE,        SpoilerCollectionCheck::RandomizerInf(RAND_INF_GANONS_CASTLE_SILVER_SPIRIT_4));
    locationTable[RC_GANONS_CASTLE_SILVER_SPIRIT_5] =        Location::Collectable(RC_GANONS_CASTLE_SILVER_SPIRIT_5,        RCQUEST_VANILLA,    RCTYPE_SILVER, ACTOR_EN_G_SWITCH, SCENE_INSIDE_GANONS_CASTLE,         TWO_ACTOR_PARAMS(-1142, 639),      "RC_GANONS_CASTLE_SILVER_SPIRIT_5",        RHT_GANONS_CASTLE_SILVER,                                RG_BLUE_RUPEE,        SpoilerCollectionCheck::RandomizerInf(RAND_INF_GANONS_CASTLE_SILVER_SPIRIT_5));
    locationTable[RC_DODONGOS_CAVERN_MQ_SILVER_1] =          Location::Collectable(RC_DODONGOS_CAVERN_MQ_SILVER_1,          RCQUEST_MQ,         RCTYPE_SILVER, ACTOR_EN_G_SWITCH, SCENE_DODONGOS_CAVERN,              TWO_ACTOR_PARAMS(-2277, -1362),    "RC_DODONGOS_CAVERN_MQ_SILVER_1",          RHT_DODONGOS_CAVERN_SILVER,                              RG_BLUE_RUPEE,        SpoilerCollectionCheck::RandomizerInf(RAND_INF_DODONGOS_CAVERN_MQ_SILVER_1));
    locationTable[RC_DODONGOS_CAVERN_MQ_SILVER_2] =          Location::Collectable(RC_DODONGOS_CAVERN_MQ_SILVER_2,          RCQUEST_MQ,         RCTYPE_SILVER, ACTOR_EN_G_SWITCH, SCENE_DODONGOS_CAVERN,              TWO_ACTOR_PARAMS(-2189, -1834),    "RC_DODONGOS_CAVERN_MQ_SILVER_2",          RHT_DODONGOS_CAVERN_SILVER,                              RG_BLUE_RUPEE,        SpoilerCollectionCheck::RandomizerInf(RAND_INF_DODONGOS_CAVERN_MQ_SILVER_2));
    locationTable[RC_DODONGOS_CAVERN_MQ_SILVER_3] =          Location::Collectable(RC_DODONGOS_CAVERN_MQ_SILVER_3,          RCQUEST_MQ,         RCTYPE_SILVER, ACTOR_EN_G_SWITCH, SCENE_DODONGOS_CAVERN,              TWO_ACTOR_PARAMS(-2411, -1836),    "RC_DODONGOS_CAVERN_MQ_SILVER_3",          RHT_DODONGOS_CAVERN_SILVER,                              RG_BLUE_RUPEE,        SpoilerCollectionCheck::RandomizerInf(RAND_INF_DODONGOS_CAVERN_MQ_SILVER_3));
    locationTable[RC_DODONGOS_CAVERN_MQ_SILVER_4] =          Location::Collectable(RC_DODONGOS_CAVERN_MQ_SILVER_4,          RCQUEST_MQ,         RCTYPE_SILVER, ACTOR_EN_G_SWITCH, SCENE_DODONGOS_CAVERN,              TWO_ACTOR_PARAMS(-1907, -1243),    "RC_DODONGOS_CAVERN_MQ_SILVER_4",          RHT_DODONGOS_CAVERN_SILVER,                              RG_BLUE_RUPEE,        SpoilerCollectionCheck::RandomizerInf(RAND_INF_DODONGOS_CAVERN_MQ_SILVER_4));
    locationTable[RC_DODONGOS_CAVERN_MQ_SILVER_5] =          Location::Collectable(RC_DODONGOS_CAVERN_MQ_SILVER_5,          RCQUEST_MQ,         RCTYPE_SILVER, ACTOR_EN_G_SWITCH, SCENE_DODONGOS_CAVERN,              TWO_ACTOR_PARAMS(-1512, -1083),    "RC_DODONGOS_CAVERN_MQ_SILVER_5",          RHT_DODONGOS_CAVERN_SILVER,                              RG_BLUE_RUPEE,        SpoilerCollectionCheck::RandomizerInf(RAND_INF_DODONGOS_CAVERN_MQ_SILVER_5));
    locationTable[RC_SHADOW_MQ_SILVER_BLADES_1] =            Location::Collectable(RC_SHADOW_MQ_SILVER_BLADES_1,            RCQUEST_MQ,         RCTYPE_SILVER, ACTOR_EN_G_SWITCH, SCENE_SHADOW_TEMPLE,                TWO_ACTOR_PARAMS(2810, -961 ),     "RC_SHADOW_MQ_SILVER_BLADES_1",            RHT_SHADOW_TEMPLE_SILVER,                                RG_BLUE_RUPEE,        SpoilerCollectionCheck::RandomizerInf(RAND_INF_SHADOW_MQ_SILVER_BLADES_1));
    locationTable[RC_SHADOW_MQ_SILVER_BLADES_2] =            Location::Collectable(RC_SHADOW_MQ_SILVER_BLADES_2,            RCQUEST_MQ,         RCTYPE_SILVER, ACTOR_EN_G_SWITCH, SCENE_SHADOW_TEMPLE,                TWO_ACTOR_PARAMS(3007, -1222),     "RC_SHADOW_MQ_SILVER_BLADES_2",            RHT_SHADOW_TEMPLE_SILVER,                                RG_BLUE_RUPEE,        SpoilerCollectionCheck::RandomizerInf(RAND_INF_SHADOW_MQ_SILVER_BLADES_2));
    locationTable[RC_SHADOW_MQ_SILVER_BLADES_3] =            Location::Collectable(RC_SHADOW_MQ_SILVER_BLADES_3,            RCQUEST_MQ,         RCTYPE_SILVER, ACTOR_EN_G_SWITCH, SCENE_SHADOW_TEMPLE,                TWO_ACTOR_PARAMS(3243, -1061),     "RC_SHADOW_MQ_SILVER_BLADES_3",            RHT_SHADOW_TEMPLE_SILVER,                                RG_BLUE_RUPEE,        SpoilerCollectionCheck::RandomizerInf(RAND_INF_SHADOW_MQ_SILVER_BLADES_3));
    locationTable[RC_SHADOW_MQ_SILVER_BLADES_4] =            Location::Collectable(RC_SHADOW_MQ_SILVER_BLADES_4,            RCQUEST_MQ,         RCTYPE_SILVER, ACTOR_EN_G_SWITCH, SCENE_SHADOW_TEMPLE,                TWO_ACTOR_PARAMS(3399, -838 ),     "RC_SHADOW_MQ_SILVER_BLADES_4",            RHT_SHADOW_TEMPLE_SILVER,                                RG_BLUE_RUPEE,        SpoilerCollectionCheck::RandomizerInf(RAND_INF_SHADOW_MQ_SILVER_BLADES_4));
    locationTable[RC_SHADOW_MQ_SILVER_BLADES_5] =            Location::Collectable(RC_SHADOW_MQ_SILVER_BLADES_5,            RCQUEST_MQ,         RCTYPE_SILVER, ACTOR_EN_G_SWITCH, SCENE_SHADOW_TEMPLE,                TWO_ACTOR_PARAMS(3558, -1490),     "RC_SHADOW_MQ_SILVER_BLADES_5",            RHT_SHADOW_TEMPLE_SILVER,                                RG_BLUE_RUPEE,        SpoilerCollectionCheck::RandomizerInf(RAND_INF_SHADOW_MQ_SILVER_BLADES_5));
    locationTable[RC_SHADOW_MQ_SILVER_PIT_1] =               Location::Collectable(RC_SHADOW_MQ_SILVER_PIT_1,               RCQUEST_MQ,         RCTYPE_SILVER, ACTOR_EN_G_SWITCH, SCENE_SHADOW_TEMPLE,                TWO_ACTOR_PARAMS(1970, 3372),      "RC_SHADOW_MQ_SILVER_PIT_1",               RHT_SHADOW_TEMPLE_SILVER,                                RG_BLUE_RUPEE,        SpoilerCollectionCheck::RandomizerInf(RAND_INF_SHADOW_MQ_SILVER_PIT_1));
    locationTable[RC_SHADOW_MQ_SILVER_PIT_2] =               Location::Collectable(RC_SHADOW_MQ_SILVER_PIT_2,               RCQUEST_MQ,         RCTYPE_SILVER, ACTOR_EN_G_SWITCH, SCENE_SHADOW_TEMPLE,                TWO_ACTOR_PARAMS(2110, -970),      "RC_SHADOW_MQ_SILVER_PIT_2",               RHT_SHADOW_TEMPLE_SILVER,                                RG_BLUE_RUPEE,        SpoilerCollectionCheck::RandomizerInf(RAND_INF_SHADOW_MQ_SILVER_PIT_2));
    locationTable[RC_SHADOW_MQ_SILVER_PIT_3] =               Location::Collectable(RC_SHADOW_MQ_SILVER_PIT_3,               RCQUEST_MQ,         RCTYPE_SILVER, ACTOR_EN_G_SWITCH, SCENE_SHADOW_TEMPLE,                TWO_ACTOR_PARAMS(2110, -1092),     "RC_SHADOW_MQ_SILVER_PIT_3",               RHT_SHADOW_TEMPLE_SILVER,                                RG_BLUE_RUPEE,        SpoilerCollectionCheck::RandomizerInf(RAND_INF_SHADOW_MQ_SILVER_PIT_3));
    locationTable[RC_SHADOW_MQ_SILVER_PIT_4] =               Location::Collectable(RC_SHADOW_MQ_SILVER_PIT_4,               RCQUEST_MQ,         RCTYPE_SILVER, ACTOR_EN_G_SWITCH, SCENE_SHADOW_TEMPLE,                TWO_ACTOR_PARAMS(2131, 3030),      "RC_SHADOW_MQ_SILVER_PIT_4",               RHT_SHADOW_TEMPLE_SILVER,                                RG_BLUE_RUPEE,        SpoilerCollectionCheck::RandomizerInf(RAND_INF_SHADOW_MQ_SILVER_PIT_4));
    locationTable[RC_SHADOW_MQ_SILVER_PIT_5] =               Location::Collectable(RC_SHADOW_MQ_SILVER_PIT_5,               RCQUEST_MQ,         RCTYPE_SILVER, ACTOR_EN_G_SWITCH, SCENE_SHADOW_TEMPLE,                TWO_ACTOR_PARAMS(2250, 3372),      "RC_SHADOW_MQ_SILVER_PIT_5",               RHT_SHADOW_TEMPLE_SILVER,                                RG_BLUE_RUPEE,        SpoilerCollectionCheck::RandomizerInf(RAND_INF_SHADOW_MQ_SILVER_PIT_5));
    locationTable[RC_SHADOW_MQ_SILVER_INVISIBLE_BLADES_1] =  Location::Collectable(RC_SHADOW_MQ_SILVER_INVISIBLE_BLADES_1,  RCQUEST_MQ,         RCTYPE_SILVER, ACTOR_EN_G_SWITCH, SCENE_SHADOW_TEMPLE,                TWO_ACTOR_PARAMS(5089, 2049),      "RC_SHADOW_MQ_SILVER_INVISIBLE_BLADES_1",  RHT_SHADOW_TEMPLE_SILVER,                                RG_BLUE_RUPEE,        SpoilerCollectionCheck::RandomizerInf(RAND_INF_SHADOW_MQ_SILVER_INVISIBLE_BLADES_1));
    locationTable[RC_SHADOW_MQ_SILVER_INVISIBLE_BLADES_2] =  Location::Collectable(RC_SHADOW_MQ_SILVER_INVISIBLE_BLADES_2,  RCQUEST_MQ,         RCTYPE_SILVER, ACTOR_EN_G_SWITCH, SCENE_SHADOW_TEMPLE,                TWO_ACTOR_PARAMS(5158, 2315),      "RC_SHADOW_MQ_SILVER_INVISIBLE_BLADES_2",  RHT_SHADOW_TEMPLE_SILVER,                                RG_BLUE_RUPEE,        SpoilerCollectionCheck::RandomizerInf(RAND_INF_SHADOW_MQ_SILVER_INVISIBLE_BLADES_2));
    locationTable[RC_SHADOW_MQ_SILVER_INVISIBLE_BLADES_3] =  Location::Collectable(RC_SHADOW_MQ_SILVER_INVISIBLE_BLADES_3,  RCQUEST_MQ,         RCTYPE_SILVER, ACTOR_EN_G_SWITCH, SCENE_SHADOW_TEMPLE,                TWO_ACTOR_PARAMS(5217, 1852),      "RC_SHADOW_MQ_SILVER_INVISIBLE_BLADES_3",  RHT_SHADOW_TEMPLE_SILVER,                                RG_BLUE_RUPEE,        SpoilerCollectionCheck::RandomizerInf(RAND_INF_SHADOW_MQ_SILVER_INVISIBLE_BLADES_3));
    locationTable[RC_SHADOW_MQ_SILVER_INVISIBLE_BLADES_4] =  Location::Collectable(RC_SHADOW_MQ_SILVER_INVISIBLE_BLADES_4,  RCQUEST_MQ,         RCTYPE_SILVER, ACTOR_EN_G_SWITCH, SCENE_SHADOW_TEMPLE,                TWO_ACTOR_PARAMS(5270, 2453),      "RC_SHADOW_MQ_SILVER_INVISIBLE_BLADES_4",  RHT_SHADOW_TEMPLE_SILVER,                                RG_BLUE_RUPEE,        SpoilerCollectionCheck::RandomizerInf(RAND_INF_SHADOW_MQ_SILVER_INVISIBLE_BLADES_4));
    locationTable[RC_SHADOW_MQ_SILVER_INVISIBLE_BLADES_5] =  Location::Collectable(RC_SHADOW_MQ_SILVER_INVISIBLE_BLADES_5,  RCQUEST_MQ,         RCTYPE_SILVER, ACTOR_EN_G_SWITCH, SCENE_SHADOW_TEMPLE,                TWO_ACTOR_PARAMS(5404, 1977),      "RC_SHADOW_MQ_SILVER_INVISIBLE_BLADES_5",  RHT_SHADOW_TEMPLE_SILVER,                                RG_BLUE_RUPEE,        SpoilerCollectionCheck::RandomizerInf(RAND_INF_SHADOW_MQ_SILVER_INVISIBLE_BLADES_5));
    locationTable[RC_SHADOW_MQ_SILVER_INVISIBLE_BLADES_6] =  Location::Collectable(RC_SHADOW_MQ_SILVER_INVISIBLE_BLADES_6,  RCQUEST_MQ,         RCTYPE_SILVER, ACTOR_EN_G_SWITCH, SCENE_SHADOW_TEMPLE,                TWO_ACTOR_PARAMS(5466, 2243),      "RC_SHADOW_MQ_SILVER_INVISIBLE_BLADES_6",  RHT_SHADOW_TEMPLE_SILVER,                                RG_BLUE_RUPEE,        SpoilerCollectionCheck::RandomizerInf(RAND_INF_SHADOW_MQ_SILVER_INVISIBLE_BLADES_6));
    locationTable[RC_SHADOW_MQ_SILVER_INVISIBLE_BLADES_7] =  Location::Collectable(RC_SHADOW_MQ_SILVER_INVISIBLE_BLADES_7,  RCQUEST_MQ,         RCTYPE_SILVER, ACTOR_EN_G_SWITCH, SCENE_SHADOW_TEMPLE,                TWO_ACTOR_PARAMS(5489, 2476),      "RC_SHADOW_MQ_SILVER_INVISIBLE_BLADES_7",  RHT_SHADOW_TEMPLE_SILVER,                                RG_BLUE_RUPEE,        SpoilerCollectionCheck::RandomizerInf(RAND_INF_SHADOW_MQ_SILVER_INVISIBLE_BLADES_7));
    locationTable[RC_SHADOW_MQ_SILVER_INVISIBLE_BLADES_8] =  Location::Collectable(RC_SHADOW_MQ_SILVER_INVISIBLE_BLADES_8,  RCQUEST_MQ,         RCTYPE_SILVER, ACTOR_EN_G_SWITCH, SCENE_SHADOW_TEMPLE,                TWO_ACTOR_PARAMS(5601, 1898),      "RC_SHADOW_MQ_SILVER_INVISIBLE_BLADES_8",  RHT_SHADOW_TEMPLE_SILVER,                                RG_BLUE_RUPEE,        SpoilerCollectionCheck::RandomizerInf(RAND_INF_SHADOW_MQ_SILVER_INVISIBLE_BLADES_8));
    locationTable[RC_SHADOW_MQ_SILVER_INVISIBLE_BLADES_9] =  Location::Collectable(RC_SHADOW_MQ_SILVER_INVISIBLE_BLADES_9,  RCQUEST_MQ,         RCTYPE_SILVER, ACTOR_EN_G_SWITCH, SCENE_SHADOW_TEMPLE,                TWO_ACTOR_PARAMS(5637, 2134),      "RC_SHADOW_MQ_SILVER_INVISIBLE_BLADES_9",  RHT_SHADOW_TEMPLE_SILVER,                                RG_BLUE_RUPEE,        SpoilerCollectionCheck::RandomizerInf(RAND_INF_SHADOW_MQ_SILVER_INVISIBLE_BLADES_9));
    locationTable[RC_SHADOW_MQ_SILVER_INVISIBLE_BLADES_10] = Location::Collectable(RC_SHADOW_MQ_SILVER_INVISIBLE_BLADES_10, RCQUEST_MQ,         RCTYPE_SILVER, ACTOR_EN_G_SWITCH, SCENE_SHADOW_TEMPLE,                TWO_ACTOR_PARAMS(5667, 2686),      "RC_SHADOW_MQ_SILVER_INVISIBLE_BLADES_10", RHT_SHADOW_TEMPLE_SILVER,                                RG_BLUE_RUPEE,        SpoilerCollectionCheck::RandomizerInf(RAND_INF_SHADOW_MQ_SILVER_INVISIBLE_BLADES_10));
    locationTable[RC_SHADOW_MQ_SILVER_SPIKES_1] =            Location::Collectable(RC_SHADOW_MQ_SILVER_SPIKES_1,            RCQUEST_MQ,         RCTYPE_SILVER, ACTOR_EN_G_SWITCH, SCENE_SHADOW_TEMPLE,                TWO_ACTOR_PARAMS(2042, 849),       "RC_SHADOW_MQ_SILVER_SPIKES_1",            RHT_SHADOW_TEMPLE_SILVER,                                RG_BLUE_RUPEE,        SpoilerCollectionCheck::RandomizerInf(RAND_INF_SHADOW_MQ_SILVER_SPIKES_1));
    locationTable[RC_SHADOW_MQ_SILVER_SPIKES_2] =            Location::Collectable(RC_SHADOW_MQ_SILVER_SPIKES_2,            RCQUEST_MQ,         RCTYPE_SILVER, ACTOR_EN_G_SWITCH, SCENE_SHADOW_TEMPLE,                TWO_ACTOR_PARAMS(2135, 1297),      "RC_SHADOW_MQ_SILVER_SPIKES_2",            RHT_SHADOW_TEMPLE_SILVER,                                RG_BLUE_RUPEE,        SpoilerCollectionCheck::RandomizerInf(RAND_INF_SHADOW_MQ_SILVER_SPIKES_2));
    locationTable[RC_SHADOW_MQ_SILVER_SPIKES_3] =            Location::Collectable(RC_SHADOW_MQ_SILVER_SPIKES_3,            RCQUEST_MQ,         RCTYPE_SILVER, ACTOR_EN_G_SWITCH, SCENE_SHADOW_TEMPLE,                TWO_ACTOR_PARAMS(2254, 988),       "RC_SHADOW_MQ_SILVER_SPIKES_3",            RHT_SHADOW_TEMPLE_SILVER,                                RG_BLUE_RUPEE,        SpoilerCollectionCheck::RandomizerInf(RAND_INF_SHADOW_MQ_SILVER_SPIKES_3));
    locationTable[RC_SHADOW_MQ_SILVER_SPIKES_4] =            Location::Collectable(RC_SHADOW_MQ_SILVER_SPIKES_4,            RCQUEST_MQ,         RCTYPE_SILVER, ACTOR_EN_G_SWITCH, SCENE_SHADOW_TEMPLE,                TWO_ACTOR_PARAMS(2478, 893),       "RC_SHADOW_MQ_SILVER_SPIKES_4",            RHT_SHADOW_TEMPLE_SILVER,                                RG_BLUE_RUPEE,        SpoilerCollectionCheck::RandomizerInf(RAND_INF_SHADOW_MQ_SILVER_SPIKES_4));
    locationTable[RC_SHADOW_MQ_SILVER_SPIKES_5] =            Location::Collectable(RC_SHADOW_MQ_SILVER_SPIKES_5,            RCQUEST_MQ,         RCTYPE_SILVER, ACTOR_EN_G_SWITCH, SCENE_SHADOW_TEMPLE,                TWO_ACTOR_PARAMS(2478, 1208),      "RC_SHADOW_MQ_SILVER_SPIKES_5",            RHT_SHADOW_TEMPLE_SILVER,                                RG_BLUE_RUPEE,        SpoilerCollectionCheck::RandomizerInf(RAND_INF_SHADOW_MQ_SILVER_SPIKES_5));
    locationTable[RC_SHADOW_MQ_SILVER_SPIKES_6] =            Location::Collectable(RC_SHADOW_MQ_SILVER_SPIKES_6,            RCQUEST_MQ,         RCTYPE_SILVER, ACTOR_EN_G_SWITCH, SCENE_SHADOW_TEMPLE,                TWO_ACTOR_PARAMS(2478, 1200),      "RC_SHADOW_MQ_SILVER_SPIKES_6",            RHT_SHADOW_TEMPLE_SILVER,                                RG_BLUE_RUPEE,        SpoilerCollectionCheck::RandomizerInf(RAND_INF_SHADOW_MQ_SILVER_SPIKES_6));
    locationTable[RC_SHADOW_MQ_SILVER_SPIKES_7] =            Location::Collectable(RC_SHADOW_MQ_SILVER_SPIKES_7,            RCQUEST_MQ,         RCTYPE_SILVER, ACTOR_EN_G_SWITCH, SCENE_SHADOW_TEMPLE,                TWO_ACTOR_PARAMS(2478, 1404),      "RC_SHADOW_MQ_SILVER_SPIKES_7",            RHT_SHADOW_TEMPLE_SILVER,                                RG_BLUE_RUPEE,        SpoilerCollectionCheck::RandomizerInf(RAND_INF_SHADOW_MQ_SILVER_SPIKES_7));
    locationTable[RC_SHADOW_MQ_SILVER_SPIKES_8] =            Location::Collectable(RC_SHADOW_MQ_SILVER_SPIKES_8,            RCQUEST_MQ,         RCTYPE_SILVER, ACTOR_EN_G_SWITCH, SCENE_SHADOW_TEMPLE,                TWO_ACTOR_PARAMS(2705, 1089),      "RC_SHADOW_MQ_SILVER_SPIKES_8",            RHT_SHADOW_TEMPLE_SILVER,                                RG_BLUE_RUPEE,        SpoilerCollectionCheck::RandomizerInf(RAND_INF_SHADOW_MQ_SILVER_SPIKES_8));
    locationTable[RC_SHADOW_MQ_SILVER_SPIKES_9] =            Location::Collectable(RC_SHADOW_MQ_SILVER_SPIKES_9,            RCQUEST_MQ,         RCTYPE_SILVER, ACTOR_EN_G_SWITCH, SCENE_SHADOW_TEMPLE,                TWO_ACTOR_PARAMS(2730, 876),       "RC_SHADOW_MQ_SILVER_SPIKES_9",            RHT_SHADOW_TEMPLE_SILVER,                                RG_BLUE_RUPEE,        SpoilerCollectionCheck::RandomizerInf(RAND_INF_SHADOW_MQ_SILVER_SPIKES_9));
    locationTable[RC_SHADOW_MQ_SILVER_SPIKES_10] =           Location::Collectable(RC_SHADOW_MQ_SILVER_SPIKES_10,           RCQUEST_MQ,         RCTYPE_SILVER, ACTOR_EN_G_SWITCH, SCENE_SHADOW_TEMPLE,                TWO_ACTOR_PARAMS(2940, 1069),      "RC_SHADOW_MQ_SILVER_SPIKES_10",           RHT_SHADOW_TEMPLE_SILVER,                                RG_BLUE_RUPEE,        SpoilerCollectionCheck::RandomizerInf(RAND_INF_SHADOW_MQ_SILVER_SPIKES_10));
    locationTable[RC_SPIRIT_MQ_SILVER_LOBBY_1] =             Location::Collectable(RC_SPIRIT_MQ_SILVER_LOBBY_1,             RCQUEST_MQ,         RCTYPE_SILVER, ACTOR_EN_G_SWITCH, SCENE_SPIRIT_TEMPLE,                TWO_ACTOR_PARAMS(1016, -73),       "RC_SPIRIT_MQ_SILVER_LOBBY_1",             RHT_SPIRIT_TEMPLE_SILVER,                                RG_BLUE_RUPEE,        SpoilerCollectionCheck::RandomizerInf(RAND_INF_SPIRIT_MQ_SILVER_LOBBY_1));
    locationTable[RC_SPIRIT_MQ_SILVER_LOBBY_2] =             Location::Collectable(RC_SPIRIT_MQ_SILVER_LOBBY_2,             RCQUEST_MQ,         RCTYPE_SILVER, ACTOR_EN_G_SWITCH, SCENE_SPIRIT_TEMPLE,                TWO_ACTOR_PARAMS(160, 268),        "RC_SPIRIT_MQ_SILVER_LOBBY_2",             RHT_SPIRIT_TEMPLE_SILVER,                                RG_BLUE_RUPEE,        SpoilerCollectionCheck::RandomizerInf(RAND_INF_SPIRIT_MQ_SILVER_LOBBY_2));
    locationTable[RC_SPIRIT_MQ_SILVER_LOBBY_3] =             Location::Collectable(RC_SPIRIT_MQ_SILVER_LOBBY_3,             RCQUEST_MQ,         RCTYPE_SILVER, ACTOR_EN_G_SWITCH, SCENE_SPIRIT_TEMPLE,                TWO_ACTOR_PARAMS(-160, 270),       "RC_SPIRIT_MQ_SILVER_LOBBY_3",             RHT_SPIRIT_TEMPLE_SILVER,                                RG_BLUE_RUPEE,        SpoilerCollectionCheck::RandomizerInf(RAND_INF_SPIRIT_MQ_SILVER_LOBBY_3));
    locationTable[RC_SPIRIT_MQ_SILVER_LOBBY_4] =             Location::Collectable(RC_SPIRIT_MQ_SILVER_LOBBY_4,             RCQUEST_MQ,         RCTYPE_SILVER, ACTOR_EN_G_SWITCH, SCENE_SPIRIT_TEMPLE,                TWO_ACTOR_PARAMS(967, -547),       "RC_SPIRIT_MQ_SILVER_LOBBY_4",             RHT_SPIRIT_TEMPLE_SILVER,                                RG_BLUE_RUPEE,        SpoilerCollectionCheck::RandomizerInf(RAND_INF_SPIRIT_MQ_SILVER_LOBBY_4));
    locationTable[RC_SPIRIT_MQ_SILVER_LOBBY_5] =             Location::Collectable(RC_SPIRIT_MQ_SILVER_LOBBY_5,             RCQUEST_MQ,         RCTYPE_SILVER, ACTOR_EN_G_SWITCH, SCENE_SPIRIT_TEMPLE,                TWO_ACTOR_PARAMS(744, 4),          "RC_SPIRIT_MQ_SILVER_LOBBY_5",             RHT_SPIRIT_TEMPLE_SILVER,                                RG_BLUE_RUPEE,        SpoilerCollectionCheck::RandomizerInf(RAND_INF_SPIRIT_MQ_SILVER_LOBBY_5));
    locationTable[RC_SPIRIT_MQ_SILVER_BIG_WALL_1] =          Location::Collectable(RC_SPIRIT_MQ_SILVER_BIG_WALL_1,          RCQUEST_MQ,         RCTYPE_SILVER, ACTOR_EN_G_SWITCH, SCENE_SPIRIT_TEMPLE,                TWO_ACTOR_PARAMS(723, -75),        "RC_SPIRIT_MQ_SILVER_BIG_WALL_1",          RHT_SPIRIT_TEMPLE_SILVER,                                RG_BLUE_RUPEE,        SpoilerCollectionCheck::RandomizerInf(RAND_INF_SPIRIT_MQ_SILVER_BIG_WALL_1));
    locationTable[RC_SPIRIT_MQ_SILVER_BIG_WALL_2] =          Location::Collectable(RC_SPIRIT_MQ_SILVER_BIG_WALL_2,          RCQUEST_MQ,         RCTYPE_SILVER, ACTOR_EN_G_SWITCH, SCENE_SPIRIT_TEMPLE,                TWO_ACTOR_PARAMS(582, -75),        "RC_SPIRIT_MQ_SILVER_BIG_WALL_2",          RHT_SPIRIT_TEMPLE_SILVER,                                RG_BLUE_RUPEE,        SpoilerCollectionCheck::RandomizerInf(RAND_INF_SPIRIT_MQ_SILVER_BIG_WALL_2));
    locationTable[RC_SPIRIT_MQ_SILVER_BIG_WALL_3] =          Location::Collectable(RC_SPIRIT_MQ_SILVER_BIG_WALL_3,          RCQUEST_MQ,         RCTYPE_SILVER, ACTOR_EN_G_SWITCH, SCENE_SPIRIT_TEMPLE,                TWO_ACTOR_PARAMS(754, -75),        "RC_SPIRIT_MQ_SILVER_BIG_WALL_3",          RHT_SPIRIT_TEMPLE_SILVER,                                RG_BLUE_RUPEE,        SpoilerCollectionCheck::RandomizerInf(RAND_INF_SPIRIT_MQ_SILVER_BIG_WALL_3));
    locationTable[RC_SPIRIT_MQ_SILVER_BIG_WALL_4] =          Location::Collectable(RC_SPIRIT_MQ_SILVER_BIG_WALL_4,          RCQUEST_MQ,         RCTYPE_SILVER, ACTOR_EN_G_SWITCH, SCENE_SPIRIT_TEMPLE,                TWO_ACTOR_PARAMS(644, -75),        "RC_SPIRIT_MQ_SILVER_BIG_WALL_4",          RHT_SPIRIT_TEMPLE_SILVER,                                RG_BLUE_RUPEE,        SpoilerCollectionCheck::RandomizerInf(RAND_INF_SPIRIT_MQ_SILVER_BIG_WALL_4));
    locationTable[RC_SPIRIT_MQ_SILVER_BIG_WALL_5] =          Location::Collectable(RC_SPIRIT_MQ_SILVER_BIG_WALL_5,          RCQUEST_MQ,         RCTYPE_SILVER, ACTOR_EN_G_SWITCH, SCENE_SPIRIT_TEMPLE,                TWO_ACTOR_PARAMS(681, -75),        "RC_SPIRIT_MQ_SILVER_BIG_WALL_5",          RHT_SPIRIT_TEMPLE_SILVER,                                RG_BLUE_RUPEE,        SpoilerCollectionCheck::RandomizerInf(RAND_INF_SPIRIT_MQ_SILVER_BIG_WALL_5));
    locationTable[RC_GTG_MQ_SILVER_SLOPE_1] =                Location::Collectable(RC_GTG_MQ_SILVER_SLOPE_1,                RCQUEST_MQ,         RCTYPE_SILVER, ACTOR_EN_G_SWITCH, SCENE_GERUDO_TRAINING_GROUND,       TWO_ACTOR_PARAMS(-1245, -2112),    "RC_GTG_MQ_SILVER_SLOPE_1",                RHT_GTG_SILVER,                                          RG_BLUE_RUPEE,        SpoilerCollectionCheck::RandomizerInf(RAND_INF_GTG_MQ_SILVER_SLOPE_1));
    locationTable[RC_GTG_MQ_SILVER_SLOPE_2] =                Location::Collectable(RC_GTG_MQ_SILVER_SLOPE_2,                RCQUEST_MQ,         RCTYPE_SILVER, ACTOR_EN_G_SWITCH, SCENE_GERUDO_TRAINING_GROUND,       TWO_ACTOR_PARAMS(-1542, -1467),    "RC_GTG_MQ_SILVER_SLOPE_2",                RHT_GTG_SILVER,                                          RG_BLUE_RUPEE,        SpoilerCollectionCheck::RandomizerInf(RAND_INF_GTG_MQ_SILVER_SLOPE_2));
    locationTable[RC_GTG_MQ_SILVER_SLOPE_3] =                Location::Collectable(RC_GTG_MQ_SILVER_SLOPE_3,                RCQUEST_MQ,         RCTYPE_SILVER, ACTOR_EN_G_SWITCH, SCENE_GERUDO_TRAINING_GROUND,       TWO_ACTOR_PARAMS(-1480, -1000),    "RC_GTG_MQ_SILVER_SLOPE_3",                RHT_GTG_SILVER,                                          RG_BLUE_RUPEE,        SpoilerCollectionCheck::RandomizerInf(RAND_INF_GTG_MQ_SILVER_SLOPE_3));
    locationTable[RC_GTG_MQ_SILVER_SLOPE_4] =                Location::Collectable(RC_GTG_MQ_SILVER_SLOPE_4,                RCQUEST_MQ,         RCTYPE_SILVER, ACTOR_EN_G_SWITCH, SCENE_GERUDO_TRAINING_GROUND,       TWO_ACTOR_PARAMS(-1886, -956),     "RC_GTG_MQ_SILVER_SLOPE_4",                RHT_GTG_SILVER,                                          RG_BLUE_RUPEE,        SpoilerCollectionCheck::RandomizerInf(RAND_INF_GTG_MQ_SILVER_SLOPE_4));
    locationTable[RC_GTG_MQ_SILVER_SLOPE_5] =                Location::Collectable(RC_GTG_MQ_SILVER_SLOPE_5,                RCQUEST_MQ,         RCTYPE_SILVER, ACTOR_EN_G_SWITCH, SCENE_GERUDO_TRAINING_GROUND,       TWO_ACTOR_PARAMS(-1261, -923),     "RC_GTG_MQ_SILVER_SLOPE_5",                RHT_GTG_SILVER,                                          RG_BLUE_RUPEE,        SpoilerCollectionCheck::RandomizerInf(RAND_INF_GTG_MQ_SILVER_SLOPE_5));
    locationTable[RC_GTG_MQ_SILVER_LAVA_1] =                 Location::Collectable(RC_GTG_MQ_SILVER_LAVA_1,                 RCQUEST_MQ,         RCTYPE_SILVER, ACTOR_EN_G_SWITCH, SCENE_GERUDO_TRAINING_GROUND,       TWO_ACTOR_PARAMS(1560, -1861),     "RC_GTG_MQ_SILVER_LAVA_1",                 RHT_GTG_SILVER,                                          RG_BLUE_RUPEE,        SpoilerCollectionCheck::RandomizerInf(RAND_INF_GTG_MQ_SILVER_LAVA_1));
    locationTable[RC_GTG_MQ_SILVER_LAVA_2] =                 Location::Collectable(RC_GTG_MQ_SILVER_LAVA_2,                 RCQUEST_MQ,         RCTYPE_SILVER, ACTOR_EN_G_SWITCH, SCENE_GERUDO_TRAINING_GROUND,       TWO_ACTOR_PARAMS(1134, -1841),     "RC_GTG_MQ_SILVER_LAVA_2",                 RHT_GTG_SILVER,                                          RG_BLUE_RUPEE,        SpoilerCollectionCheck::RandomizerInf(RAND_INF_GTG_MQ_SILVER_LAVA_2));
    locationTable[RC_GTG_MQ_SILVER_LAVA_3] =                 Location::Collectable(RC_GTG_MQ_SILVER_LAVA_3,                 RCQUEST_MQ,         RCTYPE_SILVER, ACTOR_EN_G_SWITCH, SCENE_GERUDO_TRAINING_GROUND,       TWO_ACTOR_PARAMS(1404, -1653),     "RC_GTG_MQ_SILVER_LAVA_3",                 RHT_GTG_SILVER,                                          RG_BLUE_RUPEE,        SpoilerCollectionCheck::RandomizerInf(RAND_INF_GTG_MQ_SILVER_LAVA_3));
    locationTable[RC_GTG_MQ_SILVER_LAVA_4] =                 Location::Collectable(RC_GTG_MQ_SILVER_LAVA_4,                 RCQUEST_MQ,         RCTYPE_SILVER, ACTOR_EN_G_SWITCH, SCENE_GERUDO_TRAINING_GROUND,       TWO_ACTOR_PARAMS(1560, -1380),     "RC_GTG_MQ_SILVER_LAVA_4",                 RHT_GTG_SILVER,                                          RG_BLUE_RUPEE,        SpoilerCollectionCheck::RandomizerInf(RAND_INF_GTG_MQ_SILVER_LAVA_4));
    locationTable[RC_GTG_MQ_SILVER_LAVA_5] =                 Location::Collectable(RC_GTG_MQ_SILVER_LAVA_5,                 RCQUEST_MQ,         RCTYPE_SILVER, ACTOR_EN_G_SWITCH, SCENE_GERUDO_TRAINING_GROUND,       TWO_ACTOR_PARAMS(1083, -1374),     "RC_GTG_MQ_SILVER_LAVA_5",                 RHT_GTG_SILVER,                                          RG_BLUE_RUPEE,        SpoilerCollectionCheck::RandomizerInf(RAND_INF_GTG_MQ_SILVER_LAVA_5));
    locationTable[RC_GTG_MQ_SILVER_LAVA_6] =                 Location::Collectable(RC_GTG_MQ_SILVER_LAVA_6,                 RCQUEST_MQ,         RCTYPE_SILVER, ACTOR_EN_G_SWITCH, SCENE_GERUDO_TRAINING_GROUND,       TWO_ACTOR_PARAMS(1317, -1243),     "RC_GTG_MQ_SILVER_LAVA_6",                 RHT_GTG_SILVER,                                          RG_BLUE_RUPEE,        SpoilerCollectionCheck::RandomizerInf(RAND_INF_GTG_MQ_SILVER_LAVA_6));
    locationTable[RC_GTG_MQ_SILVER_WATER_1] =                Location::Collectable(RC_GTG_MQ_SILVER_WATER_1,                RCQUEST_MQ,         RCTYPE_SILVER, ACTOR_EN_G_SWITCH, SCENE_GERUDO_TRAINING_GROUND,       TWO_ACTOR_PARAMS(2453, -1612),     "RC_GTG_MQ_SILVER_WATER_1",                RHT_GTG_SILVER,                                          RG_BLUE_RUPEE,        SpoilerCollectionCheck::RandomizerInf(RAND_INF_GTG_MQ_SILVER_WATER_1));
    locationTable[RC_GTG_MQ_SILVER_WATER_2] =                Location::Collectable(RC_GTG_MQ_SILVER_WATER_2,                RCQUEST_MQ,         RCTYPE_SILVER, ACTOR_EN_G_SWITCH, SCENE_GERUDO_TRAINING_GROUND,       TWO_ACTOR_PARAMS(2302, -1464),     "RC_GTG_MQ_SILVER_WATER_2",                RHT_GTG_SILVER,                                          RG_BLUE_RUPEE,        SpoilerCollectionCheck::RandomizerInf(RAND_INF_GTG_MQ_SILVER_WATER_2));
    locationTable[RC_GTG_MQ_SILVER_WATER_3] =                Location::Collectable(RC_GTG_MQ_SILVER_WATER_3,                RCQUEST_MQ,         RCTYPE_SILVER, ACTOR_EN_G_SWITCH, SCENE_GERUDO_TRAINING_GROUND,       TWO_ACTOR_PARAMS(2160, -1315),     "RC_GTG_MQ_SILVER_WATER_3",                RHT_GTG_SILVER,                                          RG_BLUE_RUPEE,        SpoilerCollectionCheck::RandomizerInf(RAND_INF_GTG_MQ_SILVER_WATER_3));
    locationTable[RC_GANONS_CASTLE_MQ_SILVER_FIRE_1] =       Location::Collectable(RC_GANONS_CASTLE_MQ_SILVER_FIRE_1,       RCQUEST_MQ,         RCTYPE_SILVER, ACTOR_EN_G_SWITCH, SCENE_INSIDE_GANONS_CASTLE,         TWO_ACTOR_PARAMS(-970, -3747),     "RC_GANONS_CASTLE_MQ_SILVER_FIRE_1",       RHT_GANONS_CASTLE_SILVER,                                RG_BLUE_RUPEE,        SpoilerCollectionCheck::RandomizerInf(RAND_INF_GANONS_CASTLE_MQ_SILVER_FIRE_1));
    locationTable[RC_GANONS_CASTLE_MQ_SILVER_FIRE_2] =       Location::Collectable(RC_GANONS_CASTLE_MQ_SILVER_FIRE_2,       RCQUEST_MQ,         RCTYPE_SILVER, ACTOR_EN_G_SWITCH, SCENE_INSIDE_GANONS_CASTLE,         TWO_ACTOR_PARAMS(-1891, -2753),    "RC_GANONS_CASTLE_MQ_SILVER_FIRE_2",       RHT_GANONS_CASTLE_SILVER,                                RG_BLUE_RUPEE,        SpoilerCollectionCheck::RandomizerInf(RAND_INF_GANONS_CASTLE_MQ_SILVER_FIRE_2));
    locationTable[RC_GANONS_CASTLE_MQ_SILVER_FIRE_3] =       Location::Collectable(RC_GANONS_CASTLE_MQ_SILVER_FIRE_3,       RCQUEST_MQ,         RCTYPE_SILVER, ACTOR_EN_G_SWITCH, SCENE_INSIDE_GANONS_CASTLE,         TWO_ACTOR_PARAMS(-2044, -3354),    "RC_GANONS_CASTLE_MQ_SILVER_FIRE_3",       RHT_GANONS_CASTLE_SILVER,                                RG_BLUE_RUPEE,        SpoilerCollectionCheck::RandomizerInf(RAND_INF_GANONS_CASTLE_MQ_SILVER_FIRE_3));
    locationTable[RC_GANONS_CASTLE_MQ_SILVER_FIRE_4] =       Location::Collectable(RC_GANONS_CASTLE_MQ_SILVER_FIRE_4,       RCQUEST_MQ,         RCTYPE_SILVER, ACTOR_EN_G_SWITCH, SCENE_INSIDE_GANONS_CASTLE,         TWO_ACTOR_PARAMS(-686, -2945),     "RC_GANONS_CASTLE_MQ_SILVER_FIRE_4",       RHT_GANONS_CASTLE_SILVER,                                RG_BLUE_RUPEE,        SpoilerCollectionCheck::RandomizerInf(RAND_INF_GANONS_CASTLE_MQ_SILVER_FIRE_4));
    locationTable[RC_GANONS_CASTLE_MQ_SILVER_FIRE_5] =       Location::Collectable(RC_GANONS_CASTLE_MQ_SILVER_FIRE_5,       RCQUEST_MQ,         RCTYPE_SILVER, ACTOR_EN_G_SWITCH, SCENE_INSIDE_GANONS_CASTLE,         TWO_ACTOR_PARAMS(-1655, -2133),    "RC_GANONS_CASTLE_MQ_SILVER_FIRE_5",       RHT_GANONS_CASTLE_SILVER,                                RG_BLUE_RUPEE,        SpoilerCollectionCheck::RandomizerInf(RAND_INF_GANONS_CASTLE_MQ_SILVER_FIRE_5));
    locationTable[RC_GANONS_CASTLE_MQ_SILVER_WATER_1] =      Location::Collectable(RC_GANONS_CASTLE_MQ_SILVER_WATER_1,      RCQUEST_MQ,         RCTYPE_SILVER, ACTOR_EN_G_SWITCH, SCENE_INSIDE_GANONS_CASTLE,         TWO_ACTOR_PARAMS(2757, -765),      "RC_GANONS_CASTLE_MQ_SILVER_WATER_1",      RHT_GANONS_CASTLE_SILVER,                                RG_BLUE_RUPEE,        SpoilerCollectionCheck::RandomizerInf(RAND_INF_GANONS_CASTLE_MQ_SILVER_WATER_1));
    locationTable[RC_GANONS_CASTLE_MQ_SILVER_WATER_2] =      Location::Collectable(RC_GANONS_CASTLE_MQ_SILVER_WATER_2,      RCQUEST_MQ,         RCTYPE_SILVER, ACTOR_EN_G_SWITCH, SCENE_INSIDE_GANONS_CASTLE,         TWO_ACTOR_PARAMS(2912, -971),      "RC_GANONS_CASTLE_MQ_SILVER_WATER_2",      RHT_GANONS_CASTLE_SILVER,                                RG_BLUE_RUPEE,        SpoilerCollectionCheck::RandomizerInf(RAND_INF_GANONS_CASTLE_MQ_SILVER_WATER_2));
    locationTable[RC_GANONS_CASTLE_MQ_SILVER_WATER_3] =      Location::Collectable(RC_GANONS_CASTLE_MQ_SILVER_WATER_3,      RCQUEST_MQ,         RCTYPE_SILVER, ACTOR_EN_G_SWITCH, SCENE_INSIDE_GANONS_CASTLE,         TWO_ACTOR_PARAMS(2905, -1478),     "RC_GANONS_CASTLE_MQ_SILVER_WATER_3",      RHT_GANONS_CASTLE_SILVER,                                RG_BLUE_RUPEE,        SpoilerCollectionCheck::RandomizerInf(RAND_INF_GANONS_CASTLE_MQ_SILVER_WATER_3));
    locationTable[RC_GANONS_CASTLE_MQ_SILVER_WATER_4] =      Location::Collectable(RC_GANONS_CASTLE_MQ_SILVER_WATER_4,      RCQUEST_MQ,         RCTYPE_SILVER, ACTOR_EN_G_SWITCH, SCENE_INSIDE_GANONS_CASTLE,         TWO_ACTOR_PARAMS(3253, -649),      "RC_GANONS_CASTLE_MQ_SILVER_WATER_4",      RHT_GANONS_CASTLE_SILVER,                                RG_BLUE_RUPEE,        SpoilerCollectionCheck::RandomizerInf(RAND_INF_GANONS_CASTLE_MQ_SILVER_WATER_4));
    locationTable[RC_GANONS_CASTLE_MQ_SILVER_WATER_5] =      Location::Collectable(RC_GANONS_CASTLE_MQ_SILVER_WATER_5,      RCQUEST_MQ,         RCTYPE_SILVER, ACTOR_EN_G_SWITCH, SCENE_INSIDE_GANONS_CASTLE,         TWO_ACTOR_PARAMS(2905, -1263),     "RC_GANONS_CASTLE_MQ_SILVER_WATER_5",      RHT_GANONS_CASTLE_SILVER,                                RG_BLUE_RUPEE,        SpoilerCollectionCheck::RandomizerInf(RAND_INF_GANONS_CASTLE_MQ_SILVER_WATER_5));
    locationTable[RC_GANONS_CASTLE_MQ_SILVER_SHADOW_1] =     Location::Collectable(RC_GANONS_CASTLE_MQ_SILVER_SHADOW_1,     RCQUEST_MQ,         RCTYPE_SILVER, ACTOR_EN_G_SWITCH, SCENE_INSIDE_GANONS_CASTLE,         TWO_ACTOR_PARAMS(1322, -2262),     "RC_GANONS_CASTLE_MQ_SILVER_SHADOW_1",     RHT_GANONS_CASTLE_SILVER,                                RG_BLUE_RUPEE,        SpoilerCollectionCheck::RandomizerInf(RAND_INF_GANONS_CASTLE_MQ_SILVER_SHADOW_1));
    locationTable[RC_GANONS_CASTLE_MQ_SILVER_SHADOW_2] =     Location::Collectable(RC_GANONS_CASTLE_MQ_SILVER_SHADOW_2,     RCQUEST_MQ,         RCTYPE_SILVER, ACTOR_EN_G_SWITCH, SCENE_INSIDE_GANONS_CASTLE,         TWO_ACTOR_PARAMS(1279, -3111),     "RC_GANONS_CASTLE_MQ_SILVER_SHADOW_2",     RHT_GANONS_CASTLE_SILVER,                                RG_BLUE_RUPEE,        SpoilerCollectionCheck::RandomizerInf(RAND_INF_GANONS_CASTLE_MQ_SILVER_SHADOW_2));
    locationTable[RC_GANONS_CASTLE_MQ_SILVER_SHADOW_3] =     Location::Collectable(RC_GANONS_CASTLE_MQ_SILVER_SHADOW_3,     RCQUEST_MQ,         RCTYPE_SILVER, ACTOR_EN_G_SWITCH, SCENE_INSIDE_GANONS_CASTLE,         TWO_ACTOR_PARAMS(1529, -4117),     "RC_GANONS_CASTLE_MQ_SILVER_SHADOW_3",     RHT_GANONS_CASTLE_SILVER,                                RG_BLUE_RUPEE,        SpoilerCollectionCheck::RandomizerInf(RAND_INF_GANONS_CASTLE_MQ_SILVER_SHADOW_3));
    locationTable[RC_GANONS_CASTLE_MQ_SILVER_SHADOW_4] =     Location::Collectable(RC_GANONS_CASTLE_MQ_SILVER_SHADOW_4,     RCQUEST_MQ,         RCTYPE_SILVER, ACTOR_EN_G_SWITCH, SCENE_INSIDE_GANONS_CASTLE,         TWO_ACTOR_PARAMS(1829, -4071),     "RC_GANONS_CASTLE_MQ_SILVER_SHADOW_4",     RHT_GANONS_CASTLE_SILVER,                                RG_BLUE_RUPEE,        SpoilerCollectionCheck::RandomizerInf(RAND_INF_GANONS_CASTLE_MQ_SILVER_SHADOW_4));
    locationTable[RC_GANONS_CASTLE_MQ_SILVER_SHADOW_5] =     Location::Collectable(RC_GANONS_CASTLE_MQ_SILVER_SHADOW_5,     RCQUEST_MQ,         RCTYPE_SILVER, ACTOR_EN_G_SWITCH, SCENE_INSIDE_GANONS_CASTLE,         TWO_ACTOR_PARAMS(1100, -2554),     "RC_GANONS_CASTLE_MQ_SILVER_SHADOW_5",     RHT_GANONS_CASTLE_SILVER,                                RG_BLUE_RUPEE,        SpoilerCollectionCheck::RandomizerInf(RAND_INF_GANONS_CASTLE_MQ_SILVER_SHADOW_5));
    // clang-format on
}

static RegisterShipInitFunc registerShuffleSilver(RegisterShuffleSilver, { "IS_RANDO" });
static RegisterShipInitFunc registerShuffleSilverLocations(Rando::StaticData::RegisterSilverLocations);
