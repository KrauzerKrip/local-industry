#pragma once

#include <memory>
#include "lc_client/eng_gui/layout/layouts/layout.h"


struct LayoutData {
	Layout* pLayout;
	glm::vec2 position;
	glm::vec2 size;
	unsigned int layer = 0;

	LayoutData(Layout* pLayout) : pLayout(pLayout), position(glm::vec2(0)), size(glm::vec2(0)){};
};
