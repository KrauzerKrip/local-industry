#pragma once

#include "tier0/tier0.h"
#include "tier1/tier1.h"
#include "eng_graphics/shader_loader.h"
#include "eng_graphics/mesh_loader.h"
#include "eng_cubemaps/cubemap_loader.h"
#include "eng_scene/scene.h"
#include "eng_model/model_manager.h"
#include "eng_map/map.h"

#include "eng_graphics/shader_system.h"
#include "eng_graphics/material_system.h"
#include "eng_model/model_system.h"
#include "eng_script/script_system.h"
#include "eng_cubemaps/cubemap_system.h"
#include "eng_physics/physics_system.h"


class Systems {
public:
	Systems(Tier0* pTier0, Tier1* pTier1, ShaderLoader* pShaderWork, MeshLoader* pMeshWork, CubemapLoader* pCubemapWork, Scene* pScene, Map* pMap, ModelManager* pModelManager);

	void update();
	void frame();

private:
	Tier1* m_pTier1 = nullptr;
	ShaderLoader* m_pShaderWork = nullptr;
	MeshLoader* m_pMeshWork = nullptr;
	CubemapLoader* m_pCubemapWork = nullptr;
	Scene* m_pScene = nullptr;
	ModelManager* m_pModelManager = nullptr;

	ShaderSystem* m_pShaderSystem = nullptr;
	ShaderSystem* m_pShaderSystemMap = nullptr;
	MaterialSystem* m_pMaterialSystem = nullptr;
	MaterialSystem* m_pMaterialSystemMap = nullptr;
	ModelSystem* m_pModelSystem = nullptr;
	ModelSystem* m_pModelSystemMap = nullptr;
	ScriptSystem* m_pScriptSystem = nullptr;
	CubemapSystem* m_pCubemapSystem = nullptr;
	PhysicsSystem* m_pPhysicsSystem = nullptr;

};
