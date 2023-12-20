#pragma once

#include "lc_client/eng_graphics/gui/background_render.h"
#include "lc_client/eng_graphics/gui/zoffset_calculator.h"
#include "lc_client/eng_graphics/gui/text_render.h"
#include "lc_client/eng_gui/input/input_controller.h"

struct TextWidgetDependecies {
	BackgroundRender* pBackgroundRender;
	TextRender* pTextRender;
	ZOffsetCalculator* pWidgetZOffsetCalculator;
	ZOffsetCalculator* pTextZOffsetCalculator;
};


struct WidgetDependecies {
	BackgroundRender* pBackgroundRender;
	ZOffsetCalculator* pZOffsetCalculator;

	WidgetDependecies(TextWidgetDependecies dependencies)
		: pBackgroundRender(dependencies.pBackgroundRender),
		  pZOffsetCalculator(dependencies.pWidgetZOffsetCalculator)
	{};

	WidgetDependecies(){};
};

struct GuiDependencies {
	WidgetDependecies widgetDependencies;
	TextWidgetDependecies textWidgetDependencies;
	InputController* pInputController;

	GuiDependencies(WidgetDependecies widgetDependencies, TextWidgetDependecies textWidgetDependencies, InputController* pInputController)
		: widgetDependencies(widgetDependencies),
		  textWidgetDependencies(textWidgetDependencies), pInputController(pInputController) {}
};
