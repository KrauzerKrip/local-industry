#include "main.h"

#include <string>

#include "lc_client/loop.h"
#include "lc_client/eng_graphics/i_window.h"
#include "lc_client/eng_graphics/openGL/gl_window.h"

int main() {

	std::string title = "Local` Engine";
	int width = 720;
	int height = 1080;
	bool vSync = true;

	IWindow* pWindow = new WindowGL(title, width, height, vSync);
	pWindow->init(); //should be in the loop

	return 0;
}