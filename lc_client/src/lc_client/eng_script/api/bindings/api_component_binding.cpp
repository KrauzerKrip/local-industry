#include "lc_client/eng_script/api/bindings/api_component_binding.h"

#include <functional>

#include <LuaBridge/LuaBridge.h>

#include "lc_client/eng_scene/entt/components.h"
#include "lc_client/eng_script/api/helpers/glm_helpers.h"
#include "lc_client/eng_script/api/helpers/components.h"


using namespace luabridge;


void bindTransform(lua_State* L) { 
	getGlobalNamespace(L)
		.beginNamespace("ldk")
		.beginNamespace("components")
		.beginClass<TransformHelper>("Transform")
		.addFunction("getPosition", &TransformHelper::getPosition)
		.addFunction("setPosition", &TransformHelper::setPosition)
		.addFunction("getScale", &TransformHelper::getScale)
		.addFunction("setScale", &TransformHelper::setScale)
		.endClass()
		.endNamespace()
		.endNamespace();
}

