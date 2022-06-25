#include "MenuWindowState.h"
#include "../../../utils/TGUIMenuFormPreprocess.h"
#include "GameWindowState.h"

void MenuWindowState::init(GameWindow &window) {
    WindowState::init(window);
    auto cursor = sf::Cursor();
    cursor.loadFromSystem(sf::Cursor::Hand);
    window._window->setMouseCursor(cursor);
    window._window->setSize(sf::Vector2u(700, 600));

    std::stringstream  ss(gen_menu_form());
    window._gui.loadWidgetsFromStream(ss);
    _level_label = window._gui.get<tgui::Label>("level_label");
    _title_label = window._gui.get<tgui::Label>("title_label");
    _difficulty_slider = window._gui.get<tgui::Slider>("difficulty_slider");
    _color_checkbox = window._gui.get<tgui::CheckBox>("color_checkbox");
    _new_game_btn = window._gui.get<tgui::Button>("new_game_btn");
    _load_game_btn = window._gui.get<tgui::Button>("load_game_btn");

    _handle_changed_difficulty();
    _new_game_btn->onClick([this]{ _handle_new_game();});
    _load_game_btn->onClick([this]{ _handle_load_game();});
    _difficulty_slider->onValueChange([this]{_handle_changed_difficulty() ;});

    auto font_bold = ResourcesManager::singleton().get<tgui::Font>(TGUI_UBUNTU_BOLD_FONT);
    _title_label->getRenderer()->setFont(*font_bold);
    _level_label->getRenderer()->setFont(*font_bold);
    _title_label->getRenderer()->setFont(*font_bold);
    _new_game_btn->getRenderer()->setFont(*font_bold);
    _load_game_btn->getRenderer()->setFont(*font_bold);

}


void MenuWindowState::draw() {
    _window->_gui.draw();
}

void MenuWindowState::handle_event(const sf::Event &event) {
    _window->_gui.handleEvent(event);
}

void MenuWindowState::update() {
}

void MenuWindowState::_handle_new_game() {
    int ai_level = (int)_difficulty_slider->getValue();
    bool are_we_white = _color_checkbox->isChecked();
    _window->change_state(std::make_shared<GameWindowState>(are_we_white, ai_level));
}

void MenuWindowState::_handle_load_game() {

}

void MenuWindowState::_handle_changed_difficulty() {
    int value = (int)_difficulty_slider->getValue();
    _level_label->setText("LEVEL " + std::to_string(value));
    _level_label->getRenderer()->setTextColor(_difficulty_to_color(value));
}

sf::Color MenuWindowState::_difficulty_to_color(int value) {
    sf::Color start_color = sf::Color(255, 183, 0);
    sf::Color end_color = sf::Color(177, 11, 0);
    sf::Vector3f dif = sf::Vector3f (end_color.r - start_color.r,
                            end_color.g - start_color.g,
                            end_color.b - start_color.b);
    double ratio = value / (double)_difficulty_slider->getMaximum();
    sf::Color color = sf::Color(start_color.r + (int)(dif.x*ratio),
                                start_color.g + (int)(dif.y*ratio),
                                start_color.b + (int)(dif.z*ratio));
    return color;
}
