#include "milestones.h"

#include "gui.h"
#include "logging.h"

namespace milestones {

Menu* getMenu() {
    return MenuBuilder()
        .withSubmenu("Milestone 1", MenuBuilder()
                                        .withOption("Part 2", []() {})
                                        ->withOption("Part 3", []() {})
                                        ->build())
        ->build();
}

void milestone1Part2() {
    logger.log("Begin Milestone 1 Part 2", "gui");
    ui.openView(MainUI::LogView);

    // Complete the actual milestone
}

void milestone1Part3() {
    logger.log("Begin Milestone 1 Part 3", "gui");
    ui.openView(MainUI::LogView);

    // Complete the actual milestone
}

}   // namespace milestones
