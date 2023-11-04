#pragma once

#include <ft2build.h>
#include FT_FREETYPE_H

#include <map>
#include <glm/glm.hpp>
#include <string>

#include "lc_client/tier0/console/i_console.h"


struct Character {
	unsigned int textureID; // ID handle of the glyph texture
	glm::ivec2 size;		// Size of glyph
	glm::ivec2 bearing;		// Offset from baseline to left/top of glyph
	unsigned int advance;	// Offset to advance to next glyph
};

class Text {
public:
	Text(IConsole* pConsole);

	void render(unsigned int shaderProgram, std::string text, float x, float y, float scale, glm::vec3 color);

private:
	IConsole* m_pConsole = nullptr;
	std::map<char, Character> m_characters;
	unsigned int m_vao;
	unsigned int m_vbo;
	glm::mat4 m_projection;
};
