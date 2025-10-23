#pragma once
#include <iostream>
#include "glm/glm.hpp"
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#define WINDOW_WIDTH 1000
#define WINDOW_HEIGHT 1500

float clampValue(float value, float min, float max);
bool isInsideRange(float value, float min, float max);
void printMat4(const glm::mat4& mat);