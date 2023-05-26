#pragma once

#include "lc_client/eng_graphics/i_window.h"

#include <unordered_map>
#include <functional>

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
	void addKeyCallback(int glfwKey, std::function<void()> callback);
	std::unordered_map<int, std::function<void()>>& getCallbacks();
	int* getSize();
	void setSize(int width, int height);
	int* getAspectRatio();
	float getFov();
	void setFov(float fov);

	static void keyCallback(GLFWwindow* pGlfwWindow, int key, int scancode, int action, int mods);
	// static void framebufferSizeCallback(GLFWwindow* window, int width, int height);
	// static void mouseSizeCallback(GLFWwindow* window, double x, double y);

private:

	friend void mouseCallback(GLFWwindow* window, double x, double y);

	std::unordered_map<int, std::function<void()>> m_callbacks;

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