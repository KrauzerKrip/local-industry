#pragma once

#include "lc_client/eng_gui/layout/layouts/frame.h"
#include "lc_client/tier0/tier0.h"
#include "game/gui/dependencies_fabric/gui_dependencies_fabric.h"



class Overlay : public Frame {
public:
	Overlay(Tier0* pTier0, GuiDependenciesFabric* pDependenciesFabric);
};
