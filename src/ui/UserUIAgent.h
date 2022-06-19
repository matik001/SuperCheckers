#ifndef CHECKERSAI_USERUIAGENT_H
#define CHECKERSAI_USERUIAGENT_H

#include <atomic>
#include "../engine/Agent.h"

class UserUIAgent : public Agent{
    Move _picked_move;
public:
    void set_move(Move move);
    Move get_move() override;
    void init(Board *board, bool color) override;
};


#endif //CHECKERSAI_USERUIAGENT_H
