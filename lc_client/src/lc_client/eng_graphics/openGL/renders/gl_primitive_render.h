#pragma once

#include <entt/entt.hpp>
#include <glm/glm.hpp>

#include "lc_client/eng_graphics/openGL/gl_shader_loader.h"


class PrimitiveRender {
public:
	PrimitiveRender(ShaderLoaderGl* pShaderLoader, entt::registry* pSceneRegisry, entt::registry* pMapRegistry);

	void render(glm::mat4 projection, glm::mat4 view);

private:
	void renderLines(glm::mat4 projection, glm::mat4 view);
	
	unsigned int m_shader;
	unsigned int m_vao;
	unsigned int m_vbo;

	entt::registry* m_pSceneRegistry = nullptr;
	entt::registry* m_pMapRegistry = nullptr;
};
