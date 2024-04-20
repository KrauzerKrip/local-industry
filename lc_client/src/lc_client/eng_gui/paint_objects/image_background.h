#pragma once

#include <string>

#include "background.h"
#include "lc_client/eng_graphics/texture.h"
#include "lc_client/eng_gui/widgets/dependencies.h"


class ImageBackground : public Background {
public:
	ImageBackground(std::string path, const GuiDependencies& dependencies);

	void render(const Rectangle& rectangle, const Layer& layer) override;

private:
	GuiDependencies m_dependencies;

	std::string m_path;
	BackgroundRender* m_pBackgroundRender = nullptr;
};
