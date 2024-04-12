#pragma once

#include "game/loader_fabric/loader_fabric.h"

#include "lc_client/util/i_eng_resource.h"
#include "lc_client/eng_graphics/shader_manager.h"
#include "lc_client/tier0/console/i_console.h"
#include "lc_client/eng_graphics/openGL/gl_mesh_loader.h"
#include "lc_client/eng_graphics/openGL/gl_shader_loader.h"
#include "lc_client/eng_cubemaps/openGL/gl_cubemap_loader.h"


class LoaderFabricGl : public LoaderFabric {
public:
	LoaderFabricGl(eng::IResource* pResource, IConsole* pConsole);

	MeshLoader* getMeshLoader();
	ShaderLoader* getShaderLoader();
	CubemapLoader* getCubemapLoader();
	MeshLoaderGl* getMeshLoaderGl();
	ShaderLoaderGl* getShaderLoaderGl();
	CubemapLoaderGl* getCubemapLoaderGl();

private: 
	MeshLoaderGl* m_pMeshLoader = nullptr;
	ShaderLoaderGl* m_pShaderLoader = nullptr;
	CubemapLoaderGl* m_pCubemapLoader = nullptr;
};
