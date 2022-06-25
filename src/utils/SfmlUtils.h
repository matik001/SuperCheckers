#ifndef CHECKERSAI_SFMLUTILS_H
#define CHECKERSAI_SFMLUTILS_H

#include "Helpers.h"
#include <TGUI/Backend/SFML-Graphics.hpp>

void scale_to_size(sf::Sprite &sprite, float width, float height);
void center_text_origin(sf::Text &text);
void center_shape_origin(sf::Shape &shape);
std::shared_ptr<sf::Texture> multiply_color(sf::Texture &texture, sf::Color color);
std::shared_ptr<sf::Texture> add_color(sf::Texture &texture, sf::Color color);
std::shared_ptr<sf::Texture> subtract_color(sf::Texture &texture, sf::Color color);
std::shared_ptr<sf::Texture> get_screenshot(sf::RenderTarget &renderer,
                                            const std::function<void(sf::RenderTarget &, sf::RenderStates)>& draw);
#endif //CHECKERSAI_SFMLUTILS_H
