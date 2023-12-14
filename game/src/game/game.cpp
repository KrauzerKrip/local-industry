#include "game.h"

#include <iostream>
#include <chrono>
#include <memory>

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
#include "lc_client/eng_graphics/openGL/gl_mesh_loader.h"
#include "lc_client/eng_graphics/openGL/gl_shader_loader.h"
#include "lc_client/eng_gui/gui_console.h"
#include "lc_client/eng_scene/skybox.h"
#include "lc_client/util/pack.h"
#include "lc_client/eng_gui/layout/layouts/frame.h"
#include "lc_client/eng_gui/widgets/widget.h"
#include "lc_client/eng_graphics/gui/openGL/gl_background_render.h"
#include "lc_client/eng_gui/widgets/text_widget.h"
#include "lc_client/eng_graphics/openGL/gl_skybox_render.h"

#include "lc_client/tier0/console/i_console.h"

#include "lc_client/eng_graphics/openGL/gl_window.h"
#include "lc_client/eng_script/entt/components.h"
#include "lc_client/eng_graphics/gui/openGL/gl_widget_zoffset_calculator.h"
#include "lc_client/eng_graphics/gui/openGL/gl_text_zoffset_calculator.h"
#include "game/gui/dependencies_fabric/gui_dependencies_fabric.h"
#include "game/gui/dependencies_fabric/openGL/gl_gui_dependencies_fabric.h"
#include "game/gui/gui.h"
#include "game/loader_fabric/openGL/gl_loader_fabric.h"
#include "game/camera/orbital_camera_controller.h"
#include "game/control/action_init.h"


Game::Game(IWindow* pWindow, Tier0* pTier0) {
	std::vector actions = std::vector<std::string>({"kb_forward", "kb_left", "kb_back", "kb_right", "kb_up", "kb_fast",
		"kb_down", "kb_use", "kb_menu", "kb_select", "kb_rotate_camera"});

	m_pWindow = pWindow;
	m_pCamera = new Camera();
	m_pResource = new eng::Resource("E:/Industry/industry/res/"); 
	m_pTier0 = pTier0;
	game::initActions(m_pTier0->getParameters(), actions);
	m_pTier1 = new Tier1Gl(m_pResource, pTier0);
	m_pMap = new Map();
	m_pGraphicsSettings = new GraphicsSettings(m_pTier0->getParameters());
	m_pActionControl =
		new ActionControl(pWindow->getInput(), m_pTier0->getParameters(), m_pTier0->getConsole(), actions);

	m_pConsoleGui = new ConsoleGui(
		m_pTier0->getConsole(), m_pTier0->getImGuiFonts(), m_pTier1->getTextureManager(), m_pTier0->getParameters());

	m_pInput = m_pWindow->getInput();

	m_pTier1->getShaderManager()->loadShaders();

	LoaderFabricGl* pLoaderFabric =  new LoaderFabricGl(m_pResource, m_pTier0->getConsole(), m_pTier1->getShaderManager());

	GuiDependenciesFabric* pGuiDependenciesFabric =
		new GuiDependenciesFabricGl(m_pTier0->getConsole(), pLoaderFabric->getShaderLoaderGl());
	m_pGui = new Gui(m_pTier0, pGuiDependenciesFabric, m_pInput);

	m_pCameraController = new OrbitalCameraController(m_pCamera, m_pInput, m_pActionControl);

	Pack pack = Pack::getPack("dev");
	SkyboxRender* m_pSkyboxRender = new SkyboxRenderGl(pLoaderFabric->getShaderLoaderGl());
	m_pSkybox = new Skybox(m_pSkyboxRender, m_pResource);

	m_pSkybox->setLightColor(255, 255, 200); // 255, 255, 236
	m_pSkybox->setLightStrength(0.4f);

	SceneLoading* pSceneLoading = new SceneLoading(m_pResource);
	m_pScene = new Scene(m_pResource, pSceneLoading);

	ModelManager* pModelManager = new ModelManager(
		m_pResource, m_pTier1->getTextureManager(), m_pScene->getUtilRegistry(), m_pTier0->getConsole());

	m_pRender = new RenderGL(
		m_pWindow, m_pCamera, pLoaderFabric->getShaderLoaderGl(), m_pGui->getPresenter(), m_pGraphicsSettings);

	m_pRender->setDependecies(m_pMap, m_pScene, m_pSkybox);

	m_pRender->init();

	m_pSystems = new Systems(m_pTier0, m_pTier1, pLoaderFabric->getShaderLoaderGl(), pLoaderFabric->getMeshLoader(),
		pLoaderFabric->getCubemapLoader(), m_pScene, m_pMap, pModelManager);
}

Game::~Game() {
	delete m_pRender;
	delete m_pResource;
	delete m_pTier1;
	delete m_pCamera;
	delete m_pTier0;
};

