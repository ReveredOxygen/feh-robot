#pragma once

#include <FEHIO.h>
#include <FEHMotor.h>
#include <FEHServo.h>

#include "controlledMotor.h"

#define M_PI 3.14159265358979323846

namespace Hardware {

const int encoderCountsPerRevolution = 318;
const float wheelDiameter = 2.5;
extern const float wheelCircumference;

const float wheelCircleRadius = 3.9375;

const float APPLE_GRAB_ROTATION = 42;
const float APPLE_LIFT_ROTATION = APPLE_GRAB_ROTATION + 60;

extern FEHMotor rawRearMotor;
extern FEHMotor rawLeftMotor;
extern FEHMotor rawRightMotor;
extern FEHMotor forkMotor;

extern DigitalEncoder rearEncoder;
extern DigitalEncoder leftEncoder;
extern DigitalEncoder rightEncoder;

extern ControlledMotor rearMotor;
extern ControlledMotor leftMotor;
extern ControlledMotor rightMotor;

extern AnalogInputPin leftOptosensor;
extern AnalogInputPin centerOptosensor;
extern AnalogInputPin rightOptosensor;

extern AnalogInputPin cdsCell;

extern FEHServo arm;

inline float countsToDistance(int counts) {
    const float inchesPerCount =
        wheelCircumference / encoderCountsPerRevolution;

    return inchesPerCount * counts;
}

};   // namespace Hardware
