#include "gl_transparent_render.h"

#include <glad/glad.h>

#include "lc_client/eng_graphics/entt/components.h"
#include "lc_client/eng_model/entt/components.h"
#include "lc_client/eng_scene/entt/components.h"
#include "lc_client/eng_graphics/openGL/renders/gl_mesh_render.h"
#include "lc_client/eng_graphics/openGL/gl_shader_uniform.h" 


TransparentRenderGl::TransparentRenderGl(
	Camera* pCamera, MeshRenderGl* pMeshRenderGl, OutlineRenderGl* pOutlineRender, entt::registry* pRegistry) {
	m_pRegistry = pRegistry;
	m_pCamera = pCamera;
	m_pMeshRender = pMeshRenderGl;
	m_pOutlineRender = pOutlineRender;
}

void TransparentRenderGl::render(const glm::mat4& projection, const glm::mat4& view) {
	auto transparentEntitiesGroup = m_pRegistry->view<Transparent, Model, Transform, ShaderGl>();

	for (auto&& [entity, model, transform, shader] : transparentEntitiesGroup.each()) {
		unsigned int shaderProgram = shader.shaderProgram;
		std::vector<entt::entity>& meshes = model.meshes;
		glUseProgram(shaderProgram);
		setUniform(shaderProgram, "viewPos", m_pCamera->getPosition());

		m_pMeshRender->setUp(transform, shaderProgram, projection, view);

		if (m_pRegistry->all_of<ShaderUniforms>(entity)) {
			const ShaderUniforms& uniforms = m_pRegistry->get<ShaderUniforms>(entity);

			for (auto&& [k, v] : uniforms.floatUniforms) {
				setUniform(shaderProgram, k, v);
			}
			for (auto&& [k, v] : uniforms.vectorUniforms) {
				setUniform(shaderProgram, k, v);
			}
		}

		if (m_pRegistry->all_of<Outline>(entity)) {
			glStencilFunc(GL_ALWAYS, 1, 0xFF);
			glStencilMask(0xFF);
		}
		for (entt::entity& meshEntity : meshes) {
			m_pMeshRender->renderMesh(meshEntity);
		}

		if (m_pRegistry->all_of<Outline>(entity)) {
			m_pOutlineRender->render(model, m_pRegistry->get<Outline>(entity), transform, projection, view);
		}
	}
}
