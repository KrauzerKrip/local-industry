#pragma once

#include "game/gui/dependencies_fabric/gui_dependencies_fabric.h"
#include "lc_client/eng_input/i_input.h"
#include "lc_client/tier0/console/i_console.h"
#include "lc_client/eng_graphics/openGL/gl_shader_loader.h"


class GuiDependenciesFabricGl : public GuiDependenciesFabric {
public:
	GuiDependenciesFabricGl(IConsole* pConsole, ShaderLoaderGl* pShaderWorkGl, IInput* pInput);

	GuiDependencies getDependencies();

private:
	GuiDependencies m_dependecies;
};
