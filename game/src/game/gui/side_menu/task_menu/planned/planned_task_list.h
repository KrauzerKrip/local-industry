#pragma once

#include <string>

#include <entt/entt.hpp>

#include "../task_list.h"
#include "../task_list_controller.h"
#include "../task_list_layout.h"
#include "lc_client/eng_gui/widgets/dependencies.h"
#include "lc_client/eng_gui/widgets/widget.h"
#include "../task_view.h"


class PlannedTaskList : public TaskList {
public:
	PlannedTaskList(std::string label, GuiDependencies dependencies);
};