#include "script_system.h"

#include <lua.hpp>
#include <LuaBridge/LuaBridge.h>

#include "entt/components.h"

using namespace luabridge;


ScriptSystem::ScriptSystem(entt::registry* pRegistry) { m_pRegistry = pRegistry; }

void ScriptSystem::update() {

	auto uninitedEntities = m_pRegistry->view<Script, Init>();

	for (auto entity : uninitedEntities) {
		
		Script script = uninitedEntities.get<Script>(entity);
		lua_State* L = script.luaState;

		auto ent = entt::entt_traits<entt::entity>::to_integral(entity);

		LuaRef init = getGlobal(L, "init");
		LuaRef upd = getGlobal(L, "update");
		try {
			init(ent);
		}
		catch (LuaException& exception) {
			std::cerr << exception.what() << std::endl;
		}

		m_pRegistry->erase<Init>(entity);
	}

	auto entities = m_pRegistry->view<Script>();

	for (auto entity : entities) {
		Script script = entities.get<Script>(entity);
		lua_State* L = script.luaState;

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
