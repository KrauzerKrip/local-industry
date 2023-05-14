#version 400 core

out vec4 FragColor;

in vec2 TexCoord;
in vec3 Normal;
in vec3 FragPos;

struct Material {
	sampler2D diffuse;
	sampler2D normal;
	sampler2D specular;
	float shininess;
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

//uniform PointLight pointLight;

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

struct DirectionalLight {
	vec3 direction;

	vec3 diffuse;
	vec3 specular;
};

uniform DirectionalLight directionalLight;

uniform vec3 viewPos;

#define NR_POINT_LIGHTS 4
uniform PointLight pointLights[NR_POINT_LIGHTS];


vec3 calculateDirectionalLight(DirectionalLight light, AmbientLight ambientLight, vec3 normal, vec3 viewDir);
vec3 calculatePointLight(PointLight light, AmbientLight ambientLight, vec3 normal, vec3 fragPos, vec3 viewDir);
vec3 calculateSpotLight(SpotLight light, AmbientLight ambientLight, vec3 normal, vec3 fragPos, vec3 viewDir);


void main()
{	

	// properties
	vec3 normal = normalize(Normal);
	vec3 viewDir = normalize(viewPos - FragPos);

	vec3 lightDir = normalize(spotLight.position - FragPos);

	// phase 1: Directional lighting
	vec3 result = calculateDirectionalLight(directionalLight, ambientLight, normal, viewDir);

	// phase 2: Point lights
	for(int i = 0; i < NR_POINT_LIGHTS; i++) {
		result += calculatePointLight(pointLights[i], ambientLight, normal, FragPos, viewDir);
	}

	float theta = dot(lightDir, normalize(-spotLight.direction));

	if(theta > spotLight.outerCutOff)
	{
		result += calculateSpotLight(spotLight, ambientLight, normal, FragPos, viewDir);
	}
	else {
		result =+ ambientLight.color * ambientLight.strength;
	}
	
	FragColor = vec4(result, 1.0);
}

vec3 calculateDirectionalLight(DirectionalLight light, AmbientLight ambientLight, vec3 normal, vec3 viewDir) 
{
	vec3 lightDir = normalize(-light.direction);
	// diffuse shading
	float diff = max(dot(normal, lightDir), 0.0);
	// specular shading
	vec3 reflectDir = reflect(-lightDir, normal);
	float spec = pow(max(dot(viewDir, reflectDir), 0.0),
	material.shininess);
	// combine results
	vec3 ambient = ambientLight.color * ambientLight.strength * vec3(texture(material.diffuse, TexCoord));
	vec3 diffuse = light.diffuse * diff * vec3(texture(material.diffuse, TexCoord));
	vec3 specular = light.specular * spec * vec3(texture(material.specular, TexCoord));

	return (ambient + diffuse + specular);
}

vec3 calculatePointLight(PointLight light, AmbientLight ambientLight, vec3 normal, vec3 fragPos, vec3 viewDir) 
{
	vec3 lightDir = normalize(light.position - fragPos);
	// diffuse shading
	float diff = max(dot(normal, lightDir), 0.0);
	// specular shading
	vec3 reflectDir = reflect(-lightDir, normal);
	float spec = pow(max(dot(viewDir, reflectDir), 0.0),
	material.shininess);
	// attenuation
	float distance = length(light.position - fragPos);
	float attenuation = 1.0 / (light.constant + light.linear * distance +
	light.quadratic * (distance * distance));
	// combine results
	vec3 ambient = ambientLight.color * ambientLight.strength * vec3(texture(material.diffuse, TexCoord));
	vec3 diffuse = light.diffuse * diff * vec3(texture(material.diffuse, TexCoord));
	vec3 specular = light.specular * spec * vec3(texture(material.specular, TexCoord));

	ambient *= attenuation;
	diffuse *= attenuation;
	specular *= attenuation;

	return (ambient + diffuse + specular);
}

vec3 calculateSpotLight(SpotLight light, AmbientLight ambientLight, vec3 normal, vec3 fragPos, vec3 viewDir)
{
		vec3 lightDir = normalize(light.position - fragPos);

		float distance = length(light.position - FragPos);
		float attenuation = 1.0 / (light.constant + spotLight.linear * distance +
		light.quadratic * (distance * distance)); // Fatt = 1.0 / (Kc + K1*d + Kq * d^2)

		float diff = max(dot(normal, lightDir), 0.0);
		vec3 diffuse = 1 * diff * vec3(texture(material.diffuse, TexCoord));

		vec3 reflectDir = reflect(-lightDir, normal);

		float spec = pow(max(dot(viewDir, reflectDir), 0.0), 32);
		vec3 specular = light.specular * spec * vec3(texture(material.specular, TexCoord));

		float theta = dot(lightDir, normalize(-light.direction));
		float epsilon = light.cutOff - light.outerCutOff;
		float intensity = clamp((theta - light.outerCutOff) / epsilon, 0.0, 1.0);

		vec3 ambient = ambientLight.color * ambientLight.strength * vec3(texture(material.diffuse, TexCoord));

		ambient *= attenuation;
		diffuse *= intensity * attenuation;
		specular *= intensity * attenuation;

		return (ambient + diffuse + specular);
}