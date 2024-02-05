#pragma once

#include <entt/entt.hpp>

#include "../task_list_controller.h"
#include "../task_list.h"


import character;


class CharacterTaskListController : public TaskListController {
public:
	CharacterTaskListController(TaskQueue* pTaskQueue, entt::registry* pRegistry, TaskList* pTaskList);

	void update() override;

private:
	TaskQueue* m_pTaskQueue = nullptr;
	entt::registry* m_pRegistry = nullptr;
	TaskList* m_pTaskList = nullptr;
};