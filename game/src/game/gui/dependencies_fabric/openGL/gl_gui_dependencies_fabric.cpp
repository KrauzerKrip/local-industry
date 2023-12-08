#include "gl_gui_dependencies_fabric.h"

#include "lc_client/eng_graphics/gui/openGL/gl_background_render.h"
#include "lc_client/eng_graphics/gui/openGL/gl_text_render.h"
#include "lc_client/eng_graphics/gui/openGL/gl_text_zoffset_calculator.h"
#include "lc_client/eng_graphics/gui/openGL/gl_widget_zoffset_calculator.h"


GuiDependenciesFabricGl::GuiDependenciesFabricGl(IConsole* pConsole, ShaderLoaderGl* pShaderWorkGl) { 
	BackgroundRenderGl* pBackgroundRender = new BackgroundRenderGl(pConsole, pShaderWorkGl);
	TextRenderGl* pTextRender = new TextRenderGl(pConsole, pShaderWorkGl);
	WidgetZOffsetCalculatorGl* pWidgetZOffsetCalculator = new WidgetZOffsetCalculatorGl();
	TextZOffsetCalculatorGl* pTextZOffsetCalculator = new TextZOffsetCalculatorGl();

	m_widgetDependecies.pBackgroundRender = pBackgroundRender;
	m_widgetDependecies.pZOffsetCalculator = pWidgetZOffsetCalculator;

	m_textWidgetDependencies.pBackgroundRender = pBackgroundRender;
	m_textWidgetDependencies.pTextRender = pTextRender;
	m_textWidgetDependencies.pWidgetZOffsetCalculator = pWidgetZOffsetCalculator;
	m_textWidgetDependencies.pTextZOffsetCalculator = pTextZOffsetCalculator;
}

WidgetDependecies GuiDependenciesFabricGl::getWidgetDependencies() { return m_widgetDependecies; }

TextWidgetDependecies GuiDependenciesFabricGl::getTextWidgetDependecies() { return m_textWidgetDependencies; }
