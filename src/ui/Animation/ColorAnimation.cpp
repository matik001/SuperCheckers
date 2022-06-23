#include "ColorAnimation.h"

sf::Color ColorAnimation::_calc_color(sf::Color from, sf::Color to, float rate) {
    return sf::Color(
            from.r + (sf::Uint8)((to.r - from.r)*rate),
            from.g + (sf::Uint8)((to.g - from.g)*rate),
            from.b + (sf::Uint8)((to.b - from.b)*rate),
            from.a + (sf::Uint8)((to.a - from.a)*rate)
    );
}


ColorAnimation::ColorAnimation(const sf::Time &time,  sf::Color from, sf::Color to, const std::function<void(sf::Color)>& update)
: Animation(time,[from, to, update](float rate){
    update(ColorAnimation::_calc_color(from, to, rate));
}) {}

