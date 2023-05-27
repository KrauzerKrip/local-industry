#include "gl_window.h"
#include "gl_window.h"
#include "gl_window.h"

#include <iostream>
#include <cmath>
#include <string>

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <imgui_impl_glfw.h>
#include <imgui_impl_opengl3.h>


#include "lc_client/eng_graphics/openGL/gl_window.h"
#include "lc_client/tier0/console/i_console_input.h"

#include "lc_client/eng_input/glfw_input.h"
#include "lc_client/exceptions/glfw_exceptions.h"
#include "lc_client/exceptions/glad_exceptions.h"


WindowGL::WindowGL(std::string title, int width, int height, int* aspectRatio, bool vSync, float fov) {
	m_title = title;
	m_width = width;
	m_height = height;
	m_pAspectRatio = aspectRatio;
	m_vSync = vSync;
	m_fov = fov;
}

WindowGL::~WindowGL() {
	delete m_pInput;
	delete[] m_pAspectRatio;
};

void WindowGL::init() {

	int code = glfwGetError(NULL);

	if (code == GLFW_NO_ERROR) {
		std::cout << "glfw all ok" << std::endl;
	}

	std::cout << "gl_window 1" << std::endl;
	std::cout << glfwInit() << std::endl;
	std::cout << "gl_window 2" << std::endl;

	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 0);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	glfwWindowHint(GLFW_RESIZABLE, true);
	glfwWindowHint(GLFW_DECORATED, true);

	m_pGlfwWindow = glfwCreateWindow(m_width, m_height, m_title.c_str(), NULL, NULL);

	if (m_pGlfwWindow == nullptr) {
		throw GlfwWindowFailException();
		glfwTerminate();
	}

	glfwMakeContextCurrent(m_pGlfwWindow);

	if (!gladLoadGLLoader((GLADloadproc) glfwGetProcAddress))
	{
		throw GladInitFailException();
	}

	glViewport(0, 0, m_width, m_height);
	//glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
	glClearColor(117.0f / 255, 187.0f / 255, 253.0f / 255, 1.0f);
	//glClearColor(0.1f, 0.1f, 0.1f, 1.0f);

	glfwSetWindowUserPointer(m_pGlfwWindow, this);

	glfwSetFramebufferSizeCallback(m_pGlfwWindow, framebufferSizeCallback);
	glfwSetKeyCallback(m_pGlfwWindow, keyCallback);

	if (m_vSync) {
		glfwSwapInterval(1);
	}

	glfwSetInputMode(m_pGlfwWindow, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
	m_windowMode = WindowMode::GAME;


	ImGui_ImplGlfw_InitForOpenGL(m_pGlfwWindow, true);
	ImGui_ImplOpenGL3_Init("#version 400");

	startFrame();

	glfwSetWindowAspectRatio(m_pGlfwWindow, m_pAspectRatio[0], m_pAspectRatio[1]);

	ImGui::StyleColorsDark();

	glfwMaximizeWindow(m_pGlfwWindow); 

	std::cout << "Window init" << std::endl;

	m_pInput = new InputGlfw(this);
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

IInput* WindowGL::getInput() {
	return m_pInput; }

void WindowGL::setMode(WindowMode mode) {
	m_windowMode = mode;
	if (mode == WindowMode::GAME) {
		glfwSetInputMode(m_pGlfwWindow, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
	}
	else if(mode == WindowMode::GUI) {
		glfwSetInputMode(m_pGlfwWindow, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
	}
}

WindowMode WindowGL::getMode() { return m_windowMode; }

GLFWwindow* WindowGL::getGlfwWindow() {
	return m_pGlfwWindow; }

void WindowGL::addKeyCallback(int glfwKey, std::function<void()> callback) {
	m_callbacks.insert_or_assign(glfwKey, callback);
}

std::unordered_map<int, std::function<void()>>& WindowGL::getCallbacks() { return m_callbacks; }

int* WindowGL::getSize() {
	int* size = new int[2];
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

float WindowGL::getFov() {
	return m_fov;
}

void WindowGL::setFov(float fov) {
	m_fov = fov; }

void WindowGL::keyCallback(GLFWwindow* pGlfwWindow, int key, int scancode, int action, int mods) {
	WindowGL* pWindow = static_cast<WindowGL*>(glfwGetWindowUserPointer(pGlfwWindow));
	
	auto& callbacks = pWindow->getCallbacks();

	for (auto& [k, callback] : callbacks) {
		if (k == key && action == GLFW_PRESS) {
			callback();
			break;
		}
	}
}

static void framebufferSizeCallback(GLFWwindow* window, int width, int height) {

	WindowGL* pWindowGL = (WindowGL*)glfwGetWindowUserPointer(window);
	int* size = pWindowGL->getSize();

	const int widthWindow = width;
	//const int aspectRatio = pWindowGL->getAspectRatio()[0] / pWindowGL->getAspectRatio()[1];
	const int heightWindow = height; // std::round(width / aspectRatio);
	pWindowGL->setSize(widthWindow, heightWindow);

	glViewport(0, 0, widthWindow, heightWindow);

	pWindowGL->update();
}

static void mouseCallback(GLFWwindow* window, double x, double y) {

	WindowGL* pWindowGL = (WindowGL*)glfwGetWindowUserPointer(window);
	
}