#pragma once

#include "lc_client/eng_graphics/graphics_entities_util.h"
#include "api_scene.h"


class Api {
public:
	Api(GraphicsEntitiesUtil* pGraphicsEntitiesUtil);
	~Api() = default;

	SceneApi& getSceneApi();

private:
	SceneApi m_sceneApi;
};