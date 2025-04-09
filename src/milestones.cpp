#include "milestones.h"

#include <FEHBuzzer.h>
#include <FEHLCD.h>
#include <FEHUtility.h>

#include "controller.h"
#include "drivetrain.h"
#include "gui.h"
#include "hardware.h"
#include "logging.h"

#define CHECK(x)           \
    if (!(x)) [[unlikely]] \
    goto end

namespace milestones {

void milestone1Part2();
void milestone1Part3();
void milestone2();
void milestone3();
void milestone4();
void simpleMilestone4();
void milestone5();
void showcase();
void showcase2();

Menu* getMenu() {
    return MenuBuilder()
        .withSubmenu("Milestone 1", MenuBuilder()
                                        .withOption("Part 2", milestone1Part2)
                                        ->withOption("Part 3", milestone1Part3)
                                        ->build())
        ->withOption("Milestone 2", milestone2)
        ->withOption("Milestone 3", milestone3)
        // ->withOption("Milestone 4", milestone4)
        ->withOption("EZ Milestone 4", simpleMilestone4)
        ->withOption("Milestone 5", milestone5)
        ->withSubmenu("Showcase",
                      MenuBuilder().withOption("Confirm", showcase)->build())
        ->withOption("Showcase 2", showcase2)
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

    while (Hardware::cdsCell.Value() > 2);
    Sleep(1.);

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

    drivetrain.rotateClockwiseDegrees(121);
    while (!drivetrain.rotationInThreshold(0.5)) {
        Sleep(0.1);
        tick();
    }

    // Drive up ramp
    drivetrain.setMaxSpeed(14);
    drivetrain.driveAxisDistance(Drivetrain::left, -37, true);
    while (!drivetrain.distanceInThreshold(0.1)) {
        Sleep(0.1);
        tick();
    }
    drivetrain.setMaxSpeed(6);

    // drivetrain.stop();
    // activeSleep(0.5);

    // drivetrain.rotateClockwiseDegrees(3);
    // while (!drivetrain.rotationInThreshold(0.5)) {
    //     Sleep(0.1);
    //     tick();
    // }

    drivetrain.stop();
    activeSleep(0.5);

    // Drive to indicator
    float light = 100;
    drivetrain.setMaxSpeed(6);
    drivetrain.driveAxisDistance(Drivetrain::left, -18);
    while (!drivetrain.distanceInThreshold(0.1)) {
        Sleep(0.1);
        tick();
        if (light < 2) {
            light = Hardware::cdsCell.Value();
            logger.log(vformat("light %.2f", light), "mile");
            break;
        }
    }

    drivetrain.stop();
    activeSleep(0.5);

    if (light > 0.7) {
        // Assume the light is blue
        logger.log("BLUE", "mile");
        drivetrain.driveAxisDistance(Drivetrain::left, 1.75, true);
        while (!drivetrain.distanceInThreshold(0.1)) {
            Sleep(0.1);
            tick();
        }
    } else {
        // Light is def red
        logger.log("RED", "mile");
        drivetrain.driveAxisDistance(Drivetrain::left, -1, true);
        while (!drivetrain.distanceInThreshold(0.1)) {
            Sleep(0.1);
            tick();
        }

        drivetrain.stop();
        activeSleep(0.5);

        drivetrain.driveAxisDistance(Drivetrain::left, 3.5, true);
        while (!drivetrain.distanceInThreshold(0.1)) {
            Sleep(0.1);
            tick();
        }
    }

    drivetrain.stop();
    activeSleep(0.5);

    // Ram into the button
    drivetrain.setMaxSpeed(10);
    drivetrain.driveAxisDistance(Drivetrain::left, -5);
    while (!drivetrain.distanceInThreshold(0.1)) {
        Sleep(0.1);
        tick();
    }

    drivetrain.stop();
    drivetrain.setMaxSpeed(6);
    activeSleep(0.5);

    // Drive back over
    drivetrain.driveAxisDistance(Drivetrain::left, 20);
    while (!drivetrain.distanceInThreshold(0.1)) {
        Sleep(0.1);
        tick();
    }

    drivetrain.stop();
    activeSleep(0.5);

    // Go back down
    drivetrain.setMaxSpeed(10);
    drivetrain.driveAxisDistance(Drivetrain::left, 35, true);
    while (!drivetrain.distanceInThreshold(0.1)) {
        Sleep(0.1);
        tick();
    }

    drivetrain.stop();
    logger.log("Milestone 2 Done", "mile");
}

void milestone3() {
    logger.log("Begin Milestone 3", "gui");
    ui.openView(MainUI::LogView);

    Buzzer.Beep();

    while (Hardware::cdsCell.Value() > 2);
    Sleep(1.);

    drivetrain.setMaxSpeed(6);

    drivetrain.rotateClockwiseDegrees(13);
    while (!drivetrain.rotationInThreshold(0.5)) {
        Sleep(0.1);
        tick();
    }

    drivetrain.stop();
    activeSleep(0.5);

    // Away from button
    drivetrain.driveAxisDistance(Drivetrain::forward, -6, true);
    while (!drivetrain.distanceInThreshold(0.1)) {
        Sleep(0.1);
        tick();
    }

    drivetrain.stop();
    activeSleep(0.5);

    // Towards wall
    drivetrain.driveAxisDistance(Drivetrain::forward, 4.5);
    while (!drivetrain.distanceInThreshold(0.1)) {
        Sleep(0.1);
        tick();
    }

    drivetrain.stop();
    activeSleep(0.5);

    drivetrain.rotateClockwiseDegrees(-115);
    while (!drivetrain.rotationInThreshold(0.5)) {
        Sleep(0.1);
        tick();
    }

    drivetrain.stop();
    activeSleep(0.5);

    // Drive up ramp
    drivetrain.setMaxSpeed(14);
    drivetrain.driveAxisDistance(Drivetrain::right, -37, true);
    while (!drivetrain.distanceInThreshold(0.1)) {
        Sleep(0.1);
        tick();
    }
    drivetrain.setMaxSpeed(6);

    drivetrain.stop();
    activeSleep(0.5);

    // Align with window
    drivetrain.setMaxSpeed(6);
    drivetrain.driveAxisDistance(Drivetrain::right, -11);
    while (!drivetrain.distanceInThreshold(0.1)) {
        Sleep(0.1);
        tick();
    }

    drivetrain.stop();
    activeSleep(0.5);

    // Spin to face window
    drivetrain.rotateClockwiseDegrees(88);
    while (!drivetrain.rotationInThreshold(0.5)) {
        Sleep(0.1);
        tick();
    }

    drivetrain.stop();
    activeSleep(0.5);

    // Drive to window
    drivetrain.setMaxSpeed(6);
    drivetrain.driveAxisDistance(Drivetrain::right, 9);
    while (!drivetrain.distanceInThreshold(0.1)) {
        Sleep(0.1);
        tick();
    }

    drivetrain.stop();
    activeSleep(0.5);

    // Open window
    drivetrain.setMaxSpeed(8);
    drivetrain.driveAxisDistance(Drivetrain::right, 8, true);
    while (!drivetrain.distanceInThreshold(0.1)) {
        Sleep(0.1);
        tick();
    }

    drivetrain.stop();
    activeSleep(0.5);

    // Realign
    drivetrain.setMaxSpeed(4);
    drivetrain.rotateClockwiseDegrees(10);
    while (!drivetrain.rotationInThreshold(0.5)) {
        Sleep(0.1);
        tick();
    }

    drivetrain.stop();
    activeSleep(0.5);

    drivetrain.driveAxisDistance(Drivetrain::right, 2, false);
    while (!drivetrain.distanceInThreshold(0.1)) {
        Sleep(0.1);
        tick();
    }

    drivetrain.stop();
    activeSleep(0.5);

    // Close window
    drivetrain.setMaxSpeed(8);
    drivetrain.driveAxisDistance(Drivetrain::right, -8, true);
    while (!drivetrain.distanceInThreshold(0.1)) {
        Sleep(0.1);
        tick();
    }

    drivetrain.stop();
    activeSleep(0.5);

    drivetrain.stop();
    logger.log("Milestone 3 Done", "mile");
}

void milestone4() {
    logger.log("Begin Normal Milestone 4", "gui");
    ui.openView(MainUI::LogView);

    drivetrain.setMaxSpeed(6);

    lineFollow(LINE_BLACK_OUTLINED);

    lineFollow(LINE_BLACK_OUTLINED, true);

    drivetrain.stop();
    logger.log("End Normal Milestone 4", "gui");
    return;
}

void simpleMilestone4() {
    logger.log("Begin Milestone 4", "gui");
    ui.openView(MainUI::LogView);

    Buzzer.Beep();

    while (Hardware::cdsCell.Value() > 2);
    Sleep(1.);

    drivetrain.setMaxSpeed(6);

    rotateClockwise(13);

    // Away from button
    driveDistance(Drivetrain::forward, -6, true);

    rotateClockwise(-54);

    // Towards bucket a bit
    driveDistance(Drivetrain::left, 10);

    // Align with stump
    driveDistance(Drivetrain::left, 7.5, true);

    // Prepare arm
    Hardware::arm.SetDegree(20);

    activeSleep(1.5);

    // Hook it
    driveDistance(Drivetrain::left, 6);

    // Lift it
    Hardware::arm.SetDegree(65);

    // Retreat
    driveDistance(Drivetrain::left, -8);

    // Back off to get to ramp
    driveDistance(Drivetrain::left, -6, true);

    // Align with ramp
    driveDistance(Drivetrain::left, -13);

    rotateClockwise(90);

    // Drive up ramp
    drivetrain.setMaxSpeed(10);
    driveDistance(Drivetrain::left, 40);
    drivetrain.setMaxSpeed(6);

    rotateClockwise(20);

    Hardware::arm.Off();

    logger.log("End Milestone 4", "mile");
}

void milestone5() {
    logger.log("Begin Milestone 5", "gui");
    ui.openView(MainUI::LogView);

    Buzzer.Beep();

    while (Hardware::cdsCell.Value() > 2);
    Sleep(1.);

    drivetrain.setMaxSpeed(6);

    rotateClockwise(10 + 60);

    // Away from button
    driveDistance(Drivetrain::right, 6, false);

    // Align
    driveDistance(Drivetrain::right, -3, true);

    // Mate with compost
    driveDistance(Drivetrain::right, 6, false);

    Hardware::forkMotor.SetPercent(25);
    activeSleep(6);
    Hardware::forkMotor.SetPercent(0);

    activeSleep(2);

    Hardware::forkMotor.SetPercent(-25);
    activeSleep(6);
    Hardware::forkMotor.SetPercent(0);

    // Back to button
    driveDistance(Drivetrain::right, -13, false);

    Hardware::arm.Off();
    logger.log("End Milestone 4", "mile");
}

void showcase() {
    logger.log("Begin showcase", "gui");
    ui.openView(MainUI::LogView);

    drivetrain.setMaxSpeed(6);

    Buzzer.Beep();

    while (Hardware::cdsCell.Value() > 2);
    // Sleep(3.);

    pauseTime = 0;

    CHECK(driveDistance(Drivetrain::left, 1, true));

    pauseTime = 0.5;

    CHECK(driveDistance(Drivetrain::left, -2, false));

    CHECK(driveDistance(Drivetrain::left, 2, false));

    //
    // Compost bin
    //

    CHECK(rotateClockwise(5 + 60));

    // Away from button
    CHECK(driveDistance(Drivetrain::right, 6, false));

    // Align with compost
    CHECK(driveDistance(Drivetrain::right, -3.2, true));

    // Mate with compost
    CHECK(driveDistance(Drivetrain::right, 6, false));

    Hardware::forkMotor.SetPercent(50);
    CHECK(activeSleep(3));
    Hardware::forkMotor.SetPercent(0);

    CHECK(activeSleep(pauseTime));

    Hardware::forkMotor.SetPercent(-50);
    CHECK(activeSleep(3));
    Hardware::forkMotor.SetPercent(0);

    //
    // Collect apple bucket
    //

    // Detach from compost
    CHECK(driveDistance(Drivetrain::right, -3, false));

    // Align with stump
    CHECK(driveDistance(Drivetrain::right, 16, true));

    // Rotate to face stump
    CHECK(rotateClockwise(-112));

    // Drive to get to the line
    CHECK(driveDistance(Drivetrain::left, 5, false));

    // Align with the line
    CHECK(lineFollow(LINE_BLACK_OUTLINED, false, 0));

    // Back up keeping alignment
    CHECK(lineFollow(LINE_BLACK_OUTLINED, true, 1.5));

    // Prepare arm
    Hardware::arm.SetDegree(Hardware::APPLE_GRAB_ROTATION);
    CHECK(activeSleep(1.5));

    // Drive into apples
    CHECK(driveDistance(Drivetrain::left, 3, false));

    // Lift apples
    Hardware::arm.SetDegree(Hardware::APPLE_LIFT_ROTATION);
    CHECK(activeSleep(1.5));

    // Retreat
    CHECK(driveDistance(Drivetrain::left, -8));

    // Back off to get to ramp
    CHECK(driveDistance(Drivetrain::left, -6, true));

    // Align with ramp
    CHECK(driveDistance(Drivetrain::left, -11));

    CHECK(rotateClockwise(90));

    // Drive up ramp
    drivetrain.setMaxSpeed(16);
    CHECK(driveDistance(Drivetrain::left, 42));
    drivetrain.setMaxSpeed(6);

    // Rotate to get arm above table
    CHECK(rotateClockwise(45));

    // Let it down
    Hardware::arm.SetDegree(Hardware::APPLE_LIFT_ROTATION - 10);
    CHECK(activeSleep(0.5));
    Hardware::arm.Off();
    CHECK(activeSleep(1.5));

    // Pull back to unhook apples
    CHECK(driveDistance(Drivetrain::left, -6));

    drivetrain.stop();
    Hardware::arm.Off();
    logger.log("End showcase", "mile");
    return;

end:
    drivetrain.stop();
    Hardware::arm.Off();
    logger.log("STOPPING SHOWCASE EARLY", "mile");
    return;
}

void showcase2() {
    logger.log("Begin showcase", "gui");
    ui.openView(MainUI::LogView);
    drivetrain.setMaxSpeed(6);
    Buzzer.Beep();

    // Align with the line
    CHECK(lineFollow(LINE_BLUE, false, 0));

    // Back up keeping alignment
    CHECK(lineFollow(LINE_BLUE, true, 1.5));

    drivetrain.stop();
    Hardware::arm.Off();
    logger.log("End showcase", "mile");
    return;

end:
    drivetrain.stop();
    Hardware::arm.Off();
    logger.log("STOPPING SHOWCASE EARLY", "mile");
    return;
}

}   // namespace milestones
