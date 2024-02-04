#include "task_list_layout.h"

#include <stdexcept>


TaskListLayout::TaskListLayout(unsigned int taskSlots, GuiDependencies dependencies) {
	m_taskSlots = taskSlots;

    for (unsigned int i = 0; i < taskSlots; i++) {
		TaskView* pTaskView = new TaskView(dependencies);
		m_taskViews.push_back(pTaskView);
		pTaskView->setName("task_view_" + std::to_string(i));
    }
}

void TaskListLayout::updateChildWidgets() {
	processTasks();

	glm::vec2 spacing(2.5, 5);
	float cursorY = m_size.y;

    for (TaskView* pTaskView : m_activeTaskViews) {
		pTaskView->getRectangle().m_size.x = m_size.x - 2 * spacing.x; 
		pTaskView->getRectangle().m_size.y = pTaskView->getSize().y;

		glm::vec2 position = glm::vec2(0);

		cursorY -= pTaskView->getRectangle().m_size.y + spacing.y;

		position.y = cursorY;
		position.x += spacing.x;

		pTaskView->getRectangle().m_absolutePosition += position;

		m_widgets.push_back(pTaskView);
	}

}

void TaskListLayout::setTasks(const std::vector<TaskData>& tasksData) { m_tasksData = tasksData; }

void TaskListLayout::processTasks() {
	m_widgets.clear();
	m_activeTaskViews.clear();

	if (m_tasksData.size() > m_taskSlots) {
		throw std::invalid_argument("tasksData.size() > m_taskSlots");
	}

	for (unsigned int i = 0; i < m_tasksData.size(); i++) {
		TaskData taskData = m_tasksData.at(i);
		TaskView* pTaskView = m_taskViews.at(i);
		pTaskView->setData(taskData);
		m_activeTaskViews.push_back(pTaskView);
	}
}
