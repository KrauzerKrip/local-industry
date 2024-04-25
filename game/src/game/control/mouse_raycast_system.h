#pragma once

#include <entt/entt.hpp>

#include "mouse_raycast_observer.h"
#include "mouse_raycast.h"
#include "lc_client/eng_gui/pointer_over_gui.h"


class MouseRaycastSystem {
public: 
	MouseRaycastSystem(MouseRaycast* pMouseRaycast, ActionControl* pActionControl, PointerOverGui* pPointerOverGui);

	void input();
	void addObserver(std::string action, MouseRaycastObserver* pObserver);
	void removeObserver(MouseRaycastObserver* pObserver);

private:
	void onAction(std::string action, MouseRaycastObserver* pObserver);

	MouseRaycast* m_pMouseRaycast = nullptr;
	ActionControl* m_pActionControl = nullptr;
	PointerOverGui* m_pPointerOverGui = nullptr;

	std::vector<MouseRaycastObserver*> m_observers;
};
