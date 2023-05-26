#include "glfw_input.h"
#include "glfw_input.h"

#include <GLFW/glfw3.h>

#include "lc_client/exceptions/input_exceptions.h"


InputGlfw::InputGlfw(WindowGL* pWindow) {
	m_pWindow = pWindow;
	m_pGlfwWindow = pWindow->getGlfwWindow();

	m_keyMapping.emplace("W", GLFW_KEY_W);
	m_keyMapping.emplace("A", GLFW_KEY_A);
	m_keyMapping.emplace("S", GLFW_KEY_S);
	m_keyMapping.emplace("D", GLFW_KEY_D);
	m_keyMapping.emplace("B", GLFW_KEY_B);

	m_keyMapping.emplace("ESC", GLFW_KEY_ESCAPE);
	m_keyMapping.emplace("SPACE", GLFW_KEY_SPACE);
	m_keyMapping.emplace("LEFT_SHIFT", GLFW_KEY_LEFT_SHIFT);
	m_keyMapping.emplace("LEFT_CTRL", GLFW_KEY_LEFT_CONTROL);

	m_keyMapping.emplace("F", GLFW_KEY_F);
}

InputGlfw::~InputGlfw() {};

bool InputGlfw::isKeyPressed(std::string key) {
	if (key == "W") {
		return glfwGetKey(m_pGlfwWindow, GLFW_KEY_W) == GLFW_PRESS;
	} 
	else if (key == "A") {
		return glfwGetKey(m_pGlfwWindow, GLFW_KEY_A) == GLFW_PRESS;
	}
	else if (key == "S") {
		return glfwGetKey(m_pGlfwWindow, GLFW_KEY_S) == GLFW_PRESS;
	}
	else if (key == "D") {
		return glfwGetKey(m_pGlfwWindow, GLFW_KEY_D) == GLFW_PRESS;
	}
	else if (key == "B") {
		return glfwGetKey(m_pGlfwWindow, GLFW_KEY_B) == GLFW_PRESS;
	}

	else if (key == "ESC") {
		return glfwGetKey(m_pGlfwWindow, GLFW_KEY_ESCAPE) == GLFW_PRESS;
	}
	else if (key == "SPACE") {
		return glfwGetKey(m_pGlfwWindow, GLFW_KEY_SPACE) == GLFW_PRESS;
	}
	else if (key == "LEFT_SHIFT") {
		return glfwGetKey(m_pGlfwWindow, GLFW_KEY_LEFT_SHIFT) == GLFW_PRESS;
	}
	else if (key == "LEFT_CTRL") {
		return glfwGetKey(m_pGlfwWindow, GLFW_KEY_LEFT_CONTROL) == GLFW_PRESS;
	}

	else {
		throw UnknownKeyCodeException(key);
	}
}

double InputGlfw::getMousePosX() {
	double xPos = 0;
	glfwGetCursorPos(m_pWindow->getGlfwWindow(), & xPos, NULL);
	return xPos;
}

double InputGlfw::getMousePosY() {
	double yPos = 0;
	glfwGetCursorPos(m_pWindow->getGlfwWindow(), NULL, &yPos);
	return yPos;
}

void InputGlfw::addKeyCallback(std::string key, std::function<void()> callback)  {

	try {
		int keyCode = m_keyMapping.at(key);
		m_pWindow->addKeyCallback(keyCode, callback);
	}
	catch (std::out_of_range&) {
		throw UnknownKeyCodeException(key);
	}

}
