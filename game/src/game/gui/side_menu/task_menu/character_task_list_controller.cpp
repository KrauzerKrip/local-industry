#include "character_task_list_controller.h"

#include <entt/entt.hpp>

#include "task_view.h"


CharacterTaskListController::CharacterTaskListController(TaskQueue* pTaskQueue, entt::registry* pRegistry, TaskList* pTaskList) {
	m_pTaskQueue = pTaskQueue;
	m_pRegistry = pRegistry;
	m_pTaskList = pTaskList;
}

void CharacterTaskListController::update() {
	std::vector<TaskData> taskViews;

	m_pTaskQueue->forEach([this, &taskViews](entt::entity entity) {
	    if (m_pRegistry->all_of<Task>(entity)) {
			Task& task = m_pRegistry->get<Task>(entity);
			TaskData taskView({task.name, task.progress});
			taskViews.push_back(taskView);
	    }
	});

	m_pTaskList->setTasks(std::move(taskViews));
}
