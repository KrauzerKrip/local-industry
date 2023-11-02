#pragma once

#include <entt/entt.hpp>

#include "entt/components.h"


class ShaderWork {
public:
	ShaderWork(){};

	virtual void loadShaders(entt::registry* pRegistry, entt::entity entity, const std::string vertexShaderName, const std::string fragmentShaderName) = 0;

protected:
};
