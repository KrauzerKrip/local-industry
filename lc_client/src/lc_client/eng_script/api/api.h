#pragma once

#include "api_scene.h"


class Api {
public:
	Api();
	~Api() = default;

	SceneApi& getSceneApi();

private:
	SceneApi m_sceneApi;
};