#include "scene.h"
#include "scene.h"
#include "scene.h"
#include "scene.h"

#include <iostream>
#include <stdexcept>

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "lc_client/eng_graphics/entt/components.h"
#include "lc_client/eng_scene/entt/components.h"


Scene::Scene() {
	m_mapRegistry = entt::registry();
	m_sceneRegistry = entt::registry();
}

Scene::~Scene() {}

void Scene::loadScene(std::string name) {

	m_name = name;

	if (m_pShaderManager == nullptr) {
		std::cout << "NullPointerException: m_pShaderManager wasn`t initialized." << std::endl;
		throw std::runtime_error("NullPointerException: m_pShaderManager wasn`t initialized.");
	}
	
	m_mapRegistry.clear();
	m_sceneRegistry.clear();

	unsigned int shaderProgram;
	shaderProgram = glCreateProgram();
	glAttachShader(shaderProgram, m_pShaderManager->getFragmentShader("base"));
	glAttachShader(shaderProgram, m_pShaderManager->getVertexShader("base"));
	glLinkProgram(shaderProgram);

	int success;
	char infoLog[512];
	glGetProgramiv(shaderProgram, GL_COMPILE_STATUS, &success);

	if (success)
	{
		std::cout << "scene: shader program linked successfully: " << shaderProgram << std::endl;
	}
	else {
		glGetProgramInfoLog(shaderProgram, 512, 0, infoLog);
		std::cerr << "scene: shader program link failure: \n" <<
			infoLog << std::endl;
	}

	auto entt = m_sceneRegistry.create();
	m_sceneRegistry.emplace<Properties>(entt, "test_uuid", "test_id");
	m_sceneRegistry.emplace<Mesh>(entt);
	m_sceneRegistry.emplace<MaterialGl>(entt, shaderProgram);
}

void Scene::setShaderManager(IShaderManager* pShaderManager) {
	m_pShaderManager = pShaderManager;
}

entt::registry* Scene::getMapRegistry() {
	return &m_mapRegistry;
}

entt::registry* Scene::getSceneRegistry() {
	return &m_sceneRegistry;
}
