#include "SohStatsWindow.h"
#include "soh/OTRGlobals.h"

void SohStatsWindow::DrawElement() {
    const float framerate = ImGui::GetIO().Framerate;
    const float deltatime = ImGui::GetIO().DeltaTime;
    ImGui::PushFont(OTRGlobals::Instance->fontMonoLarger);
    StatsWindow::DrawElement();
    ImGui::PopFont();
}
