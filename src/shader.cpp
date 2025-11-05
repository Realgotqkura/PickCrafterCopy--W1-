#include "shader.h"
#include "rawdata.h"
#include <glad/glad.h>
#include <random>
#include <ctime>
#include <iostream>

unsigned int e_ShaderProgram = -1;
unsigned int t_ShaderProgram = -1;

unsigned int loadVertexShader()
{
    unsigned int vertexShader;
    vertexShader = glCreateShader(GL_VERTEX_SHADER);

    std::string vertexShaderSource = loadShaderSource("src/shaders/vertex.glsl");
    const char *rawSource = vertexShaderSource.c_str();

    glShaderSource(vertexShader, 1, &rawSource, NULL);
    glCompileShader(vertexShader);
    return vertexShader;
}

unsigned int loadFragmentShader()
{
    unsigned int fragmentShader;
    fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);

    std::string fragmentShaderSource = loadShaderSource("src/shaders/fragment.glsl");
    const char *rawSource = fragmentShaderSource.c_str();

    glShaderSource(fragmentShader, 1, &rawSource, NULL);
    glCompileShader(fragmentShader);
    return fragmentShader;
}

unsigned int loadTextVertexShader()
{
    unsigned int vertexShader;
    vertexShader = glCreateShader(GL_VERTEX_SHADER);

    std::string vertexShaderSource = loadShaderSource("src/shaders/text_vertex.glsl");
    const char *rawSource = vertexShaderSource.c_str();

    glShaderSource(vertexShader, 1, &rawSource, NULL);
    glCompileShader(vertexShader);
    return vertexShader;
}

unsigned int loadTextFragmentShader()
{
    unsigned int fragmentShader;
    fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);

    std::string fragmentShaderSource = loadShaderSource("src/shaders/text_fragment.glsl");
    const char *rawSource = fragmentShaderSource.c_str();

    glShaderSource(fragmentShader, 1, &rawSource, NULL);
    glCompileShader(fragmentShader);

    return fragmentShader;
}


void createShaderProgram(unsigned int vertexShader, unsigned int fragmentShader, bool isTextShader)
{
    unsigned int shaderProgram;
    shaderProgram = glCreateProgram();
    glAttachShader(shaderProgram, vertexShader);
    glAttachShader(shaderProgram, fragmentShader);
    glLinkProgram(shaderProgram);
    glUseProgram(shaderProgram);


    int success;
    char infoLog[512];
    glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);
    if (!success) {
        glGetProgramInfoLog(shaderProgram, 512, NULL, infoLog);
        std::cout << "Shader link error:\n" << infoLog << std::endl;
    }

    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);
    loadUniforms(shaderProgram);
    if(isTextShader){
       t_ShaderProgram = shaderProgram; 
    }else{
        e_ShaderProgram = shaderProgram;
    }
}

// Basically calls all shader functions made, kind of like boilerplate but it makes the usage cleaner
void initShaders()
{
    unsigned int f_vertexShader = loadVertexShader();
    unsigned int f_fragmentShader = loadFragmentShader();
    createShaderProgram(f_vertexShader, f_fragmentShader, false);

    unsigned int f_TextvertexShader = loadTextVertexShader();
    unsigned int f_TextfragmentShader = loadTextFragmentShader();
    createShaderProgram(f_TextvertexShader, f_TextfragmentShader, true);
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

void setMat4(const unsigned int &shaderID, const std::string &name, const glm::mat4 &mat)
{
    glUniformMatrix4fv(glGetUniformLocation(shaderID, name.c_str()), 1, GL_FALSE, &mat[0][0]);
}

void setInt(const unsigned int &shaderID, const std::string &name, unsigned int num)
{
    glUniform1i(glGetUniformLocation(shaderID, name.c_str()), num);
}