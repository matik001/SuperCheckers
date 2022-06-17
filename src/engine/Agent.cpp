
#include "Agent.h"
#include "Helpers.h"

void Agent::init(Board *board, bool color) {
    this->board = board;
    this->color = color;
}

void MinMaxAgent::init(Board *board, bool color) {
    Agent::init(board, color);
}


MinMaxRes::MinMaxRes(int eval, int best_move_id) {
    this->eval = eval;
    this->best_move_id = best_move_id;
}

MinMaxAgent::MinMaxAgent(int max_depth) {
    _max_depth = max_depth;
}

Move MinMaxAgent::get_move() {
    auto res= _minmax(0);
    return board->get_all_possible_moves()[res.best_move_id];
}

MinMaxRes MinMaxAgent::_minmax(int depth, int alpha, int beta) {
    auto moves = board->get_all_possible_moves();
    auto state0 = board->get_state(moves);

    if (depth == _max_depth || state0 != IN_PROGRESS) {
        return MinMaxRes(_evaluate_board(moves), -1);
    }

    bool player1 = board->get_color_on_move();

    MinMaxRes best(-1, -1);
    for (int i = 0; i<moves.size() && alpha < beta; i++) {
        const Move &move = moves[i];

        board->play_move(move);
        MinMaxRes resi = _minmax(depth+1, alpha, beta);
        if(best.best_move_id == -1){ /// jezeli best niebylo ustawione to ustawiamy
            best.best_move_id = i;
            best.eval = resi.eval;
        }
        if (player1) {  /// player1 chce zmaksymalizowac eval
            if(resi.eval > best.eval){
                best.eval = resi.eval;
                best.best_move_id = i;
            }
            alpha = max(alpha, resi.eval);
        }
        else{
            if(resi.eval < best.eval){
                best.eval = resi.eval;
                best.best_move_id = i;
            }
            beta = min(beta, resi.eval);
        }
        board->revert_move();
    }
    return best;
}

int MinMaxAgent::_evaluate_board(const DynamicArray<Move> &possible_moves) {
    auto state = board->get_state(possible_moves);
    if (state == WIN_1)
        return INF;
    if (state == WIN_2)
        return -INF;
    return board->get_amount_of_queens(true) * 3 + board->get_amount_of_pawns(true)
           - (board->get_amount_of_queens(false) * 3 + board->get_amount_of_pawns(false));
}

void UserAgent::init(Board *board, bool color) {
    Agent::init(board, color);
}

Move UserAgent::get_move() {
    auto moves = board->get_all_possible_moves();
    Move move = _pick_move(moves);
    return move;
}

void UserAgent::_print_moves(DynamicArray<Move> &moves) {
    std::cout << "(GRACZ " << 2 - (int) color << ") Mozliwe ruchy:" << std::endl;
    for (int i = 0; i < moves.size(); i++) {
        std::cout << i + 1 << ") " << moves[i] << std::endl;
    }
}

Move UserAgent::_pick_move(DynamicArray<Move> &moves) {
    _print_moves(moves);
    std::cout << "Podaj numer ruchu\n>";
    while (true) {
        int move_id;
        std::cin >> move_id;
        move_id--;
        if (std::cin.fail() || move_id < 0 || move_id >= moves.size()) {
            std::cin.clear();
            std::cin.ignore(256, '\n');
            std::cout << "Bledny numer ruchu" << std::endl;
            std::cout << "Podaj poprawny numer ruchu\n>";
            continue;
        }
        return moves[move_id];
    }
}


