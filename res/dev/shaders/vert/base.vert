#version 400 core

layout (location = 0) in vec3 aPos; // position has attribute position 0
//layout (location = 1) in vec3 aColor; // color has attribute position 1
layout (location = 1) in vec2 aTexCoord;

out vec4 vertexColor; // specify a color output to the fragment shader
out vec2 TexCoord;


void main()
{
	gl_Position = vec4(aPos, 1.0); // we give a vec3 to vec4’s constructor
	vec3 aColor = vec3(1.0, 1.0, 1.0);
	vertexColor = vec4(aColor, 1.0); 
	TexCoord = aTexCoord;
} 