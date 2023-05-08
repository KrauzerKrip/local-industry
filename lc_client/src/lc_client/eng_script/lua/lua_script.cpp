#include "lua_script.h"

#include <vector>
#include <algorithm>

#include <lua.hpp>
#include <LuaBridge/LuaBridge.h>
#include <entt/entt.hpp>

#include "lc_client/eng_script/api/bindings/api_component_binding.h"
#include "lc_client/eng_script/api/bindings/glm_binding.h"
#include "lc_client/eng_script/api/bindings/api_binding.h"
#include "lc_client/exceptions/lua_exceptions.h"


using namespace luabridge;


ScriptLua::ScriptLua(const std::string source) { 
	m_pL = luaL_newstate();

	luaL_openlibs(m_pL);

	loadAPI();

	if (luaL_loadstring(m_pL, source.c_str()) || lua_pcall(m_pL, 0, 0, 0)) {
		const std::string exceptionInfo(lua_tostring(m_pL, -1));
		throw LuaRunException(exceptionInfo);
	}
}

ScriptLua::ScriptLua(const std::string path, const eng::IResource* resource) {
	m_pL = luaL_newstate();

	luaL_openlibs(m_pL);

	const std::vector<unsigned char> buffer = resource->getFileResource(path);
	const std::string source{buffer.begin(), buffer.end()};

	loadAPI();

	if (luaL_loadstring(m_pL, source.c_str()) || lua_pcall(m_pL, 0, 0, 0)) {
		std::string luaErrorInfo(lua_tostring(m_pL, -1));
		std::replace(luaErrorInfo.begin(), luaErrorInfo.end(), '"', ' ');
		std::cerr << luaErrorInfo << std::endl;
		const std::string exceptionInfo = "================================================\nFile: '" + path + "': \n" + luaErrorInfo + "\n================================================";
		throw LuaRunException(exceptionInfo);
	}

	std::cout << "Script loaded: " << path << std::endl;
}

lua_State* ScriptLua::getState() { return m_pL; }

void ScriptLua::loadAPI() { 

	bindVec3(m_pL);
	bindTransform(m_pL);

	bindApi(m_pL);
	bindSceneApi(m_pL);


}
