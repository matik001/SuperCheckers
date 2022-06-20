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

    ///////////////////// FONTS
    COURGETTE_FONT,
};

class ResourcesManager {
    std::map<Resource, std::shared_ptr<void> > _dict;
public:
    void load_texture_from_memory(Resource name, const void *data, size_t size);
    void load_font_from_memory(Resource name, const void *data, size_t size);
    std::shared_ptr<void> get(Resource name);
    void load_all();
    static ResourcesManager& singleton();
};


#endif //CHECKERSAI_RESOURCESMANAGER_H
