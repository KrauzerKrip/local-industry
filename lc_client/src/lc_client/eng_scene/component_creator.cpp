#include "component_creator.h"

Transform getTransform(pugi::xml_node node) {

	const glm::vec3 position = makeVector3(node.child("position"));
	const glm::vec3 rotation = makeVector3(node.child("rotation"));
	const glm::vec3 scale = makeVector3(node.child("scale"));

	return Transform(position, rotation, scale);
}

ModelData getModelData(pugi::xml_node node) {
	const std::string packName = node.child("pack").text().as_string();
	const std::string modelName = node.child("model").text().as_string();

	return ModelData(packName, modelName);
}

glm::vec3 makeVector3(pugi::xml_node node) {
	const float x = node.attribute("x").as_float();
	const float y = node.attribute("y").as_float();
	const float z = node.attribute("z").as_float();

	return glm::vec3(x, y, z);
}


using namespace pseudo;

Object::Object(pugi::xml_node objectNode) {}
