#include "trade_menu_view.h"



TradeMenuView::TradeMenuView(GuiDependencies dependencies) : WindowWidget(dependencies) {
	Background* pBaseBlurBackground = new BlurBackground(dependencies.pStyle->getColor("blur_background_base"),
		dependencies.pStyle->getBlurIntensity("base"), dependencies);
	ColorBackground* pBaseBackground =
		new ColorBackground(dependencies.pStyle->getColor("background_base"), dependencies);
	ColorBackground* pDarkBackground =
		new ColorBackground(dependencies.pStyle->getColor("background_dark"), dependencies);

	this->setPosition(200, 200);
	this->setSize(480, 720);
	this->setBackground(pBaseBlurBackground);

	VBox* pVBox = new VBox();
	pVBox->setMode(BoxMode::STRETCH_WIDGETS);
	this->setContentLayout(pVBox);
	pVBox->setPadding(5, 0);

	this->setLabel("Trader");

	m_pScrollWidget = new ScrollWidget(dependencies);
	pVBox->addChild(m_pScrollWidget);
	m_pScrollWidget->setSize(480, 720);
	m_pScrollWidget->setSizePolicy(SizePolicy::FIXED);
	
	m_pScrollWidget->setScrollbarBackground(
		new ColorBackground(dependencies.pStyle->getColor("background_dark"), dependencies));
	m_pScrollWidget->setScrollThumbBackground(pBaseBackground);
	m_pScrollWidget->setHoverScrollThumbBackground(pDarkBackground);
	m_pScrollWidget->enableVoidThumb();
	m_pScrollWidget->setScrollSpeed(20.0f);
	
	for (int i = 0; i < 10; i++) {
		TradeMenuSlot* pSlot = new TradeMenuSlot(dependencies);
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
	m_pScrollWidget->clear();

	for (int i = 0; i < offersData.size(); i++) {
		const OfferData& data = offersData.at(i);
		TradeMenuSlot* pSlot = m_slots.at(i);
		pSlot->setIcon(data.iconPath);
		pSlot->setPriceLabel(data.priceLabel);
		pSlot->setButtonLabel(data.buttonLabel);
		pSlot->setLabel(data.label);
		pSlot->setCallback(data.callback);

		m_pScrollWidget->addWidget(pSlot);
	}
}
