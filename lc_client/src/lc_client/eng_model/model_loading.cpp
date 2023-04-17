#include "model_loading.h"

#include <iostream>

#include "lc_client/exceptions/io_exceptions.h"	
#include "lc_client/eng_graphics/entt/components.h"
#include "lc_client/eng_procedures/openGL/gl_texture_manager.h"
#include "lc_client/util/file_util.h"


namespace eng {

	ModelLoading::ModelLoading(std::string modelPath,
		std::string texturesDirPath,
		std::string fileFormat,
		eng::IResource* pResource,
		TextureManager* pTextureManager,
		entt::registry* pUtilRegistry)

		: m_modelPath(modelPath),
		m_texturesDirPath(texturesDirPath),
		m_fileFormat(fileFormat),
		m_pResource(pResource),
		m_pTextureManager(pTextureManager),
		m_pUtilRegistry(pUtilRegistry) {}

	std::vector<MaterialSG>& ModelLoading::getMeshesMaterialsSG() {
		return m_materials;
	};

	int ModelLoading::cat() { return 1; };

	Model* ModelLoading::loadModel() {

		std::cout << m_modelPath << std::endl;

		std::vector<unsigned char> buffer = m_pResource->getFileResource(m_modelPath);

		const unsigned char* pBuffer = buffer.data();

		Assimp::Importer importer;
		const aiScene* scene = importer.ReadFileFromMemory(pBuffer, buffer.size(), aiProcess_Triangulate | aiProcess_FlipUVs, m_fileFormat.c_str());

		if (!scene || scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE || !scene->mRootNode) {
			throw AssimpException(importer.GetErrorString());
		}

		Model* pModel = new Model();

		eng::ModelLoading::processNode(scene->mRootNode, scene, pModel);

		return pModel;
	}

	void ModelLoading::processNode(aiNode* node, const aiScene* scene, Model* pModel) {

		std::vector<entt::entity>& meshes = pModel->meshes;

		for (unsigned int i = 0; i < node->mNumMeshes; i++) {
			aiMesh* pMesh = scene->mMeshes[node->mMeshes[i]];
			entt::entity entity = m_pUtilRegistry->create();
			m_pUtilRegistry->emplace<Mesh>(entity, eng::ModelLoading::processMesh(pMesh, scene));

			MaterialSG materialSG;
			if (pMesh->mMaterialIndex >= 0) {
				eng::ModelLoading::processMaterialSG(scene->mMaterials[pMesh->mMaterialIndex], materialSG);
			}

			m_pUtilRegistry->emplace<MaterialSG>(entity, materialSG);

			meshes.push_back(entity);
		}

		for (unsigned int i = 0; i < node->mNumChildren; i++) {
			eng::ModelLoading::processNode(node->mChildren[i], scene, pModel);
		}
	}

	Mesh ModelLoading::processMesh(aiMesh* pMesh, const aiScene* scene) {
		std::vector<Vertex> vertices;
		std::vector<unsigned int> indices;
		std::vector<Texture> textures;

		eng::ModelLoading::processVertices(pMesh, vertices);
		eng::ModelLoading::processIndices(pMesh, indices);

		Mesh mesh = Mesh();
		mesh.vertices = vertices;
		mesh.indices = indices;

		return mesh;
	}

	void ModelLoading::processVertices(aiMesh* pMesh, std::vector<Vertex>& vertices) {
		for (unsigned int i = 0; i < pMesh->mNumVertices; i++) {
			Vertex vertex;

			glm::vec3 vector;
			vector.x = pMesh->mVertices[i].x;
			vector.y = pMesh->mVertices[i].y;
			vector.z = pMesh->mVertices[i].z;
			vertex.position = vector;
			vertices.push_back(vertex);

			if (pMesh->mNormals != nullptr) {
				vector.x = pMesh->mNormals[i].x;
				vector.y = pMesh->mNormals[i].y;
				vector.z = pMesh->mNormals[i].z;
				vertex.normal = vector;
			}
			else {
				vertex.normal = glm::vec3(0.0f, 0.0f, 0.0f);
			}

			if (pMesh->mTextureCoords[0]) {  // does the pMesh contain texture coordinates? 
				glm::vec2 vec;
				vec.x = pMesh->mTextureCoords[0][i].x;
				vec.y = pMesh->mTextureCoords[0][i].y;
				vertex.textureCoords = vec;
			}
			else {
				vertex.textureCoords = glm::vec2(0.0f, 0.0f);
			}
		}
	}

