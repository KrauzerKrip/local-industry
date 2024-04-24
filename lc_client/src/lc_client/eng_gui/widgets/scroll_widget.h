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

private:
	void input();

	void setWidgetInteractiveAreas(Layout* pLayout);

	bool m_isMouseScrolling;
	glm::vec2 m_lastMousePosition;

	VerticalScrollArea* m_pVerticalScrollArea = nullptr;
	Widget* m_pScrollbar = nullptr;
	Widget* m_pScrollThumb = nullptr;
	Widget* m_pScrollAreaWidget = nullptr;

	GuiDependencies m_dependencies;

	static const int m_scrollbarWidth;
};