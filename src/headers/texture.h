#pragma once
#include <string>
#include <map>
#include <memory>

class Texture
{
public:
    std::string m_textureName;
    Texture(const char* path, const char* textureName);
};

namespace TextureManager
{
    extern std::map<std::string, unsigned int> texturesList; //For openGL
    extern std::map<std::string, std::unique_ptr<Texture>> textureObjectsList;
};

void loadAllTextures();
