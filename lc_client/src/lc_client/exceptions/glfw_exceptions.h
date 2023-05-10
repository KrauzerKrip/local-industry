#pragma once

#include <stdexcept>

class GlfwWindowFailException : public std::runtime_error {
public:
	GlfwWindowFailException() : std::runtime_error("Failed to create GLFW window.") { }
};