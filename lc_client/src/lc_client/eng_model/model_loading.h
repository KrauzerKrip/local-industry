#pragma once

#include <vector>

#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

#include "entt/components.h"
#include "lc_client/eng_procedures/openGL/gl_texture_manager.h"
#include "lc_client/util/eng_resource.h"


namespace eng {

	class ModelLoading {

	public:
		ModelLoading(const std::string& modelPath, const std::string& texturesDirPath, const std::string& fileFormat, eng::IResource* pResource, TextureManager* pTextureManager);
		Model* loadModel();
		std::vector<MaterialSG&>& getMeshesMaterialsSG();

	private:
		 void processNode(aiNode* node, const aiScene* scene, Model* pModel);

		 Mesh processMesh(aiMesh* pMesh, const aiScene* scene);

		 void processVertices(aiMesh* pMesh, std::vector<Vertex>& vertices);
		 void processIndices(aiMesh* pMesh, std::vector<unsigned int>& indices);
		 void processMaterialMR(aiMaterial* pMaterial, MaterialMR& material);
		 void processMaterialSG(aiMaterial* pMaterial, MaterialSG& material);


		 const std::string& m_modelPath;
		 const std::string& m_texturesDirPath;
		 const std::string& m_fileFormat;
		 eng::IResource* m_pResource = nullptr;
		 TextureManager* m_pTextureManager = nullptr;
		 std::vector<MaterialSG&> m_materials;
	
	};
}
