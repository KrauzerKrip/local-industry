#include "trade_menu_view.h"



TradeMenuView::TradeMenuView(GuiDependencies dependencies) : WindowWidget(dependencies) {
	m_purchasesScroll = 0;
	m_salesScroll = 0;

	m_activeTab = ActiveTab::PURCHASES;

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
	pVBox->setSpacing(10);

	this->setLabel("Trader");

	Widget* pTabsWidget = new Widget();
	pVBox->addChild(pTabsWidget);
	pTabsWidget->setSizePolicy(SizePolicy::FIXED);
	pTabsWidget->setSize(1, 32);
	HBox* pTabsBox = new HBox();
	pTabsWidget->setLayout(pTabsBox);
	pTabsBox->setBoxMode(BoxMode::STRETCH_WIDGETS);
	pTabsBox->setSpacing(5);
	
	Button* pPurchasesButton = new Button(dependencies);
	pTabsBox->addChild(pPurchasesButton);
	pPurchasesButton->setBackground(pDarkBackground);
	pPurchasesButton->setText("purchases");
	pPurchasesButton->setTextColor(255, 255, 255, 255);
	pPurchasesButton->setBackground(new ColorBackground(dependencies.pStyle->getColor("button"), dependencies));
	pPurchasesButton->setHoverBackground(
		new ColorBackground(dependencies.pStyle->getColor("button_hover"), dependencies));
	pPurchasesButton->setCallback([this]() { 
		if (m_activeTab == ActiveTab::PURCHASES) {
			return;
		}

		m_salesScroll = m_pScrollWidget->getVerticalScroll();
		m_pScrollWidget->setVerticalScroll(m_purchasesScroll);

		m_activeTab = ActiveTab::PURCHASES;

		m_pScrollWidget->clear();
		for (Widget* pWidget : m_purchaseScrollWidgets) {
			m_pScrollWidget->addWidget(pWidget);
			pWidget->showWithChildren();
		}
		for (Widget* pWidget : m_saleScrollWidgets) {
			pWidget->hideWithChildren();
		}
		});
	Button* pSalesButton = new Button(dependencies);
	pTabsBox->addChild(pSalesButton);
	pSalesButton->setBackground(pDarkBackground);
	pSalesButton->setText("sales");
	pSalesButton->setTextColor(255, 255, 255, 255);
	pSalesButton->setBackground(new ColorBackground(dependencies.pStyle->getColor("button"), dependencies));
	pSalesButton->setHoverBackground(new ColorBackground(dependencies.pStyle->getColor("button_hover"), dependencies));
	pSalesButton->setCallback([this]() {
		if (m_activeTab == ActiveTab::SALES) {
			return;
		}

		m_purchasesScroll = m_pScrollWidget->getVerticalScroll();
		m_pScrollWidget->setVerticalScroll(m_salesScroll);

		m_activeTab = ActiveTab::SALES;

		m_pScrollWidget->clear();
		for (Widget* pWidget : m_saleScrollWidgets) {
			m_pScrollWidget->addWidget(pWidget);
			pWidget->showWithChildren();
		}
		for (Widget* pWidget : m_purchaseScrollWidgets) {
			pWidget->hideWithChildren();
		}
	});

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
		m_purchaseSlots.push_back(pSlot);;
	}

	for (int i = 0; i < 10; i++) {
		TradeMenuSlot* pSlot = new TradeMenuSlot(dependencies);
		m_saleSlots.push_back(pSlot);
	}
}

void TradeMenuView::render() { 
	for (TradeMenuSlot* pSlot : m_purchaseSlots) {
		pSlot->setSize(this->getRectangle().m_size.x, this->getRectangle().m_size.y * 0.1);
	}
	for (TradeMenuSlot* pSlot : m_saleSlots) {
		pSlot->setSize(this->getRectangle().m_size.x, this->getRectangle().m_size.y * 0.1);
	}

	Widget::render();
}

void TradeMenuView::setPurchasesData(std::vector<OfferData> offersData) {
	m_purchaseScrollWidgets.clear();

	for (int i = 0; i < offersData.size(); i++) {
		const OfferData& data = offersData.at(i);
		TradeMenuSlot* pSlot = m_purchaseSlots.at(i);
		pSlot->setIcon(data.iconPath);
		pSlot->setPriceLabel(data.priceLabel);
		pSlot->setButtonLabel(data.buttonLabel);
		pSlot->setLabel(data.label);
		pSlot->setCallback(data.callback);

		m_purchaseScrollWidgets.push_back(pSlot);
	}
}

void TradeMenuView::setSalesData(std::vector<OfferData> offersData) {
	m_saleScrollWidgets.clear();

	for (int i = 0; i < offersData.size(); i++) {
		const OfferData& data = offersData.at(i);
		TradeMenuSlot* pSlot = m_saleSlots.at(i);
		pSlot->setIcon(data.iconPath);
		pSlot->setPriceLabel(data.priceLabel);
		pSlot->setButtonLabel(data.buttonLabel);
		pSlot->setLabel(data.label);
		pSlot->setCallback(data.callback);

		m_saleScrollWidgets.push_back(pSlot);
	}
}

void TradeMenuView::show() { 
	m_pScrollWidget->setVerticalScroll(0);
	m_purchasesScroll = 0;
	m_salesScroll = 0;

	m_activeTab = ActiveTab::PURCHASES;

	m_pScrollWidget->clear();
	for (Widget* pWidget : m_purchaseScrollWidgets) {
		m_pScrollWidget->addWidget(pWidget);
		pWidget->showWithChildren();
	}
	for (Widget* pWidget : m_saleScrollWidgets) {
		pWidget->hideWithChildren();
	}

	WindowWidget::show();
}
