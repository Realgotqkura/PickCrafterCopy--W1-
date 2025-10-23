#include "input.h"
#include "gamestate.h"
#include "entity.h"
#include <iostream>

bool isKeyPressedOnce(GLFWwindow* window, int key)
{
    static std::unordered_map<int, bool> keyStates;

    bool currentlyPressed = glfwGetKey(window, key) == GLFW_PRESS;
    bool lastPressed = keyStates[key];

    keyStates[key] = currentlyPressed;

    return (currentlyPressed && !lastPressed);
}

void processCameraMovement(GLFWwindow *window, Camera2D &cam2D)
{
    if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
    {
        cam2D.moveCameraX(-0.5f);
        return;
    }

    if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
    {
        cam2D.moveCameraX(0.5f);
        return;
    }

    if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
    {
        cam2D.moveCameraY(0.5f);
        return;
    }

    if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
    {
        cam2D.moveCameraY(-0.5f);
        return;
    }

    if (glfwGetKey(window, GLFW_KEY_Q) == GLFW_PRESS)
    {
        cam2D.zoomCamera(0.005f);
        return;
    }

    if (glfwGetKey(window, GLFW_KEY_E) == GLFW_PRESS)
    {
        cam2D.zoomCamera(-0.005f);
        return;
    }
}

void changeBlockBreakTexture(GLFWwindow *window)
{
    if (!isKeyPressedOnce(window, GLFW_KEY_SPACE))
        return;


 
    switch (GameData::blockBreakStage)
    {
    case 1:
        GameData::blockBreakStage++;
        GameData::currentBlockBreakTexture = TextureManager::textureObjectsList["blockbreak_stage2"].get();
        break;
    case 2:
        GameData::blockBreakStage++;
        GameData::currentBlockBreakTexture = TextureManager::textureObjectsList["blockbreak_stage3"].get();
        break;
    case 3:
        GameData::blockBreakStage++;
        GameData::currentBlockBreakTexture = TextureManager::textureObjectsList["blockbreak_stage4"].get();
        break;
    default:
        GameData::blockBreakStage = 1;
        GameData::currentBlockBreakTexture = TextureManager::textureObjectsList["blockbreak_stage1"].get();

        for(int i = 0; i < EntityManager::entities.size(); i++){
            if(strcmp(EntityManager::entities[i].get()->m_entityType, "main_block") == 0){
                if(strcmp(EntityManager::entities[i].get()->m_texture->m_textureName.c_str(), "grass") == 0){
                    EntityManager::entities[i].get()->m_texture = TextureManager::textureObjectsList["cobblestone"].get();
                }else if(strcmp(EntityManager::entities[i].get()->m_texture->m_textureName.c_str(), "cobblestone") == 0){
                    EntityManager::entities[i].get()->m_texture = TextureManager::textureObjectsList["grass"].get();
                }
            }
        }
        break;
    }

    std::cout << GameData::currentBlockBreakTexture->m_textureName << std::endl;
}
