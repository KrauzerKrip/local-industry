#pragma once

#include <entt/entt.hpp>
#include <string>

#include <glm/glm.hpp>


struct GameCharacter {
	std::string name;

	GameCharacter(std::string name) : name(name) {};
};

struct Walkable {};

enum class TaskProgress {
	PLANNED,
    QUEUED,
	WAYPOINT,
	COMPLETED
};

struct Task {
	TaskProgress progress;
	std::string name;


	Task() : progress(TaskProgress::PLANNED), name("Unnamed task") {
	};
};

struct CharacterAssignedTo {
	entt::entity entity;

	CharacterAssignedTo(entt::entity entity) : entity(entity) {}
};