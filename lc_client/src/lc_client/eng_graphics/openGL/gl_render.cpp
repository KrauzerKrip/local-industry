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
	m_pShaderLoader = pShaderWork;
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

	m_framebufferShader = m_pShaderLoader->createShaderProgram("framebuffer", "framebuffer");

	m_pWindow->setResizeCallback([this](int width, int height) {
		if (width != 0 && height != 0) {
			delete m_pFramebuffer;
			m_pFramebuffer = new Framebuffer(width, height);
		}
	});

}

void RenderGL::render() {
	m_pFramebuffer->bind();

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);

	glStencilMask(0x00);

	float aspectRatio = (float)m_pWindow->getAspectRatio()[0] / (float)m_pWindow->getAspectRatio()[1];
	glm::mat4 projection = glm::perspective(glm::radians(m_pGraphicsSettings->getFov()), aspectRatio, 0.1f, 1000.0f);
	glm::mat4 view = m_pCamera->getViewMatrix(); // glm::mat4(1.0f);

	m_pRenderMap->render(view, projection);

	m_pOpaqueRender->render(projection, view);

	glDepthFunc(GL_LEQUAL);
	m_pSkybox->render(projection, view);
	glDepthFunc(GL_LESS);

	glDepthMask(false);
	m_pTransparentRender->render(projection, view);
	glDepthMask(true);
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

    m_pMeshRender = new MeshRenderGl(m_pUtilRegistry);
	m_pOutlineRender = new OutlineRenderGl(m_pMeshRender, m_pShaderLoader);
	m_pRenderMap = new RenderMapGl(m_pLighting, this, m_pCamera, m_pSkybox, m_pRegistry, m_pUtilRegistry);
	m_pPrimitiveRender = new PrimitiveRender(m_pShaderLoader, m_pRegistry, m_pRegistry);
	m_pOpaqueRender = new OpaqueRenderGl(
		m_pCamera, m_pMeshRender, m_pOutlineRender, m_pLighting, m_pSkybox, m_pRegistry, m_pUtilRegistry);
	m_pTransparentRender = new TransparentRenderGl(m_pCamera, m_pMeshRender, m_pOutlineRender, m_pRegistry);
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

