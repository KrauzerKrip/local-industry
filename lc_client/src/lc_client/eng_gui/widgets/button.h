#pragma once

#include "widget.h"
#include "lc_client/eng_gui/input/input_receiver.h"


class Button : public Widget, public InputReceiver {
public:
	Button(WidgetDependecies dependencies);

	void mouseClick(MouseClickEvent event);
	void keyPressed(KeyEvent event);
	void characterInput(std::string character);
	virtual void click();

private:
};
