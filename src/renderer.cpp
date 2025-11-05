#include "renderer.h"
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <random>
#include <ctime>
#include "loader.h"
#include "shader.h"
#include "entity.h"
#include "glm/glm.hpp"
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <chrono>
#include "utilities.h"
#include "gamestate.h"
#include "gui.h"
#include "font_rendering.h"

void simple_color_render(bool randomize)
{

    if (!randomize)
    {
        glClearColor(72 / 255.0f, 181 / 255.0f, 58 / 255.0f, 1);
    }
    else
    {
        static std::mt19937 gen(static_cast<unsigned int>(std::time(nullptr)));
        std::uniform_int_distribution<int> dist(0, 255);

        float r = dist(gen) / 255.0f;
        float g = dist(gen) / 255.0f;
        float b = dist(gen) / 255.0f;

        glClearColor(r, g, b, 1.0f);
    }

    glClear(GL_COLOR_BUFFER_BIT);
}

void preRender()
{
    glm::mat4 projection = glm::ortho(0.0f, (float)WINDOW_WIDTH, 0.0f, (float)WINDOW_HEIGHT, -1.0f, 1.0f);
    glUseProgram(t_ShaderProgram);
    setMat4(t_ShaderProgram, "projection", projection);
    setInt(t_ShaderProgram, "textureOne", 0);

    glUseProgram(e_ShaderProgram);
    setMat4(e_ShaderProgram, "projection", projection);
    setInt(e_ShaderProgram, "textureOne", 0);
}

void renderText(Camera2D &cam2D)
{

    glm::mat4 view = cam2D.getViewMatrix();
    setMat4(t_ShaderProgram, "view", view);

    for (int i = 0; i < TextManager::textComponents.size(); i++)
    {
        setMat4(t_ShaderProgram, "transform", TextManager::textComponents[i].get()->getModelMatrix());
        TextManager::textComponents[i].get()->renderText();
    }
}

void render(Camera2D &cam2D)
{

    unsigned int shaderProgram = e_ShaderProgram;

    /*
    glm::mat4 trans = glm::mat4(1.0f);
    trans = glm::translate(trans, glm::vec3(100.0f, 0.0f,0.0f));
    trans = glm::scale(trans, glm::vec3(50.0f, 50.0f, 1)); // scale in pixels

    */

    // cam
    glm::mat4 view = cam2D.getViewMatrix();
    setMat4(e_ShaderProgram, "view", view);

    for (int i = 0; i < EntityManager::entities.size(); i++)
    {
        Entity *entity = EntityManager::entities[i].get();
        setMat4(shaderProgram, "transform", entity->getModelMatrix());
        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, TextureManager::texturesList[entity->m_texture->m_textureName]);
        glBindVertexArray(entity->m_object.m_Vao);

        /*
        float size = 0.0f;
        glGetBufferParameteriv(GL_ARRAY_BUFFER, GL_BUFFER_SIZE, (GLint *)&size);
        std::cout << "VBO size: " << size << std::endl;
        */

        glDrawArrays(GL_TRIANGLES, 0, 6);

        // do stuff
        static float cleanupTimer = 0.0f; // persists between frames
        float deltaTime = 1.0f / fps;     // seconds per frame

        cleanupTimer += deltaTime;
        if (cleanupTimer >= 1.0f / 30.0f)
        { // 60 times per second
            entity->doEverything();
        }
    }

    for (int i = 0; i < GuiManager::elements.size(); i++)
    {
        setMat4(shaderProgram, "transform", GuiManager::elements[i].get()->getModelMatrix());
        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, TextureManager::texturesList[GuiManager::elements[i]->m_texture->m_textureName]);
        glBindVertexArray(GuiManager::elements[i]->m_object.m_Vao);
        glDrawArrays(GL_TRIANGLES, 0, 6);
    }
}