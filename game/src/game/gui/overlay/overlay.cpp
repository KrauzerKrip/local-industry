#include "overlay.h"

#include <memory>

#include "lc_client/eng_debug/gui/debug_widget.h"


Overlay::Overlay(Tier0* pTier0, GuiDependenciesFabric* pDependenciesFabric, IInput* pInput) {
	WidgetDependecies widgetDependencies = pDependenciesFabric->getWidgetDependencies();
	TextWidgetDependecies textWidgetDependecies = pDependenciesFabric->getTextWidgetDependecies();

	std::shared_ptr<DebugWidget> debugWidget = std::make_shared<DebugWidget>(pTier0, pInput, widgetDependencies, textWidgetDependecies);
	this->addChild(debugWidget);

	debugWidget->show();
}
 