#include "physics_parser.h"

#include "lc_client/exceptions/io_exceptions.h"
#include "lc_client/eng_scene/component_creator.h"



PhysicsParser::PhysicsParser(eng::IResource* pResource) { m_pResource = pResource; }

std::vector<ColliderData> PhysicsParser::parse(std::string filePath) {
	pugi::xml_document document;
	std::vector<unsigned char> buffer = m_pResource->getFileResource(filePath);
	pugi::xml_parse_result result = document.load_buffer(buffer.data(), buffer.size());

	if (!result) {
		throw XmlException(result.description());
	}

	std::vector<ColliderData> collidersData;

	for (pugi::xml_node colliderXml : document.child("physics").children()) {
		collidersData.push_back(parseCollider(colliderXml));
	}

	return collidersData;
}

ColliderData PhysicsParser::parseCollider(const pugi::xml_node& colliderNode) {
	ColliderData data;
	std::string type = colliderNode.name();
	if (type == "box_collider") {
		data.type = ColliderType::BOX;
	}
	data.transform = getTransform(colliderNode);
	return data;
}
