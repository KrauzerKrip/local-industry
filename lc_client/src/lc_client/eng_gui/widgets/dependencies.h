#pragma once

#include "lc_client/eng_graphics/gui/background_render.h"
#include "lc_client/eng_graphics/gui/zoffset_calculator.h"
#include "lc_client/eng_graphics/gui/text_render.h"

struct TextWidgetDependecies {
	BackgroundRender* pBackgroundRender;
	TextRender* pTextRender;
	ZOffsetCalculator* pZOffsetCalculator;
};


struct WidgetDependecies {
	BackgroundRender* pBackgroundRender;
	ZOffsetCalculator* pZOffsetCalculator;

	WidgetDependecies(TextWidgetDependecies dependencies)
		: pBackgroundRender(dependencies.pBackgroundRender),
		  pZOffsetCalculator(dependencies.pZOffsetCalculator)
	{};

	WidgetDependecies(){};
};