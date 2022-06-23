#include "MoveAnimation.h"


MoveAnimation::MoveAnimation(const sf::Time &time,
                             const sf::Vector2f &from,
                             const sf::Vector2f &to,
                             sf::Transformable *object)
                     : Animation(time,[to, from, object](float rate){
                           sf::Vector2f offset = to - from;
                           sf::Vector2f new_pos = from + (offset * rate);
                           object->setPosition(new_pos);
                       }){}

MoveAnimation::MoveAnimation()
    : Animation(sf::Time::Zero, [](float rate){}){
}
