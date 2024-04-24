#include "image_background.h"

ImageBackground::ImageBackground(std::string path, const GuiDependencies& dependencies) : m_dependencies(dependencies) {
	m_path = path;
	m_pBackgroundRender = dependencies.pBackgroundRender;
	m_hasStencil = false;
}

void ImageBackground::setStencil(Rectangle& rectangle) {
	m_hasStencil = true;
	m_stencil = rectangle;
}

void ImageBackground::render(const Rectangle& rectangle, const Layer& layer) {
	if (m_hasStencil) {
		m_pBackgroundRender->renderImageStencil(ImageQuad({m_path, rectangle.getVertices(),
			m_dependencies.pWidgetZOffsetCalculator->calculateZOffset(layer.number)}), m_stencil.getVertices());
	}
	else {
		m_pBackgroundRender->renderImage(ImageQuad({m_path, rectangle.getVertices(),
			m_dependencies.pWidgetZOffsetCalculator->calculateZOffset(layer.number)}));
	}
}

