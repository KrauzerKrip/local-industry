#include "component_creator.h"

Transform getTransform(pugi::xml_node node) {

	glm::vec3 position = makeVector3(node.child("position"));
	glm::vec3 rotation = makeVector3(node.child("rotation"));
	glm::vec3 scale = makeVector3(node.child("scale"));
	
	return Transform(position, rotation, scale);
}

ModelData getModelData(pugi::xml_node node) { return ModelData(); }

glm::vec3 makeVector3(pugi::xml_node node) {
	float x = node.attribute("x").as_float();
	float y = node.attribute("y").as_float();
	float z = node.attribute("z").as_float();

	return glm::vec3(x, y, z);
}


using namespace pseudo;

Object::Object(pugi::xml_node objectNode) {
	
}

