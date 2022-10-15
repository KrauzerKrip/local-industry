#pragma once

#include "lc_client/i_game_logic.h"

#include "lc_client/eng_graphics/i_window.h"
#include "lc_client/eng_input/i_input.h"

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
};
