#include "image_background.h"

ImageBackground::ImageBackground(std::shared_ptr<eng::Image> image) { m_image = std::move(image); }
void ImageBackground::render(const Rectangle& rectangle, const Layer& layer) {
    
}

