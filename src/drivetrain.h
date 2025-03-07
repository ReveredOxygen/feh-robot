#pragma once

#include <cmath>

#include "controlledMotor.h"
#include "hardware.h"

class Drivetrain {
   public:
    enum Axis { forward, left, right };

    void stop();
    void rotateClockwise(float speed);
    void rotateCounterClockwise(float speed);
    void rotateClockwiseDegrees(float degrees);
    void rotateCounterClockwiseDegrees(float degrees);
    void driveAxis(Axis axis, float speed, bool strafe = false);
    void driveAxisDistance(Axis axis, float distance, bool strafe = false);

    void update();

    void resetDistances();

    bool distanceInThreshold(float threshold);
    bool rotationInThreshold(float threshold);

    void setMaxSpeed(float speed);

   private:
    void selectMotors(Axis axis);

    float leftDist = 0, rightDist = 0, axialDist = 0;

    float maxSpeed = 6;

    // Info for controlled driving
    float distanceDriven = 0;
    float targetDistance = NAN;
    float drivingStrafe = false;

    float targetRotation = NAN;
    float degreesRotated = 0;

    ControlledMotor *currentAxialMotor = &Hardware::rearMotor;
    ControlledMotor *currentLeftMotor = &Hardware::leftMotor;
    ControlledMotor *currentRightMotor = &Hardware::rightMotor;
};

extern Drivetrain drivetrain;
