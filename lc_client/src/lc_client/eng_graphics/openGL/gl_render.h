#pragma once

#include <entt/entt.hpp>
#include <glm/glm.hpp>

#include "lc_client/eng_graphics/i_render.h"
#include "lc_client/eng_graphics/i_window.h"
#include "lc_client/eng_scene/entt/components.h"
#include "lc_client/eng_graphics/camera/camera.h"
#include "lc_client/eng_world/world.h"
#include "lc_client/eng_scene/skybox.h"
#include "gl_shader_loader.h"
#include "lc_client/eng_graphics/openGL/gl_framebuffer.h"
#include "lc_client/eng_cubemaps/entt/components.h"
#include "lc_client/eng_lighting/entt/components.h"
#include "renders/gl_render_map.h"
#include "lc_client/eng_graphics/openGL/renders/gl_lighting.h"
#include "lc_client/eng_graphics/gui/openGL/gl_text_render.h"
#include "lc_client/eng_gui/view/gui_presenter.h"
#include "lc_client/eng_graphics/gui/text_render.h"
#include "lc_client/eng_graphics/graphics_settings.h"
#include "renders/gl_primitive_render.h"


typedef decltype(entt::registry().view<CubemapGl, Transform>()) CubemapView;
typedef decltype(entt::registry().view<Transform, PointLight>()) PointLightView;
typedef decltype(entt::registry().view<Transform, SpotLight>()) SpotLightView;

class ShaderLoaderGl;

class RenderMapGl;

class RenderGL : public IRender {

friend class RenderMapGl;

public:
RenderGL(IWindow* pWindow, Camera* pCamera, ShaderLoaderGl* pShaderWork, GuiPresenter* pGuiPresenter,
		 GraphicsSettings* pGraphicsSettings);
	~RenderGL();

	void init(); 
	void render();
	void clear();
	void cleanUp();
	void setDependecies(World* pWorld);

private:
	void transform(glm::mat4& transformation, Transform& transform);
	void createFramebufferVao();
	void renderMesh(entt::entity meshEntity, entt::registry* pUtilRegistry);

	void setMaterialSg(unsigned int shaderProgram);
	unsigned int getNearestCubemap(glm::vec3& entityPosition, CubemapView& cubemapEntities);
	void setMatrices(unsigned int shaderProgram, glm::mat4& model, glm::mat4& view, glm::mat4 projection);

	IWindow* m_pWindow; //mb remove it
	Camera* m_pCamera;
	ShaderLoaderGl* m_pShaderWork;
	RenderMapGl* m_pRenderMap;	
	Skybox* m_pSkybox = nullptr;
	LightingGl* m_pLighting = nullptr;
	GuiPresenter* m_pGuiPresenter = nullptr;
	TextRender* m_pRenderText = nullptr;
	PrimitiveRender* m_pPrimitiveRender = nullptr;
	GraphicsSettings* m_pGraphicsSettings = nullptr;


	entt::registry* m_pRegistry = nullptr;
	entt::registry* m_pUtilRegistry = nullptr;

	Framebuffer* m_pFramebuffer = nullptr;
	unsigned int m_framebufferTexture = 0;
	unsigned int m_framebufferVao = 0;
	unsigned int m_framebufferShader = 0;

	unsigned int m_outlineShader = 0;
};