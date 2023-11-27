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

#include "lc_client/tier0/tier0.h"


RenderGL::RenderGL(IWindow* pWindow, Camera* pCamera, ShaderWorkGl* pShaderWork, GuiPresenter* pGuiPresenter) {
	m_pWindow = pWindow; // mb remove it
	m_pCamera = pCamera;
	m_pShaderWork = pShaderWork;
	m_pFramebuffer = new Framebuffer(pWindow->getSize()[0], pWindow->getSize()[1]);
	m_pGuiPresenter = pGuiPresenter;
}

RenderGL::~RenderGL() {}

void RenderGL::init() {
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glEnable(GL_CULL_FACE);
	glCullFace(GL_BACK);
	glFrontFace(GL_CCW);

	glEnable(GL_MULTISAMPLE);

	createFramebufferVao();

	m_framebufferShader = m_pShaderWork->createShaderProgram("framebuffer", "framebuffer");

	m_pWindow->setResizeCallback([this](int width, int height) {
		delete m_pFramebuffer;
		m_pFramebuffer = new Framebuffer(width, height);
	});
}

void RenderGL::render() {
	m_pFramebuffer->bind();

	glEnable(GL_DEPTH_TEST);

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	float aspectRatio = (float)m_pWindow->getAspectRatio()[0] / (float)m_pWindow->getAspectRatio()[1];
	glm::mat4 projection = glm::perspective(glm::radians(m_pWindow->getFov()), aspectRatio, 0.1f, 1000.0f);
	glm::mat4 view = m_pCamera->getViewMatrix(); // glm::mat4(1.0f);

	// auto test = m_pSceneRegistry->view<Properties, Transform>();
	// for (auto& ent : test) {
	//	if (test.get<Properties>(ent).id == "surface") {
	//		std::cout << test.get<Transform>(ent).position.x << std::endl;
	//	}
	// }

	m_pRenderMap->render(view, projection);


	entt::view<entt::get_t<CubemapGl, Transform>, entt::exclude_t<>> cubemapEntities =
		m_pMapRegistry->view<CubemapGl, Transform>();

	auto pointLights = m_pSceneRegistry->view<Transform, PointLight>();

	auto materialEntitiesGroup =
		m_pSceneRegistry->group<Model, Transform, ShaderGl, Properties>(entt::exclude<Water>); // TODO

	for (entt::entity entity : materialEntitiesGroup) {
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
		setMaterialSg(shaderProgram);
		m_pLighting->setLighting(shaderProgram);
		setUniform(shaderProgram, "viewPos", m_pCamera->getPosition());
		glm::mat4 modelMatrix = glm::mat4(1.0f);
		RenderGL::transform(modelMatrix, transform);
		setMatrices(shaderProgram, modelMatrix, view, projection);

		for (entt::entity& meshEntity : meshes) {
			renderMesh(meshEntity, m_pUtilRegistry);
		}
	}


	glDepthFunc(GL_LEQUAL);
	m_pSkybox->render(projection, view);
	glDepthFunc(GL_LESS);

	auto waterEntitiesGroup = m_pSceneRegistry->view<Water, Model, Transform, ShaderGl>();

	for (entt::entity entity : waterEntitiesGroup) {
		Model& model = waterEntitiesGroup.get<Model>(entity);
		std::vector<entt::entity>& meshes = model.meshes;
		unsigned int shaderProgram = waterEntitiesGroup.get<ShaderGl>(entity).shaderProgram;
		glUseProgram(shaderProgram);
		m_pSkybox->bindTexture();
		Transform& transform = waterEntitiesGroup.get<Transform>(entity);
		unsigned int nearestCubemapId = getNearestCubemap(transform.position, cubemapEntities);
		if (nearestCubemapId != 0) {
			glActiveTexture(GL_TEXTURE0 + TextureType::CUBEMAP);
			glBindTexture(GL_TEXTURE_CUBE_MAP, nearestCubemapId);
		}

		m_pFramebuffer->bindTexture();
		setUniform(shaderProgram, "framebuffer", TextureType::FRAMEBUFFER);

		setUniform(shaderProgram, "skybox", TextureType::SKYBOX);
		setUniform(shaderProgram, "cubemap", TextureType::CUBEMAP);
		setMaterialSg(shaderProgram);
		m_pLighting->setLighting(shaderProgram);
		setUniform(shaderProgram, "viewPos", m_pCamera->getPosition());
		glm::mat4 modelMatrix = glm::mat4(1.0f);
		RenderGL::transform(modelMatrix, transform);
		setMatrices(shaderProgram, modelMatrix, view, projection);

		for (entt::entity& meshEntity : meshes) {
			renderMesh(meshEntity, m_pUtilRegistry);
		}
	}

	auto textView = m_pSceneRegistry->view<Properties, ShaderGl>();

	unsigned int textShaderProgram;

	for (auto& ent : textView) {
		if (m_pSceneRegistry->get<Properties>(ent).id == "text_shader") {
			textShaderProgram = m_pSceneRegistry->get<ShaderGl>(ent).shaderProgram;
		}
	}
	
	m_pGuiPresenter->render();

	glBindFramebuffer(GL_FRAMEBUFFER, 0); // back to default
	m_pFramebuffer->bindTexture();
	glDisable(GL_DEPTH_TEST);
	glClear(GL_COLOR_BUFFER_BIT);

	glUseProgram(m_framebufferShader);
	setUniform(m_framebufferShader, "screenTexture", TextureType::FRAMEBUFFER);

	glBindVertexArray(m_framebufferVao);
	glDrawArrays(GL_TRIANGLES, 0, 6);
}

