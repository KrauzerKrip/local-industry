#pragma once

#include "lc_client/tier0/tier0.h"
#include "lc_client/eng_graphics/shader_loader.h"
#include "lc_client/eng_graphics/mesh_loader.h"
#include "lc_client/eng_cubemaps/cubemap_loader.h"
#include "lc_client/eng_world/world.h"
#include "lc_client/eng_model/model_manager.h"
#include "lc_client/eng_world/world.h"
#include "lc_client/eng_model/model_parser.h"
#include "lc_client/eng_graphics/skybox_render.h"
#include "lc_client/eng_graphics/shader_manager.h"
#include "lc_client/eng_graphics/texture_manager.h"

#include "lc_client/eng_graphics/shader_system.h"
#include "lc_client/eng_model/material_system.h"
#include "lc_client/eng_model/model_system.h"
#include "lc_client/eng_script/script_system.h"
#include "lc_client/eng_cubemaps/cubemap_system.h"
#include "lc_client/eng_physics/physics_system.h"
#include "lc_client/eng_scene/skybox_system.h"


class GraphicsSystems {
public:
	GraphicsSystems(Tier0* pTier0, ShaderManager* pShaderManager, TextureManager* pTextureManager, ShaderLoader* pShaderWork, MeshLoader* pMeshWork,
		CubemapLoader* pCubemapWork,
		World* pWorld, ModelManager* pModelManager, ModelParser* pModelParser, SkyboxRender* pSkyboxRender, eng::IResource* pResource);

	void update();
	void frame();

private:
	ShaderSystem* m_pShaderSystem = nullptr;
	MaterialSystem* m_pMaterialSystem = nullptr;
	ModelSystem* m_pModelSystem = nullptr;
	CubemapSystem* m_pCubemapSystem = nullptr;
	SkyboxSystem* m_pSkyboxSystem = nullptr;
};