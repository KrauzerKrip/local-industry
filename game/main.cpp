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

	std::cout << "main 1" << std::endl; // DEBUG

	IWindow* pWindow = new WindowGL(title, width, height, new int[2]{16, 9}, vSync, 45.0);
	std::cout << "main 2" << std::endl; // DEBUG
	IGameLogic* pGameLogic = new Game(pWindow);
	std::cout << "main 3" << std::endl; // DEBUG
	Loop* pLoop = Loop::createInstance(pWindow, pGameLogic, targetFPS, targetUPS);
	std::cout << "main 4" << std::endl; // DEBUG

	pLoop->init();
	std::cout << "main 5" << std::endl; // DEBUG

	pLoop->startLoop();
	std::cout << "main 6" << std::endl; // DEBUG

	pLoop->cleanUp();
	pWindow->terminate(); // mb in loop

	std::cout << "main 7" << std::endl; // DEBUG

	delete pLoop;
	delete pWindow;
	delete pGameLogic;
	
}



