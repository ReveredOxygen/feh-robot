#include "milestones.h"

#include <FEHUtility.h>

#include "controller.h"
#include "drivetrain.h"
#include "gui.h"
#include "hardware.h"
#include "logging.h"

namespace milestones {

void milestone1Part2();
void milestone1Part3();
void milestone2();

Menu* getMenu() {
    return MenuBuilder()
        .withSubmenu("Milestone 1", MenuBuilder()
                                        .withOption("Part 2", milestone1Part2)
                                        ->withOption("Part 3", milestone1Part3)
                                        ->build())
        ->withOption("Milestone 2", milestone2)
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

void milestone2() {
    logger.log("Begin Milestone 2", "gui");
    ui.openView(MainUI::LogView);

    drivetrain.setMaxSpeed(6);

    drivetrain.driveAxisDistance(Drivetrain::forward, -6, true);
    while (!drivetrain.distanceInThreshold(0.1)) {
        Sleep(0.1);
        tick();
    }

    drivetrain.stop();
    activeSleep(0.5);

    drivetrain.driveAxisDistance(Drivetrain::forward, 4);
    while (!drivetrain.distanceInThreshold(0.1)) {
        Sleep(0.1);
        tick();
    }

    drivetrain.stop();
    activeSleep(0.5);

    drivetrain.rotateClockwiseDegrees(120);
    while (!drivetrain.rotationInThreshold(0.5)) {
        Sleep(0.1);
        tick();
    }

    // Drive up ramp
    drivetrain.setMaxSpeed(14);
    drivetrain.driveAxisDistance(Drivetrain::left, -38, true);
    while (!drivetrain.distanceInThreshold(0.1)) {
        Sleep(0.1);
        tick();
    }

    drivetrain.stop();
    activeSleep(0.5);

    // Drive to indicator
    drivetrain.setMaxSpeed(6);
    drivetrain.driveAxisDistance(Drivetrain::left, -18);
    while (!drivetrain.distanceInThreshold(0.1)) {
        Sleep(0.1);
        tick();
        float light = Hardware::cdsCell.Value();
        if (light < 2) {
            logger.log(vformat("light %.2f", light), "mile");
            break;
        }
    }

    drivetrain.stop();
    activeSleep(0.5);

    // Assume the light is blue
    drivetrain.driveAxisDistance(Drivetrain::left, 2, true);
    while (!drivetrain.distanceInThreshold(0.1)) {
        Sleep(0.1);
        tick();
    }

    drivetrain.stop();
    activeSleep(0.5);

    // Ram into the button
    drivetrain.setMaxSpeed(10);
    drivetrain.driveAxisDistance(Drivetrain::left, -10);
    while (!drivetrain.distanceInThreshold(0.1)) {
        Sleep(0.1);
        tick();
    }

    drivetrain.stop();
    drivetrain.setMaxSpeed(6);
    activeSleep(0.5);

    // Drive back over
    drivetrain.driveAxisDistance(Drivetrain::left, 25);
    while (!drivetrain.distanceInThreshold(0.1)) {
        Sleep(0.1);
        tick();
    }

    drivetrain.stop();
    drivetrain.setMaxSpeed(6);
    activeSleep(0.5);

    // Go back down
    drivetrain.driveAxisDistance(Drivetrain::left, 30, true);
    while (!drivetrain.distanceInThreshold(0.1)) {
        Sleep(0.1);
        tick();
    }

    drivetrain.stop();
    logger.log("Milestone 2 Done", "mile");
}

}   // namespace milestones
