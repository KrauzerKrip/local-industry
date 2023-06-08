#include "script_system.h"

#include <lua.hpp>
#include <LuaBridge/LuaBridge.h>

#include "entt/components.h"

using namespace luabridge;


std::string ScriptSystem::m_currentId;

ScriptSystem::ScriptSystem(entt::registry* pRegistry) : m_api() {
	m_pRegistry = pRegistry;
}

void ScriptSystem::update() {
	auto uninitedEntities = m_pRegistry->view<Script, Init, Properties>();

	for (auto entity : uninitedEntities) {
		
		Script& script = uninitedEntities.get<Script>(entity);
		lua_State* L = script.luaState;

		auto ent = entt::entt_traits<entt::entity>::to_integral(entity);

		LuaRef init = getGlobal(L, "init");
		LuaRef upd = getGlobal(L, "update");

		ScriptSystem::m_currentId = uninitedEntities.get<Properties>(entity).id;

		try {
			init(ent, &m_api);
		}
		catch (LuaException& exception) {
			std::cerr << exception.what() << std::endl;
		}

		m_pRegistry->erase<Init>(entity);
	}

	auto entities = m_pRegistry->view<Script, Properties>();

	for (auto entity : entities) {
		Script& script = entities.get<Script>(entity);
		lua_State* L = script.luaState;

		ScriptSystem::m_currentId = entities.get<Properties>(entity).id;
		Tier0::getIConsole()->devMessage("SCRIPT_SYSTEM: current script: " + script.path);

		LuaRef update = getGlobal(L, "update");
		update();
	}

}

void ScriptSystem::frame() {

	auto entities = m_pRegistry->view<Script>(entt::exclude<Init>);

	for (auto entity : entities) {
		Script script = entities.get<Script>(entity);
		lua_State* L = script.luaState;

		LuaRef frame = getGlobal(L, "frame");
		frame();
	}
}
