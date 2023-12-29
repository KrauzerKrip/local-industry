#pragma once

#include <entt/entt.hpp>

#include "lc_client/eng_gui/widgets/widget.h"
#include "lc_client/eng_gui/widgets/dependencies.h"
#include "game/control/action_control.h"
#include "game/machine/blueprint/machine_blueprint_creator.h"
#include "machine_slot.h"
#include "game/machine/machine_loader.h"



class MachineBuildMenu : public Widget {
public:
	MachineBuildMenu(ActionControl* pActionControl, GuiDependencies guiDependecies, entt::registry* pRegistry);
	~MachineBuildMenu();

private:
	MachineSlot* createSlot(MachineType type, std::string typeString);

	MachineBlueprintCreator* m_pMachineBlueprintCreator = nullptr;

	GuiDependencies m_guiDependencies;
};
