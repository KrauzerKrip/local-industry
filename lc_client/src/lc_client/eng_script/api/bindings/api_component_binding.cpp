#include "lc_client/eng_script/api/bindings/api_component_binding.h"

#include <functional>

#include <LuaBridge/LuaBridge.h>

#include "lc_client/eng_scene/entt/components.h"
#include "lc_client/eng_script/api/helpers/glm_helpers.h"
#include "lc_client/eng_lighting/entt/components.h"


using namespace luabridge;


void bindTransform(lua_State* L) { 
	getGlobalNamespace(L)
		.beginNamespace("ldk")
		.beginNamespace("components")
		.beginClass<Transform>("Transform")
		.addFunction("getPosition", &Transform::getPosition)
		.addFunction("setPosition", &Transform::setPosition)
		.addFunction("getScale", &Transform::getScale)
		.addFunction("setScale", &Transform::setScale)
		.endClass()
		.endNamespace()
		.endNamespace();
}

void bindPointLight(lua_State* L) {
	getGlobalNamespace(L)
		.beginNamespace("ldk")
		.beginNamespace("components")
		.beginClass<PointLight>("PointLight")
		.addFunction("setColor", &PointLight::setColor)
		.endClass()
		.endNamespace()
		.endNamespace();
}

