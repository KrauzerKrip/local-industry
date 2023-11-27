#pragma once

#include "widget.h"
#include "lc_client/eng_gui/paint_objects/text.h"
#include "lc_client/eng_graphics/gui/render_text.h"

class TextWidget : public Widget {
public:
	TextWidget(Background background, RenderBackground* pBackgroundRender, RenderText* pTextRender);
	~TextWidget(){};
	
	void setText(std::string text);
	std::string getText();
	void setColor(glm::vec4 color);
	void setTextSize(unsigned int size);
	void render(glm::vec2 absolutePosition, glm::vec2 size, unsigned int layer);

private:
	std::string m_text;
	unsigned int m_size;
	glm::vec4 m_color;

	RenderBackground* m_pBackgroundRender = nullptr;
	RenderText* m_pTextRender = nullptr;
};
