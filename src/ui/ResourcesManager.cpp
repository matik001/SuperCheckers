#include "ResourcesManager.h"
#include "../utils/FontResources.h"
#include <TGUI/Backend/SFML-Graphics.hpp>

void ResourcesManager::load_texture_from_memory(Resource name, const void *data, size_t size) {
    auto texture = std::make_shared<sf::Texture>();
    texture->loadFromMemory(data, size);
    texture->setSmooth(true);
    _dict[name] = texture;
}
void ResourcesManager::load_font_from_memory(Resource name, const void *data, size_t size) {
    auto font = std::make_shared<sf::Font>();
    font->loadFromMemory(data, size);
    _dict[name] = font;
}



std::shared_ptr<void> ResourcesManager::get(Resource name) {
    return _dict[name];
}

void ResourcesManager::load_all() {
    ///////////////////// IMAGES
    load_texture_from_memory(Resource::WHITE_PAWN, WHITE_PAWN_PNG, WHITE_PAWN_PNG_SIZE);
    load_texture_from_memory(Resource::BLACK_PAWN, BLACK_PAWN_PNG, BLACK_PAWN_PNG_SIZE);
    load_texture_from_memory(Resource::WHITE_QUEEN, WHITE_QUEEN_PNG, WHITE_QUEEN_PNG_SIZE);
    load_texture_from_memory(Resource::BLACK_QUEEN, BLACK_QUEEN_PNG, BLACK_QUEEN_PNG_SIZE);

    ///////////////////// FONTS
    load_font_from_memory(Resource::COURGETTE_FONT, COURGETTE_REGULAR_TTF, COURGETTE_REGULAR_TTF_SIZE);

}

ResourcesManager& ResourcesManager::singleton() {
    static ResourcesManager manager;
    return manager;
}

