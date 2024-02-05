#include "character_task_list.h"

#include "lc_client/eng_gui/includes.h"

CharacterTaskList::CharacterTaskList(std::string name, GuiDependencies dependencies) {
    unsigned int taskSlots = 10;
    m_pTaskListLayout = new TaskListLayout(taskSlots, dependencies);

	this->setSize(400, 1);
	this->setName(name + " character_task_list");

	PercentagePane* pPercantagePane = new PercentagePane();
	TextWidget* pLabel = new TextWidget(dependencies);
	pLabel->setBackground(new ColorBackground(120, 120, 120, 255, dependencies));
	pLabel->setTextSize(24);
	pLabel->setText(name);
	pLabel->setTextColor(255, 255, 255, 255);
	pPercantagePane->addWidget(pLabel, glm::vec2(0, 0.90), glm::vec2(1, 0.1));

	Widget* pTaskBoxBorderWidget = new Widget(new ColorBackground(120, 120, 120, 255, dependencies));
	VBox* pTaskBoxBorderLayout = new VBox();
	pTaskBoxBorderLayout->setMode(BoxMode::STRETCH_WIDGETS);
	pTaskBoxBorderLayout->setPadding(5, 5);
	pTaskBoxBorderWidget->setLayout(pTaskBoxBorderLayout);
	Widget* pTaskBoxWidget = new Widget(new ColorBackground(72, 72, 72, 255, dependencies));
	pTaskBoxWidget->setName("task_box_widget");
	pTaskBoxWidget->setLayout(m_pTaskListLayout);
	pTaskBoxBorderLayout->addChild(pTaskBoxWidget);
	pPercantagePane->addWidget(pTaskBoxBorderWidget, glm::vec2(0, 0), glm::vec2(1, 0.90));

	this->setLayout(pPercantagePane);
}
