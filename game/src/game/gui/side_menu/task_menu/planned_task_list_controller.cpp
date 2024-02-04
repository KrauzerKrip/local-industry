#include "planned_task_list_controller.h"

#include "game/machine/components.h"


PlannedTaskListController::PlannedTaskListController(entt::registry* pRegistry, TaskList* pTaskList) {
    m_pRegistry = pRegistry;
	m_pTaskList = pTaskList;
} 

void PlannedTaskListController::update() {
	auto tasks = m_pRegistry->view<Task>();

    std::vector<TaskData> tasksData;

    for (auto&& [entity, task] : tasks.each()) {
        if (task.progress == TaskProgress::PLANNED) {
            TaskData taskData;
			taskData.name = "Build " + task.name; 
			taskData.progress = task.progress; 
            tasksData.push_back(taskData);
        }
    }

    m_pTaskList->setTasks(tasksData);
}
