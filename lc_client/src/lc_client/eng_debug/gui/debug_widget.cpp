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
	Frame* pFrame =  new Frame();
	pRow->setLayout(pFrame);
	pRow->setName("row");

	TextWidget* pLabel = new TextWidget(dependencies);
	pLabel->setTextSize(16);
	pLabel->setPosition(glm::vec2(10, 0));
	pLabel->setText(labelText);
	pLabel->setName("label_" + labelText);
	pLabel->setTextColor(glm::vec4(1, 1, 1, 1));
	pFrame->addChild(pLabel);

	TextWidget* pData = new TextWidget(dependencies);
	pData->setTextSize(16);
	pData->setPosition(glm::vec2(120, 0));
	pData->setText(dataText);
	pData->setName("data");
	pData->setTextColor(glm::vec4(1, 1, 1, 1));
	pFrame->addChild(pData);

	*pDataWidget = pData;

	return pRow;
}


DebugWidget::DebugWidget(Tier0* pTier0, IInput* pInput, Camera* pCamera, GuiDependencies dependencies) : Widget(dependencies) {
	m_pInput = pInput;
	m_pCamera = pCamera;

	
	this->setBackground(new ColorBackground(glm::vec4(0, 0, 0, 0.5), dependencies));
	this->setPosition(glm::vec2(1700, 820));
	this->setSize(glm::vec2(200, 250));
	this->setName("debugWidget");

	TextWidget* pLabel = new TextWidget(dependencies);
	pLabel->setTextSize(16);
	pLabel->setPosition(glm::vec2(10, -10));
	pLabel->setSize(glm::vec2(200, 36));
	pLabel->setText("Local` V0.0.1");
	pLabel->setName("label_local");
	pLabel->setTextColor(glm::vec4(1, 1, 1, 1));

	VBox* pVbox = new VBox();
	pVbox->setPadding(10, 10);
	this->setLayout(pVbox);

    Widget* rowFps = createRow("FPS", "", dependencies, &m_pFpsDataWidget);
	Widget* rowMousePos = createRow("MPos", "", dependencies, &m_pMousePositionWidget);
	Widget* rowCameraPos = createRow("CPos", "", dependencies, &m_pCameraPositionWidget);

	pVbox->addChild(pLabel);
	pVbox->addChild(rowFps);
	pVbox->addChild(rowMousePos);
	pVbox->addChild(rowCameraPos);

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

	m_pCameraPositionWidget->setText(
		std::to_string((int)m_pCamera->getPosition().x) + " " +
		std::to_string((int)m_pCamera->getPosition().y) + " " + 
			std::to_string((int)m_pCamera->getPosition().z));

	Widget::render();
}
