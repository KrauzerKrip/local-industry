#include "game.h"

#include <iostream>
#include <chrono>
#include <memory>

#include <entt/entt.hpp>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>

#include "ldk_client/local_engine/time.h"
#include "lc_client/eng_graphics/openGL/gl_render.h"
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
#include "game/control/control_system.h"
#include "game/machine/physics/physical_constants.h"

#include "game/control/components.h"

#include "lc_client/eng_npc/npc_graph.h"
#include "lc_client/eng_npc/npc_graph_loader/npc_graph_loader.h"
#include "lc_client/eng_npc/components.h"
#include "lc_client/eng_physics/physics.h"


Game::Game(IWindow* pWindow, Tier0* pTier0) {
	m_pWindow = pWindow;
	m_pCamera = new Camera();
	m_pResource = new eng::Resource("E:/Industry/industry/res/"); 
	m_pTier0 = pTier0;
	m_pTier1 = new Tier1Gl(m_pResource, pTier0);
	m_pGraphicsSettings = new GraphicsSettings(m_pTier0->getParameters());
	m_pActionControl =
		new ActionControl(pWindow->getInput(), m_pTier0->getParameters(), m_pTier0->getConsole());

	m_pConsoleGui = new ConsoleGui(
		m_pTier0->getConsole(), m_pTier0->getImGuiFonts(), m_pTier1->getTextureManager(), m_pTier0->getParameters());

	m_pInput = m_pWindow->getInput();

	m_pTier1->getShaderManager()->loadShaders();

	LoaderFabricGl* pLoaderFabric =  new LoaderFabricGl(m_pResource, m_pTier0->getConsole(), m_pTier1->getShaderManager());

	Pack pack = Pack::getPack("dev");
	SkyboxRender* pSkyboxRender = new SkyboxRenderGl(pLoaderFabric->getShaderLoaderGl());

	SceneLoading* pSceneLoading = new SceneLoading(m_pResource);
	m_pWorld = new World(m_pResource, pSceneLoading, pSkyboxRender);

	Skybox* pSkybox = m_pWorld->getSkybox();
	pSkybox->setLightColor(255, 255, 200); // 255, 255, 236
	pSkybox->setLightStrength(0.4f);

	ModelManager* pModelManager = new ModelManager(
		m_pResource, m_pTier1->getTextureManager(), m_pWorld->getUtilRegistry(), m_pTier0->getConsole());
	ModelParser* pModelParser = new ModelParser(m_pResource);

	PhysicalConstants* pPhysicalConstants = new PhysicalConstants(m_pTier0->getParameters(), m_pTier0->getConsole());

    m_pTier1->initGameConfig();

	FramebufferController* pFramebufferController = new FramebufferController(m_pWindow);
	

	GuiDependenciesFabric* pGuiDependenciesFabric = new GuiDependenciesFabricGl(m_pTier0->getConsole(),
		pLoaderFabric->getShaderLoaderGl(), m_pInput, m_pTier1->getTextureManager(), pFramebufferController, pWindow);
	m_pGui = new Gui(m_pTier0, pGuiDependenciesFabric, m_pInput, m_pActionControl, &m_pWorld->getRegistry());

	m_pRender = new RenderGL(m_pWindow, m_pCamera, pLoaderFabric->getShaderLoaderGl(), pFramebufferController, m_pGui->getPresenter(), m_pGraphicsSettings);

	m_pRender->setDependecies(m_pWorld);

	m_pRender->init();

	m_pGraphicsSystems = new GraphicsSystems(m_pTier0, m_pTier1, pLoaderFabric->getShaderLoaderGl(), pLoaderFabric->getMeshLoader(), pLoaderFabric->getCubemapLoader(), m_pWorld, pModelManager, pModelParser);

	m_pScriptSystem = new ScriptSystem(&m_pWorld->getRegistry());
	Physics* pPhysics = new Physics(&m_pWorld->getRegistry());
	PhysicsLoader* pPhysicsLoader = new PhysicsLoader(new PhysicsParser(m_pResource), &m_pWorld->getRegistry());

	m_pPhysicsSystem = new PhysicsSystem(
		pPhysics, pPhysicsLoader, pTier0->getParameters(), &m_pWorld->getRegistry(), m_pTier0->getConsole());

	m_pNpcSystem = new NpcSystem(m_pTier0->getParameters(), m_pWorld);

	m_pControlSystem = new ControlSystem(
		m_pGraphicsSettings, m_pInput, m_pCamera, m_pActionControl, pPhysics,
		&m_pWorld->getRegistry());
	m_pCharacterSystem = new CharacterSystem(&m_pWorld->getRegistry());

	m_pMachineSystem = new MachineSystem(m_pResource, &m_pWorld->getRegistry(), pPhysicalConstants);
}

