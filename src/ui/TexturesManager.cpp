#include "TexturesManager.h"

void TexturesManager::load_from_memory(Textures name, const void *data, size_t size) {
    auto texture = std::make_shared<sf::Texture>();
    texture->loadFromMemory(data, size);
    texture->setSmooth(true);
    _dict[name] = texture;
}

void TexturesManager::load_from_path(Textures name, const char *path) {
    auto texture = std::make_shared<sf::Texture>();
    texture->loadFromFile(path);
    _dict[name] = texture;
}

std::shared_ptr<sf::Texture> TexturesManager::get(Textures name) {
    return _dict[name];
}

void TexturesManager::load_all() {
    load_from_memory(Textures::WHITE_PAWN, WHITE_PAWN_IMG, WHITE_PAWN_IMG_SIZE);
    load_from_memory(Textures::BLACK_PAWN, BLACK_PAWN_IMG, BLACK_PAWN_IMG_SIZE);
    load_from_memory(Textures::WHITE_QUEEN, WHITE_QUEEN_IMG, WHITE_QUEEN_IMG_SIZE);
    load_from_memory(Textures::BLACK_QUEEN, BLACK_QUEEN_IMG, BLACK_QUEEN_IMG_SIZE);
}

TexturesManager& TexturesManager::singleton() {
    static TexturesManager manager;
    return manager;
}
