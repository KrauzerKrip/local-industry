#pragma once

#include <stdexcept>

class NpcGraphException : public std::runtime_error {
public:
	NpcGraphException(std::string msg) : std::runtime_error(msg) {}
};
