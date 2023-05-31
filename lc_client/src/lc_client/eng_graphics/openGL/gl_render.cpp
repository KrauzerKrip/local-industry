#include "gl_render.h"
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


RenderGL::RenderGL(IWindow* pWindow, Camera* pCamera, ShaderWorkGl* pShaderWork) { 
	m_pWindow = pWindow; // mb remove it
	m_pCamera = pCamera;
	m_pShaderWork = pShaderWork;
	m_pFramebuffer = new Framebuffer(pWindow->getSize()[0], pWindow->getSize()[1]);
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
	glm::mat4 projection = glm::perspective(glm::radians(m_pWindow->getFov()), aspectRatio, 0.1f, 100.0f);
	glm::mat4 view = m_pCamera->getViewMatrix(); // glm::mat4(1.0f);


	// auto test = m_pSceneRegistry->view<Properties, Transform>();
	// for (auto& ent : test) {
	//	if (test.get<Properties>(ent).id == "surface") {
	//		std::cout << test.get<Transform>(ent).position.x << std::endl;
	//	}
	// }


	auto pointLights = m_pSceneRegistry->view<Transform, PointLight>();

	auto materialEntitiesGroup = m_pSceneRegistry->group<Model, Transform, ShaderGl>(); // TODO

	for (entt::entity entity : materialEntitiesGroup) {

		Model& model = materialEntitiesGroup.get<Model>(entity);
		Transform& transform = materialEntitiesGroup.get<Transform>(entity);

		std::vector<entt::entity>& meshes = model.meshes;

		unsigned int shaderProgram = materialEntitiesGroup.get<ShaderGl>(entity).shaderProgram;

		glUseProgram(shaderProgram);


		setUniform(shaderProgram, "material.diffuse", TextureType::DIFFUSE);
		setUniform(shaderProgram, "material.normal", TextureType::NORMAL);
		setUniform(shaderProgram, "material.specular", TextureType::SPECULAR);
		setUniform(shaderProgram, "material.shininess", 32.0f);

		setUniform(shaderProgram, "ambientLight.color", m_pScene->getSkybox().getLightColor());
		setUniform(shaderProgram, "ambientLight.strength", m_pScene->getSkybox().getLightStrength());

		setUniform(shaderProgram, "spotLight.position", m_pCamera->getPosition());
		setUniform(shaderProgram, "spotLight.direction", m_pCamera->getCameraFront());
		setUniform(shaderProgram, "spotLight.cutOff", (float)glm::cos(glm::radians(12.5)));
		setUniform(shaderProgram, "spotLight.outerCutOff", (float)glm::cos(glm::radians(17.5)));
		setUniform(shaderProgram, "spotLight.diffuse", glm::vec3(1.0f));
		setUniform(shaderProgram, "spotLight.specular", glm::vec3(0.5f));
		setUniform(shaderProgram, "spotLight.constant", 1.0f);
		setUniform(shaderProgram, "spotLight.linear", 0.09f);
		setUniform(shaderProgram, "spotLight.quadratic", 0.032f);


		int i = 0;

		for (entt::entity entity : pointLights) { 
			glm::vec3 color = pointLights.get<PointLight>(entity).color;
			glm::vec3 pos = pointLights.get<Transform>(entity).position;

			std::string iStr = std::to_string(i);

			setUniform(shaderProgram, "pointLights[" + iStr + "].position", pos);
			setUniform(shaderProgram, "pointLights[" + iStr + "].diffuse", color * 0.5f);
			setUniform(shaderProgram, "pointLights[" + iStr + "].specular", color * 0.25f);
			setUniform(shaderProgram, "pointLights[" + iStr + "].constant", 1.0f);
			setUniform(shaderProgram, "pointLights[" + iStr + "].linear", 0.09f);
			setUniform(shaderProgram, "pointLights[" + iStr + "].quadratic", 0.032f);

			i++;
		}

		setUniform(shaderProgram, "directionalLight.direction", glm::vec3(-0.2f, -1.0f, -0.3f));
		setUniform(shaderProgram, "directionalLight.diffuse", glm::vec3(1.0f, 1.0f, 0.8f));
		setUniform(shaderProgram, "directionalLight.specular", glm::vec3(1.0f, 1.0f, 0.8f));

		setUniform(shaderProgram, "pointLightsCount", i);

		setUniform(shaderProgram, "viewPos", m_pCamera->getPosition());




		glm::mat4 modelMatrix = glm::mat4(1.0f);
		RenderGL::transform(modelMatrix, transform);

		glm::mat4 normalMatrix = modelMatrix;
		glm::inverse(normalMatrix);
		glm::transpose(normalMatrix);


		// glm::mat4 modelView = view * model;

		unsigned int modelLoc = glGetUniformLocation(shaderProgram, "model");
		unsigned int viewLoc = glGetUniformLocation(shaderProgram, "view");
		unsigned int projLoc = glGetUniformLocation(shaderProgram, "projection");
		unsigned int normalMatrixLoc = glGetUniformLocation(shaderProgram, "normalMatrix");

		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(modelMatrix));
		glUniformMatrix4fv(viewLoc, 1, GL_FALSE, glm::value_ptr(view));
		glUniformMatrix4fv(projLoc, 1, GL_FALSE, glm::value_ptr(projection));
		glUniformMatrix4fv(normalMatrixLoc, 1, GL_FALSE, glm::value_ptr(normalMatrix));

		for (entt::entity& meshEntity : meshes) {
			Mesh& mesh = m_pUtilRegistry->get<Mesh>(meshEntity);
			int vao = m_pUtilRegistry->get<VaoGl>(meshEntity).vaoId;
			MaterialSG& materialSG = m_pUtilRegistry->get<MaterialSG>(meshEntity);

			Texture* aoTexture = materialSG.aoTexture;
			Texture* diffuseTexture = materialSG.diffuseTexture;
			Texture* normalMap = materialSG.normalMap;
			Texture* specularMap = materialSG.specularTexture;

			aoTexture->bind();
			diffuseTexture->bind();
			normalMap->bind();
			specularMap->bind();

			glBindVertexArray(vao);
			glDrawElements(GL_TRIANGLES, mesh.indices.size(), GL_UNSIGNED_INT, 0);
		}
	}

	glBindFramebuffer(GL_FRAMEBUFFER, 0); // back to default
	m_pFramebuffer->bindTexture();
	glDisable(GL_DEPTH_TEST);
	glClear(GL_COLOR_BUFFER_BIT);

	glUseProgram(m_framebufferShader);

	glBindVertexArray(m_framebufferVao);
	glDrawArrays(GL_TRIANGLES, 0, 6);

}

void RenderGL::clear() {}

void RenderGL::cleanUp() {}

void RenderGL::setDependecies(Scene* pScene) {
	m_pScene = pScene;

	m_pMapRegistry = &pScene->getMapRegistry();
	m_pSceneRegistry = &pScene->getSceneRegistry();
	m_pUtilRegistry = &pScene->getUtilRegistry();
}

void RenderGL::transform(glm::mat4& model, Transform& transform) {
	model = glm::translate(model, transform.position);
	model = glm::rotate(model, glm::radians(-55.0f), transform.rotation);
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
