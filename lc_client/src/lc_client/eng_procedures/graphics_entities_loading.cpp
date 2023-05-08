#include "graphics_entities_loading.h"

#include <iostream>

#include "lc_client/eng_scene/entt/components.h"
#include "lc_client/eng_graphics/entt/components.h"
#include "lc_client/util/pack.h"
#include "lc_client/exceptions/io_exceptions.h"



void GraphicsEntitiesLoading::loadMapEntities() {}

void GraphicsEntitiesLoading::loadSceneEntities() {
	auto entitiesGroup = m_pSceneRegistry->group<Properties, ModelData>();

	for (entt::entity entity : entitiesGroup) {
		Properties& properties = entitiesGroup.get<Properties>(entity);
		ModelData& modelData = entitiesGroup.get<ModelData>(entity);
		const std::string packName = modelData.packName;
		const std::string modelName = modelData.modelName;

		m_pGraphicsEntitiesUtil->setModel(entity, packName, modelName);
	}
}


