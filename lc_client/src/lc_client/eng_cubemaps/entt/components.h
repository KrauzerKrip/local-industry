#pragma once

#include <string>


struct Cubemap {
	entt::entity cubemap;
};

struct CubemapReflection {
    
};

struct AssignedCubemap {
	entt::entity cubemap;
};

struct CubemapLoadRequest {
	std::string path;
};

struct CubemapUnloadRequest {};

struct CubemapGl {
	unsigned int textureId;
};

