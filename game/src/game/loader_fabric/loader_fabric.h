#pragma once

#include "lc_client/eng_graphics/mesh_loader.h"
#include "lc_client/eng_graphics/shader_loader.h"
#include "lc_client/eng_cubemaps/cubemap_loader.h"


class LoaderFabric {
public:
	virtual ~LoaderFabric(){};
	
	virtual MeshLoader* getMeshLoader() = 0;
	virtual ShaderLoader* getShaderLoader() = 0;
	virtual CubemapLoader* getCubemapLoader() = 0;
};
