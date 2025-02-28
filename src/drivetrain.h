#pragma once

class Drivetrain {
   public:
    enum Axis { forward, left, right };

    void stop();
    void rotateClockwise(float speed);
    void rotateCounterClockwise(float speed);
    void driveAxis(Axis axis, float speed, bool strafe = false);

    void update();
};

extern Drivetrain drivetrain;
