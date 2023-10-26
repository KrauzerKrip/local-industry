#include "systems.h"

Systems::Systems(Tier1* pTier1, ShaderWork* pShaderWork, MeshWork* pMeshWork, CubemapWork* pCubemapWork, Scene* pScene,
	Map* pMap, ModelManager* pModelManager) {
	m_pTier1 = pTier1;
	m_pShaderWork = pShaderWork;
	m_pMeshWork = pMeshWork;
	m_pCubemapWork = pCubemapWork;
	m_pScene = pScene;
	m_pModelManager = pModelManager;

	m_pShaderSystem = new ShaderSystem(pShaderWork, &pScene->getMapRegistry(), &pScene->getSceneRegistry());
	m_pMaterialSystem = new MaterialSystem(&pScene->getUtilRegistry());
	m_pMaterialSystemMap = new MaterialSystem(&pMap->getUtilRegistry());
	m_pModelSystem = new ModelSystem(pModelManager, pMeshWork, &pScene->getSceneRegistry());
	m_pModelSystemMap = new ModelSystem(pModelManager, pMeshWork, &pMap->getRegistry());
	m_pScriptSystem = new ScriptSystem(&pScene->getSceneRegistry());
	m_pCubemapSystem = new CubemapSystem(&pScene->getSceneRegistry(), pCubemapWork);
}

void Systems::update() {
	m_pScriptSystem->update();
	m_pModelSystem->update();
	m_pCubemapSystem->update();
	m_pModelSystemMap->update();
	m_pModelSystem->update();
	m_pMaterialSystemMap->loadMaterials();
	m_pMaterialSystemMap->unloadMaterials();
	m_pMaterialSystem->loadMaterials();
	m_pMaterialSystem->unloadMaterials();
	m_pShaderSystem->update();
}

void Systems::frame() { m_pScriptSystem->frame(); }
