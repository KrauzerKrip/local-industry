#pragma once

#include "lc_client/tier0/tier0.h"
#include "lc_client/eng_gui/widgets/widget.h"
#include "lc_client/eng_gui/widgets/text_widget.h"
#include "lc_client/eng_input/i_input.h"

class DebugWidget : public Widget {
public:
	DebugWidget(Tier0* pTier0, IInput* pInput, GuiDependencies dependencies);
	
	void render();

private:
	IInput* m_pInput = nullptr;

	TextWidget* m_pFpsDataWidget = nullptr;
	TextWidget* m_pMousePositionWidget = nullptr;
	float timeSinceLastFpsShow = 0.0f;
};
