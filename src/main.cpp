#include <iostream>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include "renderer.h"
#include "shader.h"
#include "loader.h"
#include "entity.h"
#include "input.h"

#define WINDOW_WIDTH 1280
#define WINDOW_HEIGHT 720

void on_resize_framebuffer_callback(GLFWwindow* window, int width, int height);

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

    initShaders();
    //loadObjects();

    if(e_ShaderProgram == -1){
        std::cout << "Shader program not loaded correctly! Exiting game [main.cpp line 46]" << std::endl;
        return -1;
    }

    loadAllTextures();
    createAllEntities();
    updateTextureUniform(e_ShaderProgram);

    preRender(e_ShaderProgram);
    Camera2D mainCamera{};

    while(!glfwWindowShouldClose(window)){

        processCameraMovement(window, mainCamera);

        glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        //simple_color_render(true);
        render(e_ShaderProgram, mainCamera);

        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glfwTerminate();
    return 0;
}


//Make sure rendering stays intact when changing window sizes
void on_resize_framebuffer_callback(GLFWwindow* window, int width, int height){
    glViewport(0,0, width, height);
}
