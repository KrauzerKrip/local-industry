#include "planned_task_list.h"

#include <iostream>
#include "lc_client/eng_gui/includes.h"


PlannedTaskList::PlannedTaskList(std::string label, GuiDependencies dependencies) {
	BlurBackground* pBaseBlurBackground = new BlurBackground(dependencies.pStyle->getColor("blur_background_base"),
		dependencies.pStyle->getBlurIntensity("base"), dependencies);
	BlurBackground* pDarkBlurBackground = new BlurBackground(dependencies.pStyle->getColor("blur_background_dark"),
		dependencies.pStyle->getBlurIntensity("base"), dependencies);
	ColorBackground* pBaseBackground =
		new ColorBackground(dependencies.pStyle->getColor("background_base"), dependencies);
	ColorBackground* pDarkBackground =
		new ColorBackground(glm::vec4(glm::vec3(dependencies.pStyle->getColor("background_dark")), 0.7), dependencies);

	unsigned int taskSlots = 10;

	this->setSize(400, 1);
	this->setName("planned_task_list");

    PercentagePane* pPercantagePane = new PercentagePane();
	TextWidget* pLabel = new TextWidget(dependencies);
	pLabel->setBackground(pBaseBackground);
	pLabel->setTextSize(24);
	pLabel->setText(label);
	pLabel->setTextColor(255, 255, 255, 255);
	pPercantagePane->addWidget(pLabel, glm::vec2(0, 0.95), glm::vec2(1, 0.05));

	Widget* pTaskBoxBorderWidget = new Widget(pBaseBackground);
	VBox* pTaskBoxBorderLayout = new VBox();
	pTaskBoxBorderLayout->setMode(BoxMode::STRETCH_WIDGETS);
	pTaskBoxBorderLayout->setPadding(5, 5);
	pTaskBoxBorderWidget->setLayout(pTaskBoxBorderLayout);
	Widget* pTaskBoxWidget = new Widget(pDarkBackground);
	pTaskBoxWidget->setName("task_box_widget");
	m_pTaskListLayout = new TaskListLayout(taskSlots, dependencies);
	pTaskBoxWidget->setLayout(m_pTaskListLayout);
	pTaskBoxBorderLayout->addChild(pTaskBoxWidget);
	pPercantagePane->addWidget(pTaskBoxBorderWidget, glm::vec2(0, 0), glm::vec2(1, 0.94));

	this->setLayout(pPercantagePane);
}


