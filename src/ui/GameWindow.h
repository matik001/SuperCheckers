#ifndef CHECKERSAI_GAMEWINDOW_H
#define CHECKERSAI_GAMEWINDOW_H
#include <SFML/Window.hpp>

class GameWindow {
    sf::Window _window;
public:
    GameWindow();
    void show();

};


#endif //CHECKERSAI_GAMEWINDOW_H
