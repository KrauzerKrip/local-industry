#include "cubemap_system.h"

#include <memory>

#include "cubemap_loader.h"
#include "entt/components.h"
#include "lc_client/eng_scene/entt/components.h"
#include <lc_client/eng_model/entt/components.h>


void CubemapSystem::update() {
	auto requestEntities = m_pRegistry->view<CubemapLoadRequest>();

	for (entt::entity entity : requestEntities) {
		CubemapLoadRequest& request = requestEntities.get<CubemapLoadRequest>(entity);

		m_pCubemapWork->loadCubemap(entity, request.path, m_pRegistry, m_pUtilRegistry);

		m_pRegistry->erase<CubemapLoadRequest>(entity);
	}
}

void CubemapSystem::frame() {
	auto reflectionEntities = m_pRegistry->view<CubemapReflection, Transform>();

	for (auto&& [entity, transform] : reflectionEntities.each()) {
		auto nearestCubemap = getNearestCubemap(transform.position);

		if (nearestCubemap) {
			m_pRegistry->emplace_or_replace<AssignedCubemap>(entity, AssignedCubemap(*nearestCubemap));
		} else {
		    if (m_pRegistry->all_of<AssignedCubemap>(entity)) {
				m_pRegistry->remove<AssignedCubemap>(entity);
		    }
		}
	}
}

std::optional<entt::entity> CubemapSystem::getNearestCubemap(const glm::vec3& position) {
	auto cubemapEntities = m_pRegistry->view<Cubemap, Transform>();

	float minDistance = 0;
	entt::entity nearestCubemap = entt::entity();

	bool isFirstTime = true;

	for (entt::entity entity : cubemapEntities) {
		Transform& cubemapTransform = cubemapEntities.get<Transform>(entity);
		glm::vec3& cubemapPosition = cubemapTransform.position;

		if (isFirstTime) {
			float distance = glm::distance(cubemapPosition, position);
			minDistance = distance;
			nearestCubemap = entity;
		}
		else {
			float distance = glm::distance(cubemapPosition, position);
			if (distance < minDistance) {
				minDistance = distance;
				nearestCubemap = entity;
			}
		}

		isFirstTime = false;
	}

	if (m_pRegistry->valid(nearestCubemap)) {
		return nearestCubemap;
	}

	return std::nullopt;
}
