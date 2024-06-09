#pragma once

#include <entt/entt.hpp>
#include <string>

#include <glm/glm.hpp>


struct GameCharacter {
	std::string name;

	GameCharacter(std::string name) : name(name) {};
};

struct CurrentTask {
	entt::entity taskEntity;

	CurrentTask(entt::entity taskEntity) : taskEntity(taskEntity) {}
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


	Task() : progress(TaskProgress::PLANNED), name("Unnamed task") {}
	Task(std::string name) : progress(TaskProgress::PLANNED), name(name) {}
};

/**
 * @brief It will be placed automatically if maxExecutors == 1. Used only for convenience.
 */
struct CharacterAssignedTo {
	entt::entity characterEntity;

	CharacterAssignedTo(entt::entity entity) : characterEntity(entity) {}
};

/**
 * @brief isLoner: if true other tasks of character will be removed
 */
struct TaskRequest {
	std::string name;
	unsigned int maxExecutors;
	bool isLoner;

	TaskRequest(std::string name, bool isLoner = false, unsigned int maxExecutors = 1)
		: name(name),
		  maxExecutors(maxExecutors),
		  isLoner(isLoner) {};
};

struct RemoveTaskRequest {

	RemoveTaskRequest() {}
};

struct AssignTaskRequest {
	unsigned int maxExecutors;
	bool isLoner;

	AssignTaskRequest(unsigned int maxExecutors, bool isLoner = false) : maxExecutors(maxExecutors), isLoner(isLoner) {}
};