#include "utilities.h"
#include "entity.h"
#include <random>
#include <ctime>

float fps = 1;

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
