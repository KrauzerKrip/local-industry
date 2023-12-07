#pragma once

#include "text_widget.h"
#include "lc_client/eng_gui/input/input_receiver.h"


class Button : public TextWidget, public InputReceiver {
public:
	Button(TextWidgetDependecies dependencies);

	void mouseClick(MouseClickEvent event);
	void keyPressed(KeyEvent event);
	void characterInput(std::string character);
	virtual void click();

private:
};
