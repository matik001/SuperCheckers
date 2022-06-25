#include "ResultWindowState.h"

#include <utility>
#include "../../ResourcesManager.h"
#include "../../UIConfig.h"
#include "MenuWindowState.h"

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
        _text_animation.start([this](){
            _show_menu_btn(); /// TODO show with effect
        });
    });
}
void ResultWindowState::draw() {
    _window->_window->clear(UIConfig::bg_color);
    _window->_window->draw(*_background_sprite);
    _window->_window->draw(_background_dim);
    _window->_window->draw(_result_text);
    _window->_gui.draw();
}

void ResultWindowState::handle_event(const sf::Event &event) {
    _window->_gui.handleEvent(event);
}

void ResultWindowState::update() {
    _text_animation.update();
    _background_animation.update();
}




void ResultWindowState::_show_menu_btn() {
    _menu_btn = tgui::BitmapButton::create("");
    _menu_btn->setSize({50, 50});
    _menu_btn->getRenderer()->setTexture(*ResourcesManager::singleton().get<sf::Texture>(Resource::MENU));
    _menu_btn->getRenderer()->setTextureHover(*ResourcesManager::singleton().get<sf::Texture>(MENU_HOVER));
    _menu_btn->getRenderer()->setTextureDown(*ResourcesManager::singleton().get<sf::Texture>(MENU_DOWN));
    _menu_btn->getRenderer()->setBorders(tgui::Borders(0));
    _menu_btn->getRenderer()->setBackgroundColor(sf::Color::Transparent);
    _menu_btn->getRenderer()->setBackgroundColorHover(sf::Color::Transparent);
    _menu_btn->getRenderer()->setBackgroundColorDown(sf::Color::Transparent);
    _menu_btn->setMouseCursor(tgui::Cursor::Type::Hand);
    _menu_btn->setOrigin({0.5, 0.5});
    auto pos = sf::Vector2f((UIConfig::game_window_size.x + UIConfig::board_size.x + UIConfig::board_number_margin.x)/2,55);
    _menu_btn->setPosition(pos.x, pos.y);
    _menu_btn->onClick([this]() {
        _window->change_state(std::make_shared<MenuWindowState>());
        return;
    });

    _window->_gui.add(_menu_btn);

    _menu_label = tgui::Label::create("MENU");
    _menu_label->getRenderer()->setTextColor(tgui::Color::White);
    _menu_label->getRenderer()->setFont(*ResourcesManager::singleton().get<tgui::Font>(Resource::TGUI_UBUNTU_BOLD_FONT));
    _menu_label->getRenderer()->setTextSize(16);
    _menu_label->setOrigin({0.5, 0.5});
    _menu_label->setPosition(pos.x, pos.y+50);

    _window->_gui.add(_menu_label);

    _menu_btn->showWithEffect(tgui::ShowEffectType::SlideFromTop, tgui::Duration(300));
    _menu_label->showWithEffect(tgui::ShowEffectType::SlideFromTop, tgui::Duration(300));

}