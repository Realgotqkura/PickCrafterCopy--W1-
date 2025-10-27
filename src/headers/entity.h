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
Entity(RawObject object, Texture* texture, std::string entityType);
Entity(RawObject object, Texture* texture, glm::vec3 position, std::string entityType);
Entity(RawObject object, Texture* texture, glm::vec3 position, glm::vec3 rotation, glm::vec3 scale, std::string entityType);
RawObject m_object;
Texture* m_texture;
glm::vec3 m_position{0.0f};
glm::vec3 m_rotation{0.0f}; //degrees
glm::vec3 m_scale{50.0f};
std::string m_entityType; //Used for differentiation instead of using textures
float m_VelocityX{0.0f};
float m_VelocityY{0.0f};
bool m_gravityEnabled{false}; //Gravity is 9.8 pixels per frame in the (-y) axis
bool m_dynamic{false}; //Enables the move function
glm::vec2 m_speed{1.0f, 1.0f};
float m_rotationSpeed{1.0f};
float m_rotationVelocity{0.0f};
bool m_delete{false};


glm::mat4 getModelMatrix();
void setPosition(glm::vec3& position);
void setRotation(glm::vec3& rotation);
void setScale(glm::vec3& scale);
void move();
void rotate();
void deleteEntity();
void doEverything(); //Just does all dynamic thingies in 1 function







};

namespace EntityManager{
    extern std::vector<std::unique_ptr<Entity>> entities;
};

void createAllEntities();

Entity* addEntity(std::unique_ptr<Entity> entity);

Entity* getEntity(std::string f_entityType);