#include "controller.h"

#include <FEHLCD.h>
#include <FEHUtility.h>

#include <algorithm>

#include "drivetrain.h"
#include "gui.h"
#include "logging.h"

float pauseTime = 0.5;

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
    activeSleep(pauseTime);

    return true;
}

bool rotateClockwise(float degrees, float precision) {
    drivetrain.rotateClockwiseDegrees(degrees);
    while (!drivetrain.rotationInThreshold(precision)) {
        Sleep(TICK_INTERVAL);
        tick();
    }
    drivetrain.stop();
    activeSleep(pauseTime);

    return true;
}

float multiSample(AnalogInputPin pin, int samples) {
    float acc = 0;

    for (int i = 0; i < samples; i++) {
        acc += pin.Value();
    }

    return acc / samples;
}

bool onLine(char sensor, LineType type) {
    switch (type) {
        case LINE_BLUE:
            // LCD.WriteRC('U', 7, 9);
            switch (sensor) {
                case 'r':
                    return multiSample(Hardware::rightOptosensor) < 2.87;
                    break;
                case 'l':
                    return multiSample(Hardware::leftOptosensor) < 2.95;
                    break;
                case 'c':
                    return multiSample(Hardware::centerOptosensor) < 2.99;
                    break;
                default:
                    logger.log("Invalid onLine sensor", "ctrl", logging::Error);
                    return false;
                    break;
            }
            break;
            logger.log("Fall through??", "ctrl", logging::Error);
        case LINE_BLACK_OUTLINED:
            // LCD.WriteRC('B', 7, 9);
            switch (sensor) {
                case 'r':
                    return Hardware::rightOptosensor.Value() > 3.0;
                    break;
                case 'l':
                    return Hardware::leftOptosensor.Value() > 3.0;
                    break;
                case 'c':
                    return Hardware::centerOptosensor.Value() > 3.0;
                    break;
                default:
                    logger.log("Invalid onLine sensor", "ctrl", logging::Error);
                    return false;
                    break;
            }
            break;
        default:
            return false;   // unreachable
            break;
    }
}

bool lineFollow(LineType type, bool reverse, float minTime) {
    logger.log("Begin line follow", "ctrl", logging::Debug);
    // Declarations for analog optosensors
    AnalogInputPin right_opto(FEHIO::P3_5);
    AnalogInputPin middle_opto(FEHIO::P3_6);
    AnalogInputPin left_opto(FEHIO::P3_7);

    double startTime = TimeNow();

    enum LineState { MIDDLE, RIGHT, LEFT };

    LineState state = MIDDLE;   // Set the initial state
    bool seenLine = false;
    bool lineFinish = false;

    float speed = 2;

    if (reverse) {
        speed = -speed;
    }

    while (!lineFinish) {   // Loop until we see the end of the line
        bool left = onLine('l', type);
        bool right = onLine('r', type);
        bool center = onLine('c', type);

        bool any = left || right || center;

        LCD.SetBackgroundColor(WHITE);
        LCD.SetFontColor(BLACK);
        if (left) {
            LCD.WriteRC('L', 2, 3);
        } else {
            LCD.WriteRC(' ', 2, 3);
        }
        if (center) {
            LCD.WriteRC('C', 3, 3);
        } else {
            LCD.WriteRC(' ', 3, 3);
        }
        if (right) {
            LCD.WriteRC('R', 4, 3);
        } else {
            LCD.WriteRC(' ', 4, 3);
        }

        if (seenLine) {
            LCD.WriteRC('S', 3, 5);
        } else {
            LCD.WriteRC(' ', 3, 5);
        }

        if (lineFinish) {
            LCD.WriteRC('F', 3, 7);
        } else {
            LCD.WriteRC(' ', 3, 7);
        }

        switch (state) {
            // If I am in the middle of the line...
            case MIDDLE:
                if (any) {
                    if (!seenLine) {
                        seenLine = true;
                    }
                } else if (seenLine && TimeNow() > startTime + minTime) {
                    // If we've seen the line before (and aren't anymore), note
                    // that we've finished the line
                    lineFinish = true;
                }

                if (right && !left) {
                    state = reverse ? LEFT : RIGHT;
                } else if (left && !right) {
                    state = reverse ? RIGHT : LEFT;
                } else {   // Neither or both are on line
                    // Drive straight
                    Hardware::rearMotor.setSpeed(-speed);
                    Hardware::leftMotor.setSpeed(speed);
                }

                break;

            // If the right sensor is on the line...
            case RIGHT:
                Hardware::rearMotor.setSpeed(-speed);
                Hardware::leftMotor.setSpeed(speed / 3);

                if (!right) {
                    state = MIDDLE;
                }
                break;

            // If the left sensor is on the line...
            case LEFT:
                Hardware::rearMotor.setSpeed(-speed / 3);
                Hardware::leftMotor.setSpeed(speed);

                if (!left) {
                    state = MIDDLE;
                }
                break;

            default:   // Error. Something is very wrong.
                logger.log("Illegal line follow state!", "ctrl",
                           logging::Error);
                break;
        }

        // Sleep a bit
        Sleep(TICK_INTERVAL);
        tick();
    }

    drivetrain.stop();
    logger.log("End line follow", "ctrl", logging::Debug);
    return true;
}
