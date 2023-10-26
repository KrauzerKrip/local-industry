#include "ldk_client/local_engine/scene_controlling.h"

void SceneControlling::loadScene(std::string pack, std::string scene) {
	m_pScene->loadScene(pack, scene);
}

Scene* SceneControlling::getScene() {
	return m_pScene;  
}

Scene* SceneControlling::m_pScene = nullptr;

