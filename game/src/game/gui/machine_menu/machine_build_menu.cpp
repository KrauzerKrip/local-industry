#include "machine_build_menu.h"

#include "lc_client/eng_gui/layout/layouts/grid.h"
 
#include "lc_client/eng_gui/widgets/text_widget.h"
#include "lc_client/eng_gui/widgets/button.h"
#include "game/machine/machine_type.h"
#include "lc_client/eng_gui/paint_objects/color_background.h"
#include "lc_client/eng_gui/includes.h"
#include "machine_category.h"
#include "machine_category_button.h"



MachineBuildMenu::MachineBuildMenu(
	ActionControl* pActionControl, Layout* pGuiLayout, GuiDependencies guiDependecies, entt::registry* pRegistry)
	: Widget(guiDependecies),
	  m_guiDependencies(guiDependecies) {

	m_pMachineBlueprintCreator = new MachineBlueprintCreator(pRegistry);

	float width = 1920;
	float height = 80;

	this->setPosition(glm::vec2(0, 0));
	this->setSize(glm::vec2(width, height));

	BlurBackground* pBackground = new BlurBackground(guiDependecies.pStyle->getColor("blur_background_base"),
		guiDependecies.pStyle->getBlurIntensity("base"), m_guiDependencies);
	this->setBackground(pBackground);

	HBox* pHBox = new HBox();
	pHBox->setBoxMode(BoxMode::STRETCH_SPACING);
	pHBox->setPadding(0, 8);
	this->setLayout(pHBox);

	Widget* pCharactersWidget = new Widget();
	pCharactersWidget->setSize(width / 4.0f, height);
	pHBox->addChild(pCharactersWidget);
	Widget* pCategoriesWidget = new Widget();
	pCategoriesWidget->setSize((width / 4.0f) * 2, height);
	pHBox->addChild(pCategoriesWidget);
	Widget* pActionsWidget = new Widget();
	pActionsWidget->setSize(width / 4.0f, height);
	pHBox->addChild(pActionsWidget);

	HBox* pCategoriexHBox = new HBox();
	pCategoriexHBox->setBoxMode(BoxMode::STRETCH_SPACING);
	pCategoriesWidget->setLayout(pCategoriexHBox);
	
	MachineCategory* pMachineCategory = new MachineCategory(guiDependecies);

	std::vector<MachineSlot*> machineSlots{
		createSlot(MachineType::HEATER, "heater"), createSlot(MachineType::BOILER, "boiler")
	};

	pMachineCategory->setSlots(machineSlots);
	pGuiLayout->addChild(pMachineCategory);

	MachineCategoryButton* pButtonThermo = new MachineCategoryButton("Thermodynamics", "gmod_vibes/", guiDependecies, pMachineCategory);
	pCategoriexHBox->addChild(pButtonThermo);
		
	this->showWithChildren();
	//Grid* pGrid = new Grid(9, 25, 100);

	//pGrid->addChild(createSlot(MachineType::HEATER, "heater"));
	//pGrid->addChild(createSlot(MachineType::BOILER, "boiler"));

	//this->setLayout(pGrid);
}

MachineBuildMenu::~MachineBuildMenu() { delete m_pMachineBlueprintCreator; }

MachineSlot* MachineBuildMenu::createSlot(MachineType type, std::string typeString) { 
	MachineSlot* pMachineSlot = new MachineSlot(type, typeString, m_guiDependencies, m_pMachineBlueprintCreator);
	return pMachineSlot;
}