#include "scene.h"

#include <iostream>
#include <stdexcept>

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "lc_client/eng_graphics/entt/components.h"
#include "lc_client/eng_scene/entt/components.h"


Scene::Scene() {
	m_mapRegistry = entt::registry();
	m_sceneRegistry = entt::registry();
}

Scene::~Scene() {}

void Scene::loadScene(std::string name) {

	m_name = name;

	if (m_pShaderManager == nullptr) {
		std::cout << "NullPointerException: m_pShaderManager wasn`t initialized." << std::endl;
		throw std::runtime_error("NullPointerException: m_pShaderManager wasn`t initialized.");
	}
	
	m_mapRegistry.clear();
	m_sceneRegistry.clear();

	auto entt = m_sceneRegistry.create();
	m_sceneRegistry.emplace<Properties>(entt, "test_uuid", "test_id");
	m_sceneRegistry.emplace<ModelData>(entt, "test_modelId", "base", "base");

	m_pGraphicsEntitiesLoading->loadMapEntities(getMapRegistry());
	m_pGraphicsEntitiesLoading->loadSceneEntities(getSceneRegistry());
}

void Scene::setDependencies(SceneDependencies& sceneDependencies) {
	m_pShaderManager = sceneDependencies.pShaderManager;
	m_pGraphicsEntitiesLoading = sceneDependencies.pGraphicsEntitiesLoading;
}


entt::registry* Scene::getMapRegistry() {
	return &m_mapRegistry;
}

entt::registry* Scene::getSceneRegistry() {
	return &m_sceneRegistry;
}