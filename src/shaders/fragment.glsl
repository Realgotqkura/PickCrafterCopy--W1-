#version 330 core

out vec4 FragColor;

in vec2 outTexCoords;

uniform vec4 codeColor;
uniform sampler2D ourTexture;

void main(){

    FragColor = texture(ourTexture, outTexCoords);
}