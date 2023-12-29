#include "machine_slot.h"

MachineSlot::MachineSlot(MachineType type, std::string typeString, GuiDependencies pGuiDependencies,
	MachineBlueprintCreator* pMachineBlueprintCreator)
	: Button(pGuiDependencies.textWidgetDependencies), m_type(type), m_typeString(typeString) {
	m_pMachineBlueprintCreator = pMachineBlueprintCreator;

	pGuiDependencies.pInputController->addReceiver(this);

	this->setSize(glm::vec2(100, 100));
	this->setText(typeString);
	this->setColor(glm::vec4(1, 1, 1, 1));
	this->setTextSize(24);
	this->setBackground(Background(glm::vec4(0, 0, 0, 0.7)));
}

void MachineSlot::click() { 
	m_pMachineBlueprintCreator->createMachineBlueprint(m_type, m_typeString);
	if (m_callback) {
		m_callback();
	}
}

void MachineSlot::setCallback(std::function<void()> callback) { m_callback = callback; }
