#pragma once

#include "lc_client/tier0/console/i_console.h"
#include "lc_client/eng_gui/paint_objects/background.h"
#include "lc_client/eng_graphics/gui/queue_render.h"
#include "lc_client/eng_gui/widgets/rectangle.h"
#include "lc_client/eng_gui/widgets/layer.h"
#include "lc_client/eng_graphics/texture.h"


struct ColorQuad {
	glm::vec4 color;
	RectangleVertices vertices;
	float zOffset;
	float blurIntensity;

	ColorQuad(glm::vec4 color)
		: color(color) {}
	ColorQuad(glm::vec4 color, RectangleVertices vertices, float zOffset, float blurIntensity)
		: color(color),
		  vertices(vertices),
		  zOffset(zOffset),
		  blurIntensity(blurIntensity)
	{};
};

struct ImageQuad {
	Texture* pTexture;
	RectangleVertices vertices;
	float zOffset;
};


class BackgroundRender {
public:
	BackgroundRender(IConsole* pConsole) : m_pConsole(pConsole){};
	virtual ~BackgroundRender() = default;

	virtual void renderColor(ColorQuad colorQuad) = 0;
	virtual void renderImage(ImageQuad colorQuad) = 0;
	virtual Texture* getTexture(std::string path) = 0;

protected:
	IConsole* m_pConsole = nullptr;
};