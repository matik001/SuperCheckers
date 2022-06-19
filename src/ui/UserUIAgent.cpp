#include "UserUIAgent.h"


Move UserUIAgent::get_move() {
    return _picked_move;
}

void UserUIAgent::init(Board *board, bool color) {
    Agent::init(board, color);
}

void UserUIAgent::set_move(Move move) {
    _picked_move = move;
}