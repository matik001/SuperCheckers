#ifndef CHECKERSAI_GAMEWINDOW_H
#define CHECKERSAI_GAMEWINDOW_H
#include <SFML/Graphics.hpp>
#include "CheckersWidget.h"

class GameWindow {
    sf::RenderWindow _window;
    std::shared_ptr<CheckersWidget> checkers_widget;
public:
    GameWindow();
    void show();

};


#endif //CHECKERSAI_GAMEWINDOW_H
