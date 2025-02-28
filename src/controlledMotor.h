#pragma once

#include <FEHIO.h>
#include <FEHMotor.h>

/// All speeds in inches per second.
class ControlledMotor {
   public:
    ControlledMotor(FEHMotor motor, DigitalEncoder encoder)
        : motor(motor), encoder(encoder) {}

    void setSpeed(float speed);
    void stop();
    void update();

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
};
