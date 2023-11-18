#include "layout_controller.h"

void LayoutController::update() {
	std::vector<WidgetData> widgets;

	updateLayout(m_layout, widgets);

	m_textController->addText();
}

void LayoutController::show() {
	
}

void LayoutController::hide() {
	
}

void LayoutController::updateLayout(std::shared_ptr<Layout> layout, std::vector<std::shared_ptr<Widget>>& widgets) {
	std::vector<Widget> layoutWidgets = layout->getChildrenWidgets();

	for (Widget& widget : layoutWidgets) {
		std::shared_ptr<Layout> childLayout = widget.getLayout();

		layout->updateChildWidget(widget);
		updateLayout(childLayout, widgets);

		// translate position of child widgets of the widget`s layout according to the widget.
		for (Widget& dataChildren : childLayout->getChildrenWidgets()) {
			auto vertices = dataChildren.getVertices();
			for (glm::vec2& vertice : vertices) {
				vertice += widget.getPosition();
			}
			dataChildren.setVertices(vertices);
		}
	}
	 
	widgets.insert(std::end(widgets), std::begin(layoutWidgets), std::end(layoutWidgets));
}