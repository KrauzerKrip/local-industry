#pragma once

#include <optional>

#include <entt/entt.hpp>
#include <glm/glm.hpp>

#include "lc_client/eng_scene/entt/components.h"
#include "machine_type.h"


enum class BlueprintState {

};


struct Machine {};

struct MachineRequest {
	MachineType type;
	std::string typeString;

	MachineRequest(MachineType type, std::string typeString) : type(type), typeString(typeString){}
};

struct BlueprintRequest {
	MachineType type;
	std::string typeString;

	BlueprintRequest(MachineType type, std::string typeString) : type(type), typeString(typeString) {}
};

struct MachineInit {};

struct Blueprint {

};

struct BlueprintItem {
	MachineType type;
	std::string typeString;

	BlueprintItem(MachineType type, std::string typeString) : type(type), typeString(typeString) {}
};

struct BlueprintAcquired {

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

struct Connectable {

};

struct ConnectionRequest {
    entt::entity entity;
	ConnectionResourceType resourceType = ConnectionResourceType::NONE;
	ConnectionType type = ConnectionType::NONE;

	explicit ConnectionRequest(entt::entity entity) : entity(entity) {}
};

struct MachineMode {
	bool toggle;

	MachineMode() { toggle = false; }
};

struct MachineProperties {
	MachineType type;
	std::string typeString;

	MachineProperties(MachineType type, std::string typeString) : type(type), typeString(typeString) {}
};

struct Connection {
	glm::vec3 position;
	glm::vec3 rotation;
	std::optional<entt::entity> entity = std::nullopt;
	float resource = 0;
};

struct Connections {
	std::unordered_map<ConnectionResourceType, Connection> inputs;
	std::unordered_map<ConnectionResourceType, Connection> outputs;
};

struct CombustionFuelStorage {
	std::optional<entt::entity> fuel;
	float mass;

	CombustionFuelStorage() : fuel(std::nullopt), mass(0) {}
	CombustionFuelStorage(entt::entity fuel, float mass) : fuel(fuel), mass(mass) {}
};

