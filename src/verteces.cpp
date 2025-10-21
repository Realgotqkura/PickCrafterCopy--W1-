#include "verteces.h"

float triangleVerteces[] = {
    // first triangle
    -0.5f, 0.5f, 0.0f, 1.0f, 0.0f,  // top-left
    -0.5f, -0.5f, 0.0f, 1.0f, 1.0f, // bottom-left
    0.5f, -0.5f, 0.0f, 0.0f, 1.0f,  // bottom-right

    // second triangle
    -0.5f, 0.5f, 0.0f, 1.0f, 0.0f, // top-left
    0.5f, -0.5f, 0.0f, 0.0f, 1.0f, // bottom-right
    0.5f, 0.5f, 0.0f, 0.0f, 0.0f   // top-right
};

const size_t triangleVertexesSize = sizeof(triangleVerteces) / sizeof(float);