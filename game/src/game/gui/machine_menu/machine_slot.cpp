#include "machine_slot.h"

#include "lc_client/eng_gui/paint_objects/color_background.h"

MachineSlot::MachineSlot(MachineType type, std::string typeString, GuiDependencies guiDependencies,
	MachineBlueprintCreator* pMachineBlueprintCreator)
	: Button(guiDependencies), m_type(type), m_typeString(typeString) {
	m_pMachineBlueprintCreator = pMachineBlueprintCreator;

	this->setSize(glm::vec2(100, 100));
	this->setText(typeString);
	this->setTextColor(glm::vec4(1, 1, 1, 1));
	this->setTextSize(24);
	ColorBackground* colorBackground = new ColorBackground(glm::vec4(0, 0, 0, 0.7), guiDependencies);
	this->setBackground(colorBackground);
}

void MachineSlot::click() { 
	m_pMachineBlueprintCreator->createMachineBlueprint(m_type, m_typeString);
	if (m_callback) {
		m_callback();
	}
}

void MachineSlot::setCallback(std::function<void()> callback) { m_callback = callback; }
