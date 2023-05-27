#include "game.h"

#include <iostream>
#include <chrono>

#include <entt/entt.hpp>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>

#include "ldk_client/local_engine/time.h"
#include "lc_client/eng_graphics/openGL/gl_render.h"
#include "ldk_client/local_engine/scene_controlling.h"
#include "lc_client/util/eng_resource.h"
#include "lc_client/eng_input/glfw_input.h"
#include "lc_client/exceptions/input_exceptions.h"
#include "lc_client/tier1/openGL/gl_tier1.h"
#include "lc_client/eng_graphics/openGL/gl_mesh_work.h"
#include "lc_client/eng_graphics/openGL/gl_shader_work.h"
#include "lc_client/eng_gui/gui_console.h"

#include "lc_client/tier0/console/i_console.h"

#include "lc_client/eng_graphics/openGL/gl_window.h"


Game::Game(IWindow* pWindow, Tier0* pTier0) {
	m_pWindow = pWindow;
	m_pCamera = new Camera();
	m_pRender = new RenderGL(m_pWindow, m_pCamera);
	m_pResource = new eng::Resource("D:/Industry/industry/res/");
	m_pTier0 = pTier0;
	m_pTier1 = new Tier1Gl(m_pResource);

	m_pConsoleGui = new ConsoleGui(m_pTier0->getConsole(), m_pTier0->getImGuiFonts());
}

Game::~Game() {
	delete m_pRender;
	delete m_pResource;
	delete m_pTier1;
	delete m_pCamera;
	delete m_pTier0;
};

void Game::init() {

	m_pInput = m_pWindow->getInput();

	m_pTier1->getShaderManager()->loadShaders();

	m_pScene = SceneControlling::getScene();
	m_pModelManager = new ModelManager(m_pResource, m_pTier1->getTextureManager(), m_pScene->getUtilRegistry(), m_pTier0->getConsole());
	
	m_pMeshWork = new MeshWorkGl(&m_pScene->getUtilRegistry());
	m_pShaderWorkScene = new ShaderWorkGl(m_pTier1->getShaderManager(), &m_pScene->getSceneRegistry());

	SceneDependencies sceneDependecies;
	sceneDependecies.pShaderManager = m_pTier1->getShaderManager();
	sceneDependecies.pResource = m_pResource;
	sceneDependecies.pGraphicsEntitiesLoading = new GraphicsEntitiesLoading(&m_pScene->getMapRegistry(), &m_pScene->getSceneRegistry());

	m_pScene->setDependencies(sceneDependecies);
	SceneControlling::loadScene("dev", "test");

	m_pRender->setDependecies(m_pScene);

	m_pRender->init();

	m_pSystems = new Systems(m_pTier1, m_pShaderWorkScene, m_pMeshWork, m_pScene, m_pModelManager);

	m_pScene->getSkybox().setLightColor(255, 255, 200); // 255, 255, 236
	m_pScene->getSkybox().setLightStrength(0.4);


	auto dirLight = m_pScene->getSceneRegistry().create(); // temp
	auto dirLightComponent = m_pScene->getSceneRegistry().emplace<DirectionalLight>(dirLight);
	dirLightComponent.color = glm::vec3(1, 1, 1);
	dirLightComponent.direction = glm::vec3(-0.2f, -1.0f, -0.3f);

	m_pInput->addKeyCallback("GRAVE_ACCENT", [pConsoleGui = this->m_pConsoleGui, pWindow = this->m_pWindow]() {
		if (pConsoleGui->isOpened()) {
			pConsoleGui->close();
			pWindow->setMode(WindowMode::GAME);
		}
		else {
			pConsoleGui->open();
			pWindow->setMode(WindowMode::GUI);
		}
	});
}

void Game::input() {

	m_pConsoleGui->update();

	if (m_pConsoleGui->isOpened()) {
		m_lastMousePosX = m_pInput->getMousePosX();
		m_lastMousePosY = m_pInput->getMousePosY();
		return;
	}

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


	float cameraSpeed = 0.05f;

	glm::vec3 cameraPos = m_pCamera->getPosition();

	try {
		if (m_pInput->isKeyPressed("LEFT_SHIFT")) {
			cameraSpeed = 0.1f;
		}

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

		if (m_pInput->isKeyPressed("SPACE")) {
			cameraPos += cameraSpeed * glm::vec3(0, 1, 0);
		}
		if (m_pInput->isKeyPressed("LEFT_CTRL")) {
			cameraPos += cameraSpeed * glm::vec3(0, -1, 0);
		}

		if (m_pInput->isKeyPressed("B")) {
			m_pWindow->setFov(10);
		}
		else {
			m_pWindow->setFov(45);
		}


		if (m_pInput->isKeyPressed("ESC")) {
			exit(0);
		}
	}
	catch (UnknownKeyCodeException& exception) {
		std::cerr << exception.what() << std::endl;
	}

	m_pCamera->setPosition(cameraPos);
}

void Game::update() {

	entt::registry* pSceneRegistry = &m_pScene->getSceneRegistry();

	m_pSystems->update();

	auto view = pSceneRegistry->view<Properties, Transform>();

	for (auto& entity : view) {
		if (view.get<Properties>(entity).id == "example_entity_1") {
			glm::vec3& rotation = view.get<Transform>(entity).rotation;
			rotation += glm::vec3(1.0, -1.0, 1.0) * Time::getDeltaTime();
			if (rotation.x > 89.0f)
				rotation.x = 0.0f;
			if (rotation.x < -89.0f)
				rotation.x = 0.0f;

			using namespace std::chrono;

			auto time = duration_cast<milliseconds>(system_clock::now().time_since_epoch()).count();

			
			glm::vec3& position = view.get<Transform>(entity).position;

			//position.x += std::sin(time / 1000) * 1.0f * Time::getDeltaTime();
			//position.y += std::cos(time / 1000) * 1.0f * Time::getDeltaTime();
		}
	}
}

void Game::render() { 
	m_pSystems->frame();
	m_pRender->render(); }

void Game::cleanUp() {}