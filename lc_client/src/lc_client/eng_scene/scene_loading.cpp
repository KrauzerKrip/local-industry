#include "scene_loading.h"

#include <iostream>

#include "lc_client/exceptions/io_exceptions.h"
#include "lc_client/eng_scene/component_creator.h"
#include "lc_client/eng_scene/entt/components.h"
#include "lc_client/eng_model/entt/components.h"
#include "lc_client/eng_graphics/entt/components.h"
#include "lc_client/tier0/tier0.h"


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

	for (pugi::xml_node entityXml : document.child("entities").children("entity")) {
		std::string id = entityXml.attribute("id").as_string();
		std::string uuid = entityXml.attribute("uuid").as_string();

		entt::entity entity = m_pSceneRegistry->create();

		m_pSceneRegistry->emplace<Properties>(entity, id, uuid);

		for (pugi::xml_node component : entityXml.child("components").children()) {
			try {
				handleComponent(component, entity);
			}
			catch (std::runtime_error& exception) {

				std::string text = "SceneLoading: can`t add the component '" + (std::string)component.name() +
								   "' to the entity '" + id + "': \n" + exception.what();

				std::cerr << text << std::endl;

				Tier0::getIConsole()->warn(text);
			}
		}
		for (pugi::xml_node component : entityXml.child("pseudo_components").children()) {}
	}
}

void SceneLoading::handleComponent(pugi::xml_node componentXml, entt::entity entity) {
	std::string componentName = componentXml.name();

	if (componentName == "transform") {
		m_pSceneRegistry->emplace<Transform>(entity, getTransform(componentXml));
	}
	else if (componentName == "model_data") {
		m_pSceneRegistry->emplace<ModelRequest>(entity, getModelData(componentXml));
	}
	else if (componentName == "script") {
		m_pSceneRegistry->emplace<Script>(entity, getScript(componentXml, m_pResource));
		m_pSceneRegistry->emplace<Init>(entity);
	}
	else if (componentName == "trigger") {}
}
