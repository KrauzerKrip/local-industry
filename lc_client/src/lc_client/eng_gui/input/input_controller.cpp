#include "input_controller.h"


InputController::InputController(IInput* pInput) { m_pInput = pInput; }

void InputController::update() { 

	m_pInput->addKeyCallback()

	for (std::shared_ptr<InputReceiver> receiver : m_receivers) {
	}
}

void InputController::addReceiver(std::shared_ptr<InputReceiver> receiver) { m_receivers.push_back(receiver); }
