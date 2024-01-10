#include "gl_render.h"

#include <iostream>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "lc_client/eng_graphics/entt/components.h"
#include "lc_client/eng_graphics/texture.h"
#include "lc_client/eng_model/entt/components.h"
#include "lc_client/eng_lighting/entt/components.h"
#include "lc_client/eng_graphics/openGL/gl_shader_uniform.h"
#include "lc_client/eng_cubemaps/entt/components.h"
#include "renders/gl_mesh_render.h"

#include "lc_client/tier0/tier0.h"


RenderGL::RenderGL(IWindow* pWindow, Camera* pCamera, ShaderLoaderGl* pShaderWork, GuiPresenter* pGuiPresenter, GraphicsSettings* pGraphicsSettings) {
	m_pWindow = pWindow; // mb remove it
	m_pCamera = pCamera;
	m_pShaderWork = pShaderWork;
	m_pFramebuffer = new Framebuffer(pWindow->getSize()[0], pWindow->getSize()[1]);
	m_pGuiPresenter = pGuiPresenter;
	m_pGraphicsSettings = pGraphicsSettings;
}

RenderGL::~RenderGL() {}

void RenderGL::init() {
	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LESS);
	glEnable(GL_STENCIL_TEST);
	glStencilOp(GL_KEEP, GL_KEEP, GL_REPLACE);
	glStencilFunc(GL_NOTEQUAL, 1, 0xFF);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glEnable(GL_CULL_FACE);
	glCullFace(GL_BACK);
	glFrontFace(GL_CCW);

	glEnable(GL_MULTISAMPLE);

	createFramebufferVao();

	m_framebufferShader = m_pShaderWork->createShaderProgram("framebuffer", "framebuffer");
	m_outlineShader = m_pShaderWork->createShaderProgram("base", "primitive");

	m_pWindow->setResizeCallback([this](int width, int height) {
		delete m_pFramebuffer;
		m_pFramebuffer = new Framebuffer(width, height);
	});

}

void RenderGL::render() {
	m_pFramebuffer->bind();

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);

	glStencilMask(0x00);

	float aspectRatio = (float)m_pWindow->getAspectRatio()[0] / (float)m_pWindow->getAspectRatio()[1];
	glm::mat4 projection = glm::perspective(glm::radians(m_pGraphicsSettings->getFov()), aspectRatio, 0.1f, 1000.0f);
	glm::mat4 view = m_pCamera->getViewMatrix(); // glm::mat4(1.0f);

	// auto test = m_pSceneRegistry->view<Properties, Transform>();
	// for (auto& ent : test) {
	//	if (test.get<Properties>(ent).id == "surface") {
	//		std::cout << test.get<Transform>(ent).position.x << std::endl;
	//	}
	// }

	m_pRenderMap->render(view, projection);

	entt::view<entt::get_t<CubemapGl, Transform>, entt::exclude_t<>> cubemapEntities =
		m_pRegistry->view<CubemapGl, Transform>();

	auto pointLights = m_pRegistry->view<Transform, PointLight>();

	auto materialEntitiesGroup =
		m_pRegistry->view<Model, Transform, ShaderGl, Properties>(entt::exclude<Transparent, Outline>); // TODO

	for (entt::entity entity : materialEntitiesGroup) {
		if (m_pRegistry->get<Properties>(entity).id == "heater") {
			int i = 0;
		}

		Model& model = materialEntitiesGroup.get<Model>(entity);
		std::vector<entt::entity>& meshes = model.meshes;
		unsigned int shaderProgram = materialEntitiesGroup.get<ShaderGl>(entity).shaderProgram;
		glUseProgram(shaderProgram);
		m_pSkybox->bindTexture();
		Transform& transform = materialEntitiesGroup.get<Transform>(entity);
		unsigned int nearestCubemapId = getNearestCubemap(transform.position, cubemapEntities);
		if (nearestCubemapId != 0) {
			glActiveTexture(GL_TEXTURE0 + TextureType::CUBEMAP);
			glBindTexture(GL_TEXTURE_CUBE_MAP, nearestCubemapId);
		}

		setUniform(shaderProgram, "skybox", TextureType::SKYBOX);
		setUniform(shaderProgram, "cubemap", TextureType::CUBEMAP);
		eng::setMaterialSg(shaderProgram);
		m_pLighting->setLighting(shaderProgram);
		setUniform(shaderProgram, "viewPos", m_pCamera->getPosition());
		glm::mat4 modelMatrix = glm::mat4(1.0f);
		eng::transform(modelMatrix, transform);
		eng::setMatrices(shaderProgram, modelMatrix, view, projection);

		for (entt::entity& meshEntity : meshes) {
			eng::renderMesh(meshEntity, m_pUtilRegistry);
		}
	}

	auto materialOutlineEntitiesGroup =
	m_pRegistry->view<Model, Transform, ShaderGl, Properties, Outline>(entt::exclude<Water>); // TODO

	for (entt::entity entity : materialOutlineEntitiesGroup) {
		Model& model = materialOutlineEntitiesGroup.get<Model>(entity);
		std::vector<entt::entity>& meshes = model.meshes;
		unsigned int shaderProgram = materialOutlineEntitiesGroup.get<ShaderGl>(entity).shaderProgram;
		glUseProgram(shaderProgram);
		m_pSkybox->bindTexture();
		Transform& transform = materialOutlineEntitiesGroup.get<Transform>(entity);
		unsigned int nearestCubemapId = getNearestCubemap(transform.position, cubemapEntities);
		if (nearestCubemapId != 0) {
			glActiveTexture(GL_TEXTURE0 + TextureType::CUBEMAP);
			glBindTexture(GL_TEXTURE_CUBE_MAP, nearestCubemapId);
		}

		setUniform(shaderProgram, "skybox", TextureType::SKYBOX);
		setUniform(shaderProgram, "cubemap", TextureType::CUBEMAP);
		eng::setMaterialSg(shaderProgram);
		m_pLighting->setLighting(shaderProgram);
		setUniform(shaderProgram, "viewPos", m_pCamera->getPosition());
		glm::mat4 modelMatrix = glm::mat4(1.0f);
		eng::transform(modelMatrix, transform);
		eng::setMatrices(shaderProgram, modelMatrix, view, projection);

		Outline& outline = materialOutlineEntitiesGroup.get<Outline>(entity);
		glm::mat4 outlineModelMatrix = glm::mat4(1.0f);
		Transform transformOutline(transform);
		transformOutline.scale = transform.scale + outline.width;
		eng::transform(outlineModelMatrix, transformOutline);

		glStencilFunc(GL_ALWAYS, 1, 0xFF);
		glStencilMask(0xFF);
		for (entt::entity& meshEntity : meshes) {
			eng::renderMesh(meshEntity, m_pUtilRegistry);
		}

		glStencilFunc(GL_NOTEQUAL, 1, 0xFF);
		glStencilMask(0x00);
		glUseProgram(m_outlineShader);
		eng::setMatrices(m_outlineShader, outlineModelMatrix, view, projection);
		setUniform(m_outlineShader, "color", outline.color);
		for (entt::entity& meshEntity : meshes) {
			eng::renderMesh(meshEntity, m_pUtilRegistry);
		}
		glStencilMask(0xFF);
		glStencilFunc(GL_ALWAYS, 0, 0xFF);
		glEnable(GL_DEPTH_TEST);
	}

	glDepthFunc(GL_LEQUAL);
	m_pSkybox->render(projection, view);
	glDepthFunc(GL_LESS);

	m_pTransparentRender->render(projection, view);
	m_pPrimitiveRender->render(projection, view);
	m_pGuiPresenter->render();

	glBindFramebuffer(GL_FRAMEBUFFER, 0); // back to default
	m_pFramebuffer->bindTexture();
	glDisable(GL_DEPTH_TEST);
	glClear(GL_COLOR_BUFFER_BIT);

	glUseProgram(m_framebufferShader);
	setUniform(m_framebufferShader, "screenTexture", TextureType::FRAMEBUFFER);

	glBindVertexArray(m_framebufferVao);
	glDrawArrays(GL_TRIANGLES, 0, 6);

	glEnable(GL_DEPTH_TEST);
}

