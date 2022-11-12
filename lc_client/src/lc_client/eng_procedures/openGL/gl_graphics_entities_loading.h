#pragma once

#include <vector>

#include <entt/entt.hpp>

#include "../i_graphics_entities_loading.h"
#include "lc_client/eng_procedures/i_shaders.h"
#include "gl_texture_manager.h"


class GraphicsEntitiesLoadingGl : public IGraphicsEntitiesLoading {
public:
	GraphicsEntitiesLoadingGl(IShaderManager* pShaderManager, TextureManager* pTextureManager);
	~GraphicsEntitiesLoadingGl();

	void loadSceneEntities(entt::registry* registry);
	void loadMapEntities(entt::registry* registry);
private:
	unsigned int createShaderProgram(std::string vertexShaderName, std::string fragmentShaderName);
	unsigned int createVao(); //change to std::vector<Vertice> vertices

	IShaderManager* m_pShaderManager;
	TextureManager* m_pTextureManager;
};
