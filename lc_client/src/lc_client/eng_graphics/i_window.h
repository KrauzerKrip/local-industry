#pragma once

#include <lc_client/local_engine.h>

#include <array>
#include <functional>

#include <GLFW/glfw3.h>

#include "lc_client/eng_input/i_input.h"


enum class WindowMode {
	GAME,
	GUI
};


/**
* Window interface to be implemented by window class (e.g gl_window.h).
*
*/
class IWindow {
public: 
	
	virtual ~IWindow() {};

	virtual void init() = 0;
	virtual void startFrame() = 0; 
	virtual void update() = 0;
	virtual bool windowShouldClose() = 0;
	virtual void terminate() = 0;
	virtual IInput* getInput() = 0;
	virtual void setMode(WindowMode mode) = 0;
	virtual WindowMode getMode() = 0;
	virtual void setResizeCallback(std::function<void(int, int)> callback) = 0;
	
	/**
	 * Breaks encapsulation
	 * remove it and 
	 * 
	 * DO NOT USE IT
	 * 
	 * NEVER
	 * 
	 * IN THE NAME OF FLANDRE 
	 * IN THE NAME OF CHRIST
	 * 
	 * DO NOT USE IT
	 */
	virtual GLFWwindow* getGlfwWindow() = 0;

	virtual int* getAspectRatio() = 0;
	virtual float getFov() = 0;
	virtual void setFov(float fov) = 0;
	virtual std::array<int, 2> getSize() = 0;
};