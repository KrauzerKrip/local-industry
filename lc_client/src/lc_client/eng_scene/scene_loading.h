#pragma once

#include <string>

#include <entt/entt.hpp>
#include <pugixml.hpp>


#include "lc_client/util/i_eng_resource.h"


class SceneLoading {
public:
    SceneLoading(entt::registry& sceneRegistry, entt::registry& mapRegistry, eng::IResource* pResource);
	~SceneLoading();

	void loadScene(std::string path);

private:

	void handleComponent(pugi::xml_node component, entt::entity entity);

	entt::registry* m_pSceneRegistry = nullptr;
	entt::registry* m_pMapRegistry = nullptr;
	eng::IResource* m_pResource = nullptr;
};

