#pragma once
#include "raw_object.h"
#include "texture.h"
#include <vector>
#include <memory>
#include "glm/glm.hpp"
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

class Entity
{
public:
Entity(RawObject object, Texture* texture);
Entity(RawObject object, Texture* texture, glm::vec3 position);
RawObject m_object;
Texture* m_texture;
glm::vec3 m_position{0.0f};
glm::vec3 m_rotation{0.0f}; //degrees
glm::vec3 m_scale{50.0f};


glm::mat4 getModelMatrix();
void setPosition(glm::vec3& position);
void setRotation(glm::vec3& rotation);
void setScale(glm::vec3& scale);





};

namespace EntityManager{
    extern std::vector<std::unique_ptr<Entity>> entities;
};

void createAllEntities();

void addEntity(std::unique_ptr<Entity> entity);