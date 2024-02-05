#pragma once

#include <entt/entt.hpp>

#include "planned/planned_task_list_controller.h"
#include "character/character_task_list_controller.h"
#include "lc_client/eng_gui/widgets/widget.h"
#include "task_list_controller.h"


class TaskMenu : public Widget {
public:
	explicit TaskMenu(entt::registry* pRegistry, GuiDependencies dependencies);

	void render() override;

private:
	entt::registry* m_pRegistry = nullptr;

	PlannedTaskListController* m_pPlannedTaskListController = nullptr;
	CharacterTaskListController* m_pCharacterTaskListController = nullptr;

	TaskList* m_pEmmyTaskList = nullptr;
	TaskList* m_pMaryTaskList = nullptr;
	TaskList* m_pErikaTaskList = nullptr;
	TaskList* m_pShoshanaTaskList = nullptr;
};