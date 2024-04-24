#include "window_widget.h"
 
#include "lc_client/eng_gui/includes.h"


WindowWidget::WindowWidget(GuiDependencies dependencies) { 
	VBox* pVBox = new VBox();
	this->setLayout(pVBox);
	pVBox->setMode(BoxMode::STRETCH_WIDGETS);
	pVBox->setSpacing(5);

	Widget* pDecorationsWidget = new Widget();
	pVBox->addChild(pDecorationsWidget);
	pDecorationsWidget->setSize(1, 32);
	pDecorationsWidget->setSizePolicy(SizePolicy::FIXED);
	pDecorationsWidget->setBackground(
		new ColorBackground(dependencies.pStyle->getColor("background_dark"), dependencies));

	HBox* pHBox = new HBox();
	pDecorationsWidget->setLayout(pHBox);
	pHBox->setBoxMode(BoxMode::STRETCH_SPACING);

	m_pLabel = new TextWidget(dependencies);
	pHBox->addChild(m_pLabel);
	m_pLabel->setSize(72, 32);
	m_pLabel->setTextColor(255, 255, 255, 255);
	Button* pButton = new Button(dependencies);
	pHBox->addChild(pButton);
	pButton->setSize(32, 32);
	pButton->setBackground(new ImageBackground("game/gui/icons/close", dependencies));
	pButton->setCallback([this]() { this->hideWithChildren(); });

	m_pContentSpaceWidget = new Widget();
	pVBox->addChild(m_pContentSpaceWidget);
}

void WindowWidget::setLabel(std::string label) { 
	m_pLabel->setText(label);
}

void WindowWidget::setContentLayout(Layout* pLayout) {
	m_pContentSpaceWidget->setLayout(pLayout);
}

void WindowWidget::render() {
	m_pLabel->setSize(this->getSize().x - 32, 32);

	Widget::render();
}
