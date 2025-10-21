#pragma once
#include <string>
#include "glm/glm.hpp"
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

extern unsigned int e_ShaderProgram;

unsigned int loadVertexShader();
unsigned int loadFragmentShader();
void createShaderProgram(unsigned int vertexShader, unsigned int fragmentShader);
void initShaders();
void loadUniforms(unsigned int& shaderProgram);
void updateColorUniform(unsigned int& shaderProgram);
void updateTextureUniform(unsigned int& shaderProgram);
void setMat4(const unsigned int &shaderID, const std::string &name, const glm::mat4 &mat);