#version 400 core

layout (location = 0) in vec4 vertex; // <vec2 pos, vec2 tex>
out vec2 TexCoords;
uniform mat4 projection;
uniform float zOffset;

void main()
{
	gl_Position = projection * vec4(vertex.xy, zOffset, 1.0);
	TexCoords = gl_Position.st * 0.5 + 0.5;
}