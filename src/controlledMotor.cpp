#include "controlledMotor.h"

#include <FEHUtility.h>

#include "hardware.h"
#include "logging.h"

float speedToPercent(float speed) {
    return 25. / 6. * speed;
}

void ControlledMotor::stop() {
    setSpeed(0);
}

void ControlledMotor::setSpeed(float speed) {
    setRawSpeed(25. / 6. * speed);
    this->targetSpeed = speed;
}

// See
// https://en.wikipedia.org/wiki/Proportional%E2%80%93integral%E2%80%93derivative_controller#Pseudocode
void ControlledMotor::update() {
    if (targetSpeed == 0) {
        setRawSpeed(0);
        previousCounts = encoder.Counts();
        lastUpdateTime = TimeNow();
        return;
    }

    int counts = encoder.Counts();
    float time = TimeNow();
    float timeElapsed = time - lastUpdateTime;

    int elapsedCounts = counts - previousCounts;
    float distanceTraveled = Hardware::countsToDistance(elapsedCounts);

    float speed = distanceTraveled / timeElapsed;

    if (targetSpeed < 0) {
        speed *= -1;
    }

    // logger.log(vformat("measured %.2f", speed), "drv");

    float error = targetSpeed - speed;

    setRawSpeed(speedToPercent(targetSpeed) + speedToPercent(error));

    // Store values for next iteration
    previousSpeed = speed;
    previousCounts = counts;
    lastUpdateTime = time;
}

void ControlledMotor::setRawSpeed(float percent) {
    motor.SetPercent(percent);
    speedPercent = percent;
}
