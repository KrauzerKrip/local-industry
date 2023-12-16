#include "gl_render_map.h"

#include <glad/glad.h>

#include "lc_client/eng_scene/entt/components.h"
#include "lc_client/eng_graphics/entt/components.h"
#include "lc_client/eng_graphics/openGL/gl_shader_uniform.h"

RenderMapGl::RenderMapGl(LightingGl* pLighting, RenderGL* pRenderGL, Camera* pCamera,
	Skybox* pSkybox, entt::registry* pRegistry, entt::registry* pUtilRegistry) { 
	m_pRegistry = pRegistry;
	m_pUtilRegistry = pUtilRegistry;
	m_pRenderGl = pRenderGL;
	m_pLighting = pLighting;
	m_pCamera = pCamera;
	m_pSkybox = pSkybox;
}

void RenderMapGl::render(glm::mat4 view, glm::mat4 projection) {
	auto meshesGroup = m_pRegistry->group<Mesh, Transform, ShaderGl>();

	entt::view<entt::get_t<CubemapGl, Transform>, entt::exclude_t<>> cubemapEntities =
		m_pRegistry->view<CubemapGl, Transform>();

	for (entt::entity entity : meshesGroup) {
		Mesh& mesh = meshesGroup.get<Mesh>(entity);
		unsigned int shaderProgram = meshesGroup.get<ShaderGl>(entity).shaderProgram;
		glUseProgram(shaderProgram);
		m_pSkybox->bindTexture();
		Transform& transform = meshesGroup.get<Transform>(entity);
		unsigned int nearestCubemapId = m_pRenderGl->getNearestCubemap(transform.position, cubemapEntities);
		if (nearestCubemapId != 0) {
			glActiveTexture(GL_TEXTURE0 + TextureType::CUBEMAP);
			glBindTexture(GL_TEXTURE_CUBE_MAP, nearestCubemapId);
		}

		setUniform(shaderProgram, "skybox", TextureType::SKYBOX);
		setUniform(shaderProgram, "cubemap", TextureType::CUBEMAP);
		m_pRenderGl->setMaterialSg(shaderProgram);
		m_pLighting->setLighting(shaderProgram);
		setUniform(shaderProgram, "viewPos", m_pCamera->getPosition());
		glm::mat4 modelMatrix = glm::mat4(1.0f);
		m_pRenderGl->transform(modelMatrix, transform);
		m_pRenderGl->setMatrices(shaderProgram, modelMatrix, view, projection);

		int vao = m_pRegistry->get<VaoGl>(entity).vaoId;
		MaterialSG& materialSG = m_pRegistry->get<MaterialSG>(entity);
		Texture* aoTexture = materialSG.aoTexture;
		Texture* diffuseTexture = materialSG.diffuseTexture;
		Texture* normalMap = materialSG.normalMap;
		Texture* specularMap = materialSG.specularTexture;
		aoTexture->bind();
		diffuseTexture->bind();
		normalMap->bind();
		specularMap->bind();
		glBindVertexArray(vao);
		glDrawElements(GL_TRIANGLES, (GLsizei)mesh.indices.size(), GL_UNSIGNED_INT, 0);
	}
}
