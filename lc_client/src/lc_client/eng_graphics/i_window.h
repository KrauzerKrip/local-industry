/**
* Window interface to be implemented by window class (e.g gl_window.h).
* 
*/

#pragma once

#include "lc_client/eng_input/i_input.h"

class IWindow {
public: 
	
	virtual ~IWindow() {};

	virtual void init() = 0;
	virtual void update() = 0;
	virtual bool windowShouldClose() = 0;
	virtual void terminate() = 0;
	virtual IInput* getInput() = 0;
	virtual bool isKeyPressed(int key) = 0;
};