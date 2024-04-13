#pragma once

#include <entt/entt.hpp>
#include <glm/glm.hpp>

#include "gl_mesh_render.h"
#include "lc_client/eng_graphics/openGL/gl_shader_loader.h"
#include "lc_client/eng_model/entt/components.h"

class OutlineRenderGl {
public:
	OutlineRenderGl(MeshRenderGl* pMeshRender, ShaderLoaderGl* pShaderLoader);

	void init();
	void render(
		const Model& model, const Outline& outline, const Transform& transform, const glm::mat4& projection, const glm::mat4& view);

private:
	MeshRenderGl* m_pMeshRender = nullptr;
	ShaderLoaderGl* m_pShaderLoader = nullptr;

	unsigned int m_outlineShader = 0;
};
