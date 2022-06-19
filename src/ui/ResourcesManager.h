#ifndef CHECKERSAI_RESOURCESMANAGER_H
#define CHECKERSAI_RESOURCESMANAGER_H


#include <SFML/Graphics/Texture.hpp>
#include <map>
#include <memory>
#include "../utils/TextureResources.h"

enum Resources{
    ///////////////////// IMAGES
    BLACK_PAWN, WHITE_PAWN,
    BLACK_QUEEN, WHITE_QUEEN,

    ///////////////////// FONTS
    COURGETTE_FONT,
};

class ResourcesManager {
    std::map<Resources, std::shared_ptr<void> > _dict;
public:
    void load_texture_from_memory(Resources name, const void *data, size_t size);
    void load_font_from_memory(Resources name, const void *data, size_t size);
    std::shared_ptr<void> get(Resources name);
    void load_all();
    static ResourcesManager& singleton();
};


#endif //CHECKERSAI_RESOURCESMANAGER_H
