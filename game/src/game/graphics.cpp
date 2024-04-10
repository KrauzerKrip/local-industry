#include "graphics.h"

#include "lc_client/eng_graphics/graphics_settings.h"
#include "loader_fabric/openGL/gl_loader_fabric.h"
#include "lc_client/eng_model/model_manager.h"
#include "lc_client/eng_model/model_parser.h"
#include "lc_client/eng_graphics/openGL/gl_framebuffer_controller.h"
#include "lc_client/eng_graphics/openGL/gl_render.h"
#include "game/gui/dependencies_fabric/openGL/gl_gui_dependencies_fabric.h"


Graphics::Graphics(Tier0* pTier0, Tier1* pTier1, IWindow* pWindow, eng::IResource* pResource, World* pWorld,
	Camera* pCamera, IInput* pInput, ActionControl* pActionControl) {
	m_graphicsSettings = std::make_unique<GraphicsSettings>(pTier0->getParameters());
	m_graphicsSettings->addUpdateCallback([pWindow](GraphicsSettings* pGraphicsSettings) {
		pWindow->setSize(pGraphicsSettings->getWindowSize()[0], pGraphicsSettings->getWindowSize()[1]);
		pWindow->setWindowMode(pGraphicsSettings->getWindowMode());
	});
	
	pTier1->getShaderManager()->loadShaders();

	LoaderFabricGl* pLoaderFabric =
		new LoaderFabricGl(pResource, pTier0->getConsole(), pTier1->getShaderManager());

	ModelManager* pModelManager = new ModelManager(
		pResource, pTier1->getTextureManager(), pWorld->getUtilRegistry(), pTier0->getConsole());
	ModelParser* pModelParser = new ModelParser(pResource);

	FramebufferController* pFramebufferController = new FramebufferController(pWindow);

	SkyboxRenderGl* pSkyboxRender = new SkyboxRenderGl(pLoaderFabric->getShaderLoaderGl());

	GuiDependenciesFabric* pGuiDependenciesFabric =
		new GuiDependenciesFabricGl(pTier0->getConsole(), pLoaderFabric->getShaderLoaderGl(),
			pInput, pTier1->getTextureManager(), pFramebufferController, pWindow);
	m_gui = std::make_unique<Gui>(pTier0, pGuiDependenciesFabric, pInput, pActionControl, m_graphicsSettings.get(), pCamera,
		&pWorld->getRegistry());
	m_render = std::make_unique<RenderGL>(pWindow, pCamera, pLoaderFabric->getShaderLoaderGl(), pSkyboxRender,
		pFramebufferController, m_gui->getPresenter(), m_graphicsSettings.get());

	m_render->setDependecies(pWorld);

	m_render->init();

	m_graphicsSystems = std::make_unique<GraphicsSystems>(pTier0, pTier1, pLoaderFabric->getShaderLoaderGl(), pLoaderFabric->getMeshLoader(),
			pLoaderFabric->getCubemapLoader(), pWorld, pModelManager, pModelParser, pSkyboxRender, pResource);
}

IRender* Graphics::getRender() { return m_render.get(); }

Gui* Graphics::getGui() { return m_gui.get(); }

GraphicsSettings* Graphics::getSettings() { return m_graphicsSettings.get(); }

GraphicsSystems* Graphics::getSystems() { return m_graphicsSystems.get(); }
