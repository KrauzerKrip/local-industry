#pragma once

#include "lc_client/eng_gui/widgets/widget.h"
#include "task_list_layout.h"

import character;


class TaskList : public Widget {
public:
    void setTasks(const std::vector<TaskData>& tasksData) {
		// std::cout << "TASKS DATA: " << tasksData.size() << std::endl;
		m_pTaskListLayout->setTasks(tasksData);
	}


protected:
	TaskListLayout* m_pTaskListLayout = nullptr;
};