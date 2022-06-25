#include "CheckersWidget.h"

#include <utility>
#include "../resources/ResourcesManager.h"
#include "UIConfig.h"
#include "../utils/SfmlUtils.h"
CheckersWidget::CheckersWidget(int computer_level
                               , bool are_we_white, std::shared_ptr<sf::RenderWindow> window, std::shared_ptr<Board> board)
        : _are_we_white(are_we_white), _window(std::move(window)) {
    this->_board_size = UIConfig::board_size;
    this->_board_number_margin = UIConfig::board_number_margin;
    _field_size = sf::Vector2f(_board_size.x / (float)FIELDS_IN_ROW,
                               _board_size.y / (float)FIELDS_IN_COLUMN);

    _user_agent = std::make_shared<UserUIAgent>();
    _computer_agent = std::make_shared<MinMaxAgent>(computer_level);

    if(board == nullptr)
        _game = std::make_shared<Game>(_computer_agent.get(), _user_agent.get(), !are_we_white);
    else
        _game = std::make_shared<Game>(_computer_agent.get(), _user_agent.get(), *board);
    _update_field_sprites();
    _update_pieces_sprites();
    _init_field_captions();
    if(!are_we_white)
        _play_enemy_moves();
}


void CheckersWidget::draw(sf::RenderTarget &target, sf::RenderStates states) const {
    _draw_board(target, states);
    _draw_field_captions(target, states);
    _draw_pieces(target, states);
}

Resource CheckersWidget::_board_field_to_texture_id(BoardField field) const{
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
    }
}

void CheckersWidget::_update_pieces_sprites() {
    _pieces.erase(std::remove_if(_pieces.begin(), _pieces.end(),
                                 [this](const std::shared_ptr<Piece> &piece){
        auto field = _game->board.get_field(piece->pos.x, piece->pos.y);
        return field == NOTHING;
    }), _pieces.end());

    for(int i = 0; i<FIELDS_IN_COLUMN; i++){
        for(int j = 0; j<FIELDS_IN_ROW; j++){
            auto field = _game->board.get_field(i, j);
            if(field == NOTHING)
                continue;
            auto piece = _find_piece_or_create(sf::Vector2u(i, j));
            sf::Vector2f pos = _map_field_to_pos(piece->pos);

            Resource resource_id = _board_field_to_texture_id(field);
            auto texture = ResourcesManager::singleton().get<sf::Texture>(resource_id);

            piece->sprite.setTexture(*texture);
            scale_to_size(piece->sprite, _field_size.x-10, _field_size.y-10);
            piece->sprite.setOrigin(piece->sprite.getTextureRect().width/2.0,
                                    piece->sprite.getTextureRect().height/2.0);
            piece->sprite.setPosition(pos);
        }
    }
}


