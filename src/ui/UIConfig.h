#ifndef CHECKERSAI_CONFIG_H
#define CHECKERSAI_CONFIG_H

#include <TGUI/Backend/SFML-Graphics.hpp>

class UIConfig{
public:
    static const sf::Color bg_color;
    static const sf::Color field_color1;
    static const sf::Color field_color2;
    static const sf::Color hover_piece_color;
    static const sf::Color selected_piece_color;
    static const sf::Color possible_move_color;
    static const sf::Color must_beat_color;
    static const sf::Color board_field_caption_color;

    static const sf::Time move_animation_time;
    static const sf::Time background_dim_time;
    static const sf::Color background_dim_color;
    static const sf::Time result_text_show_time;

    static const sf::Vector2<unsigned int> game_window_size;
    static const sf::Vector2f board_size;
    static const sf::Vector2f board_number_margin;
    static const sf::Color margin_color1;
    static const sf::Color margin_color2;

    static const std::string save_file;

};

#endif //CHECKERSAI_CONFIG_H
