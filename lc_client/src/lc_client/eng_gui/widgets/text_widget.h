#pragma once

#include "widget.h"
#include "lc_client/eng_gui/paint_objects/text.h"

class TextWidget : Widget {
public:
	TextWidget(Text text);
	~TextWidget(){};
	
	Text getText();

private:
	Text m_text;
};
