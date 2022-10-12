#

#include "lc_client/loop.h"
#include "lc_client/eng_graphics/i_window.h"
#include "lc_client/eng_graphics/openGL/gl_window.h"

int main() {

	

	IWindow* pWindow = new WindowGL();
	pWindow->init(); //should be on loop

}