#pragma once

#include "lc_client/tier0/console/i_console.h"
#include "lc_client/eng_gui/paint_objects/background.h"
#include "lc_client/eng_gui/paint_objects/image_background.h"
#include "lc_client/eng_graphics/gui/queue_render.h"

struct ColorQuad {
	Background background;
	glm::vec2 absolutePosition;
	glm::vec2 size;
	unsigned int layer;
};

struct ImageQuad {
	ImageBackground background;
	glm::vec2 absolutePosition;
	glm::vec2 size;
	unsigned int layer;
};


class BackgroundRender {
public:
	BackgroundRender(IConsole* pConsole) : m_pConsole(pConsole){};
	virtual ~BackgroundRender(){};

	virtual void renderColor(ColorQuad colorQuad) = 0;
	virtual void renderImage(ImageQuad colorQuad) = 0;

protected:
	IConsole* m_pConsole = nullptr;
};