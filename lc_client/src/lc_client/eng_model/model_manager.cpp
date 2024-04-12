#include "model_manager.h"
#include "model_manager.h"

#include <iostream>
#include <stdexcept>
#include <memory>

#include "entt/components.h"
#include "lc_client/exceptions/io_exceptions.h"
#include "lc_client/eng_model/model_loading.h"
#include "lc_client/eng_graphics/entt/components.h"


ModelManager::ModelManager(
	eng::IResource* pResource, entt::registry& pUtilRegistry, IConsole* pConsole) {
	m_pResource = pResource;
	m_pUtilRegistry = &pUtilRegistry;
	m_pConsole = pConsole;
}

Model* ModelManager::getModel(const std::string modelPath, const std::string texturesDirPath, const std::string materialType) {
	try {
		return m_modelMap.at(modelPath);
	}
	catch (std::out_of_range) {
		std::cout << "Model '" << modelPath << "' not found in cache, will try to load." << std::endl;
		return loadModel(modelPath, texturesDirPath, materialType);
	}
}

void ModelManager::setTextureManager(TextureManager* pTextureManager) { m_pTextureManager = pTextureManager; }

Model* ModelManager::loadModel(const std::string modelPath, const std::string texturesDirPath, const std::string materialType) {
	Model* pModel = nullptr;  

	bool success = false;

	try {
		eng::ModelLoading modelLoading(
			modelPath, FILE_FORMAT, m_pResource, m_pUtilRegistry);
		pModel = modelLoading.loadModel();

		success = true;
	}
	catch (ResourceFileNotFoundException& exception) {
		std::cerr << "Model resource not found: " << modelPath << ": " << exception.what() << std::endl;

		// "gmod vibe" here just to occur exception and load black-purple textures
		eng::ModelLoading modelLoading(
			ERROR_MODEL_PATH, FILE_FORMAT, m_pResource, m_pUtilRegistry);
		pModel = modelLoading.loadModel();
	}
	catch (AssimpException& exception) {
		std::cerr << "Failed to load model: " << modelPath << ": " << exception.what() << std::endl;

		// "gmod vibe" here just to occur exception and load black-purple textures
		eng::ModelLoading modelLoading(
			ERROR_MODEL_PATH, FILE_FORMAT, m_pResource, m_pUtilRegistry);

		pModel = modelLoading.loadModel();
	}

	if (pModel == nullptr) {
		throw std::runtime_error(
			"ModelManager: pModel of  " + modelPath + "  OR  " + ERROR_MODEL_PATH + "  is nullptr.");
	}

	m_modelMap.emplace(modelPath, pModel);

	if (success) {
		std::cout << "Model '" << modelPath << "' loaded." << std::endl;
		m_pConsole->devMessage("Model '" + modelPath + "' loaded.");
	}
	else {
		std::cout << "Model '" << modelPath << "' wasn`t loaded successfully. Set default instead." << std::endl;
		m_pConsole->warn("Model '" + modelPath + " wasn`t loaded successfully. Set default instead.");
	}

	pModel->materialDir = texturesDirPath;
	pModel->materialType = materialType;

	return pModel;
}

const std::string ModelManager::FILE_FORMAT = ".";
const std::string ModelManager::ERROR_MODEL_PATH = "dev/models/eng_model_not_found/model.obj";
