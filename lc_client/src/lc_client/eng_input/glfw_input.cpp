#include "glfw_input.h"

#include "GLFW/glfw3.h"

#include "lc_client/exceptions/input_exceptions.h"


InputGlfw::InputGlfw() {
	m_keyMap.emplace(KeyCode::W, GLFW_KEY_W);
	m_keyMap.emplace(KeyCode::A, GLFW_KEY_A);
	m_keyMap.emplace(KeyCode::S, GLFW_KEY_S);
	m_keyMap.emplace(KeyCode::D, GLFW_KEY_D);
	m_keyMap.emplace(KeyCode::B, GLFW_KEY_B);

	m_keyMap.emplace(KeyCode::ESC, GLFW_KEY_ESCAPE);
	m_keyMap.emplace(KeyCode::SPACE, GLFW_KEY_SPACE);
	m_keyMap.emplace(KeyCode::LEFT_SHIFT, GLFW_KEY_LEFT_SHIFT);
	m_keyMap.emplace(KeyCode::LEFT_CTRL, GLFW_KEY_LEFT_CONTROL);

	m_keyMap.emplace(KeyCode::GRAVE_ACCENT, GLFW_KEY_GRAVE_ACCENT);

	for (auto& [k, v] : m_keyMap) {
		m_keyStates.emplace(k, false);
	}

	m_mousePosition = glm::vec2(0);
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

void InputGlfw::addKeyCallback(std::function<void(KeyCode)> callback) { m_keyCallbacks.push_back(callback); }

void InputGlfw::addMappedKeyCallback(KeyCode key, std::function<void()> callback) {
	m_mappedKeyCallbacks.emplace(key, callback);
}

void InputGlfw::addMouseClickCallback(std::function<void(glm::vec2)> callback) { m_mouseCallbacks.push_back(callback); }

void InputGlfw::invokeKeyCallbacks(int key, int action) { 
	KeyCode keyString;

	for (auto& [k, v] : m_keyMap) {
		if (v == key) {
			keyString = k;
		}
	}

	if (action == GLFW_RELEASE) {
		m_keyStates[keyString] = false;
	}

	if (action == GLFW_PRESS) {
		m_keyStates[keyString] = true;

		for (auto& callback : m_keyCallbacks) {
			callback(keyString);
		}

		for (auto& [key, callback] : m_mappedKeyCallbacks) {
			if (key == keyString) {
				callback();
			}
		}
	}
}

void InputGlfw::invokeMouseCallbacks(glm::vec2 position) {
	m_mousePosition = position;

	for (auto& callback : m_mouseCallbacks) {
		callback(position);
	}
}
