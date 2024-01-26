#pragma once

#include "lc_client/eng_gui/widgets/layer.h"
#include "lc_client/eng_gui/widgets/rectangle.h"

class Background {
public:
	virtual ~Background() = default;

	virtual void render(const Rectangle& rectangle, const Layer& layer) = 0;
};
