#pragma once

#include "lc_client/eng_gui/layout/layouts/layout.h"
#include "task_view.h"

import character;


class TaskListLayout : public Layout {
public:
	TaskListLayout(unsigned int taskSlots, GuiDependencies dependencies);
	void updateChildWidgets() override;
	void setTasks(const std::vector<TaskData>& tasksData);

private:
	void processTasks();

	unsigned int m_taskSlots;

	std::vector<TaskView*> m_activeTaskViews;
	std::vector<TaskView*> m_taskViews;
	std::vector<TaskData> m_tasksData;
};