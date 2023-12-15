#include "graphics_systems.h"

GraphicsSystems::GraphicsSystems(Tier0* pTier0, Tier1* pTier1, ShaderLoader* pShaderWork, MeshLoader* pMeshWork,
	CubemapLoader* pCubemapWork, Scene* pScene, Map* pMap, ModelManager* pModelManager) {
	
		m_pShaderSystem = new ShaderSystem(pShaderWork, &pScene->getSceneRegistry());
	m_pShaderSystemMap = new ShaderSystem(pShaderWork, &pMap->getRegistry());
	m_pMaterialSystem = new MaterialSystem(&pScene->getUtilRegistry());
	m_pMaterialSystemMap = new MaterialSystem(&pMap->getUtilRegistry());
	m_pModelSystem = new ModelSystem(pModelManager, pMeshWork, &pScene->getSceneRegistry(), &pScene->getUtilRegistry());
	m_pModelSystemMap = new ModelSystem(pModelManager, pMeshWork, &pMap->getRegistry(), &pMap->getUtilRegistry());
	m_pCubemapSystem = new CubemapSystem(&pMap->getRegistry(), pCubemapWork);
}

void GraphicsSystems::update() {
	m_pModelSystem->update();
	m_pCubemapSystem->update();
	m_pModelSystemMap->update();
	m_pModelSystem->update();
	m_pMaterialSystemMap->loadMaterials();
	m_pMaterialSystemMap->unloadMaterials();
	m_pMaterialSystem->loadMaterials();
	m_pMaterialSystem->unloadMaterials();
	m_pShaderSystem->update();
	m_pShaderSystemMap->update();
}

void GraphicsSystems::frame() {}
