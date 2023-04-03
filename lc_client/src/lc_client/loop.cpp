#include "lc_client/loop.h"

#include <GLFW/glfw3.h>
#include <stdexcept>

#include "ldk_client/local_engine/time.h"


Loop::Loop(IWindow* pWindow, IGameLogic* gameLogic, int targetFPS, int targetUPS) {
	m_pWindow = pWindow;
	m_pGameLogic = gameLogic;
	m_targetFPS = targetFPS;
	m_targetUPS = targetUPS;
	m_deltaTime = 0;
}

Loop* Loop::createInstance(IWindow* pWindow, IGameLogic* gameLogic, int targetFPS, int targetUPS) {
	m_pInstance = new Loop(pWindow, gameLogic, targetFPS, targetUPS);
	return m_pInstance;
}

Loop* Loop::getInstance() {

	if (&m_pInstance == 0) {
		throw std::runtime_error("Instance of loop haven`t been created before.");
	}

	return m_pInstance;
}

void Loop::init() {

	m_pWindow->init();
	m_pGameLogic->init(); // it was before
}

void Loop::startLoop() {

	double lastTime = 0.0;

	while (!m_pWindow->windowShouldClose()) {

		double currentTime = glfwGetTime();

		m_deltaTime = currentTime - lastTime;
		lastTime = currentTime;
		Time::m_deltaTime = m_deltaTime;

		m_pGameLogic->input();

		//

		m_pGameLogic->render();
		m_pWindow->update();
	}
}

void Loop::cleanUp(){
	m_pWindow->terminate();
}

Loop* Loop::m_pInstance = nullptr;

