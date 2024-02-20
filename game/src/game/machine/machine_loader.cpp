#include "machine_loader.h"

#include "lc_client/exceptions/io_exceptions.h"

#include "lc_client/eng_scene/component_creator.h"
#include "components.h"


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
		Transform relativeTransform = getTransform(componentXml);
		m_pRegistry->emplace<RelativeTransform>(entity, relativeTransform);
		Transform transform;
		transform.rotation = relativeTransform.rotation;
		transform.scale = relativeTransform.scale;
		m_pRegistry->emplace<Transform>(entity, transform);
	}
	else if (componentName == "model_data") {
		ModelRequest modelRequest = getModelData(componentXml);
		modelRequest.loadShaders = false;
		m_pRegistry->emplace<ModelRequest>(entity, modelRequest);
	}
	else if (componentName == "heat_out") {
		HeatOut heatOut;
		heatOut.position = makeVector3(componentXml.child("position"));
		heatOut.rotation = makeVector3(componentXml.child("rotation"));
		m_pRegistry->emplace<HeatOut>(entity, heatOut);
	}
	else if (componentName == "heat_in") {
		HeatIn heatIn;
		heatIn.position = makeVector3(componentXml.child("position"));
		m_pRegistry->emplace<HeatIn>(entity, heatIn);
	}
}