#version 330 core

layout (location = 0) in vec3 aPos;
layout (location = 1) in vec2 textureCoords;

out vec4 vertexColor;
out vec2 outTexCoords;


uniform mat4 view;
uniform mat4 projection;
uniform mat4 transform;

void main(){

    gl_Position = projection * view * transform * vec4(aPos.x, aPos.y, 0.0f, 1.0f);
    outTexCoords = textureCoords;

}