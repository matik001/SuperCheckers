
#include <cstring>
#include <iostream>
#include "Board.h"
#include "Helpers.h"


char board_field_to_char(BoardField boardField) {
    switch (boardField) {
        case BoardField::NOTHING:
            return '.';
        case BoardField::PAWN1:
            return 'f';
        case BoardField::PAWN2:
            return 'F';
        case BoardField::QUEEN1:
            return 'q';
        case BoardField::QUEEN2:
            return 'Q';
    }
    return 0; /// zeby nie bylo warningow
}

inline bool get_board_field_color(BoardField boardField) {
    return boardField == BoardField::PAWN1 || boardField == BoardField::QUEEN1;
}

inline bool is_board_field_queen(BoardField boardField) {
    return boardField == BoardField::QUEEN1 || boardField == BoardField::QUEEN2;
}

BoardField create_board_field(bool color, bool is_queen) {
    return (color
        ? (is_queen ? QUEEN1 : PAWN1)
        : (is_queen ? QUEEN2 : PAWN2)
    );
}



Board::Board(bool is_player1_on_move) {
    this->_reset_board(is_player1_on_move);
}

void Board::_reset_board(bool is_player1_on_move) {
    _queens_cnt[0] = _queens_cnt[1] = 0;
    _pawns_cnt[0] = _pawns_cnt[1] = 12;
    _capture_number = 0;
    _is_player1_on_move = is_player1_on_move;
    memset(_board_table, BoardField::NOTHING, sizeof(BoardField)*8*8);

    for(int i = 0; i<8; i++){
        if(i == 3 || i == 4)
            continue;
        for(int j = (i+1)%2; j<8; j+=2)
            _board_table[j][i] = (i>4 ? BoardField::PAWN2 : BoardField::PAWN1);
    }
}

void Board::print() const {
    for(int j = 0; j<8; j++){
        for(int i = 0; i<8; i++){
            std::cout << board_field_to_char(_board_table[i][j]) << " ";
        }
        std::cout << "\n";
    }
    std::cout << "pawns1: " << get_amount_of_pawns(true) << " " << "queens1: " << get_amount_of_queens(true)
            << std::endl << "pawns2: " << get_amount_of_pawns(false) << " " << "queens2: " << get_amount_of_queens(false) << std::endl<< std::endl;
    std::cout << "GRACZ " <<  2 - get_color_on_move()  << " na ruchu" << std::endl;

    std::cout << std::flush;
}

bool Board::_should_be_promoted(Position position, BoardField piece) const {
    if(piece == NOTHING)
        return false;
    return (piece == PAWN1 && position.y == 7)
           || (piece == PAWN2 && position.y == 0);
}


DynamicArray<Move> Board::_get_pawn_moves(Position from, bool color) const {
    DynamicArray<Move> res;

    int direction = (color ? 1 : -1);
    Position to_list[2] = {
        Position(from.x - 1, from.y + direction),
        Position(from.x + 1, from.y + direction)
    };
    for(auto & to : to_list){
        if(to.x >= 0 && to.x < 8 && to.y >= 0 && to.y<8 && _board_table[to.x][to.y] == NOTHING)
            res.push(Move(from, to, color,
                          _should_be_promoted(to, _board_table[from.x][from.y])));
    }

    return res;
}




DynamicArray<Move> Board::_get_pawn_beats(Position from, bool color) const {
    DynamicArray<Move> res;
    int offset_x = -1, offset_y = -1;  /// zeby nie robisz 4 dlugich ifow i nie powtarzac kodu
    for(int i = 0; i<4; i++){
        int offset_x2 = 2*offset_x,
            offset_y2 = 2*offset_y;

        Position to = Position(from.x + offset_x2, from.y + offset_y2);
        Position beaten_pos = Position(from.x + offset_x, from.y + offset_y);

        if(to.x >= 0 && to.y >= 0
                && to.x < 8 && to.y < 8
                && _board_table[to.x][to.y] == BoardField::NOTHING
                && _board_table[beaten_pos.x][beaten_pos.y] != BoardField::NOTHING
                && get_board_field_color(_board_table[beaten_pos.x][beaten_pos.y]) != color){

            bool was_beaten_queen = is_board_field_queen(_board_table[beaten_pos.x][beaten_pos.y]);
            res.push(Move(
                    from,
                    to,
                    color,
                    _should_be_promoted(to, _board_table[from.x][from.y]),
                    beaten_pos,
                    was_beaten_queen,
                    _capture_number+1));
        }

        offset_y *= -1;
        if(i == 1)
            offset_x *= -1;
    }
    return res;
}

