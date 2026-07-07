#include <libultraship/bridge.h>
#include "soh/Enhancements/game-interactor/GameInteractor.h"
#include "soh/ShipInit.hpp"
#include "soh/OTRGlobals.h"

extern "C" {
#include "z64.h"
#include "macros.h"
#include "functions.h"
#include "variables.h"
#include "soh/ResourceManagerHelpers.h"
#include "assets/objects/gameplay_keep/gameplay_keep.h"

void SkelAnime_InitLink(PlayState* play, SkelAnime* skelAnime, FlexSkeletonHeader* skeletonHeaderSeg,
                        LinkAnimationHeader* animation, s32 flags, Vec3s* jointTable, Vec3s* morphTable,
                        s32 limbBufCount);
extern PlayState* gPlayState;
}

// MM player forms, matching 2Ship's PlayerTransformation values where it matters.
typedef enum {
    PLAYER_SHIPFORM_HUMAN,
    PLAYER_SHIPFORM_GORON,
    PLAYER_SHIPFORM_ZORA,
    PLAYER_SHIPFORM_MAX,
} PlayerShipForm;

// MM Goron/Zora Link skeletons and idle anims, loaded from a user-provided mm.o2r (2Ship) in the mods folder.
//
// These OTR path strings MUST be even-aligned: SkelAnime_InitLink / LinkAnimation_Change hand the pointer to
// ResourceMgr_OTRSigCheck to tell an OTR path apart from an already-resolved resource pointer, and that check
// rejects any odd address (`(i & 1) == 1`) before it ever looks at the "__OTR__" prefix. A bare string literal
// can land on an odd address, in which case the path is treated as a raw pointer and ->segment reads garbage
// (segfault in AnimationContext_SetLoadFrame). alignas(2) guarantees the low bit is clear.
alignas(2) static const char sSkelPathGoron[] = "__OTR__objects/object_link_goron/gLinkGoronSkel";
alignas(2) static const char sSkelPathZora[] = "__OTR__objects/object_link_zora/gLinkZoraSkel";
alignas(2) static const char sWaitPathGoron[] = "__OTR__objects/gameplay_keep/gPlayerAnim_pg_wait";
alignas(2) static const char sWaitPathZora[] = "__OTR__objects/gameplay_keep/gPlayerAnim_pz_wait";

static const char* sFormSkelPaths[PLAYER_SHIPFORM_MAX] = {
    nullptr, // human uses gPlayerSkelHeaders[linkAge]
    sSkelPathGoron,
    sSkelPathZora,
};

static const char* sFormWaitAnimPaths[PLAYER_SHIPFORM_MAX] = {
    nullptr, // human uses gPlayerAnim_link_normal_wait
    sWaitPathGoron,
    sWaitPathZora,
};

static bool FormAssetsAvailable() {
    return ResourceMgr_FileExists(sFormSkelPaths[PLAYER_SHIPFORM_GORON]) &&
           ResourceMgr_FileExists(sFormSkelPaths[PLAYER_SHIPFORM_ZORA]);
}

static void ApplyFormSkeleton(PlayState* play, Player* player, PlayerShipForm form) {
    FlexSkeletonHeader* skel = form == PLAYER_SHIPFORM_HUMAN
                                   ? gPlayerSkelHeaders[gSaveContext.linkAge]
                                   : (FlexSkeletonHeader*)sFormSkelPaths[form];
    LinkAnimationHeader* waitAnim = form == PLAYER_SHIPFORM_HUMAN
                                        ? (LinkAnimationHeader*)gPlayerAnim_link_normal_wait
                                        : (LinkAnimationHeader*)sFormWaitAnimPaths[form];

    ResourceMgr_UnregisterSkeleton(&player->skelAnime);
    ResourceMgr_UnregisterSkeleton(&player->upperSkelAnime);
    SkelAnime_InitLink(play, &player->skelAnime, skel, waitAnim, 9, player->jointTable, player->morphTable,
                       PLAYER_LIMB_MAX);
    SkelAnime_InitLink(play, &player->upperSkelAnime, skel, waitAnim, 9, player->upperJointTable,
                       player->upperMorphTable, PLAYER_LIMB_MAX);
}

// Phase 0 spike: hot-swap the player's skeleton to MM Goron/Zora Link via the developer
// CVar gDeveloperTools.MMFormSwap (0 = human, 1 = Goron, 2 = Zora). Validates that 2Ship
// skeletons and animations load and render on OOT's SkelAnime_Link system.
static PlayerShipForm sAppliedForm = PLAYER_SHIPFORM_HUMAN;

static void RegisterTransformationMasks() {
    // Player_InitCommon re-inits the skeleton to human on every scene load; it ends in this
    // hook, which marks the form stale so the next OnPlayerUpdate re-applies it. Our own
    // ApplyFormSkeleton also lands here, so sAppliedForm is assigned after it returns.
    GameInteractor::Instance->RegisterGameHook<GameInteractor::OnLinkSkeletonInit>(
        []() { sAppliedForm = PLAYER_SHIPFORM_HUMAN; });

    GameInteractor::Instance->RegisterGameHook<GameInteractor::OnPlayerUpdate>([]() {
        s32 wanted = CVarGetInteger(CVAR_DEVELOPER_TOOLS("MMFormSwap"), PLAYER_SHIPFORM_HUMAN);
        if (wanted < PLAYER_SHIPFORM_HUMAN || wanted >= PLAYER_SHIPFORM_MAX) {
            wanted = PLAYER_SHIPFORM_HUMAN;
        }
        if (wanted == sAppliedForm) {
            return;
        }
        if (wanted != PLAYER_SHIPFORM_HUMAN && !FormAssetsAvailable()) {
            return;
        }

        ApplyFormSkeleton(gPlayState, GET_PLAYER(gPlayState), (PlayerShipForm)wanted);
        sAppliedForm = (PlayerShipForm)wanted;
    });
}

static RegisterShipInitFunc initFunc(RegisterTransformationMasks);
