#pragma once

#include <entt/entt.hpp>
#include <glm/glm.hpp>

#include "lc_client/eng_scene/entt/components.h"


namespace eng {

	void renderMesh(entt::entity meshEntity, entt::registry* pUtilRegistry);
	void setMatrices(unsigned int shaderProgram, glm::mat4& model, glm::mat4& view, glm::mat4 projection);
	void transform(glm::mat4& model, Transform& transform);
	void setMaterialSg(unsigned int shaderProgram);

}