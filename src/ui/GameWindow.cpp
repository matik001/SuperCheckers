#include "GameWindow.h"


GameWindow::GameWindow(){
}

void GameWindow::show(){
    _window.create(sf::VideoMode(800, 600), "SuperCheckers by Mateusz Kisiel");

    while (_window.isOpen())
    {
        sf::Event event;
        while (_window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                _window.close();
        }
    }
}
