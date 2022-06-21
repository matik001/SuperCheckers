#ifndef CHECKERSAI_GAMEWINDOW_H
#define CHECKERSAI_GAMEWINDOW_H
#include <TGUI/Backend/SFML-Graphics.hpp>
#include <TGUI/TGUI.hpp>
#include "../CheckersWidget.h"
#include <utility>

/// State design pattern

class WindowState;

class GameWindow{
    std::shared_ptr<sf::RenderWindow> _window;
    tgui::Gui _gui;
    std::shared_ptr<WindowState> _current_state;
public:
    GameWindow();
    void show();
    void change_state(std::shared_ptr<WindowState> new_state);

    friend class WindowState;
    friend class MenuWindowState;
    friend class GameWindowState;
    friend class ResultWindowState;
};


#endif //CHECKERSAI_GAMEWINDOW_H
