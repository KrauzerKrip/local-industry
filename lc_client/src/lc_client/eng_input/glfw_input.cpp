#include "glfw_input.h"

#include <GLFW/glfw3.h>

#include "lc_client/exceptions/input_exceptions.h"


InputGlfw::InputGlfw(IWindow* pWindow) {
	m_pWindow = pWindow;
	m_pGlfwWindow = pWindow->getGlfwWindow();
}

InputGlfw::~InputGlfw() {};

bool InputGlfw::isKeyPressed(const char* key) {
	if (*key == 'W') {
		return glfwGetKey(m_pGlfwWindow, GLFW_KEY_W) == GLFW_PRESS;
	} 
	else if (*key == 'A') {
		return glfwGetKey(m_pGlfwWindow, GLFW_KEY_A) == GLFW_PRESS;
	}
	else if (*key == 'S') {
		return glfwGetKey(m_pGlfwWindow, GLFW_KEY_S) == GLFW_PRESS;
	}
	else if (*key == 'D') {
		return glfwGetKey(m_pGlfwWindow, GLFW_KEY_D) == GLFW_PRESS;
	}
	else if (*key == 'E') {
		return glfwGetKey(m_pGlfwWindow, GLFW_KEY_ESCAPE) == GLFW_PRESS;
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
