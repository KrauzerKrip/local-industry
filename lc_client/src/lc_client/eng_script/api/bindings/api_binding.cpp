#include "api_binding.h"

#include "lc_client/eng_script/api/api.h"
#include "lc_client/eng_script/api/api_scene.h"


using namespace luabridge;


void bindApi(lua_State* L) {
	getGlobalNamespace(L)
		.beginNamespace("ldk")
		.beginClass<Api>("Api")
		.addFunction("getSceneApi", &Api::getSceneApi)
		.endClass()
		.endNamespace();
}

void bindSceneApi(lua_State* L) {
	getGlobalNamespace(L)
		.beginNamespace("ldk")
		.beginClass<SceneApi>("SceneApi")
		.addFunction("getRegistry", &SceneApi::getRegistry)
		.endClass()
		.endNamespace();
}
