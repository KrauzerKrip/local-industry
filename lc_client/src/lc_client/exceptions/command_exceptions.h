#pragma once

#include <stdexcept>
#include <string>


class IncorrectCommandException : public std::runtime_error {
public:
	IncorrectCommandException(std::string command) : std::runtime_error("Incorrect command form: '" + command + "'") {}
};
