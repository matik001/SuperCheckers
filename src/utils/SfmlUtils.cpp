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
                                            const std::function<void(sf::RenderTarget &renderer, sf::RenderStates)>& draw) {

    sf::RenderTexture render_texture;
    render_texture.create(renderer.getView().getSize().x, renderer.getView().getSize().y);
    draw(render_texture, sf::RenderStates::Default);
    render_texture.display();
    auto texture = std::make_shared<sf::Texture>(render_texture.getTexture());


    return std::move(texture);
}

void center_text_origin(sf::Text &text) {
    auto bounds = text.getLocalBounds();
    text.setOrigin(bounds.width/2, bounds.height/2);
}

void center_shape_origin(sf::Shape &shape) {
    auto bounds = shape.getLocalBounds();
    shape.setOrigin(bounds.width/2, bounds.height/2);
}

std::shared_ptr<sf::Texture> multiply_color(sf::Texture &texture, sf::Color color) {
    sf::Sprite sprite(texture);
    sprite.setColor(color);

    sf::RenderTexture render;
    render.create(texture.getSize().x, texture.getSize().y);
    render.draw(sprite, sf::RenderStates::Default);
    render.display();
    return std::move(std::make_shared<sf::Texture>(render.getTexture()));
}

std::shared_ptr<sf::Texture> add_color(sf::Texture &texture, sf::Color color) {
    auto img = texture.copyToImage();
    for(int x = 0; x<img.getSize().x; x++){
        for(int y = 0; y<img.getSize().y; y++){
            img.setPixel(x, y, img.getPixel(x, y) + color);
        }
    }
    auto res = std::make_shared<sf::Texture>();
    res->loadFromImage(img);
    return std::move(res);
}
