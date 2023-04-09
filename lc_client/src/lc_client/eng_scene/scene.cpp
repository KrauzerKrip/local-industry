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


Scene::Scene() {
	m_mapRegistry = entt::registry();
	m_sceneRegistry = entt::registry();
	m_utilRegistry = entt::registry();
	m_pSceneLoading = new SceneLoading(m_sceneRegistry, m_mapRegistry, m_pResource);
}

Scene::~Scene() { delete m_pSceneLoading; }

void Scene::loadScene(std::string name) {



	m_name = name;

	if (m_pShaderManager == nullptr) {
		std::cerr << "NullPointerException: m_pShaderManager wasn`t initialized." << std::endl;
		throw std::runtime_error("NullPointerException: m_pShaderManager wasn`t initialized.");
	}

	m_mapRegistry.clear();
	m_sceneRegistry.clear();
	m_utilRegistry.clear();

	Pack::loadPack("dev", "dev/pack.json", m_pResource);

	auto entity = m_sceneRegistry.create();
	m_sceneRegistry.emplace<Properties>(entity, "test_uuid", "test_id");
	ModelData& modelData = m_sceneRegistry.emplace<ModelData>(entity);
	modelData.modelName = "test_model";
	modelData.packName = "dev";

	Transform& transform = m_sceneRegistry.emplace<Transform>(entity);
	transform.position = glm::vec3(0.0f, 0.0f, -5.0f);
	transform.rotation = glm::vec3(1.0f, 0.0f, 0.0f);
	transform.scale = glm::vec3(10.0f, 10.0f, 10.0f);

	m_pGraphicsEntitiesLoading->loadMapEntities();
	m_pGraphicsEntitiesLoading->loadSceneEntities();
}

void Scene::setDependencies(SceneDependencies& sceneDependencies) {
	m_pShaderManager = sceneDependencies.pShaderManager;
	m_pResource = sceneDependencies.pResource;
	m_pGraphicsEntitiesLoading = sceneDependencies.pGraphicsEntitiesLoading;
}


entt::registry& Scene::getMapRegistry() { return m_mapRegistry; }

entt::registry& Scene::getSceneRegistry() { return m_sceneRegistry; }

entt::registry& Scene::getUtilRegistry() { return m_utilRegistry; }