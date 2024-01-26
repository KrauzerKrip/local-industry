#pragma once

#include <memory>
#include "lc_client/util/image.h"
#include "background.h"

class ImageBackground : public Background {
public:
	ImageBackground(std::shared_ptr<eng::Image> image);

	void render(const Rectangle& rectangle, const Layer& layer) override;

private:
	std::shared_ptr<eng::Image> m_image;
};
