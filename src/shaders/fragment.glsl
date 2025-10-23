#version 330 core

out vec4 FragColor;

in vec2 outTexCoords;

uniform sampler2D textureOne;
uniform sampler2D textureTwo;

void main() {

    vec4 tex1 = texture(textureOne, outTexCoords);
    vec4 tex2 = texture(textureTwo, outTexCoords);


// RGB blend only
    vec3 rgb = mix(tex1.rgb, tex2.rgb, 0.2);

// Alpha = top texture’s alpha
    float alpha = 1.0 - tex2.a;

    FragColor = vec4(rgb, alpha);
}