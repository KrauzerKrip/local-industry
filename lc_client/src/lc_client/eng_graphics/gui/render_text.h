#pragma once

#include "lc_client/tier0/console/i_console.h"
#include "lc_client/eng_gui/paint_objects/text.h"

class RenderText {
public:
	RenderText(IConsole* pConsole) : m_pConsole(pConsole){};
	virtual ~RenderText(){};
	
	virtual void render(Text& text) = 0;
	
protected:
	IConsole* m_pConsole = nullptr;
};