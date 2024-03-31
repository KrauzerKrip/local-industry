#include "gl_gui_dependencies_fabric.h"

#include "lc_client/eng_graphics/gui/openGL/gl_background_render.h"
#include "lc_client/eng_graphics/gui/openGL/gl_text_render.h"
#include "lc_client/eng_graphics/gui/openGL/gl_text_zoffset_calculator.h"
#include "lc_client/eng_graphics/gui/openGL/gl_widget_zoffset_calculator.h"
#include "lc_client/eng_gui/widgets/style_impl.h"


GuiDependenciesFabricGl::GuiDependenciesFabricGl(IConsole* pConsole, ShaderLoaderGl* pShaderWorkGl, IInput* pInput,
	TextureManager* pTextureManager, FramebufferController* pFramebufferController) { 
	BackgroundRenderGl* pBackgroundRender =
		new BackgroundRenderGl(pConsole, pShaderWorkGl, pTextureManager, pFramebufferController);
	TextRenderGl* pTextRender = new TextRenderGl(pConsole, pShaderWorkGl);
	WidgetZOffsetCalculatorGl* pWidgetZOffsetCalculator = new WidgetZOffsetCalculatorGl();
	TextZOffsetCalculatorGl* pTextZOffsetCalculator = new TextZOffsetCalculatorGl();
	InputController* pInputController = new InputController(pInput);

	StyleImpl* pStyle = new StyleImpl();
	pStyle->setColor("blur_background_base", 160, 160, 160, 255);
	pStyle->setColor("blur_background_dark", 72, 72, 72, 255);
	pStyle->setColor("background_base", 140, 140, 140, 150);
	pStyle->setColor("background_dark", 72, 72, 72, 150);
	pStyle->setBlurIntensitry("base", 0.05);

	m_dependecies.pBackgroundRender = pBackgroundRender;
	m_dependecies.pWidgetZOffsetCalculator = pWidgetZOffsetCalculator;
	m_dependecies.pBackgroundRender = pBackgroundRender;
	m_dependecies.pTextRender = pTextRender;
	m_dependecies.pWidgetZOffsetCalculator = pWidgetZOffsetCalculator;
	m_dependecies.pTextZOffsetCalculator = pTextZOffsetCalculator;
	m_dependecies.pInputController = pInputController;
	m_dependecies.pStyle = pStyle;
}

GuiDependencies GuiDependenciesFabricGl::getDependencies() { return m_dependecies; }
