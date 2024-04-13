#include "gui.h"

#include "lc_client/eng_gui/layout/layouts/anchor_pane.h"
#include "lc_client/eng_gui/layout/layouts/percentage_pane.h"
#include "overlay/overlay.h"
#include "machine_menu/machine_build_menu.h"
#include "side_menu/side_menu.h"
#include "lc_client/eng_gui/widgets/button.h"


Gui::Gui(GuiPresenter* pGuiPresenter, Tier0* pTier0, GuiDependenciesFabric* pDependenciesFabric, IInput* pInput,
	ActionControl* pActionControl,
	GraphicsSettings* pGraphicsSettings, Camera* pCamera, entt::registry* pRegistry)
	: m_inputController(pInput) { 
	GuiDependencies dependencies = pDependenciesFabric->getDependencies();

	m_pMachineInspectorView = new MachineInspectorView(dependencies);
	m_pMachineInspectorController =
		new MachineInspectorController(m_pMachineInspectorView, pGraphicsSettings, pCamera, pRegistry);

	std::vector<QueueRender*> queueRenders;

	Overlay* pOverlay = new Overlay(pTier0, pDependenciesFabric, pInput);
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
	Widget* pPercentagePaneWidget = new Widget(dependencies);
	pPercentagePaneWidget->setLayout(pPercentagePane);
	pPercentagePaneWidget->setPosition(0, 0);
	pPercentagePaneWidget->setSize(1920, 1080);
	pSideMenu->showWithChildren();
	pFrame->addChild(pPercentagePaneWidget);

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

void Gui::update() {
	m_overlayLayoutController.update();
	m_layoutController.update();
	m_inputController.update();

	m_pMachineInspectorController->input();
	m_pMachineInspectorView->frame();
}

GuiPresenter* Gui::getPresenter() { return pGuiPresenter; }
