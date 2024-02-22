#include "model_parser.h"

#include <pugixml.hpp>

#include "lc_client/exceptions/io_exceptions.h"


ModelParser::ModelParser(eng::IResource* pResource) { m_pResource = pResource; }

ModelData ModelParser::parse(const std::string& filePath) {
	pugi::xml_document document;
	std::vector<unsigned char> buffer = m_pResource->getFileResource(filePath);
	pugi::xml_parse_result result = document.load_buffer(buffer.data(), buffer.size());

	if (!result) {
		throw XmlException(result.description());
	}

	auto modelXml = document.child("model");

	std::string modelFile = modelXml.child("model_file").text().as_string();
	std::string materialType = modelXml.child("material_type").text().as_string();
	std::string vertexShader = modelXml.child("vertex_shader").text().as_string();
	std::string fragmentShader = modelXml.child("fragment_shader").text().as_string();
	std::string physicsFileStr = modelXml.child("physics_file").text().as_string();

	std::optional<std::string> physicsFile;

	if (!physicsFileStr.empty()) {
		physicsFile = physicsFileStr;
	}

	if (modelFile.empty() || materialType.empty() || vertexShader.empty() || fragmentShader.empty()) {
		throw XmlException("Incorrect model XML: " + filePath);
	}

	return ModelData(modelFile, materialType, vertexShader, fragmentShader, physicsFile);
}
