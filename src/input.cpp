#include "input.h"


void processCameraMovement(GLFWwindow* window, Camera2D &cam2D){
    if(glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS){
        cam2D.moveCameraX(-0.5f);
        return;
    }

    if(glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS){
        cam2D.moveCameraX(0.5f);
        return;
    }

    if(glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS){
        cam2D.moveCameraY(0.5f);
        return;
    }

    if(glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS){
        cam2D.moveCameraY(-0.5f);
        return;
    }

    if(glfwGetKey(window, GLFW_KEY_Q) == GLFW_PRESS){
        cam2D.zoomCamera(0.005f);
        return;
    }

    if(glfwGetKey(window, GLFW_KEY_E) == GLFW_PRESS){
        cam2D.zoomCamera(-0.005f);
        return;
    }

}
