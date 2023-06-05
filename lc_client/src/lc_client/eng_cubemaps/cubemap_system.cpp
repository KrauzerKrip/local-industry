#include "cubemap_system.h"

#include <memory>

#include "cubemap_loader.h"
#include "entt/components.h"


void CubemapSystem::update() {
	auto requestEntities = m_pRegistry->view<CubemapLoadRequest>();

	for (entt::entity entity : requestEntities) {
		CubemapLoadRequest& request = requestEntities.get<CubemapLoadRequest>(entity);

		m_pCubemapWork->loadCubemap(entity, request.path);

		m_pRegistry->erase<CubemapLoadRequest>(entity);
	}
}
