#include "gui.h"
#include "utilities.h"

GuiElement::GuiElement(RawObject object, Texture *texture, const char* entityType) : m_object(object), m_texture(texture), m_entityType(entityType) {}

GuiElement::GuiElement(RawObject object, Texture *texture, glm::vec3 position, const char* entityType) : m_object(object), m_texture(texture), m_position(position), m_entityType(entityType) {}

GuiElement::GuiElement(RawObject object, Texture *texture, glm::vec3 position, glm::vec3 rotation, glm::vec3 scale, const char* entityType) : m_object(object), m_texture(texture), m_position(position), m_rotation(rotation), m_scale(scale), m_entityType(entityType) {}


glm::mat4 GuiElement::getModelMatrix()
{
    glm::mat4 model = glm::mat4(1.0f);

    model = glm::translate(model, m_position);
    model = glm::rotate(model, glm::radians(m_rotation.x), glm::vec3(1, 0, 0));
    model = glm::rotate(model, glm::radians(m_rotation.y), glm::vec3(0, 1, 0));
    model = glm::rotate(model, glm::radians(m_rotation.z), glm::vec3(0, 0, 1));
    model = glm::scale(model, m_scale);

    return model;
}

void GuiElement::setPosition(glm::vec3 &position)
{
    m_position = position;
}

void GuiElement::setRotation(glm::vec3 &rotation)
{
    m_rotation = rotation;
}

void GuiElement::setScale(glm::vec3 &scale)
{
    m_scale = scale;
}

namespace GuiManager
{
    std::vector<std::unique_ptr<GuiElement>> elements;
}

void createAllGuiElements()
{

    addGuiElements(std::make_unique<GuiElement>(createBasicSquare(), TextureManager::textureObjectsList["downMenu_GUI"].get(), glm::vec3(WINDOW_WIDTH/2.0f,45.0f, 0.0100f), glm::vec3{0.0f}, glm::vec3(WINDOW_WIDTH, 100.0f, 0.0f), "downGuiMenu"));
    addGuiElements(std::make_unique<GuiElement>(createBasicSquare(), TextureManager::textureObjectsList["downMenu_Pickaxes"].get(), glm::vec3(100.0f,45.0f, 0.0101f), glm::vec3{0.0f}, glm::vec3(65.0f, 65.0f, 0.0f), "buttonUpgrades"));
    addGuiElements(std::make_unique<GuiElement>(createBasicSquare(), TextureManager::textureObjectsList["downMenu_Paid"].get(), glm::vec3(200.0f,45.0f, 0.0101f), glm::vec3{0.0f}, glm::vec3(65.0f, 65.0f, 0.0f), "buttonPaid"));
    addGuiElements(std::make_unique<GuiElement>(createBasicSquare(), TextureManager::textureObjectsList["downMenu_Artifacts"].get(), glm::vec3(300.0f,45.0f, 0.0101f), glm::vec3{0.0f}, glm::vec3(65.0f, 65.0f, 0.0f), "buttonArtifacts"));
    addGuiElements(std::make_unique<GuiElement>(createBasicSquare(), TextureManager::textureObjectsList["downMenu_Rebirth"].get(), glm::vec3(400.0f,45.0f, 0.0101f), glm::vec3{0.0f}, glm::vec3(65.0f, 65.0f, 0.0f), "buttonRebirth"));
    addGuiElements(std::make_unique<GuiElement>(createBasicSquare(), TextureManager::textureObjectsList["downMenu_Empty"].get(), glm::vec3(500.0f,45.0f, 0.0101f), glm::vec3{0.0f}, glm::vec3(65.0f, 65.0f, 0.0f), "buttonEmpty"));
}

void addGuiElements(std::unique_ptr<GuiElement> entity)
{
    GuiManager::elements.emplace_back(std::move(entity));
}