#include "drivetrain.h"

#include <FEHMotor.h>

#include <algorithm>

#include "hardware.h"
#include "logging.h"

using namespace std;

const float ROOT_3 = sqrt(3);

const float P_CONST = 3.5;

void Drivetrain::stop() {
    Hardware::leftMotor.stop();
    Hardware::rightMotor.stop();
    Hardware::rearMotor.stop();

    resetDistances();

    distanceDriven = 0;
    leftDist = 0;
    rightDist = 0;
    axialDist = 0;
    targetDistance = NAN;

    targetRotation = NAN;
    degreesRotated = 0;
}

void Drivetrain::rotateClockwise(float speed) {
    rotateCounterClockwise(-speed);
}

void Drivetrain::rotateCounterClockwise(float speed) {
    Hardware::leftMotor.setSpeed(speed);
    Hardware::rightMotor.setSpeed(speed);
    Hardware::rearMotor.setSpeed(speed);
}

void Drivetrain::rotateClockwiseDegrees(float degrees) {
    rotateCounterClockwiseDegrees(-degrees);
}

void Drivetrain::rotateCounterClockwiseDegrees(float degrees) {
    stop();
    targetRotation = degrees;
}

void Drivetrain::selectMotors(Axis axis) {
    switch (axis) {
        case forward:
            currentAxialMotor = &Hardware::rearMotor;
            currentLeftMotor = &Hardware::leftMotor;
            currentRightMotor = &Hardware::rightMotor;
            break;
        case left:
            currentAxialMotor = &Hardware::rightMotor;
            currentLeftMotor = &Hardware::rearMotor;
            currentRightMotor = &Hardware::leftMotor;
            break;
        case right:
            currentAxialMotor = &Hardware::leftMotor;
            currentLeftMotor = &Hardware::rightMotor;
            currentRightMotor = &Hardware::rearMotor;
            break;
    }
}

void Drivetrain::driveAxis(Axis axis, float speed, bool strafe) {
    stop();
    selectMotors(axis);

    // I took this from https://en.wikipedia.org/wiki/Kiwi_drive#Motion
    if (strafe) {
        currentAxialMotor->setSpeed(speed);
        currentLeftMotor->setSpeed(-speed / 2);
        currentRightMotor->setSpeed(-speed / 2);
    } else {
        currentAxialMotor->setSpeed(0);
        currentLeftMotor->setSpeed(-speed);
        currentRightMotor->setSpeed(speed);
    }
}

void Drivetrain::driveAxisDistance(Axis axis, float distance, bool strafe) {
    stop();

    selectMotors(axis);
    drivingStrafe = strafe;
    targetDistance = distance;
}

void Drivetrain::update() {
    float leftDelta = currentLeftMotor->getDistance() - leftDist;
    float rightDelta = currentRightMotor->getDistance() - rightDist;
    float axialDelta = currentAxialMotor->getDistance() - axialDist;

    leftDist += leftDelta;
    rightDist += rightDelta;
    axialDist += axialDelta;

    if (!isnan(targetDistance)) {
        if (!drivingStrafe) {
            float delta =
                2. / 3. *
                ((ROOT_3 / 2.) * rightDelta - (ROOT_3 / 2.) * leftDelta);
            distanceDriven += delta;

            float error = targetDistance - distanceDriven;

            float command = clamp(error * P_CONST, -maxSpeed, maxSpeed);

            currentRightMotor->setSpeed(command);
            currentLeftMotor->setSpeed(-command);

            // logger.log(vformat("%.2f", distanceDriven), "drv");
        } else {
            float delta =
                2. / 3. * (axialDelta - .5 * rightDelta - .5 * leftDelta);
            distanceDriven += delta;

            float error = targetDistance - distanceDriven;

            float command = clamp(error * P_CONST, -maxSpeed, maxSpeed);

            currentAxialMotor->setSpeed(command);
            currentLeftMotor->setSpeed(-command / 2);
            currentRightMotor->setSpeed(-command / 2);

            // logger.log(vformat("%.2f", distanceDriven), "drv");
        }
    } else if (!isnan(targetRotation)) {
        float delta = 180. / M_PI / 3. / Hardware::wheelCircleRadius *
                      (leftDelta + rightDelta + axialDelta);
        degreesRotated += delta;

        float error = targetRotation - degreesRotated;

        float command = clamp(error / 4.f, -maxSpeed, maxSpeed);

        currentAxialMotor->setSpeed(command);
        currentLeftMotor->setSpeed(command);
        currentRightMotor->setSpeed(command);
    }

    Hardware::rearMotor.update();
    Hardware::leftMotor.update();
    Hardware::rightMotor.update();
}

bool Drivetrain::distanceInThreshold(float threshold) {
    return fabs(distanceDriven - targetDistance) < threshold;
}

bool Drivetrain::rotationInThreshold(float threshold) {
    return fabs(degreesRotated - targetRotation) < threshold;
}

void Drivetrain::resetDistances() {
    Hardware::rearMotor.resetDistance();
    Hardware::leftMotor.resetDistance();
    Hardware::rightMotor.resetDistance();
}

void Drivetrain::setMaxSpeed(float speed) {
    maxSpeed = speed;
}

Drivetrain drivetrain;
