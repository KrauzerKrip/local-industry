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
	GLFWwindow* getGlfwWindow();
	void addKeyCallback(int glfwKey, std::function<void()> callback);
	std::unordered_map<int, std::function<void()>>& getCallbacks();
	int* getSize();
	void setSize(int width, int height);
	int* getAspectRatio();
	float getFov();
	void setFov(float fov);
	
	static ConsoleGui* m_pConsoleGui;

	inline static auto keyCallback(GLFWwindow* window, int key, int scancode, int action, int mods) -> void {
		WindowGL* pWindow = static_cast<WindowGL*>(glfwGetWindowUserPointer(window));



		if (key == GLFW_KEY_GRAVE_ACCENT && action == GLFW_PRESS) {
			
			if (m_pConsoleGui != nullptr) {
				if (m_pConsoleGui->isOpened()) {
					m_pConsoleGui->close();
				}
				else {
					m_pConsoleGui->open();
				}
			}
		}
	}

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