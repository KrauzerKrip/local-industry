#version 400 core

out vec4 FragColor;

in vec4 vertexColor; // input variable from vs (same name and type)
in vec2 TexCoord;

uniform sampler2D textureSamplerColor;
uniform sampler2D textureSamplerNormal;


void main()
{	
	vec4 color = texture(textureSamplerColor, TexCoord);
	vec4 normal = texture(textureSamplerNormal, TexCoord);

	float ambientStrength = 0.1;
//	vec3 ambient = ambientStrength * lightColor;
//	vec3 result = ambient * objectColor;

	FragColor = color;
}