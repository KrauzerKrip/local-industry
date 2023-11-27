#pragma once

#include <string>

#include <glad/glad.h>
#include <glm/gtc/type_ptr.hpp>


void setUniform(unsigned int shaderProgram, std::string uniform, float value) {
	glUniform1f(glGetUniformLocation(shaderProgram, uniform.c_str()), value);
}

void setUniform(unsigned int shaderProgram, std::string uniform, int value) {
	glUniform1i(glGetUniformLocation(shaderProgram, uniform.c_str()), value);
}

void setUniform(unsigned int shaderProgram, std::string uniform, glm::vec3 vector) {
	glUniform3fv(glGetUniformLocation(shaderProgram, uniform.c_str()), 1, glm::value_ptr(vector));
}

void setUniform(unsigned int shaderProgram, std::string uniform, glm::vec4 vector) {
	glUniform4fv(glGetUniformLocation(shaderProgram, uniform.c_str()), 1, glm::value_ptr(vector));
}

// void setUniform(unsigned int shaderProgram, std::string uniform, glm::vec3& vector) {
//	glUniformMatrix4fv(projLoc, 1, GL_FALSE, glm::value_ptr(projection));
// }
