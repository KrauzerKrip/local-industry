#include "input_controller.h"


InputController::InputController(IInput* pInput) { 
	m_pInput = pInput;
	
	m_pInput->addMappedKeyCallback(KeyCode::MOUSE_BUTTON_LEFT, [this]() {
		for (std::shared_ptr<InputReceiver> receiver : m_receivers) {
			receiver->mouseClick(MouseClickEvent(m_pInput->getMousePosition(), KeyCode::MOUSE_BUTTON_LEFT));
		}
	});

	m_pInput->addMappedKeyCallback(KeyCode::MOUSE_BUTTON_RIGHT, [this]() {
		for (std::shared_ptr<InputReceiver> receiver : m_receivers) {
			receiver->mouseClick(MouseClickEvent(m_pInput->getMousePosition(), KeyCode::MOUSE_BUTTON_RIGHT));
		}
	});

	m_pInput->addMouseWheelCallback([this](glm::vec2 vec) {
		for (std::shared_ptr<InputReceiver> receiver : m_receivers) {
			receiver->scroll(ScrollEvent(vec.y));
		}
	});
}

void InputController::update() { 

}

void InputController::addReceiver(std::shared_ptr<InputReceiver> receiver) { m_receivers.push_back(receiver); }

void InputController::addReceiver(InputReceiver* pReceiver) { addReceiver(std::shared_ptr<InputReceiver>(pReceiver));
 }
