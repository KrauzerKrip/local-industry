#include "scene.h"

#include <iostream>

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "lc_client/eng_graphics/entt/components.h"


Scene::Scene(std::string name, IShaderManager* pShaderManager) {
	m_mapRegistry = entt::registry();
	m_sceneRegistry = entt::registry();

	m_name = name;

	m_pShaderManager = pShaderManager;
}

Scene::~Scene() {

}

void Scene::loadScene() {
	unsigned int shaderProgram;
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
	m_sceneRegistry.emplace<ShaderGL>(entt, shaderProgram);
	
}
