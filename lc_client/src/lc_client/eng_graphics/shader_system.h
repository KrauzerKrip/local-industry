#pragma once

#include <entt/entt.hpp>

#include "lc_client/eng_graphics/shader_loader.h"


class ShaderSystem {
public:
	ShaderSystem(ShaderLoader* pShaderWork, entt::registry* pRegistry);

	void update();

private:
	ShaderLoader* m_pShaderWork = nullptr;

	entt::registry* m_pRegistry = nullptr;
};
