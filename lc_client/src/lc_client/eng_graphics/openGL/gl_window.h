#pragma once

#include "lc_client/eng_graphics/i_window.h"

#include <unordered_map>
#include <functional>

#include <GLFW/glfw3.h>
#include <string>
#include <lc_client/eng_gui/gui_console.h>

static void framebufferSizeCallback(GLFWwindow* window, int width, int height);
static void mouseCallback(GLFWwindow* window, double x, double y);
static void keyCallback(GLFWwindow* window, int key, int scancode, int action, int mods);

class WindowGL : public IWindow {
public:

	WindowGL(std::string, int width, int height, int* aspectRatio, bool vSync, float fov);
	virtual ~WindowGL();

	void init();
	void update();
	void startFrame(); 
	bool windowShouldClose();
	void terminate();
	IInput* getInput();
	void setMode(WindowMode mode);
	WindowMode getMode();
	void setResizeCallback(std::function<void(int, int)> callback);

	GLFWwindow* getGlfwWindow();
	void addKeyCallback(int glfwKey, std::function<void()> callback);
	std::unordered_map<int, std::function<void()>>& getCallbacks();
	std::function<void(int, int)>& getResizeCallback();
	std::array<int, 2> getSize();
	void setSize(int width, int height);
	int* getAspectRatio();
	float getFov();
	void setFov(float fov);

	static void keyCallback(GLFWwindow* pGlfwWindow, int key, int scancode, int action, int mods);
	// static void framebufferSizeCallback(GLFWwindow* window, int width, int height);
	// static void mouseSizeCallback(GLFWwindow* window, double x, double y);

	bool m_debug = false;

private:


	friend void mouseCallback(GLFWwindow* window, double x, double y);

	std::unordered_map<int, std::function<void()>> m_callbacks;
	std::function<void(int, int)> m_resizeCallback;

	std::string m_title;
	int m_width;
	int m_height;
	int* m_pAspectRatio;
	bool m_vSync;
	float m_fov;
	double mouseOffsetX;
	double mouseOffsetY;
	WindowMode m_windowMode;

	GLFWwindow* m_pGlfwWindow;
	IInput* m_pInput;
};