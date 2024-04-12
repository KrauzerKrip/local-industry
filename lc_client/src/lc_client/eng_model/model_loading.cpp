#include "model_loading.h"

#include <iostream>

#include "lc_client/exceptions/io_exceptions.h"
#include "lc_client/eng_graphics/entt/components.h"
#include "lc_client/util/file_util.h"


namespace eng {

	ModelLoading::ModelLoading(std::string modelPath,
		std::string fileFormat, eng::IResource* pResource, entt::registry* pUtilRegistry)

		: m_modelPath(modelPath),
		  m_fileFormat(fileFormat),
		  m_pResource(pResource),
		  m_pUtilRegistry(pUtilRegistry) {}

	Model* ModelLoading::loadModel() {

		std::cout << m_modelPath << std::endl;

		std::vector<unsigned char> buffer = m_pResource->getFileResource(m_modelPath);

		const unsigned char* pBuffer = buffer.data();

		Assimp::Importer importer;
		const aiScene* scene = importer.ReadFileFromMemory(
			pBuffer, buffer.size(), aiProcess_Triangulate | aiProcess_FlipUVs, m_fileFormat.c_str());

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

			if (pMesh->mNormals != nullptr) {
				vector.x = pMesh->mNormals[i].x;
				vector.y = pMesh->mNormals[i].y;
				vector.z = pMesh->mNormals[i].z;
				vertex.normal = vector;
			}
			else {
				vertex.normal = glm::vec3(0.0f, 0.0f, 0.0f);
			}

			if (pMesh->mTextureCoords[0]) { // does the pMesh contain texture coordinates?
				glm::vec2 vec;
				vec.x = pMesh->mTextureCoords[0][i].x;
				vec.y = pMesh->mTextureCoords[0][i].y;
				vertex.textureCoords = vec;
			}
			else {
				vertex.textureCoords = glm::vec2(0.0f, 0.0f);
			}
			
			vertices.push_back(vertex);
		}

	}

	void ModelLoading::processIndices(aiMesh* pMesh, std::vector<unsigned int>& indices) {
		for (unsigned int i = 0; i < pMesh->mNumFaces; i++) {
			aiFace face = pMesh->mFaces[i];
			for (unsigned int j = 0; j < face.mNumIndices; j++) {
				indices.push_back(face.mIndices[j]);
			}
		}
	}

}
