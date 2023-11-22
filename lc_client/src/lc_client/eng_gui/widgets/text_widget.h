#pragma once

#include "widget.h"
#include "lc_client/eng_gui/paint_objects/text.h"
#include "lc_client/eng_graphics/gui/render_text.h"

class TextWidget : Widget {
public:
	TextWidget(Text text, Background background, RenderBackground* pBackgroundRender, RenderText* pRanderText);
	~TextWidget(){};
	
	Text getText();

private:
	Text m_text;
};
