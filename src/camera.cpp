#include "camera.h"
#include "utilities.h"

Camera2D::Camera2D() : m_position(glm::vec2(0.0f, 0.0f)), m_zoom(1.0f){}

Camera2D::Camera2D(glm::vec2 position, float zoom) : m_position(position), m_zoom(zoom) {}

glm::mat4 Camera2D::getViewMatrix(){
    glm::mat4 view = glm::mat4(1.0f);

    view = glm::translate(view, glm::vec3(-m_position, 0.0f));
    view = glm::scale(view, glm::vec3(m_zoom, m_zoom, 1.0f));

    return view;
}

void Camera2D::moveCameraX(float distance){
    m_position.x += distance;
}

void Camera2D::moveCameraY(float distance){
    m_position.y += distance;
}

void Camera2D::zoomCamera(float zoom){
    if(!isInsideRange(m_zoom + zoom, 0.5f, 5.0f)) return;

    m_zoom += zoom;
}

