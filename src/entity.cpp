#include "entity.h"
#include "verteces.h"
#include <iostream>
#include "utilities.h"
#include <algorithm>

Entity::Entity(RawObject object, Texture *texture, std::string entityType) : m_object(object), m_texture(texture), m_entityType(entityType) {}

Entity::Entity(RawObject object, Texture *texture, glm::vec3 position, std::string entityType) : m_object(object), m_texture(texture), m_position(position), m_entityType(entityType) {}

Entity::Entity(RawObject object, Texture *texture, glm::vec3 position, glm::vec3 rotation, glm::vec3 scale, std::string entityType) : m_object(object), m_texture(texture), m_position(position), m_rotation(rotation), m_scale(scale), m_entityType(entityType) {}

glm::mat4 Entity::getModelMatrix()
{
    glm::mat4 model = glm::mat4(1.0f);

    model = glm::translate(model, m_position);
    model = glm::rotate(model, glm::radians(m_rotation.x), glm::vec3(1, 0, 0));
    model = glm::rotate(model, glm::radians(m_rotation.y), glm::vec3(0, 1, 0));
    model = glm::rotate(model, glm::radians(m_rotation.z), glm::vec3(0, 0, 1));
    model = glm::scale(model, m_scale);

    return model;
}

void Entity::setPosition(glm::vec3 &position)
{
    m_position = position;
}

void Entity::setRotation(glm::vec3 &rotation)
{
    m_rotation = rotation;
}

void Entity::setScale(glm::vec3 &scale)
{
    m_scale = scale;
}

void Entity::move()
{
    float gravity = m_gravityEnabled ? -0.98f : 0.0f;

    float delta_x = m_speed.x * ((m_VelocityX > 0) - (m_VelocityX < 0));
    float delta_y = m_speed.y * ((m_VelocityY > 0) - (m_VelocityY < 0));

    if (std::abs(m_VelocityY) == 0)
        delta_y = gravity;

    if (std::abs(m_VelocityX) - m_speed.x > 0)
        m_VelocityX -= m_speed.x * ((m_VelocityX > 0) - (m_VelocityX < 0));

    if (std::abs(m_VelocityY) - m_speed.y > 0)
        m_VelocityY -= m_speed.y * ((m_VelocityY > 0) - (m_VelocityY < 0));

    if (isInsideRange(m_VelocityX, -5, 5))
        delta_x = 0;

    if (isInsideRange(m_VelocityY, -5, 5))
        m_VelocityY = 0;

    m_position.x += delta_x;
    m_position.y += delta_y;

    if (m_position.y < 0)
        m_delete = true;
}

void Entity::rotate(){
    
    float delta_r = m_rotationSpeed * ((m_rotationVelocity > 0) - (m_rotationVelocity < 0));

    if (std::abs(m_rotationVelocity) - m_rotationSpeed > 0)
        m_rotationVelocity -= m_rotationSpeed * ((m_rotationVelocity > 0) - (m_rotationVelocity < 0));

    if (isInsideRange(m_rotationVelocity, -5, 5))
        m_rotationVelocity = 0;

    m_rotation.z += delta_r;
}

void Entity::deleteEntity(){
    if (m_delete)
    {
        auto it = std::find_if(EntityManager::entities.begin(), EntityManager::entities.end(),
                               [this](const std::unique_ptr<Entity> &e)
                               { return e.get() == this; });

        if (it != EntityManager::entities.end())
        {
            EntityManager::entities.erase(it); // automatically deletes the object
        }
    }
}

void Entity::doEverything()
{
    if (!m_dynamic)
        return;

    move();
    rotate();
    deleteEntity();
}

namespace EntityManager
{
    std::vector<std::unique_ptr<Entity>> entities;
}

void createAllEntities()
{

    addEntity(std::make_unique<Entity>(createBasicSquare(), TextureManager::textureObjectsList["grass"].get(), glm::vec3(WINDOW_WIDTH / 2.0f, WINDOW_HEIGHT / 2.0f, 0.0f), glm::vec3{0.0f}, glm::vec3(WINDOW_WIDTH, WINDOW_HEIGHT, 0.0f), "main_block"));
    addEntity(std::make_unique<Entity>(createBasicSquare(), TextureManager::textureObjectsList["blockbreak_stage1"].get(), glm::vec3(WINDOW_WIDTH / 2.0f, WINDOW_HEIGHT / 2.0f, 0.0001f), glm::vec3{0.0f}, glm::vec3(WINDOW_WIDTH, WINDOW_HEIGHT, 0.0f), "breaking_entity"));

    addEntity(std::make_unique<Entity>(createBasicSquare(), TextureManager::textureObjectsList["diamond_pickaxe"].get(), glm::vec3(WINDOW_WIDTH - 100.0f, WINDOW_HEIGHT / 2.5f, 0.0002f), glm::vec3{0.0f, 0.0f, 35.0f}, glm::vec3(600, 900, 0.0f), "pickaxe"));
}

Entity *addEntity(std::unique_ptr<Entity> entity)
{
    EntityManager::entities.emplace_back(std::move(entity));
    return EntityManager::entities.back().get();
}

Entity *getEntity(std::string f_entityType)
{
    for (size_t i = 0; i < EntityManager::entities.size(); i++)
    {
        if (f_entityType.compare(EntityManager::entities[i]->m_entityType) == 0)
        {
            return EntityManager::entities[i].get();
        }
    }

    return nullptr;
}