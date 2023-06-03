#version 400 core

layout (location = 0) in vec3 aPos;

out vec3 TexCoords;

uniform mat4 projection;
uniform mat4 view;

void main()
{
	vec3 pos = vec3(aPos.x, aPos.y, aPos.z);
	TexCoords = pos;
	gl_Position = projection * view * vec4(aPos, 1.0);
}