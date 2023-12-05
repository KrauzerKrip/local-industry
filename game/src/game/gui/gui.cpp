#include "gui.h"

#include "overlay/overlay.h"


Gui::Gui(Tier0* pTier0, GuiDependenciesFabric* pDependenciesFabric) { 
	std::vector<QueueRender*> queueRenders;

	pGuiPresenter = new GuiPresenter(&overlayLayoutController, &layoutController, queueRenders);

	std::shared_ptr<Overlay> overlay = std::make_shared<Overlay>(pTier0, pDependenciesFabric);
	overlayLayoutController.setLayout(overlay);
}

Gui::~Gui() { 
	delete pGuiPresenter; 
}

void Gui::update() {
	overlayLayoutController.update();
	//layoutController.update();
}

GuiPresenter* Gui::getPresenter() { return pGuiPresenter; }
