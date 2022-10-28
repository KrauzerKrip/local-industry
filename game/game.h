#pragma once

#include "lc_client/i_game_logic.h"

#include "lc_client/eng_graphics/i_window.h"
#include "lc_client/eng_graphics/i_render.h"
#include "lc_client/eng_input/i_input.h"
#include "lc_client/eng_scene/scene.h"
#include "lc_client/eng_procedures/i_shaders.h"
#include "lc_client/eng_procedures/shaders.h"

class Game : public IGameLogic {
public:
	Game(IWindow *pWindow);
	virtual ~Game();

	void init();
	void update();
	void render();
	void cleanUp();

private:
	IWindow* m_pWindow;;
	IInput* m_pInput;
	IRender* m_pRender;
	Scene* m_pScene;
	IShaderManager* m_pShaderManager;
};
