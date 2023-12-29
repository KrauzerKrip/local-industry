#pragma once

#include <entt/entt.hpp>
#include <glm/glm.hpp>

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


