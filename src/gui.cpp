#include "gui.h"

#include <FEHBattery.h>
#include <FEHLCD.h>

#include <algorithm>

#include "logging.h"

using namespace std;

const unsigned int TEXT_COLOR = WHITE;
const unsigned int BUTTON_COLOR = DEEPSKYBLUE;
const unsigned int BACKGROUND_COLOR = BLACK;

const int BUTTON_PADDING = 3;
const int TEXT_HEIGHT = 14;
const int BUTTON_HEIGHT = BUTTON_PADDING * 2 + TEXT_HEIGHT;
const int LETTER_WIDTH = 12;
const int LETTER_HEIGHT = 17;
const int TRAY_HEIGHT = 20;
const int MENU_WIDTH = 150;

void Menu::addOption(std::string text, std::function<void()> action) {
    options.push_back(Button(text, action));
}

void Menu::addSubmenu(std::string text, Menu* submenu) {
    submenus.push_back(submenu);

    submenu->options.insert(submenu->options.begin(), Button("Back", [this]() {
                                this->activeSubmenu = -1;
                            }));

    options.push_back(
        Button(text, [this]() { this->activeSubmenu = submenus.size() - 1; }));
}

void Menu::setLeft(int left) {
    this->left = left;

    for (Menu* child : submenus) {
        child->setLeft(left);
    }
}
void Menu::setTop(int top) {
    this->top = top;

    for (Menu* child : submenus) {
        child->setTop(top);
    }
}
void Menu::setWidth(int width) {
    this->width = width;

    for (Menu* child : submenus) {
        child->setWidth(width);
    }
}

void Menu::propagatePosition() {
    setLeft(left);
    setTop(top);
    setWidth(width);
}

void Menu::draw() {
    if (activeSubmenu == -1) {
        LCD.SetFontColor(BUTTON_COLOR);
        LCD.DrawVerticalLine(width - 1, top, 239);

        int currY = top;
        for (Button option : options) {
            option.draw(left, currY, width);

            currY += BUTTON_HEIGHT;
        }
    } else {
        submenus[activeSubmenu]->draw();
    }
}

bool Menu::processClick(int x, int y) {
    if (activeSubmenu == -1) {
        if (y < top || x < left || x > left + width) {
            return false;
        }

        int buttonIdx = (y - top) / BUTTON_HEIGHT;

        if (buttonIdx < options.size()) {
            options[buttonIdx].action();
            return true;
        }

        return false;
    } else {
        return submenus[activeSubmenu]->processClick(x, y);
    }
}

/*
 * Methods for Button
 */

Button::Button(std::string text, std::function<void()> action) {
    this->text = text;
    this->action = action;
    this->textColor = TEXT_COLOR;
    this->borderColor = BUTTON_COLOR;
}

Button::Button(std::string text, std::function<void()> action,
               unsigned int textColor, unsigned int borderColor) {
    this->text = text;
    this->action = action;
    this->textColor = textColor;
    this->borderColor = borderColor;
}

void Button::draw(int x, int y, int width) {
    if (width == -1) {
        width = BUTTON_PADDING * 2 - 2 + (LETTER_WIDTH + 2) * text.length();
    }

    LCD.SetFontColor(borderColor);
    LCD.DrawRectangle(x, y, width, BUTTON_HEIGHT);

    LCD.SetFontColor(textColor);
    LCD.WriteAt(
        text.substr(0, (width - BUTTON_PADDING * 2 - 2) / (LETTER_WIDTH))
            .c_str(),
        x + BUTTON_PADDING - 2, y + BUTTON_PADDING);
}

/*
 * Methods for Tray
 */

Tray::Tray() : stopButton("STOP", [this]() { this->stop = true; }, RED, RED) {
    this->stop = false;
}

