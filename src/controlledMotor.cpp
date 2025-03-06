#include "controlledMotor.h"

#include <FEHUtility.h>

#include <algorithm>
#include <cmath>

#include "hardware.h"
#include "logging.h"

using namespace std;

float speedToPercent(float speed) {
    return 3 * speed;
}

ControlledMotor::ControlledMotor(std::string name, FEHMotor motor,
                                 DigitalEncoder encoder)
    : motor(motor), encoder(encoder), name(name) {
    // targetDistance = NAN;
}

void ControlledMotor::stop() {
    setSpeed(0);
    // clearTargetDistance();
    resetDistance();
}

void ControlledMotor::setSpeed(float speed) {
    // setRawSpeed(speedToPercent(speed));
    this->targetSpeed = speed;

    // logger.log(vformat("%s: %f", this->name.c_str(), speed), "drv");
}

// See
// https://en.wikipedia.org/wiki/Proportional%E2%80%93integral%E2%80%93derivative_controller#Pseudocode
void ControlledMotor::update() {
    // Gather environmental data

    int counts = encoder.Counts();
    float time = TimeNow();
    float timeElapsed = time - lastUpdateTime;

    int elapsedCounts = counts - previousCounts;
    float stepDistanceTraveled = Hardware::countsToDistance(elapsedCounts);

    if (speedPercent < 0) {
        stepDistanceTraveled *= -1;
    }

    this->distanceTraveled += stepDistanceTraveled;

    float speed = stepDistanceTraveled / timeElapsed;

    // // Process distance targeting

    // if (!isnan(targetDistance)) {
    //     float distError = targetDistance - distanceTraveled;
    //     targetSpeed = clamp(distError, -maxSpeed, maxSpeed);
    //     // logger.log(vformat("%s %.2f", name.c_str(), distError), "drv");
    // }

    // Process speed targeting

    if (targetSpeed == 0) {
        setRawSpeed(0);
        previousCounts = encoder.Counts();
        lastUpdateTime = TimeNow();
        return;
    }

    // logger.log(vformat("measured %.2f", speed), "drv");

    float error = targetSpeed - speed;

    setRawSpeed(speedPercent + speedToPercent(error));

    // Store values for next iteration
    previousSpeed = speed;
    previousCounts = counts;
    lastUpdateTime = time;
}

float ControlledMotor::getDistance() {
    return distanceTraveled;
}

void ControlledMotor::resetDistance() {
    distanceTraveled = 0;
}

// float ControlledMotor::getTargetDistance() {
//     return targetDistance;
// }

// void ControlledMotor::setTargetDistance(float distance) {
//     targetDistance = distance;
//     // logger.log(vformat("%s %.2f", name.c_str(), distance), "drv");
// }

// void ControlledMotor::clearTargetDistance() {
//     targetDistance = NAN;
// }

// float ControlledMotor::getMaxSpeed() {
//     return maxSpeed;
// }

// void ControlledMotor::setMaxSpeed(float maxSpeed) {
//     this->maxSpeed = maxSpeed;
// }

void ControlledMotor::setRawSpeed(float percent) {
    motor.SetPercent(percent);
    speedPercent = percent;
}
