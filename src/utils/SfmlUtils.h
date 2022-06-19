#ifndef CHECKERSAI_SFMLUTILS_H
#define CHECKERSAI_SFMLUTILS_H


#include <SFML/Graphics/Sprite.hpp>
#include "../engine/Helpers.h"

void scale_to_size(sf::Sprite &sprite, float width, float height){
    auto rect = sprite.getTextureRect();
    float scale_x = width/ rect.width;
    float scale_y = height/ rect.height;
    float mini = min(scale_x, scale_y);
    sprite.setScale(mini, mini);
}

#endif //CHECKERSAI_SFMLUTILS_H
