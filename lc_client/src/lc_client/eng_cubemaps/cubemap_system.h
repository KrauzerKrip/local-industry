#pragma once

#include <optional>

#include <entt/entt.hpp>
#include <glm/glm.hpp>

#include "cubemap_loader.h"
#include "lc_client/util/eng_resource.h"


class CubemapSystem {
public:
	CubemapSystem(entt::registry* pRegistry, entt::registry* pUtilRegistry, CubemapLoader* pCubemapWork)
		: m_pRegistry(pRegistry),
    m_pUtilRegistry(pUtilRegistry),
    m_pCubemapWork(pCubemapWork) {}

	void update();
	void frame();

private:
	std::optional<entt::entity> getNearestCubemap(const glm::vec3& position);

	entt::registry* m_pRegistry = nullptr;
	entt::registry* m_pUtilRegistry = nullptr;
	CubemapLoader* m_pCubemapWork = nullptr;
};
