#include "graphics.h"

#include "lc_client/eng_graphics/graphics_settings.h"
#include "lc_client/eng_graphics/openGL/gl_framebuffer_controller.h"
#include "lc_client/eng_graphics/openGL/gl_render.h"
#include "game/gui/dependencies_fabric/openGL/gl_gui_dependencies_fabric.h"


Graphics::Graphics(Tier0* pTier0, IWindow* pWindow, eng::IResource* pResource, World* pWorld,
	Camera* pCamera, IInput* pInput, ActionControl* pActionControl) {
	m_pTier0 = pTier0;
	m_pResource = pResource;
	m_pActionControl = pActionControl;
	m_pWindow = pWindow;
	m_pWorld = pWorld;
	m_pInput = pInput;
	m_pCamera = pCamera;

	m_graphicsSettings = std::make_unique<GraphicsSettings>(pTier0->getParameters());
	m_graphicsSettings->addUpdateCallback([pWindow](GraphicsSettings* pGraphicsSettings) {
		pWindow->setSize(pGraphicsSettings->getWindowSize()[0], pGraphicsSettings->getWindowSize()[1]);
		pWindow->setWindowMode(pGraphicsSettings->getWindowMode());
	});
	
	m_loaderFabric = std::make_unique<LoaderFabricGl>(pResource, pTier0->getConsole());

	m_modelManager = std::make_unique<ModelManager>(
		pResource, pWorld->getUtilRegistry(), pTier0->getConsole());
	m_modelParser = std::make_unique<ModelParser>(pResource);

	m_textureManager = std::make_unique<TextureManagerGl>(m_pResource);

	m_skyboxRender = std::make_unique<SkyboxRenderGl>(m_loaderFabric->getShaderLoaderGl());
}

void Graphics::load() {}

void Graphics::recreate() { 
	if (m_debug) {
		int i = 0;
	}

	m_debug = true;

	entt::registry* pRegistry = &m_pWorld->getRegistry();

	m_textureManager->reload();
	m_shaderManager.reset();

	m_shaderManager = std::make_unique<ShaderManagerGl>(m_pResource);

	m_shaderManager->loadShaders();

	m_loaderFabric->getShaderLoaderGl()->setShaderManager(m_shaderManager.get());

	m_skyboxRender->reload();

	m_modelManager->setTextureManager(m_textureManager.get());

	FramebufferController* pFramebufferController = new FramebufferController(m_pWindow);

	m_graphicsSystems.reset();
	m_graphicsSystems = std::make_unique<GraphicsSystems>(m_pTier0, static_cast<ShaderManager*>(m_shaderManager.get()),
		static_cast<TextureManager*>(m_textureManager.get()), m_loaderFabric->getShaderLoaderGl(),
		m_loaderFabric->getMeshLoader(), m_loaderFabric->getCubemapLoader(), m_pWorld, m_modelManager.get(),
		m_modelParser.get(), static_cast<SkyboxRender*>(m_skyboxRender.get()), m_pResource);

	GuiDependenciesFabric* pGuiDependenciesFabric = new GuiDependenciesFabricGl(m_pTier0->getConsole(),
		m_loaderFabric->getShaderLoaderGl(), m_pInput, m_textureManager.get(), pFramebufferController, m_pWindow);
	m_gui = std::make_unique<Gui>(m_pTier0, pGuiDependenciesFabric, m_pInput, m_pActionControl, m_graphicsSettings.get(), m_pCamera, pRegistry);
	m_render = std::make_unique<RenderGL>(m_pWindow, m_pCamera, m_loaderFabric->getShaderLoaderGl(), m_skyboxRender.get(),
		pFramebufferController, m_gui->getPresenter(), m_graphicsSettings.get());

	m_render->setDependecies(m_pWorld);
	m_render->init();

	auto models = pRegistry->view<Model>();

	std::cout << "Graphics" << std::endl;
	for (auto&& [entity, model] : models.each()) {
		pRegistry->emplace_or_replace<MeshUnloadRequest>(entity);
		pRegistry->emplace_or_replace<MeshLoadRequest>(entity);
		pRegistry->emplace_or_replace<ShaderReloadRequest>(entity);
	}
}

IRender* Graphics::getRender() { return m_render.get(); }

Gui* Graphics::getGui() { return m_gui.get(); }

GraphicsSettings* Graphics::getSettings() { return m_graphicsSettings.get(); }

GraphicsSystems* Graphics::getSystems() { return m_graphicsSystems.get(); }

TextureManager* Graphics::getTextureManager() { return m_textureManager.get(); }
