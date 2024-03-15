#version 400 core

out vec4 FragColor;

in vec4 vertexColor; // input variable from vs (same name and type)
in vec2 TexCoord;

struct Material {
	sampler2D diffuse;
	sampler2D normal;
	sampler2D specular;
	float shininess;
};

uniform Material material;


void main()
{	
	vec4 color = texture(material.diffuse, TexCoord);
	vec4 normal = texture(material.normal, TexCoord);

	float ambientStrength = 0.1;
//	vec3 ambient = ambientStrength * lightColor;
//	vec3 result = ambient * objectColor;

	FragColor = color;
}