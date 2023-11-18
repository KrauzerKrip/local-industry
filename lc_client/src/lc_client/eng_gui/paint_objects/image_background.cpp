#include "image_background.h"

ImageBackground::Background(std::shared_ptr<eng::Image> image) { m_image = image; }

std::shared_ptr<eng::Image> ImageBackground::getImage() { return m_image; }
