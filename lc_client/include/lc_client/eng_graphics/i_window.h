/**
* Window interface to be implemented by window class (e.g gl_window.h).
* 
*/

#pragma once

class IWindow {
public: 
	
	virtual ~IWindow() {};

	virtual void init() = 0;
	virtual void update() = 0;
};