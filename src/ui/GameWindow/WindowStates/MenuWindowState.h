#ifndef CHECKERSAI_MENUWINDOWSTATE_H
#define CHECKERSAI_MENUWINDOWSTATE_H

#include "../WindowState.h"
#include "../GameWindow.h"

class MenuWindowState : public WindowState{
    tgui::Label::Ptr _level_label;
    tgui::Label::Ptr _title_label;
    tgui::Slider::Ptr _difficulty_slider;
    tgui::CheckBox::Ptr _color_checkbox;
    tgui::Button::Ptr _new_game_btn;
    tgui::Button::Ptr _load_game_btn;

    void _handle_new_game();
    void _handle_load_game();
    void _handle_changed_difficulty();
    sf::Color _difficulty_to_color(int value);
public:
    void init(GameWindow &window) override;
    void draw() override;
    void handle_event(const sf::Event &event) override;
    void update() override;

};


#endif //CHECKERSAI_MENUWINDOWSTATE_H
