#pragma once

#include "lc_client/eng_graphics/gui/background_render.h"
#include "lc_client/eng_graphics/gui/zoffset_calculator.h"
#include "lc_client/eng_graphics/gui/text_render.h"
#include "lc_client/eng_gui/input/input_controller.h"
#include "style.h"


struct GuiDependencies {
	BackgroundRender* pBackgroundRender;
	TextRender* pTextRender;
	ZOffsetCalculator* pWidgetZOffsetCalculator;
	ZOffsetCalculator* pTextZOffsetCalculator;
	InputController* pInputController;
	Style* pStyle;

	GuiDependencies() { 
		pBackgroundRender = nullptr;
		pTextRender = nullptr;
		pWidgetZOffsetCalculator = nullptr;
		pTextZOffsetCalculator = nullptr;
		pInputController = nullptr;
		pStyle = nullptr;
	}

	GuiDependencies(GuiDependencies& t) {
		pBackgroundRender = t.pBackgroundRender;
		pTextRender = t.pTextRender;
		pWidgetZOffsetCalculator = t.pWidgetZOffsetCalculator;
		pTextZOffsetCalculator = t.pTextZOffsetCalculator;
		pInputController = t.pInputController;
		pStyle = t.pStyle;
	}

	GuiDependencies(const GuiDependencies& t) {
		pBackgroundRender = t.pBackgroundRender;
		pTextRender = t.pTextRender;
		pWidgetZOffsetCalculator = t.pWidgetZOffsetCalculator;
		pTextZOffsetCalculator = t.pTextZOffsetCalculator;
		pInputController = t.pInputController;
		pStyle = t.pStyle;
	}
};

