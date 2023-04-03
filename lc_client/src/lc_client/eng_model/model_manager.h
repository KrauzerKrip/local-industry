#pragma once

#include <unordered_map> 

#include <entt/entt.hpp>

#include "lc_client/util/eng_resource.h"
#include "entt/components.h"
#include "lc_client/eng_procedures/openGL/gl_texture_manager.h"

class ModelManager {

public:
	ModelManager(eng::IResource* pResource, TextureManager* pTextureManager, entt::registry* pUtilRegistry);

	Model* getModel(const std::string modelPath, const std::string texturesDirPath);

private :
	Model* loadModel(const std::string modelPath, const std::string texturesDirPath);

	std::unordered_map<std::string, Model*> m_modelMap;

	eng::IResource* m_pResource;
	TextureManager* m_pTextureManager;
	entt::registry* m_pUtilRegistry;

	const static std::string FILE_FORMAT;
};
