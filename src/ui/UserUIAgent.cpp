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

std::shared_ptr<Agent> UserUIAgent::clone() {
    auto res = std::make_shared<UserUIAgent>();
    res->color = this->color;
    res->board = this->board;
    res->_picked_move = this->_picked_move;
    return std::move(res);
}
