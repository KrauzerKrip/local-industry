#include "systems.h"

Systems::Systems(Tier1* pTier1, ShaderWork* pShaderWork, MeshWork* pMeshWork, Scene* pScene, ModelManager* pModelManager) {
	m_pTier1 = pTier1;
	m_pShaderWork = pShaderWork;
	m_pMeshWork = pMeshWork;
	m_pScene = pScene;
	m_pModelManager = pModelManager;

	m_pShaderSystem = new ShaderSystem(pShaderWork, &pScene->getMapRegistry(), &pScene->getSceneRegistry());
	m_pMaterialSystem = new MaterialSystem(&pScene->getUtilRegistry());
	m_pModelSystem = new ModelSystem(pModelManager, pMeshWork, &pScene->getSceneRegistry());
	m_pScriptSystem = new ScriptSystem(&pScene->getSceneRegistry());
}

void Systems::update() {
	m_pScriptSystem->update();
	m_pModelSystem->update();
	m_pMaterialSystem->loadMaterials();
	m_pMaterialSystem->unloadMaterials();
	m_pShaderSystem->update();
}

void Systems::frame() { m_pScriptSystem->frame(); }