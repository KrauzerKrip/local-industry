#include "model_system.h"

#include "lc_client/eng_model/entt/components.h"
#include "lc_client/util/pack.h"
#include "lc_client/util/timer.h"
#include <lc_client/exceptions/io_exceptions.h>


ModelSystem::ModelSystem(ModelManager* pModelManager, ModelParser* pModelParser, MeshLoader* pMeshWork,
	entt::registry* pSceneRegistry, entt::registry* pUtilRegistry) {
	m_pModelManager = pModelManager;
	m_pModelParser = pModelParser;
	m_pMeshWork = pMeshWork;
	m_pSceneRegistry = pSceneRegistry;
	m_pUtilRegistry = pUtilRegistry;
}

void ModelSystem::update() {
	auto entities = m_pSceneRegistry->view<ModelRequest>();

	for (auto& entity : entities) {
		ModelRequest& modelRequest = entities.get<ModelRequest>(entity);

		std::string modelDirPath;
		try {
			Pack& pack = Pack::getPack(modelRequest.packName);
			modelDirPath = Pack::Model(pack, modelRequest.modelName).getPath();
		}
		catch (std::runtime_error& exception) {
			Pack& pack = Pack::getPack("dev");
			modelDirPath = Pack::Model(pack, "eng_model_not_found").getPath();
			std::cerr << exception.what() << std::endl;
		} 

		Model* pModel = nullptr;

		auto modelCashed = m_loadedModelMap.find(modelRequest);

		if (modelCashed != m_loadedModelMap.end()) {
			auto&& [pModel, vertexShader, fragmentShader] = modelCashed->second;
			m_pSceneRegistry->emplace_or_replace<Model>(entity, *pModel);
			if (modelRequest.loadShaders) {
				m_pSceneRegistry->emplace<ShaderRequest>(entity, modelRequest.packName, vertexShader, fragmentShader);
			}
			m_pSceneRegistry->erase<ModelRequest>(entity);
			
			break;
		}

		std::string modelVertexShader;
		std::string modelFragmentShader;

		try {
			ModelData modelData = m_pModelParser->parse(modelDirPath + "model.xml");
			pModel = m_pModelManager->getModel(
				modelDirPath + modelData.modelFile, modelDirPath, modelData.materialType);
			if (modelRequest.loadShaders) {
				m_pSceneRegistry->emplace<ShaderRequest>(
					entity, modelRequest.packName, modelData.vertexShader, modelData.fragmentShader);
			}

			modelVertexShader = modelData.vertexShader;
			modelFragmentShader = modelData.fragmentShader;
		}
		catch (std::runtime_error& exception) {
			std::cerr << exception.what() << std::endl;
		}

		if (pModel == nullptr) {
			pModel = m_pModelManager->getModel("gmodVibe", "gmodVibe", "sg");
			m_pSceneRegistry->emplace<ShaderRequest>(entity, modelRequest.packName, "base", "base");
			modelVertexShader = "base";
			modelFragmentShader = "base";
		}

		for (auto& mesh : pModel->meshes) {
			m_pMeshWork->loadMesh(m_pUtilRegistry, mesh);
		}

		m_pSceneRegistry->emplace_or_replace<Model>(entity, *pModel);

		m_loadedModelMap.emplace(modelRequest, std::make_tuple(pModel, modelVertexShader, modelFragmentShader));

		m_pSceneRegistry->erase<ModelRequest>(entity);
	}
}