void RenderGL::clear() {}

void RenderGL::cleanUp() {}

void RenderGL::setDependecies(Map* pMap, Scene* pScene, Skybox* pSkybox) {
	m_pScene = pScene;

	m_pMapRegistry = &pScene->getMapRegistry();
	m_pSceneRegistry = &pScene->getSceneRegistry();
	m_pUtilRegistry = &pScene->getUtilRegistry();

	m_pSkybox = pSkybox;
	
	m_pLighting = new LightingGl(m_pMapRegistry, m_pSceneRegistry, m_pCamera, m_pSkybox);

	m_pRenderMap = new RenderMapGl(m_pLighting, this, m_pCamera, m_pSkybox, &pMap->getRegistry(), &pMap->getUtilRegistry());
}

void RenderGL::transform(glm::mat4& model, Transform& transform) {
	model = glm::translate(model, transform.position);
	model *= glm::mat4_cast(transform.rotation);
	model = glm::scale(model, transform.scale);
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

void RenderGL::renderMesh(entt::entity meshEntity, entt::registry* pUtilRegistry) {
	Mesh& mesh = pUtilRegistry->get<Mesh>(meshEntity);
	int vao = pUtilRegistry->get<VaoGl>(meshEntity).vaoId;
	MaterialSG& materialSG = pUtilRegistry->get<MaterialSG>(meshEntity);
	Texture* aoTexture = materialSG.aoTexture; 
	Texture* diffuseTexture = materialSG.diffuseTexture;
	Texture* normalMap = materialSG.normalMap;
	Texture* specularMap = materialSG.specularTexture;
	aoTexture->bind();
	diffuseTexture->bind();
	normalMap->bind();
	specularMap->bind();
	glBindVertexArray(vao);
	glDrawElements(GL_TRIANGLES, (GLsizei)mesh.indices.size(), GL_UNSIGNED_INT, 0);
}

void RenderGL::setMaterialSg(unsigned int shaderProgram) {
	setUniform(shaderProgram, "material.diffuse", TextureType::DIFFUSE);
	setUniform(shaderProgram, "material.normal", TextureType::NORMAL);
	setUniform(shaderProgram, "material.specular", TextureType::SPECULAR);
	setUniform(shaderProgram, "material.shininess", 32.0f);
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

void RenderGL::setMatrices(unsigned int shaderProgram, glm::mat4& model, glm::mat4& view, glm::mat4 projection) {
	glm::mat4 normal = model;
	glm::inverse(normal);
	glm::transpose(normal);

	// glm::mat4 modelView = view * model;

	unsigned int modelLoc = glGetUniformLocation(shaderProgram, "model");
	unsigned int viewLoc = glGetUniformLocation(shaderProgram, "view");
	unsigned int projLoc = glGetUniformLocation(shaderProgram, "projection");
	unsigned int normalMatrixLoc = glGetUniformLocation(shaderProgram, "normalMatrix");

	glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
	glUniformMatrix4fv(viewLoc, 1, GL_FALSE, glm::value_ptr(view));
	glUniformMatrix4fv(projLoc, 1, GL_FALSE, glm::value_ptr(projection));
	glUniformMatrix4fv(normalMatrixLoc, 1, GL_FALSE, glm::value_ptr(normal));
}
