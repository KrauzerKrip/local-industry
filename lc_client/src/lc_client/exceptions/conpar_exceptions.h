#pragma once

#include <stdexcept>

class ConsoleParameterNotFoundException : public std::runtime_error {
public:
	ConsoleParameterNotFoundException(std::string name) : std::runtime_error("Console parameter not found: '" + name + "'") {}
};
