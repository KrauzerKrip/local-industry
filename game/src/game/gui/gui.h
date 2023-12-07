#pragma once

#include "lc_client/eng_gui/layout/layout_controller.h"
#include "lc_client/eng_gui/view/gui_presenter.h"
#include "lc_client/tier0/tier0.h"
#include "game/gui/dependencies_fabric/gui_dependencies_fabric.h"
#include "lc_client/eng_gui/input/input_controller.h"
#include "lc_client/eng_input/i_input.h"

class Gui {
public:
	Gui(Tier0* pTier0, GuiDependenciesFabric* pDependenciesFabric, IInput* pInput);
	~Gui();
	
	void update();
	GuiPresenter* getPresenter();

private:
	LayoutController m_overlayLayoutController;
	LayoutController m_layoutController;
	InputController m_inputController;
	GuiPresenter* pGuiPresenter = nullptr;
};
