
#ifndef CHECKERSAI_AGENT_H
#define CHECKERSAI_AGENT_H


#include "Board.h"
#include <memory>

class Agent {
protected:
    bool color; /// true oznacza ze jestesmy player1
    Board *board;
public:
    virtual void change_board(Board *board);
    virtual void init(Board *board, bool color);
    virtual Move get_move() = 0; /// wybiera ruch ktory chce zagrac
    virtual std::shared_ptr<Agent> clone() = 0;
};
struct MinMaxRes{
    int eval;
    int best_move_id;
    MinMaxRes();
    MinMaxRes(int eval, int best_move_id);
    MinMaxRes(const MinMaxRes &obj);
    MinMaxRes& operator=(const MinMaxRes &obj);
};

const int INF = 1e9;
class MinMaxAgent : public Agent{
    int _max_depth;
    MinMaxRes _minmax(int depth, int alpha = -INF, int beta = INF);

    int _evaluate_board(const DynamicArray<Move> &possible_moves);
public:
    MinMaxAgent(int max_depth);
    Move get_move() override;
    void init(Board *board, bool color) override;

    std::shared_ptr<Agent> clone() override;
};

class UserConsoleAgent : public Agent{
    void _print_moves(DynamicArray<Move> &moves);
    Move _pick_move(DynamicArray<Move> &moves);
public:
    Move get_move() override;
    void init(Board *board, bool color) override;

    std::shared_ptr<Agent> clone() override;
};


#endif //CHECKERSAI_AGENT_H
