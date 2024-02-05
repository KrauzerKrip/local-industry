#include "glfw_input.h"

#include "GLFW/glfw3.h"

#include "lc_client/exceptions/input_exceptions.h"


InputGlfw::InputGlfw() {
	m_keyMap.emplace(KeyCode::MOUSE_BUTTON_LEFT, GLFW_MOUSE_BUTTON_LEFT);
	m_keyMap.emplace(KeyCode::MOUSE_BUTTON_RIGHT, GLFW_MOUSE_BUTTON_RIGHT);
	m_keyMap.emplace(KeyCode::MOUSE_BUTTON_MIDDLE, GLFW_MOUSE_BUTTON_MIDDLE);
	
	m_keyMap.emplace(KeyCode::A, GLFW_KEY_A);
	m_keyMap.emplace(KeyCode::B, GLFW_KEY_B);
	m_keyMap.emplace(KeyCode::C, GLFW_KEY_C);
	m_keyMap.emplace(KeyCode::D, GLFW_KEY_D);
	m_keyMap.emplace(KeyCode::E, GLFW_KEY_E);
	m_keyMap.emplace(KeyCode::F, GLFW_KEY_F);
	m_keyMap.emplace(KeyCode::G, GLFW_KEY_G);
	m_keyMap.emplace(KeyCode::H, GLFW_KEY_H);
	m_keyMap.emplace(KeyCode::I, GLFW_KEY_I);
	m_keyMap.emplace(KeyCode::J, GLFW_KEY_J);
	m_keyMap.emplace(KeyCode::K, GLFW_KEY_K);
	m_keyMap.emplace(KeyCode::L, GLFW_KEY_L);
	m_keyMap.emplace(KeyCode::M, GLFW_KEY_M);
	m_keyMap.emplace(KeyCode::N, GLFW_KEY_N);
	m_keyMap.emplace(KeyCode::O, GLFW_KEY_O);
	m_keyMap.emplace(KeyCode::P, GLFW_KEY_P);
	m_keyMap.emplace(KeyCode::Q, GLFW_KEY_Q);
	m_keyMap.emplace(KeyCode::R, GLFW_KEY_R);
	m_keyMap.emplace(KeyCode::S, GLFW_KEY_S);
	m_keyMap.emplace(KeyCode::T, GLFW_KEY_T);
	m_keyMap.emplace(KeyCode::U, GLFW_KEY_U);
	m_keyMap.emplace(KeyCode::V, GLFW_KEY_V);
	m_keyMap.emplace(KeyCode::W, GLFW_KEY_W);
	m_keyMap.emplace(KeyCode::X, GLFW_KEY_X);
	m_keyMap.emplace(KeyCode::Y, GLFW_KEY_Y);
	m_keyMap.emplace(KeyCode::Z, GLFW_KEY_Z);

	m_keyMap.emplace(KeyCode::ESC, GLFW_KEY_ESCAPE);
	m_keyMap.emplace(KeyCode::SPACE, GLFW_KEY_SPACE);
	m_keyMap.emplace(KeyCode::LEFT_SHIFT, GLFW_KEY_LEFT_SHIFT);
	m_keyMap.emplace(KeyCode::LEFT_CTRL, GLFW_KEY_LEFT_CONTROL);

	m_keyMap.emplace(KeyCode::GRAVE_ACCENT, GLFW_KEY_GRAVE_ACCENT);

	m_keyMap.emplace(KeyCode::F1, GLFW_KEY_F1);
	m_keyMap.emplace(KeyCode::F2, GLFW_KEY_F2);
	m_keyMap.emplace(KeyCode::F3, GLFW_KEY_F3);
	m_keyMap.emplace(KeyCode::F4, GLFW_KEY_F4);
	m_keyMap.emplace(KeyCode::F5, GLFW_KEY_F5);
	m_keyMap.emplace(KeyCode::F6, GLFW_KEY_F6);
	m_keyMap.emplace(KeyCode::F7, GLFW_KEY_F7);
	m_keyMap.emplace(KeyCode::F8, GLFW_KEY_F8);
	m_keyMap.emplace(KeyCode::F9, GLFW_KEY_F9);
	m_keyMap.emplace(KeyCode::F10, GLFW_KEY_F10);
	m_keyMap.emplace(KeyCode::F11, GLFW_KEY_F11);
	m_keyMap.emplace(KeyCode::F12, GLFW_KEY_F12);

	for (auto& [k, v] : m_keyMap) {
		m_keyStates.emplace(k, false);
	}

	m_mousePosition = glm::vec2(0);
	m_mouseWheelOffset = glm::vec2(0);
}

InputGlfw::~InputGlfw() {};

bool InputGlfw::isKeyPressed(KeyCode key) {
	if (m_keyStates.at(key) == true) {
		return true;
	}
	else {
		return false;
	}
}

glm::vec2 InputGlfw::getMousePosition() { return m_mousePosition; }

glm::vec2 InputGlfw::getMouseWheelOffset() { return m_mouseWheelOffset; }

void InputGlfw::addKeyCallback(std::function<void(KeyCode)> callback) { m_keyCallbacks.push_back(callback); }

void InputGlfw::addMappedKeyCallback(KeyCode key, std::function<void()> callback) {
	if (m_mappedKeyCallbacks.find(key) == m_mappedKeyCallbacks.end()) {
		m_mappedKeyCallbacks.emplace(key, std::vector<std::function<void()>>());
	}
	
	m_mappedKeyCallbacks.at(key).push_back(callback);
}

void InputGlfw::addMouseCallback(std::function<void(glm::vec2)> callback) { m_mouseCallbacks.push_back(callback); }

void InputGlfw::addMouseWheelCallback(std::function<void(glm::vec2)> callback) {
	m_mouseWheelCallbacks.push_back(callback);
}

void InputGlfw::invokeKeyCallbacks(int key, int action) { 
	KeyCode keyCode;

	for (auto& [k, v] : m_keyMap) {
		if (v == key) {
			keyCode = k;
			break;
		}
	}

	if (action == GLFW_RELEASE) {
		m_keyStates[keyCode] = false;
	}

	if (action == GLFW_PRESS) {
		m_keyStates[keyCode] = true;

		for (auto& callback : m_keyCallbacks) {
			callback(keyCode);
		}

		for (auto& [key, callbacks] : m_mappedKeyCallbacks) {
			if (key == keyCode) {
				for (auto& callback : callbacks)
				callback();
			}
		}
	}
}

void InputGlfw::invokeMouseCallbacks(glm::vec2 position) {
	glm::vec2 pos = glm::vec2(position.x, (1080 - position.y));

	m_mousePosition = pos;

	for (auto& callback : m_mouseCallbacks) {
		callback(pos);
	}
}

void InputGlfw::invokeMouseWheelCallbacks(glm::vec2 offset) {
	m_mouseWheelOffset = offset;

	for (auto& callback : m_mouseWheelCallbacks) {
		callback(offset);
	}
}
