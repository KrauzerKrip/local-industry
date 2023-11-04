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


Scene::Scene(eng::IResource* pResource, SceneLoading* pSceneLoading) {
	m_mapRegistry = entt::registry();
	m_sceneRegistry = entt::registry();
	m_utilRegistry = entt::registry();
	m_pResource = pResource;
	m_pSceneLoading = pSceneLoading;
}

Scene::~Scene() {
	delete m_pSceneLoading;
}

void Scene::loadScene(std::string pack, std::string scene) {

	m_name = scene;
	m_pack = pack;

	m_mapRegistry.clear();
	m_sceneRegistry.clear();
	m_utilRegistry.clear();

	m_pSceneLoading->loadScene(pack + "/scenes/" + scene + "/scene.xml", m_sceneRegistry);

	auto view = m_sceneRegistry.view<Properties>();
	for (auto& ent : view) {
		if (view.get<Properties>(ent).id == "cube_water") {
			m_sceneRegistry.emplace<Water>(ent);
		}
	}

	entt::entity textShader = m_sceneRegistry.create();
	ShaderRequest request("dev", "text", "text");
	m_sceneRegistry.emplace<ShaderRequest>(textShader, request);
	Properties properties("text_shader", "");
	m_sceneRegistry.emplace<Properties>(textShader, properties);
}

entt::registry& Scene::getMapRegistry() { return m_mapRegistry; }

entt::registry& Scene::getSceneRegistry() { return m_sceneRegistry; }

entt::registry& Scene::getUtilRegistry() { return m_utilRegistry; }

Skybox* Scene::getSkybox() { return m_pSkybox; }

void Scene::setSkybox(Skybox* pSkybox) { m_pSkybox = pSkybox; }
