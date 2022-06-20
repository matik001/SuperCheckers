#ifndef CHECKERSAI_GAMEWINDOWSTATE_H
#define CHECKERSAI_GAMEWINDOWSTATE_H


#include "../WindowState.h"

class GameWindowState  : public WindowState{
    std::shared_ptr<CheckersWidget> _checkers_widget;
    bool _are_we_white;
    int _ai_level;

    void _draw(sf::RenderTarget &target, sf::RenderStates states) const;
public:
    GameWindowState(bool are_we_white, int aiLevel);

    void init(GameWindow &window) override;

    void draw() override;

    void handle_event(const sf::Event &event) override;

    void update() override;
};


#endif //CHECKERSAI_GAMEWINDOWSTATE_H
