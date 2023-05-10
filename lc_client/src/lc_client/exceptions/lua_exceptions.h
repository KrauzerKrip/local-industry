#pragma once

#include <stdexcept>

class LuaRunException : public std::runtime_error {
public:
	LuaRunException(std::string info) : std::runtime_error("Lua run exception:\n" + info + "\n") {}
};
