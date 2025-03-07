#pragma once

#include <FEHIO.h>
#include <FEHMotor.h>

#include "controlledMotor.h"

namespace Hardware {

const int encoderCountsPerRevolution = 318;
const float wheelDiameter = 2.5;
extern const float wheelCircumference;

const float wheelCircleRadius = 3.875;

extern FEHMotor rawRearMotor;
extern FEHMotor rawLeftMotor;
extern FEHMotor rawRightMotor;

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

inline float countsToDistance(int counts) {
    const float inchesPerCount =
        wheelCircumference / encoderCountsPerRevolution;

    return inchesPerCount * counts;
}

};   // namespace Hardware
