#include "demos.h"

#include "drivetrain.h"

namespace demos {

Menu* genAxisMenu(Drivetrain::Axis axis, float speed) {
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
        ->build();
}

Menu* drivetrainMenu() {
    return MenuBuilder()
        .withSubmenu("Forward", genAxisMenu(Drivetrain::forward, 25))
        ->withSubmenu("Left", genAxisMenu(Drivetrain::left, 25))
        ->withSubmenu("Right", genAxisMenu(Drivetrain::right, 25))
        ->build();
}

Menu* getMenu() {
    return MenuBuilder().withSubmenu("Motors", drivetrainMenu())->build();
}

}   // namespace demos
