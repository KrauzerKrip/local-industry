#include "gui.h"

#include "lc_client/eng_gui/layout/layouts/anchor_pane.h"
#include "lc_client/eng_gui/layout/layouts/percentage_pane.h"
#include "overlay/overlay.h"
#include "machine_menu/machine_build_menu.h"
#include "side_menu/side_menu.h"
#include "lc_client/eng_gui/widgets/button.h"
#include "trade_menu/trade_menu_view.h"


Gui::Gui(GuiPresenter* pGuiPresenter, Tier0* pTier0, GuiDependenciesFabric* pDependenciesFabric, IInput* pInput,
	ActionControl* pActionControl,
	GraphicsSettings* pGraphicsSettings, Camera* pCamera, entt::registry* pRegistry)
	: m_inputController(pInput) { 
	GuiDependencies dependencies = pDependenciesFabric->getDependencies();

	m_pMachineInspectorView = new MachineInspectorView(dependencies);
	m_pMachineInspectorController =
		new MachineInspectorController(m_pMachineInspectorView, pGraphicsSettings, pCamera, pRegistry);
	m_pInventoryView = new InventoryView(dependencies);
	m_pInventoryController = new InventoryController(m_pInventoryView, pGraphicsSettings, pCamera, pRegistry);

	std::vector<QueueRender*> queueRenders;

	Overlay* pOverlay = new Overlay(pTier0, pDependenciesFabric, pInput, pCamera);
	m_overlayLayoutController.setLayout(pOverlay);

	Frame* pFrame = new Frame();
	m_layoutController.setLayout(pFrame);

	pGuiPresenter->setDependencies(dependencies, &m_overlayLayoutController, &m_layoutController);

	MachineBuildMenu* pMachineBuildMenu = new MachineBuildMenu(pActionControl, pFrame, dependencies, pRegistry);
	pFrame->addChild(pMachineBuildMenu);

	PercentagePane* pPercentagePane = new PercentagePane();

	TaskMenu* pTaskMenu = new TaskMenu(pRegistry, dependencies); 
	glm::vec2 taskMenuPercentagePosition(0.045, 0.25);
	glm::vec2 taskMenuPercentageSize(0.25, 0.70);
	SideMenu* pSideMenu = new SideMenu(pTaskMenu, dependencies);
	glm::vec2 sideMenuPercentagePosition(0, 0.65);
	glm::vec2 sideMenuPercentageSize(0.04, 0.25);
	pPercentagePane->addWidget(pTaskMenu, taskMenuPercentagePosition, taskMenuPercentageSize);
	pPercentagePane->addWidget(pSideMenu, sideMenuPercentagePosition, sideMenuPercentageSize);
	m_pPercentagePaneWidget = new Widget(dependencies);
	m_pPercentagePaneWidget->setLayout(pPercentagePane);
	m_pPercentagePaneWidget->setPosition(0, 0);
	pSideMenu->showWithChildren();
	pFrame->addChild(m_pPercentagePaneWidget);

	TradeMenuView* pTradeMenuView = new TradeMenuView(dependencies);
	m_pTradeMenuController = new TradeMenuController(pTradeMenuView, pRegistry);
	glm::vec2 tradeMenuPercentagePosition(0.33, 0.14);
	glm::vec2 tradeMenuPercentageSize(0.33, 0.75);
	pPercentagePane->addWidget(pTradeMenuView, tradeMenuPercentagePosition, tradeMenuPercentageSize);

	//std::shared_ptr<Button> button = std::make_shared<Button>(pDependenciesFabric->getTextWidgetDependecies());
	//button->setSize(glm::vec2(200, 100));
	//button->setPosition(glm::vec2(20, 960));
	//button->setBackground(Background(glm::vec4(0, 0, 0, 0.5)));
	//button->setText("Exit");
	//button->setTextSize(48);
	//button->setTextColor(glm::vec4(1, 1, 1, 1));
	//frame->addChild(button);
	//button->show();

	//m_inputController.addReceiver(button);
}

Gui::~Gui() { 
	delete pGuiPresenter; 
}

void Gui::setSize(unsigned int width, unsigned int height) { m_pPercentagePaneWidget->setSize(width, height); }

void Gui::update() {
	m_overlayLayoutController.update();
	m_layoutController.update();
	m_inputController.update();

	m_pMachineInspectorController->input();
	m_pMachineInspectorView->frame();
	m_pInventoryController->input();
	m_pInventoryView->frame();
	m_pTradeMenuController->input();
}

GuiPresenter* Gui::getPresenter() { return pGuiPresenter; }
