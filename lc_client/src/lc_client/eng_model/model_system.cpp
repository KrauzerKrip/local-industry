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

		Pack& pack = Pack::getPack(modelRequest.packName);
		Pack::Model modelData(pack, modelRequest.modelName);

		Model* model = m_pModelManager->getModel(modelData.getPath(), modelData.getTexturesPath(), modelData.getMaterialType());

		for (auto& mesh : model->meshes) {
			m_pMeshWork->loadMesh(mesh);
		}

		m_pSceneRegistry->emplace<ShaderRequest>(entity, modelRequest.packName, modelData.getVertexShader(), modelData.getFragmentShader());

		m_pSceneRegistry->erase<ModelRequest>(entity);
	}


}
