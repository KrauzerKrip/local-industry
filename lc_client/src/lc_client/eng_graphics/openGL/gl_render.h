#pragma once

#include "lc_client/eng_graphics/i_render.h"

class RenderGL : public IRender {
public:
	RenderGL();
	virtual ~RenderGL();

	void init();
	void render();
	void clear();
	void cleanUp();
};