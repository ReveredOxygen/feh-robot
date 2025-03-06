#pragma once

#include <FEHIO.h>
#include <FEHMotor.h>

#include <string>

/// All speeds in inches per second.
class ControlledMotor {
   public:
    ControlledMotor(std::string name, FEHMotor motor, DigitalEncoder encoder);

    void setSpeed(float speed);
    void stop();
    void update();

    float getDistance();
    void resetDistance();

    // float getTargetDistance();
    // void setTargetDistance(float distance);
    // void clearTargetDistance();

    // float getMaxSpeed();
    // void setMaxSpeed(float maxSpeed);

    std::string name;

   private:
    void setRawSpeed(float percent);

    FEHMotor motor;
    DigitalEncoder encoder;

    double lastUpdateTime = 0;

    float targetSpeed = 0;
    float previousSpeed = 0;
    float integral = 0;

    int previousCounts = 0;

    float speedPercent = 0;

    float distanceTraveled = 0;
    // float targetDistance;
    // float maxSpeed = 6;
};
