#pragma once

#include <string>

#include <entt/entt.hpp>
#include <pugixml.hpp>


#include "lc_client/util/i_eng_resource.h"


class SceneLoading {
public:
    SceneLoading(eng::IResource* pResource);
	~SceneLoading();

	void loadScene(std::string path, entt::registry& sceneRegistry);

private:
	void handleComponent(pugi::xml_node component, entt::entity entity);

	entt::registry* m_pSceneRegistry = nullptr;
	entt::registry* m_pMapRegistry = nullptr;
	eng::IResource* m_pResource = nullptr;
};

