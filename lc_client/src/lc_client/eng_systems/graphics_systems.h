#pragma once

#include "lc_client/tier0/tier0.h"
#include "lc_client/tier1/tier1.h"
#include "lc_client/eng_graphics/shader_loader.h"
#include "lc_client/eng_graphics/mesh_loader.h"
#include "lc_client/eng_cubemaps/cubemap_loader.h"
#include "lc_client/eng_world/world.h"
#include "lc_client/eng_model/model_manager.h"
#include "lc_client/eng_world/world.h"
#include "lc_client/eng_model/model_parser.h"

#include "lc_client/eng_graphics/shader_system.h"
#include "lc_client/eng_graphics/material_system.h"
#include "lc_client/eng_model/model_system.h"
#include "lc_client/eng_script/script_system.h"
#include "lc_client/eng_cubemaps/cubemap_system.h"
#include "lc_client/eng_physics/physics_system.h"


class GraphicsSystems {
public:
	GraphicsSystems(Tier0* pTier0, Tier1* pTier1, ShaderLoader* pShaderWork, MeshLoader* pMeshWork,
		CubemapLoader* pCubemapWork,
		World* pWorld, ModelManager* pModelManager, ModelParser* pModelParser);

	void update();
	void frame();

private:
	ShaderSystem* m_pShaderSystem = nullptr;
	MaterialSystem* m_pMaterialSystem = nullptr;
	ModelSystem* m_pModelSystem = nullptr;
	CubemapSystem* m_pCubemapSystem = nullptr;
};