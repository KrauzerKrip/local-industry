#include "main.h"

#include <iostream>
#include <string>

#include "game.h"
#include "lc_client/loop.h"
#include "lc_client/eng_graphics/i_window.h"
#include "lc_client/eng_graphics/openGL/gl_window.h"

int main() {

	std::string title = "Local` Engine";
	int width = 1080;
	int height = 720;
	bool vSync = true;

	int targetFPS = 60;
	int targetUPS = 60;

	IWindow* pWindow = new WindowGL(title, width, height, new int[2]{16, 9}, vSync, 45.0);
	IGameLogic* pGameLogic = new Game(pWindow);
	Loop* pLoop = Loop::createInstance(pWindow, pGameLogic, targetFPS, targetUPS);

	pLoop->init();

	pLoop->startLoop();

	pLoop->cleanUp();
	pWindow->terminate(); // mb in loop

	delete pLoop;
	delete pWindow;
	delete pGameLogic;
	
}



