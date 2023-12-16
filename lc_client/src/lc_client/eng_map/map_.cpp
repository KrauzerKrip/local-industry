#include "map.h"
#include "lc_client/eng_scene/entt/components.h"
#include "lc_client/eng_model/entt/components.h"
#include "lc_client/eng_cubemaps/entt/components.h"

Map::Map() {}

Map::~Map() {}

void Map::loadMap(std::string pack, std::string map) {
	m_registry.clear();
	m_utilRegistry.clear();

	entt::entity cubemap = m_registry.create();

	m_registry.emplace<CubemapLoadRequest>(cubemap, "dev/textures/test_cubemap/");
	Transform transform;
	transform.position = glm::vec3(0, 0, 0);
	m_registry.emplace<Transform>(cubemap, transform);
}

entt::registry& Map::getRegistry() { return m_registry; }

entt::registry& Map::getUtilRegistry() { return m_utilRegistry; }
