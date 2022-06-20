#include "CheckersWidget.h"
#include "ResourcesManager.h"
#include "UIConfig.h"
#include "../utils/SfmlUtils.h"

CheckersWidget::CheckersWidget(sf::Vector2<float> size, int computer_level, bool are_we_white)
        : _are_we_white(are_we_white) {
    this->_size = size;
    _field_size = sf::Vector2f(_size.x / (float)FIELDS_IN_ROW, _size.y / (float)FIELDS_IN_COLUMN);

    _user_agent = std::make_shared<UserUIAgent>();
    _computer_agent = std::make_shared<MinMaxAgent>(computer_level);
    _game = std::make_shared<Game>(_computer_agent.get(), _user_agent.get(), !are_we_white);
    _update_field_sprites();
    _update_pieces_sprites();
}


void CheckersWidget::draw(sf::RenderTarget &target, sf::RenderStates states) const {
    _draw_board(target, states);
    _draw_pieces(target, states);
}

Resource CheckersWidget::_board_field_to_texture_id(BoardField field){
    auto queen1 = Resource::WHITE_QUEEN;
    auto queen2 = Resource::BLACK_QUEEN;
    auto pawn1 = Resource::WHITE_PAWN;
    auto pawn2 = Resource::BLACK_PAWN;
    if(_are_we_white){
        std::swap(queen1, queen2);
        std::swap(pawn1, pawn2);
    }
    switch (field) {
        case BoardField::QUEEN1:
            return queen1;
        case BoardField::QUEEN2:
            return queen2;
        case BoardField::PAWN1:
            return pawn1;
        case BoardField::PAWN2:
            return pawn2;
        case NOTHING:
            std::cout << "_board_field_to_texture_id - field can't be NOTHING";
            exit(1);
    }
}

void CheckersWidget::_update_pieces_sprites() {
    for(int i = 0; i<FIELDS_IN_ROW; i++){
        for(int j = 0; j<FIELDS_IN_COLUMN; j++){
            sf::Vector2f pos = _map_field_to_pos(sf::Vector2u(i, j));
            std::shared_ptr<void> texture;
            auto field = _game->board.get_field(i, j);
            if(field == NOTHING)
                continue;

            Resource resource_id = _board_field_to_texture_id(field);
            texture = ResourcesManager::singleton().get(resource_id);

            _pieces_sprites[i][j].setTexture(*std::static_pointer_cast<sf::Texture>(texture));
            scale_to_size(_pieces_sprites[i][j], _field_size.x-10, _field_size.y-10);
            _pieces_sprites[i][j].setOrigin(_pieces_sprites[i][j].getTextureRect().width/2.0, _pieces_sprites[i][j].getTextureRect().height/2.0);
            _pieces_sprites[i][j].setPosition(pos);
        }
    }
}

void CheckersWidget::_update_field_sprites() {
    for(int i = 0; i<FIELDS_IN_ROW; i++){
        for(int j = 0; j<FIELDS_IN_COLUMN; j++){
            sf::Vector2f pos = sf::Vector2f(_field_size.x * i, _field_size.y * j);
            _field_sprites[i][j].setSize(_field_size);
            _field_sprites[i][j].setPosition(pos);
            _field_sprites[i][j].setOutlineThickness(1);
            _field_sprites[i][j].setOutlineColor(sf::Color::Black);
            sf::Color color = ( (i+j) % 2 == 0
                                ?   UIConfig::field_color1
                                :   UIConfig::field_color2);
            _field_sprites[i][j].setFillColor(color);
        }
    }
    if(!_game->board.get_player_on_move()){
        if(_hovered_field != std::nullopt){
            BoardField field = _game->board.get_field(_hovered_field->x, _hovered_field->y);
            if(field != NOTHING && _game->board.get_player_on_move() == get_board_field_color(field))
                _field_sprites[_hovered_field->x][_hovered_field->y].setFillColor(UIConfig::hover_piece_color);
        }
        if(_selected_field != std::nullopt){
            _field_sprites[_selected_field->x][_selected_field->y].setFillColor(UIConfig::selected_piece_color);
        }
        for (auto move: _possible_moves) {
            _field_sprites[move.to.x][move.to.y].setFillColor(UIConfig::possible_move_color);
        }
    }
}

void CheckersWidget::_update_cursor(sf::RenderWindow &window) {
    sf::Cursor cursor;
    cursor.loadFromSystem(sf::Cursor::Arrow);
    if(_hovered_field != std::nullopt && !_game->board.get_player_on_move()){
        BoardField field = _game->board.get_field(_hovered_field->x, _hovered_field->y);
        /// jezeli jest to nasza figura i jestesmy na ruchu
        if(field != NOTHING && _game->board.get_player_on_move() == get_board_field_color(field))
            cursor.loadFromSystem(sf::Cursor::Hand);

        /// jezeli jest to miejsce gdzie mozemy zagrac
        if(std::any_of(_possible_moves.begin(), _possible_moves.end(),
                    [this](const Move &move){return move.to.x == _hovered_field->x && move.to.y == _hovered_field->y;}))
            cursor.loadFromSystem(sf::Cursor::Hand);
    }
    window.setMouseCursor(cursor);
}

