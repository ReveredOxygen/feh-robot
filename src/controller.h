#pragma once

#include "drivetrain.h"

bool activeSleep(float seconds);
bool tick();
bool driveDistance(Drivetrain::Axis axis, float distance, bool strafe = false,
                   float precision = 0.1);

const float TICK_INTERVAL = 0.05;
