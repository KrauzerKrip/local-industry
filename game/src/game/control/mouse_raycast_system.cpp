#include "mouse_raycast_system.h"



MouseRaycastSystem::MouseRaycastSystem(
	MouseRaycast* pMouseRaycast, ActionControl* pActionControl, PointerOverGui* pPointerOverGui) {
	m_pMouseRaycast = pMouseRaycast;
	m_pActionControl = pActionControl;
	m_pPointerOverGui = pPointerOverGui;
}

void MouseRaycastSystem::input() {
	//result will be acquired in the after the update
	RaycastResult result = m_pMouseRaycast->doMouseRaycast();
	if (result.entityIntersectedWith.has_value()) {
		for (MouseRaycastObserver* pObserver : m_observers) {
			pObserver->onMouseMove(result.entityIntersectedWith.value(), 
				result.intersectionPoint.value(), 
				result.intersectionDistance.value());
		}
	}
}

void MouseRaycastSystem::addObserver(std::string action, MouseRaycastObserver* pObserver) { 
	m_observers.push_back(pObserver);

	m_pActionControl->addActionCallback(action, [=]() { onAction(action, pObserver); });
}

void MouseRaycastSystem::removeObserver(MouseRaycastObserver* pObserver) { 
	for (auto i = m_observers.begin(); i != m_observers.end(); ++i) {
		if (*i == pObserver) {
			m_observers.erase(i);
		}
	}
}

void MouseRaycastSystem::onAction(std::string action, MouseRaycastObserver* pObserver) {
	if (m_pPointerOverGui->isPointerOverGui()) {
		return;
	}

	RaycastResult result = m_pMouseRaycast->doMouseRaycast();

	if (result.entityIntersectedWith.has_value()) {
		//for (MouseRaycastObserver* pObserver : m_observers) {
			pObserver->onAction(action, result.entityIntersectedWith.value(), result.intersectionPoint.value(),
				result.intersectionDistance.value());
		//}
	}
}
