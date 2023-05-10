#pragma once

#include "lc_client/eng_graphics/graphics_entities_util.h"


class GraphicsEntitiesUtilGl : public GraphicsEntitiesUtil {
public:
	GraphicsEntitiesUtilGl(IShaderManager* pShaderManager, TextureManager* pTextureManager, ModelManager* pModelManager,
		entt::registry* pMapRegistry, entt::registry* pSceneRegistry, entt::registry* pUtilRegistry)
		: GraphicsEntitiesUtil(
			  pShaderManager, pTextureManager, pModelManager, pMapRegistry, pSceneRegistry, pUtilRegistry) {}

	~GraphicsEntitiesUtilGl() = default;

	void setModel(entt::entity entity, std::string packName, std::string modelName);
	void setVertexShader(entt::entity entity, std::string packName, std::string shaderName);
	void setFragmentShader(entt::entity entity, std::string packName, std::string shaderName);

private:
	void handleModel(Model* pModel);
	unsigned int createShaderProgram(std::string vertexShaderName, std::string fragmentShaderName);
	unsigned int createVao(std::vector<Vertex>& vertices, std::vector<unsigned int>& indices);
};
