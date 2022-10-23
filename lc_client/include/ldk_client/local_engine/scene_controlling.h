#pragma once

#include "lc_client/eng_scene/scene.h"
 
class SceneControlling {
public:
	static void loadScene(std::string name);
	static Scene* getScene();

private:
	static Scene* m_pScene;
};
