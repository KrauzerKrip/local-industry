#include "gl_window.h"

#include <iostream>
#include <cmath>
#include <string>

#include <imgui_impl_glfw.h>
#include <imgui_impl_opengl3.h>


#include "lc_client/eng_graphics/openGL/gl_window.h"
#include "lc_client/tier0/console/i_console_input.h"

#include "lc_client/eng_input/glfw_input.h"
#include "lc_client/exceptions/glfw_exceptions.h"
#include "lc_client/exceptions/glad_exceptions.h"


WindowGL::WindowGL(std::string title, int width, int height, int* aspectRatio) {
	m_title = title;
	m_width = width;
	m_height = height;
	m_pAspectRatio = aspectRatio;

	m_windowMode = WindowMode::WINDOWED;
	m_cursorMode = CursorMode::CURSOR_DISABLED;

	m_shouldWindowResize = false;
	m_shouldChangeWindowMode = false;

	m_resizeCallback = [](int width, int height) {};

	m_pInput = new InputGlfw();

	m_debug = false;

	int code = glfwGetError(NULL);

	if (code == GLFW_NO_ERROR) {
		std::cout << "glfw all ok" << std::endl;
	}

	std::cout << "glfwInit 1" << std::endl;
	std::cout << glfwInit() << std::endl;
	std::cout << "glfwInit 2" << std::endl;

	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	glfwWindowHint(GLFW_RESIZABLE, true);
	glfwWindowHint(GLFW_DECORATED, true);
	glfwWindowHint(GLFW_OPENGL_DEBUG_CONTEXT, GL_TRUE);
	glfwWindowHint(GLFW_SAMPLES, 8);
}

WindowGL::~WindowGL() {
	delete m_pInput;
	delete[] m_pAspectRatio;
};

void WindowGL::init() {
	if (m_debug) {
		int i = 0;
	}

	m_debug = true;

	if (m_windowMode == WindowMode::FULLSCREEN) {
		m_pGlfwWindow = glfwCreateWindow(m_width, m_height, m_title.c_str(), glfwGetPrimaryMonitor(), NULL);
	}
	else if (m_windowMode == WindowMode::WINDOWED) {
		m_pGlfwWindow = glfwCreateWindow(m_width, m_height, m_title.c_str(), NULL, NULL);
	}

	if (m_pGlfwWindow == nullptr) {
		throw GlfwWindowFailException();
		glfwTerminate();
	}

	glfwMakeContextCurrent(m_pGlfwWindow);

	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
		throw GladInitFailException();
	}

	GLint flags;
	glGetIntegerv(GL_CONTEXT_FLAGS, &flags);
	if (flags & GL_CONTEXT_FLAG_DEBUG_BIT) {
		glEnable(GL_DEBUG_OUTPUT);
		glEnable(GL_DEBUG_OUTPUT_SYNCHRONOUS);
		glDebugMessageCallback(messageCallback, nullptr);
		glDebugMessageControl(GL_DONT_CARE, GL_DONT_CARE, GL_DONT_CARE, 0, nullptr, GL_TRUE);
		glDebugMessageControl(GL_DONT_CARE, GL_DONT_CARE, GL_DEBUG_SEVERITY_NOTIFICATION, 0, nullptr, GL_FALSE);
		glDebugMessageControl(GL_DONT_CARE, GL_DONT_CARE, GL_DEBUG_SEVERITY_LOW, 0, nullptr, GL_FALSE);
		std::cout << "OpenGL debug context was created." << std::endl;
	}
	else {
		std::cout << "OpenGL Error: OpenGL debug context wasn`t created." << std::endl;
	}

	glViewport(0, 0, m_width, m_height);
	// glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
	glClearColor(117.0f / 255, 187.0f / 255, 253.0f / 255, 1.0f);
	// glClearColor(0.1f, 0.1f, 0.1f, 1.0f);

	if (m_vSync) {
		glfwSwapInterval(1);
	}

	glfwSetWindowUserPointer(m_pGlfwWindow, this);
	glfwSetFramebufferSizeCallback(m_pGlfwWindow, framebufferSizeCallback);
	glfwSetKeyCallback(m_pGlfwWindow, keyCallback);
	glfwSetMouseButtonCallback(m_pGlfwWindow, mouseButtonCallback);
	glfwSetCursorPosCallback(m_pGlfwWindow, mouseCallback);
	glfwSetScrollCallback(m_pGlfwWindow, mouseWheelCallback);

	ImGui_ImplGlfw_InitForOpenGL(m_pGlfwWindow, true);
	ImGui_ImplOpenGL3_Init("#version 400");

	glfwSetWindowAspectRatio(m_pGlfwWindow, m_pAspectRatio[0], m_pAspectRatio[1]);

	ImGui::StyleColorsDark();

	std::cout << "Window init" << std::endl;

	m_debug = true;

	glfwMaximizeWindow(m_pGlfwWindow);
	
	m_creationCallback();
}

void WindowGL::input() {
}

void WindowGL::frame() {
	ImGui::Render();
	ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

	glfwSwapBuffers(m_pGlfwWindow);
	glfwPollEvents();
}

