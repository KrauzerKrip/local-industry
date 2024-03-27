#pragma once

#include <string>
#include <vector>
#include <tuple>

#include "game/machine/machine_type.h"
#include "machine_slot.h"
#include "lc_client/eng_gui/includes.h"
#include "machine_category.h"


class MachineCategoryButton : public Button {
public:
	MachineCategoryButton(std::string label, std::string iconPath, const GuiDependencies& dependencies, MachineCategory* pMachineCategory);
	void click() override;

private:
	MachineCategory* m_pMachineCategory = nullptr;
};