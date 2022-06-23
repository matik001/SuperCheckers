#ifndef CHECKERSAI_DISPATCHER_H
#define CHECKERSAI_DISPATCHER_H
#include <queue>
#include <functional>
#include <mutex>

class Dispatcher {
    std::queue< std::function<void()> > _queue;
    std::mutex _mutex;
public:
    void execute(std::function<void()> func);
    void update();
};


#endif //CHECKERSAI_DISPATCHER_H
