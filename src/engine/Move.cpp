#include <ostream>
#include "Move.h"


Position::Position() {
    this->x = this->y = 0;
}

Position::Position(int x, int y) {
    this->x = x;
    this->y = y;
}

std::ostream& operator<<(std::ostream& os, Position const& pos)
{
    os << (char)('A'+pos.x) << 8-pos.y;
    return os;
}

Move::Move(Position from, Position to, bool player1, bool pawn_promoted) {
    this->from = from;
    this->to = to;
    this->player1 = player1;
    this->pawn_promoted = pawn_promoted;
    this->is_beating = false;
    this->capture_number = 0;
}

Move::Move(Position from, Position to, bool player1, bool pawn_promoted, Position pos_beated, bool was_beated_queen,
           int capture_number)
        : Move(from, to, player1, pawn_promoted) {
    this->is_beating = true;
    this->pos_beaten = pos_beated;
    this->was_beaten_queen = was_beated_queen;
    this->capture_number = capture_number;
}

Move::Move() {}


std::ostream &operator<<(std::ostream &os, const Move &move) {
    os << move.from << " --> " << move.to;
    if(move.is_beating)
        os << " (BICIE)";
    if(move.pawn_promoted)
        os << " (PROMOCJA W DAME)";
    return os;
}