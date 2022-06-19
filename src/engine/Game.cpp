#include "Game.h"

Game::Game(Agent *agent1, Agent *agent2, bool is_player1_starting) : board(is_player1_starting){
    this->agent1 = agent1;
    this->agent2 = agent2;
    agent1->init(&board, true);
    agent2->init(&board, false);
}

BoardState Game::play_next_move() {
    Agent *agent = (board.get_color_on_move() ? agent1 : agent2);
    Move move = agent->get_move();
    board.play_move(move);
    return board.get_state(board.get_all_possible_moves());
}

bool Game::is_finished() const {
    return board.get_state(board.get_all_possible_moves()) != IN_PROGRESS;
}

Game::Game() {

}
