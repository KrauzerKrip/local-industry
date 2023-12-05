#include "debug_widget.h"

#include <memory>
#include "lc_client/eng_gui/layout/layouts/vbox.h"
#include "lc_client/eng_gui/layout/layouts/frame.h"
#include "lc_client/eng_gui/widgets/text_widget.h"


std::shared_ptr<Widget> createRow(std::string labelText, std::string dataText, WidgetDependecies dependencies, TextWidgetDependecies textDependencies) {
	std::shared_ptr<Widget> row = std::make_shared<Widget>(dependencies);
	row->setSize(glm::vec2(200, 24));
	std::shared_ptr<Frame> frame = std::make_shared<Frame>();
	row->setLayout(frame);
	row->setName("row");
	row->show();

	std::shared_ptr<TextWidget> label = std::make_shared<TextWidget>(textDependencies);
	label->setTextSize(16);
	label->setPosition(glm::vec2(10, 0));
	label->setText(labelText);
	label->setName("label");
	label->setColor(glm::vec4(1, 1, 1, 1));
	frame->addChild(label);
	label->show();

	std::shared_ptr<TextWidget> data = std::make_shared<TextWidget>(textDependencies);
	data->setTextSize(16);
	data->setPosition (glm::vec2(120, 0));
	data->setText(dataText);
	data->setName("data");
	data->setColor(glm::vec4(1, 1, 1, 1));
	frame->addChild(data);
	data->show();

	return row;
}



DebugWidget::DebugWidget(Tier0* pTier0, WidgetDependecies dependencies, TextWidgetDependecies textDependencies) : Widget(dependencies) {
	this->setBackground(glm::vec4(0, 0, 0, 0.5));
	this->setPosition(glm::vec2(1750, 870));
	this->setSize(glm::vec2(160, 200));
	this->setName("debugWidget");

	std::shared_ptr<VBox> vbox = std::make_shared<VBox>();
	this->setLayout(vbox);

	std::shared_ptr<Widget> row1 = createRow("test1", "100", dependencies, textDependencies);
	std::shared_ptr<Widget> row2 = createRow("test2", "100", dependencies, textDependencies);

	vbox->addChild(row1);
	vbox->addChild(row2);
}
