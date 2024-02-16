#pragma once

#include <entt/entt.hpp>
#include <glm/glm.hpp>

#include "lc_client/eng_graphics/camera/camera.h"
#include "gl_mesh_render.h"
#include "gl_outline_render.h"
#include "gl_lighting.h"
#include "lc_client/eng_scene/skybox.h"


class OpaqueRenderGl {
public:
	OpaqueRenderGl(
		Camera* pCamera, MeshRenderGl* pMeshRenderGl, OutlineRenderGl* pOutlineRender, LightingGl* pLighting, Skybox* pSkybox, entt::registry* pRegistry, entt::registry* pUtilRegistry);

	void render(const glm::mat4& projection, const glm::mat4& view);

private:
	entt::registry* m_pRegistry = nullptr;
	entt::registry* m_pUtilRegistry = nullptr;

	Camera* m_pCamera = nullptr;
	MeshRenderGl* m_pMeshRender = nullptr;
	OutlineRenderGl* m_pOutlineRender = nullptr;
	LightingGl* m_pLighting = nullptr;
	Skybox* m_pSkybox = nullptr;
};