#pragma once

#include "game/gui/dependencies_fabric/gui_dependencies_fabric.h"

#include "lc_client/tier0/console/i_console.h"
#include "lc_client/eng_graphics/openGL/gl_shader_work.h"

class GuiDependenciesFabricGl : public GuiDependenciesFabric {
public:
	GuiDependenciesFabricGl(IConsole* pConsole, ShaderWorkGl* pShaderWorkGl);

	WidgetDependecies getWidgetDependencies();
	TextWidgetDependecies getTextWidgetDependecies();

private:
	WidgetDependecies m_widgetDependecies;
	TextWidgetDependecies m_textWidgetDependencies;
};
