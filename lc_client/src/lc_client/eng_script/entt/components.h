#pragma once

#include <string>
#include <memory>

#include <lua.hpp>


struct Script {
	std::string path;
	lua_State* luaState;

	Script() = default;
	Script(std::string path, lua_State* luaState) : path(path), luaState(luaState) {}
	Script(const Script&) = default;
};
