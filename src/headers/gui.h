#pragma once
#include "raw_object.h"
#include "texture.h"
#include <vector>
#include <memory>
#include "glm/glm.hpp"
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

class GuiElement
{
public:
GuiElement(RawObject object, Texture* texture, const char* entityType);
GuiElement(RawObject object, Texture* texture, glm::vec3 position, const char* entityType);
GuiElement(RawObject object, Texture* texture, glm::vec3 position, glm::vec3 rotation, glm::vec3 scale, const char* entityType);
RawObject m_object;
Texture* m_texture;
glm::vec3 m_position{0.0f};
glm::vec3 m_rotation{0.0f}; //degrees
glm::vec3 m_scale{50.0f};
const char* m_entityType; //Used for differentiation instead of using textures


glm::mat4 getModelMatrix();
void setPosition(glm::vec3& position);
void setRotation(glm::vec3& rotation);
void setScale(glm::vec3& scale);





};

namespace GuiManager{
    extern std::vector<std::unique_ptr<GuiElement>> elements;
};

void createAllGuiElements();

void addGuiElements(std::unique_ptr<GuiElement> entity);