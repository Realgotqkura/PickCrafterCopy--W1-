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

void preRender(unsigned int &shaderProgram)
{
    glm::mat4 projection = glm::ortho(0.0f, 1280.0f, 0.0f, 720.0f, -1.0f, 1.0f);
    setMat4(shaderProgram, "projection", projection);
}

void render(unsigned int &shaderProgram, Camera2D &cam2D)
{

    /*
    glm::mat4 trans = glm::mat4(1.0f);
    trans = glm::translate(trans, glm::vec3(100.0f, 0.0f,0.0f));
    trans = glm::scale(trans, glm::vec3(50.0f, 50.0f, 1)); // scale in pixels

    */
    //cam
    glm::mat4 view = cam2D.getViewMatrix();
    setMat4(shaderProgram, "view", view);


    for (int i = 0; i < EntityManager::entities.size(); i++)
    {
        setMat4(shaderProgram, "transform", EntityManager::entities[i].get()->getModelMatrix());
        glActiveTexture(GL_TEXTURE0);                                                                                         // activate textureunit 0
        glBindTexture(GL_TEXTURE_2D, TextureManager::texturesList.at(EntityManager::entities[i]->m_texture->m_textureName)); // bind your texture
        glBindVertexArray(EntityManager::entities[i]->m_object.m_Vao);
        glDrawArrays(GL_TRIANGLES, 0, 6);

        //do stuff
        runSmily();
    }
        
        
}