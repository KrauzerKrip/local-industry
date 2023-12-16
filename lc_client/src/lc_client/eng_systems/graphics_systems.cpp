#include "graphics_systems.h"

GraphicsSystems::GraphicsSystems(Tier0* pTier0, Tier1* pTier1, ShaderLoader* pShaderWork, MeshLoader* pMeshWork,
	CubemapLoader* pCubemapWork, World* pWorld, ModelManager* pModelManager) {
	
		m_pShaderSystem = new ShaderSystem(pShaderWork, &pWorld->getRegistry());
	m_pShaderSystemMap = new ShaderSystem(pShaderWork, &pWorld->getRegistry());
	m_pMaterialSystem = new MaterialSystem(&pWorld->getUtilRegistry());
	m_pMaterialSystemMap = new MaterialSystem(&pWorld->getUtilRegistry());
	m_pModelSystem = new ModelSystem(pModelManager, pMeshWork, &pWorld->getRegistry(), &pWorld->getUtilRegistry());
	m_pModelSystemMap = new ModelSystem(pModelManager, pMeshWork, &pWorld->getRegistry(), &pWorld->getUtilRegistry());
	m_pCubemapSystem = new CubemapSystem(&pWorld->getRegistry(), pCubemapWork);
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
