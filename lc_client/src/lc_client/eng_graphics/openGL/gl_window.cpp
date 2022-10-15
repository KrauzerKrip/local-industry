#include "lc_client/eng_graphics/openGL/gl_window.h"

#include <iostream>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <string>

#include "lc_client/eng_input/glfw_input.h"
#include "lc_client/exceptions/glfw_exceptions.h"
#include "lc_client/exceptions/glad_exceptions.h"


WindowGL::WindowGL(std::string title, int width, int height, bool vSync) {
	m_title = title;
	m_width = width;
	m_height = height;
	m_vSync = vSync;
}

WindowGL::~WindowGL() {};

void WindowGL::init() {
	glfwInit();
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

	//glfwSetFramebufferSizeCallback(m_pGlfwWindow, framebufferSizeCallback);

	if (m_vSync) {
		glfwSwapInterval(0);
	}

	std::cout << "Window init" << std::endl;

	m_pInput = new InputGlfw(this);

}

void WindowGL::update() {
	glfwSwapBuffers(m_pGlfwWindow);
	glfwPollEvents();
}

bool WindowGL::windowShouldClose() {
	return glfwWindowShouldClose(m_pGlfwWindow);
}

void WindowGL::terminate() {
	glfwTerminate();
}

IInput* WindowGL::getInput() {
	return m_pInput;
}

bool WindowGL::isKeyPressed(int key) {
	if (glfwGetKey(m_pGlfwWindow, key) == GLFW_PRESS) {
		return true;
	}
	else {
		return false;
	}
}

static void framebufferSizeCallback(GLFWwindow* window, int width, int height) {
	glViewport(0, 0, width, height);
}