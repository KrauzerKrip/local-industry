#pragma once

#include <entt/entt.hpp>
#include <glm/glm.hpp>

#include "lc_client/eng_graphics/openGL/gl_shader_loader.h"


class PrimitiveRender {
public:
	PrimitiveRender(ShaderLoaderGl* pShaderLoader, entt::registry* pSceneRegisry, entt::registry* pMapRegistry);

	void init();
	void render(glm::mat4 projection, glm::mat4 view);

private:
	void renderLines(glm::mat4 projection, glm::mat4 view);
	void renderCubes(glm::mat4 projection, glm::mat4 view);
	
	unsigned int m_shader;
	unsigned int m_lineVao;
	unsigned int m_lineVbo;
	unsigned int m_cubeVao;

	entt::registry* m_pSceneRegistry = nullptr;
	entt::registry* m_pMapRegistry = nullptr;

	ShaderLoaderGl* m_pShaderLoader = nullptr;
};
