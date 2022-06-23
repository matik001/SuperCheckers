#ifndef CHECKERSAI_MOVEANIMATION_H
#define CHECKERSAI_MOVEANIMATION_H
#include <TGUI/Backend/SFML-Graphics.hpp>
#include <future>
#include <thread>
#include "Animation.h"

class MoveAnimation : public Animation{
public:
    MoveAnimation();
    MoveAnimation(const sf::Time &time, const sf::Vector2f &from,
                  const sf::Vector2f &to, sf::Transformable *object);
};


#endif //CHECKERSAI_MOVEANIMATION_H
