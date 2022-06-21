#ifndef CHECKERSAI_MOVEANIMATION_H
#define CHECKERSAI_MOVEANIMATION_H
#include <TGUI/Backend/SFML-Graphics.hpp>
#include <future>
#include <thread>

class MoveAnimation {
    sf::Vector2f _from;
    sf::Vector2f _to;
    sf::Time _time;
    sf::Transformable * _object;
    sf::Clock _clock;
    std::function<void()> _callback;
    bool _is_working = false;
    void _update_is_working();
    [[nodiscard]] sf::Vector2f _calc_pos() const;
public:
    MoveAnimation(const sf::Vector2f &from, const sf::Vector2f &to, const sf::Time &time,
                  sf::Transformable * object);

    void start(std::function<void()> callback);
    void update();
    [[nodiscard]] bool is_working() const;
};


#endif //CHECKERSAI_MOVEANIMATION_H
