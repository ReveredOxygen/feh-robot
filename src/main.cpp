#include <FEHLCD.h>
#include <FEHUtility.h>

#include "drivetrain.h"
#include "gui.h"
#include "milestones.h"

void doNothing() {
    logger.log("doing nothing", "idk");
}

void doSomething() {
    logger.log("doing something", "idk", logging::Warning);
}

int main(void) {
    ui.mainMenu =
        MenuBuilder()
            .withOption("View Logs", []() { ui.openView(MainUI::LogView); })
            ->withOption("Check Bat", []() {})
            ->withSubmenu("Milestones", milestones::getMenu())
            ->withOption("do nothing", doNothing)
            ->withOption("do something", doSomething)
            ->withSubmenu(
                "submenu",
                MenuBuilder().withOption("do nothing", doNothing)->build())
            ->build();

    ui.openView(MainUI::MenuView);

    logger.log("Started gui", "gui");

    while (1) {
        ui.update();

        if (ui.wantsStop()) {
            logger.log("Stopping", "gui");
            drivetrain.stop();
            ui.openView(MainUI::MenuView);
        }
    }
    // comments

    return 0;
}
