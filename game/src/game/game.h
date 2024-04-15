#pragma once

#include "lc_client/i_game_logic.h"

#include "lc_client/eng_graphics/i_window.h"
#include "lc_client/eng_graphics/openGl/gl_render.h"
#include "lc_client/eng_input/i_input.h"
#include "lc_client/eng_world/world.h"
#include "lc_client/tier1/tier1.h"
#include "lc_client/util/i_eng_resource.h"
#include "lc_client/eng_graphics/camera/camera.h"
#include "lc_client/eng_model/model_manager.h"
#include "lc_client/eng_script/script_system.h"
#include "lc_client/eng_graphics/mesh_loader.h"
#include "lc_client/eng_graphics/shader_loader.h"
#include "lc_client/tier0/tier0.h"
#include "lc_client/eng_gui/gui_console.h"
#include "lc_client/eng_gui/layout/layout_controller.h"
#include "lc_client/eng_gui/view/gui_presenter.h"
#include "lc_client/eng_graphics/openGL/gl_shader_loader.h"
#include "lc_client/eng_graphics/gui/text_render.h"
#include "game/gui/gui.h"
#include "lc_client/eng_graphics/graphics_settings.h"
#include "game/loader_fabric/loader_fabric.h"
#include "game/control/action_control.h"
#include "lc_client/eng_systems/graphics_systems.h"
#include "game/control/control_system.h"
#include "lc_client/eng_npc/npc_system.h"
#include "machine/machine_system.h"
#include "game/graphics.h"
#include "agriculture/agriculture_system.h"


import character;


class Game : public IGameLogic {
public:
	Game(IWindow *pWindow, Tier0* pTier0);
	virtual ~Game();

	void init();
	void input(double deltaTime);
	void update(double updateInterval);
	void render();
	void cleanUp();

private:
	eng::IResource* m_pResource = nullptr;
	Tier0* m_pTier0 = nullptr;
	Tier1* m_pTier1 = nullptr;

	IWindow* m_pWindow = nullptr;
	IInput* m_pInput = nullptr;
	Camera* m_pCamera = nullptr;
	ActionControl* m_pActionControl = nullptr;
	World* m_pWorld = nullptr;
	Graphics* m_pGraphics = nullptr;
	ConsoleGui* m_pConsoleGui = nullptr;
	PhysicsSystem* m_pPhysicsSystem = nullptr;
	ScriptSystem* m_pScriptSystem = nullptr;
	NpcSystem* m_pNpcSystem = nullptr;
	ControlSystem* m_pControlSystem = nullptr;
	CharacterSystem* m_pCharacterSystem = nullptr;
	MachineSystem* m_pMachineSystem = nullptr;
	AgricultureSystem* m_pAgricultureSystem = nullptr;

	Gui* m_pGui = nullptr;

	bool m_guiMode = false;

	double m_lastMousePosX = 0.0;
	double m_lastMousePosY = 0.0;
	float m_sensivity = 0.1f;
};
