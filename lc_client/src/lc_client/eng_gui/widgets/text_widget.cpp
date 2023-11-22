#include "text_widget.h"

TextWidget::TextWidget(Text text, Background background, RenderBackground* pBackgroundRender, RenderText* pRanderText)
	: Widget(background, pBackgroundRender), m_text(text) {
}

Text TextWidget::getText() { return m_text; }
