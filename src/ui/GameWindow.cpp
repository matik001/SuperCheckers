#include "GameWindow.h"
#include "UIConfig.h"


GameWindow::GameWindow(){
    checkers_widget = std::make_shared<CheckersWidget>(sf::Vector2u(800,600), 5);
}

void GameWindow::show(){
    _window.create(sf::VideoMode(800, 600), "SuperCheckers by Mateusz Kisiel",
                    sf::Style::Default, sf::ContextSettings(0,0, 16));
    _window.setFramerateLimit(60);
//    _window.setVerticalSyncEnabled(true);

    while (_window.isOpen())
    {
        sf::Event event;
        while (_window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                _window.close();

            checkers_widget->handle_event(event, _window);
        }
        _window.clear(UIConfig::bg_color);
        _window.draw(*checkers_widget);
        _window.display();
    }
}
