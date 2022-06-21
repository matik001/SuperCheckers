#ifndef CHECKERSAI_GAME_H
#define CHECKERSAI_GAME_H


#include "Agent.h"



class Game {
    BoardStatus _state = BoardStatus::IN_PROGRESS;
public:
    Agent *agent1, *agent2;
    Board board;
    Game();
    Game(Agent *agent1, Agent *agent2, bool is_player1_starting);
    BoardStatus play_next_move(); /// zwraca informacje o stanie gry
    void revert_move();
    bool is_finished() const;
    BoardStatus get_state() const;
};


#endif //CHECKERSAI_GAME_H
