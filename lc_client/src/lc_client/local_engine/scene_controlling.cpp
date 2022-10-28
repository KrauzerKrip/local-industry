#include "ldk_client/local_engine/scene_controlling.h"

void SceneControlling::loadScene(std::string name) {
	m_pScene->loadScene(name);
}

Scene* SceneControlling::getScene() {
	return m_pScene;  
}

Scene* SceneControlling::m_pScene = new Scene();

