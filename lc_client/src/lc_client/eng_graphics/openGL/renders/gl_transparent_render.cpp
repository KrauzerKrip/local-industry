#include "gl_transparent_render.h"

#include <glad/glad.h>

#include "lc_client/eng_graphics/entt/components.h"
#include "lc_client/eng_model/entt/components.h"
#include "lc_client/eng_scene/entt/components.h"
#include "lc_client/eng_graphics/openGL/renders/gl_mesh_render.h"
#include "lc_client/eng_graphics/openGL/gl_shader_uniform.h" 


TransparentRenderGl::TransparentRenderGl(Camera* pCamera, entt::registry* pRegistry, entt::registry* pUtilRegistry) {
	m_pRegistry = pRegistry;
	m_pUtilRegistry = pUtilRegistry;
	m_pCamera = pCamera;
}

void TransparentRenderGl::render(glm::mat4 projection, glm::mat4 view) {
	auto transparentEntitiesGroup = m_pRegistry->view<Transparent, Model, Transform, ShaderGl>();

	for (auto&& [entity, model, transform, shader] : transparentEntitiesGroup.each()) {
		unsigned int shaderProgram = shader.shaderProgram;
		std::vector<entt::entity>& meshes = model.meshes;
		glUseProgram(shaderProgram);
		eng::setMaterialSg(shaderProgram);
		setUniform(shaderProgram, "viewPos", m_pCamera->getPosition());
		glm::mat4 modelMatrix = glm::mat4(1.0f);
		eng::transform(modelMatrix, transform);
		eng::setMatrices(shaderProgram, modelMatrix, view, projection);

		for (entt::entity& meshEntity : meshes) {
			eng::renderMesh(meshEntity, m_pUtilRegistry);
		}
	}
}
