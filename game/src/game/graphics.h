#pragma once

#include <memory>

#include "lc_client/tier0/tier0.h"
#include "lc_client/tier1/tier1.h"
#include "lc_client/util/i_eng_resource.h"
#include "lc_client/eng_graphics/i_window.h"
#include "lc_client/eng_world/world.h"
#include "lc_client/eng_graphics/camera/camera.h"
#include "game/gui/gui.h"
#include "game/control/action_control.h"
#include "lc_client/eng_graphics/openGL/gl_render.h"
#include "lc_client/eng_systems/graphics_systems.h"
#include "lc_client/eng_graphics/openGL/gl_shader_manager.h"
#include "lc_client/eng_graphics/openGL/gl_texture_manager.h"
#include "loader_fabric/openGL/gl_loader_fabric.h"
#include "lc_client/eng_model/model_manager.h"
#include "lc_client/eng_model/model_parser.h"


class Graphics {
public:
	Graphics(Tier0* pTier0, IWindow* pWindow, eng::IResource* pResource, World* pWorld, Camera* pCamera, IInput* pInput, ActionControl* pActionControl);

	void load();
	void recreate();

	IRender* getRender();
	Gui* getGui();
	GraphicsSettings* getSettings();
	GraphicsSystems* getSystems();
	TextureManager* getTextureManager();


private:
	std::unique_ptr<RenderGL> m_render;
	std::unique_ptr<Gui> m_gui;
	std::unique_ptr<GraphicsSettings> m_graphicsSettings;
	std::unique_ptr<GraphicsSystems> m_graphicsSystems;
	std::unique_ptr<ShaderManagerGl> m_shaderManager;
	std::unique_ptr<TextureManagerGl> m_textureManager;
	std::unique_ptr<LoaderFabricGl> m_loaderFabric;
	std::unique_ptr<SkyboxRenderGl> m_skyboxRender;
	std::unique_ptr<ModelManager> m_modelManager;
	std::unique_ptr<ModelParser> m_modelParser;

	Tier0* m_pTier0 = nullptr;
	eng::IResource* m_pResource = nullptr;
	IWindow* m_pWindow = nullptr;
	World* m_pWorld;
	IInput* m_pInput = nullptr;
	ActionControl* m_pActionControl = nullptr;
	Camera* m_pCamera = nullptr;

	bool m_debug = false;
};