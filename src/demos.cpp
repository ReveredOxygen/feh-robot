#include "demos.h"

#include <string>

#include "drivetrain.h"
#include "hardware.h"

namespace demos {

Menu* genAxisMenu(std::string name, Drivetrain::Axis axis, float speed) {
    return MenuBuilder()
        .withOption(
            "Straight",
            [axis, speed]() { drivetrain.driveAxis(axis, speed, false); })
        ->withOption(
            "Strafe",
            [axis, speed]() { drivetrain.driveAxis(axis, speed, true); })
        ->withOption(
            "Rev Straight",
            [axis, speed]() { drivetrain.driveAxis(axis, -speed, false); })
        ->withOption(
            "Rev Strafe",
            [axis, speed]() { drivetrain.driveAxis(axis, -speed, true); })
        ->withOption("Stop", []() { drivetrain.stop(); })
        ->withOption(name, []() {})
        ->build();
}

Menu* genAxisMenuDistance(std::string name, Drivetrain::Axis axis,
                          float distance) {
    return MenuBuilder()
        .withOption("Straight",
                    [axis, distance]() {
                        drivetrain.driveAxisDistance(axis, distance, false);
                    })
        ->withOption("Strafe",
                     [axis, distance]() {
                         drivetrain.driveAxisDistance(axis, distance, true);
                     })
        ->withOption("Rev Straight",
                     [axis, distance]() {
                         drivetrain.driveAxisDistance(axis, -distance, false);
                     })
        ->withOption("Rev Strafe",
                     [axis, distance]() {
                         drivetrain.driveAxisDistance(axis, -distance, true);
                     })
        ->withOption("Stop", []() { drivetrain.stop(); })
        ->withOption(name, []() {})
        ->build();
}

Menu* genMotorMenu() {
    return MenuBuilder()
        .withOption("Rear", []() { Hardware::rearMotor.setSpeed(6); })
        ->withOption("Left", []() { Hardware::leftMotor.setSpeed(6); })
        ->withOption("Right", []() { Hardware::rightMotor.setSpeed(6); })
        ->withOption("Fork", []() { Hardware::forkMotor.SetPercent(25); })
        ->build();
}

Menu* drivetrainMenu() {
    return MenuBuilder()
        .withSubmenu("Forward", genAxisMenu("Forward", Drivetrain::forward, 6))
        ->withSubmenu("Left", genAxisMenu("Left", Drivetrain::left, 6))
        ->withSubmenu("Right", genAxisMenu("Right", Drivetrain::right, 6))
        ->withOption("Clockwise", []() { drivetrain.rotateClockwise(6); })
        ->withOption("Counterclockwise",
                     []() { drivetrain.rotateCounterClockwise(6); })
        ->withSubmenu("Motors", genMotorMenu())
        ->build();
}

Menu* twoFtMenu() {
    return MenuBuilder()
        .withSubmenu("Forward",
                     genAxisMenuDistance("Forward", Drivetrain::forward, 24))
        ->withSubmenu("Left", genAxisMenuDistance("Left", Drivetrain::left, 24))
        ->withSubmenu("Right",
                      genAxisMenuDistance("Right", Drivetrain::right, 24))
        ->withOption("90 Clockwise",
                     []() { drivetrain.rotateClockwiseDegrees(90); })
        ->withOption("90 Counterclockwise",
                     []() { drivetrain.rotateCounterClockwiseDegrees(90); })
        // ->withOption("Clockwise", []() { drivetrain.rotateClockwise(6); })
        // ->withOption("Counterclockwise",
        //              []() { drivetrain.rotateCounterClockwise(6); })
        // ->withSubmenu("Motors", genMotorMenu())
        ->build();
}

Menu* getMenu() {
    return MenuBuilder()
        .withSubmenu("Drive", drivetrainMenu())
        ->withSubmenu("2 ft", twoFtMenu())
        ->build();
}

}   // namespace demos
