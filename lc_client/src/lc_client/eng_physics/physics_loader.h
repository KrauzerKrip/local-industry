#pragma once

#include <entt/entt.hpp>

#include "physics_parser.h"
#include "lc_client/util/i_eng_resource.h"
#include "lc_client/tier0/console/i_console.h"


class PhysicsLoader {
public:
	PhysicsLoader(PhysicsParser* pPhysicsParser, entt::registry* pRegistry);

	void loadPhysics(entt::entity entity, std::string path);

private:
	[[nodiscard]]
	entt::entity loadCollider(const ColliderData& colliderData);

	PhysicsParser* m_pPhysicsParser = nullptr;
	entt::registry* m_pRegistry = nullptr;
	IConsole* m_pConsole = nullptr;
};