#include "machine_build_menu.h"

#include "lc_client/eng_gui/layout/layouts/grid.h"
 
#include "lc_client/eng_gui/widgets/text_widget.h"
#include "lc_client/eng_gui/widgets/button.h"
#include "game/machine/machine_type.h"


MachineBuildMenu::MachineBuildMenu(ActionControl* pActionControl, GuiDependencies guiDependecies, entt::registry* pRegistry)
	: Widget(guiDependecies.widgetDependencies),
	  m_guiDependencies(guiDependecies) {

	m_pMachineBlueprintCreator = new MachineBlueprintCreator(pRegistry);

	this->setPosition(glm::vec2(100, 100));
	this->setSize(glm::vec2(1500, 800));

	pActionControl->addActionCallback("kb_machine_menu", [this]() {
		if (this->isVisible()) {
			this->hideWithChildren();
		}
		else {
			this->showWithChildren();
		}
	});

	this->setBackground(Background(glm::vec4(0, 0, 0, 0.5)));


	Grid* pGrid = new Grid(9, 25, 100);

	pGrid->addChild(createSlot(MachineType::HEATER, "heater"));

	this->setLayout(pGrid);
}

MachineBuildMenu::~MachineBuildMenu() { delete m_pMachineBlueprintCreator; }

MachineSlot* MachineBuildMenu::createSlot(MachineType type, std::string typeString) { 
	MachineSlot* pMachineSlot = new MachineSlot(type, typeString, m_guiDependencies, m_pMachineBlueprintCreator);
	pMachineSlot->setCallback([this]() { this->hideWithChildren(); });
	return pMachineSlot;
}
