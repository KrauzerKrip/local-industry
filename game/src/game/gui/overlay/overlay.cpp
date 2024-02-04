#include "overlay.h"

#include <memory>

#include "lc_client/eng_debug/gui/debug_widget.h"
#include "lc_client/eng_gui/paint_objects/image_background.h"


Overlay::Overlay(Tier0* pTier0, GuiDependenciesFabric* pDependenciesFabric, IInput* pInput) {
	GuiDependencies widgetDependencies = pDependenciesFabric->getDependencies();

	DebugWidget* debugWidget = new DebugWidget(pTier0, pInput, widgetDependencies);
	this->addChild(debugWidget);
}
 