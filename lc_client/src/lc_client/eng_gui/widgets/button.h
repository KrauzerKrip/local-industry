#pragma once

#include <functional>

#include "text_widget.h"
#include "lc_client/eng_gui/input/input_receiver.h"


class Button : public TextWidget, public InputReceiver {
public:
	Button(GuiDependencies dependencies);

	void mouseClick(MouseClickEvent event);
	void keyPressed(KeyEvent event);
	void characterInput(std::string character);
	void setCallback(std::function<void()> callback);
	virtual void click();

private:
	std::function<void()> m_callback;
};
