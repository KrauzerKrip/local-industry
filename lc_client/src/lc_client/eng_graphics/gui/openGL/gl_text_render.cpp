#include "gl_text_render.h"

#include <glad/glad.h>
#include <glm/gtc/matrix_transform.hpp>
#include<glm/gtc/type_ptr.hpp>
#include <iostream>
#include "lc_client/eng_graphics/openGL/gl_shader_uniform.h"

TextRenderGl::TextRenderGl(IConsole* pConsole, ShaderWorkGl* pShaderWork) : TextRender(pConsole) {
	m_shader = pShaderWork->createShaderProgram("gui_text", "gui_text");

	FT_Library ft;
	if (FT_Init_FreeType(&ft)) {
		m_pConsole->warn("ERROR::FREETYPE: Could not init FreeType Library");
		std::cout << "ERROR::FREETYPE: Could not init FreeType Library" << std::endl;
	}
	FT_Face face;
	if (FT_New_Face(ft, "C:\\Windows\\Fonts\\arial.ttf", 0, &face)) {
		m_pConsole->warn("ERROR::FREETYPE: Failed to load font");
		std::cout << "ERROR::FREETYPE: Failed to load font" << std::endl;
	}

	FT_Set_Pixel_Sizes(face, 0, 48);

	glPixelStorei(GL_UNPACK_ALIGNMENT, 1); // no byte-alignment restriction

	for (unsigned char c = 0; c < 128; c++) {
		// load character glyph
		if (FT_Load_Char(face, c, FT_LOAD_RENDER)) {
			m_pConsole->warn("ERROR::FREETYTPE: Failed to load Glyph");
			continue;
		}
		// generate texture
		unsigned int texture;
		glGenTextures(1, &texture);
		glBindTexture(GL_TEXTURE_2D, texture);
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RED, face->glyph->bitmap.width, face->glyph->bitmap.rows, 0, GL_RED,
			GL_UNSIGNED_BYTE, face->glyph->bitmap.buffer);
		// set texture options
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		// now store character for later use
		Character character = {texture, glm::ivec2(face->glyph->bitmap.width, face->glyph->bitmap.rows),
			glm::ivec2(face->glyph->bitmap_left, face->glyph->bitmap_top), face->glyph->advance.x};
		m_characters.insert(std::pair<char, Character>(c, character));
	}

	FT_Done_Face(face);
	FT_Done_FreeType(ft);

	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	m_projection = glm::ortho(0.0f, 1920.0f, 0.0f, 1080.0f);

	glGenVertexArrays(1, &m_vao);
	glGenBuffers(1, &m_vbo);
	glBindVertexArray(m_vao);
	glBindBuffer(GL_ARRAY_BUFFER, m_vbo);
	glBufferData(GL_ARRAY_BUFFER, sizeof(float) * 6 * 4, NULL, GL_DYNAMIC_DRAW);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 4 * sizeof(float), 0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);
}

