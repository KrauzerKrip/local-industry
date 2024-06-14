#pragma once

#include <string>

#include <entt/entt.hpp>
#include <pugixml.hpp>

#include "lc_client/util/i_eng_resource.h"


class MachineLoader {
public:
	MachineLoader(eng::IResource* pResource, entt::registry* pRegistry);

	void loadMachine(entt::entity, std::string typeString);

private:
	void handleComponent(pugi::xml_node componentXml, entt::entity entity);
	void handleConnection(pugi::xml_node connectionXml, entt::entity entity);

	const std::string m_machinesPath = "game/machines/";

	eng::IResource* m_pResource = nullptr;

	entt::registry* m_pRegistry = nullptr;
};