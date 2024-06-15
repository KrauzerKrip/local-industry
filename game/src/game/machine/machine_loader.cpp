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
	else if (componentName == "connections") {
		for (auto& child : componentXml.children()) {
			this->handleConnection(child, entity);
		}
	}
}

void MachineLoader::handleConnection(pugi::xml_node connectionXml, entt::entity entity) {
	std::string connectionName = connectionXml.name();

	Connection connection;
	connection.position = makeVector3(connectionXml.child("position"));
	connection.rotation = makeVector3(connectionXml.child("rotation"));

	if (connectionName == "heat_in") {
		m_pRegistry->get<Connections>(entity).inputs.emplace(ConnectionResourceType::HEAT, connection);
	}
	else if (connectionName == "heat_out") {
		m_pRegistry->get<Connections>(entity).outputs.emplace(ConnectionResourceType::HEAT, connection);
	}
	else if (connectionName == "latex_in") {
		m_pRegistry->get<Connections>(entity).inputs.emplace(ConnectionResourceType::LATEX, connection);
	}
	else if (connectionName == "latex_out") {
		m_pRegistry->get<Connections>(entity).outputs.emplace(ConnectionResourceType::LATEX, connection);
	}

	if (!connectionXml.attribute("attachment").empty() && connectionXml.attribute("attachment").as_bool()) {
		m_pRegistry->emplace<Attachment>(entity, Attachment());
	}
}
