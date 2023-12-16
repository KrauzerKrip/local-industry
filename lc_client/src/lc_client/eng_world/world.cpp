#include "world.h"

#include "lc_client/eng_map/entt/components.h"



World::World(eng::IResource* pResource, SceneLoading* pSceneLoading, SkyboxRender* pSkyboxRender) { 
	m_pResource = pResource;
	m_pSceneLoading = pSceneLoading;
	m_pSkybox = new Skybox(pSkyboxRender, pResource);
}

World::~World() {}

void World::loadScene(std::string pack, std::string scene) {
	m_registry.each([this](entt::entity entity) {
		if (!m_registry.all_of<MapEntity>(entity)) {
			m_registry.destroy(entity);
		}
		}); 
	m_utilRegistry.each([this](entt::entity entity) {
		if (!m_utilRegistry.all_of<MapEntity>(entity)) {
			m_utilRegistry.destroy(entity);
		}
	}); 


	m_pSceneLoading->loadScene(pack + "/scenes/" + scene + "/scene.xml", m_registry);
}

void World::loadMap(std::string pack, std::string map) {
	m_registry.clear();
	m_utilRegistry.clear();
}

entt::registry& World::getRegistry() { return m_registry; }

entt::registry& World::getUtilRegistry() { return m_utilRegistry; }

Skybox* World::getSkybox() { return m_pSkybox; }
