#include "texture.h"
#include "stb_image.h"
#include "glad/glad.h"
#include "GLFW/glfw3.h"
#include <iostream>


namespace TextureManager
{
    std::map<std::string, unsigned int> texturesList;
    std::map<std::string, std::unique_ptr<Texture>> textureObjectsList;
}

Texture::Texture(const char *path, const char *textureName)
{
    int width, height, channels;
    unsigned char *data = stbi_load(path, &width, &height, &channels, STBI_rgb_alpha);
    unsigned int texture;

    if (data)
    {
        glGenTextures(1, &texture);
        glBindTexture(GL_TEXTURE_2D, texture);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
    }
    else
    {
        printf("failed to load image: %s\n", stbi_failure_reason());
    }

    m_textureName = textureName;

    TextureManager::texturesList.insert({std::string(textureName), texture});
    stbi_image_free(data);
}


void loadAllTextures(){
    std::cout << "ran texture check" << std::endl;
    TextureManager::textureObjectsList["cobblestone"] = std::make_unique<Texture>("textures/cobblestone.jpg", "cobblestone");
    TextureManager::textureObjectsList["smily"] = std::make_unique<Texture>("textures/smily.png", "smily");
}
