#include "hardware.h"

#define _USE_MATH_DEFINES
#include <cmath>

namespace Hardware {

FEHMotor rawRearMotor(FEHMotor::Motor1, 9.0);
FEHMotor rawLeftMotor(FEHMotor::Motor3, 9.0);
FEHMotor rawRightMotor(FEHMotor::Motor2, 9.0);
FEHMotor forkMotor(FEHMotor::Motor0, 5.0);

DigitalEncoder rearEncoder(FEHIO::P0_1);
DigitalEncoder leftEncoder(FEHIO::P0_2);
DigitalEncoder rightEncoder(FEHIO::P0_0);

ControlledMotor rearMotor("rear", rawRearMotor, rearEncoder);
ControlledMotor leftMotor("left", rawLeftMotor, leftEncoder);
ControlledMotor rightMotor("right", rawRightMotor, rightEncoder);

AnalogInputPin leftOptosensor(FEHIO::P3_7);
AnalogInputPin centerOptosensor(FEHIO::P3_6);
AnalogInputPin rightOptosensor(FEHIO::P3_5);

AnalogInputPin cdsCell(FEHIO::P0_7);

FEHServo arm(FEHServo::Servo0);

const float wheelCircumference = M_PI * wheelDiameter;

}   // namespace Hardware
