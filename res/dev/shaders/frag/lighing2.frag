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
	vec3 lightDir = normalize(spotLight.position - FragPos);

	vec4 color = texture(material.diffuse, TexCoord);
	//vec4 normal = texture(material.normal, TexCoord);

	vec3 amb = ambientLight.color * ambientLight.strength;

	float theta = dot(lightDir, normalize(-spotLight.direction));

	if(theta > spotLight.cutOff)
	{
	
        // ambient
        vec3 ambient = amb * texture(material.diffuse, TexCoord).rgb;
        
        // diffuse 
        vec3 norm = normalize(Normal);
        float diff = max(dot(norm, lightDir), 0.0);
        vec3 diffuse = spotLight.diffuse * diff * texture(material.diffuse, TexCoord).rgb;  
        
        // specular
        vec3 viewDir = normalize(viewPos - FragPos);
        vec3 reflectDir = reflect(-lightDir, norm);  
        float spec = pow(max(dot(viewDir, reflectDir), 0.0), 32);
        vec3 specular = spotLight.specular * spec * texture(material.specular, TexCoord).rgb;  
        
        // attenuation
        float distance    = length(spotLight.position - FragPos);
        float attenuation = 1.0 / (spotLight.constant + spotLight.linear * distance + spotLight.quadratic * (distance * distance));    

        // ambient  *= attenuation; // remove attenuation from ambient, as otherwise at large distances the light would be darker inside than outside the spotlight due the ambient term in the else branch
        diffuse   *= attenuation;
        specular *= attenuation;   
            
        vec3 result = ambient + diffuse + specular;
        FragColor = vec4(result, color.w);
	
	}
	else {
		vec3 result = vec3(amb * texture(material.diffuse, TexCoord).rgb);
		FragColor = vec4(result, color.w);
	}

}