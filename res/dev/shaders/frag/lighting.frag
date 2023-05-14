#version 400 core

out vec4 FragColor;

in vec2 TexCoord;
in vec3 Normal;
in vec3 FragPos;

struct Material {
	sampler2D diffuse;
	sampler2D normal;
	sampler2D specular;
};

uniform Material material;

struct Light {
	vec3 ambientColor;
	float ambientStrength;
	vec3 diffuse;
	vec3 specular;
	//vec3 position;
	vec3 direction;
};

uniform Light light;

uniform vec3 viewPos;


void main()
{	

	vec4 color = texture(material.diffuse, TexCoord);
	vec4 normal = texture(material.normal, TexCoord);

	vec3 norm = normalize(Normal);
	vec3 lightDir = normalize(-light.direction);

	float diff = max(dot(norm, lightDir), 0.0);
	vec3 diffuse = 1 * diff * vec3(texture(material.diffuse, TexCoord));

	vec3 viewDir = normalize(viewPos - FragPos);
	vec3 reflectDir = reflect(-lightDir, norm);

	float spec = pow(max(dot(viewDir, reflectDir), 0.0), 32);
	vec3 specular = light.specular * spec * vec3(texture(material.specular, TexCoord));

	vec3 ambient = light.ambientColor * light.ambientStrength;
	vec3 result = (ambient + diffuse + specular) * vec3(color.x, color.y, color.z);

	FragColor = vec4(result, color.w);
}