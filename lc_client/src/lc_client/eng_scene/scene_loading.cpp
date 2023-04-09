#include "scene_loading.h"

#include "lc_client/exceptions/io_exceptions.h"


SceneLoading::SceneLoading(entt::registry& sceneRegistry, entt::registry& mapRegistry, eng::IResource* pResource) {
	m_pSceneRegistry = &sceneRegistry;
	m_pMapRegistry = &mapRegistry;
	m_pResource = pResource;
}

SceneLoading::~SceneLoading() {}

void SceneLoading::loadScene(std::string path) {
	pugi::xml_document document;
	std::vector<unsigned char> buffer = m_pResource->getFileResource(path);
	pugi::xml_parse_result result = document.load_buffer(buffer.data(), buffer.size());

	if (!result) {
		throw XmlException(result.description());
	}

	for (pugi::xml_node entity : document.child("entities").children("entity")) {
		std::string id = entity.attribute("id").as_string();
		std::string uuid = entity.attribute("uuid").as_string();

		for (pugi::xml_node component : entity.child("components").children()) {
			handleComponent(component);
		}
		for (pugi::xml_node component : entity.child("pseudo_components").children()) {}
	}
}

void SceneLoading::handleComponent(pugi::xml_node component) {
	if (component.name() == "transform") {}
	else if (component.name() == "model") {}
	else if (component.name() == "script") {}
	else if (component.name() == "trigger") {}
}
