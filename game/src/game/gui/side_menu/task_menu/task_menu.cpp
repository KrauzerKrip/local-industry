#include "task_menu.h"

#include "lc_client/eng_gui/includes.h"
#include "planned/planned_task_list.h"
#include "character/character_task_list.h"



TaskMenu::TaskMenu(entt::registry* pRegistry, GuiDependencies dependencies) : Widget(dependencies) {
	m_pRegistry = pRegistry;

	BlurBackground* pBaseBackground = new BlurBackground(dependencies.pStyle->getColor("blur_background_base"),
		dependencies.pStyle->getBlurIntensity("base"), dependencies);
	BlurBackground* pDarkBackground = new BlurBackground(dependencies.pStyle->getColor("blur_background_dark"),
		dependencies.pStyle->getBlurIntensity("base"), dependencies);

	this->setBackground(pDarkBackground);
	HBox* pHBox = new HBox();
	pHBox->setPadding(5, 5);
	pHBox->setSpacing(5);

	VBox* pCharacterTaskBox = new VBox();
	pCharacterTaskBox->setMode(BoxMode::STRETCH_WIDGETS);
	Widget* pCharacterTaskBoxWidget = new Widget();
	pCharacterTaskBoxWidget->setBackground(pBaseBackground);
	pCharacterTaskBoxWidget->setLayout(pCharacterTaskBox);

    TaskList* pTaskList = new PlannedTaskList("Tasks", dependencies);
	m_pEmmyTaskList = new CharacterTaskList("1", dependencies);
	m_pMaryTaskList = new CharacterTaskList("2", dependencies);
	m_pErikaTaskList = new CharacterTaskList("3", dependencies);
	m_pShoshanaTaskList = new CharacterTaskList("4", dependencies);

	pCharacterTaskBox->addChild(m_pEmmyTaskList);
	pCharacterTaskBox->addChild(m_pMaryTaskList);
	pCharacterTaskBox->addChild(m_pErikaTaskList);
	pCharacterTaskBox->addChild(m_pShoshanaTaskList);

	m_pPlannedTaskListController = new PlannedTaskListController(pRegistry, pTaskList);

	pHBox->addChild(pCharacterTaskBoxWidget);
	pHBox->addChild(pTaskList);

	this->setLayout(pHBox);
}

void TaskMenu::render() {
	m_pPlannedTaskListController->update();
	if (m_pCharacterTaskListController) {
		m_pCharacterTaskListController->update();
	} else {
		for (auto&& [entity, character, taskQueue] : m_pRegistry->view<GameCharacter, TaskQueue>().each()) {
			if (character.name == "emmy") {
				m_pCharacterTaskListController =
					new CharacterTaskListController(&taskQueue, m_pRegistry, m_pEmmyTaskList);
			}
		}

	}
    Widget::render();
}
