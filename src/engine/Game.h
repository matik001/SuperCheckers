#ifndef CHECKERSAI_GAME_H
#define CHECKERSAI_GAME_H


#include "Agent.h"
#include <functional>


class Game {
    BoardStatus _state = BoardStatus::IN_PROGRESS;
public:
    Agent *agent1, *agent2;
    Board board;
    Game();
    Game(Agent *agent1, Agent *agent2, bool is_player1_starting);
    BoardStatus play_next_move(); /// zwraca informacje o stanie gry
    BoardStatus play_move(const Move& move);
    void find_next_move_async(const std::function<void(Move)>& callback);

    void revert_move();
    bool is_finished() const;
    BoardStatus get_state() const;
};


#endif //CHECKERSAI_GAME_H