void RenderGL::clear() {}

void RenderGL::cleanUp() {}

void RenderGL::setDependecies(World* pWorld) {
	m_pRegistry = &pWorld->getRegistry();
	m_pUtilRegistry = &pWorld->getUtilRegistry();

	m_pSkybox = pWorld->getSkybox();
	
	m_pLighting = new LightingGl(m_pRegistry, m_pCamera, m_pSkybox);

	m_pRenderMap = new RenderMapGl(m_pLighting, this, m_pCamera, m_pSkybox, m_pRegistry, m_pUtilRegistry);
	m_pPrimitiveRender = new PrimitiveRender(m_pShaderWork, m_pRegistry, m_pRegistry);
	m_pTransparentRender = new TransparentRenderGl(m_pCamera, m_pRegistry, m_pUtilRegistry);
}

void RenderGL::createFramebufferVao() {
	float quadVertices[] = {// positions // texCoords
		-1.0f, 1.0f, 0.0f, 1.0f, -1.0f, -1.0f, 0.0f, 0.0f, 1.0f, -1.0f, 1.0f, 0.0f, -1.0f, 1.0f, 0.0f, 1.0f, 1.0f,
		-1.0f, 1.0f, 0.0f, 1.0f, 1.0f, 1.0f, 1.0f};

	unsigned int quadVBO;
	glGenVertexArrays(1, &m_framebufferVao);
	glGenBuffers(1, &quadVBO);
	glBindVertexArray(m_framebufferVao);
	glBindBuffer(GL_ARRAY_BUFFER, quadVBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(quadVertices), &quadVertices, GL_STATIC_DRAW);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(float), (void*)(2 * sizeof(float)));
}

unsigned int RenderGL::getNearestCubemap(glm::vec3& entityPosition, CubemapView& cubemapEntities) {
	float minDistance = 0;
	unsigned int nearestCubemapId = 0;

	bool isFirstTime = true;

	for (entt::entity cubemap : cubemapEntities) {
		Transform& cubemapTransform = cubemapEntities.get<Transform>(cubemap);
		glm::vec3& cubemapPosition = cubemapTransform.position;
		unsigned int cubemapId = cubemapEntities.get<CubemapGl>(cubemap).textureId;

		if (isFirstTime) {
			float distance = glm::distance(cubemapPosition, entityPosition);
			minDistance = distance;
			nearestCubemapId = cubemapId;
		}
		else {
			float distance = glm::distance(cubemapPosition, entityPosition);
			if (distance < minDistance) {
				minDistance = distance;
				nearestCubemapId = cubemapId;
			}
		}

		isFirstTime = false;
	}

	return nearestCubemapId;
}
