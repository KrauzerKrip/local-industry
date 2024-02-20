#pragma once

#include <optional>

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

struct MachineInit {};

struct Blueprint {

};

/**
 * @brief Workaround for selection on creation of blueprint.
*/
struct BlueprintInit {

};

struct Built {
    
};

struct Attachment {
    
};

struct ConnectionRequest {
    entt::entity entity;
	ConnectionType type;

	explicit ConnectionRequest(entt::entity entity) : entity(entity),  type(ConnectionType::NONE) {}
};

struct CharacterAssignedTo {
	entt::entity entity;

	CharacterAssignedTo(entt::entity entity) : entity(entity){};
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
	glm::vec3 rotation;
	std::optional<entt::entity> entity;
	float heat = 0;

	HeatOut() : entity(std::nullopt) {}
};

struct CombustionFuelStorage {
	std::optional<entt::entity> fuel;
	float mass;

	CombustionFuelStorage() : fuel(std::nullopt), mass(0) {}
	CombustionFuelStorage(entt::entity fuel, float mass) : fuel(fuel), mass(mass) {}
};

