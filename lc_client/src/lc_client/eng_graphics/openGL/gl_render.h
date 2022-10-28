#pragma once

#include <entt/entt.hpp>

#include "lc_client/eng_graphics/i_render.h"
#include "lc_client/eng_graphics/i_window.h"

class RenderGL : public IRender {
public:
	RenderGL(IWindow* pWindow);
	virtual ~RenderGL();

	void init(); 
	void render();
	void clear();
	void cleanUp();
	void setRegistries(entt::registry* sceneRegistry, entt::registry* mapRegistry);

private:
	IWindow* m_pWindow; //mb remove it 
	
	entt::registry* m_pSceneRegistry = nullptr;
	entt::registry* m_pMapRegistry = nullptr;
};