#include "image_background.h"

ImageBackground::ImageBackground(std::string path, const GuiDependencies& dependencies) : m_dependencies(dependencies) {
	m_path = path;
	m_pBackgroundRender = dependencies.pBackgroundRender;
}
void ImageBackground::render(const Rectangle& rectangle, const Layer& layer) {
	m_pBackgroundRender->renderImage(ImageQuad({m_path, rectangle.getVertices(),
		m_dependencies.pWidgetZOffsetCalculator->calculateZOffset(layer.number)}));
}

