#pragma once

#include <stdexcept>

class GladInitFailException : public std::runtime_error {
public:
	GladInitFailException() : std::runtime_error("Failed to initialize GLAD.") { }
};