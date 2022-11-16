#version 400 core

out vec4 FragColor;

in vec4 vertexColor; // input variable from vs (same name and type)
in vec2 TexCoord;

uniform sampler2D textureSampler;


void main()
{
	FragColor = texture(textureSampler, TexCoord);
}