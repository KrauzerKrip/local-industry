#pragma once

#include <string>

#include <entt/entt.hpp>


class SceneLoading {
	SceneLoading(entt::registry& sceneRegistry, entt::registry& mapRegistry);
	~SceneLoading();

	void loadScene(std::string path);

	entt::registry* m_pSceneRegistry;
	entt::registry* m_pMapRegistry;
};
