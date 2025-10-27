#pragma once
#include <iostream>
#include "glm/glm.hpp"
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#define WINDOW_WIDTH 600
#define WINDOW_HEIGHT 900
#define MINIMUM_Y -2000;

extern float fps; //Used for functions with velocity. the formula is (FPS / 60.0f) and its used as velocity / fps_dividor

float clampValue(float value, float min, float max);
bool isInsideRange(float value, float min, float max);
void printMat4(const glm::mat4& mat);