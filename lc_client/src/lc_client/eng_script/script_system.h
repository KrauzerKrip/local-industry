#pragma once

#include <entt/entt.hpp>

#include "lc_client/eng_script/api/api.h"

class ScriptSystem {
public:
	ScriptSystem(entt::registry* pRegistry);
	~ScriptSystem() = default;

	void update();
	void frame();

private:
	entt::registry* m_pRegistry;

	Api m_api;
};
