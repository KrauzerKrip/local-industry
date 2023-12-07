#pragma once

#include <entt/entt.hpp>

#include "lc_client/eng_scene/entt/components.h"
#include "lc_client/eng_graphics/camera/camera.h"
#include "lc_client/eng_scene/skybox.h"
#include "lc_client/eng_lighting/entt/components.h"

class LightingGl {
public:
	LightingGl(entt::registry* pMapRegistry, entt::registry* pSceneRegistry, Camera* pCamera, Skybox* pSkybox);

	void setLighting(unsigned int shaderProgram);
	void setPointLight(unsigned int shaderProgram, int number, PointLight& pointLight, Transform& transform);

private:
	entt::registry* m_pMapRegistry;
	entt::registry* m_pSceneRegistry;
	Camera* m_pCamera;
	Skybox* m_pSkybox;
};
