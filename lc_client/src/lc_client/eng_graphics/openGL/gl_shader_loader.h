#pragma once

#include "lc_client/eng_graphics/shader_loader.h"

#include <vector>

#include "lc_client/eng_graphics/openGL/gl_shader_manager.h"
#include "lc_client/tier0/console/i_console.h"


class ShaderLoaderGl : public ShaderLoader {
public:
	ShaderLoaderGl(IConsole* pConsole)
		: ShaderLoader(), m_pShaderManager(nullptr),
		  m_pConsole(pConsole) {};

	void loadShaders(entt::registry* pRegistry, entt::entity entity, const std::string vertexShaderName,
		const std::string fragmentShaderName);
	unsigned int createShaderProgram(std::string vertexShaderName, std::string fragmentShaderName);
	void setShaderManager(ShaderManagerGl* pShaderManager);

private:
	ShaderManager* m_pShaderManager;
	IConsole* m_pConsole;
};
