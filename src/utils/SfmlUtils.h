#ifndef CHECKERSAI_SFMLUTILS_H
#define CHECKERSAI_SFMLUTILS_H

#include "Helpers.h"
#include <TGUI/Backend/SFML-Graphics.hpp>

void scale_to_size(sf::Sprite &sprite, float width, float height);
std::shared_ptr<sf::Texture> get_screenshot(sf::RenderTarget &renderer,
                                            std::function<void(sf::RenderTarget &, sf::RenderStates)> draw);
#endif //CHECKERSAI_SFMLUTILS_H
