#include "lua_script.h"

#include <vector>

#include <lua.hpp>
#include <LuaBridge/LuaBridge.h>


ScriptLua::ScriptLua(const std::string source) { 
	m_pL = luaL_newstate();

	luaL_loadstring(m_pL, source.c_str());

	luaL_openlibs(m_pL);

	lua_pcall(m_pL, 0, 0, 0);

	luabridge::LuaRef s = luabridge::getGlobal(m_pL, "testString");
	std::string luaString = s.cast<std::string>();
	std::cout << "LUA STRING: " << luaString << std::endl;

	loadAPI();
}

lua_State* ScriptLua::getState() { return m_pL; }

void ScriptLua::loadAPI() {

}
