#include "gui_presenter.h"

#include <iostream>

#include "lc_client/eng_gui/layout/widget_data.h"


GuiPresenter::GuiPresenter(LayoutController* pOverlayLayoutController,
	LayoutController* pLayoutController, std::vector<QueueRender*> queueRenders) {
	m_pOverlayLayoutController = pOverlayLayoutController;
	m_pLayoutController = pLayoutController;
	m_queueRenders = queueRenders;
}

void GuiPresenter::render() { 
	std::vector<std::shared_ptr<Widget>> overlayWidgets = m_pOverlayLayoutController->getWidgets();

	for (std::shared_ptr<Widget>& widget : overlayWidgets) {
		widget->render();
	}

	for (QueueRender* pQueueRender : m_queueRenders) {
		pQueueRender->renderQueue();
	}


	std::vector<std::shared_ptr<Widget>> widgets = m_pLayoutController->getWidgets();

	for (std::shared_ptr<Widget>& widget : widgets) {
		widget->render();
	} 

	for (QueueRender* pQueueRender : m_queueRenders) {
		pQueueRender->renderQueue();
	}
}
