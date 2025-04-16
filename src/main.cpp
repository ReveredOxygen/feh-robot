#include <FEHLCD.h>
#include <FEHRCS.h>
#include <FEHUtility.h>

#include "controller.h"
#include "demos.h"
#include "drivetrain.h"
#include "gui.h"
#include "hardware.h"
#include "milestones.h"

void doNothing() {
    logger.log("doing nothing", "idk");
}

void doSomething() {
    logger.log("doing something", "idk", logging::Warning);
}

int main(void) {
    Hardware::arm.SetMax(2440);
    Hardware::arm.SetMin(540);

    ui.mainMenu =
        MenuBuilder()
            .withOption("View Logs", []() { ui.openView(MainUI::LogView); })
            ->withOption("Check Bat", []() {})
            ->withOption("RCS", []() { RCS.InitializeTouchMenu("1020C1DXY"); })
            ->withSubmenu("Milestones", milestones::getMenu())
            ->withSubmenu("Demos", demos::getMenu())
            ->withOption(
                "Arm",
                []() {
                    Hardware::arm.SetDegree(Hardware::APPLE_GRAB_ROTATION);
                })
            ->build();

    ui.openView(MainUI::MenuView);

    logger.log("Started gui", "gui");

    loadCalibration(LINE_BLUE);
    loadCalibration(LINE_BLACK_OUTLINED);

    while (1) {
        Sleep(TICK_INTERVAL);
        drivetrain.update();

        ui.update();

        if (ui.wantsStop()) {
            logger.log("Stopping", "gui");
            drivetrain.stop();
            ui.openView(MainUI::MenuView);
        }
    }
    // comments

    return 0;
}
