#include "ResourcesManager.h"
#include "../utils/FontResources.h"
#include "../utils/SfmlUtils.h"

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

void ResourcesManager::load_tgui_font_from_memory(Resource name, const void *data, size_t size) {
    auto font = std::make_shared<tgui::Font>(data, size);
    _dict[name] = font;
}



void ResourcesManager::load_all_sfml() {
    ///////////////////// IMAGES
    load_texture_from_memory(Resource::WHITE_PAWN, WHITE_PAWN_PNG, WHITE_PAWN_PNG_SIZE);
    load_texture_from_memory(Resource::BLACK_PAWN, BLACK_PAWN_PNG, BLACK_PAWN_PNG_SIZE);
    load_texture_from_memory(Resource::WHITE_QUEEN, WHITE_QUEEN_PNG, WHITE_QUEEN_PNG_SIZE);
    load_texture_from_memory(Resource::BLACK_QUEEN, BLACK_QUEEN_PNG, BLACK_QUEEN_PNG_SIZE);
    load_texture_from_memory(Resource::MENU, MENU_PNG, MENU_PNG_SIZE);
    load_texture_from_memory(Resource::SAVE, SAVE_PNG, SAVE_PNG_SIZE);
    load_texture_from_memory(Resource::REVERT, REVERT_PNG, REVERT_PNG_SIZE);
    add(REVERT_HOVER, add_color(*get<sf::Texture>(REVERT), sf::Color(255, 255, 255, 0)));
    add(REVERT_DOWN, add_color(*get<sf::Texture>(REVERT), sf::Color(0, 220, 0, 0)));
    add(REVERT, add_color(*get<sf::Texture>(REVERT), sf::Color(210, 210, 210, 0)));

    ///////////////////// FONTS
    load_font_from_memory(Resource::COURGETTE_FONT, COURGETTE_REGULAR_TTF, COURGETTE_REGULAR_TTF_SIZE);
    load_font_from_memory(Resource::UBUNTU_REGULAR_FONT, UBUNTU_REGULAR_TTF, UBUNTU_REGULAR_TTF_SIZE);
    load_font_from_memory(Resource::UBUNTU_BOLD_FONT, UBUNTU_BOLD_TTF, UBUNTU_BOLD_TTF_SIZE);
}

void ResourcesManager::load_all_tgui() {
    ///////////////////// FONTS TGUI
    load_tgui_font_from_memory(Resource::TGUI_COURGETTE_FONT, COURGETTE_REGULAR_TTF, COURGETTE_REGULAR_TTF_SIZE);
    load_tgui_font_from_memory(Resource::TGUI_UBUNTU_REGULAR_FONT, UBUNTU_REGULAR_TTF, UBUNTU_REGULAR_TTF_SIZE);
    load_tgui_font_from_memory(Resource::TGUI_UBUNTU_BOLD_FONT, UBUNTU_BOLD_TTF, UBUNTU_BOLD_TTF_SIZE);

}



ResourcesManager& ResourcesManager::singleton() {
    static ResourcesManager manager;
    return manager;
}

void ResourcesManager::add(Resource name, std::shared_ptr<void> obj) {
    _dict[name] = obj;
}


