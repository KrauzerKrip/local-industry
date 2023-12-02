#pragma once

#include "widget.h"
#include "lc_client/eng_gui/paint_objects/text.h"
#include "lc_client/eng_graphics/gui/text_render.h"

class TextWidget : public Widget {
public:
	TextWidget(Background background, TextWidgetDependecies dependencies);
	~TextWidget(){};
	
	void setText(std::string text);
	std::string getText();
	void setColor(glm::vec4 color);
	void setTextSize(unsigned int size);
	void render();

private:
	std::string m_text;
	unsigned int m_size;
	glm::vec4 m_color;

	TextRender* m_pTextRender = nullptr;
};
