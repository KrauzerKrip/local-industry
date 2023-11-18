#pragma once

#include <memory>
#include "lc_client/util/image.h"

class ImageBackground {
public:
	ImageBackground(std::shared_ptr<eng::Image> image);

	std::shared_ptr<eng::Image> getImage();

private:
	std::shared_ptr<eng::Image> m_image;
};
