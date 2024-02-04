#pragma once

#include "lc_client/eng_gui/widgets/dependencies.h"
#include "lc_client/eng_gui/widgets/button.h"
#include "game/gui/side_menu/task_menu/task_menu.h"


class TaskMenuButton : public Button {
public:
	explicit TaskMenuButton(TaskMenu* pTaskMenum, GuiDependencies dependencies);

    void click() override;

private:
	TaskMenu* m_pTaskMenu = nullptr;
};