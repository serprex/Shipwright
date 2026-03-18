#include "SohGfxDebuggerWindow.h"
#include "soh/OTRGlobals.h"

void SohGfxDebuggerWindow::DrawElement() {
    ImGui::BeginDisabled(CVarGetInteger(CVAR_SETTING("DisableChanges"), 0));
    ImGui::PushFont(OTRGlobals::Instance->fontMonoLarger);
    GfxDebuggerWindow::DrawElement();
    ImGui::PopFont();
    ImGui::EndDisabled();
}
