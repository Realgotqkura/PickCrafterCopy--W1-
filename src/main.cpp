#include <iostream>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include "renderer.h"
#include "shader.h"
#include "loader.h"
#include "entity.h"
#include "input.h"
#include "utilities.h"
#include "gamestate.h"
#include "gui.h"
#include <chrono>
#include <ctime>

void on_resize_framebuffer_callback(GLFWwindow *window, int width, int height);

int main()
{

    // Creating a window
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    GLFWwindow *window = glfwCreateWindow(WINDOW_WIDTH, WINDOW_HEIGHT, "PickCrafter", NULL, NULL);

    if (window == NULL)
    {
        std::cout << "Failed to create OpenGL Window, Exiting Program" << std::endl;
        glfwTerminate();
        return -1;
    }

    glfwMakeContextCurrent(window);

    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cout << "Failed to initialize GLAD" << std::endl;
        return -1;
    }

    glViewport(0, 0, WINDOW_WIDTH, WINDOW_HEIGHT);
    glfwSetFramebufferSizeCallback(window, on_resize_framebuffer_callback);

    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LESS);

    initShaders();
    // loadObjects();

    if (e_ShaderProgram == -1)
    {
        std::cout << "Shader program not loaded correctly! Exiting game [main.cpp line 46]" << std::endl;
        return -1;
    }

    loadAllTextures();
    createAllEntities();
    createAllGuiElements();
    initGameData();
    setInt(e_ShaderProgram, "textureOne", 0);

    preRender(e_ShaderProgram);
    Camera2D mainCamera{};
    static double lastTime = glfwGetTime();
    static unsigned int frames = 0;

    while (!glfwWindowShouldClose(window))
    {
        // Render stuff
        changeBlockBreakTexture(window);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        render(e_ShaderProgram, mainCamera);
        glfwSwapBuffers(window);
        glfwPollEvents();

        // FPS calculation
        frames++;
        double currentTime = glfwGetTime();
        if (currentTime - lastTime >= 1.0)
        {
            fps = frames;
            frames = 0;
            lastTime = currentTime; // <-- reset to current time
            std::cout << "FPS: " << fps << std::endl;
        }
    }

    glfwTerminate();
    return 0;
}

// Make sure rendering stays intact when changing window sizes
void on_resize_framebuffer_callback(GLFWwindow *window, int width, int height)
{
    glViewport(0, 0, width, height);
}
