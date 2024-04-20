#include "trade_menu_slot.h"

TradeMenuSlot::TradeMenuSlot(GuiDependencies dependencies) : m_dependencies(dependencies) { 
	this->setBackground(new ColorBackground(dependencies.pStyle->getColor("background_dark"), dependencies));

	m_pIcon = new Widget();
	m_pIcon->setSize(70, 70);
	m_pLabel = new TextWidget(dependencies);
	m_pLabel->setTextColor(255, 255, 255, 255);
	m_pLabel->setTextSize(32);
	m_pQuantity = new TextWidget(dependencies);
	m_pQuantity->setTextColor(255, 255, 255, 255);
	m_pPrice = new TextWidget(dependencies);
	m_pPrice->setTextColor(255, 255, 255, 255);
	m_pButton = new Button(dependencies);
	m_pButton->setSize(64, 48);
	m_pButton->setTextColor(255, 255, 255, 255);
	m_pButton->setBackground(new ColorBackground(dependencies.pStyle->getColor("background_dark"), dependencies));
	m_pButton->setCallback([]() {});

	HBox* pHBox = new HBox();
	this->setLayout(pHBox);
	pHBox->setBoxMode(BoxMode::STRETCH_SPACING);
	pHBox->setPadding(5, 5);

	pHBox->addChild(m_pIcon);
	pHBox->addChild(m_pLabel);

	Widget* pVBoxWidget = new Widget();
	pHBox->addChild(pVBoxWidget);
	pVBoxWidget->setSize(64, 64);
	VBox* pVBox = new VBox();
	pVBoxWidget->setLayout(pVBox);
	pVBox->addChild(m_pPrice);
	pVBox->addChild(m_pButton);
}

void TradeMenuSlot::setIcon(std::string path) { 
	if (m_pIcon->getBackground() != nullptr) {
		delete m_pIcon->getBackground();
	};
	m_pIcon->setBackground(new ImageBackground(path, m_dependencies));
}

void TradeMenuSlot::setLabel(std::string label) { m_pLabel->setText(label); }

void TradeMenuSlot::setButtonLabel(std::string buttonLabel) { m_pButton->setText(buttonLabel); }

void TradeMenuSlot::setPriceLabel(std::string price) { m_pPrice->setText(price); }

void TradeMenuSlot::setCallback(std::function<void()> callback) { m_pButton->setCallback(callback); }