void TextRenderGl::render(
	std::string text, glm::vec4 color, glm::vec2 absolutePosition, unsigned int size, float zOffset) {
	float x = absolutePosition.x;
	float y = absolutePosition.y;
	std::string textString = text;

	// activate corresponding render state
	glUseProgram(m_shader);
	unsigned int projLoc = glGetUniformLocation(m_shader, "projection");
	glUniformMatrix4fv(projLoc, 1, GL_FALSE, glm::value_ptr(m_projection));
	glUniform3f(glGetUniformLocation(m_shader, "textColor"), color.x, color.y, color.z);
	setUniform(m_shader, "textColor", color);
	setUniform(m_shader, "zOffset", zOffset);

	glActiveTexture(GL_TEXTURE0);
	glBindVertexArray(m_vao);
	// iterate through all characters
	std::string::const_iterator c;

	float scale = float(size) / 48.0f;

	for (c = textString.begin(); c != textString.end(); c++) {
		Character ch = m_characters[*c];
		float xpos = x + ch.bearing.x * scale;
		float ypos = y - (ch.size.y - ch.bearing.y) * scale;
		float w = ch.size.x * scale;
		float h = ch.size.y * scale;
		// update m_vbo for each char.acter
		float vertices[6][4] = {{xpos, ypos + h, 0.0f, 0.0f}, {xpos, ypos, 0.0f, 1.0f}, {xpos + w, ypos, 1.0f, 1.0f},
			{xpos, ypos + h, 0.0f, 0.0f}, {xpos + w, ypos, 1.0f, 1.0f}, {xpos + w, ypos + h, 1.0f, 0.0f}};
		// render glyph texture over quad
		glBindTexture(GL_TEXTURE_2D, ch.textureID);
		// update content of m_vbo memory
		glBindBuffer(GL_ARRAY_BUFFER, m_vbo);
		glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(vertices), vertices);
		glBindBuffer(GL_ARRAY_BUFFER, 0);
		// render quad
		glDrawArrays(GL_TRIANGLES, 0, 6);
		// advance cursors for next glyph (advance is 1/64 pixels)
		x += (ch.advance >> 6) * scale; // bitshift by 6 (2^6 = 64)
	}

	glBindVertexArray(0);
	glBindTexture(GL_TEXTURE_2D, 0);
}

void TextRenderGl::renderCentered(
	std::string text, glm::vec4 color, glm::vec2 centerAbsolutePosition, unsigned int size, float zOffset) {
	
	std::string::const_iterator c;

	float scale = float(size) / 48.0f;

	float textWidth = 0;
	float maxHeight = 0;

	for (c = text.begin(); c != text.end(); c++) {
		Character ch = m_characters[*c];
		float xpos = ch.bearing.x * scale;
		float ypos = (ch.size.y - ch.bearing.y) * scale;
		float w = ch.size.x * scale;
		float h = ch.size.y * scale;

		maxHeight = std::max(maxHeight, h);

		textWidth += w;
	}

	float x = centerAbsolutePosition.x - (textWidth / 2);
	float y = centerAbsolutePosition.y - (maxHeight / 2);

	// activate corresponding render state
	glUseProgram(m_shader);
	unsigned int projLoc = glGetUniformLocation(m_shader, "projection");
	glUniformMatrix4fv(projLoc, 1, GL_FALSE, glm::value_ptr(m_projection));
	glUniform3f(glGetUniformLocation(m_shader, "textColor"), color.x, color.y, color.z);
	setUniform(m_shader, "textColor", color);
	setUniform(m_shader, "zOffset", zOffset);

	glActiveTexture(GL_TEXTURE0);
	glBindVertexArray(m_vao);
	// iterate through all characters
	c = std::string::const_iterator();

	for (c = text.begin(); c != text.end(); c++) {
		Character ch = m_characters[*c];
		float xpos = x + ch.bearing.x * scale;
		float ypos = y - (ch.size.y - ch.bearing.y) * scale;
		float w = ch.size.x * scale;
		float h = ch.size.y * scale;
		// update m_vbo for each char.acter
		float vertices[6][4] = {{xpos, ypos + h, 0.0f, 0.0f}, {xpos, ypos, 0.0f, 1.0f}, {xpos + w, ypos, 1.0f, 1.0f},
			{xpos, ypos + h, 0.0f, 0.0f}, {xpos + w, ypos, 1.0f, 1.0f}, {xpos + w, ypos + h, 1.0f, 0.0f}};
		// render glyph texture over quad
		glBindTexture(GL_TEXTURE_2D, ch.textureID);
		// update content of m_vbo memory
		glBindBuffer(GL_ARRAY_BUFFER, m_vbo);
		glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(vertices), vertices);
		glBindBuffer(GL_ARRAY_BUFFER, 0);
		// render quad
		glDrawArrays(GL_TRIANGLES, 0, 6);
		// advance cursors for next glyph (advance is 1/64 pixels)
		x += (ch.advance >> 6) * scale; // bitshift by 6 (2^6 = 64)
	}

	glBindVertexArray(0);
	glBindTexture(GL_TEXTURE_2D, 0);
}
