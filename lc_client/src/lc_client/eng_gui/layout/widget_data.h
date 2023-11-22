#pragma once

#include <memory>
#include "lc_client/eng_gui/widgets/widget.h"


class Widget;

struct WidgetData {
	std::shared_ptr<Widget> widget;
	glm::vec2 position;
	glm::vec2 size;

	WidgetData(std::shared_ptr<Widget> widget) : widget(widget), position(glm::vec2(0)), size(glm::vec2(0)){};
};
