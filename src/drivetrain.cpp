#include "drivetrain.h"

#include <FEHMotor.h>

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

void Drivetrain::driveAxis(Axis axis, float speed, bool strafe) {
    FEHMotor *axialMotor;
    FEHMotor *leftMotor;
    FEHMotor *rightMotor;

    switch (axis) {
        case forward:
            axialMotor = &Hardware::rearMotor;
            leftMotor = &Hardware::leftMotor;
            rightMotor = &Hardware::rightMotor;
            break;
        case left:
            axialMotor = &Hardware::leftMotor;
            leftMotor = &Hardware::rearMotor;
            rightMotor = &Hardware::rightMotor;
        case right:
            axialMotor = &Hardware::rightMotor;
            leftMotor = &Hardware::rearMotor;
            rightMotor = &Hardware::leftMotor;
            break;
    }

    // I took this from https://en.wikipedia.org/wiki/Kiwi_drive#Motion
    if (strafe) {
        axialMotor->SetPercent(speed);
        leftMotor->SetPercent(-speed / 2);
        rightMotor->SetPercent(-speed / 2);
    } else {
        axialMotor->SetPercent(0);
        leftMotor->SetPercent(speed);
        rightMotor->SetPercent(-speed);
    }
}

Drivetrain drivetrain;
