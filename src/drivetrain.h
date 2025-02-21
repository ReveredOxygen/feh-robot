class Drivetrain {
   public:
    enum Axis { forward, left, right };

    void stop();
    void rotateClockwise(float speed);
    void rotateCounterClockwise(float speed);
    void driveAxis(Axis axis, float speed, bool strafe = false);
};

extern Drivetrain drivetrain;
