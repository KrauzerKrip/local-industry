#include "glm_binding.h"

#include <iostream>


void bindVec3(lua_State* L) {
	std::cout << "bind vec3 start" << std::endl;
	getGlobalNamespace(L).beginNamespace("glm").beginClass<glm::vec3>("vec3").endClass().endNamespace(); 
	std::cout << "bind vec3 finished" << std::endl;
}
