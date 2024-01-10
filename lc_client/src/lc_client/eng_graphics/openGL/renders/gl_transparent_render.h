#pragma once

#include <entt/entt.hpp>
#include <glm/glm.hpp>

#include "lc_client/eng_graphics/camera/camera.h"


class TransparentRenderGl {
public:
	TransparentRenderGl(Camera* pCamera, entt::registry* pRegistry, entt::registry* pUtilRegistry);

	void render(glm::mat4 projection, glm::mat4 view);

private:
	entt::registry* m_pRegistry = nullptr;
	entt::registry* m_pUtilRegistry = nullptr;

	Camera* m_pCamera = nullptr;
};