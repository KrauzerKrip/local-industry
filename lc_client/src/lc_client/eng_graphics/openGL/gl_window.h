#pragma once

#include "lc_client/eng_graphics/i_window.h"

#include <GLFW/glfw3.h>
#include <string>

static void framebufferSizeCallback(GLFWwindow* window, int width, int height);
static void mouseCallback(GLFWwindow* window, double x, double y);

class WindowGL : public IWindow {
public:

	WindowGL(std::string, int width, int height, int* aspectRatio, bool vSync, float fov);
	virtual ~WindowGL();

	void init();
	void update();
	bool windowShouldClose();
	void terminate();
	IInput* getInput();
	GLFWwindow* getGlfwWindow();
	int* getSize();
	void setSize(int width, int height);
	int* getAspectRatio();
	float getFov();
	void setFov(float fov);

private:
	//static void framebufferSizeCallback(GLFWwindow* window, int width, int height);
	//static void mouseSizeCallback(GLFWwindow* window, double x, double y);

	friend void mouseCallback(GLFWwindow* window, double x, double y);

	std::string m_title;
	int m_width;
	int m_height;
	int* m_pAspectRatio;
	bool m_vSync;
	float m_fov;
	double mouseOffsetX;
	double mouseOffsetY;

	GLFWwindow* m_pGlfwWindow;
	IInput* m_pInput;
};