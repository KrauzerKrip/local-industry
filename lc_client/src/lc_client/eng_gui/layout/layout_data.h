#pragma once

#include <memory>
#include "lc_client/eng_gui/layout/layouts/layout.h"


struct LayoutData {
	std::shared_ptr<Layout> layout;
	glm::vec2 position;
	glm::vec2 size;
	unsigned int layer = 0;

	LayoutData(std::shared_ptr<Layout> layout) : layout(layout), position(glm::vec2(0)), size(glm::vec2(0)){};
};
