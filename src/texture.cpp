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
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
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

void loadAllTextures()
{
    std::cout << "ran texture check" << std::endl;
    TextureManager::textureObjectsList["cobblestone"] = std::make_unique<Texture>("textures/cobblestone.jpg", "cobblestone");
    TextureManager::textureObjectsList["smily"] = std::make_unique<Texture>("textures/smily.png", "smily");
    TextureManager::textureObjectsList["grass"] = std::make_unique<Texture>("textures/grass.png", "grass");

    // Block break textures
    TextureManager::textureObjectsList["blockbreak_stage1"] = std::make_unique<Texture>("textures/breaking_stages/stage_one.png", "blockbreak_stage1");
    TextureManager::textureObjectsList["blockbreak_stage2"] = std::make_unique<Texture>("textures/breaking_stages/stage_two.png", "blockbreak_stage2");
    TextureManager::textureObjectsList["blockbreak_stage3"] = std::make_unique<Texture>("textures/breaking_stages/stage_three.png", "blockbreak_stage3");
    TextureManager::textureObjectsList["blockbreak_stage4"] = std::make_unique<Texture>("textures/breaking_stages/stage_final.png", "blockbreak_stage4");

    // guis
    TextureManager::textureObjectsList["downMenu_GUI"] = std::make_unique<Texture>("textures/gui/downMenu.png", "downMenu_GUI");
    TextureManager::textureObjectsList["downMenu_Empty"] = std::make_unique<Texture>("textures/gui/buttonFrameEmpty.png", "downMenu_Empty");
    TextureManager::textureObjectsList["downMenu_Pickaxes"] = std::make_unique<Texture>("textures/gui/buttonFrameUpgrades.png", "downMenu_Pickaxes");
    TextureManager::textureObjectsList["downMenu_Paid"] = std::make_unique<Texture>("textures/gui/buttonFramePaid.png", "downMenu_Paid");
    TextureManager::textureObjectsList["downMenu_Artifacts"] = std::make_unique<Texture>("textures/gui/buttonFrameArtifacts.png", "downMenu_Artifacts");
    TextureManager::textureObjectsList["downMenu_Rebirth"] = std::make_unique<Texture>("textures/gui/buttonFrameRebirth.png", "downMenu_Rebirth");

    TextureManager::textureObjectsList["diamond_pickaxe"] = std::make_unique<Texture>("textures/pickaxes/Diamond_Pickaxe.png", "diamondPickaxe");
}
