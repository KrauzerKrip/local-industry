#pragma once

#include "eng_graphics/i_window.h"
#include "i_game_logic.h"

class Loop {
public:

	static Loop* createInstance(IWindow* pWindow, IGameLogic* pGameLogic, int targetFPS, int targetUPS);
	static Loop* getInstance(); 

	Loop(Loop const&) = delete;
	void operator=(Loop const&) = delete;

	void init();
	void startLoop();
	void cleanUp();

private:
	Loop(IWindow* pWindow, IGameLogic* pGameLogic, int targetFPS, int targetUPS);

	IWindow* m_pWindow;
	IGameLogic* m_pGameLogic;
	int m_targetFPS;
	int m_targetUPS;
	double m_deltaTime;

	static Loop* m_pInstance;

	
};