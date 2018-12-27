#version 330 core
layout (location = 0) out vec3 gPosition;
layout (location = 1) out vec3 gNormal;
layout (location = 2) out vec4 gAlbedoSpec;
layout (location = 3) out vec3 gtangent;
layout (location = 4) out vec3 gbitangent;

in vec2 TexCoords;
in vec3 FragPos;
in vec3 TangentLightPos;
in vec3 TangentViewPos;
in vec3 TangentFragPos;

uniform sampler2D texture_diffuse1;
uniform sampler2D texture_specular1;
uniform sampler2D texture_specular1;

void main()
{    
    // Store the fragment position vector in the first gbuffer texture
    gPosition = FragPos;
    // Also store the per-fragment normals into the gbuffer
	vec3 normal = texture(normalMap, TexCoords).rgb;
    // Transform normal vector to range [-1,1]
    gNormal = normalize(normal * 2.0 - 1.0); 
    // And the diffuse per-fragment color
    gAlbedoSpec.rgb = texture(texture_diffuse1, TexCoords).rgb;
    // Store specular intensity in gAlbedoSpec's alpha component
    gAlbedoSpec.a = texture(texture_specular1, TexCoords).r;

	gtangent = TangentViewPos;

	gbitangent = TangentFragPos;
}