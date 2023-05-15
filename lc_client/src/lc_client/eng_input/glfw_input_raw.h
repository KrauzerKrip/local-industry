#pragma once

#include <string>
#include <GLFW/glfw3.h>

#include "lc_client/eng_input/i_input_raw.h"
#include "lc_client/eng_graphics/i_window.h"

class InputGlfw : public IInputRaw {
public:
	InputGlfw(IWindow* pWindow);
	~InputGlfw();

	bool isKeyPressed(std::string key);
	double getMousePosX();
	double getMousePosY();

private: 
	IWindow* m_pWindow;
	GLFWwindow* m_pGlfwWindow;

	double m_mouseOffsetX = 0;
	double m_mouseOffsetY = 0;

};