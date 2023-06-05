#pragma once

#include <string>


struct CubemapLoadRequest {
	std::string path;
};

struct CubemapUnloadRequest {};

struct CubemapGl {
	unsigned int textureId;
};
