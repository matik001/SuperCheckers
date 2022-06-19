//
// Created by mateu on 6/17/2022.
//

#ifndef CHECKERSAI_CHECKERSWIDGET_H
#define CHECKERSAI_CHECKERSWIDGET_H


#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <memory>
#include "../engine/Game.h"
#include "UserUIAgent.h"

#define FIELDS_IN_ROW  8
#define FIELDS_IN_COLUMN  8

class CheckersWidget : public sf::Drawable{
    std::shared_ptr<UserUIAgent> _user_agent;
    std::shared_ptr<MinMaxAgent> _computer_agent;
    std::shared_ptr<Game> _game;
    sf::Vector2u _size;
    sf::Vector2f _field_size;
    sf::RectangleShape _field_sprites[8][8];
    sf::Sprite _pieces_sprites[8][8];
    std::optional<sf::Vector2u> _hovered_field = std::nullopt;
    std::optional<sf::Vector2u> _selected_field = std::nullopt;
    std::vector<Move> _possible_moves; /// mozliwe ruchy obecnie wybranej figury


    std::optional<sf::Vector2u> _map_pos_to_field(sf::Vector2f pos) const;
    void _update_cursor(sf::RenderWindow &window);
    void _update_possible_moves();
    void _update_field_sprites();
    void _update_pieces_sprites();
    void _draw_board(sf::RenderTarget &target, sf::RenderStates states) const;
    void _draw_pieces(sf::RenderTarget &target, sf::RenderStates states) const;
public:
    CheckersWidget(sf::Vector2u size, int computer_level);
    void handle_event(const sf::Event &event, sf::RenderWindow &window);


protected:
    void draw(sf::RenderTarget &target, sf::RenderStates states) const override;
};


#endif //CHECKERSAI_CHECKERSWIDGET_H
