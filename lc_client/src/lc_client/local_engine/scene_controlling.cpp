#include "ldk_client/local_engine/scene_controlling.h"

void SceneControlling::loadScene(std::string name) {
	m_pScene = new Scene(name); // mb memory leak
}

Scene* SceneControlling::getScene() {
	return m_pScene;  
}


