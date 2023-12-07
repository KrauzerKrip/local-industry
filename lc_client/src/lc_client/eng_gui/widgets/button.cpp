#include "button.h"

Button::Button(TextWidgetDependecies dependencies) : TextWidget(dependencies){};

void Button::mouseClick(MouseClickEvent event) {
	if (m_rectangle.isPointIntersecting(event.position)) {
		if (event.button == KeyCode::MOUSE_BUTTON_LEFT) {
			click();
		}
	}
}

void Button::keyPressed(KeyEvent event) {}

void Button::characterInput(std::string character) {}

void Button::click() { exit(0); }
