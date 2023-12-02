#include "layout_controller.h"

void LayoutController::update() {
	m_widgets.clear();

	LayoutData layoutData(m_layout);

	updateLayout(layoutData, m_widgets);
}

std::vector<std::shared_ptr<Widget>>& LayoutController::getWidgets() { return m_widgets; }

void LayoutController::show() {
	
}

void LayoutController::hide() {
	
}

void LayoutController::setLayout(std::shared_ptr<Layout> layout) { m_layout = layout; }

void LayoutController::updateLayout(LayoutData layoutData, std::vector<std::shared_ptr<Widget>>& widgets) {
	std::vector<std::shared_ptr<Widget>> layoutWidgets = layoutData.layout->getChildrenWidgets();

	for (std::shared_ptr<Widget>& widget : layoutWidgets) {
		widget->getRectangle().m_absolutePosition = layoutData.position;
		layoutData.layout->updateChildWidget(*widget);

		widget->getLayer().setLayerNumber(layoutData.layer);

		LayoutData childLayoutData(widget->getLayout());
		childLayoutData.position = widget->getRectangle().m_absolutePosition;
		childLayoutData.size = widget->getRectangle().m_size;
		childLayoutData.layer = layoutData.layer;

		widgets.push_back(widget);
		
		if (widget->getLayout().get() != nullptr) {
			childLayoutData.layer++;
			updateLayout(childLayoutData, widgets);
		}
	}
}