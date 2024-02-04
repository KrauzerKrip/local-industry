#pragma once

#include <entt/entt.hpp>

#include "task_list_controller.h"
#include "task_list.h"


class PlannedTaskListController : public TaskListController {
public:
	PlannedTaskListController(entt::registry* pRegistry, TaskList* pTaskList);

	void update() override;

private:
	entt::registry* m_pRegistry = nullptr;
	TaskList* m_pTaskList = nullptr;
};