Game::~Game() {
	delete m_pRender;
	delete m_pResource;
	delete m_pTier1;
	delete m_pCamera;
	delete m_pTier0;
};

void Game::init() {
	m_pWorld->loadMap("dev", "test");
	m_pWorld->loadScene("dev", "test");

	m_pWorld->getSkybox()->loadSkybox("anime");


	auto dirLight = m_pWorld->getRegistry().create(); // temp
	auto dirLightComponent = m_pWorld->getRegistry().emplace<DirectionalLight>(dirLight);
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

	//m_pInput->addMappedKeyCallback(KeyCode::B, [this]() {
	//	entt::registry* registry = &m_pScene->getSceneRegistry();
	//	entt::entity entity = registry->create();

	//	std::cout << "ray sent" << std::endl;

	//	glm::vec3 position = m_pCamera->getPosition();
	//	glm::vec3 direction = m_pCamera->getCameraFront();

	//	RaycastQuery raycastQuery(position, direction);

	//	registry->emplace<RaycastQuery>(entity, raycastQuery);
	//});

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

	auto pRegistry = &m_pWorld->getRegistry();
	auto view = pRegistry->view<Properties>();

	for (auto&& [entity, properties] : view.each()) {
		if (properties.id == "cube_2") {
			pRegistry->emplace<Walkable>(entity);
		}
		if (properties.id == "surface") {
			pRegistry->emplace<Walkable>(entity);
		}
	}
}

void Game::input() {
	m_pConsoleGui->update();

	if (!m_pConsoleGui->isOpened()) { 
		m_pControlSystem->input();
	}

	m_pMachineSystem->input(Time::getDeltaTime());

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

	if (!m_pConsoleGui->isOpened()) {
		m_pControlSystem->input();
	}
	//m_pCamera->setPosition(cameraPos);

	m_pCharacterSystem->input();
}

void Game::update() {
	entt::registry* pRegistry = &m_pWorld->getRegistry();

	entt::entity surface;
	entt::entity surfaceScene;

	//if (pMapRegistry->view<Mesh>().size() == 0) {
	//	surface = pMapRegistry->create();
	//	surfaceScene = pRegistry->create();

	//	pRegistry->emplace<ModelRequest>(surfaceScene, "dev", "test_surface");
	//}

	m_pGraphicsSystems->update();
	m_pPhysicsSystem->update();
	m_pScriptSystem->update();
	m_pNpcSystem->update();
	m_pControlSystem->update();
	m_pCharacterSystem->update();
	m_pMachineSystem->update(Time::getDeltaTime());
	m_pMachineSystem->machineUpdate(Time::getDeltaTime());

	//if (pMapRegistry->view<Mesh>().size() == 0) {
	//	m_pGraphicsSystems->update();
	//	Model* model = &pRegistry->get<Model>(surfaceScene);
	//	auto meshEnt = model->meshes.at(0);
	//	entt::registry* pUtilReg = &m_pScene->getUtilRegistry();
	//	Mesh* pMesh = &pUtilReg->get<Mesh>(meshEnt);
	//	pMapRegistry->emplace<Mesh>(surface, *pMesh);
	//	VaoGl* pVao = &pUtilReg->get<VaoGl>(meshEnt);
	//	pMapRegistry->emplace<VaoGl>(surface, *pVao);
	//	MaterialSG* pMaterial = &pUtilReg->get<MaterialSG>(meshEnt);
	//	pMapRegistry->emplace<MaterialSG>(surface, *pMaterial);

	//	ShaderGl shader = pRegistry->get<ShaderGl>(surfaceScene);
	//	pMapRegistry->emplace<ShaderGl>(surface, shader);

	//	pMapRegistry->emplace<Transform>(surface, glm::vec3(0, -1, 0), glm::vec3(0, 0, 0), glm::vec3(100, 0.1, 100));
	//}

	auto view = pRegistry->view<Transform, Properties>();

	//for (auto& entity : view) {
	//	if (view.get<Properties>(entity).id == "cube") {
	//		auto& transform = view.get<Transform>(entity);
	//		transform.rotation *= glm::angleAxis(glm::radians(1.f), glm::vec3(0.f, 1.f, 0.f));
	//	}
	//}

	m_pGui->update();
}

void Game::render() {
	m_pScriptSystem->frame();
	m_pGraphicsSystems->frame();
	m_pMachineSystem->frame(Time::getDeltaTime());
	m_pRender->render();
}

void Game::cleanUp() {}

