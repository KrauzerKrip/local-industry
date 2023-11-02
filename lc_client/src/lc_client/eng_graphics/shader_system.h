#pragma once

#include <entt/entt.hpp>

#include "lc_client/eng_graphics/shader_work.h"


class ShaderSystem {
public:
	ShaderSystem(ShaderWork* pShaderWork, entt::registry* pRegistry);

	void update();

private:
	ShaderWork* m_pShaderWork = nullptr;

	entt::registry* m_pRegistry = nullptr;
};
