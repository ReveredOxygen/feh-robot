#include "controller.h"

#include <FEHUtility.h>

#include <algorithm>

#include "drivetrain.h"
#include "gui.h"
#include "logging.h"

void activeSleep(float seconds) {
    float startTime = TimeNow();
    float currTime = TimeNow();

    while (startTime + seconds > currTime) {
        Sleep(std::min(0.1f, currTime - startTime + seconds));
        drivetrain.update();

        if (ui.wantsStop()) {
            logger.log("Stopping", "gui");
            drivetrain.stop();
            ui.openView(MainUI::MenuView);
            return;
        }
    }
}
