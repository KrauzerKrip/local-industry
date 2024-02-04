#include "task_view.h"

#include "lc_client/eng_gui/includes.h"


TaskView::TaskView(GuiDependencies dependencies) {
	this->setSize(1, 50);

	this->setBackground(new ColorBackground(120, 120, 120, 255, dependencies));

    HBox* pHBox = new HBox();
	pHBox->setBoxMode(BoxMode::STRETCH_WIDGETS);
	m_pLabel = new TextWidget(new ColorBackground(120, 120, 120, 255, dependencies), dependencies);
	m_pLabel->setTextSize(16);
	m_pLabel->setTextColor(255, 255, 255, 255);
	m_pLabel->setSize(70, 36);
	pHBox->addChild(m_pLabel);
	this->setLayout(pHBox);
}

void TaskView::setData(const TaskData& taskData) { m_pLabel->setText(taskData.name); }

