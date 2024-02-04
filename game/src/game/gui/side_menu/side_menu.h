#pragma once

#include "lc_client/eng_gui/widgets/dependencies.h"
#include "lc_client/eng_gui/widgets/widget.h"
#include "task_menu/task_menu.h"


class SideMenu : public Widget {
public:
	explicit SideMenu(TaskMenu* pTaskMenu, GuiDependencies dependencies);
};
