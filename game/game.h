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


class Game : public IGameLogic {
public:
	Game(IWindow *pWindow, Tier0* pTier0);
	virtual ~Game();

	void init();
	void input();
	void update();
	void render();
	void cleanUp();

private:
	IWindow* m_pWindow;;
	IInput* m_pInput;
	Camera* m_pCamera;
	IRender* m_pRender;
	Scene* m_pScene;
	eng::IResource* m_pResource;
	ModelManager* m_pModelManager;
	Systems* m_pSystems;
	MeshWork* m_pMeshWork;
	ShaderWork* m_pShaderWorkScene;
	ConsoleGui* m_pConsoleGui;

	Tier0* m_pTier0;
	Tier1* m_pTier1;

	double m_lastMousePosX = 0.0;
	double m_lastMousePosY = 0.0;
	float m_sensivity = 0.1f;
};
