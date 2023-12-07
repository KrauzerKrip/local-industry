#pragma once

#include <ft2build.h>
#include FT_FREETYPE_H

#include <map>
#pragma once

#include <glm/glm.hpp>
#include <string>

#include "lc_client/eng_graphics/gui/text_render.h"
#include "lc_client/eng_graphics/entt/components.h"
#include "lc_client/eng_gui/paint_objects/text.h"
#include "lc_client/eng_graphics/gui/queue_render.h"
#include "lc_client/eng_graphics/openGL/gl_shader_work.h"

class ShaderWorkGl;

struct Character {
	unsigned int textureID; // ID handle of the glyph texture
	glm::ivec2 size;		// Size of glyph
	glm::ivec2 bearing;		// Offset from baseline to left/top of glyph
	unsigned int advance;	// Offset to advance to next glyph
};

class TextRenderGl : public TextRender {
public:
	TextRenderGl(IConsole* pConsole, ShaderWorkGl* pShaderWork);

	void render(std::string text, glm::vec4 color, glm::vec2 absolutePosition, unsigned int size, float zOffset);
	void renderCentered(
		std::string text, glm::vec4 color, glm::vec2 centerAbsolutePosition, unsigned int size, float zOffset);

private:
	std::map<char, Character> m_characters;
	unsigned int m_shader;
	unsigned int m_vao;
	unsigned int m_vbo;
	glm::mat4 m_projection;
};
