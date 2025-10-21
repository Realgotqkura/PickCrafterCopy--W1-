#pragma once
#include <iostream>
#include "glm/glm.hpp"
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

float clampValue(float value, float min, float max);
bool isInsideRange(float value, float min, float max);
void printMat4(const glm::mat4& mat);
void runSmily();