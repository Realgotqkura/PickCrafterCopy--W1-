#pragma once
#include "glm/glm.hpp"
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

class Camera2D{
    public:
    glm::vec2 m_position;
    float m_zoom;

    Camera2D();
    Camera2D(glm::vec2 position, float zoom);

    glm::mat4 getViewMatrix();
    void moveCameraX(float distance);
    void moveCameraY(float distance);
    void zoomCamera(float zoom);
};