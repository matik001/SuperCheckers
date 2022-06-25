#include "ResultWindowState.h"

#include <utility>
#include "../../ResourcesManager.h"
#include "../../UIConfig.h"

ResultWindowState::ResultWindowState(BoardStatus game_result, std::shared_ptr<sf::Texture> background_texture)
        : _game_result(game_result), _background_texture(std::move(background_texture)),
          _background_animation(UIConfig::background_dim_time, sf::Color::Transparent, UIConfig::background_dim_color,
                                [this](sf::Color color){_background_dim.setFillColor(color);}),
          _text_animation(UIConfig::result_text_show_time, sf::Color::Transparent, sf::Color::White,
                                [this](sf::Color color){_result_text.setFillColor(color);})

{}

void ResultWindowState::init(GameWindow &window) {
    WindowState::init(window);
    _background_sprite = std::make_shared<sf::Sprite>(*_background_texture);
    _background_sprite->setPosition(0,0);
    std::wstring info = (
            _game_result == WIN_1
            ? L"Niestety porażka ;\\"
            : L"Gratulacje mistrzu! ;)"
    );
    _result_text.setFillColor(sf::Color::Transparent);
    _result_text.setFont(*ResourcesManager::singleton().get<sf::Font>(Resource::COURGETTE_FONT));
    _result_text.setString(info);
    _result_text.setCharacterSize(64);
    auto rect = _result_text.getLocalBounds();
    _result_text.setOrigin(rect.left+ rect.width/2.0, rect.top+rect.height/2.0);

    _result_text.setPosition(_window->_window->getView().getCenter());

    _background_dim.setSize(_window->_window->getView().getSize());
    _background_dim.setPosition(0, 0);

    _background_animation.start([this](){
        _text_animation.start([](){});
    });
}
void ResultWindowState::draw() {
    _window->_window->clear(UIConfig::bg_color);
    _window->_window->draw(*_background_sprite);
    _window->_window->draw(_background_dim);
    _window->_window->draw(_result_text);
}

void ResultWindowState::handle_event(const sf::Event &event) {

}

void ResultWindowState::update() {
    _text_animation.update();
    _background_animation.update();
}

