#pragma once

#include "lc_client/tier0/console/i_console.h"
#include "lc_client/eng_gui/paint_objects/background.h"
#include "lc_client/eng_gui/paint_objects/image_background.h"

class RenderBackground {
public:
	RenderBackground(IConsole* pConsole) : m_pConsole(pConsole){};
	virtual ~RenderBackground(){};

	virtual void addToQueue(Background& background, std::array<glm::vec2, 4> vertices) = 0;
	virtual void addToQueue(ImageBackground& background, std::array<glm::vec2, 4> vertices) = 0;
	virtual void render() = 0;

protected:
	IConsole* m_pConsole = nullptr;
};