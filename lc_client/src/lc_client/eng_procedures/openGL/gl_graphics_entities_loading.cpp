#include "gl_graphics_entities_loading.h"

#include <iostream>
#include <glad/glad.h>

#include "lc_client/eng_scene/entt/components.h"
#include "lc_client/eng_graphics/entt/components.h"
#include "lc_client/eng_graphics/texture.h"


GraphicsEntitiesLoadingGl::GraphicsEntitiesLoadingGl(IShaderManager* pShaderManager, TextureManager* pTextureManager) {
	m_pShaderManager = pShaderManager;
	m_pTextureManager = pTextureManager;
};

GraphicsEntitiesLoadingGl::~GraphicsEntitiesLoadingGl() {};

void GraphicsEntitiesLoadingGl::loadMapEntities(entt::registry* registry) {
	
}

void GraphicsEntitiesLoadingGl::loadSceneEntities(entt::registry* registry) {
	auto entitiesGroup = registry->group<Properties, ModelData>();


	for (entt::entity entity : entitiesGroup) {

		Properties& properties = entitiesGroup.get<Properties>(entity);
		ModelData& modelData = entitiesGroup.get<ModelData>(entity);
 		std::string id = modelData.id;
		std::string vertexShaderName = modelData.vertexShader;
		std::string fragmentShaderName = modelData.fragmentShader;

		unsigned int shaderProgram = createShaderProgram(vertexShaderName, fragmentShaderName);
		
		Texture* colorTexture = m_pTextureManager->getTexture(modelData.colorTexture);
		Texture* aoTexture = m_pTextureManager->getTexture(modelData.aoTexture);
		Texture* metallicTexture = m_pTextureManager->getTexture(modelData.metallicTexture);
		Texture* normalMap = m_pTextureManager->getTexture(modelData.normalMap);

		unsigned int vaoId = createVao();
      
		VaoGl vaoGl = registry->emplace<VaoGl>(entity, vaoId);
		MaterialGl materialGl = registry->emplace<MaterialGl>(entity);

		aoTexture->load();
		colorTexture->load();
		metallicTexture->load();
		normalMap->load();
		
		materialGl.aoTexture = aoTexture;
		materialGl.colorTexture = colorTexture;
		materialGl.metallicTexture = metallicTexture;
		materialGl.normalMap = normalMap;

		registry->erase<ModelData>(entity);

	}
}

unsigned int GraphicsEntitiesLoadingGl::createShaderProgram(std::string vertexShaderName, std::string fragmentShaderName) {
	unsigned int shaderProgram;
	shaderProgram = glCreateProgram();

	try {
		glAttachShader(shaderProgram, m_pShaderManager->getFragmentShader(vertexShaderName));
	}
	catch (const std::out_of_range &exception) {
		std::cerr << exception.what() << std::endl;
	}
	try {
		glAttachShader(shaderProgram, m_pShaderManager->getVertexShader(fragmentShaderName));
	}
	catch (const std::out_of_range &exception) {
		std::cerr << exception.what() << std::endl;
	}

	glLinkProgram(shaderProgram);

	int success;
	char infoLog[512];
	glGetProgramiv(shaderProgram, GL_COMPILE_STATUS, &success);

	if (success) {
		std::cout << "gl_graphics_entities_loading: shader program linked successfully: " << shaderProgram << std::endl;
	} 
	else {
		glGetProgramInfoLog(shaderProgram, 512, 0, infoLog);
		std::cerr << "gl_graphics_entities_loading: shader program link failure: \n" <<
			infoLog << std::endl;
	}
	
	return shaderProgram;
}

unsigned int GraphicsEntitiesLoadingGl::createVao() {
	unsigned int vbo;
	glGenBuffers(1, &vbo);

	unsigned int vao;
	glGenVertexArrays(1, &vao);

	unsigned int ebo;
	glGenBuffers(1, &ebo);

	//
	float vertices[] {
		0.5f, 0.5f, 0.0f, 1.0f, 0.0f, 0.0f, // top right
			0.5f, -0.5f, 0.0f, 0.0f, 1.0f, 0.0f, // bottom right
			-0.5f, -0.5f, 0.0f, 0.0f, 0.0f, 1.0f,// bottom left
			-0.5f, 0.5f, 0.0f, 1.0f, 1.0f, 1.0f// top left
	};

	unsigned int indices_[] { // note that we start from 0!
		0, 1, 3, // first triangle
			1, 2, 3 // second triangle
	};

	float textureCoords[] {
		0.0f, 0.0f, // lower-left corner
		1.0f, 0.0f, // lower-right corner
		0.5f, 1.0f // top-center corner
	};
	//

	// 1. bind Vertex Array Object
	glBindVertexArray(vao);
	// 2. copy our vertices array in a vertex buffer for OpenGL to use
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
	// 3. copy our index array in a element buffer for OpenGL to use
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices_), indices_, GL_STATIC_DRAW);

	// 4. then set the vertex attributes pointers
	// position attribute
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);
	// color attribute
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(1);

	return vao;
}

