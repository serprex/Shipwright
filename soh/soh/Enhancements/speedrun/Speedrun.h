#pragma once

#include <libultraship/libultra/types.h>

#ifdef __cplusplus
extern "C" {
#endif
struct GameState;
struct FileChooseContext;

void FileChoose_UpdateSpeedrunMenu(struct GameState* gameState);
void FileChoose_DrawSpeedrunMenuWindowContents(struct FileChooseContext* fileChooseContext);

// Applies the preset picked in the file select menu and snapshots the resulting settings onto the new file.
void Speedrun_InitSaveFile(void);

// Gyro aiming is not allowed in a speedrun, so this reads back as 0 there and unchanged everywhere else.
f32 Ship_FilterGyro(f32 gyroAxis);
#ifdef __cplusplus
};

#include "z64save.h"

// Registers the save section and the hooks that put settings back when a run is left. Call once at startup.
void Speedrun_Register();

// Whether the loaded file is a speedrun file, for code that can't reach gSaveContext.
bool Speedrun_IsActive();

void Speedrun_SaveSaveSection(SaveContext* saveContext, int sectionID, bool fullSave);
void Speedrun_LoadSaveSection();

// Unlocks the menu and puts back the settings that were replaced by a speedrun file. Safe to call when nothing was
// replaced.
void Speedrun_RestoreSettings();

namespace Ship {
class GuiWindow;
}

// Called by the menu every frame, before the other windows draw. While a speedrun file is loaded it keeps every window
// a run may not show hidden, and turns opening the menu into toggling the run info windows. True while locked, meaning
// the menu must not draw.
bool Speedrun_EnforceGuiLockdown(Ship::GuiWindow& menu);
#endif

#define SPEEDRUN_MAX_OPTIONS_ON_SCREEN 6
