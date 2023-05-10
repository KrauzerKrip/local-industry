#pragma once

#include <string>
#include <memory>

#include <lua.hpp>


struct Script {
	std::string path;
	lua_State* luaState;

	Script() : luaState(luaL_newstate()){};
	Script(std::string path, lua_State* luaState) : path(path), luaState(luaState) {}
	Script(const Script&) = default;
};

struct Init {
};
