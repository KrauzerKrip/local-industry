#pragma once

#include <string>

#include <lua.hpp>


class ScriptLua {
public:
	ScriptLua(const std::string source);
	~ScriptLua() = default;

	lua_State* getState();

private:
	void loadAPI();

	lua_State* m_pL;
};
