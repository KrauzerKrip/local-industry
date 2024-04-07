#pragma once

#include <entt/entt.hpp>

#include "lc_client/eng_gui/layout/layout_controller.h"
#include "lc_client/eng_gui/view/gui_presenter.h"
#include "lc_client/tier0/tier0.h"
#include "game/gui/dependencies_fabric/gui_dependencies_fabric.h"
#include "lc_client/eng_gui/input/input_controller.h"
#include "lc_client/eng_input/i_input.h"
#include "game/control/action_control.h"
#include "lc_client/eng_graphics/graphics_settings.h"
#include "machine_inspector/machine_inspector_view.h"
#include "machine_inspector/machine_inspector_controller.h"
#include "lc_client/eng_graphics/camera/camera.h"



class Gui {
public:
	Gui(Tier0* pTier0, GuiDependenciesFabric* pDependenciesFabric, IInput* pInput, ActionControl* pActionControl,
		GraphicsSettings* pGraphicsSettings, Camera* pCamera, entt::registry* pRegistry);
	~Gui();
	
	void update();
	GuiPresenter* getPresenter();

private:
	LayoutController m_overlayLayoutController;
	LayoutController m_layoutController;
	InputController m_inputController;
	GuiPresenter* pGuiPresenter = nullptr;
	MachineInspectorView* m_pMachineInspectorView;
	MachineInspectorController* m_pMachineInspectorController;
};
