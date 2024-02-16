#pragma once

#include <entt/entt.hpp>
#include <glm/glm.hpp>

#include "lc_client/eng_scene/entt/components.h"


class MeshRenderGl {
public:
	MeshRenderGl(entt::registry* pUtilRegistry);

	void setUp(const Transform& transform, unsigned int shaderProgram, const glm::mat4& projection, const glm::mat4& view);
	void renderMesh(entt::entity meshEntity);

private:
	void setMatrices(
		unsigned int shaderProgram, const glm::mat4& model, const glm::mat4& projection, const glm::mat4& view);
	void appleTransform(glm::mat4& model, const Transform& transform);
	void setMaterialSg(unsigned int shaderProgram);

	entt::registry* m_pUtilRegistry = nullptr;
};