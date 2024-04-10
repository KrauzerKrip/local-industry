#pragma once

#include <entt/entt.hpp>
#include <glm/glm.hpp>

#include "lc_client/eng_graphics/camera/camera.h"
#include "gl_mesh_render.h"
#include "gl_outline_render.h"
#include "gl_lighting.h"
#include "lc_client/eng_graphics/openGL/gl_skybox_render.h"


class OpaqueRenderGl {
public:
	OpaqueRenderGl(Camera* pCamera, MeshRenderGl* pMeshRenderGl, OutlineRenderGl* pOutlineRender, LightingGl* pLighting,
		SkyboxRenderGl* pSkyboxRender, entt::registry* pRegistry, entt::registry* pUtilRegistry);

	void render(const glm::mat4& projection, const glm::mat4& view);

private:
	entt::registry* m_pRegistry = nullptr;
	entt::registry* m_pUtilRegistry = nullptr;

	Camera* m_pCamera = nullptr;
	MeshRenderGl* m_pMeshRender = nullptr;
	OutlineRenderGl* m_pOutlineRender = nullptr;
	LightingGl* m_pLighting = nullptr;
	SkyboxRenderGl* m_pSkyboxRender = nullptr;
};