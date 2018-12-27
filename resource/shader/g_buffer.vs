#version 330 core
layout (location = 0) in vec3 position;
layout (location = 1) in vec3 normal;
layout (location = 2) in vec2 texCoords;
layout (location = 3) in vec3 tangent;
layout (location = 4) in vec3 bitangent;

out vec3 FragPos;
out vec2 TexCoords;
out mat3 TBN;


uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

void main()
{
    vec4 worldPos = model * vec4(position, 1.0f);
    FragPos = worldPos.xyz; 
    gl_Position = projection * view * worldPos;
    TexCoords = texCoords;
    
    mat3 normalMatrix = transpose(inverse(mat3(model)));
   vec3 T = normalize(vec3(model * vec4(tangent,   0.0)));
   vec3 N = normalize(vec3(model * vec4(normal,    0.0)));  
   T = normalize(T - dot(T, N) * N);
   vec3 B = cross(T, N);
    
    mat3 TBN = mat3(T, B, N);;  
}