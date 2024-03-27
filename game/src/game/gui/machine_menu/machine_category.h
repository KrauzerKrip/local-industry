	 #pragma once

#include "machine_slot.h"
#include "lc_client/eng_gui/includes.h"


class MachineCategory : public Widget {
public:
	MachineCategory(const GuiDependencies& dependencies);
	void setSlots(const std::vector<MachineSlot*>& machineSlots);

private:
	const static unsigned int SLOTS_IN_ROW;
	const static float PADDING;

	Grid* m_pGrid = nullptr;
};