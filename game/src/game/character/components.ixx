module;

#include <entt/entt.hpp>
#include <string>

#include <glm/glm.hpp>

export module character:components;


export struct GameCharacter {
	std::string name;

	GameCharacter(std::string name) : name(name) {};
};

export struct Walkable {};

export enum class TaskProgress {
	PLANNED,
    QUEUED,
	WAYPOINT,
	COMPLETED
};

export struct Task {
	TaskProgress progress;


	Task() : progress(TaskProgress::PLANNED){
	};
};