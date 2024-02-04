#include "side_menu.h"

#include "lc_client/eng_gui/includes.h"
#include "buttons/task_menu_button.h"


SideMenu::SideMenu(TaskMenu* pTaskMenu, GuiDependencies dependencies) : Widget(new ColorBackground(120, 120, 120, 255, dependencies)) {
	this->setSize(500, 800);
	this->setName("side_menu");

	VBox* pVBox = new VBox();
	pVBox->setMode(BoxMode::STRETCH_SPACING);
	pVBox->setPadding(5, 5);
	TaskMenuButton* pButtonTasks = new TaskMenuButton(pTaskMenu, dependencies);
	Button* pButton2 = new Button(dependencies);
	pButton2->setBackground(new ColorBackground(70, 70, 70, 255, dependencies));
	pButton2->setSize(80, 80);
	pButton2->setName("button_other");
	Button* pButton3 = new Button(dependencies);
	pButton3->setBackground(new ColorBackground(70, 70, 70, 255, dependencies));
	pButton3->setSize(80, 80);
	pButton3->setName("button_other");

    Button* pButton4 = new Button(dependencies);
	pButton4->setBackground(new ColorBackground(70, 70, 70, 255, dependencies));
	pButton4->setSize(80, 80);
	pButton4->setName("button_other");

	pVBox->addChild(pButtonTasks);
	pVBox->addChild(pButton2);
	pVBox->addChild(pButton3);

	this->setLayout(pVBox);
}
