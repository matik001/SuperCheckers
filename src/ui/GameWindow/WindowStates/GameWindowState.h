#ifndef CHECKERSAI_GAMEWINDOWSTATE_H
#define CHECKERSAI_GAMEWINDOWSTATE_H


#include "../WindowState.h"

class GameWindowState  : public WindowState{
    std::shared_ptr<CheckersWidget> _checkers_widget;
    std::shared_ptr<Board> _board = nullptr;

    bool _are_we_white;
    int _ai_level;
    tgui::BitmapButton::Ptr _revert_btn;
    tgui::Label::Ptr _undo_label;

    tgui::BitmapButton::Ptr _save_btn;
    tgui::Label::Ptr _save_label;

    void _init_revert();
    void _init_save();


    void _draw(sf::RenderTarget &target, sf::RenderStates states) const;
public:
    GameWindowState(bool are_we_white, int aiLevel, std::shared_ptr<Board> board = nullptr);

    void init(GameWindow &window) override;

    void draw() override;

    void handle_event(const sf::Event &event) override;

    void update() override;
};


#endif //CHECKERSAI_GAMEWINDOWSTATE_H
