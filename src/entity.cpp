#include "entity.h"
#include "verteces.h"
#include <iostream>
#include "utilities.h"

Entity::Entity(RawObject object, Texture *texture) : m_object(object), m_texture(texture) {}

Entity::Entity(RawObject object, Texture *texture, glm::vec3 position) : m_object(object), m_texture(texture), m_position(position) {}

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

namespace EntityManager
{
    std::vector<std::unique_ptr<Entity>> entities;
}

void createAllEntities()
{
    addEntity(std::make_unique<Entity>(createBasicSquare(), TextureManager::textureObjectsList["smily"].get(), glm::vec3(700.0f, 350.0f, 0.0f)));
    addEntity(std::make_unique<Entity>(createBasicSquare(), TextureManager::textureObjectsList["smily"].get(), glm::vec3(700.0f, 450.0f, 0.0f)));
    addEntity(std::make_unique<Entity>(createBasicSquare(), TextureManager::textureObjectsList["smily"].get(), glm::vec3(700.0f, 550.0f, 0.0f)));
    addEntity(std::make_unique<Entity>(createBasicSquare(), TextureManager::textureObjectsList["smily"].get(), glm::vec3(700.0f, 650.0f, 0.0f)));
    addEntity(std::make_unique<Entity>(createBasicSquare(), TextureManager::textureObjectsList["smily"].get(), glm::vec3(700.0f, 750.0f, 0.0f)));
}

void addEntity(std::unique_ptr<Entity> entity)
{
    EntityManager::entities.emplace_back(std::move(entity));
}