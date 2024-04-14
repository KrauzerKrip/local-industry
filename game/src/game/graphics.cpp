#include "graphics.h"


Graphics::Graphics(Tier0* pTier0, IWindow* pWindow, eng::IResource* pResource, World* pWorld,
	Camera* pCamera, GuiPresenter* pGuiPresenter) {
	m_pTier0 = pTier0;
	m_pResource = pResource;
	m_pWindow = pWindow;
	m_pWorld = pWorld;
	m_pCamera = pCamera;

	m_graphicsSettings = std::make_unique<GraphicsSettings>(pTier0->getParameters());
	m_graphicsSettings->addUpdateCallback([pWindow](GraphicsSettings* pGraphicsSettings) {
		if (pGraphicsSettings->getWindowMode() == WindowMode::FULLSCREEN) {
			pWindow->setSize(1920, 1080);
		}
		else {
			pWindow->setSize(pGraphicsSettings->getWindowSize()[0], pGraphicsSettings->getWindowSize()[1]);
		}
		pWindow->setVSync(pGraphicsSettings->getVSync());
		pWindow->setTargetFps(pGraphicsSettings->getTargetFps());
		pWindow->setWindowMode(pGraphicsSettings->getWindowMode());
	});
	
	m_loaderFabric = std::make_unique<LoaderFabricGl>(pResource, pTier0->getConsole());

	m_textureManager = std::make_unique<TextureManagerGl>(m_pResource);

	m_modelManager = std::make_unique<ModelManager>(m_textureManager.get(), 
		pResource, pWorld->getUtilRegistry(), pTier0->getConsole());
	m_modelParser = std::make_unique<ModelParser>(pResource);

	m_skyboxRender = std::make_unique<SkyboxRenderGl>(m_loaderFabric->getShaderLoaderGl());

	m_framebufferController = std::make_unique<FramebufferController>(m_pWindow);

	m_render = std::make_unique<RenderGL>(m_pWindow, m_pCamera, m_loaderFabric->getShaderLoaderGl(),
		m_skyboxRender.get(), m_framebufferController.get(), pGuiPresenter, m_graphicsSettings.get());

	m_render->setDependecies(m_pWorld);
}

void Graphics::init() { 
	m_shaderManager.reset();
	m_shaderManager = std::make_unique<ShaderManagerGl>(m_pResource);
	m_shaderManager->loadShaders();
	m_loaderFabric->getShaderLoaderGl()->setShaderManager(m_shaderManager.get());
	m_skyboxRender->reload();
	m_textureManager->reload();

	m_graphicsSystems.reset();
	m_graphicsSystems = std::make_unique<GraphicsSystems>(m_pTier0, static_cast<ShaderManager*>(m_shaderManager.get()),
		static_cast<TextureManager*>(m_textureManager.get()), m_loaderFabric->getShaderLoaderGl(),
		m_loaderFabric->getMeshLoader(), m_loaderFabric->getCubemapLoader(), m_pWorld, m_modelManager.get(),
		m_modelParser.get(), static_cast<SkyboxRender*>(m_skyboxRender.get()), m_pResource);

	m_render->init();
}

IRender* Graphics::getRender() { return m_render.get(); }

GraphicsSettings* Graphics::getSettings() { return m_graphicsSettings.get(); }

GraphicsSystems* Graphics::getSystems() { return m_graphicsSystems.get(); }

TextureManager* Graphics::getTextureManager() { return m_textureManager.get(); }

LoaderFabricGl* Graphics::getLoaderFabric() { return m_loaderFabric.get(); }

FramebufferController* Graphics::getFramebufferController() { return m_framebufferController.get(); }
