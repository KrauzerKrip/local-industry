#include "text.h"

#include <glad/glad.h>
#include <glm/gtc/matrix_transform.hpp>
#include<glm/gtc/type_ptr.hpp>
#include <iostream>
#include "lc_client/eng_graphics/openGL/gl_shader_uniform.h"

Text::Text(std::string text, glm::vec2 position, float scale, glm::vec3 color) { 
	m_text = text;
	m_position = position;
	m_scale = scale;
	m_color = color;
}

