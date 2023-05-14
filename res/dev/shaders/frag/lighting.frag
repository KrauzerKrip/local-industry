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

struct AmbientLight {
	vec3 color;
	float strength;
};

uniform AmbientLight ambientLight;

struct PointLight {
	vec3 position;

	vec3 diffuse;
	vec3 specular;

	float constant;
	float linear;
	float quadratic;
};

uniform PointLight pointLight;

struct SpotLight {
	vec3 position;
	vec3 direction;
	float cutOff;
	float outerCutOff;

	vec3 diffuse;
	vec3 specular;

	float constant;
	float linear;
	float quadratic;
};

uniform SpotLight spotLight;

uniform vec3 viewPos;


void main()
{	

	vec3 norm = normalize(Normal);
	vec3 lightDir = normalize(spotLight.position - FragPos);

	vec4 color = texture(material.diffuse, TexCoord);
	vec4 normal = texture(material.normal, TexCoord);

	vec3 ambient = ambientLight.color * ambientLight.strength;

	float theta = dot(lightDir, normalize(-spotLight.direction));

	if(theta > spotLight.outerCutOff)
	{
	
		float distance = length(spotLight.position - FragPos);
		float attenuation = 1.0 / (spotLight.constant + spotLight.linear * distance +
		spotLight.quadratic * (distance * distance)); // Fatt = 1.0 / (Kc + K1*d + Kq * d^2)

		float diff = max(dot(norm, lightDir), 0.0);
		vec3 diffuse = 1 * diff * vec3(texture(material.diffuse, TexCoord));

		vec3 viewDir = normalize(viewPos - FragPos);
		vec3 reflectDir = reflect(-lightDir, norm);

		float spec = pow(max(dot(viewDir, reflectDir), 0.0), 32);
		vec3 specular = spotLight.specular * spec * vec3(texture(material.specular, TexCoord));

		float epsilon = spotLight.cutOff - spotLight.outerCutOff;
		float intensity = clamp((theta - spotLight.outerCutOff) / epsilon, 0.0, 1.0);

		//ambient *= attenuation;
		diffuse *= intensity * attenuation;
		specular *= intensity * attenuation;

		vec3 result = (ambient + diffuse + specular) * vec3(color.x, color.y, color.z);
		FragColor = vec4(result, color.w);
	
	}
	else {
		vec3 result = ambient * vec3(color.x, color.y, color.z);
		FragColor = vec4(result, color.w);
	}

}