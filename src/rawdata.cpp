#include "rawdata.h"
#include <sstream>
#include <iostream>

std::string loadVertexShaderSource(){

    std::ifstream vertexShaderFile;

    vertexShaderFile.open("src/shaders/vertex.glsl");

    if(!vertexShaderFile.is_open()){
        std::cout << "Couldn't Open Vertex Shader!" << std::endl;
        return "";
    }

    std::stringstream buffer;
    buffer << vertexShaderFile.rdbuf();
    return buffer.str();

}

std::string loadFragmentShaderSource(){

    std::ifstream fragmentShaderSource;

    fragmentShaderSource.open("src/shaders/fragment.glsl");

    if(!fragmentShaderSource.is_open()){
        std::cout << "Couldn't Open Fragment Shader!" << std::endl;
        return "";
    }

    std::stringstream buffer;
    buffer << fragmentShaderSource.rdbuf();
    return buffer.str();

}





