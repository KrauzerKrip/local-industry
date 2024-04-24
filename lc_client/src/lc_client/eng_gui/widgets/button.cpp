#include "button.h"

#include <iostream>


Button::Button(GuiDependencies dependencies) : TextWidget(dependencies) {
	m_pInputController = dependencies.pInputController;
	m_pInputController->addReceiver(this);
};

void Button::mouseClick(MouseClickEvent event) {
	if (this->isVisible()) {
		if (m_rectangle.isPointIntersecting(event.position) && m_interactiveArea.isPointIntersecting(event.position)) {
			if ((event.button == KeyCode::MOUSE_BUTTON_LEFT)) {
				if (m_callback) {
					m_callback();
				}

				click();
			}
		}
	}
}

void Button::keyPressed(KeyEvent event) {}

void Button::characterInput(std::string character) {}

void Button::setCallback(std::function<void()> callback) { m_callback = callback; }

void Button::setBackground(Background* pBackground) { 
	m_pBackground = pBackground; 
	m_pDefaultBackground = pBackground;
	m_pHoverBackground = pBackground;
	m_pClickBackground = pBackground;
}

void Button::setHoverBackground(Background* pBackground) { m_pHoverBackground = pBackground; }

void Button::setClickBackground(Background* pBackground) { m_pClickBackground = pBackground; }

void Button::scroll(ScrollEvent event) {

}

void Button::click() { }

void Button::render() { 
	if (m_rectangle.isPointIntersecting(m_pInputController->getMousePosition())) {
		m_pBackground = m_pHoverBackground;
	}
	else {
		m_pBackground = m_pDefaultBackground;
	}

	TextWidget::render();
}
