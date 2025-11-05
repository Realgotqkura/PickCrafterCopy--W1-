#include "rawdata.h"
#include <sstream>
#include <iostream>

std::string loadShaderSource(const char* path){
    std::ifstream shaderFile;

    shaderFile.open(path);

    if(!shaderFile.is_open()){
        std::cout << "Couldn't Open Vertex Shader!" << std::endl;
        return "";
    }

    std::stringstream buffer;
    buffer << shaderFile.rdbuf();
    return buffer.str();
}







