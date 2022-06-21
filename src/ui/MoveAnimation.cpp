#include "MoveAnimation.h"

#include <utility>

MoveAnimation::MoveAnimation(const sf::Vector2f &from, const sf::Vector2f &to, const sf::Time &time,
                             sf::Transformable * object) : _from(from), _to(to), _time(time), _object(object) {
}

sf::Vector2f MoveAnimation::_calc_pos() const {
    sf::Vector2f offset = _to - _from;
    float w = _clock.getElapsedTime().asMilliseconds()/(float)_time.asMilliseconds();
    offset *= w;

    return _from + offset;
}

void MoveAnimation::_update_is_working() {
    if(_clock.getElapsedTime().asMilliseconds() > _time.asMilliseconds()){
        _is_working = false;
        _object->setPosition(_to);
        _callback();
    }
}

bool MoveAnimation::is_working() const {
    return _is_working;
}

void MoveAnimation::update() {
    _update_is_working();
    if(is_working()){
        auto new_pos = _calc_pos();
        _object->setPosition(new_pos);
    }
}

void MoveAnimation::start(std::function<void()> callback) {
    _clock.restart();
    _is_working = true;
    _object->setPosition(_from);
    _callback = std::move(callback);
}
