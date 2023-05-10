#pragma once

#include <entt/entt.hpp>

#include "lc_client/eng_procedures/i_shaders.h"
#include "lc_client/eng_procedures/texture_manager.h"
#include "lc_client/eng_graphics/entt/components.h"
#include "lc_client/eng_model/model_manager.h"


class GraphicsEntitiesUtil {
public:
	GraphicsEntitiesUtil(IShaderManager* pShaderManager, TextureManager* pTextureManager, ModelManager* pModelManager,
		entt::registry* pMapRegistry, entt::registry* pSceneRegistry, entt::registry* pUtilRegistry)
		: m_pShaderManager(pShaderManager),
		  m_pTextureManager(pTextureManager),
		  m_pModelManager(pModelManager),
		  m_pMapRegistry(pMapRegistry),
		  m_pSceneRegistry(pSceneRegistry),
		  m_pUtilRegistry(pUtilRegistry) {};
	
	~GraphicsEntitiesUtil() = default;


	virtual void setModel(entt::entity entity, std::string packName, std::string modelName) = 0;
	virtual void setVertexShader(entt::entity entity, std::string packName, std::string shaderName) = 0;
	virtual void setFragmentShader(entt::entity entity, std::string packName, std::string shaderName) = 0;

protected:
	IShaderManager* m_pShaderManager = nullptr;
	TextureManager* m_pTextureManager = nullptr;
	ModelManager* m_pModelManager = nullptr;
	entt::registry* m_pMapRegistry = nullptr;
	entt::registry* m_pSceneRegistry = nullptr;
	entt::registry* m_pUtilRegistry = nullptr;
};
