#include "game.h"

#include <entt/entt.hpp>

#include "lc_client/eng_graphics/openGL/gl_render.h"
#include "ldk_client/local_engine/scene_controlling.h"
#include "lc_client/eng_procedures/openGL/gl_graphics_entities_loading.h"
#include "lc_client/util/eng_resource.h"


Game::Game(IWindow* pWindow) {
	m_pWindow = pWindow;
	m_pRender = new RenderGL(m_pWindow);
	m_pResource = new eng::Resource("D:/Industry/industry/res/");
	m_pShaderManager = new ShaderManagerGl(m_pResource);
	m_pTextureManager = new TextureManager(m_pResource);
	m_pGraphicsEntitiesLoading = new GraphicsEntitiesLoadingGl(m_pShaderManager, m_pTextureManager);
}

Game::~Game() {
	delete m_pRender;
	delete m_pResource;
	delete m_pShaderManager;
	delete m_pGraphicsEntitiesLoading;
};

void Game::init() {
	m_pInput = m_pWindow->getInput();

	m_pShaderManager->loadShaders();

	SceneDependencies sceneDependecies;
	sceneDependecies.pShaderManager = m_pShaderManager;
	sceneDependecies.pGraphicsEntitiesLoading = m_pGraphicsEntitiesLoading;

	m_pScene = SceneControlling::getScene();
	m_pScene->setDependencies(sceneDependecies);
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