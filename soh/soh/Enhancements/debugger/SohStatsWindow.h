#ifndef SOH_STATS_H
#define SOH_STATS_H

#include <ship/window/gui/StatsWindow.h>

class SohStatsWindow final : public Ship::StatsWindow {
  public:
    using StatsWindow::StatsWindow;

  protected:
    void InitElement() override;
    void DrawElement() override;
    void UpdateElement() override;
};

#endif // SOH_STATS_H
