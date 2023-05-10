#include "model_system.h"

#include "lc_client/eng_model/entt/components.h"
#include "lc_client/util/pack.h"


ModelSystem::ModelSystem(ModelManager* pModelManager, MeshWork* pMeshWork, entt::registry* pSceneRegistry) {
	m_pModelManager = pModelManager;
	m_pMeshWork = pMeshWork;
	m_pSceneRegistry = pSceneRegistry;
}

void ModelSystem::update() {
	auto entities = m_pSceneRegistry->view<ModelRequest>();

	for (auto& entity : entities) {
		ModelRequest& modelRequest = entities.get<ModelRequest>(entity);

		Model* pModel = nullptr;

		try {
			Pack& pack = Pack::getPack(modelRequest.packName);
			Pack::Model modelData(pack, modelRequest.modelName);

			pModel = m_pModelManager->getModel(
				modelData.getPath(), modelData.getTexturesPath(), modelData.getMaterialType());

			m_pSceneRegistry->emplace<ShaderRequest>(
				entity, modelRequest.packName, modelData.getVertexShader(), modelData.getFragmentShader());
		}
		catch (std::runtime_error& exception) {
			std::cerr << exception.what() << std::endl;
		}

		if (pModel == nullptr) {
			pModel = m_pModelManager->getModel("gmodVibe", "gmodVibe", "sg");
			m_pSceneRegistry->emplace<ShaderRequest>(entity, modelRequest.packName, "base", "base");
		}

		for (auto& mesh : pModel->meshes) {
			m_pMeshWork->loadMesh(mesh);
		}

		m_pSceneRegistry->emplace_or_replace<Model>(entity, *pModel);

		m_pSceneRegistry->erase<ModelRequest>(entity);
	}
}