void Game::init() {
	m_pScene->loadScene("dev", "test");
	m_pMap->loadMap("dev", "test");

	m_pSkybox->loadSkybox("anime");


	auto dirLight = m_pScene->getSceneRegistry().create(); // temp
	auto dirLightComponent = m_pScene->getSceneRegistry().emplace<DirectionalLight>(dirLight);
	dirLightComponent.color = glm::vec3(1, 1, 1);
	dirLightComponent.direction = glm::vec3(-0.2f, -1.0f, -0.3f);

	m_pInput->addMappedKeyCallback(KeyCode::GRAVE_ACCENT, [pConsoleGui = this->m_pConsoleGui, pWindow = this->m_pWindow]() {
		if (pConsoleGui->isOpened()) {
			pConsoleGui->close();
		}
		else {
			pConsoleGui->open();
		}
	});

	m_pInput->addMappedKeyCallback(KeyCode::B, [this]() {
		entt::registry* registry = &m_pScene->getSceneRegistry();
		entt::entity entity = registry->create();

		std::cout << "ray sent" << std::endl;

		glm::vec3 position = m_pCamera->getPosition();
		glm::vec3 direction = m_pCamera->getCameraFront();

		RaycastQuery raycastQuery(position, direction);

		registry->emplace<RaycastQuery>(entity, raycastQuery);
	});

	m_pInput->addMappedKeyCallback(
		KeyCode::F3, [this]() {
			if (m_pWindow->getMode() == WindowMode::CURSOR_DISABLED) {
				m_pWindow->setMode(WindowMode::CURSOR_ENABLED);
				m_guiMode = true;
			}
			else {
				m_pWindow->setMode(WindowMode::CURSOR_DISABLED);
				m_guiMode = false;
			}
		});

	m_pInput->addMappedKeyCallback(KeyCode::F3, [this]() {
		if (m_pWindow->getMode() == WindowMode::CURSOR_DISABLED) {
			m_pWindow->setMode(WindowMode::CURSOR_ENABLED);
			m_guiMode = true;
		}
		else {
			m_pWindow->setMode(WindowMode::CURSOR_DISABLED);
			m_guiMode = false;
		}
	});

	m_pWindow->setMode(WindowMode::CURSOR_ENABLED);

	auto pRegistry = &m_pScene->getSceneRegistry();
	auto view = pRegistry->view<Properties>();

	for (auto&& [entity, properties] : view.each()) {
		if (properties.id == "cube") {
			pRegistry->emplace<BoxCollider>(entity, 2.f, 2.0f, 2.0f);
		}
		if (properties.id == "cube_2") {
			pRegistry->emplace<BoxCollider>(entity, 2.f, 2.0f, 2.0f);
		}
	}
}

void Game::input() {
	m_pConsoleGui->update();

	if (m_pActionControl->isAction("kb_menu")) {
		exit(0);
	}

	//if (m_pWindow->getMode() == WindowMode::CURSOR_ENABLED) {
	//	m_lastMousePosX = m_pInput->getMousePosition().x;
	//	m_lastMousePosY = m_pInput->getMousePosition().y;
	//	return;
	//}

	float offsetMouseX = (float)(m_pInput->getMousePosition().x- m_lastMousePosX);
	float offsetMouseY = (float)(m_pInput->getMousePosition().y-m_lastMousePosY);

	m_lastMousePosX = m_pInput->getMousePosition().x;
	m_lastMousePosY = m_pInput->getMousePosition().y;

	m_pCameraController->update();
	//m_pCamera->setPosition(cameraPos);
}

void Game::update() {
	entt::registry* pMapRegistry = &m_pMap->getRegistry();
	entt::registry* pSceneRegistry = &m_pScene->getSceneRegistry();

	entt::entity surface;
	entt::entity surfaceScene;

	if (pMapRegistry->view<Mesh>().size() == 0) {
		surface = pMapRegistry->create();
		surfaceScene = pSceneRegistry->create();

		pSceneRegistry->emplace<ModelRequest>(surfaceScene, "dev", "test_surface");
	}

	m_pSystems->update();

	if (pMapRegistry->view<Mesh>().size() == 0) {
		m_pSystems->update();
		Model* model = &pSceneRegistry->get<Model>(surfaceScene);
		auto meshEnt = model->meshes.at(0);
		entt::registry* pUtilReg = &m_pScene->getUtilRegistry();
		Mesh* pMesh = &pUtilReg->get<Mesh>(meshEnt);
		pMapRegistry->emplace<Mesh>(surface, *pMesh);
		VaoGl* pVao = &pUtilReg->get<VaoGl>(meshEnt);
		pMapRegistry->emplace<VaoGl>(surface, *pVao);
		MaterialSG* pMaterial = &pUtilReg->get<MaterialSG>(meshEnt);
		pMapRegistry->emplace<MaterialSG>(surface, *pMaterial);

		ShaderGl shader = pSceneRegistry->get<ShaderGl>(surfaceScene);
		pMapRegistry->emplace<ShaderGl>(surface, shader);

		pMapRegistry->emplace<Transform>(surface, glm::vec3(0, -1, 0), glm::vec3(0, 0, 0), glm::vec3(100, 0.1, 100));
	}

	auto view = pSceneRegistry->view<Transform, Properties>();

	//for (auto& entity : view) {
	//	if (view.get<Properties>(entity).id == "cube") {
	//		auto& transform = view.get<Transform>(entity);
	//		transform.rotation *= glm::angleAxis(glm::radians(1.f), glm::vec3(0.f, 1.f, 0.f));
	//	}
	//}

	m_pGui->update();

}

void Game::render() {
	m_pSystems->frame();
	m_pRender->render();
}

void Game::cleanUp() {}

