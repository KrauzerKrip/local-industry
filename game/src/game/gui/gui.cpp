#include "gui.h"

#include "overlay/overlay.h"

#include "lc_client/eng_gui/widgets/button.h"


Gui::Gui(Tier0* pTier0, GuiDependenciesFabric* pDependenciesFabric, IInput* pInput) : m_inputController(pInput) { 
	std::vector<QueueRender*> queueRenders;

	pGuiPresenter = new GuiPresenter(&m_overlayLayoutController, &m_layoutController, queueRenders);

	std::shared_ptr<Overlay> overlay = std::make_shared<Overlay>(pTier0, pDependenciesFabric, pInput);
	m_overlayLayoutController.setLayout(overlay);


	std::shared_ptr<Frame> frame = std::make_shared<Frame>();
	m_layoutController.setLayout(frame);

	std::shared_ptr<Button> button = std::make_shared<Button>(pDependenciesFabric->getWidgetDependencies());
	button->setSize(glm::vec2(200, 100));
	button->setPosition(glm::vec2(500, 500));
	button->setBackground(Background(glm::vec4(0, 0, 0, 1)));
	frame->addChild(button);
	button->show();

	m_inputController.addReceiver(button);
}

Gui::~Gui() { 
	delete pGuiPresenter; 
}

void Gui::update() {
	m_overlayLayoutController.update();
	m_layoutController.update();
	m_inputController.update();
}

GuiPresenter* Gui::getPresenter() { return pGuiPresenter; }
