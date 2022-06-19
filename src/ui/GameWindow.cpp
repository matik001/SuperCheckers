#include "GameWindow.h"
#include "UIConfig.h"


GameWindow::GameWindow(){
    checkers_widget = std::make_shared<CheckersWidget>(sf::Vector2u(700,600), 5);
}
/// TODO STATY

void GameWindow::show(){
    _window.create(sf::VideoMode(700, 600), "SuperCheckers by Mateusz Kisiel",
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
            if(checkers_widget->get_status() == IN_PROGRESS)
                checkers_widget->handle_event(event, _window);
            else
            result_info.init(checkers_widget->get_status(), _window);
        }
        _window.clear(UIConfig::bg_color);
        if(checkers_widget->get_status() == IN_PROGRESS)
            _window.draw(*checkers_widget);
        else
            _window.draw(result_info);

        _window.display();
    }
}
