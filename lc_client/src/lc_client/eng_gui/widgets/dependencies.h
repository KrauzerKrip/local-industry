#pragma once

#include "lc_client/eng_graphics/gui/background_render.h"
#include "lc_client/eng_graphics/gui/zoffset_calculator.h"
#include "lc_client/eng_graphics/gui/text_render.h"
#include "lc_client/eng_gui/input/input_controller.h"


struct GuiDependencies {
	BackgroundRender* pBackgroundRender;
	TextRender* pTextRender;
	ZOffsetCalculator* pWidgetZOffsetCalculator;
	ZOffsetCalculator* pTextZOffsetCalculator;
	InputController* pInputController;
};

