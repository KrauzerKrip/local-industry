#pragma once

#include "lc_client/tier0/tier0.h"
#include "lc_client/eng_gui/widgets/widget.h"
#include "lc_client/eng_gui/widgets/text_widget.h"


class DebugWidget : public Widget {
public:
	DebugWidget(Tier0* pTier0, WidgetDependecies dependencies, TextWidgetDependecies textDependencies);
	
	void render();

private:
	TextWidget* m_pFpsDataWidget = nullptr;
	float timeSinceLastFpsShow = 0.0f;
};
