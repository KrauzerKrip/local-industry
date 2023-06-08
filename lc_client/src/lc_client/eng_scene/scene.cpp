#include "scene.h"
#include "scene.h"
#include "scene.h"

#include <iostream>
#include <stdexcept>

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/vec3.hpp>

#include "lc_client/eng_graphics/entt/components.h"
#include "lc_client/eng_scene/entt/components.h"
#include "entt/components.h"
#include "lc_client/util/pack.h"
#include "lc_client/eng_cubemaps/entt/components.h"
#include "lc_client/tier0/tier0.h"


Scene::Scene() {
	m_mapRegistry = entt::registry();
	m_sceneRegistry = entt::registry();
	m_utilRegistry = entt::registry();
}

Scene::~Scene() {
	delete m_pSceneLoading;
}

void Scene::loadScene(std::string pack, std::string scene) {

	m_name = scene;
	m_pack = pack;

	if (m_pShaderManager == nullptr) {
		std::cerr << "NullPointerException: m_pShaderManager wasn`t initialized." << std::endl;
		throw std::runtime_error("NullPointerException: m_pShaderManager wasn`t initialized.");
	}

	m_mapRegistry.clear();
	m_sceneRegistry.clear();
	m_utilRegistry.clear();

	m_pSceneLoading->loadScene(pack + "/scenes/" + scene + "/scene.xml");

	auto view = m_sceneRegistry.view<Properties>();
	for (auto& ent : view) {
		if (view.get<Properties>(ent).id == "cube_water") {
			m_sceneRegistry.emplace<Water>(ent);
		}
	}

	auto view2 = m_sceneRegistry.view<Properties, Transform>();
	for (auto& ent : view2) {
		if (view.get<Properties>(ent).id == "cube") {

			Transform& transform = view2.get<Transform>(ent);

			std::string id = view2.get<Properties>(ent).id;
			long iPtr = (long)&transform;
			std::string str = std::to_string(iPtr);
			Tier0::getIConsole()->devMessage("Transform ptr scene: " + id + " " + str);
		}
	}

	entt::entity cubemap = m_sceneRegistry.create();

	m_sceneRegistry.emplace<CubemapLoadRequest>(cubemap, "dev/textures/test_cubemap/");
	Transform transform;
	transform.position = glm::vec3(0, 0, 0);
	m_sceneRegistry.emplace<Transform>(cubemap, transform);

	m_pGraphicsEntitiesLoading->loadMapEntities();
	m_pGraphicsEntitiesLoading->loadSceneEntities();
}

void Scene::setDependencies(SceneDependencies& sceneDependencies) {
	m_pShaderManager = sceneDependencies.pShaderManager;
	m_pResource = sceneDependencies.pResource;
	m_pGraphicsEntitiesLoading = sceneDependencies.pGraphicsEntitiesLoading;

	m_pSceneLoading = new SceneLoading(m_sceneRegistry, m_mapRegistry, m_pResource);
}


entt::registry& Scene::getMapRegistry() { return m_mapRegistry; }

entt::registry& Scene::getSceneRegistry() { return m_sceneRegistry; }

entt::registry& Scene::getUtilRegistry() { return m_utilRegistry; }

Skybox* Scene::getSkybox() { return m_pSkybox; }

void Scene::setSkybox(Skybox* pSkybox) { m_pSkybox = pSkybox; }
