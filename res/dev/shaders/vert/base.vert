#version 400 core

layout (location = 0) in vec3 aPos; // position has attribute position 0
layout (location = 1) in vec3 aNormal; // color has attribute position 1
layout (location = 2) in vec2 aTexCoord;

out vec2 TexCoord;
out vec3 FragPos;
out vec3 Normal;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;
uniform mat4 normalMatrix;


void main()
{
	gl_Position = projection * view * model * vec4(aPos, 1.0f); 
	TexCoord = vec2(aTexCoord.x, 1 - aTexCoord.y);
	FragPos = vec3(model * vec4(aPos, 1.0));
	Normal = mat3(normalMatrix) * aNormal;
} 