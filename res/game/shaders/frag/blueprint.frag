#version 400 core

out vec4 FragColor;

in vec4 vertexColor; // input variable from vs (same name and type)
in vec2 TexCoord;


void main()
{	 
	vec4 color = vec4(48.0 / 255.0, 87.0 / 255.0, 225.0 / 255.0, 0.5); 
	FragColor = color;
}