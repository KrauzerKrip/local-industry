#pragma once

#include "api_scene.h"


class Api {
public:
	Api(entt::registry* pSceneRegistry) : m_sceneApi(pSceneRegistry){};
	~Api() = default;

	SceneApi& getSceneApi();

private:
	SceneApi m_sceneApi;
};