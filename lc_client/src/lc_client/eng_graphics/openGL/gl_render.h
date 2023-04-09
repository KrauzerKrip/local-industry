#pragma once

#include <entt/entt.hpp>
#include <glm/glm.hpp>

#include "lc_client/eng_graphics/i_render.h"
#include "lc_client/eng_graphics/i_window.h"
#include "lc_client/eng_scene/entt/components.h"
#include "lc_client/eng_graphics/camera/camera.h"

class RenderGL : public IRender {
public:
	RenderGL(IWindow* pWindow, Camera* pCamera);
	~RenderGL();

	void init(); 
	void render();
	void clear();
	void cleanUp();
	void setRegistries(entt::registry& pSceneRegistry, entt::registry& pMapRegistry, entt::registry& pUtilRegistry);

private:
	void transform(glm::mat4& transformation, Transform& transform);

	IWindow* m_pWindow; //mb remove it
	Camera* m_pCamera;
	
	entt::registry* m_pSceneRegistry = nullptr;
	entt::registry* m_pMapRegistry = nullptr;
	entt::registry* m_pUtilRegistry = nullptr;
};