#pragma once

#include <glm/glm.hpp>

#include "lc_client/eng_gui/widgets/dependencies.h"
#include "lc_client/eng_gui/widgets/layer.h"
#include "lc_client/eng_gui/widgets/rectangle.h"


class BlurBackground : public Background {
public:
	BlurBackground(glm::vec4 color, float blurIntensity, const GuiDependencies& guiDependencies);
	BlurBackground(unsigned int r, unsigned int g, unsigned int b, unsigned a,
		float blurIntensity, const GuiDependencies& guiDependencies);

	void setStencil(Rectangle& rectangle);
	void render(const Rectangle& rectangle, const Layer& layer) override;

private:
	glm::vec4 m_color;
	float m_blurIntensity;
	GuiDependencies m_guiDependencies;
	bool m_hasStencil;
	Rectangle m_stencil;
};