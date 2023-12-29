#pragma once

#include <string>

#include "lc_client/eng_gui/widgets/button.h"
#include "game/machine/machine_type.h"
#include "game/machine/blueprint/machine_blueprint_creator.h"
#include "functional"


class MachineSlot : public Button {
public:
	MachineSlot(MachineType type, std::string typeString, GuiDependencies guiDependencies, MachineBlueprintCreator* pMachineBlueprintCreator);

	void click();
	void setCallback(std::function<void()> callback);

private:
	MachineType m_type;
	std::string m_typeString;
	std::function<void()> m_callback;

	MachineBlueprintCreator* m_pMachineBlueprintCreator = nullptr;
};
