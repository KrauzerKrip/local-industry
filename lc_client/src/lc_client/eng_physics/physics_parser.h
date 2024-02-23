#pragma once

#include "lc_client/util/i_eng_resource.h"
#include "lc_client/eng_scene/entt/components.h"
#include "entt/components.h"
#include <pugixml.hpp>

struct ColliderData {
	ColliderType type;
	Transform transform;
};

class PhysicsParser {
public:
	PhysicsParser(eng::IResource* pResource);
	 
	std::vector<ColliderData> parse(std::string filePath);
private:
	ColliderData parseCollider(const pugi::xml_node& colliderNode);

	eng::IResource* m_pResource = nullptr;
};