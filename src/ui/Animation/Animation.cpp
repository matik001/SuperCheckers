#include "Animation.h"

void Animation::_update_is_working() {
    if(_is_working && _clock.getElapsedTime().asMilliseconds() > _time.asMilliseconds()){
        _is_working = false;
        _step_func(1);
        _callback();
    }
}

Animation::Animation(const sf::Time &time, std::function<void(double)> step_func)
            : _time(time), _step_func(std::move(step_func)){}

void Animation::start(std::function<void()> callback) {
    _clock.restart();
    _is_working = true;
    _step_func(0);
    _callback = std::move(callback);
}

void Animation::update() {
    _update_is_working();
    if(is_working()){
        float rate = _clock.getElapsedTime().asMilliseconds()/(float)_time.asMilliseconds();
        _step_func(rate);
    }
}

bool Animation::is_working() const {
    return _is_working;
}
