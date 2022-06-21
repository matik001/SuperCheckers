#include "GameWindowState.h"

#include <memory>
#include "ResultWindowState.h"
#include "../../UIConfig.h"
#include "../../../utils/SfmlUtils.h"

GameWindowState::GameWindowState(bool are_we_white, int aiLevel) : _are_we_white(are_we_white), _ai_level(aiLevel) {}


void GameWindowState::init(GameWindow &window) {
    WindowState::init(window);
    _checkers_widget = std::make_shared<CheckersWidget>(window._window->getView().getSize(),
                                                        _ai_level,
                                                        _are_we_white,
                                                        _window->_window);
}

void GameWindowState::draw() {
    _draw(*_window->_window, sf::RenderStates::Default);
}

void GameWindowState::handle_event(const sf::Event &event) {
    _checkers_widget->handle_event(event);
}

void GameWindowState::update() {
    _checkers_widget->update();

    auto game_status = _checkers_widget->get_status();
    if(_checkers_widget->is_finished()){
        auto background_texture = get_screenshot(*_window->_window,
                                                 [this](sf::RenderTarget &target, sf::RenderStates states){
            _draw(target, states);
        });
        _window->change_state(
                std::make_shared<ResultWindowState>(game_status, std::move(background_texture)));
    }
}

void GameWindowState::_draw(sf::RenderTarget &target, sf::RenderStates states) const {
    target.clear(UIConfig::bg_color);
    target.draw(*_checkers_widget);
}

