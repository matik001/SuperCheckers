
#ifndef CHECKERSAI_ANIMATION_H
#define CHECKERSAI_ANIMATION_H


#include <TGUI/Backend/SFML-Graphics.hpp>
#include <future>
#include <thread>

class Animation {
    sf::Time _time;
    sf::Clock _clock;
    std::function<void()> _callback;
    std::function<void(double rate)> _step_func; /// rate to czas jaki minal przez caly czas
    bool _is_working = false;
    void _update_is_working();
public:
    Animation(const sf::Time &time, std::function<void(double rate)> step_func);

    void start(std::function<void()> callback);
    void update();
    [[nodiscard]] bool is_working() const;
};



#endif //CHECKERSAI_ANIMATION_H
