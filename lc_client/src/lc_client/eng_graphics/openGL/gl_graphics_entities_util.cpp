#include "gl_graphics_entities_util.h"

#include <iostream>
#include <glad/glad.h>

#include "lc_client/eng_scene/entt/components.h"
#include "lc_client/eng_graphics/entt/components.h"
#include "lc_client/eng_graphics/texture.h"
#include "lc_client/util/pack.h"
#include "lc_client/exceptions/io_exceptions.h"
#include "lc_client/eng_procedures/i_shaders.h"
#include "lc_client/eng_procedures/openGL/gl_texture_manager.h"


void GraphicsEntitiesUtilGl::setModel(entt::entity entity, std::string packName, std::string modelName) {

	Model* pModel = nullptr;
	unsigned int shaderProgram = 0;

	try {

		try {
			Pack& pack = Pack::getPack(packName);
			Pack::Model modelDataFull = Pack::Model(pack, modelName);
			pModel = m_pModelManager->getModel(
				modelDataFull.getPath(), modelDataFull.getTexturesPath(), modelDataFull.getMaterialType());
			shaderProgram = createShaderProgram(modelDataFull.getVertexShader(), modelDataFull.getFragmentShader());
		}
		catch (std::runtime_error& exception) {
			std::cerr << exception.what() << std::endl;
		}

		if (pModel == nullptr) {
			pModel = m_pModelManager->getModel("gmodVibe", "gmodVibe", "sg");
		}
		if (shaderProgram == 0) {
			shaderProgram = createShaderProgram("base", "base");
		}

		handleModel(pModel);

		std::cout << std::endl << "pre placing" << std::endl << std::endl;

		m_pSceneRegistry->emplace_or_replace<Model>(entity, *pModel); // TODO: fix

		std::cout << std::endl << "placed" << std::endl << std::endl;

		m_pSceneRegistry->emplace_or_replace<ShaderGl>(entity, (int) shaderProgram);
	}
	catch (std::runtime_error& exception) {
		std::cerr << exception.what() << std::endl;
		exit(1);
	}
}

/**
 *  @todo
 * @brief
 * @param entity
 * @param packName
 * @param shaderName
 */
void GraphicsEntitiesUtilGl::setVertexShader(entt::entity entity, std::string packName, std::string shaderName) {
	//Pack& pack = Pack::getPack(packName);
	//Pack::VertexShader shaderData = Pack::VertexShader(pack, shaderName);
	// shaderProgram = createShaderProgram(shaderData., modelDataFull.getFragmentShader());
}

/**
 *  @todo
 * @brief
 * @param entity
 * @param packName
 * @param shaderName
 */
void GraphicsEntitiesUtilGl::setFragmentShader(entt::entity entity, std::string packName, std::string shaderName) {}


void GraphicsEntitiesUtilGl::handleModel(Model* pModel) {
	std::vector<entt::entity>& meshes = pModel->meshes;

	for (entt::entity& entity : meshes) {

		Mesh& mesh = m_pUtilRegistry->get<Mesh>(entity);
		MaterialSG& materialSG = m_pUtilRegistry->get<MaterialSG>(entity);

		mesh.vaoId = createVao(mesh.vertices, mesh.indices);

		materialSG.aoTexture->load();
		materialSG.diffuseTexture->load();
		materialSG.glossinessTexture->load();
		materialSG.normalMap->load();
		materialSG.specularTexture->load();
	}
}

unsigned int GraphicsEntitiesUtilGl::createShaderProgram(std::string vertexShaderName, std::string fragmentShaderName) {
	unsigned int shaderProgram;
	shaderProgram = glCreateProgram();

	try {
		glAttachShader(shaderProgram, m_pShaderManager->getFragmentShader(fragmentShaderName));
	}
	catch (const std::out_of_range& exception) {
		std::cerr << exception.what() << std::endl;
	}
	try {
		glAttachShader(shaderProgram, m_pShaderManager->getVertexShader(vertexShaderName));
	}
	catch (const std::out_of_range& exception) {
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
		std::cerr << "gl_graphics_entities_loading: shader program link failure: \n" << infoLog << std::endl;
	}

	return shaderProgram;
}

unsigned int GraphicsEntitiesUtilGl::createVao(std::vector<Vertex>& vertices, std::vector<unsigned int>& indices) {
	unsigned int vbo;
	glGenBuffers(1, &vbo);

	unsigned int vao;
	glGenVertexArrays(1, &vao);

	unsigned int ebo;
	glGenBuffers(1, &ebo);

	glBindVertexArray(vao);

	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(Vertex), vertices.data(), GL_STATIC_DRAW);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(unsigned int), indices.data(), GL_STATIC_DRAW);

	// vertex positions
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)0);

	// vertex normals
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, normal));


	// vertex texture coords
	glEnableVertexAttribArray(2);
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)(offsetof(Vertex, textureCoords)));

	glBindVertexArray(0);

	return vao;
}
