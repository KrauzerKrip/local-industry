#pragma once

#include <string>

#include <lua.hpp>

#include "lc_client/util/i_eng_resource.h"


class ScriptLua {
public:
	ScriptLua(const std::string source);
	ScriptLua(const std::string path, const eng::IResource* resource);
	~ScriptLua() = default;

	lua_State* getState();

private:
	void loadAPI();

	lua_State* m_pL;
};
