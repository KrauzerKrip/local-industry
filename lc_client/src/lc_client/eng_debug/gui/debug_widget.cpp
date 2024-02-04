#include "debug_widget.h"

#include <memory>
#include "lc_client/eng_gui/layout/layouts/vbox.h"
#include "lc_client/eng_gui/layout/layouts/frame.h"
#include "lc_client/eng_gui/paint_objects/color_background.h"
#include "lc_client/eng_gui/widgets/text_widget.h"
#include "ldk_client/local_engine/time.h"


Widget* createRow(std::string labelText, std::string dataText, GuiDependencies dependencies, TextWidget** pDataWidget) {
	Widget* pRow = new Widget(dependencies);
	pRow->setSize(glm::vec2(200, 24));
	std::shared_ptr<Frame> frame = std::make_shared<Frame>();
	pRow->setLayout(frame);
	pRow->setName("row");

	TextWidget* pLabel = new TextWidget(dependencies);
	pLabel->setTextSize(16);
	pLabel->setPosition(glm::vec2(10, 0));
	pLabel->setText(labelText);
	pLabel->setName("label_" + labelText);
	pLabel->setTextColor(glm::vec4(1, 1, 1, 1));
	frame->addChild(pLabel);

	TextWidget* pData = new TextWidget(dependencies);
	pData->setTextSize(16);
	pData->setPosition(glm::vec2(120, 0));
	pData->setText(dataText);
	pData->setName("data");
	pData->setTextColor(glm::vec4(1, 1, 1, 1));
	frame->addChild(pData);

	*pDataWidget = pData;

	return pRow;
}


DebugWidget::DebugWidget(Tier0* pTier0, IInput* pInput, GuiDependencies dependencies) : Widget(dependencies) {
	m_pInput = pInput;
	
	this->setBackground(new ColorBackground(glm::vec4(0, 0, 0, 0.5), dependencies));
	this->setPosition(glm::vec2(1750, 870));
	this->setSize(glm::vec2(160, 200));
	this->setName("debugWidget");

	TextWidget* pLabel = new TextWidget(dependencies);
	pLabel->setTextSize(16);
	pLabel->setPosition(glm::vec2(10, -10));
	pLabel->setSize(glm::vec2(200, 36));
	pLabel->setText("Local` V0.0.1");
	pLabel->setName("label_local");
	pLabel->setTextColor(glm::vec4(1, 1, 1, 1));

	std::shared_ptr<VBox> vbox = std::make_shared<VBox>();
	this->setLayout(vbox);

    Widget* rowFps = createRow("FPS", "", dependencies, &m_pFpsDataWidget);
	Widget* rowMousePos = createRow("MP", "", dependencies, &m_pMousePositionWidget);

	vbox->addChild(pLabel);
	vbox->addChild(rowFps);
	vbox->addChild(rowMousePos);

	pTier0->getParameters()->getParameter<bool>("cl_debug_mode").setCallback([this](bool value) {
		if (value) {
			this->showWithChildren();
		}
		else {
			this->hideWithChildren();
		}
	});
}

void DebugWidget::render() { 
	float deltaTime = Time::getDeltaTime();
	
	timeSinceLastFpsShow += deltaTime;

	if (timeSinceLastFpsShow > 1) {
		timeSinceLastFpsShow = 0.0f;
		int fps = 1.0f / deltaTime;
		m_pFpsDataWidget->setText(std::to_string(fps));
	}

	m_pMousePositionWidget->setText(std::to_string((int)m_pInput->getMousePosition().x) + " " +
									std::to_string((int)m_pInput->getMousePosition().y));

	Widget::render();
}
