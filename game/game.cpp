#include "game.h"

#include <iostream>
#include <entt/entt.hpp>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>

#include "ldk_client/local_engine/time.h"
#include "lc_client/eng_graphics/openGL/gl_render.h"
#include "ldk_client/local_engine/scene_controlling.h"
#include "lc_client/eng_procedures/openGL/gl_graphics_entities_loading.h"
#include "lc_client/util/eng_resource.h"
#include "lc_client/eng_input/glfw_input.h"


Game::Game(IWindow* pWindow) {
	m_pWindow = pWindow;
	m_pCamera = new Camera();
	m_pRender = new RenderGL(m_pWindow, m_pCamera);
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
	delete m_pCamera;
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

	m_pRender->init();
}

void Game::input() {
	double offsetMouseX = m_pInput->getMousePosX() - m_lastMousePosX;
	double offsetMouseY = m_lastMousePosY - m_pInput->getMousePosY();

	m_lastMousePosX = m_pInput->getMousePosX();
	m_lastMousePosY = m_pInput->getMousePosY();

	glm::vec3 cameraRot = m_pCamera->getRotation();

	cameraRot.x += offsetMouseY * m_sensivity;
	cameraRot.z += offsetMouseX * m_sensivity;

	if (cameraRot.x > 89.0f)
		cameraRot.x = 89.0f;
	if (cameraRot.x < -89.0f)
		cameraRot.x = -89.0f;

	m_pCamera->setRotation(cameraRot);


	const float cameraSpeed = 0.05f; 

	glm::vec3 cameraPos = m_pCamera->getPosition();

	if (m_pInput->isKeyPressed("W")) {
		cameraPos += cameraSpeed * m_pCamera->getCameraFront();
	}
	if (m_pInput->isKeyPressed("S")) {
		cameraPos += cameraSpeed * -m_pCamera->getCameraFront();
	}
	if (m_pInput->isKeyPressed("A")) {
		cameraPos += cameraSpeed * -m_pCamera->getCameraRight();
	}
	if (m_pInput->isKeyPressed("D")) {
		cameraPos += cameraSpeed * m_pCamera->getCameraRight();
	}

	if (m_pInput->isKeyPressed("E")) {
		exit(0);
	}
	
	m_pCamera->setPosition(cameraPos);
}

void Game::update() {

}

void Game::render() {

	m_pRender->render();
}

void Game::cleanUp() {

}