void CheckersWidget::_update_possible_moves() {
    _possible_moves.clear();
    if(_selected_field == std::nullopt)
        return;
    else{
        auto moves = _game->board.get_all_possible_moves();
        for(auto move : moves){
            if(move.from.x == _selected_field->x && move.from.y == _selected_field->y)
                _possible_moves.push_back(move);
        }

    }
}


void CheckersWidget::_draw_board(sf::RenderTarget &target, sf::RenderStates states) const {
    for (int i = 0; i < FIELDS_IN_ROW; i++) {
        for (int j = 0; j < FIELDS_IN_COLUMN; j++) {
            target.draw(_field_sprites[i][j]);
        }
    }
}

void CheckersWidget::_draw_pieces(sf::RenderTarget &target, sf::RenderStates states) const {
    for(int i = 0; i<FIELDS_IN_ROW; i++){
        for(int j = 0; j<FIELDS_IN_COLUMN; j++){
            if(_game->board.get_field(i, j) != NOTHING)
                target.draw(_pieces_sprites[i][j]);
        }
    }
}
void CheckersWidget::_play_next_move() {
    _game->play_next_move();
    auto played_move = _game->board.get_last_move();
    auto from = _map_field_to_pos(sf::Vector2u(played_move.from.x, played_move.from.y));
    auto to = _map_field_to_pos(sf::Vector2u(played_move.to.x, played_move.to.y));
    _move_animation = std::make_shared<MoveAnimation>(
                from,
                to,
              sf::milliseconds(1000),
              std::shared_ptr<sf::Transformable>(&_pieces_sprites[played_move.from.x][played_move.from.y]));
    _move_animation->start();


//    _update_possible_moves();
    _update_field_sprites();
    _update_pieces_sprites();
//    _update_cursor(window);
}



void CheckersWidget::handle_event(const sf::Event &event, sf::RenderWindow &window) {
    if(_game->get_state() != IN_PROGRESS)
        return;
    if(event.type == sf::Event::MouseMoved){
        if(_game->board.get_player_on_move() || _is_move_animation_now())
            return;

        auto pos = _map_pos_to_field(
                window.mapPixelToCoords(
                sf::Vector2i(event.mouseMove.x, event.mouseMove.y)));
        _hovered_field = pos;
        _update_field_sprites();
        _update_cursor(window);
    }
    if(event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left) {
        if(_game->board.get_player_on_move() || _is_move_animation_now())
            return;

        auto pos = _map_pos_to_field(
                window.mapPixelToCoords(
                        sf::Vector2i(event.mouseButton.x, event.mouseButton.y)));
        _hovered_field = std::nullopt;
        BoardField field = _game->board.get_field(pos->x, pos->y);
        if(field != NOTHING && !get_board_field_color(field)){
            if(_selected_field == pos)
                _selected_field = std::nullopt;
            else
                _selected_field = pos;
        }
        else
            _selected_field = std::nullopt;

        if(pos.has_value()){
            auto considered_move = std::find_if(_possible_moves.begin(), _possible_moves.end(),
                                                [pos](const Move &move){return move.to.x == pos->x && move.to.y == pos->y;});
            if(considered_move != _possible_moves.end()){
                _user_agent->set_move(*considered_move);

                _game->play_next_move();
                if(!_game->board.get_player_on_move() && _game->get_state() == IN_PROGRESS)
                    _selected_field = sf::Vector2u(considered_move->to.x, considered_move->to.y);
                while(_game->board.get_player_on_move() && _game->get_state() == IN_PROGRESS)
                    _game->play_next_move();
            }
        }
        _update_possible_moves();
        _update_field_sprites();
        _update_pieces_sprites();
        _update_cursor(window);

    }
}

std::optional<sf::Vector2u> CheckersWidget::_map_pos_to_field(sf::Vector2f pos) const{
    sf::Vector2u res = sf::Vector2u(pos.x / _field_size.x, pos.y / _field_size.y) ;
    if(res.x < 0 || res.x >= 8 || res.y < 0 || res.y >= 8)
        return std::nullopt;
    return res;
}
sf::Vector2f CheckersWidget::_map_field_to_pos(sf::Vector2u pos) const {
    return sf::Vector2f(_field_size.x * (pos.x+0.5f), _field_size.y * (pos.y+0.5f));
}



BoardStatus CheckersWidget::get_status() const {
    return _game->get_state();
}

void CheckersWidget::update() {
    if(_move_animation)
        _move_animation->update();
}

bool CheckersWidget::_is_move_animation_now() const {
    return _move_animation && _move_animation->is_working();
}






