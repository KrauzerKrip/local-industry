#pragma once

#include <entt/entt.hpp>

#include "lc_client/eng_script/api/api.h"
#include "lc_client/eng_graphics/graphics_entities_util.h"


class ScriptSystem {
public:
	ScriptSystem(entt::registry* pRegistry, GraphicsEntitiesUtil* temp);
	~ScriptSystem() = default;

	void update();
	void frame();

private:
	entt::registry* m_pRegistry;

	Api m_api;
};
