#pragma once

#include "lc_client/eng_gui/layout/layout_controller.h"
#include "lc_client/eng_graphics/gui/queue_render.h"
#include "lc_client/eng_graphics/gui/background_render.h"


class GuiPresenter {
public:
	GuiPresenter();

	void render();
	void setDependencies(const GuiDependencies& dependencies, LayoutController* pOverlayLayoutController, LayoutController* pLayoutController);

private:
	LayoutController* m_pOverlayLayoutController = nullptr;
	LayoutController* m_pLayoutController = nullptr;
	std::vector<QueueRender*> m_queueRenders;
	BackgroundRender* m_pBackgroundRender = nullptr;
	TextRender* m_pTextRender = nullptr;
};
