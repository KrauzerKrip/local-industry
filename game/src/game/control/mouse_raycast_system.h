#pragma once

#include <entt/entt.hpp>

#include "mouse_raycast_observer.h"
#include "mouse_raycast.h"


class MouseRaycastSystem {
public: 
	MouseRaycastSystem(MouseRaycast* pMouseRaycast);

	void input();
	void addObserver(MouseRaycastObserver* pObserver);
	void removeObserver(MouseRaycastObserver* pObserver);

private:
	void onSelect();

	MouseRaycast* m_pMouseRaycast = nullptr;

	std::vector<MouseRaycastObserver*> m_observers;
};
