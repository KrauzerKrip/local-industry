#pragma once

#include <string>
#include <glm/glm.hpp>

void setUniform(unsigned int shaderProgram, std::string uniform, float value);

void setUniform(unsigned int shaderProgram, std::string uniform, int value);

void setUniform(unsigned int shaderProgram, std::string uniform, glm::vec2 vector);

void setUniform(unsigned int shaderProgram, std::string uniform, glm::vec3 vector);

void setUniform(unsigned int shaderProgram, std::string uniform, glm::vec4 vector);

//void setUniform(unsigned int shaderProgram, std::string uniform, glm::vec3& vector) {
//	glUniformMatrix4fv(projLoc, 1, GL_FALSE, glm::value_ptr(projection));
//}


