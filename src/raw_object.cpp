#include "raw_object.h"
#include <glad/glad.h>
#include "verteces.h"
#include <iostream>

RawObject::RawObject(const std::vector<float>& vertexes){
    std::array<unsigned int, 2> vaoAndVbo = loadRawObject(vertexes);
    m_Vao = vaoAndVbo[0];
    m_Vbo = vaoAndVbo[1];
    m_VertexSize = vertexes.size() / 3;
}

std::array<unsigned int, 2> RawObject::loadRawObject(const std::vector<float>& vertexes){
    unsigned int VBO;
    unsigned int VAO;

    glGenVertexArrays(1, &VAO);
    glBindVertexArray(VAO);

    glGenBuffers(1, &VBO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, vertexes.size() * sizeof(float), vertexes.data(), GL_STATIC_DRAW);
    
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float),(void*) 0);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float),(void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);

    return {VAO, VBO};
}

RawObject createBasicSquare(){
    const std::vector<float> floatVec(triangleVerteces, triangleVerteces + triangleVertexesSize);
    return RawObject(floatVec);
}