void WindowGL::startFrame() { 
	if (m_shouldWindowResize) {
		this->resize();
		m_shouldWindowResize = false;
	}
	if (m_shouldChangeWindowMode) {
		this->changeWindowMode();
		m_shouldChangeWindowMode = false;
	}

	ImGui_ImplGlfw_NewFrame();
	ImGui_ImplOpenGL3_NewFrame();
	ImGui::NewFrame();
}

bool WindowGL::windowShouldClose() {
	return glfwWindowShouldClose(m_pGlfwWindow);
}

void WindowGL::terminate() {
	ImGui_ImplOpenGL3_Shutdown();
	ImGui_ImplGlfw_Shutdown();
	ImGui::DestroyContext();

	glfwDestroyWindow(m_pGlfwWindow);
	glfwTerminate();
}

InputGlfw* WindowGL::getInput() {
	return m_pInput;
}

void WindowGL::setCursorMode(CursorMode mode) {
	m_cursorMode = mode;
	if (mode == CursorMode::CURSOR_DISABLED) {
		glfwSetInputMode(m_pGlfwWindow, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
	}
	else if(mode == CursorMode::CURSOR_ENABLED) {
		glfwSetInputMode(m_pGlfwWindow, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
	}
}

CursorMode WindowGL::getCursorMode() { return m_cursorMode; }

void WindowGL::setResizeCallback(std::function<void(int, int)> callback) { m_resizeCallback = callback; }

void WindowGL::setCreationCallback(std::function<void()> callback) { m_creationCallback = callback; }

GLFWwindow* WindowGL::getGlfwWindow() {
	return m_pGlfwWindow; 
}

std::function<void(int, int)>& WindowGL::getResizeCallback() { return m_resizeCallback; }

std::array<int, 2> WindowGL::getSize() {
	std::array<int, 2> size;
	size[0] = m_width;
	size[1] = m_height;

	return size;
}

void WindowGL::setSize(int width, int height) {
	m_width = width;
	m_height = height;

	m_shouldWindowResize = true;
}

int* WindowGL::getAspectRatio() {
	return m_pAspectRatio;
}

void WindowGL::keyCallback(GLFWwindow* pGlfwWindow, int key, int scancode, int action, int mods) {
	WindowGL* pWindow = static_cast<WindowGL*>(glfwGetWindowUserPointer(pGlfwWindow));
	pWindow->getInput()->invokeKeyCallbacks(key, action);
}

void WindowGL::mouseButtonCallback(GLFWwindow* pGlfwWindow, int button, int action, int mods) {
	WindowGL* pWindow = static_cast<WindowGL*>(glfwGetWindowUserPointer(pGlfwWindow));
	pWindow->getInput()->invokeKeyCallbacks(button, action);
}

void WindowGL::mouseCallback(GLFWwindow* pGlfwWindow, double x, double y) {
	WindowGL* pWindow = (WindowGL*)glfwGetWindowUserPointer(pGlfwWindow);

	float offsetX = 1920.0f / pWindow->m_width;
	float offsetY = 1080.0f / pWindow->m_height;
	glm::vec2 relativePosition(x * offsetX, y * offsetY);

	pWindow->getInput()->invokeMouseCallbacks(relativePosition);
}

void WindowGL::mouseWheelCallback(GLFWwindow* pGlfwWindow, double xoffset, double yoffset) {
	WindowGL* pWindow = (WindowGL*)glfwGetWindowUserPointer(pGlfwWindow);
	pWindow->getInput()->invokeMouseWheelCallbacks(glm::vec2((float) xoffset, (float) yoffset));
}

static void framebufferSizeCallback(GLFWwindow* pWindow, int width, int height) {
	WindowGL* pWindowGL = (WindowGL*)glfwGetWindowUserPointer(pWindow);

	bool debug = pWindowGL->m_debug;

	const int widthWindow = width;
	//const int aspectRatio = pWindowGL->getAspectRatio()[0] / pWindowGL->getAspectRatio()[1];
	const int heightWindow = height; // std::round(width / aspectRatio);
	pWindowGL->setSize(widthWindow, heightWindow);

	//pWindowGL->update();
}

void GLAPIENTRY messageCallback(GLenum source, GLenum type, GLuint id, GLenum severity, GLsizei length,
	const GLchar* message, const void* userParam) {

	//fprintf(stderr, "GL CALLBACK: %s type = 0x%x, severity = 0x%x, message = %s\n",
	//	(type == GL_DEBUG_TYPE_ERROR ? "** GL ERROR **" : ""), type, severity, message);
}

void WindowGL::resize() {
	glfwSetWindowSize(m_pGlfwWindow, m_width, m_height);
	glViewport(0, 0, m_width, m_height);
	m_resizeCallback(m_width, m_height);
}

void WindowGL::setWindowMode(WindowMode mode) { 
	if (mode == m_windowMode) {
		return;
	}
	
	m_shouldChangeWindowMode = true;

	m_windowMode = mode;
}

WindowMode WindowGL::getWindowMode() { return m_windowMode; }

void WindowGL::changeWindowMode() {
	glfwDestroyWindow(m_pGlfwWindow);
	ImGui_ImplOpenGL3_Shutdown();
	ImGui_ImplGlfw_Shutdown();
	//ImGui::DestroyContext();

	this->init();

	m_resizeCallback(m_width, m_height);
}