#version 400 core

in vec2 TexCoords;
out vec4 color;

uniform sampler2D image;

void main()
{
	vec4 sampled = texture(image, TexCoords);
	color = sampled;
}