#pragma once

#include "layout.h"


struct PercentageWidget {
	Widget* pWidget = nullptr;
	glm::vec2 percentagePosition;
	glm::vec2 percentageSize;

	PercentageWidget(Widget* pWidget, glm::vec2 percentagePosition, glm::vec2 percentageSize)
		: pWidget(pWidget),
		  percentagePosition(percentagePosition),
		  percentageSize(percentageSize) {}
};


class PercentagePane : public Layout {
public:
	auto addWidget(Widget* pWidget, glm::vec2 percentagePosition, glm::vec2 percentageSize) -> void;
	void updateChildWidgets() override;

private:
	std::vector<PercentageWidget> m_percentageWidgets;
};