#include "scene_loading.h"

SceneLoading::SceneLoading(entt::registry& sceneRegistry, entt::registry& mapRegistry) {
	m_pSceneRegistry = &sceneRegistry;
	m_pMapRegistry = &mapRegistry;
}

SceneLoading::~SceneLoading(){

}

void SceneLoading::loadScene(std::string path) {

}

