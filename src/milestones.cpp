#include "milestones.h"

#include <FEHBuzzer.h>
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
void milestone3();
void milestone4();
void simpleMilestone4();
void milestone5();

Menu* getMenu() {
    return MenuBuilder()
        .withSubmenu("Milestone 1", MenuBuilder()
                                        .withOption("Part 2", milestone1Part2)
                                        ->withOption("Part 3", milestone1Part3)
                                        ->build())
        ->withOption("Milestone 2", milestone2)
        ->withOption("Milestone 3", milestone3)
        ->withOption("Milestone 4", milestone4)
        ->withOption("EZ Milestone 4", simpleMilestone4)
        ->withOption("Milestone 5", milestone5)
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

    // Declarations for analog optosensors
    AnalogInputPin right_opto(FEHIO::P3_5);
    AnalogInputPin middle_opto(FEHIO::P3_6);
    AnalogInputPin left_opto(FEHIO::P3_7);

    enum LineStates { MIDDLE, RIGHT, LEFT };

    int state = MIDDLE;   // Set the initial state

    while (true) {        // I will follow this line forever!

        switch (state) {
            // If I am in the middle of the line...
            case MIDDLE:

                // Set motor powers for driving straight
                drivetrain.driveAxis(Drivetrain::left, 6);

                if (right_opto.Value() < 3.0) {
                    state = RIGHT;   // update a new state
                }

                if (left_opto.Value() < 3.0) {
                    state = LEFT;   // update a new state
                }

                break;

                // If the right sensor is on the line...
            case RIGHT:
                // Set motor powers for right turn

                Hardware::rearMotor.setSpeed(-6);
                Hardware::leftMotor.setSpeed(3);

                if (right_opto.Value() > 3.0) {
                    state = MIDDLE;
                }
                break;

            // If the left sensor is on the line...
            case LEFT:

                Hardware::rearMotor.setSpeed(3);
                Hardware::leftMotor.setSpeed(-6);

                if (left_opto.Value() > 3.0) {
                    state = MIDDLE;
                }
                break;

            default:   // Error. Something is very wrong.
                break;
        }

        // Sleep a bit
        Sleep(TICK_INTERVAL);
        tick();
    }
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

}   // namespace milestones
