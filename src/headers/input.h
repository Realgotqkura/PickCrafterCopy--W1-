#pragma once
#include "GLFW/glfw3.h"
#include "camera.h"

void processCameraMovement(GLFWwindow* window, Camera2D &cam2D);
void changeBlockBreakTexture(GLFWwindow* window);
bool isKeyPressedOnce(GLFWwindow* window, int key);