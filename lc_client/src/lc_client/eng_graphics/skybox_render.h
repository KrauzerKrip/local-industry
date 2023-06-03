#pragma once

#include "lc_client/util/image.h"

struct SkyboxMaterial {
	eng::Image right;
	eng::Image left;
	eng::Image top;
	eng::Image bottom;
	eng::Image back;
	eng::Image front;
};

class SkyboxRender {
public:
	virtual void render() = 0;
};
