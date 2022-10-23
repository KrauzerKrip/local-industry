#pragma once

#include <entt/entt.hpp>

#include "lc_client/eng_graphics/i_render.h"
#include "lc_client/eng_graphics/i_window.h"

class RenderGL : public IRender {
public:
	RenderGL(IWindow* pWindow);
	virtual ~RenderGL();

	void init();
	void render(std::vector<entt::entity>* pGraphicsEntities);
	void clear();
	void cleanUp();

private:
	IWindow* m_pWindow; //mb remove it
};