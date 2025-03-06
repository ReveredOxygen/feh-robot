#include "drivetrain.h"

#include <FEHMotor.h>

#include "hardware.h"

void Drivetrain::stop() {
    Hardware::leftMotor.stop();
    Hardware::rightMotor.stop();
    Hardware::rearMotor.stop();
}

void Drivetrain::rotateClockwise(float speed) {
    rotateCounterClockwise(-speed);
}

void Drivetrain::rotateCounterClockwise(float speed) {
    Hardware::leftMotor.setSpeed(speed);
    Hardware::rightMotor.setSpeed(speed);
    Hardware::rearMotor.setSpeed(speed);
}

void Drivetrain::driveAxis(Axis axis, float speed, bool strafe) {
    ControlledMotor *axialMotor;
    ControlledMotor *leftMotor;
    ControlledMotor *rightMotor;

    switch (axis) {
        case forward:
            axialMotor = &Hardware::rearMotor;
            leftMotor = &Hardware::leftMotor;
            rightMotor = &Hardware::rightMotor;
            break;
        case left:
            axialMotor = &Hardware::rightMotor;
            leftMotor = &Hardware::rearMotor;
            rightMotor = &Hardware::leftMotor;
            break;
        case right:
            axialMotor = &Hardware::leftMotor;
            leftMotor = &Hardware::rightMotor;
            rightMotor = &Hardware::rearMotor;
            break;
    }

    // I took this from https://en.wikipedia.org/wiki/Kiwi_drive#Motion
    if (strafe) {
        axialMotor->setSpeed(speed);
        leftMotor->setSpeed(-speed / 2);
        rightMotor->setSpeed(-speed / 2);
    } else {
        axialMotor->setSpeed(0);
        leftMotor->setSpeed(-speed);
        rightMotor->setSpeed(speed);
    }
}

void Drivetrain::update() {
    Hardware::rearMotor.update();
    Hardware::leftMotor.update();
    Hardware::rightMotor.update();
}

Drivetrain drivetrain;
