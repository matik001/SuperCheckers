#ifndef CHECKERSAI_RESULTWINDOWSTATE_H
#define CHECKERSAI_RESULTWINDOWSTATE_H


#include "../WindowState.h"

class ResultWindowState : public WindowState{
    sf::Text _result_text;
    sf::RectangleShape _background_dim;
    BoardStatus _game_result;
    std::shared_ptr<sf::Texture> _background_texture;
    std::shared_ptr<sf::Sprite> _background_sprite;
public:
    ResultWindowState(BoardStatus game_result, std::shared_ptr<sf::Texture> background_texture);

    void init(GameWindow &window) override;

    void draw() override;

    void handle_event(const sf::Event &event) override;

    void update() override;
};


#endif //CHECKERSAI_RESULTWINDOWSTATE_H