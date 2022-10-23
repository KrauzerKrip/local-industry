#include "game.h"

#include <entt/entt.hpp>

#include "lc_client/eng_graphics/openGL/gl_render.h"


Game::Game(IWindow* pWindow) {
	m_pWindow = pWindow;
	m_pRender = new RenderGL(m_pWindow);
}

Game::~Game() {
	delete m_pRender;
};

void Game::init() {
	m_pInput = m_pWindow->getInput();
}

void Game::update() {

}

void Game::render() {
	std::vector<entt::entity>* pGraphicsEntties = new std::vector<entt::entity>();

	m_pRender->render(pGraphicsEntties);
}

void Game::cleanUp() {

}