#include "gui_presenter.h"

#include "lc_client/eng_gui/layout/widget_data.h"


GuiPresenter::GuiPresenter(LayoutController* pLayoutController, std::vector<QueueRender*> queueRenders) {
	m_pLayoutController = pLayoutController;
	m_queueRenders = queueRenders;
}

void GuiPresenter::render() { 
	std::vector<std::shared_ptr<Widget>> widgets = m_pLayoutController->getWidgets();

	for (std::shared_ptr<Widget>& widget : widgets) {
		widget->render();
	} 

	for (QueueRender* pQueueRender : m_queueRenders) {
		pQueueRender->renderQueue();
	}
}
