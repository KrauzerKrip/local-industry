#pragma once

#include <entt/entt.hpp>
#include <glm/glm.hpp>

#include "lc_client/eng_graphics/i_render.h"
#include "lc_client/eng_graphics/i_window.h"
#include "lc_client/eng_scene/entt/components.h"

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
	void transform(glm::mat4& transformation, Transform& transform);

	IWindow* m_pWindow; //mb remove it 
	
	entt::registry* m_pSceneRegistry = nullptr;
	entt::registry* m_pMapRegistry = nullptr;
};