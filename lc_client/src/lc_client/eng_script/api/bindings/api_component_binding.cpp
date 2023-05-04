#include "lc_client/eng_script/api/bindings/api_component_binding.h"

#include <LuaBridge/LuaBridge.h>

#include "lc_client/eng_scene/entt/components.h"


using namespace luabridge;


void bindTransform(lua_State* L) { 

	getGlobalNamespace(L)
		.beginNamespace("components")
		.beginClass<Transform>("Transform")
		.addProperty("position", &Transform::position)
		.addProperty("scale", &Transform::scale)
		.endClass()
		.endNamespace();
}
