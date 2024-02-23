#pragma once

#include <stdexcept>

class PhysicsLoadingException : public std::runtime_error {
public:
	PhysicsLoadingException(std::string msg) : std::runtime_error(msg) {}
};
