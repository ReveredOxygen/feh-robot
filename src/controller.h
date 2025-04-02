#pragma once

#include "drivetrain.h"

bool activeSleep(float seconds);
bool tick();
bool driveDistance(Drivetrain::Axis axis, float distance, bool strafe = false,
                   float precision = 0.1);
bool rotateClockwise(float degrees, float precision = 0.5);

// approx 33.5 ms
const float TICK_INTERVAL = (1. / 3.) / (318 / (2 * 2 * 2 * 2 * 2));
