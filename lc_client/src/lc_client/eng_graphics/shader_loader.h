#pragma once

#include <entt/entt.hpp>

#include "entt/components.h"


class ShaderLoader {
public:
	ShaderLoader(){};

	virtual void loadShaders(entt::registry* pRegistry, entt::entity entity, const std::string vertexShaderName, const std::string fragmentShaderName) = 0;

protected:
};
