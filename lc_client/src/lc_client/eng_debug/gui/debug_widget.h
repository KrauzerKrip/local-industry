#pragma once

#include "lc_client/tier0/tier0.h"
#include "lc_client/eng_gui/widgets/widget.h"
#include "lc_client/eng_gui/widgets/text_widget.h"
#include "lc_client/eng_input/i_input.h"
#include "lc_client/eng_graphics/camera/camera.h"


class DebugWidget : public Widget {
public:
	DebugWidget(Tier0* pTier0, IInput* pInput, Camera* pCamera, GuiDependencies dependencies);
	
	void render();

private:
	IInput* m_pInput = nullptr;
	Camera* m_pCamera = nullptr;

	TextWidget* m_pFpsDataWidget = nullptr;
	TextWidget* m_pMousePositionWidget = nullptr;
	TextWidget* m_pCameraPositionWidget = nullptr;
	float timeSinceLastFpsShow = 0.0f;
};
