#include "gui_presenter.h"

#include <iostream>

#include "lc_client/eng_gui/layout/widget_data.h"


GuiPresenter::GuiPresenter(LayoutController* pOverlayLayoutController, LayoutController* pLayoutController,
	BackgroundRender* pBackgroundRender, std::vector<QueueRender*> queueRenders) {
	m_pOverlayLayoutController = pOverlayLayoutController;
	m_pLayoutController = pLayoutController;
	m_pBackgroundRender = pBackgroundRender;
	m_queueRenders = queueRenders;
}

void GuiPresenter::render() { 
	m_pBackgroundRender->frame();

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