void Tray::draw() {
    LCD.SetFontColor(BACKGROUND_COLOR);
    LCD.FillRectangle(0, 0, 319, TRAY_HEIGHT);
    LCD.SetFontColor(BUTTON_COLOR);
    LCD.DrawHorizontalLine(TRAY_HEIGHT + 1, 0, 319);

    LCD.SetFontColor(TEXT_COLOR);
    char voltage[10];
    sprintf(voltage, "%2.1f V", Battery.Voltage());
    LCD.WriteAt(voltage, 320 - BUTTON_PADDING - LETTER_WIDTH * 7,
                BUTTON_PADDING);

    stopButton.draw(0, 0, -1);
}

bool Tray::processClick(int x, int y) {
    int stopWidth = BUTTON_PADDING * 2 - 2 + (LETTER_WIDTH + 2) * 4;

    if (x < stopWidth && y < TRAY_HEIGHT) {
        stopButton.action();
        return true;
    }

    return false;
}

/*
 * Methods for LogDisplay
 */

void LogDisplay::draw(list<logging::LogMessage>& messages) {
    int cols = (x2 - x1) / LETTER_WIDTH;
    int rows = (y2 - y1) / LETTER_HEIGHT;

    int currY = y2;

    for (auto it = messages.rbegin(); it != messages.rend(); ++it) {
        switch (it->level) {
            case logging::Debug:
                LCD.SetFontColor(GRAY);
                break;
            case logging::Info:
                LCD.SetFontColor(TEXT_COLOR);
                break;
            case logging::Warning:
                LCD.SetFontColor(YELLOW);
                break;
            case logging::Error:
                LCD.SetFontColor(RED);
                break;
            default:
                break;
        }

        int len = it->message.length();
        int rowsNeeded = (len + (cols - 1)) / cols;
        currY -= LETTER_HEIGHT * rowsNeeded;
        for (int i = 0; i < rowsNeeded; i++) {
            auto line = it->message.substr(i * cols, (i + 1) * cols);
            if (currY + (i + 1) * LETTER_HEIGHT >= y1) {
                LCD.WriteAt(line.c_str(), x1, currY + i * LETTER_HEIGHT);
            }
        }

        if (currY + LETTER_HEIGHT < y1) {
            break;
        }
    }
}

void LogDisplay::setDimensions(int x1, int y1, int x2, int y2) {
    this->x1 = x1;
    this->y1 = y1;
    this->x2 = x2;
    this->y2 = y2;
}

/*
 * Methods for MainUI
 */

void MainUI::draw() {
    switch (view) {
        case NullView:
            LCD.WriteLine("This screen intentionally left blank");
            break;
        case MenuView:
            mainMenu->draw();
            logs.draw(logger.recent);
            tray.draw();
            break;
        case LogView:
            logs.draw(logger.recent);
            tray.draw();
            break;
        default:
            LCD.WriteLine("Invalid view :(");
            break;
    }
}

void MainUI::update() {
    if (needsRedraw) {
        LCD.Clear(BACKGROUND_COLOR);
        draw();
        needsRedraw = false;
    }

    int x, y;
    if (LCD.Touch(&x, &y)) {
        if (!previouslyClicked) {
            if (y > 12) {
                // The screen has a vertical offset between the display and
                // touch. This accounts for that
                y -= 12;
            }

            needsRedraw |= tray.processClick(x, y);
            needsRedraw |= mainMenu->processClick(x, y);

            if (logger.newMessages) {
                logger.newMessages = false;
                needsRedraw = true;
            }
        }

        previouslyClicked = true;
    } else {
        previouslyClicked = false;
    }
}

void MainUI::openView(View view) {
    this->view = view;

    switch (view) {
        case MenuView:
            mainMenu->setTop(TRAY_HEIGHT);
            mainMenu->setWidth(MENU_WIDTH);

            logs.setDimensions(MENU_WIDTH, TRAY_HEIGHT, 320, 240);
            break;
        case LogView:
            logs.setDimensions(0, TRAY_HEIGHT, 320, 240);
            break;
    }
}

bool MainUI::wantsStop() {
    bool result = false;

    if (tray.stop) {
        result = true;
        tray.stop = false;
    }

    return result;
}

MainUI ui;
