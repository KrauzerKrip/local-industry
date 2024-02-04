#pragma once

#include <string>

#include <entt/entt.hpp>

#include "task_list_controller.h"
#include "task_list_layout.h"
#include "lc_client/eng_gui/widgets/dependencies.h"
#include "lc_client/eng_gui/widgets/widget.h"
#include "task_view.h"

import character;


class TaskList : public Widget {
public:
	TaskList(unsigned int taskSlots, std::string label, GuiDependencies dependencies);

	void setTasks(const std::vector<TaskData>& tasksData);

private:
	TaskListLayout* m_pTaskListLayout = nullptr;
};