#pragma once

#include "lc_client/eng_graphics/i_window.h"

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <string>

class WindowGL : public IWindow {
public:

	WindowGL(std::string, int width, int height, int* aspectRatio, bool vSync);
	virtual ~WindowGL();

	void init();
	void update();
	bool windowShouldClose();
	void terminate();
	IInput* getInput();
	bool isKeyPressed(int key);
	int* getSize();
	void setSize(int width, int height);
	int* getAspectRatio();

private:
	static void framebufferSizeCallback(GLFWwindow* window, int width, int height);

	std::string m_title;
	int m_width;
	int m_height;
	int* m_pAspectRatio;
	bool m_vSync; 

	GLFWwindow* m_pGlfwWindow;
	IInput* m_pInput;
};