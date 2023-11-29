#pragma once

#include "lc_client/i_game_logic.h"

#include "lc_client/eng_graphics/i_window.h"
#include "lc_client/eng_graphics/i_render.h"
#include "lc_client/eng_input/i_input.h"
#include "lc_client/eng_scene/scene.h"
#include "lc_client/tier1/i_shaders.h"
#include "lc_client/tier1/tier1.h"
#include "lc_client/util/i_eng_resource.h"
#include "lc_client/tier1/openGL/gl_texture_manager.h"
#include "lc_client/eng_graphics/camera/camera.h"
#include "lc_client/eng_model/model_manager.h"
#include "lc_client/eng_script/script_system.h"
#include "lc_client/systems.h"
#include "lc_client/eng_graphics/mesh_work.h"
#include "lc_client/eng_graphics/shader_work.h"
#include "lc_client/tier0/tier0.h"
#include "lc_client/eng_gui/gui_console.h"
#include "lc_client/eng_cubemaps/cubemap_work.h"
#include "lc_client/eng_map/map.h"
#include "lc_client/eng_gui/layout/layout_controller.h"
#include "lc_client/eng_gui/view/gui_presenter.h"
#include "lc_client/eng_graphics/openGL/gl_shader_work.h"
#include "lc_client/eng_graphics/gui/text_render.h"


class Game : public IGameLogic {
public:
	Game(IWindow *pWindow, Tier0* pTier0);
	virtual ~Game();

	void init();
	void input();
	void update();
	void render();
	void cleanUp();

	void setUpGui(ShaderWorkGl* pShaderWorkGl);

private:
	IWindow* m_pWindow = nullptr;
	IInput* m_pInput = nullptr;
	Camera* m_pCamera = nullptr;
	IRender* m_pRender = nullptr;
	Scene* m_pScene = nullptr;
	Map* m_pMap = nullptr;
	eng::IResource* m_pResource = nullptr;
	ModelManager* m_pModelManager = nullptr;
	Systems* m_pSystems = nullptr;
	MeshWork* m_pMeshWork = nullptr;
	ShaderWork* m_pShaderWorkScene = nullptr;
	ConsoleGui* m_pConsoleGui = nullptr;
	CubemapWork* m_pCubemapWork = nullptr;

	LayoutController* m_pLayoutController = nullptr;
	GuiPresenter* m_pGuiPresenter = nullptr;
	Layout* m_pGuiLayout = nullptr;
	BackgroundRender* m_pBackgroundRender = nullptr;
	TextRender* m_pTextRender = nullptr;


	Tier0* m_pTier0 = nullptr;
	Tier1* m_pTier1 = nullptr;

	double m_lastMousePosX = 0.0;
	double m_lastMousePosY = 0.0;
	float m_sensivity = 0.1f;
};
