#include "lc_client/eng_script/api/bindings/api_component_binding.h"

#include <functional>

#include <LuaBridge/LuaBridge.h>

#include "lc_client/eng_scene/entt/components.h"
#include "lc_client/eng_script/api/helpers/glm_helpers.h"
#include "lc_client/eng_script/api/helpers/components.h"
#include "lc_client/eng_lighting/entt/components.h"


using namespace luabridge;


#include "api_binding.h"

#include "lc_client/eng_script/api/api.h"
#include "lc_client/eng_script/api/api_scene.h"


using namespace luabridge;

void bindRegistryHelper(lua_State* L) {
	getGlobalNamespace(L)
		.beginNamespace("ldk")
		.beginClass<RegistryHelper>("Registry")
		.addFunction("requestModel", &RegistryHelper::requestModel)
		.addFunction("addTransform", &RegistryHelper::addTransform)
		.addFunction("getTransform", &RegistryHelper::getTransform)
		.addFunction("addPointLight", &RegistryHelper::addPointLight)
		.endClass()
		.endNamespace();
}
