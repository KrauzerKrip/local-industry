#include "glfw_input.h"

#include <GLFW/glfw3.h>

#include "lc_client/exceptions/input_exceptions.h"


InputGlfw::InputGlfw(IWindow* pWindow) {
	m_pWindow = pWindow;
	m_pGlfwWindow = pWindow->getGlfwWindow();
}

InputGlfw::~InputGlfw(){};

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

	else if (key == "UP_ARROW") {
		return glfwGetKey(m_pGlfwWindow, GLFW_KEY_UP) == GLFW_PRESS;
	}
	else if (key == "LEFT_ARROW") {
		return glfwGetKey(m_pGlfwWindow, GLFW_KEY_LEFT) == GLFW_PRESS;
	}
	else if (key == "DOWN_ARROW") {
		return glfwGetKey(m_pGlfwWindow, GLFW_KEY_DOWN) == GLFW_PRESS;
	}
	else if (key == "RIGHT_ARROW") {
		return glfwGetKey(m_pGlfwWindow, GLFW_KEY_RIGHT) == GLFW_PRESS;
	}

	else if (key == "Q") {
		return glfwGetKey(m_pGlfwWindow, GLFW_KEY_Q) == GLFW_PRESS;
	}
	else if (key == "E") {
		return glfwGetKey(m_pGlfwWindow, GLFW_KEY_E) == GLFW_PRESS;
	}
	else if (key == "R") {
		return glfwGetKey(m_pGlfwWindow, GLFW_KEY_R) == GLFW_PRESS;
	}
	else if (key == "T") {
		return glfwGetKey(m_pGlfwWindow, GLFW_KEY_T) == GLFW_PRESS;
	}
	else if (key == "Y") {
		return glfwGetKey(m_pGlfwWindow, GLFW_KEY_Y) == GLFW_PRESS;
	}
	else if (key == "U") {
		return glfwGetKey(m_pGlfwWindow, GLFW_KEY_U) == GLFW_PRESS;
	}
	else if (key == "I") {
		return glfwGetKey(m_pGlfwWindow, GLFW_KEY_I) == GLFW_PRESS;
	}
	else if (key == "O") {
		return glfwGetKey(m_pGlfwWindow, GLFW_KEY_O) == GLFW_PRESS;
	}
	else if (key == "P") {
		return glfwGetKey(m_pGlfwWindow, GLFW_KEY_P) == GLFW_PRESS;
	}
	else if (key == "F") {
		return glfwGetKey(m_pGlfwWindow, GLFW_KEY_F) == GLFW_PRESS;
	}
	else if (key == "G") {
		return glfwGetKey(m_pGlfwWindow, GLFW_KEY_G) == GLFW_PRESS;
	}
	else if (key == "H") {
		return glfwGetKey(m_pGlfwWindow, GLFW_KEY_H) == GLFW_PRESS;
	}
	else if (key == "J") {
		return glfwGetKey(m_pGlfwWindow, GLFW_KEY_J) == GLFW_PRESS;
	}
	else if (key == "K") {
		return glfwGetKey(m_pGlfwWindow, GLFW_KEY_K) == GLFW_PRESS;
	}
	else if (key == "L") {
		return glfwGetKey(m_pGlfwWindow, GLFW_KEY_L) == GLFW_PRESS;
	}
	else if (key == "Z") {
		return glfwGetKey(m_pGlfwWindow, GLFW_KEY_Z) == GLFW_PRESS;
	}
	else if (key == "X") {
		return glfwGetKey(m_pGlfwWindow, GLFW_KEY_X) == GLFW_PRESS;
	}
	else if (key == "C") {
		return glfwGetKey(m_pGlfwWindow, GLFW_KEY_C) == GLFW_PRESS;
	}
	else if (key == "V") {
		return glfwGetKey(m_pGlfwWindow, GLFW_KEY_V) == GLFW_PRESS;
	}
	else if (key == "B") {
		return glfwGetKey(m_pGlfwWindow, GLFW_KEY_B) == GLFW_PRESS;
	}
	else if (key == "N") {
		return glfwGetKey(m_pGlfwWindow, GLFW_KEY_N) == GLFW_PRESS;
	}
	else if (key == "M") {
		return glfwGetKey(m_pGlfwWindow, GLFW_KEY_M) == GLFW_PRESS;
	}

	else if (key == "LEFT_BRACKET") {
		return glfwGetKey(m_pGlfwWindow, GLFW_KEY_LEFT_BRACKET) == GLFW_PRESS;
	}
	else if (key == "RIGHT_BRACKET") {
		return glfwGetKey(m_pGlfwWindow, GLFW_KEY_RIGHT_BRACKET) == GLFW_PRESS;
	}

	else if (key == "1") {
		return glfwGetKey(m_pGlfwWindow, GLFW_KEY_1) == GLFW_PRESS;
	}
	else if (key == "2") {
		return glfwGetKey(m_pGlfwWindow, GLFW_KEY_2) == GLFW_PRESS;
	}
	else if (key == "3") {
		return glfwGetKey(m_pGlfwWindow, GLFW_KEY_3) == GLFW_PRESS;
	}
	else if (key == "4") {
		return glfwGetKey(m_pGlfwWindow, GLFW_KEY_4) == GLFW_PRESS;
	}
	else if (key == "5") {
		return glfwGetKey(m_pGlfwWindow, GLFW_KEY_5) == GLFW_PRESS;
	}
	else if (key == "6") {
		return glfwGetKey(m_pGlfwWindow, GLFW_KEY_6) == GLFW_PRESS;
	}
	else if (key == "7") {
		return glfwGetKey(m_pGlfwWindow, GLFW_KEY_7) == GLFW_PRESS;
	}
	else if (key == "8") {
		return glfwGetKey(m_pGlfwWindow, GLFW_KEY_8) == GLFW_PRESS;
	}
	else if (key == "9") {
		return glfwGetKey(m_pGlfwWindow, GLFW_KEY_9) == GLFW_PRESS;
	}
	else if (key == "0") {
		return glfwGetKey(m_pGlfwWindow, GLFW_KEY_0) == GLFW_PRESS;
	}

	else if (key == "F1") {
		return glfwGetKey(m_pGlfwWindow, GLFW_KEY_F1) == GLFW_PRESS;
	}
	else if (key == "F2") {
		return glfwGetKey(m_pGlfwWindow, GLFW_KEY_F2) == GLFW_PRESS;
	}
	else if (key == "F3") {
		return glfwGetKey(m_pGlfwWindow, GLFW_KEY_F3) == GLFW_PRESS;
	}
	else if (key == "F4") {
		return glfwGetKey(m_pGlfwWindow, GLFW_KEY_F4) == GLFW_PRESS;
	}
	else if (key == "F5") {
		return glfwGetKey(m_pGlfwWindow, GLFW_KEY_F5) == GLFW_PRESS;
	}
	else if (key == "F6") {
		return glfwGetKey(m_pGlfwWindow, GLFW_KEY_F6) == GLFW_PRESS;
	}
	else if (key == "F7") {
		return glfwGetKey(m_pGlfwWindow, GLFW_KEY_F7) == GLFW_PRESS;
	}
	else if (key == "F8") {
		return glfwGetKey(m_pGlfwWindow, GLFW_KEY_F8) == GLFW_PRESS;
	}
	else if (key == "F9") {
		return glfwGetKey(m_pGlfwWindow, GLFW_KEY_F9) == GLFW_PRESS;
	}
	else if (key == "F10") {
		return glfwGetKey(m_pGlfwWindow, GLFW_KEY_F10) == GLFW_PRESS;
	}
	else if (key == "F11") {
		return glfwGetKey(m_pGlfwWindow, GLFW_KEY_F11) == GLFW_PRESS;
	}


	else {
		throw UnknownKeyCodeException(key);
	}
}

double InputGlfw::getMousePosX() {
	double xPos = 0;
	glfwGetCursorPos(m_pWindow->getGlfwWindow(), &xPos, NULL);
	return xPos;
}

double InputGlfw::getMousePosY() {
	double yPos = 0;
	glfwGetCursorPos(m_pWindow->getGlfwWindow(), NULL, &yPos);
	return yPos;
}
