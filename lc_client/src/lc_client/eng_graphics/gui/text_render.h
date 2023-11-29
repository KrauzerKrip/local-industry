#pragma once

#include <string>
#include <glm/glm.hpp>
#include "lc_client/eng_gui/paint_objects/text.h"
#include "lc_client/tier0/console/i_console.h"


class TextRender {
public:
	TextRender(IConsole* pConsole) : m_pConsole(pConsole){};
	virtual ~TextRender(){};
	
	virtual void render(
		std::string text, glm::vec4 color, glm::vec2 absolutePosition, unsigned int size, unsigned int layer) = 0;
	
protected:
	IConsole* m_pConsole = nullptr;
};