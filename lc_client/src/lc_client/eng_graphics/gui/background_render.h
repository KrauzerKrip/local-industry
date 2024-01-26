#pragma once

#include "lc_client/tier0/console/i_console.h"
#include "lc_client/eng_gui/paint_objects/background.h"
#include "lc_client/eng_gui/paint_objects/image_background.h"
#include "lc_client/eng_graphics/gui/queue_render.h"
#include "lc_client/eng_gui/widgets/rectangle.h"
#include "lc_client/eng_gui/widgets/layer.h"


struct ColorQuad {
	glm::vec4 color;
	RectangleVertices vertices;
	float zOffset;

	ColorQuad(glm::vec4 color)
		: color(color) {}
	ColorQuad(glm::vec4 color, RectangleVertices vertices, float zOffset)
		: color(color),
		  vertices(vertices),
		  zOffset(zOffset){};
};

struct ImageQuad {
	std::shared_ptr<eng::Image> image;
	RectangleVertices vertices;
	Layer layer;
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