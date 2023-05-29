#pragma once

#include "lc_client/eng_graphics/shader_work.h"

#include <vector>

#include "lc_client/tier1/i_shaders.h"
#include "lc_client/eng_graphics/openGL/gl_render.h"


class ShaderWorkGl : public ShaderWork {
	friend class RenderGL; 

public:
	ShaderWorkGl(IShaderManager* pShaderManager, entt::registry* pRegistry)
		: ShaderWork(pRegistry),
		  m_pShaderManager(pShaderManager){};

	void loadShaders(entt::entity entity, const std::string vertexShaderName, const std::string fragmentShaderName);

private:
	IShaderManager* m_pShaderManager;

	unsigned int createShaderProgram(std::string vertexShaderName, std::string fragmentShaderName);
};
