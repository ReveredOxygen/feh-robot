#include <FEHIO.h>
#include <FEHMotor.h>

/// All speeds in inches per second.
class ControlledMotor {
   public:
    ControlledMotor(FEHMotor motor, DigitalEncoder encoder)
        : motor(motor), encoder(encoder) {}

    void setSpeed(float speed);
    void stop();

   private:
    FEHMotor motor;
    DigitalEncoder encoder;

    float lastUpdateTime = 0;

    float targetSpeed = 0;
    float previousSpeed = 0;
    float integral = 0;
};
