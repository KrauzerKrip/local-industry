#pragma once

#include <entt/entt.hpp>

#include "mouse_raycast_observer.h"
#include "mouse_raycast.h"


class MouseRaycastSystem {
public: 
	MouseRaycastSystem(MouseRaycast* pMouseRaycast, ActionControl* pActionControl);

	void input();
	void addObserver(std::string action, MouseRaycastObserver* pObserver);
	void removeObserver(MouseRaycastObserver* pObserver);

private:
	void onAction(std::string action, MouseRaycastObserver* pObserver);

	MouseRaycast* m_pMouseRaycast = nullptr;
	ActionControl* m_pActionControl = nullptr;

	std::vector<MouseRaycastObserver*> m_observers;
};
