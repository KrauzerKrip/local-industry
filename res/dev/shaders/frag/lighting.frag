#version 400 core

out vec4 FragColor;

in vec4 vertexColor; // input variable from vs (same name and type)
in vec2 TexCoord;

uniform sampler2D textureSamplerColor;
uniform sampler2D textureSamplerNormal;

uniform vec3 ambientLightColor;
uniform float ambientLightStrength;


void main()
{	
	vec4 color = texture(textureSamplerColor, TexCoord);
	vec4 normal = texture(textureSamplerNormal, TexCoord);

	vec3 ambient = ambientLightStrength * ambientLightColor;
	vec3 result = ambient * vec3(color.x, color.y, color.z);

	FragColor = vec4(result, color.w);
}