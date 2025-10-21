#pragma once
#include "camera.h"

void simple_color_render(bool randomize);
void render(unsigned int& shaderProgram, Camera2D &cam2D);
void preRender(unsigned int& shaderProgram);