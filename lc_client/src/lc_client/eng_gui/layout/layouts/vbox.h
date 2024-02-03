#pragma once

#include <vector>
#include "layout.h"
#include "lc_client/eng_gui/layout/modes.h"


class VBox : public Layout {
public:
	VBox();
	void setPadding(unsigned int x, unsigned int y);
	void setPadding(glm::vec2 padding);
	void setSpacing(unsigned int spacing);
	void updateChildWidgets();
	void setMode(BoxMode mode);

private:
	glm::vec2 m_padding;
	unsigned int m_spacing;
	BoxMode m_mode;
};