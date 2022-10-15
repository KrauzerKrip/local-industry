#include "lc_client/loop.h"

#include <stdexcept>

Loop::Loop(IWindow* pWindow, IGameLogic* gameLogic, int targetFPS, int targetUPS) {
	m_pWindow = pWindow;
	m_pGameLogic = gameLogic;
	m_targetFPS = targetFPS;
	m_targetUPS = targetUPS;
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
	m_pGameLogic->init();
	m_pWindow->init();
}

void Loop::startLoop() {
	while (true) {
		m_pGameLogic->update();
		m_pWindow->update();
	}
}

void Loop::cleanUp(){
	m_pWindow->terminate();
}

Loop* Loop::m_pInstance = nullptr;

