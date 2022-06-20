#include "ResultWindowState.h"

#include <utility>
#include "../../ResourcesManager.h"
#include "../../UIConfig.h"

ResultWindowState::ResultWindowState(BoardStatus game_result, std::shared_ptr<sf::Texture> background_texture)
        : _game_result(game_result), _background_texture(std::move(background_texture)) {
}

void ResultWindowState::init(GameWindow &window) {
    WindowState::init(window);
    _background_sprite = std::make_shared<sf::Sprite>(*_background_texture);
    _background_sprite->setPosition(0,0);
    std::wstring info = (
            _game_result == WIN_1
            ? L"Niestety porażka ;\\"
            : L"Gratulacje mistrzu! ;)"
    );
    _result_text.setFont(*std::static_pointer_cast<sf::Font>(ResourcesManager::singleton().get(Resource::COURGETTE_FONT)));
    _result_text.setString(info);
    _result_text.setCharacterSize(64);
    _result_text.setFillColor(sf::Color::White);
    auto rect = _result_text.getLocalBounds();
    _result_text.setOrigin(rect.left+ rect.width/2.0, rect.top+rect.height/2.0);

    _result_text.setPosition(_window->_window.getView().getCenter());

    _background_dim.setSize(_window->_window.getView().getSize());
    _background_dim.setPosition(0, 0);
    _background_dim.setFillColor(sf::Color(0, 0, 0, 170));
}
void ResultWindowState::draw() {
    _window->_window.clear(UIConfig::bg_color);
    _window->_window.draw(*_background_sprite);
    _window->_window.draw(_background_dim);
    _window->_window.draw(_result_text);
}

void ResultWindowState::handle_event(const sf::Event &event) {

}

void ResultWindowState::update() {

}

