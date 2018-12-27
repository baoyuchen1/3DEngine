#version 330 core
layout (location = 0) in vec3 position;
layout (location = 1) in vec2 texCoords;

out vec2 TexCoords;

struct Light {
    vec3 Position;
    vec3 Color;
    
    float Linear;
    float Quadratic;
    float Radius;
};
const int NR_LIGHTS = 32;
uniform Light lights[NR_LIGHTS];
uniform mat4 model;

void main()
{
    gl_Position = vec4(position, 1.0f);
    TexCoords = texCoords;
}