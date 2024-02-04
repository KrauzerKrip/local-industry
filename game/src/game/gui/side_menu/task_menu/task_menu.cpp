#include "task_menu.h"

#include "lc_client/eng_gui/includes.h"
#include "task_list.h"


TaskMenu::TaskMenu(entt::registry* pRegistry, GuiDependencies dependencies) : Widget(dependencies) {
	this->setBackground(new ColorBackground(70, 70, 70, 255, dependencies));
	HBox* pHBox = new HBox();
	pHBox->setPadding(5, 5);

	VBox* pCharacterTaskBox = new VBox();
	VBox* pTaskBox = new VBox();
	pTaskBox->setPadding(5, 5);
	pTaskBox->setSpacing(5);

	Widget* pWidget1 = new Widget(new ColorBackground(120, 120, 120, 255, dependencies));
	pWidget1->setSize(50, 50);
	Widget* pWidget2 = new Widget(new ColorBackground(120, 120, 120, 255, dependencies));
	pWidget2->setSize(50, 50);

	pCharacterTaskBox->addChild(pWidget1);
	pTaskBox->addChild(pWidget2);

	Widget* pCharacterTaskBoxWidget = new Widget();
	pCharacterTaskBoxWidget->setBackground(new ColorBackground(120, 120, 120, 255, dependencies));

    TaskList* pTaskList = new TaskList(10, "Tasks", dependencies);

	m_pPlannedTaskListController = new PlannedTaskListController(pRegistry, pTaskList);

	pCharacterTaskBoxWidget->setLayout(pCharacterTaskBox);
	pHBox->addChild(pCharacterTaskBoxWidget);
	pHBox->addChild(pTaskList);

	this->setLayout(pHBox);
}

void TaskMenu::render() {
	m_pPlannedTaskListController->update();
    Widget::render();
}
