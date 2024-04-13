#include "gui_presenter.h"

#include <iostream>
#include <imgui.h>

#include "lc_client/eng_gui/layout/widget_data.h"


GuiPresenter::GuiPresenter() {
}

void GuiPresenter::render() { 
	m_pBackgroundRender->frame();
	m_pTextRender->frame();

	std::vector<Widget*> overlayWidgets = m_pOverlayLayoutController->getWidgets();

	for (Widget* pWidget : overlayWidgets) {
		pWidget->render();
	}

	for (QueueRender* pQueueRender : m_queueRenders) {
		pQueueRender->renderQueue();
	}


	std::vector<Widget*> widgets = m_pLayoutController->getWidgets();

	for (Widget* pWidget : widgets) {
		pWidget->render();
	} 

	for (QueueRender* pQueueRender : m_queueRenders) {
		pQueueRender->renderQueue();
	}
}

void GuiPresenter::setDependencies(const GuiDependencies& dependencies, LayoutController* pOverlayLayoutController,
	LayoutController* pLayoutController) {
	m_pBackgroundRender = dependencies.pBackgroundRender;
	m_pTextRender = dependencies.pTextRender;
	m_pOverlayLayoutController = pOverlayLayoutController;
	m_pLayoutController = pLayoutController;
}