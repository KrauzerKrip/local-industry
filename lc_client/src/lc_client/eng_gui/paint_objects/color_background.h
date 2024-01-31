#pragma once

#include <memory>
#include <glm/glm.hpp>

#include "lc_client/eng_gui/widgets/dependencies.h"
#include "lc_client/eng_gui/widgets/layer.h"
#include "lc_client/eng_gui/widgets/rectangle.h"

class ColorBackground : public Background {
public:
	ColorBackground(glm::vec4 color, const GuiDependencies& guiDependencies);
	ColorBackground(unsigned int r, unsigned int g, unsigned int b, unsigned a, const GuiDependencies& guiDependencies);

    void render(const Rectangle& rectangle, const Layer& layer) override;

private:
	glm::vec4 m_color;
	GuiDependencies m_guiDependencies;
};
