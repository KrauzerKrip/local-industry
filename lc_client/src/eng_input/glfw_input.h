#pragma once
#include "lc_client/eng_input/i_input.h"
#include "lc_client/eng_graphics/i_window.h"

class InputGlfw : public IInput {
public:
	InputGlfw(IWindow* pWindow);
	virtual ~InputGlfw();

	bool getKeyPressed(const char* key);

private: 
	IWindow* m_pWindow;
};