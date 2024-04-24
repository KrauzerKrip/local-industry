#include "trade_menu_view.h"


TradeMenuView::TradeMenuView(GuiDependencies dependencies) : WindowWidget(dependencies) {
	this->setPosition(200, 200);
	this->setSize(480, 720);
	Background* pBaseBackground = new BlurBackground(dependencies.pStyle->getColor("blur_background_base"),
		dependencies.pStyle->getBlurIntensity("base"), dependencies);
	this->setBackground(pBaseBackground);

	VBox* pVBox = new VBox();
	pVBox->setMode(BoxMode::STRETCH_WIDGETS);
	this->setContentLayout(pVBox);
	pVBox->setPadding(5, 0);

	this->setLabel("Trader");

	ScrollWidget* pOffersWidget = new ScrollWidget(dependencies);
	pOffersWidget->setSize(480, 720);
	pOffersWidget->setSizePolicy(SizePolicy::FIXED);
	pVBox->addChild(pOffersWidget);
	
	for (int i = 0; i < 5; i++) {
		TradeMenuSlot* pSlot = new TradeMenuSlot(dependencies);
		pOffersWidget->addWidget(pSlot);
		m_slots.push_back(pSlot);;
	}
}

void TradeMenuView::render() { 
	for (TradeMenuSlot* pSlot : m_slots) {
		pSlot->setSize(this->getRectangle().m_size.x, this->getRectangle().m_size.y * 0.1);
	}

	Widget::render();
}

void TradeMenuView::setData(std::vector<OfferData> offersData) {
	for (int i = 0; i < offersData.size(); i++) {
		const OfferData& data = offersData.at(i);
		TradeMenuSlot* pSlot = m_slots.at(i);
		pSlot->setIcon(data.iconPath);
		pSlot->setPriceLabel(data.priceLabel);
		pSlot->setButtonLabel(data.buttonLabel);
		pSlot->setLabel(data.label);
		pSlot->setCallback(data.callback);
	}
}
