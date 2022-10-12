#include "lc_client/eng_graphics/openGL/gl_window.h"

#include "exceptions/glfw_exceptions.h"
#include "exceptions/glad_exceptions.h"

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <string>


WindowGL::WindowGL(std::string title, int width, int height) {
	m_title = title;
	m_width = width;
	m_height = height;
}

WindowGL::~WindowGL(){}

void WindowGL::init() {
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 0);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	glfwWindowHint(GLFW_RESIZABLE, true);
	glfwWindowHint(GLFW_DECORATED, true);
	
	m_glfwWindow = glfwCreateWindow(m_width, m_height, m_title.c_str(), NULL, NULL);
	
	if (m_glfwWindow == NULL) {
		throw GlfwWindowFailException();
		glfwTerminate();   
	}

	glfwMakeContextCurrent(m_glfwWindow);

	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		throw GladInitFailException();
	}

	glViewport(0, 0, m_width, m_height);

	glfwSetFramebufferSizeCallback(m_glfwWindow, framebufferSizeCallback);

}

void WindowGL::update() {

}

static void framebufferSizeCallback(GLFWwindow* window, int width, int height)
{
	glViewport(0, 0, width, height);
}