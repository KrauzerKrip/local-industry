#pragma once

#include <stdexcept>
#include <string>


class ConsoleParameterNotFoundException : public std::runtime_error {
public:
	ConsoleParameterNotFoundException(std::string name) : std::runtime_error("Console parameter not found: '" + name + "'") {}
};

class ConsoleParameterConstantValueException : public std::runtime_error {
public:
	ConsoleParameterConstantValueException(std::string name)
		: std::runtime_error("Attempt to change value of console parameter flagged as CONSTANT. Console parameter: '" + name + "'") {}
};

class ConsoleParameterCheatsException : public std::runtime_error {
public:
	ConsoleParameterCheatsException(std::string name)
		: std::runtime_error(
			  "Console parameter '" + name + "' is protected by sv_cheats.") {}
};