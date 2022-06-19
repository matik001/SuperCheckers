#include "ResultInfo.h"
#include "ResourcesManager.h"
void ResultInfo::draw(sf::RenderTarget &target, sf::RenderStates states) const {
    target.clear(sf::Color(0,0,0,100));
    target.draw(_result_text);

}
// TODO FADE IN AND THEME AND THEN TEXT
void ResultInfo::init(BoardState result, const sf::RenderWindow &window) {
    if(_inited)
        return;
    _inited = true;

    std::wstring info = (
        result == WIN_1
            ? L"Niestety porażka ;\\"
            : L"Gratulacje zwycięzco! ;)"
        );
    _result_text.setFont(*std::static_pointer_cast<sf::Font>(ResourcesManager::singleton().get(Resources::COURGETTE_FONT)));
    _result_text.setString(info);
    _result_text.setCharacterSize(64);
    _result_text.setFillColor(sf::Color::White);
    auto rect = _result_text.getLocalBounds();
    _result_text.setOrigin(rect.left+ rect.width/2.0, rect.top+rect.height/2.0);

    _result_text.setPosition(window.getView().getCenter());

}
