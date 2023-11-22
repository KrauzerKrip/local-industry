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

Text::Text(Text& other) { 
	m_text = other.m_text;
	m_position = other.m_position;
	m_scale = other.m_scale;
	m_color = other.m_color;
}

Text& Text::operator=(Text& other) {
	if (this != &other)  {
		m_text = other.m_text;
		m_position = other.m_position;
		m_scale = other.m_scale;
		m_color = other.m_color;
	}
	return *this;
}

std::string Text::getText() { return m_text; }

glm::vec2 Text::getPosition() { return m_position; }

float Text::getScale() { return m_scale; }

glm::vec3 Text::getColor() { return m_color; }

