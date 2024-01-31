#pragma once

#include <vector>
#include <utility>
#include "layout.h"
#include "lc_client/eng_gui/layout/modes.h"


class HBox : public Layout {
public:
	HBox();
	void setPadding(unsigned int x, unsigned int y);
	void setPadding(glm::vec2 padding);
	void updateChildWidgets();
	void setBoxMode(BoxMode mode);

private:
	glm::vec2 m_padding;
	BoxMode m_mode;
};