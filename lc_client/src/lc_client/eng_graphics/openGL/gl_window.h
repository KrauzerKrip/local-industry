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
	~WindowGL();

	void init() override;
	void input() override;
	void frame() override;
	void startFrame() override; 
	bool windowShouldClose() override;
	void terminate() override;
	InputGlfw* getInput();
	void setCursorMode(CursorMode mode);
	CursorMode getCursorMode();
	void setResizeCallback(std::function<void(int, int)> callback);
	void setCreationCallback(std::function<void()> callback);
	void setWindowMode(WindowMode mode) override;
	WindowMode getWindowMode() override;
	void setTargetFps(unsigned int fps) override;

	GLFWwindow* getGlfwWindow();
	std::function<void(int, int)>& getResizeCallback();
	std::array<int, 2> getSize() override;
	void setSize(int width, int height) override;
	int* getAspectRatio() override;

	static void keyCallback(GLFWwindow* pGlfwWindow, int key, int scancode, int action, int mods);
	static void mouseButtonCallback(GLFWwindow* pGlfwWindow, int button, int action, int mods);
	static void mouseCallback(GLFWwindow* pGlfwWindow, double x, double y);
	static void mouseWheelCallback(GLFWwindow* pGlfwWindow, double xoffset, double yoffset);

	// static void framebufferSizeCallback(GLFWwindow* window, int width, int height);
	// static void mouseSizeCallback(GLFWwindow* window, double x, double y);

	bool m_debug = false;

private:
	void resize();
	void changeWindowMode();

	std::function<void(int, int)> m_resizeCallback; 
	std::function<void()> m_creationCallback;

	int m_width;
	int m_height;
	std::string m_title;
	int* m_pAspectRatio;
	bool m_vSync;
	float m_fov;
	double mouseOffsetX;
	double mouseOffsetY;
	CursorMode m_cursorMode;
	WindowMode m_windowMode;
	bool m_shouldWindowResize;
	bool m_shouldChangeWindowMode;
	unsigned int m_targetFps;

	GLFWwindow* m_pGlfwWindow = nullptr;
	InputGlfw* m_pInput = nullptr;
};