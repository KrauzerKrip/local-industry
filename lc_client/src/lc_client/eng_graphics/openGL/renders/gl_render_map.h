#pragma once

#include <entt/entt.hpp>
#include "lc_client/eng_graphics/openGL/gl_render.h"
#include "lc_client/eng_graphics/openGL/renders/gl_lighting.h"

class RenderGL;

class RenderMapGl {
public:
	RenderMapGl(LightingGl* pLighting, RenderGL* pRenderGl, Camera* pCamera, entt::registry* pMapRegistry,
		entt::registry* pUtilRegistry);

	void render(glm::mat4 view, glm::mat4 projection);

private:
	entt::registry* m_pMapRegistry;
	entt::registry* m_pUtilRegistry;

	RenderGL* m_pRenderGl = nullptr;
	LightingGl* m_pLighting = nullptr;
	Camera* m_pCamera = nullptr;
};
