#include "controller.h"

#include <FEHLCD.h>
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

    return true;
}

bool onLine(char sensor) {
    switch (sensor) {
        case 'r':
            return Hardware::rightOptosensor.Value() < 2.9;
        case 'l':
            return Hardware::leftOptosensor.Value() < 3.0;
        case 'c':
            return Hardware::centerOptosensor.Value() < 3.0;
        default:
            logger.log("Invalid onLine sensor", "ctrl");
            return false;
    }
}

void lineFollow(float speed) {
    logger.log("Begin line follow", "ctrl");
    // Declarations for analog optosensors
    AnalogInputPin right_opto(FEHIO::P3_5);
    AnalogInputPin middle_opto(FEHIO::P3_6);
    AnalogInputPin left_opto(FEHIO::P3_7);

    enum LineState { MIDDLE, RIGHT, LEFT };

    LineState state = MIDDLE;   // Set the initial state
    bool seenLine = false;
    bool lineFinish = false;

    while (!lineFinish) {   // Loop until we see the end of the line
        bool left = onLine('l');
        bool right = onLine('r');
        bool center = onLine('c');

        bool any = left || right || center;

        // LCD.SetBackgroundColor(WHITE);
        // LCD.SetFontColor(BLACK);
        // if (left) {
        //     LCD.WriteRC('L', 2, 3);
        // } else {
        //     LCD.WriteRC(' ', 2, 3);
        // }
        // if (center) {
        //     LCD.WriteRC('C', 3, 3);
        // } else {
        //     LCD.WriteRC(' ', 3, 3);
        // }
        // if (right) {
        //     LCD.WriteRC('R', 4, 3);
        // } else {
        //     LCD.WriteRC(' ', 4, 3);
        // }

        // if (seenLine) {
        //     LCD.WriteRC('S', 3, 5);
        // } else {
        //     LCD.WriteRC(' ', 3, 5);
        // }

        // if (lineFinish) {
        //     LCD.WriteRC('F', 3, 7);
        // } else {
        //     LCD.WriteRC(' ', 3, 7);
        // }

        switch (state) {
            // If I am in the middle of the line...
            case MIDDLE:
                if (any) {
                    if (!seenLine) {
                        seenLine = true;
                    }
                } else if (seenLine) {
                    // If we've seen the line before (and aren't anymore), note
                    // that we've finished the line
                    lineFinish = true;
                }

                if (right && !left) {
                    state = RIGHT;
                } else if (left && !right) {
                    state = LEFT;
                } else {   // Neither or both are on line
                    // Drive straight
                    Hardware::rearMotor.setSpeed(-speed);
                    Hardware::leftMotor.setSpeed(speed);
                }

                break;

            // If the right sensor is on the line...
            case RIGHT:
                Hardware::rearMotor.setSpeed(-speed);
                Hardware::leftMotor.setSpeed(-speed / 2);

                if (!onLine('r')) {
                    state = MIDDLE;
                }
                break;

            // If the left sensor is on the line...
            case LEFT:
                Hardware::rearMotor.setSpeed(speed / 2);
                Hardware::leftMotor.setSpeed(speed);

                if (!onLine('l')) {
                    state = MIDDLE;
                }
                break;

            default:   // Error. Something is very wrong.
                logger.log("Illegal line follow state!", "ctrl");
                break;
        }

        // Sleep a bit
        Sleep(TICK_INTERVAL);
        tick();
    }

    drivetrain.stop();
    logger.log("End line follow", "ctrl");
}
