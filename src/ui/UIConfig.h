#ifndef CHECKERSAI_CONFIG_H
#define CHECKERSAI_CONFIG_H

#include <SFML/Graphics/Color.hpp>

class UIConfig{
public:
    static const sf::Color bg_color;
    static const sf::Color field_color1;
    static const sf::Color field_color2;
    static const sf::Color hover_piece_color;
    static const sf::Color selected_piece_color;
    static const sf::Color possible_move_color;
};

#endif //CHECKERSAI_CONFIG_H
