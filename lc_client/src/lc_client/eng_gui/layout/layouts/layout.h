#pragma once

#include <vector>
#include <memory>
#include "lc_client/eng_gui/widgets/widget.h"
#include "lc_client/eng_gui/layout/widget_data.h"

class Widget;

class Layout {
public:
	virtual ~Layout(){};

	virtual std::vector<std::shared_ptr<Widget>> getChildrenWidgets();
	virtual void addChild(std::shared_ptr<Widget> widget);
	virtual void updateChildWidgets() = 0;

	glm::vec2 m_position;
	glm::vec2 m_size;

protected:
	std::vector<std::shared_ptr<Widget>> m_widgets;
};
