#include "main.h"

#include <iostream>
#include <string>

#include "game.h"
#include "lc_client/loop.h"
#include "lc_client/eng_graphics/i_window.h"
#include "lc_client/eng_graphics/openGL/gl_window.h"
#include "lc_client/tier0/tier0.h"


int main() {

	std::string title = "Local` Engine";
	// int width = 1080;
	// int height = 720;
	int width = 1920;
	int height = 1080;
	bool vSync = true;

	int targetFPS = 60;
	int targetUPS = 60;

	Tier0* pTier0 = nullptr;

	IWindow* pWindow = nullptr;
	IGameLogic* pGameLogic = nullptr;
	Loop* pLoop = nullptr;

	try {
		Tier0* pTier0 = new Tier0();

		IWindow* pWindow = new WindowGL(title, width, height, new int[2]{16, 9}, vSync, 45.0);
		IGameLogic* pGameLogic = new Game(pWindow, pTier0);
		Loop* pLoop = Loop::createInstance(pWindow, pGameLogic, targetFPS, targetUPS);

		pLoop->init();
		pLoop->startLoop();

		pLoop->cleanUp();
		pWindow->terminate(); // mb in loop
	}
	catch (std::runtime_error& exception) {
		std::cerr << "Exception: " << exception.what() << std::endl;
		exit(-1);
	}

	if (pLoop) {
		delete pLoop;
	}

	if (pWindow) {
		delete pWindow;
	}
	if (pGameLogic) {
		delete pGameLogic;
	}
	if (pTier0) {
		delete pTier0;
	}

	exit(0);
}
