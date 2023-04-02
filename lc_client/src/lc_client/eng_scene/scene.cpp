#include "scene.h"

#include <iostream>
#include <stdexcept>

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/vec3.hpp>

#include "lc_client/eng_graphics/entt/components.h"
#include "lc_client/eng_scene/entt/components.h"


Scene::Scene() {
	m_mapRegistry = entt::registry();
	m_sceneRegistry = entt::registry();
	m_utilRegistry = entt::registry();
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
	m_utilRegistry.clear();

	auto entity = m_sceneRegistry.create();
	m_sceneRegistry.emplace<Properties>(entity, "test_uuid", "test_id");
	MeshData& modelData = m_sceneRegistry.emplace<MeshData>(entity);
	modelData.id = "test_modelId";
	modelData.path = "test_modelDir/test_model";
	modelData.vertexShader = "base";
	modelData.fragmentShader = "base";
	//modelData.colorTexture =    "dev/textures/loli/color";
	//modelData.aoTexture =       "dev/textures/loli/none";
	//modelData.metallicTexture = "dev/textures/loli/none";
	//modelData.normalMap =       "dev/textures/loli/normal";

	Transform& transform = m_sceneRegistry.emplace<Transform>(entity);
	transform.position = glm::vec3(0.0f, 0.0f, -5.0f);
	transform.rotation = glm::vec3(1.0f, 0.0f, 0.0f);
	transform.scale = glm::vec3(1.0f, 1.0f, 1.0f);

	m_pGraphicsEntitiesLoading->loadMapEntities();
	m_pGraphicsEntitiesLoading->loadSceneEntities();
}

void Scene::setDependencies(SceneDependencies& sceneDependencies) {
	m_pShaderManager = sceneDependencies.pShaderManager;
	m_pResource = sceneDependencies.pResource;
	m_pGraphicsEntitiesLoading = sceneDependencies.pGraphicsEntitiesLoading;
}


entt::registry* Scene::getMapRegistry() {
	return &m_mapRegistry;
}

entt::registry* Scene::getSceneRegistry() {
	return &m_sceneRegistry;
}

entt::registry* Scene::getUtil Registry() {
	return &m_utilRegistry;
}