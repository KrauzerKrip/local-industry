#include "gl_window.h"
#include "lc_client/eng_graphics/openGL/gl_window.h"

#include <iostream>
#include <cmath>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <string>

#include "lc_client/eng_input/glfw_input.h"
#include "lc_client/exceptions/glfw_exceptions.h"
#include "lc_client/exceptions/glad_exceptions.h"


WindowGL::WindowGL(std::string title, int width, int height, int* aspectRatio, bool vSync) {
	m_title = title;
	m_width = width;
	m_height = height;
	m_pAspectRatio = aspectRatio;
	m_vSync = vSync;
}

WindowGL::~WindowGL() {
	delete m_pInput;
	delete[] m_pAspectRatio;
};

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
	glClearColor(0.2f, 0.3f, 0.3f, 1.0f);

	//glfwSetFramebufferSizeCallback(m_pGlfwWindow, framebufferSizeCallback);

	if (m_vSync) {
		glfwSwapInterval(1);
	}

	glfwSetWindowUserPointer(m_pGlfwWindow, this);
	glfwSetWindowAspectRatio(m_pGlfwWindow, m_pAspectRatio[0], m_pAspectRatio[1]);

	std::cout << "Window init" << std::endl;

	m_pInput = new InputGlfw(this);

}

void WindowGL::update() {
	//if (resizer)

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

static void framebufferSizeCallback(GLFWwindow* window, int width, int height) {

	WindowGL* pWindowGL = (WindowGL*)glfwGetWindowUserPointer(window);
	int* size = pWindowGL->getSize();

	const int widthWindow = width;
	//const int aspectRatio = pWindowGL->getAspectRatio()[0] / pWindowGL->getAspectRatio()[1];
	const int heightWindow = height; //std::round(width / aspectRatio);
	pWindowGL->setSize(widthWindow, heightWindow);
	
	
	glViewport(0, 0, widthWindow, heightWindow);
}