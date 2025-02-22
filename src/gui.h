#pragma once

#include <functional>
#include <list>
#include <string>
#include <vector>

#include "logging.h"

struct Button {
   public:
    Button(std::string text, std::function<void()> action);
    Button(std::string text, std::function<void()> action,
           unsigned int textColor, unsigned int borderColor);

    std::string text;
    std::function<void()> action;

    unsigned int textColor;
    unsigned int borderColor;

    void draw(int x, int y, int width);
};

class Menu {
   public:
    void addOption(std::string text, std::function<void()> action);
    void addSubmenu(std::string text, Menu* submenu);

    void setLeft(int left);
    void setTop(int top);
    void setWidth(int width);
    void propagatePosition();

    void draw();
    bool processClick(int x, int y);

   private:
    std::vector<Button> options;
    std::vector<Menu*> submenus;

    int activeSubmenu = -1;

    int left = 0;
    int top = 0;
    int width = 100;
};

class Tray {
   public:
    Tray();

    void draw();
    bool processClick(int x, int y);

    Button stopButton;

    bool stop = false;
};

class LogDisplay {
   public:
    void draw(std::list<logging::LogMessage>& messages);

    void setDimensions(int x1, int y1, int x2, int y2);

   private:
    int x1 = 0;
    int y1 = 0;
    int x2 = 100;
    int y2 = 100;
};

class MenuBuilder {
   public:
    MenuBuilder() {
        menu = new Menu();
    }

    Menu* build() {
        menu->propagatePosition();
        return menu;
    }

    MenuBuilder* withOption(std::string text, std::function<void()> action) {
        menu->addOption(text, action);
        return this;
    }

    MenuBuilder* withSubmenu(std::string text, Menu* submenu) {
        menu->addSubmenu(text, submenu);
        return this;
    }

   private:
    Menu* menu;
};

class MainUI {
   public:
    enum View { NullView, MenuView, LogView };

    Menu* mainMenu;
    Tray tray;
    LogDisplay logs;

    void draw();
    void update();

    void openView(View view);

    bool wantsStop();

   private:
    bool previouslyClicked = true;
    View view;
};
