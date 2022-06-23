#ifndef CHECKERSAI_COLORANIMATION_H
#define CHECKERSAI_COLORANIMATION_H


#include "Animation.h"

class ColorAnimation : public Animation {
    static sf::Color _calc_color(sf::Color from, sf::Color to, float rate);
public:
    ColorAnimation(const sf::Time &time, sf::Color from, sf::Color to, const std::function<void(sf::Color)>& update);
};


#endif //CHECKERSAI_COLORANIMATION_H
