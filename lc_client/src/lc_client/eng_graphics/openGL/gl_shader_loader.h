#pragma once

#include "lc_client/eng_graphics/shader_loader.h"

#include <vector>

#include "lc_client/tier1/i_shaders.h"
#include "lc_client/tier0/console/i_console.h"


class ShaderLoaderGl : public ShaderLoader {
public:
	ShaderLoaderGl(IShaderManager* pShaderManager, IConsole* pConsole)
		: ShaderLoader(),
		  m_pShaderManager(pShaderManager),
		  m_pConsole(pConsole) {};

	void loadShaders(entt::registry* pRegistry, entt::entity entity, const std::string vertexShaderName,
		const std::string fragmentShaderName);
	unsigned int createShaderProgram(std::string vertexShaderName, std::string fragmentShaderName);

private:
	IShaderManager* m_pShaderManager;
	IConsole* m_pConsole;
};
