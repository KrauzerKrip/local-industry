#pragma once

#include "lc_client/eng_gui/includes.h"


class ScrollWidget : public Widget, public InputReceiver {
public:
	ScrollWidget(GuiDependencies dependencies);

	void render() override;
	void mouseClick(MouseClickEvent event) override;
	void keyPressed(KeyEvent event) override;
	void characterInput(std::string character) override;
	void scroll(ScrollEvent event) override;
	void addWidget(Widget* pWidget);
	void setScrollbarBackground(Background* pBackground);
	void setScrollThumbBackground(Background* pBackground);
	void setHoverScrollThumbBackground(Background* pBackground);
	void setScrollbarWidgth(int width);
	void enableVoidThumb();

private:
	void input();

	void setWidgetInteractiveAreas(Layout* pLayout);

	bool m_isMouseScrolling;
	glm::vec2 m_lastMousePosition;

	VerticalScrollArea* m_pVerticalScrollArea = nullptr;
	Widget* m_pScrollbar = nullptr;
	Button* m_pScrollThumb = nullptr;
	Widget* m_pScrollAreaWidget = nullptr;

	GuiDependencies m_dependencies;

	int m_scrollbarWidth;
	glm::vec2 m_scrollbarPadding;
	bool m_isThumbVoid;
};