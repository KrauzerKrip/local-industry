#include "image_background.h"

ImageBackground::ImageBackground(std::shared_ptr<eng::Image> image) { m_image = image; }

std::shared_ptr<eng::Image> ImageBackground::getImage() { return m_image; }
