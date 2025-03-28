#include <FEHLCD.h>
#include <FEHUtility.h>

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
    // while (true) {
    //     Sleep(0.1);
    //     LCD.WriteRC(Hardware::centerOptosensor.Value(), 0, 0);
    // }

    // Hardware::arm.TouchCalibrate();
    Hardware::arm.SetMax(2440);
    Hardware::arm.SetMin(540);

    ui.mainMenu =
        MenuBuilder()
            .withOption("View Logs", []() { ui.openView(MainUI::LogView); })
            ->withOption("Check Bat", []() {})
            ->withSubmenu("Milestones", milestones::getMenu())
            ->withSubmenu("Demos", demos::getMenu())
            ->withOption("Arm", []() { Hardware::arm.SetDegree(20); })
            ->build();

    ui.openView(MainUI::MenuView);

    logger.log("Started gui", "gui");

    while (1) {
        Sleep(0.1);
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
