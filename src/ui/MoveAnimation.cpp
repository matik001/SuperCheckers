#include "MoveAnimation.h"

#include <utility>

MoveAnimation::MoveAnimation(const sf::Vector2f &from, const sf::Vector2f &to, const sf::Time &time,
                             std::shared_ptr<sf::Transformable> object) : _from(from), _to(to), _time(time),
                                                                                 _object(std::move(object)) {}

sf::Vector2f MoveAnimation::_calc_pos() const {
    sf::Vector2f offset = _from - _to;
    offset *= (float)(_clock.getElapsedTime().asMicroseconds()/_time.asMilliseconds());
    return _from + offset;
}

void MoveAnimation::_update_is_working() {
    if(_clock.getElapsedTime().asMilliseconds() > _time.asMilliseconds()){
        _is_working = false;
        _object->setPosition(_to);
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

void MoveAnimation::start() {
    _clock.restart();
    _is_working = true;
}
