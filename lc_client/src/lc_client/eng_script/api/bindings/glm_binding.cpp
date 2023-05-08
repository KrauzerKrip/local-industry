#include "glm_binding.h"

#include <iostream>

#include "lc_client/eng_script/api/helpers/glm_helpers.h"


void bindVec3(lua_State* L) {
	getGlobalNamespace(L).
		beginNamespace("glm")
		.beginClass<Vec3fHelper>("vec3f")
		.addFunction("x", &Vec3fHelper::x)
		.addFunction("y", &Vec3fHelper::y)
		.addFunction("z", &Vec3fHelper::z)
		.addFunction("setX", &Vec3fHelper::setX)
		.addFunction("setY", &Vec3fHelper::setY)
		.addFunction("setZ", &Vec3fHelper::setZ)
		.addFunction("setXYZ", &Vec3fHelper::setXYZ)
		.endClass()
		.endNamespace(); 
}
