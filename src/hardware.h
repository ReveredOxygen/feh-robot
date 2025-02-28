#pragma once

#include <FEHIO.h>
#include <FEHMotor.h>

#include "controlledMotor.h"

namespace Hardware {

FEHMotor rawRearMotor(FEHMotor::Motor1, 9.0);
FEHMotor rawLeftMotor(FEHMotor::Motor3, 9.0);
FEHMotor rawRightMotor(FEHMotor::Motor2, 9.0);

DigitalEncoder rearEncoder(FEHIO::P0_1);
DigitalEncoder leftEncoder(FEHIO::P3_0);
DigitalEncoder rightEncoder(FEHIO::P0_0);

ControlledMotor rearMotor(rawRearMotor, rearEncoder);
ControlledMotor leftMotor(rawLeftMotor, leftEncoder);
ControlledMotor rightMotor(rawRightMotor, rightEncoder);

};   // namespace Hardware
