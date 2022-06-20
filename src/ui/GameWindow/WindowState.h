#ifndef CHECKERSAI_WINDOWSTATE_H
#define CHECKERSAI_WINDOWSTATE_H

#include "GameWindow.h"

class WindowState{
protected:
    GameWindow *_window;
public:
    virtual void init(GameWindow &window);
    virtual void draw() = 0;
    virtual void handle_event(const sf::Event &event) = 0;
    virtual void update() = 0;
};

#endif //CHECKERSAI_WINDOWSTATE_H
