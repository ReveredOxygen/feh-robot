#include <FEHIO.h>
#include <FEHMotor.h>

namespace Hardware {

FEHMotor rearMotor(FEHMotor::Motor1, 9.0);
FEHMotor leftMotor(FEHMotor::Motor3, 9.0);
FEHMotor rightMotor(FEHMotor::Motor2, 9.0);

};   // namespace Hardware