void CheckersWidget::_update_field_sprites() {
    for(unsigned int i = 0; i<FIELDS_IN_ROW; i++){
        for(unsigned int j = 0; j<FIELDS_IN_COLUMN; j++){
            sf::Vector2f pos = _map_field_to_pos({i,j});
            _field_sprites[i][j].setSize(_field_size);
            _field_sprites[i][j].setOrigin(_field_size/2.0f);
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
        for (auto move: _all_beats) {
            _field_sprites[move.from.x][move.from.y].setFillColor(UIConfig::must_beat_color);
        }
        if(_selected_field != std::nullopt){
            _field_sprites[_selected_field->x][_selected_field->y].setFillColor(UIConfig::selected_piece_color);
        }
        for (auto move: _possible_moves) {
            _field_sprites[move.to.x][move.to.y].setFillColor(UIConfig::possible_move_color);
        }
    }
}

void CheckersWidget::_update_cursor() {
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
    _window->setMouseCursor(cursor);
}


void CheckersWidget::_update_beats() {
    if(!_game->board.get_player_on_move()){
        _all_beats.clear();
        auto moves = _game->board.get_all_possible_moves();
        if(moves.size() > 0 && moves[0].is_beating){
            for(auto move : moves)
                _all_beats.push_back(move);
        }
    }

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

void CheckersWidget::_draw_field_captions(sf::RenderTarget &target, sf::RenderStates states) const {
    for (int i = 0; i < FIELDS_IN_ROW; i++) {
        target.draw(_captions_left_bg[i]);
        target.draw(_field_captions_left[i]);
    }
    for (int i = 0; i < FIELDS_IN_COLUMN; i++) {
        target.draw(_captions_bottom_bg[i]);
        target.draw(_field_captions_bottom[i]);
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
    for (auto &piece: _pieces) {
        target.draw(piece->sprite);
    }
}
void CheckersWidget::_play_next_move(const std::function<void()>& callback) {

    _game->find_next_move_async([this, callback](const Move& move){
        _dispatcher.execute([this, move, callback](){
            _game->play_move(move);
            auto from = _map_field_to_pos(sf::Vector2u(move.from.x, move.from.y));
            auto to = _map_field_to_pos(sf::Vector2u(move.to.x, move.to.y));
            auto piece = _find_piece(sf::Vector2u(move.from.x, move.from.y));
            piece->pos = sf::Vector2u(move.to.x, move.to.y);

            auto animation = std::make_shared<MoveAnimation>(
                    UIConfig::move_animation_time,
                    from,
                    to,
                    &piece->sprite);
            _move_animation = animation; /// musi byc w ten sposob, bo inaczej wykona sie destruktor, przy kolejnej animacji, w callbacku obecnej

            _selected_field = std::nullopt;
            _update_possible_moves();
            animation->start([this, callback, animation]{ /// trzeba wrzucic animation, z powyzszego powodu
                _update_beats();
                _update_field_sprites();
                _update_pieces_sprites();
                _update_cursor();
                    callback();
            });
        });
    });
}

void CheckersWidget::_play_user_move(const Move& move) {
    _user_agent->set_move(move);
    _play_next_move([this, move]{
        if(!_game->board.get_player_on_move() && _game->get_state() == IN_PROGRESS){
            _selected_field = sf::Vector2u(move.to.x, move.to.y);
            _update_possible_moves();
            _update_beats();
            _update_field_sprites();
            _update_pieces_sprites();
            _update_cursor();
        }
        else
            _play_enemy_moves();
    });
}

void CheckersWidget::_play_enemy_moves() {
    if(_game->board.get_player_on_move() && _game->get_state() == IN_PROGRESS)
        _play_next_move([this]{
            _play_enemy_moves();
        });
}


void CheckersWidget::handle_event(const sf::Event &event) {
    if(_game->get_state() != IN_PROGRESS)
        return;
    if(event.type == sf::Event::MouseMoved){
        if(_game->board.get_player_on_move() || _is_move_animation_now())
            return;

        auto pos = _map_pos_to_field(
                _window->mapPixelToCoords(
                sf::Vector2i(event.mouseMove.x, event.mouseMove.y)));
        _hovered_field = pos;
        _update_field_sprites();
        _update_cursor();
    }
    if(event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left) {
        if(_game->board.get_player_on_move() || _is_move_animation_now())
            return;

        auto pos = _map_pos_to_field(
                _window->mapPixelToCoords(
                        sf::Vector2i(event.mouseButton.x, event.mouseButton.y)));
        if (pos == std::nullopt)
            return;

        _hovered_field = std::nullopt;
        BoardField field = _game->board.get_field(pos->x, pos->y);
        if (field != NOTHING && !get_board_field_color(field)) { /// kliknieto na nasza figure
            if (_selected_field == pos) /// odznaczamy gdy kliknieto na obecnie zaznaczona
                _selected_field = std::nullopt;
            else
                _selected_field = pos;
        } else
            _selected_field = std::nullopt;


        auto considered_move = std::find_if(_possible_moves.begin(), _possible_moves.end(),
                                            [pos](const Move &move) {
                                                return move.to.x == pos->x && move.to.y == pos->y;
                                            });
        if (considered_move != _possible_moves.end()) {
            _play_user_move(*considered_move);
            return;
        }

        _update_possible_moves();
        _update_field_sprites();
        _update_pieces_sprites();
        _update_cursor();
    }
}

std::optional<sf::Vector2u> CheckersWidget::_map_pos_to_field(sf::Vector2f pos) const{
    sf::Vector2u res = sf::Vector2u((pos.x - _board_number_margin.x) / _field_size.x, pos.y / _field_size.y) ;
    if(res.x < 0 || res.x >= 8 || res.y < 0 || res.y >= 8)
        return std::nullopt;
    return res;
}
sf::Vector2f CheckersWidget::_map_field_to_pos(sf::Vector2u pos) const {
    return {_board_number_margin.x + _field_size.x * (pos.x+0.5f),
            _field_size.y * (pos.y+0.5f)};
}

sf::Vector2f CheckersWidget::_get_caption_left_pos(int i) const {
    return {_board_number_margin.x/2,
            _field_size.y * (i+0.5f)};
}
sf::Vector2f CheckersWidget::_get_caption_bottom_pos(int i) const {
    return {_board_number_margin.x + _field_size.x * (i+0.5f),
            _board_size.y + _board_number_margin.y/2 };
}

BoardStatus CheckersWidget::get_status() const {
    return _game->get_state();
}

void CheckersWidget::update() {
    _dispatcher.update();
    if(_move_animation)
        _move_animation->update();
}

bool CheckersWidget::_is_move_animation_now() const {
    return _move_animation && _move_animation->is_working();
}

std::shared_ptr<Piece> CheckersWidget::_find_piece(sf::Vector2u pos) const {
    auto res = std::find_if(_pieces.begin(), _pieces.end(),[pos](const std::shared_ptr<Piece> &p){
        return p->pos == pos;
    });
    if(res == _pieces.end()){
        return nullptr;
    }
    return *res;
}

std::shared_ptr<Piece> CheckersWidget::_find_piece_or_create(sf::Vector2u pos)  {
    auto res = _find_piece(pos);
    if(res != nullptr)
        return res;
    _pieces.push_back(std::make_shared<Piece>(pos));
    return _pieces.back();
}

bool CheckersWidget::is_finished() const {
    return _game->is_finished() && !_is_move_animation_now() && !_is_thinking();
}

bool CheckersWidget::_is_thinking() const {
    _thinking_thread != nullptr && _thinking_thread->joinable();
}

void CheckersWidget::_init_field_captions() {
    for(int i = 0; i<8; i++){
        _field_captions_left[i].setString(std::to_string(8-i));
        _field_captions_bottom[i].setString(std::string(1, (char)('A' + i)));
        _field_captions_left[i].setCharacterSize(26);
        _field_captions_bottom[i].setCharacterSize(26);
        _field_captions_left[i].setFillColor(UIConfig::board_field_caption_color);
        _field_captions_bottom[i].setFillColor(UIConfig::board_field_caption_color);

        auto font = ResourcesManager::singleton().get<sf::Font>(Resource::UBUNTU_BOLD_FONT).get();
        _field_captions_left[i].setFont(*font);
        _field_captions_bottom[i].setFont(*font);

        center_text_origin(_field_captions_left[i]);
        center_text_origin(_field_captions_bottom[i]);

        _field_captions_left[i].setPosition(_get_caption_left_pos(i) + sf::Vector2f(0, -5));
        _field_captions_bottom[i].setPosition(_get_caption_bottom_pos(i) + sf::Vector2f(0, -5));

        _captions_left_bg[i].setSize(sf::Vector2f(_board_number_margin.x, _field_size.y));
        _captions_bottom_bg[i].setSize(sf::Vector2f(_field_size.x, _board_number_margin.y));
        center_shape_origin(_captions_left_bg[i]);
        center_shape_origin(_captions_bottom_bg[i]);
        _captions_left_bg[i].setOutlineThickness(1);
        _captions_bottom_bg[i].setOutlineThickness(1);
        _captions_left_bg[i].setOutlineColor(sf::Color::Black);
        _captions_bottom_bg[i].setOutlineColor(sf::Color::Black);
        _captions_left_bg[i].setFillColor((i%2 == 0 ? UIConfig::margin_color1 : UIConfig::margin_color2));
        _captions_bottom_bg[i].setFillColor((i%2 == 1 ? UIConfig::margin_color1 : UIConfig::margin_color2));
        _captions_left_bg[i].setPosition(_get_caption_left_pos(i));
        _captions_bottom_bg[i].setPosition(_get_caption_bottom_pos(i));

    }
}

bool CheckersWidget::can_revert_move() const {
    return !_is_move_animation_now() && !_is_thinking()
        && _game->get_state() == IN_PROGRESS && !_game->board.get_player_on_move()
        && _game->board.get_moves_amount() > 0;
}

void CheckersWidget::revert_move() { /// chcemy cofnac ruch przeciwnika i nasz
    if(_game->board.get_player_on_move())
        return;
    /// chcemy po serii cofniec byc na ruchu
    while(_game->board.get_moves_amount() > 0){
        _game->revert_move();
        if(!_game->board.get_player_on_move())
            break;
    }
    _selected_field = std::nullopt;
    _update_beats();
    _update_cursor();
    _update_possible_moves();
    _update_field_sprites();
    _update_pieces_sprites();

    /// jezeli ruch przeciwnika to niech gra
    if(_game->board.get_player_on_move())
        _play_enemy_moves();
}

void CheckersWidget::save(const std::string &filename) {
    _game->board.save(filename);
}











