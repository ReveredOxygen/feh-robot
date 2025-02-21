#include "drivetrain.h"

#include "hardware.h"

void Drivetrain::stop() {
    Hardware::leftMotor.Stop();
    Hardware::rightMotor.Stop();
    Hardware::rearMotor.Stop();
}

void Drivetrain::rotateClockwise(float speed) {
    Hardware::leftMotor.SetPercent(speed);
    Hardware::rightMotor.SetPercent(speed);
    Hardware::rearMotor.SetPercent(speed);
}

void Drivetrain::rotateCounterClockwise(float speed) {
    rotateClockwise(-speed);
}
