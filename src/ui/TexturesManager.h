#ifndef CHECKERSAI_TEXTURESMANAGER_H
#define CHECKERSAI_TEXTURESMANAGER_H


#include <SFML/Graphics/Texture.hpp>
#include <map>
#include <memory>
#include "../utils/TextureResources.h"

enum Textures{
    BLACK_PAWN, WHITE_PAWN,
    BLACK_QUEEN, WHITE_QUEEN
};
class TexturesManager {
    std::map<Textures, std::shared_ptr<sf::Texture> > _dict;
public:
    void load_from_memory(Textures name, const void *data, size_t size);
    void load_from_path(Textures name, const char *path);
    std::shared_ptr<sf::Texture> get(Textures name);
    void load_all();
    static TexturesManager& singleton();
};


#endif //CHECKERSAI_TEXTURESMANAGER_H
