#pragma once

#include <glm/glm.hpp>
#include <string>
#include <array>
#include <queue>

#include "lc_client/eng_graphics/gui/background_render.h"
#include "lc_client/eng_graphics/entt/components.h"
#include "lc_client/eng_gui/paint_objects/text.h"
#include "lc_client/eng_graphics/openGL/gl_shader_work.h"


class ShaderWorkGl;

class BackgroundRenderGl : public BackgroundRender {
public:
	BackgroundRenderGl(IConsole* pConsole, ShaderWorkGl* pShaderWork);

	void renderColor(ColorQuad colorQuad);
	void renderImage(ImageQuad colorQuad);

private:
	std::queue<ColorQuad> m_colorQuads;
	std::queue<ImageQuad> m_imageQuads;

	unsigned int m_shader;
	unsigned int m_vao;
	unsigned int m_vbo;
	glm::mat4 m_projection;
};