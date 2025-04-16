#pragma once

#include "drivetrain.h"

bool activeSleep(float seconds);
bool tick();
bool driveDistance(Drivetrain::Axis axis, float distance, bool strafe = false,
                   float precision = 0.1);
bool rotateClockwise(float degrees, float precision = 0.5);

enum LineType { LINE_BLUE, LINE_BLACK_OUTLINED };

bool onLine(char sensor, LineType type);

bool lineFollow(LineType type, bool reverse = false, float minTime = 0);

float multiSample(AnalogInputPin pin, int samples = 5, float time = 1. / 1000);

void calibrateLine(LineType type);

extern float pauseTime;

// approx 33.5 ms
const float TICK_INTERVAL = (1. / 3.) / (318 / (2 * 2 * 2 * 2 * 2));

namespace thresholds {

extern float line_blue[3];
extern float line_black[3];

};   // namespace thresholds
