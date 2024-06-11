#pragma once

#include <entt/entt.hpp>
#include <string>

#include <glm/glm.hpp>


struct GameCharacter {
	std::string name;
	float workSpeed = 10.0;

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
	int requiredWork;
	double workDone = 0;
	double deltaWork = 0;

	Task() : progress(TaskProgress::PLANNED), name("Unnamed task"), requiredWork(1) {}
	Task(std::string name) : progress(TaskProgress::PLANNED), name(name), requiredWork(1) {}
	Task(std::string name, int requiredWork) : progress(TaskProgress::PLANNED), name(name), requiredWork(requiredWork) {}
};

/**
 * @brief It will be placed automatically if maxExecutors == 1. Used only for convenience.
 */
struct CharacterAssignedTo {
	entt::entity characterEntity;

	CharacterAssignedTo(entt::entity entity) : characterEntity(entity) {}
};

struct TaskRequest {
	std::string name;
	unsigned int maxExecutors;
	bool isLoner;
	int requiredWork;

	TaskRequest(std::string name, int requiredWork = 1, unsigned int maxExecutors = 1)
		: name(name),
		  maxExecutors(maxExecutors),
		  isLoner(isLoner), 
		requiredWork(requiredWork)
	{};
};

/**
 * @brief isLoner: if present other tasks of character will be removed
 */
struct LonerTask {

};

struct RemoveTaskRequest {

	RemoveTaskRequest() {}
};

struct AssignTaskRequest {
	unsigned int maxExecutors;
	bool isLoner;

	AssignTaskRequest(unsigned int maxExecutors, bool isLoner = false) : maxExecutors(maxExecutors), isLoner(isLoner) {}
};