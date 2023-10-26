#include "map.h"
#include "lc_client/eng_scene/entt/components.h"
#include "lc_client/eng_model/entt/components.h"

Map::Map() {}

Map::~Map() {}

void Map::loadMap(std::string pack, std::string map) {
	m_registry.clear();
	m_utilRegistry.clear();

	entt::entity surface = m_registry.create();
	m_registry.emplace<Transform>(surface, glm::vec3(0, 0, 0), glm::vec3(0, 0, 0), glm::vec3(100, 0.1, 100));
	m_registry.emplace<ModelRequest>(surface, "dev", "test_surface");


}

entt::registry& Map::getRegistry() { return m_registry; }

entt::registry& Map::getUtilRegistry() { return m_utilRegistry; }
