#include "controller.h"

#include <FEHUtility.h>

#include <algorithm>

#include "drivetrain.h"
#include "gui.h"
#include "logging.h"

bool activeSleep(float seconds) {
    float startTime = TimeNow();
    float currTime = TimeNow();

    while (startTime + seconds > currTime) {
        Sleep(std::min(TICK_INTERVAL, currTime - startTime + seconds));
        drivetrain.update();
        ui.update();

        if (ui.wantsStop()) {
            logger.log("Stopping", "gui");
            drivetrain.stop();
            ui.openView(MainUI::MenuView);
            return false;
        }

        currTime = TimeNow();
    }

    return true;
}

bool tick() {
    ui.update();
    drivetrain.update();

    if (ui.wantsStop()) {
        logger.log("Stopping", "gui");
        drivetrain.stop();
        ui.openView(MainUI::MenuView);
        return false;
    }

    return true;
}

bool driveDistance(Drivetrain::Axis axis, float distance, bool strafe,
                   float precision) {
    drivetrain.driveAxisDistance(axis, distance, strafe);
    while (!drivetrain.distanceInThreshold(precision)) {
        Sleep(TICK_INTERVAL);
        if (!tick()) {
            break;
        };
    }

    drivetrain.stop();
    activeSleep(0.5);

    return true;
}

bool rotateClockwise(float degrees, float precision) {
    drivetrain.rotateClockwiseDegrees(degrees);
    while (!drivetrain.rotationInThreshold(precision)) {
        Sleep(TICK_INTERVAL);
        tick();
    }
    drivetrain.stop();
    activeSleep(0.5);
}
