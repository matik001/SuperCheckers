#ifndef CHECKERSAI_MOVEANIMATION_H
#define CHECKERSAI_MOVEANIMATION_H
#include <TGUI/Backend/SFML-Graphics.hpp>


class MoveAnimation {
    sf::Vector2f _from;
    sf::Vector2f _to;
    sf::Time _time;
    std::shared_ptr<sf::Transformable> _object;
    sf::Clock _clock;
    bool _is_working = false;
    void _update_is_working();
    [[nodiscard]] sf::Vector2f _calc_pos() const;
public:
    MoveAnimation(const sf::Vector2f &from, const sf::Vector2f &to, const sf::Time &time,
                  std::shared_ptr<sf::Transformable> object);
/// TODO dodac callback

    void start();
    void update();
    [[nodiscard]] bool is_working() const;
};


#endif //CHECKERSAI_MOVEANIMATION_H
