#include "shader.h"
#include "rawdata.h"
#include <glad/glad.h>
#include <random>
#include <ctime>

unsigned int e_ShaderProgram = -1;

unsigned int loadVertexShader()
{
    unsigned int vertexShader;
    vertexShader = glCreateShader(GL_VERTEX_SHADER);

    std::string vertexShaderSource = loadVertexShaderSource();
    const char *rawSource = vertexShaderSource.c_str();

    glShaderSource(vertexShader, 1, &rawSource, NULL);
    glCompileShader(vertexShader);
    return vertexShader;
}

unsigned int loadFragmentShader()
{
    unsigned int fragmentShader;
    fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);

    std::string fragmentShaderSource = loadFragmentShaderSource();
    const char *rawSource = fragmentShaderSource.c_str();

    glShaderSource(fragmentShader, 1, &rawSource, NULL);
    glCompileShader(fragmentShader);
    return fragmentShader;
}

void createShaderProgram(unsigned int vertexShader, unsigned int fragmentShader)
{
    unsigned int shaderProgram;
    shaderProgram = glCreateProgram();
    glAttachShader(shaderProgram, vertexShader);
    glAttachShader(shaderProgram, fragmentShader);
    glLinkProgram(shaderProgram);
    glUseProgram(shaderProgram);
    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);
    loadUniforms(shaderProgram);
    e_ShaderProgram = shaderProgram;
}

// Basically calls all shader functions made, kind of like boilerplate but it makes the usage cleaner
void initShaders()
{
    unsigned int f_vertexShader = loadVertexShader();
    unsigned int f_fragmentShader = loadFragmentShader();
    createShaderProgram(f_vertexShader, f_fragmentShader);
}

void loadUniforms(unsigned int &shaderProgram)
{
    int colorUniformLocation = glGetUniformLocation(shaderProgram, "codeColor");
    glUniform4f(colorUniformLocation, 0.5f, 0.5f, 0.5f, 1.0f);
    glUniform1i(glGetUniformLocation(shaderProgram, "ourTexture"), 0);
}

void updateColorUniform(unsigned int &shaderProgram)
{
    static std::mt19937 gen(static_cast<unsigned int>(std::time(nullptr)));
    std::uniform_int_distribution<int> dist(0, 255);
    float rgb[3] = {dist(gen) / 255.0f, dist(gen) / 255.0f, dist(gen) / 255.0f};
    int colorUniformLocation = glGetUniformLocation(shaderProgram, "codeColor");
    glUniform4f(colorUniformLocation, rgb[0], rgb[1], rgb[2], 1.0f);
}

void updateTextureUniform(unsigned int &shaderProgram)
{
    glUniform1i(glGetUniformLocation(shaderProgram, "ourTexture"), 0);
    glActiveTexture(GL_TEXTURE0);
}

void setMat4(const unsigned int &shaderID, const std::string &name, const glm::mat4 &mat)
{
    glUniformMatrix4fv(glGetUniformLocation(shaderID, name.c_str()), 1, GL_FALSE, &mat[0][0]);
}