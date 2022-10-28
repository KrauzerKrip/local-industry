#include "game.h"

#include <entt/entt.hpp>

#include "lc_client/eng_graphics/openGL/gl_render.h"
#include "ldk_client/local_engine/scene_controlling.h"


Game::Game(IWindow* pWindow) {
	m_pWindow = pWindow;
	m_pRender = new RenderGL(m_pWindow);
	m_pShaderManager = new ShaderManager();
}

Game::~Game() {
	delete m_pRender;
};

void Game::init() {
	m_pInput = m_pWindow->getInput();

	m_pShaderManager->loadShaders();

	m_pScene = SceneControlling::getScene();
	m_pScene->setShaderManager(m_pShaderManager);
	SceneControlling::loadScene("test");

	m_pRender->setRegistries(m_pScene->getMapRegistry(), m_pScene->getSceneRegistry());
}

void Game::update() {

}

void Game::render() {

	m_pRender->render();
}

void Game::cleanUp() {

}