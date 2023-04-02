#include "model_manager.h"

#include <iostream>
#include <stdexcept>
#include <memory>

#include "entt/components.h"
#include "lc_client/exceptions/io_exceptions.h"
#include "lc_client/eng_model/model_loading.h"
#include "lc_client/eng_graphics/entt/components.h"


ModelManager::ModelManager(eng::IResource* pResource, TextureManager* pTextureManager, entt::registry* pUtilRegistry) {
	m_pResource = pResource;
	m_pTextureManager = pTextureManager;
	m_pUtilRegistry = pUtilRegistry;
}

Model* ModelManager::getModel(const std::string modelPath, const std::string texturesDirPath) {
	try {
		return m_modelMap.at(modelPath);
	}
	catch (std::out_of_range) {
		std::cout << "Model '" << modelPath << "' not found in cache, will try to load." << std::endl;
		return loadModel(modelPath, texturesDirPath);
	}
}
  
Model* ModelManager::loadModel(const std::string modelPath, const std::string texturesDirPath) {

	Model* pModel;

	try {
		eng::ModelLoading modelLoading(modelPath, texturesDirPath, FILE_FORMAT, m_pResource, m_pTextureManager);
		pModel = modelLoading.loadModel();

		std::vector<MaterialSG&>& materials = modelLoading.getMeshesMaterialsSG();

		std::vector<Mesh> meshes = pModel->meshes;

		for (unsigned int i = 0; i < meshes.size(); i++) {
			MaterialSG& material = materials.at(i);
			auto materialEntity = m_pUtilRegistry->create();
			m_pUtilRegistry->emplace<MaterialSG>(materialEntity, material);
			meshes.at(i).material = &materialEntity;
		}
	}
	catch (AssimpException& exception) {
		std::cerr << "Failed to load model: " << modelPath << ": " << exception.what() << std::endl;
		
		// "gmod vibe" here just to occur exception and load black-purple textures
		eng::ModelLoading modelLoading("dev/textures/eng_object_not_found/model", "gmod_vibe", FILE_FORMAT, m_pResource, m_pTextureManager);

		pModel = modelLoading.loadModel();
	}

	m_modelMap.emplace(modelPath, pModel);

	std::cout << "Model" << modelPath << "' loaded." << std::endl;
	 
	return pModel;
}

const std::string ModelManager::FILE_FORMAT = ".";
