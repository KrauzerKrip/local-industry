#pragma once

#include <vector>

#include <entt/entt.hpp>

#include "../i_graphics_entities_loading.h"
#include "lc_client/eng_procedures/i_shaders.h"


class GraphicsEntitiesLoadingGl : public IGraphicsEntitiesLoading {
public:
	GraphicsEntitiesLoadingGl(IShaderManager* shaderManager);
	~GraphicsEntitiesLoadingGl();

	void loadSceneEntities(entt::registry* registry);
	void loadMapEntities(entt::registry* registry);
private:
	unsigned int createShaderProgram(std::string vertexShaderName, std::string fragmentShaderName);
	unsigned int createVao(); //change to std::vector<Vertice> vertices
	unsigned int createTexture(std::string textureName);

	IShaderManager* m_pShaderManager;
};
