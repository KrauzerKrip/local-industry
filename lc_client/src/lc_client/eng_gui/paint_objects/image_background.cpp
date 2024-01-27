#include "image_background.h"

ImageBackground::ImageBackground(std::string path, GuiDependencies dependencies) : m_dependencies(dependencies) {
	m_pTexture = dependencies.pBackgroundRender->getTexture(path);
	m_pTexture->setTextureType(TextureType::NORMAL);
    m_pTexture->load();
	m_pBackgroundRender = dependencies.pBackgroundRender;
}
void ImageBackground::render(const Rectangle& rectangle, const Layer& layer) {
	m_pBackgroundRender->renderImage(ImageQuad({m_pTexture, rectangle.getVertices(),
		m_dependencies.pWidgetZOffsetCalculator->calculateZOffset(layer.number)}));
}

