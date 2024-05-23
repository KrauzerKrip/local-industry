#pragma once

#include "game/gui/dependencies_fabric/gui_dependencies_fabric.h"
#include "lc_client/eng_input/i_input.h"
#include "lc_client/tier0/console/i_console.h"
#include "lc_client/eng_graphics/openGL/gl_shader_loader.h"
#include "lc_client/eng_graphics/texture_manager.h"
#include "lc_client/eng_graphics/openGL/gl_framebuffer.h"
#include "lc_client/eng_graphics/openGL/gl_framebuffer_controller.h"
#include "lc_client/eng_graphics/i_window.h"
#include "lc_client/eng_gui/popup_controller_impl.h"


class GuiDependenciesFabricGl : public GuiDependenciesFabric {
public:
	GuiDependenciesFabricGl(IConsole* pConsole, ShaderLoaderGl* pShaderWorkGl, IInput* pInput,
		TextureManager* pTextureManager, FramebufferController* pFramebufferController, IWindow* pWindow);

	GuiDependencies getDependencies() override;

private:
	GuiDependencies m_dependecies;
};
