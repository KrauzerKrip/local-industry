#pragma once

#include "lc_client/i_game_logic.h"

class Game : public IGameLogic {
	virtual ~Game();

	void init();
	void update();
	void render();
	void cleanUp();
};
