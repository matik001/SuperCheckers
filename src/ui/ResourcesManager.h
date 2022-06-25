#ifndef CHECKERSAI_RESOURCESMANAGER_H
#define CHECKERSAI_RESOURCESMANAGER_H


#include <TGUI/Backend/SFML-Graphics.hpp>
#include <map>
#include <memory>
#include "../utils/TextureResources.h"

enum Resource{
    ///////////////////// IMAGES
    BLACK_PAWN, WHITE_PAWN,
    BLACK_QUEEN, WHITE_QUEEN,
    MENU, SAVE,  REVERT, REVERT_HOVER,  REVERT_DOWN,

    ///////////////////// FONTS
    COURGETTE_FONT,
    UBUNTU_REGULAR_FONT,
    UBUNTU_BOLD_FONT,

    ///////////////////// FONTS TGUI
    TGUI_COURGETTE_FONT,
    TGUI_UBUNTU_REGULAR_FONT,
    TGUI_UBUNTU_BOLD_FONT,
};

class ResourcesManager {
    std::map<Resource, std::shared_ptr<void> > _dict;
public:
    void load_texture_from_memory(Resource name, const void *data, size_t size);
    void load_font_from_memory(Resource name, const void *data, size_t size);
    void load_tgui_font_from_memory(Resource name, const void *data, size_t size);
    void add(Resource name, std::shared_ptr<void> obj);

    /// nie moze byc w .cpp bo linker w c++ jest glupi: https://bytefreaks.net/programming-2/c/c-undefined-reference-to-templated-class-function
    template<class T>
    std::shared_ptr<T> get(Resource name) {
        return std::static_pointer_cast<T>(_dict[name]);
    }

    void load_all_sfml();
    void load_all_tgui();
    static ResourcesManager& singleton();
};


#endif //CHECKERSAI_RESOURCESMANAGER_H
