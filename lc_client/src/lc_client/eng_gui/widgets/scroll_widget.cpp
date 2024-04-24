#include "scroll_widget.h"

#include <iostream>


ScrollWidget::ScrollWidget(GuiDependencies dependencies) : m_dependencies(dependencies) { 
	m_isMouseScrolling = false;
	m_lastMousePosition = glm::vec2(0);
	m_scrollbarWidth = 32;
	m_scrollbarPadding = glm::vec2(5, 5);
	m_isThumbVoid = false;

	dependencies.pInputController->addReceiver(this);

	HBox* pHBox = new HBox();
	this->setLayout(pHBox);
	pHBox->setBoxMode(BoxMode::STRETCH_WIDGETS);
	pHBox->setSpacing(5);

	m_pScrollAreaWidget = new Widget();
	pHBox->addChild(m_pScrollAreaWidget);
	m_pScrollAreaWidget->setSizePolicy(SizePolicy::RESIZE);

	m_pVerticalScrollArea = new VerticalScrollArea();
	m_pScrollAreaWidget->setLayout(m_pVerticalScrollArea);
	m_pVerticalScrollArea->setSpacing(5);
	
	m_pScrollbar = new Widget();
	pHBox->addChild(m_pScrollbar);
	m_pScrollbar->setName("scrollbar");
	m_pScrollbar->setSizePolicy(SizePolicy::FIXED);
	Frame* pScrollbarFrame = new Frame();
	m_pScrollbar->setLayout(pScrollbarFrame);
	m_pScrollThumb = new Widget(new ColorBackground(0, 0, 0, 255, dependencies));
	pScrollbarFrame->addChild(m_pScrollThumb);
}


void ScrollWidget::render() {
	if (m_isThumbVoid) {
		m_pScrollbar->getBackground()->setStencil(m_pScrollThumb->getRectangle());
	}

	this->input();

	float contentSize = static_cast<float>(m_pVerticalScrollArea->getContentSize());
	float notFittingSize = static_cast<float>(m_pVerticalScrollArea->getNotFittingSize());

	int scrollspace = m_size.y - m_scrollbarPadding.y * 2;


	int scrollThumbHeight = scrollspace;
	if (notFittingSize > 0) {
		scrollThumbHeight -= scrollThumbHeight * (notFittingSize / contentSize);
	}

	m_pScrollThumb->setSize(m_scrollbarWidth - m_scrollbarPadding.x * 2, scrollThumbHeight);
	m_pScrollbar->setSize(m_scrollbarWidth, m_size.y);
	m_pScrollAreaWidget->setSize(m_size.x, m_size.y);

	int scrollThumbPosY = (scrollspace - scrollThumbHeight) * (1.0f - m_pVerticalScrollArea->getScroll()) + m_scrollbarPadding.y;
	m_pScrollThumb->setPosition(m_scrollbarPadding.x, scrollThumbPosY);
	
	this->setWidgetInteractiveAreas(m_pVerticalScrollArea);

	m_dependencies.pBackgroundRender->enableScissors(m_rectangle.m_absolutePosition.x, 
		m_rectangle.m_absolutePosition.y, 
		m_rectangle.m_size.x,
		m_rectangle.m_size.y);

	Widget::render();

	m_dependencies.pBackgroundRender->disableScissors();
}

void ScrollWidget::mouseClick(MouseClickEvent event) {}

void ScrollWidget::keyPressed(KeyEvent event) {}

void ScrollWidget::characterInput(std::string character) {}

void ScrollWidget::scroll(ScrollEvent event) { m_pVerticalScrollArea->scroll(event.offset * 10); }

void ScrollWidget::addWidget(Widget* pWidget) { m_pVerticalScrollArea->addChild(pWidget); }

void ScrollWidget::setScrollbarBackground(Background* pBackground) { m_pScrollbar->setBackground(pBackground); }

void ScrollWidget::setScrollThumbBackground(Background* pBackground) { m_pScrollThumb->setBackground(pBackground); }

void ScrollWidget::setScrollbarWidgth(int width) { m_scrollbarWidth = width; }

void ScrollWidget::enableVoidThumb() { m_isThumbVoid = true; }

void ScrollWidget::input() { 
	InputController* pInputController = m_dependencies.pInputController;

	if (pInputController->isKeyPressed(KeyCode::MOUSE_BUTTON_LEFT)) {
		if (m_pScrollThumb->getRectangle().isPointIntersecting(pInputController->getMousePosition())) {
			m_isMouseScrolling = true;
		}
	}
	else {
		m_isMouseScrolling = false;
	}

	glm::vec2 pos = pInputController->getMousePosition();
	if (m_isMouseScrolling) {
		glm::vec2 posOffset = pos - m_lastMousePosition;
		m_pVerticalScrollArea->scroll(posOffset.y);
	}
	m_lastMousePosition = pos;
}

void ScrollWidget::setWidgetInteractiveAreas(Layout* pLayout) { 
	for (Widget* pWidget : pLayout->getChildrenWidgets()) {
		pWidget->setInteractiveArea(m_rectangle);
		if (pWidget->getLayout()) {
			this->setWidgetInteractiveAreas(pWidget->getLayout());
		}
	}
}