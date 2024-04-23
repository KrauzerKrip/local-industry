#include "button.h"

#include <iostream>


Button::Button(GuiDependencies dependencies) : TextWidget(dependencies) {
    dependencies.pInputController->addReceiver(this);
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

void Button::scroll(ScrollEvent event) {

}

void Button::click() { }
