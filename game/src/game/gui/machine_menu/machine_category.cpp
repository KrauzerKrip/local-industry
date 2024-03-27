#include "machine_category.h"

const unsigned int MachineCategory::SLOTS_IN_ROW = 5;
const float MachineCategory::PADDING = 8;


MachineCategory::MachineCategory(const GuiDependencies& dependencies) {
	m_pGrid = new Grid(5, 8, 100);
	ColorBackground* pColorBackground = new ColorBackground(120, 120, 120, 120, dependencies);
	this->setBackground(pColorBackground);
	this->setLayout(m_pGrid);
}

void MachineCategory::setSlots(const std::vector<MachineSlot*>& machineSlots) {
	int rowNumber = std::ceil(machineSlots.size() / 5.0f);

	float rowHeight = 100;
	this->setSize(512, PADDING * (rowNumber + 1) + rowNumber * rowHeight);

	for (MachineSlot* pMachineSlot : machineSlots) {
		pMachineSlot->setCallback([this]() { this->hideWithChildren(); });
		m_pGrid->addChild(pMachineSlot);
	}
}