DynamicArray<Move> Board::_get_queen_moves(Position from, bool color) const {
    DynamicArray<Move> res;

    int offset_x = -1, offset_y = -1;
    for(int i = 0; i<4; i++){
        Position new_pos(from.x + offset_x, from.y+offset_y);
        while(new_pos.x >= 0 && new_pos.x < 8 && new_pos.y >=0 && new_pos.y<8){
            if(_board_table[new_pos.x][new_pos.y] != NOTHING){
                break;
            }
            res.push(Move(from, new_pos, color,
                          _should_be_promoted(new_pos, _board_table[from.x][from.y])));
            new_pos.x += offset_x;
            new_pos.y += offset_y;
        }

        offset_y *= -1;
        if(i == 1)
            offset_x *= -1;
    }
    return res;
}

DynamicArray<Move> Board::_get_queen_beats(Position from, bool color) const {
    DynamicArray<Move> res;

    int offset_x = -1, offset_y = -1;
    for(int i = 0; i<4; i++){
        Position new_pos(from.x + offset_x, from.y+offset_y);
        bool was_beaten_piece = false; /// czy juz cokolwiek bylo zbite
        bool was_beaten_queen = false; /// czy zbita figura to krolowa
        Position beaten_pos;
        while(new_pos.x >= 0 && new_pos.x < 8 && new_pos.y >=0 && new_pos.y<8){
            if (_board_table[new_pos.x][new_pos.y] != NOTHING) {
                if(was_beaten_piece) /// nie mozemy zbic dwoch figur naraz
                    break;
                if (get_board_field_color(_board_table[new_pos.x][new_pos.y]) == color) /// nie mozemy zbic swojej figury
                    break;
                was_beaten_piece = true;
                beaten_pos = new_pos;
                was_beaten_queen = is_board_field_queen(_board_table[new_pos.x][new_pos.y]);
            }
            else{
                if(was_beaten_piece) {
                    res.push(Move(from,
                                  new_pos,
                                  color,
                                  _should_be_promoted(new_pos, _board_table[from.x][from.y]),
                                  beaten_pos,
                                  was_beaten_queen,
                                  _capture_number+1));
                }
            }
            new_pos.x += offset_x;
            new_pos.y += offset_y;
        }

        offset_y *= -1;
        if(i == 1)
            offset_x *= -1;
    }
    return res;
}

DynamicArray<Move> Board::_get_moves(Position from) const {
    bool color = get_color_on_move();
    if(_board_table[from.x][from.y] != NOTHING
            && get_board_field_color(_board_table[from.x][from.y]) == color){
        if(is_board_field_queen(_board_table[from.x][from.y]))
            return _get_queen_moves(from, color);
        return _get_pawn_moves(from, color);
    }
    return DynamicArray<Move>();
}

DynamicArray<Move> Board::_get_beats(Position from) const {
    bool color = get_color_on_move();
    if(_board_table[from.x][from.y] != NOTHING
       && get_board_field_color(_board_table[from.x][from.y]) == color){
        if(is_board_field_queen(_board_table[from.x][from.y]))
            return _get_queen_beats(from, color);
        return _get_pawn_beats(from, color);
    }
    return DynamicArray<Move>();
}

