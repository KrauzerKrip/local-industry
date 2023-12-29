#include "machine_loader.h"

#include "lc_client/exceptions/io_exceptions.h"

#include "lc_client/eng_scene/component_creator.h"


MachineLoader::MachineLoader(eng::IResource* pResource, entt::registry* pRegistry) { 
	m_pResource = pResource;
	m_pRegistry = pRegistry;
}

void MachineLoader::loadMachine(entt::entity entity, std::string typeString) {
	pugi::xml_document document;
	std::vector<unsigned char> buffer = m_pResource->getFileResource(m_machinesPath + typeString + ".xml");
	pugi::xml_parse_result result = document.load_buffer(buffer.data(), buffer.size());

	if (!result) {
		throw XmlException(result.description());
	}

	for (pugi::xml_node componentXml : document.child("machine").child("components").children()) {
		try {
			handleComponent(componentXml, entity);
		}
		catch (std::runtime_error& exception) {

			std::string text = "MachineLoader: can`t add the component '" + (std::string)componentXml.name() + exception.what();

			std::cerr << text << std::endl;

			// Tier0::getIConsole()->warn(text);
		}
	}
}

void MachineLoader::handleComponent(pugi::xml_node componentXml, entt::entity entity) {
	std::string componentName = componentXml.name();

	if (componentName == "transform") {
		m_pRegistry->emplace<Transform>(entity, getTransform(componentXml));
	}
	else if (componentName == "model_data") {
		m_pRegistry->emplace<ModelRequest>(entity, getModelData(componentXml));
	}
}