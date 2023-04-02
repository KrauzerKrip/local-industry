#pragma once

#include <vector>

#include <entt/entt.hpp>

#include "../graphics_entities_loading.h"
#include "lc_client/eng_procedures/i_shaders.h"
#include "gl_texture_manager.h"
#include "lc_client/eng_graphics/entt/components.h"
#include "lc_client/eng_model/model_manager.h"


class GraphicsEntitiesLoadingGl : public GraphicsEntitiesLoading {
public:
	GraphicsEntitiesLoadingGl(IShaderManager* pShaderManager,
		TextureManager* pTextureManager,
		ModelManager* pModelManager,
		entt::registry* pMapRegistry,
		entt::registry* pSceneRegistry,
		entt::registry* pUtilRegistry);

	~GraphicsEntitiesLoadingGl();

	void loadSceneEntities();
	void loadMapEntities();
private:
	void handleModel(Model* pModel);
	unsigned int createShaderProgram(std::string vertexShaderName, std::string fragmentShaderName);
	unsigned int createVao(std::vector<Vertex>& vertices, std::vector<unsigned int>& indices);
};
