#include "gl_outline_render.h"

#include <glad/glad.h>

#include "lc_client/eng_graphics/entt/components.h"
#include "lc_client/eng_model/entt/components.h"
#include "lc_client/eng_scene/entt/components.h"
#include "lc_client/eng_graphics/openGL/renders/gl_mesh_render.h"
#include "lc_client/eng_graphics/openGL/gl_shader_uniform.h"


OutlineRenderGl::OutlineRenderGl(MeshRenderGl* pMeshRender, ShaderLoaderGl* pShaderLoader) {
	m_pMeshRender = pMeshRender;
    m_outlineShader = pShaderLoader->createShaderProgram("base", "primitive");
}

void OutlineRenderGl::render(const Model& model, const Outline& outline, const Transform& transform,
	const glm::mat4& projection, const glm::mat4& view) {
	Transform transformOutline(transform);
	transformOutline.scale = transform.scale + outline.width;

	glStencilFunc(GL_NOTEQUAL, 1, 0xFF);
	glStencilMask(0x00);
	glUseProgram(m_outlineShader);
	setUniform(m_outlineShader, "color", outline.color);
	m_pMeshRender->setUp(transformOutline, m_outlineShader, projection, view);
	for (const entt::entity& meshEntity : model.meshes) {
		m_pMeshRender->renderMesh(meshEntity);
	}
	glStencilMask(0xFF);
	glStencilFunc(GL_ALWAYS, 0, 0xFF);
	glEnable(GL_DEPTH_TEST);
}
