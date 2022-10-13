#pragma once

#include "../../eng_graphics/i_window.h"

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <string>

class WindowGL : public IWindow {
public:

	WindowGL(std::string, int height, int width, bool vSync);
	virtual ~WindowGL();

	void init();
	void update();
	bool windowShouldClose();
	void terminateGlfw();

private:
	static void framebufferSizeCallback(GLFWwindow* window, int width, int height);

	GLFWwindow* m_glfwWindow;
	std::string m_title;
	int m_width;
	int m_height;
	bool m_vSync;
};