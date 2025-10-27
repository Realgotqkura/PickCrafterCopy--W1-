#include "input.h"
#include "gamestate.h"
#include "entity.h"
#include <iostream>
#include "utilities.h"
#include <random>
#include <ctime>

bool isKeyPressedOnce(GLFWwindow *window, int key)
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

    static std::mt19937 gen(static_cast<unsigned int>(std::time(nullptr)));

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

        std::string breakTex = "grass";
        for (int i = 0; i < EntityManager::entities.size(); i++)
        {

            if (EntityManager::entities[i]->m_entityType == "main_block")
            {
                if (strcmp(EntityManager::entities[i].get()->m_texture->m_textureName.c_str(), "grass") == 0)
                {
                    breakTex = "grass";
                    EntityManager::entities[i].get()->m_texture = TextureManager::textureObjectsList["cobblestone"].get();
                }
                else if (strcmp(EntityManager::entities[i].get()->m_texture->m_textureName.c_str(), "cobblestone") == 0)
                {
                    breakTex = "cobblestone";
                    EntityManager::entities[i].get()->m_texture = TextureManager::textureObjectsList["grass"].get();
                }
            }
        }

        std::uniform_int_distribution<int> dist(0, 1000000000);
        std::uniform_int_distribution<int> generatedVelocityX(-600, 600);
        std::uniform_int_distribution<int> generatedVelocityY(300, 1000);
        std::uniform_int_distribution<int> generatedPosX(250, 350);
        std::uniform_int_distribution<int> generatedPosY(300, 700);
        std::uniform_int_distribution<int> generatedRotation(-700, 700);
        for (int i = 0; i < 30; i++)
        {
            std::string type = std::string("moving_") + std::to_string(dist(gen)).c_str();
            Entity *movable = addEntity(std::make_unique<Entity>(createBasicSquare(), TextureManager::textureObjectsList[breakTex.c_str()].get(), glm::vec3(generatedPosX(gen), generatedPosY(gen), 0.0003f), glm::vec3{0.0f}, glm::vec3(75.0f, 75.0f, 0.0f), type));
            movable->m_dynamic = true;
            movable->m_gravityEnabled = true;
            movable->m_VelocityX = (float)generatedVelocityX(gen);
            movable->m_VelocityY = (float)generatedVelocityY(gen);
            movable->m_speed = glm::vec2{0.5f, 2.0f};
            movable->m_rotationVelocity = (float)generatedRotation(gen);
            movable->m_rotationSpeed = 0.3f;
        }
        break;
    }
    getEntity("breaking_entity")->m_texture = GameData::currentBlockBreakTexture;
    Entity *pickaxeEntity = getEntity("pickaxe");

    if (pickaxeEntity->m_rotation.z == 35.0f)
    {
        pickaxeEntity->m_rotation.z = 55.0f;
    }
    else
    {
        pickaxeEntity->m_rotation.z = 35.0f;
    }
}
