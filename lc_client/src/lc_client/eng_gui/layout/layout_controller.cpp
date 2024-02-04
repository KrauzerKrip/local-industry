#include "layout_controller.h"

void LayoutController::update() {
	m_widgets.clear();

	LayoutData layoutData(m_layout);

	updateLayout(layoutData, m_widgets);
}

std::vector<Widget*>& LayoutController::getWidgets() { return m_widgets; }

void LayoutController::show() {
	
}

void LayoutController::hide() {
	
}

void LayoutController::setLayout(std::shared_ptr<Layout> layout) { m_layout = layout; }

void LayoutController::updateLayout(LayoutData layoutData, std::vector<Widget*>& widgets) {
	std::vector<Widget*> layoutWidgets = layoutData.layout->getChildrenWidgets();

	for (Widget* pWidget : layoutWidgets) {
		pWidget->getRectangle().m_absolutePosition = glm::vec2(0);
		//widget->getRectangle().m_size = glm::vec2(0);
	}

	layoutData.layout->updateChildWidgets();

	for (Widget* pWidget : layoutWidgets) {
		pWidget->getRectangle().m_absolutePosition += layoutData.position;

		pWidget->getLayer().number = layoutData.layer;

		LayoutData childLayoutData(pWidget->getLayout());
		childLayoutData.position = pWidget->getRectangle().m_absolutePosition;
		childLayoutData.size = pWidget->getRectangle().m_size;
		childLayoutData.layer = layoutData.layer;

		widgets.push_back(pWidget);
		
		if (pWidget->getLayout().get() != nullptr) {
			childLayoutData.layer++;
			pWidget->getLayout()->m_position = pWidget->getRectangle().m_absolutePosition;
			pWidget->getLayout()->m_size = pWidget->getRectangle().m_size;
			updateLayout(childLayoutData, widgets);
		}
	}
}