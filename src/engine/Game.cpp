#include "Game.h"
#include <thread>
Game::Game(Agent *agent1, Agent *agent2, bool is_player1_starting) : board(is_player1_starting){
    this->agent1 = agent1;
    this->agent2 = agent2;
    agent1->init(&board, true);
    agent2->init(&board, false);
}
Game::Game(Agent *agent1, Agent *agent2, const Board &board) {
    this->agent1 = agent1;
    this->agent2 = agent2;
    this->board = board;
    agent1->init(&this->board, true);
    agent2->init(&this->board, false);
}


BoardStatus Game::play_next_move() {
    Agent *agent = (board.get_player_on_move() ? agent1 : agent2);
    Move move = agent->get_move();
    return play_move(move);
}

bool Game::is_finished() const {
    return _state != IN_PROGRESS;
}

Game::Game() {

}

BoardStatus Game::get_state() const {
    return _state;
}

void Game::revert_move() {
    board.revert_move();
}

BoardStatus Game::play_move(const Move& move) {
    board.play_move(move);
    _state = board.get_state(board.get_all_possible_moves());
    return _state;
}

/// nie operuje na oryginalnym boardzie, aby nie bylo kolizji gdy jest wiecej watkow
void Game::find_next_move_async(const std::function<void(Move)>& callback) {
    Agent *agent = (board.get_player_on_move() ? agent1 : agent2);
    auto agent_clone = agent->clone();
    auto board_clone = std::make_shared<Board>(board); /// to jest problemem
    agent_clone->change_board(board_clone.get());

    auto f = [callback](std::shared_ptr<Agent> agent_clone, std::shared_ptr<Board> Board){
        auto move = agent_clone->get_move();
        callback(move);
    };

    std::thread t(f, std::move(agent_clone), std::move(board_clone));
    t.detach();
}

