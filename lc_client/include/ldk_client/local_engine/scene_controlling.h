#pragma once

#include "lc_client/eng_scene/scene.h"
#include "lc_client/tier1/i_shaders.h"
 
class SceneControlling {
public:
	static void loadScene(std::string pack, std::string scene);
	static Scene* getScene();

	/**
	 * temporary
	 */
	static void setScene(Scene* pScene) { m_pScene = pScene; };

private:
	static Scene* m_pScene;
	static IShaderManager* m_pShaderManager;
};
