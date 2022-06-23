#include "Dispatcher.h"

void Dispatcher::execute(std::function<void()> func) {
    std::scoped_lock lock(_mutex);
    _queue.push(func);
}

void Dispatcher::update() {
    std::scoped_lock lock(_mutex);
    while(!_queue.empty()){
        _queue.front()();
        _queue.pop();
    }
}
