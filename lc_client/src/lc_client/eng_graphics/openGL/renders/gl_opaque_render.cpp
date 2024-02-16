#include "gl_opaque_render.h"

#include <glad/glad.h>

#include "lc_client/eng_cubemaps/entt/components.h"
#include "lc_client/eng_graphics/entt/components.h"
#include "lc_client/eng_model/entt/components.h"
#include "lc_client/eng_scene/entt/components.h"
#include "lc_client/eng_graphics/openGL/renders/gl_mesh_render.h"
#include "lc_client/eng_graphics/openGL/gl_shader_uniform.h"


OpaqueRenderGl::OpaqueRenderGl(Camera* pCamera, MeshRenderGl* pMeshRenderGl, OutlineRenderGl* pOutlineRender,
	LightingGl* pLighting, Skybox* pSkybox, entt::registry* pRegistry, entt::registry* pUtilRegistry) {
	m_pRegistry = pRegistry;
	m_pUtilRegistry = pUtilRegistry;
	m_pCamera = pCamera;
	m_pMeshRender = pMeshRenderGl;
	m_pOutlineRender = pOutlineRender;
	m_pLighting = pLighting;
	m_pSkybox = pSkybox;
}

void OpaqueRenderGl::render(const glm::mat4& projection, const glm::mat4& view) {
	auto materialEntitiesGroup = m_pRegistry->view<Model, Transform, ShaderGl, Properties>(entt::exclude<Transparent>);

	for (auto&& [entity, model, transform, shader, properties] : materialEntitiesGroup.each()) {
		std::vector<entt::entity>& meshes = model.meshes;
		unsigned int shaderProgram = shader.shaderProgram;
		glUseProgram(shaderProgram);
		m_pSkybox->bindTexture();
		
		if (m_pRegistry->all_of<AssignedCubemap>(entity)) {
			entt::entity cubemapEntity = m_pRegistry->get<AssignedCubemap>(entity).cubemap;
			entt::entity cubemapGlEntity = m_pRegistry->get<Cubemap>(cubemapEntity).cubemap;
			const CubemapGl& cubemapGl = m_pUtilRegistry->get<CubemapGl>(cubemapGlEntity);
			glActiveTexture(GL_TEXTURE0 + TextureType::CUBEMAP);
			glBindTexture(GL_TEXTURE_CUBE_MAP, cubemapGl.textureId);
		}

		setUniform(shaderProgram, "skybox", TextureType::SKYBOX);
		setUniform(shaderProgram, "cubemap", TextureType::CUBEMAP);
		m_pLighting->setLighting(shaderProgram);
		setUniform(shaderProgram, "viewPos", m_pCamera->getPosition());

		m_pMeshRender->setUp(transform, shaderProgram, projection, view);

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
