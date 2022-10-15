#include "glfw_input.h"

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "lc_client/exceptions/input_exceptions.h"


InputGlfw::InputGlfw(IWindow* pWindow) {
	m_pWindow = pWindow;
}

InputGlfw::~InputGlfw() {};

bool InputGlfw::getKeyPressed(const char* key) {
	if (key == "W") {
		return m_pWindow->isKeyPressed(GLFW_KEY_W);
	} 
	else if (key == "A") {
		return m_pWindow->isKeyPressed(GLFW_KEY_A);
	}
	else if (key == "S") {
		return m_pWindow->isKeyPressed(GLFW_KEY_S);
	}
	else if (key == "D") {
		return m_pWindow->isKeyPressed(GLFW_KEY_D);
	}
	else {
		throw UnknownKeyCode(key);
	}
}