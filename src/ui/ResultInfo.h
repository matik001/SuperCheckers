#ifndef CHECKERSAI_RESULTINFO_H
#define CHECKERSAI_RESULTINFO_H


#include <SFML/Graphics.hpp>
#include "../engine/Board.h"

class ResultInfo : public sf::Drawable{
    sf::Text _result_text;
    sf::RectangleShape _background;
    bool _inited = false;
public:
    void init(BoardState result, const sf::RenderWindow &window);
protected:
    void draw(sf::RenderTarget &target, sf::RenderStates states) const override;
};


#endif //CHECKERSAI_RESULTINFO_H
