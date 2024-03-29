#include "gl_gui_dependencies_fabric.h"

#include "lc_client/eng_graphics/gui/openGL/gl_background_render.h"
#include "lc_client/eng_graphics/gui/openGL/gl_text_render.h"
#include "lc_client/eng_graphics/gui/openGL/gl_text_zoffset_calculator.h"
#include "lc_client/eng_graphics/gui/openGL/gl_widget_zoffset_calculator.h"


GuiDependenciesFabricGl::GuiDependenciesFabricGl(IConsole* pConsole, ShaderLoaderGl* pShaderWorkGl, IInput* pInput,
	TextureManager* pTextureManager, FramebufferController* pFramebufferController) { 
	BackgroundRenderGl* pBackgroundRender =
		new BackgroundRenderGl(pConsole, pShaderWorkGl, pTextureManager, pFramebufferController);
	TextRenderGl* pTextRender = new TextRenderGl(pConsole, pShaderWorkGl);
	WidgetZOffsetCalculatorGl* pWidgetZOffsetCalculator = new WidgetZOffsetCalculatorGl();
	TextZOffsetCalculatorGl* pTextZOffsetCalculator = new TextZOffsetCalculatorGl();
	InputController* pInputController = new InputController(pInput);

	m_dependecies.pBackgroundRender = pBackgroundRender;
	m_dependecies.pWidgetZOffsetCalculator = pWidgetZOffsetCalculator;
	m_dependecies.pBackgroundRender = pBackgroundRender;
	m_dependecies.pTextRender = pTextRender;
	m_dependecies.pWidgetZOffsetCalculator = pWidgetZOffsetCalculator;
	m_dependecies.pTextZOffsetCalculator = pTextZOffsetCalculator;
	m_dependecies.pInputController = pInputController;
}

GuiDependencies GuiDependenciesFabricGl::getDependencies() { return m_dependecies; }
