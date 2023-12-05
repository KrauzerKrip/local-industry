#pragma once

#include "lc_client/eng_gui/layout/layout_controller.h"
#include "lc_client/eng_gui/view/gui_presenter.h"
#include "lc_client/tier0/tier0.h"
#include "game/gui/dependencies_fabric/gui_dependencies_fabric.h"


class Gui {
public:
	Gui(Tier0* pTier0, GuiDependenciesFabric* pDependenciesFabric);
	~Gui();
	
	void update();
	GuiPresenter* getPresenter();

private:
	LayoutController overlayLayoutController;
	LayoutController layoutController;
	GuiPresenter* pGuiPresenter = nullptr;
};
