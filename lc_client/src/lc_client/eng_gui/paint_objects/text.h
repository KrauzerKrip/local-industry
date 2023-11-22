#pragma once

#include <glm/glm.hpp>
#include <string>

class Text {
public:
	Text(std::string text, glm::vec2 position, float scale, glm::vec3 color);
	Text(Text& other);
	Text& operator=(Text& other);  

	std::string getText();
	glm::vec2 getPosition();
	float getScale();
	glm::vec3 getColor();

private:
	std::string m_text;
	glm::vec2 m_position;
	float m_scale;
	glm::vec3 m_color;
};
