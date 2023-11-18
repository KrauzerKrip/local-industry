#pragma once

#include <glm/glm.hpp>
#include <string>
#include <array>
#include <queue>

#include "lc_client/eng_graphics/gui/render_background.h"
#include "lc_client/eng_graphics/entt/components.h"
#include "lc_client/eng_gui/paint_objects/text.h"

struct ColorQuad {
	Background background;
	std::array<glm::vec2, 4> vertices;
};

struct ImageQuad {
	ImageBackground background;
	std::array<glm::vec2, 4> vertices;
};

class RenderBackgroundGl : public RenderBackground {
public:
	RenderBackgroundGl(IConsole* pConsole, ShaderGl shader);

	void addToQueue(Background& background, std::array<glm::vec2, 4> vertices);
	void addToQueue(ImageBackground& background, std::array<glm::vec2, 4> vertices);
	void render();

private:
	std::queue<ColorQuad> m_colorQuads;
	std::queue<ImageQuad> m_imageQuads;

	unsigned int m_shader;
	unsigned int m_vao;
	unsigned int m_vbo;
	glm::mat4 m_projection;
};