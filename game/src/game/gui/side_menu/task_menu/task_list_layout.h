#pragma once

#include "lc_client/eng_gui/layout/layouts/layout.h"
#include "task_view.h"

#include "game/character/task_queue.h"


class TaskListLayout : public Layout {
public:
	TaskListLayout(unsigned int taskSlots, GuiDependencies dependencies);
	void updateChildWidgets() override;
	void setTasks(const std::vector<TaskData>& tasksData);
	void hide() override;
	void show() override;
	std::vector<Widget*>& getChildrenWidgets() override;

private:
	unsigned int m_taskSlots;

	std::vector<TaskView*> m_activeTaskViews;
	std::vector<TaskView*> m_taskViews;
	std::vector<TaskData> m_tasksData;
};