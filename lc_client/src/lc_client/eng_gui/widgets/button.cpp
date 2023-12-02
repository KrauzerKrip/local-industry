#include "button.h"

void Button::mouseClick(MouseClickEvent event) {
	if (m_rectangle.isPointIntersecting(event.position)) {
		if (event.button == "left_mouse_button") {
			click();
		}
	}
}

void Button::keyPressed(KeyEvent event) {}

void Button::characterInput(std::string character) {}

void Button::click() {}
