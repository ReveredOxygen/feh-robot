#include <FEHLCD.h>
#include <FEHUtility.h>

#include "gui.h"

void doNothing() {
    logger.log("doing nothing", "idk");
}

void doSomething() {
    logger.log("doing something", "idk", logging::Warning);
}

int main(void) {
    MainUI ui;

    ui.mainMenu =
        MenuBuilder()
            .withOption("View Logs", [&ui]() { ui.openView(MainUI::LogView); })
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
            ui.openView(MainUI::MenuView);
        }
    }
    // comments

    return 0;
}
