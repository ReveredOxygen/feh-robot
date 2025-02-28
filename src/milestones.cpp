#include "milestones.h"

#include <FEHUtility.h>

#include "controller.h"
#include "drivetrain.h"
#include "gui.h"
#include "logging.h"

namespace milestones {

void milestone1Part2();
void milestone1Part3();

Menu* getMenu() {
    return MenuBuilder()
        .withSubmenu("Milestone 1", MenuBuilder()
                                        .withOption("Part 2", milestone1Part2)
                                        ->withOption("Part 3", milestone1Part3)
                                        ->build())
        ->build();
}

void milestone1Part2() {
    logger.log("Begin Milestone 1 Part 2", "gui");
    ui.openView(MainUI::LogView);

    logger.log("Drive Forward", "mile");
    drivetrain.driveAxis(Drivetrain::forward, 6);
    activeSleep(5);
    logger.log("Done", "mile");
    drivetrain.stop();
}

void milestone1Part3() {
    logger.log("Begin Milestone 1 Part 3", "gui");
    ui.openView(MainUI::LogView);

    logger.log("Drive Forward", "mile");
    drivetrain.driveAxis(Drivetrain::forward, 6, true);
    activeSleep(5);
    logger.log("Back down", "mile");
    drivetrain.driveAxis(Drivetrain::forward, -6, true);
    activeSleep(5);
    logger.log("Done", "mile");
    drivetrain.stop();
}

}   // namespace milestones
