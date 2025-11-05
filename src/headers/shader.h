#pragma once
#include <string>
#include "glm/glm.hpp"
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

extern unsigned int e_ShaderProgram; //entities
extern unsigned int t_ShaderProgram; //text

unsigned int loadVertexShader();
unsigned int loadFragmentShader();
unsigned int loadTextVertexShader();
unsigned int loadTextFragmentShader();
void createShaderProgram(unsigned int vertexShader, unsigned int fragmentShader, bool isTextShader);
void initShaders();
void loadUniforms(unsigned int& shaderProgram);
void updateColorUniform(unsigned int& shaderProgram);
void setInt(const unsigned int &shaderID, const std::string &name, unsigned int num);
void setMat4(const unsigned int &shaderID, const std::string &name, const glm::mat4 &mat);