#ifndef CHECKERSAI_CHECKERSWIDGET_H
#define CHECKERSAI_CHECKERSWIDGET_H


#include <TGUI/Backend/SFML-Graphics.hpp>
#include <SFML/Window.hpp>
#include <memory>
#include <utility>
#include "../engine/Game.h"
#include "UserUIAgent.h"
#include "ResourcesManager.h"
#include "MoveAnimation.h"

#define FIELDS_IN_ROW  8
#define FIELDS_IN_COLUMN  8
struct Piece{
    sf::Vector2u pos;
    sf::Sprite sprite;
    Piece(){}
    Piece(const sf::Vector2u &pos) : pos(pos) {}
    Piece(const sf::Vector2u &pos, sf::Sprite &sprite) : pos(pos), sprite(std::move(sprite)) {}
};
class CheckersWidget : public sf::Drawable{
    std::shared_ptr<UserUIAgent> _user_agent;
    std::shared_ptr<MinMaxAgent> _computer_agent;
    std::shared_ptr<Game> _game;
    sf::Vector2f _size;
    sf::Vector2f _field_size;
    sf::RectangleShape _field_sprites[8][8];
    std::vector<std::shared_ptr<Piece>> _pieces;
    std::shared_ptr<sf::RenderWindow> _window;
    std::optional<sf::Vector2u> _hovered_field = std::nullopt;
    std::optional<sf::Vector2u> _selected_field = std::nullopt;
    std::vector<Move> _possible_moves; /// mozliwe ruchy obecnie wybranej figury
    bool _are_we_white; /// jest to tylko informacja jakiego koloru rysowac nasze pionki, my zawsze jestesmy graczem 2 z _game
    bool _is_move_animation_now() const;
    std::shared_ptr<MoveAnimation> _move_animation;

    std::optional<sf::Vector2u> _map_pos_to_field(sf::Vector2f pos)  const;
    sf::Vector2f _map_field_to_pos(sf::Vector2u pos) const;
    std::shared_ptr<Piece> _find_piece(sf::Vector2u pos) const;
    std::shared_ptr<Piece> _find_piece_or_create(sf::Vector2u pos);

    void _update_cursor();
    void _update_possible_moves();
    void _update_field_sprites();
    void _update_pieces_sprites();
    Resource _board_field_to_texture_id(BoardField field) const;
    void _draw_board(sf::RenderTarget &target, sf::RenderStates states) const;
    void _draw_pieces(sf::RenderTarget &target, sf::RenderStates states) const;
    void _play_next_move(const std::function<void()>& callback);
    void _play_enemy_moves();
    void _play_user_move(const Move& move);
public:
    CheckersWidget(sf::Vector2<float> size, int computer_level, bool are_we_white, std::shared_ptr<sf::RenderWindow> window);
    void handle_event(const sf::Event &event);
    void update();
    BoardStatus get_status() const;
    bool is_finished() const; /// true jezeli gra sie skonczyla i zakonczyly sie animacje

protected:
    void draw(sf::RenderTarget &target, sf::RenderStates states) const override;
};


#endif //CHECKERSAI_CHECKERSWIDGET_H
