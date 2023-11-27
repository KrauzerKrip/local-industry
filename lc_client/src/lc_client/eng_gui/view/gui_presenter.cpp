#include "gui_presenter.h"

#include "lc_client/eng_gui/layout/widget_data.h"


GuiPresenter::GuiPresenter(LayoutController* pLayoutController, std::vector<QueueRender*> queueRenders) {
	m_pLayoutController = pLayoutController;
	m_queueRenders = queueRenders;
}

void GuiPresenter::render() { 
	std::vector<WidgetData> widgetsData = m_pLayoutController->getWidgets();

	for (WidgetData& widgetData : widgetsData) {
		widgetData.widget->render(widgetData.position, widgetData.size, widgetData.layer);
	} 

	for (QueueRender* pQueueRender : m_queueRenders) {
		pQueueRender->renderQueue();
	}
}
