#include "layout_controller.h"

void LayoutController::update() {
	m_widgets.clear();

	LayoutData layoutData(m_layout);

	updateLayout(layoutData, m_widgets);
}

std::vector<WidgetData>& LayoutController::getWidgets() { return m_widgets; }

void LayoutController::show() {
	
}

void LayoutController::hide() {
	
}

void LayoutController::setLayout(std::shared_ptr<Layout> layout) { m_layout = layout; }

void LayoutController::updateLayout(LayoutData layoutData, std::vector<WidgetData>& widgets) {
	std::vector<std::shared_ptr<Widget>> layoutWidgets = layoutData.layout->getChildrenWidgets();

	for (std::shared_ptr<Widget>& widget : layoutWidgets) {
		WidgetData widgetData(widget);
		widgetData.position = layoutData.position;
		layoutData.layout->updateChildWidget(widgetData);

		LayoutData childLayoutData(widget->getLayout());
		childLayoutData.position = widgetData.position;
		childLayoutData.size = widgetData.size;

		widgets.push_back(widgetData);
		
		if (widget->getLayout().get() != nullptr) {
			updateLayout(childLayoutData, widgets);
		}
	}
}