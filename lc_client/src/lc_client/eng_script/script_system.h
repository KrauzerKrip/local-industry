#pragma once

#include <entt/entt.hpp>
#include <string>

#include "lc_client/eng_script/api/api.h"

class ScriptSystem {
public:
	ScriptSystem(entt::registry* pRegistry);
	~ScriptSystem() = default;

	void update();
	void frame();

	static std::string m_currentId;

private:
	entt::registry* m_pRegistry;

	Api m_api;
};