	void ModelLoading::processIndices(aiMesh* pMesh, std::vector<unsigned int>& indices) {
		for (unsigned int i = 0; i < pMesh->mNumFaces; i++) {
			aiFace face = pMesh->mFaces[i];
			for (unsigned int j = 0; j < face.mNumIndices; j++)
				indices.push_back(face.mIndices[j]);
		}
	}
	void ModelLoading::processMaterialMR(aiMaterial* pMaterial, MaterialMR& material) {
		aiString str;

		std::cout << "processMaterialMR in model_loading.cpp isn`t ready yet" << std::endl;

		assert(1);

		pMaterial->GetTexture(aiTextureType_BASE_COLOR, 0, &str);
		std::cout << "processMaterial BASE_COLOR str: " << str.C_Str() << std::endl;
		material.colorTexture = m_pTextureManager->getTexture(m_texturesDirPath + str.C_Str());

		//pMaterial->GetTexture(aiTextureType_, 0, &str);
		material.metallicTexture = m_pTextureManager->getTexture(m_texturesDirPath + str.C_Str());

		pMaterial->GetTexture(aiTextureType_AMBIENT_OCCLUSION, 0, &str);
		material.aoTexture = m_pTextureManager->getTexture(m_texturesDirPath + str.C_Str());

		pMaterial->GetTexture(aiTextureType_AMBIENT_OCCLUSION, 0, &str);
		material.aoTexture = m_pTextureManager->getTexture(m_texturesDirPath + str.C_Str());

		pMaterial->GetTexture(aiTextureType_AMBIENT_OCCLUSION, 0, &str);
		material.aoTexture = m_pTextureManager->getTexture(m_texturesDirPath + str.C_Str());
	}

	void ModelLoading::processMaterialSG(aiMaterial* pMaterial, MaterialSG& material) {
		aiString str;

		pMaterial->GetTexture(aiTextureType_DIFFUSE, 0, &str);
		std::cout << "processMaterial DIFFUSE str: " << str.C_Str() << std::endl;
		material.diffuseTexture = m_pTextureManager->getTexture(m_texturesDirPath + "diffuse"); // str.C_Str());
		material.diffuseTexture->setTextureType(TextureType::DIFFUSE);

		pMaterial->GetTexture(aiTextureType_SPECULAR, 0, &str);
		material.specularTexture = m_pTextureManager->getTexture(m_texturesDirPath + str.C_Str());
		material.specularTexture->setTextureType(TextureType::SPECULAR);

		pMaterial->GetTexture(aiTextureType_SHININESS, 0, &str);
		material.glossinessTexture = m_pTextureManager->getTexture(m_texturesDirPath + str.C_Str());
		material.glossinessTexture->setTextureType(TextureType::GLOSSINESS);

		pMaterial->GetTexture(aiTextureType_AMBIENT_OCCLUSION, 0, &str);
		material.aoTexture = m_pTextureManager->getTexture(m_texturesDirPath + str.C_Str());
		material.aoTexture->setTextureType(TextureType::AO);

		pMaterial->GetTexture(aiTextureType_NORMALS, 0, &str);
		material.normalMap = m_pTextureManager->getTexture(m_texturesDirPath + str.C_Str());
		material.normalMap->setTextureType(TextureType::NORMAL);
	} 

}

