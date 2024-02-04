#include "task_list.h"

#include <iostream>

#include "task_list_layout.h"
#include "lc_client/eng_gui/includes.h"


TaskList::TaskList(unsigned int taskSlots, std::string label, GuiDependencies dependencies) {

    PercentagePane* pPercantagePane = new PercentagePane();
	TextWidget* pLabel = new TextWidget(dependencies);
	pLabel->setBackground(new ColorBackground(120, 120, 120, 255, dependencies));
	pLabel->setTextSize(24);
	pLabel->setSize(1, 52);
	pLabel->setText(label);
	pLabel->setTextColor(255, 255, 255, 255);
	pPercantagePane->addWidget(pLabel, glm::vec2(0, 0.9), glm::vec2(1, 0.1));


	Widget* pTaskBoxBorderWidget = new Widget(new ColorBackground(120, 120, 120, 255, dependencies));
	VBox* pTaskBoxBorderLayout = new VBox();
	pTaskBoxBorderLayout->setMode(BoxMode::STRETCH_WIDGETS);
	pTaskBoxBorderLayout->setPadding(5, 5);
	pTaskBoxBorderWidget->setLayout(pTaskBoxBorderLayout);
	Widget* pTaskBoxWidget = new Widget(new ColorBackground(72, 72, 72, 255, dependencies));
	pTaskBoxWidget->setName("task_box_widget");
	m_pTaskListLayout = new TaskListLayout(taskSlots, dependencies);
	pTaskBoxWidget->setLayout(m_pTaskListLayout);
	pTaskBoxBorderLayout->addChild(pTaskBoxWidget);
	pPercantagePane->addWidget(pTaskBoxBorderWidget, glm::vec2(0, 0), glm::vec2(1, 0.89));

	this->setLayout(pPercantagePane);
}

void TaskList::setTasks(const std::vector<TaskData>& tasksData) {
	std::cout << "TASKS DATA: " << tasksData.size() << std::endl;
    m_pTaskListLayout->setTasks(tasksData);
}


