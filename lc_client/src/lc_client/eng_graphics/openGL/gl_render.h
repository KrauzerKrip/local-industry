#pragma once

#include <entt/entt.hpp>
#include <glm/glm.hpp>

#include "lc_client/eng_graphics/i_render.h"
#include "lc_client/eng_graphics/i_window.h"
#include "lc_client/eng_scene/entt/components.h"
#include "lc_client/eng_graphics/camera/camera.h"
#include "lc_client/eng_scene/scene.h"
#include "lc_client/eng_scene/skybox.h"
#include "gl_shader_work.h"
#include "lc_client/eng_graphics/openGL/gl_framebuffer.h"


class ShaderWorkGl;

class RenderGL : public IRender {
public:
	RenderGL(IWindow* pWindow, Camera* pCamera, ShaderWorkGl* pShaderWork);
	~RenderGL();

	void init(); 
	void render();
	void clear();
	void cleanUp();
	void setDependecies(Scene* pScene);

private:
	void transform(glm::mat4& transformation, Transform& transform);

	IWindow* m_pWindow; //mb remove it
	Camera* m_pCamera;
	ShaderWorkGl* m_pShaderWork;
	
	Scene* m_pScene = nullptr;

	entt::registry* m_pSceneRegistry = nullptr;
	entt::registry* m_pMapRegistry = nullptr;
	entt::registry* m_pUtilRegistry = nullptr;

	Framebuffer* m_pFramebuffer = nullptr;
	unsigned int m_framebufferTexture = 0;
	unsigned int m_framebufferVao = 0;
	unsigned int m_framebufferShader = 0;
};