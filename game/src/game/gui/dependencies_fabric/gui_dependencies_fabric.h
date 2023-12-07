#pragma once

#include "lc_client/eng_gui/widgets/dependencies.h"


class GuiDependenciesFabric {
public:
	virtual ~GuiDependenciesFabric(){};

	virtual WidgetDependecies getWidgetDependencies() = 0;
	virtual TextWidgetDependecies getTextWidgetDependecies() = 0;
};