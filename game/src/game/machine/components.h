#pragma once

#include <entt/entt.hpp>
#include <glm/glm.hpp>

#include "lc_client/eng_scene/entt/components.h"
#include "machine_type.h"


struct Machine {

};

struct MachineRequest {
	MachineType type;
	std::string typeString;

	MachineRequest(MachineType type, std::string typeString) : type(type), typeString(typeString){}
};

struct Blueprint {

};

/**
 * @brief Workaround for selection of blueprint just after creation.
*/
struct BlueprintInit {

};

struct RelativeTransform {
	Transform transform;

	RelativeTransform() : transform(Transform()){};
	RelativeTransform(Transform transform) : transform(transform){};
};

struct HeatIn {
	glm::vec3 position;
	float heat = 0;

	HeatIn() {} 
};

struct HeatOut {
	glm::vec3 position;
	entt::entity entity;
	float heat = 0;

	HeatOut(entt::entity entity) : entity(entity) {}
};


