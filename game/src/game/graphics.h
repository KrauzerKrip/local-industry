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


class Graphics {
public:
	Graphics(Tier0* pTier0, Tier1* pTier1, IWindow* pWindow, eng::IResource* pResource, World* pWorld, Camera* pCamera, IInput* pInput, ActionControl* pActionControl);

	IRender* getRender();
	Gui* getGui();
	GraphicsSettings* getSettings();
	GraphicsSystems* getSystems();

private:
	std::unique_ptr<RenderGL> m_render;
	std::unique_ptr<Gui> m_gui;
	std::unique_ptr<GraphicsSettings> m_graphicsSettings;
	std::unique_ptr<GraphicsSystems> m_graphicsSystems;
};