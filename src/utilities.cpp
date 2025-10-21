#include "utilities.h"
#include "entity.h"
#include <random>
#include <ctime>

float clampValue(float value, float min, float max)
{
    if (value < min)
        return min += 0.001f;

    if (value > max)
        return max -= 0.001f;

    return value;
}

bool isInsideRange(float value, float min, float max)
{
    if (value < min)
        return false;

    if (value > max)
        return false;

    return true;
}

void printMat4(const glm::mat4 &mat)
{
    for (int row = 0; row < 4; ++row)
    {
        std::cout << "| ";
        for (int col = 0; col < 4; ++col)
        {
            std::cout << mat[col][row] << " "; // glm is column-major
        }
        std::cout << "|\n";
    }
}

void runSmily()
{
    for (int i = 0; i < EntityManager::entities.size(); i++)
    {
        Entity *entity = EntityManager::entities[i].get();
        Texture *tex = entity->m_texture;

        if (tex->m_textureName == "smily")
        {
            static std::mt19937 gen(static_cast<unsigned int>(std::time(nullptr)));
            std::uniform_int_distribution<int> dist(1, 10);

            if(isInsideRange(entity->m_position.x + dist(gen), 0, 1280)){
                entity->m_position.x += dist(gen) / 100.0f;
            }else{
                entity->m_position.x = 0.0f;
            }

            
        }
    }
}