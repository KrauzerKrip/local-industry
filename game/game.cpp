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
#include "lc_client/eng_graphics/openGL/gl_mesh_work.h"
#include "lc_client/eng_graphics/openGL/gl_shader_work.h"
#include "lc_client/eng_gui/gui_console.h"
#include "lc_client/eng_scene/skybox.h"
#include "lc_client/eng_cubemaps/cubemap_loader.h"
#include "lc_client/util/pack.h"
#include "lc_client/eng_cubemaps/openGL/gl_cubemap_work.h"
#include "lc_client/eng_gui/layout/layouts/frame.h"
#include "lc_client/eng_gui/widgets/widget.h"
#include "lc_client/eng_graphics/gui/openGL/gl_background_render.h"
#include "lc_client/eng_gui/widgets/text_widget.h"
#include "lc_client/eng_graphics/openGL/gl_skybox_render.h"

#include "lc_client/tier0/console/i_console.h"

#include "lc_client/eng_graphics/openGL/gl_window.h"
#include "lc_client/eng_script/entt/components.h"


Game::Game(IWindow* pWindow, Tier0* pTier0) {
	m_pWindow = pWindow;
	m_pCamera = new Camera();
	m_pResource = new eng::Resource("E:/Industry/industry/res/"); 
	m_pTier0 = pTier0;
	m_pTier1 = new Tier1Gl(m_pResource, pTier0);
	m_pMap = new Map();
	m_pLayoutController = new LayoutController();
}

Game::~Game() {
	delete m_pRender;
	delete m_pResource;
	delete m_pTier1;
	delete m_pCamera;
	delete m_pTier0;
};

void Game::init() {
	m_pConsoleGui = new ConsoleGui(
		m_pTier0->getConsole(), m_pTier0->getImGuiFonts(), m_pTier1->getTextureManager(), m_pTier0->getParameters());

	m_pInput = m_pWindow->getInput();

	m_pTier1->getShaderManager()->loadShaders();
	
	SceneLoading* pSceneLoading = new SceneLoading(m_pResource);
	m_pScene = new Scene(m_pResource, pSceneLoading);
	SceneControlling::setScene(m_pScene);

	m_pModelManager = new ModelManager(
		m_pResource, m_pTier1->getTextureManager(), m_pScene->getUtilRegistry(), m_pTier0->getConsole());

	m_pMeshWork = new MeshWorkGl();
	auto pShaderWork = new ShaderWorkGl(m_pTier1->getShaderManager(), m_pTier0->getConsole());
	m_pShaderWorkScene = pShaderWork;

	Pack pack = Pack::getPack("dev");
	std::string skyboxPath = Pack::Skybox(pack, "anime").getPath();
	std::unique_ptr<CubemapMaterial> skyboxMaterial = CubemapLoader(skyboxPath, m_pResource).getMaterial();
	SkyboxRender* pSkyboxRender = new SkyboxRenderGl(skyboxMaterial.get(), pShaderWork);
	Skybox* pSkybox = new Skybox(pSkyboxRender);

    m_pBackgroundRender = new BackgroundRenderGl(m_pTier0->getConsole(), pShaderWork);
	m_pTextRender = new TextRenderGl(m_pTier0->getConsole(), pShaderWork);

	std::vector<QueueRender*> queueRenders;
	m_pGuiPresenter = new GuiPresenter(m_pLayoutController, queueRenders);

	m_pRender = new RenderGL(m_pWindow, m_pCamera, pShaderWork, m_pGuiPresenter);

	m_pScene->loadScene("dev", "test");
	m_pMap->loadMap("dev", "test");

	m_pRender->setDependecies(m_pMap, m_pScene, pSkybox);

	m_pRender->init();

	m_pCubemapWork = new CubemapWorkGl(m_pResource);

	m_pSystems = new Systems(m_pTier1, m_pShaderWorkScene, m_pMeshWork, m_pCubemapWork, m_pScene, m_pMap, m_pModelManager);

	pSkybox->setLightColor(255, 255, 200); // 255, 255, 236
	pSkybox->setLightStrength(0.4f);


	auto dirLight = m_pScene->getSceneRegistry().create(); // temp
	auto dirLightComponent = m_pScene->getSceneRegistry().emplace<DirectionalLight>(dirLight);
	dirLightComponent.color = glm::vec3(1, 1, 1);
	dirLightComponent.direction = glm::vec3(-0.2f, -1.0f, -0.3f);

	m_pInput->addKeyCallback("GRAVE_ACCENT", [pConsoleGui = this->m_pConsoleGui, pWindow = this->m_pWindow]() {
		if (pConsoleGui->isOpened()) {
			pConsoleGui->close();
		}
		else {
			pConsoleGui->open();
		}
	});

	setUpGui(pShaderWork);
}

void Game::input() {

	if (m_pConsoleGui->isOpened()) {
		if (m_pWindow->getMode() == WindowMode::GAME) {
			m_pWindow->setMode(WindowMode::GUI);
		}
	}
	else {
		if (m_pWindow->getMode() == WindowMode::GUI) {
			m_pWindow->setMode(WindowMode::GAME);
		}
	}

	m_pConsoleGui->update();

	if (m_pInput->isKeyPressed("ESC")) {
		exit(0);
	}

	if (m_pConsoleGui->isOpened()) {
		m_lastMousePosX = m_pInput->getMousePosX();
		m_lastMousePosY = m_pInput->getMousePosY();
		return;
	}

	float offsetMouseX = (float) (m_pInput->getMousePosX() - m_lastMousePosX);
	float offsetMouseY = (float) (m_lastMousePosY - m_pInput->getMousePosY());

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
			cameraSpeed *= 2.0f;
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
	}
	catch (UnknownKeyCodeException& exception) {
		std::cerr << exception.what() << std::endl;
	}

	m_pCamera->setPosition(cameraPos);
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

	m_pLayoutController->update();

}

void Game::render() {
	m_pSystems->frame();
	m_pRender->render();
}

void Game::cleanUp() {}

void Game::setUpGui(ShaderWorkGl* pShaderWorkGl) { 
	std::shared_ptr<Frame> frame = std::make_shared<Frame>();

	Background background(glm::vec4(1, 1, 1, 0.8));
	Background background2(glm::vec4(0, 1, 1, 0.8));

	std::shared_ptr<Widget> widget = std::make_shared<Widget>(background, m_pBackgroundRender);
	widget->setPosition(glm::vec2(25, 25));
	widget->setSize(glm::vec2(400, 200));
	frame->addChild(widget);

	std::shared_ptr<Layout> layout2 = std::make_shared<Frame>();
	widget->setLayout(layout2);
	std::shared_ptr<Widget> widget2 = std::make_shared<Widget>(background2, m_pBackgroundRender);
	widget2->setPosition(glm::vec2(50, 100));
	widget2->setSize(glm::vec2(50, 50));
	//layout2->addChild(widget2);

	Background background3(glm::vec4(1, 1, 1, 0));
	TextRender* pTextRender = new TextRenderGl(m_pTier0->getConsole(), pShaderWorkGl);
	std::shared_ptr<TextWidget> textWidget =
		std::make_shared<TextWidget>(background3, m_pBackgroundRender, m_pTextRender);
	textWidget->setPosition(glm::vec2(50, 100));
	textWidget->setTextSize(1);
	textWidget->setColor(glm::vec4(0, 0, 0, 1));
	textWidget->setText("Test");
	layout2->addChild(textWidget);

	m_pLayoutController->setLayout(frame);
}
