#pragma once

#include "widget.h"
#include "lc_client/eng_gui/paint_objects/text.h"
#include "lc_client/eng_graphics/gui/text_render.h"

class TextWidget : public Widget {
public:
	TextWidget(Background* background, GuiDependencies dependencies);
	TextWidget(GuiDependencies dependencies);
	~TextWidget(){};
	
	void setText(std::string text);
	std::string getText();
	void setTextColor(glm::vec4 color);
	void setTextColor(unsigned int r, unsigned int g, unsigned int b, unsigned int a);
	void setTextSize(unsigned int size);
	virtual void render();

private:
	std::string m_text;
	unsigned int m_textSize;
	glm::vec4 m_textColor;
	Layer m_textLayer;

	TextRender* m_pTextRender = nullptr;

	GuiDependencies m_textDependencies;
};
