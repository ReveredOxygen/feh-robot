#include "controlledMotor.h"

void ControlledMotor::stop() {
    setSpeed(0);
}

void ControlledMotor::setSpeed(float speed) {
    motor.SetPercent(25. / 6. * speed);
}
