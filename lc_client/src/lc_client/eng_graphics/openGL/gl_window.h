#pragma once

#include "lc_client/eng_graphics/i_window.h"

#include <unordered_map>
#include <functional>
#include <string>
#include <glm/glm.hpp>

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <lc_client/eng_gui/gui_console.h>
#include "lc_client/eng_input/glfw_input.h"


static void framebufferSizeCallback(GLFWwindow* window, int width, int height);
static void mouseCallback(GLFWwindow* window, double x, double y);
static void keyCallback(GLFWwindow* window, int key, int scancode, int action, int mods);
static void GLAPIENTRY messageCallback(GLenum source, GLenum type, GLuint id, GLenum severity, GLsizei length,
	const GLchar* message, const void* userParam);


class WindowGL : public IWindow {
public:

	WindowGL(std::string, int width, int height, int* aspectRatio);
	virtual ~WindowGL();

	void init();
	void update();
	void startFrame(); 
	bool windowShouldClose();
	void terminate();
	InputGlfw* getInput();
	void setMode(WindowMode mode);
	WindowMode getMode();
	void setResizeCallback(std::function<void(int, int)> callback);

	GLFWwindow* getGlfwWindow();
	std::function<void(int, int)>& getResizeCallback();
	std::array<int, 2> getSize();
	void setSize(int width, int height);
	int* getAspectRatio();

	static void keyCallback(GLFWwindow* pGlfwWindow, int key, int scancode, int action, int mods);
	static void mouseButtonCallback(GLFWwindow* window, int button, int action, int mods);
	static void mouseCallback(GLFWwindow* window, double x, double y);

	// static void framebufferSizeCallback(GLFWwindow* window, int width, int height);
	// static void mouseSizeCallback(GLFWwindow* window, double x, double y);

	bool m_debug = false;

private:
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
	InputGlfw* m_pInput;
};