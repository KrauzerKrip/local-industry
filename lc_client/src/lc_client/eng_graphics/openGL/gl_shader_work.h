#pragma once

#include "lc_client/eng_graphics/shader_work.h"

#include <vector>

#include "lc_client/tier1/i_shaders.h"
#include "lc_client/eng_graphics/openGL/gl_render.h"
#include "lc_client/eng_graphics/openGL/gl_skybox_render.h"
#include "lc_client/eng_graphics/gui/openGL/gl_render_background.h"
#include "lc_client/tier0/console/i_console.h"
#include "lc_client/eng_graphics/gui/openGL/gl_render_text.h"


class ShaderWorkGl : public ShaderWork {
	friend class RenderGL; 
	friend class SkyboxRenderGl;
	friend class RenderBackgroundGl;
	friend class RenderTextGl;

public:
	ShaderWorkGl(IShaderManager* pShaderManager, IConsole* pConsole)
		: ShaderWork(),
		  m_pShaderManager(pShaderManager),
		  m_pConsole(pConsole) {};

	void loadShaders(entt::registry* pRegistry, entt::entity entity, const std::string vertexShaderName,
		const std::string fragmentShaderName);

private:
	IShaderManager* m_pShaderManager;
	IConsole* m_pConsole;

	unsigned int createShaderProgram(std::string vertexShaderName, std::string fragmentShaderName);
};
