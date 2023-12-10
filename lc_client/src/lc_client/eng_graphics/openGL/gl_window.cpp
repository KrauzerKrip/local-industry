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

	m_resizeCallback = [](int width, int height) {};

	m_pInput = new InputGlfw();

		int code = glfwGetError(NULL);

	if (code == GLFW_NO_ERROR) {
		std::cout << "glfw all ok" << std::endl;
	}

	std::cout << "gl_window 1" << std::endl;
	std::cout << glfwInit() << std::endl;
	std::cout << "gl_window 2" << std::endl;

	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	glfwWindowHint(GLFW_RESIZABLE, true);
	glfwWindowHint(GLFW_DECORATED, true);
	glfwWindowHint(GLFW_OPENGL_DEBUG_CONTEXT, GL_TRUE);
	glfwWindowHint(GLFW_SAMPLES, 8);


	m_pGlfwWindow = glfwCreateWindow(m_width, m_height, m_title.c_str(), NULL, NULL);

	if (m_pGlfwWindow == nullptr) {
		throw GlfwWindowFailException();
		glfwTerminate();
	}

	glfwMakeContextCurrent(m_pGlfwWindow);

	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
		throw GladInitFailException();
	}

	glViewport(0, 0, m_width, m_height);
	// glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
	glClearColor(117.0f / 255, 187.0f / 255, 253.0f / 255, 1.0f);
	// glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
}

WindowGL::~WindowGL() {
	delete m_pInput;
	delete[] m_pAspectRatio;
};

void WindowGL::init() {
	glfwSetWindowUserPointer(m_pGlfwWindow, this);
	glfwSetFramebufferSizeCallback(m_pGlfwWindow, framebufferSizeCallback);
	glfwSetKeyCallback(m_pGlfwWindow, keyCallback);
	glfwSetMouseButtonCallback(m_pGlfwWindow, mouseButtonCallback);
	glfwSetCursorPosCallback(m_pGlfwWindow, mouseCallback);
	glfwSetScrollCallback(m_pGlfwWindow, mouseWheelCallback);

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

	if (m_vSync) {
		glfwSwapInterval(1);
	}

	glfwSetInputMode(m_pGlfwWindow, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
	m_windowMode = WindowMode::CURSOR_DISABLED;


	ImGui_ImplGlfw_InitForOpenGL(m_pGlfwWindow, true);
	ImGui_ImplOpenGL3_Init("#version 400");

	startFrame();

	glfwSetWindowAspectRatio(m_pGlfwWindow, m_pAspectRatio[0], m_pAspectRatio[1]);

	ImGui::StyleColorsDark();

	glfwMaximizeWindow(m_pGlfwWindow); 

	std::cout << "Window init" << std::endl;

	m_debug = true;
}

void WindowGL::update() {

	ImGui::Render();
	ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

	glfwSwapBuffers(m_pGlfwWindow);
	glfwPollEvents();
}

void WindowGL::startFrame() { 
	ImGui_ImplGlfw_NewFrame();
	ImGui_ImplOpenGL3_NewFrame();
	ImGui::NewFrame();
}

bool WindowGL::windowShouldClose() {
	return glfwWindowShouldClose(m_pGlfwWindow);
}

void WindowGL::terminate() {
	ImGui_ImplGlfw_Shutdown();
	ImGui_ImplOpenGL3_Shutdown();
	ImGui::DestroyContext();

	glfwTerminate();
}

InputGlfw* WindowGL::getInput() {
	return m_pInput;
}

void WindowGL::setMode(WindowMode mode) {
	m_windowMode = mode;
	if (mode == WindowMode::CURSOR_DISABLED) {
		glfwSetInputMode(m_pGlfwWindow, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
	}
	else if(mode == WindowMode::CURSOR_ENABLED) {
		glfwSetInputMode(m_pGlfwWindow, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
	}
}

WindowMode WindowGL::getMode() { return m_windowMode; }

void WindowGL::setResizeCallback(std::function<void(int, int)> callback) { m_resizeCallback = callback; }

GLFWwindow* WindowGL::getGlfwWindow() {
	return m_pGlfwWindow; }

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
	pWindow->getInput()->invokeMouseCallbacks(glm::vec2(x, y));
}

void WindowGL::mouseWheelCallback(GLFWwindow* pGlfwWindow, double xoffset, double yoffset) {
	WindowGL* pWindow = (WindowGL*)glfwGetWindowUserPointer(pGlfwWindow);
	pWindow->getInput()->invokeMouseWheelCallbacks(glm::vec2((float) xoffset, (float) yoffset));
}

static void framebufferSizeCallback(GLFWwindow* window, int width, int height) {
	WindowGL* pWindowGL = (WindowGL*)glfwGetWindowUserPointer(window);

	bool debug = pWindowGL->m_debug;

	const int widthWindow = width;
	//const int aspectRatio = pWindowGL->getAspectRatio()[0] / pWindowGL->getAspectRatio()[1];
	const int heightWindow = height; // std::round(width / aspectRatio);
	pWindowGL->setSize(widthWindow, heightWindow);

	glViewport(0, 0, widthWindow, heightWindow);

	std::function<void(int, int)>& resizeCallback = pWindowGL->getResizeCallback();
	resizeCallback(width, height);

	pWindowGL->update();
}

void GLAPIENTRY messageCallback(GLenum source, GLenum type, GLuint id, GLenum severity, GLsizei length,
	const GLchar* message, const void* userParam) {

	//fprintf(stderr, "GL CALLBACK: %s type = 0x%x, severity = 0x%x, message = %s\n",
		//(type == GL_DEBUG_TYPE_ERROR ? "** GL ERROR **" : ""), type, severity, message);
}
