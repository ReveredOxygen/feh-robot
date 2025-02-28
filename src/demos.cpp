#include "demos.h"

#include <string>

#include "drivetrain.h"

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

Menu* drivetrainMenu() {
    return MenuBuilder()
        .withSubmenu("Forward", genAxisMenu("Forward", Drivetrain::forward, 6))
        ->withSubmenu("Left", genAxisMenu("Left", Drivetrain::left, 6))
        ->withSubmenu("Right", genAxisMenu("Right", Drivetrain::right, 6))
        ->withOption("Clockwise", []() { drivetrain.rotateClockwise(6); })
        ->withOption("Counterclockwise",
                     []() { drivetrain.rotateCounterClockwise(6); })
        ->build();
}

Menu* getMenu() {
    return MenuBuilder().withSubmenu("Motors", drivetrainMenu())->build();
}

}   // namespace demos
