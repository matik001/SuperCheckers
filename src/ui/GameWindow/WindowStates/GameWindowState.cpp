#include "GameWindowState.h"

#include <memory>
#include <utility>
#include "ResultWindowState.h"
#include "../../UIConfig.h"
#include "../../../utils/SfmlUtils.h"

GameWindowState::GameWindowState(bool are_we_white, int aiLevel, std::shared_ptr<Board> board)
                                    : _are_we_white(are_we_white), _ai_level(aiLevel), _board(std::move(board)) {
}


void GameWindowState::init(GameWindow &window) {
    WindowState::init(window);
    window._window->setSize(UIConfig::game_window_size);
    window._window->setView(sf::View(sf::FloatRect(0,0,
                                                   UIConfig::game_window_size.x,
                                                   UIConfig::game_window_size.y)));
    _checkers_widget = std::make_shared<CheckersWidget>(_ai_level,
                                                        _are_we_white,
                                                        _window->_window,
                                                        _board);
    _init_revert();
    _init_save();
}

void GameWindowState::_init_save() {
    _save_btn = tgui::BitmapButton::create("");
    _save_btn->setSize({50, 50});
    _save_btn->getRenderer()->setTexture(*ResourcesManager::singleton().get<sf::Texture>(Resource::SAVE));
    _save_btn->getRenderer()->setTextureHover(*ResourcesManager::singleton().get<sf::Texture>(SAVE_HOVER));
    _save_btn->getRenderer()->setTextureDown(*ResourcesManager::singleton().get<sf::Texture>(SAVE_DOWN));
    _save_btn->getRenderer()->setBorders(tgui::Borders(0));
    _save_btn->getRenderer()->setBackgroundColor(sf::Color::Transparent);
    _save_btn->getRenderer()->setBackgroundColorHover(sf::Color::Transparent);
    _save_btn->getRenderer()->setBackgroundColorDown(sf::Color::Transparent);
    _save_btn->setMouseCursor(tgui::Cursor::Type::Hand);
    _save_btn->setOrigin({0.5, 0.5});
    auto pos = sf::Vector2f((UIConfig::game_window_size.x + UIConfig::board_size.x + UIConfig::board_number_margin.x)/2,
                            UIConfig::game_window_size.y - 100);
    _save_btn->setPosition(pos.x, pos.y);
    _save_btn->onClick([this](){
        _checkers_widget->save(UIConfig::save_file);
    });
    _window->_gui.add(_save_btn);

    _save_label = tgui::Label::create("SAVE");
    _save_label->getRenderer()->setTextColor(tgui::Color::White);
    _save_label->getRenderer()->setFont(*ResourcesManager::singleton().get<tgui::Font>(Resource::TGUI_UBUNTU_BOLD_FONT));
    _save_label->getRenderer()->setTextSize(16);
    _save_label->setOrigin({0.5, 0.5});
    _save_label->setPosition(pos.x, pos.y+50);

    _window->_gui.add(_save_label);
}

void GameWindowState::_init_revert() {
    _revert_btn = tgui::BitmapButton::create("");
    _revert_btn->setSize({50, 50});
    _revert_btn->getRenderer()->setTexture(*ResourcesManager::singleton().get<sf::Texture>(Resource::REVERT));
    _revert_btn->getRenderer()->setTextureHover(*ResourcesManager::singleton().get<sf::Texture>(REVERT_HOVER));
    _revert_btn->getRenderer()->setTextureDown(*ResourcesManager::singleton().get<sf::Texture>(REVERT_DOWN));
    _revert_btn->getRenderer()->setBorders(tgui::Borders(0));
    _revert_btn->getRenderer()->setBackgroundColor(sf::Color::Transparent);
    _revert_btn->getRenderer()->setBackgroundColorHover(sf::Color::Transparent);
    _revert_btn->getRenderer()->setBackgroundColorDown(sf::Color::Transparent);
    _revert_btn->setMouseCursor(tgui::Cursor::Type::Hand);
    _revert_btn->setOrigin({0.5, 0.5});
    auto pos = sf::Vector2f((UIConfig::game_window_size.x + UIConfig::board_size.x + UIConfig::board_number_margin.x)/2,55);
    _revert_btn->setPosition(pos.x, pos.y);
    _revert_btn->onClick([this](){
        _checkers_widget->revert_move();
    });
    _window->_gui.add(_revert_btn);

    _undo_label = tgui::Label::create("UNDO");
    _undo_label->getRenderer()->setTextColor(tgui::Color::White);
    _undo_label->getRenderer()->setFont(*ResourcesManager::singleton().get<tgui::Font>(Resource::TGUI_UBUNTU_BOLD_FONT));
    _undo_label->getRenderer()->setTextSize(16);
    _undo_label->setOrigin({0.5, 0.5});
    _undo_label->setPosition(pos.x, pos.y+50);

    _window->_gui.add(_undo_label);
}

void GameWindowState::draw() {
    _draw(*_window->_window, sf::RenderStates::Default);
}

void GameWindowState::handle_event(const sf::Event &event) {
    if(!_window->_gui.handleEvent(event)){
        _checkers_widget->handle_event(event);
    }
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
        return;
    }

    _revert_btn->setVisible(_checkers_widget->can_revert_move());
    _undo_label->setVisible(_checkers_widget->can_revert_move());

}

void GameWindowState::_draw(sf::RenderTarget &target, sf::RenderStates states) const {
    target.clear(UIConfig::bg_color);
    target.draw(*_checkers_widget);
    _window->_gui.draw();
}



