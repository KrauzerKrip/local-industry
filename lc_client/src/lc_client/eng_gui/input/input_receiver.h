#pragma once

#include <string>
#include "events.h"
#include "lc_client/eng_gui/widgets/rectangle.h"

class InputReceiver {
public:
	virtual ~InputReceiver(){};

	virtual void mouseClick(MouseClickEvent event) = 0;
	virtual void keyPressed(KeyEvent event) = 0;
	virtual void characterInput(std::string character) = 0;
	virtual void scroll(ScrollEvent event) = 0;
};
