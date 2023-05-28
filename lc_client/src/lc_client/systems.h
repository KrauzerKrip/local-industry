#pragma once

#include "tier1/tier1.h"
#include "eng_graphics/shader_work.h"
#include "eng_graphics/mesh_work.h"
#include "eng_scene/scene.h"
#include "eng_model/model_manager.h"

#include "eng_graphics/shader_system.h"
#include "eng_graphics/material_system.h"
#include "eng_model/model_system.h"
#include "eng_script/script_system.h"


class Systems {
public:
	Systems(Tier1* pTier1, ShaderWork* pShaderWork, MeshWork* pMeshWork, Scene* pScene, ModelManager* pModelManager);

	void update();
	void frame();

private:
	Tier1* m_pTier1 = nullptr;
	ShaderWork* m_pShaderWork = nullptr;
	MeshWork* m_pMeshWork = nullptr;
	Scene* m_pScene = nullptr;
	ModelManager* m_pModelManager = nullptr;

	ShaderSystem* m_pShaderSystem = nullptr;
	MaterialSystem* m_pMaterialSystem = nullptr;
	ModelSystem* m_pModelSystem = nullptr;
	ScriptSystem* m_pScriptSystem = nullptr;
};
