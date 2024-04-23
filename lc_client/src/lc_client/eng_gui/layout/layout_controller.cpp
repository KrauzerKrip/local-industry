#include "layout_controller.h"

LayoutController::~LayoutController() = default;

void LayoutController::update() {
	m_widgets.clear();

	LayoutData layoutData(m_layout.get());

	updateLayout(layoutData, m_widgets);
}

std::vector<Widget*>& LayoutController::getWidgets() { return m_layout->getChildrenWidgets(); }

void LayoutController::show() {
	
}

void LayoutController::hide() {
	
}

void LayoutController::setLayout(Layout* pLayout) { m_layout = std::unique_ptr<Layout>(pLayout); }

void LayoutController::updateLayout(LayoutData layoutData, std::vector<Widget*>& widgets) {
	std::vector<Widget*> layoutWidgets = layoutData.pLayout->getChildrenWidgets();

	for (Widget* pWidget : layoutWidgets) {
		pWidget->getRectangle().m_absolutePosition = glm::vec2(0);
		//widget->getRectangle().m_size = glm::vec2(0);
	}

	layoutData.pLayout->updateChildWidgets();

	for (Widget* pWidget : layoutWidgets) {
		pWidget->getRectangle().m_absolutePosition += layoutData.position;

		pWidget->getLayer().number = layoutData.layer;

		LayoutData childLayoutData(pWidget->getLayout());
		childLayoutData.position = pWidget->getRectangle().m_absolutePosition;
		childLayoutData.size = pWidget->getRectangle().m_size;
		childLayoutData.layer = layoutData.layer;

		widgets.push_back(pWidget);
		
		if (pWidget->getLayout() != nullptr) {
			childLayoutData.layer++;
			pWidget->getLayout()->m_position = pWidget->getRectangle().m_absolutePosition;
			pWidget->getLayout()->m_size = pWidget->getRectangle().m_size;
			updateLayout(childLayoutData, widgets);
		}
	}
}