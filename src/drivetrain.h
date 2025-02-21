class Drivetrain {
   public:
    void stop();
    void rotateClockwise(float speed);
    void rotateCounterClockwise(float speed);
};

extern Drivetrain drivetrain;
