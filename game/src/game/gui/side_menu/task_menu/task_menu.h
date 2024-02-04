#pragma once

#include <entt/entt.hpp>

#include "planned_task_list_controller.h"
#include "lc_client/eng_gui/widgets/widget.h"
#include "task_list_controller.h"


class TaskMenu : public Widget {
public:
	explicit TaskMenu(entt::registry* pRegistry, GuiDependencies dependencies);

	void render() override;

private:
	PlannedTaskListController* m_pPlannedTaskListController = nullptr;
};