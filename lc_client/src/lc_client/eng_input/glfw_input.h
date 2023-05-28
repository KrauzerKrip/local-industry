#pragma once

#include <string>
#include <unordered_map>

#include <GLFW/glfw3.h>

#include "lc_client/eng_input/i_input.h"
#include "lc_client/eng_graphics/openGL/gl_window.h"


class InputGlfw : public IInput {
public:
	InputGlfw(WindowGL* pWindow);
	~InputGlfw();

	bool isKeyPressed(std::string key);
	double getMousePosX();
	double getMousePosY();
	void addKeyCallback(std::string key, std::function<void()> callback);

private: 
	std::unordered_map<std::string, int> m_keyMapping;

	WindowGL* m_pWindow;
	GLFWwindow* m_pGlfwWindow;

	double m_mouseOffsetX = 0;
	double m_mouseOffsetY = 0;

};