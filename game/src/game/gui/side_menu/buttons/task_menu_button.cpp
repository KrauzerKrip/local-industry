#include "task_menu_button.h"

#include "lc_client/eng_gui/paint_objects/image_background.h"


TaskMenuButton::TaskMenuButton(TaskMenu* pTaskMenu, GuiDependencies dependencies) : Button(dependencies) {
	m_pTaskMenu = pTaskMenu;

	this->setBackground(new ImageBackground("game/gui/icons/side_menu_task_button", dependencies));
	this->setSize(70, 70);
	this->setName("task_menu_button");
}

void TaskMenuButton::click() { m_pTaskMenu->toggleWithChildren(); }
