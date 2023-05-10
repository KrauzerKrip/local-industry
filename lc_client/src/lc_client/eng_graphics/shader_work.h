#pragma once

#include <entt/entt.hpp>

#include "entt/components.h"


class ShaderWork {
public:
	ShaderWork(entt::registry* pRegistry)
		: m_pRegistry(pRegistry) {}

	virtual void loadShaders(entt::entity entity, const std::string vertexShaderName, const std::string fragmentShaderName) = 0;

protected:
	entt::registry* m_pRegistry = nullptr;
};
