#include "GameWindow.h"

#include <utility>
#include "../UIConfig.h"
#include <memory>
#include "WindowStates/MenuWindowState.h"
#include "WindowState.h"

GameWindow::GameWindow(){
}

void GameWindow::show(){

    _window = std::make_shared<sf::RenderWindow>();
    _window->create(sf::VideoMode(700, 600), "SuperCheckers by Mateusz Kisiel",
                    sf::Style::Titlebar | sf::Style::Close, sf::ContextSettings(0,0, 16));
    _window->setFramerateLimit(60);
    _gui.setWindow(*_window);

    change_state(std::make_shared<MenuWindowState>());

    while (_window->isOpen())
    {
        sf::Event event;
        while (_window->pollEvent(event))
        {
            _gui.handleEvent(event);
            if (event.type == sf::Event::Closed)
                _window->close();

            _current_state->handle_event(event);
        }
        _current_state->update();

        _current_state->draw();
        _gui.draw();
        _window->display();
    }
}

void GameWindow::change_state(std::shared_ptr<WindowState> new_state) {
    _current_state = std::move(new_state);
    _gui.removeAllWidgets();
    _current_state->init(*this);
}

