#pragma once

#include "lc_client/eng_gui/widgets/dependencies.h"


class GuiDependenciesFabric {
public:
	virtual ~GuiDependenciesFabric(){};

	virtual GuiDependencies getDependencies() = 0;
};