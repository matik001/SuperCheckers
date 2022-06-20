#include "SfmlUtils.h"
#include <algorithm>

void scale_to_size(sf::Sprite &sprite, float width, float height){
    auto rect = sprite.getTextureRect();
    float scale_x = width/ rect.width;
    float scale_y = height/ rect.height;
    float mini = std::min(scale_x, scale_y);
    sprite.setScale(mini, mini);
}

std::shared_ptr<sf::Texture> get_screenshot(sf::RenderTarget &renderer,
                                            std::function<void(sf::RenderTarget &, sf::RenderStates)> draw) {
    sf::RenderTexture render_texture;
    render_texture.create(renderer.getView().getSize().x, renderer.getView().getSize().y);
    draw(renderer, sf::RenderStates::Default);
    render_texture.display();
    std::shared_ptr<sf::Texture> res = std::make_shared<sf::Texture>(render_texture.getTexture());

    return res;
}
