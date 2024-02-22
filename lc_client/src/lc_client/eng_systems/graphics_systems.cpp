#include "graphics_systems.h"

GraphicsSystems::GraphicsSystems(Tier0* pTier0, Tier1* pTier1, ShaderLoader* pShaderWork, MeshLoader* pMeshWork,
	CubemapLoader* pCubemapWork, World* pWorld, ModelManager* pModelManager, ModelParser* pModelParser) {
	
    m_pShaderSystem = new ShaderSystem(pShaderWork, &pWorld->getRegistry());
	m_pMaterialSystem = new MaterialSystem(&pWorld->getUtilRegistry());
	m_pModelSystem = new ModelSystem(pModelManager, pModelParser, pMeshWork, &pWorld->getRegistry(), &pWorld->getUtilRegistry());
	m_pCubemapSystem = new CubemapSystem(&pWorld->getRegistry(), &pWorld->getUtilRegistry(), pCubemapWork);
}

void GraphicsSystems::update() {
	m_pModelSystem->update();
	m_pCubemapSystem->update();
	m_pModelSystem->update();
	m_pMaterialSystem->loadMaterials();
	m_pMaterialSystem->unloadMaterials();
	m_pShaderSystem->update();
}

void GraphicsSystems::frame() {
    m_pCubemapSystem->frame();
}
