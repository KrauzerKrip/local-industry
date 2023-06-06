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
#include "lc_client/eng_cubemaps/entt/components.h"
#include "lc_client/eng_lighting/entt/components.h"


typedef decltype(entt::registry().view<CubemapGl, Transform>()) CubemapView;
typedef decltype(entt::registry().view<Transform, PointLight>()) PointLightView;
typedef decltype(entt::registry().view<Transform, SpotLight>()) SpotLightView;

class ShaderWorkGl;

class RenderGL : public IRender {
public:
	RenderGL(IWindow* pWindow, Camera* pCamera, ShaderWorkGl* pShaderWork);
	~RenderGL();

	void init(); 
	void render();
	void clear();
	void cleanUp();
	void setDependecies(Scene* pScene, Skybox* pSkybox);

private:
	void transform(glm::mat4& transformation, Transform& transform);
	void createFramebufferVao();

	void setLighting(unsigned int shaderProgram, PointLightView& pointLights);

	void setPointLight(unsigned int shaderProgram, int number, PointLight& pointLight, Transform& transform);
	void setMaterialSg(unsigned int shaderProgram);
	unsigned int getNearestCubemap(glm::vec3& entityPosition, CubemapView& cubemapEntities);
	void setMatrices(unsigned int shaderProgram, glm::mat4& model, glm::mat4& view, glm::mat4 projection);

	IWindow* m_pWindow; //mb remove it
	Camera* m_pCamera;
	ShaderWorkGl* m_pShaderWork;
	
	Scene* m_pScene = nullptr;
	Skybox* m_pSkybox = nullptr;

	entt::registry* m_pSceneRegistry = nullptr;
	entt::registry* m_pMapRegistry = nullptr;
	entt::registry* m_pUtilRegistry = nullptr;

	Framebuffer* m_pFramebuffer = nullptr;
	unsigned int m_framebufferTexture = 0;
	unsigned int m_framebufferVao = 0;
	unsigned int m_framebufferShader = 0;
};