#pragma once

#include <entt/entt.hpp>


class ScriptSystem {
public:
	ScriptSystem(entt::registry* pRegistry);
	~ScriptSystem() = default;

	void update();
	void frame();

private:
	entt::registry* m_pRegistry;
};