DynamicArray<Move> Board::get_all_possible_moves() const {
    if(this->_capture_number > 0){  /// jezeli jest to drugie lub kolejne bicie w tej turze
        return _get_beats(this->_last_capture_piece_pos);
    }
    DynamicArray<Move> beat_moves;
    DynamicArray<Move> normal_moves;

    for(int i = 0; i<8; i++){
        for(int j = 0; j<8; j++){
            Position pos(i, j);

            beat_moves.push_many(_get_beats(pos));
            normal_moves.push_many(_get_moves(pos));
        }
    }

    if(beat_moves.size() > 0) /// bicie jest przymusowe
        return beat_moves;
    return normal_moves;
}

bool Board::get_color_on_move() const {
    return _is_player1_on_move;
}


int Board::get_amount_of_pawns(bool player) const {
    return _pawns_cnt[(player ? 0 : 1)];
}

int Board::get_amount_of_queens(bool player) const {
    return _queens_cnt[(player ? 0 : 1)];
}

int Board::get_amount_of_pieces(bool player) const {
    return get_amount_of_pawns(player) + get_amount_of_queens(player);
}
void Board::_change_pieces_cnt(BoardField piece, int change) {
    bool color = get_board_field_color(piece);
    bool is_queen = is_board_field_queen(piece);
    if(is_queen)
        _queens_cnt[(color ? 0 : 1)] += change;
    else
        _pawns_cnt[(color ? 0 : 1)] += change;
}

void Board::revert_move() {
    Move move = _moves_history.pop();

    _is_player1_on_move = move.player1;
    if(move.pawn_promoted){
        _change_pieces_cnt(_board_table[move.to.x][move.to.y], -1);
        _board_table[move.to.x][move.to.y] = (move.player1 ? PAWN1 : PAWN2);
        _change_pieces_cnt(_board_table[move.to.x][move.to.y], 1);
    }

    if(!move.is_beating){
        _capture_number = 0;
    }
    else{
        _capture_number = move.capture_number-1;
        _last_capture_piece_pos = move.from;

        BoardField beaten_piece = create_board_field(!move.player1, move.was_beaten_queen);
        _board_table[move.pos_beaten.x][move.pos_beaten.y] = beaten_piece;
        _change_pieces_cnt(beaten_piece, 1);

    }


    swap(_board_table[move.from.x][move.from.y], _board_table[move.to.x][move.to.y]);
}


void Board::play_move(Move move) {
    swap(_board_table[move.to.x][move.to.y], _board_table[move.from.x][move.from.y]);

    bool has_next_beat = false;
    if(!move.is_beating){
        _is_player1_on_move = !_is_player1_on_move;
        _capture_number = 0;
    }
    else{
        _change_pieces_cnt(_board_table[move.pos_beaten.x][move.pos_beaten.y], -1);
        _board_table[move.pos_beaten.x][move.pos_beaten.y] = NOTHING;

        has_next_beat = _get_beats(move.to).size() > 0;
        if(has_next_beat){
            _last_capture_piece_pos = move.to;
            _capture_number++;
        }
        else{
            _is_player1_on_move = !_is_player1_on_move;
            _capture_number = 0;
        }
    }

    if(move.pawn_promoted && has_next_beat){ /// jezeli staje sie damka w wyniku bicia i ma kolejne bicie to nie jest damka
        move.pawn_promoted = false;
    }
    if(move.pawn_promoted){
        _change_pieces_cnt(_board_table[move.to.x][move.to.y], -1);
        _board_table[move.to.x][move.to.y] = (move.player1 ? QUEEN1 : QUEEN2);
        _change_pieces_cnt(_board_table[move.to.x][move.to.y], 1);
    }
    _moves_history.push(move);
}

BoardState Board::get_state(const DynamicArray<Move> &all_possible_moves) const {
    if (get_amount_of_pieces(true) == 0)
        return WIN_2;
    if (get_amount_of_pieces(false) == 0)
        return WIN_1;
    if (all_possible_moves.size() == 0)
        return (get_color_on_move() ? WIN_2 : WIN_1);
    return IN_PROGRESS;
}


