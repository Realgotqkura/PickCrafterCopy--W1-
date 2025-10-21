#pragma once
#include "vector"
#include <array>

class RawObject
{
public:
    std::vector<float> verteces;
    RawObject(const std::vector<float>& vertexes);
    unsigned int m_Vao;
    unsigned int m_Vbo;
    unsigned int m_VertexSize;
    

private:
    std::array<unsigned int, 2> loadRawObject(const std::vector<float>& vertexes);
};

RawObject createBasicSquare();