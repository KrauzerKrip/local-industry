#include "gl_graphics_entities_loading.h"

#include <iostream>
#include <glad/glad.h>

#include "lc_client/eng_scene/entt/components.h"
#include "lc_client/eng_graphics/entt/components.h"
#include "lc_client/eng_graphics/texture.h"


GraphicsEntitiesLoadingGl::GraphicsEntitiesLoadingGl(IShaderManager* pShaderManager,
	TextureManager* pTextureManager,
	ModelManager* pModelManager,
	entt::registry* pMapRegistry,
	entt::registry* pSceneRegistry,
	entt::registry* pUtilRegistry)
	: GraphicsEntitiesLoading{ pShaderManager, pTextureManager, pModelManager,
	pMapRegistry, pSceneRegistry, pUtilRegistry } {};

GraphicsEntitiesLoadingGl::~GraphicsEntitiesLoadingGl() {};

void GraphicsEntitiesLoadingGl::loadMapEntities() {
	
}

void GraphicsEntitiesLoadingGl::loadSceneEntities() {
	auto entitiesGroup = m_pSceneRegistry->group<Properties, ModelData>();
	 

	for (entt::entity entity : entitiesGroup) {

		Properties& properties = entitiesGroup.get<Properties>(entity);
		ModelData& modelData = entitiesGroup.get<ModelData>(entity);
		const std::string id = modelData.id;
		const std::string vertexShaderName = modelData.vertexShader;
		const std::string fragmentShaderName = modelData.fragmentShader;

		unsigned int shaderProgram = createShaderProgram(vertexShaderName, fragmentShaderName);

		Model* pModel = m_pModelManager->getModel(modelData.path, modelData.texturesPath);

		handleModel(pModel);
      
		Model& model = m_pSceneRegistry->emplace<Model>(entity, pModel->meshes);
		delete pModel;

		m_pSceneRegistry->erase<ModelData>(entity);
	}
}

void GraphicsEntitiesLoadingGl::handleModel(Model* pModel) {
	std::vector<Mesh>& meshes = pModel->meshes;

	for (Mesh& mesh : meshes) { 
		mesh.vaoId = createVao(mesh.vertices, mesh.indices);

		entt::entity materialEntity = mesh.material;

		MaterialSG& materialSG = m_pUtilRegistry->get<MaterialSG>(materialEntity); // materialEntity was nullptr.
		
		materialSG.aoTexture->load();
		materialSG.diffuseTexture->load();
		materialSG.glossinessTexture->load();
		materialSG.normalMap->load();
		materialSG.specularTexture->load();
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

unsigned int GraphicsEntitiesLoadingGl::createVao(std::vector<Vertex>& vertices, std::vector<unsigned int>& indices) {
	unsigned int vbo;
	glGenBuffers(1, &vbo);

	unsigned int vao;
	glGenVertexArrays(1, &vao);

	unsigned int ebo;
	glGenBuffers(1, &ebo);

	glBindVertexArray(vao);

	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(Vertex), &vertices[0], GL_STATIC_DRAW);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(unsigned int), &indices[0], GL_STATIC_DRAW);
	
	// vertex positions
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)0);
	
	// vertex normals
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, normal));
	
	// vertex texture coords
	glEnableVertexAttribArray(2);
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, textureCoords));
	glBindVertexArray(0);

	return vao;
}

