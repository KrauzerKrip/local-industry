#include "task_view.h"

#include "lc_client/eng_gui/includes.h"


TaskView::TaskView(GuiDependencies dependencies) {
	BlurBackground* pBaseBlurBackground = new BlurBackground(dependencies.pStyle->getColor("blur_background_base"),
		dependencies.pStyle->getBlurIntensity("base"), dependencies);
	BlurBackground* pDarkBlurBackground = new BlurBackground(dependencies.pStyle->getColor("blur_background_dark"),
		dependencies.pStyle->getBlurIntensity("base"), dependencies);
	ColorBackground* pDarkBackground =
		new ColorBackground(dependencies.pStyle->getColor("background_dark"), dependencies);

	this->setSize(1, 50);

	this->setBackground(pBaseBlurBackground);

    HBox* pHBox = new HBox();
	pHBox->setBoxMode(BoxMode::STRETCH_WIDGETS);
	m_pLabel = new TextWidget(pBaseBlurBackground, dependencies);
	m_pLabel->setTextSize(16);
	m_pLabel->setTextColor(255, 255, 255, 255);
	m_pLabel->setSize(70, 36);
	pHBox->addChild(m_pLabel);
	this->setLayout(pHBox);
}

void TaskView::setPurchasesData(const TaskData& taskData) { m_pLabel->setText(taskData.name); }

