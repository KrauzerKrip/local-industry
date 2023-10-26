#pragma once

#include <string>
#include <entt/entt.hpp>


class Map {
public:
	Map();
	~Map();

	void loadMap(std::string pack, std::string map);

	entt::registry& getRegistry();
	entt::registry& getUtilRegistry();

private:
	entt::registry m_registry;
	entt::registry m_utilRegistry;

	std::string m_name;
	std::string m_pack;
};